/*
 * SPDX-FileCopyrightText: 2023 Yuki Joou <yukijoou [a] kemonomimi [-] gay>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "ipa-sil.hpp"

#include <fcitx/inputpanel.h>
#include <fcitx/instance.h>

std::optional<std::string> getIPAForSIL(std::string   baseCharacter,
                                        fcitx::KeySym silModifier)
{
	// TODO: Use a proper data structure, like a hash map
	//       Even better: load that data off of a file!

	// TODO: Add more characters! This is only enough for narrow RP
	//       transcriptions...
	if (baseCharacter == "s") {
		if (silModifier == FcitxKey_equal) return "ʃ";
	}

	if (baseCharacter == "z") {
		if (silModifier == FcitxKey_equal) return "ʒ";
	}

	if (baseCharacter == "t") {
		if (silModifier == FcitxKey_equal) return "θ";
	}

	if (baseCharacter == "d") {
		if (silModifier == FcitxKey_equal) return "ð";
	}

	if (baseCharacter == "n") {
		if (silModifier == FcitxKey_greater) return "ŋ";
	}

	if (baseCharacter == "i") {
		if (silModifier == FcitxKey_equal) return "ɪ";
	}

	if (baseCharacter == "e") {
		if (silModifier == FcitxKey_equal) return "ə";
	}

	if (baseCharacter == "a") {
		if (silModifier == FcitxKey_less) return "æ";
		if (silModifier == FcitxKey_equal) return "ɑ";
	}

	if (baseCharacter == "o") {
		if (silModifier == FcitxKey_less) return "ɔ";
		if (silModifier == FcitxKey_equal) return "ɒ";
	}

	if (baseCharacter == "u") {
		if (silModifier == FcitxKey_greater) return "ʌ";
		if (silModifier == FcitxKey_less) return "ʊ";
	}

	return {};
}

bool isSILModifier(fcitx::KeySym key)
{
	return key == FcitxKey_less || key == FcitxKey_greater ||
	       key == FcitxKey_equal;
}

void SILState::handleAlphaKey(fcitx::Key key)
{
	// TODO: Don't make this a special case, have a better system for handling
	//       this!
	if (key.check(FcitxKey_colon)) {
		m_buffer.type("ː");
		m_lastKey.reset();
		return;
	}
	
	if (!isSILModifier(key.sym()) || !m_lastKey.has_value()) {
		m_lastKey = key.toString();
		m_buffer.type(key.sym());
		return;
	}

	if (isSILModifier(key.sym())) {
		auto ipaChar = getIPAForSIL(*m_lastKey, key.sym());
		if (ipaChar) {
			m_buffer.backspace();
			m_buffer.type(*ipaChar);
		}
		m_lastKey.reset();
	}
}

void SILState::keyEvent(fcitx::KeyEvent& keyEvent)
{
	// If it's not a simple letter key, and we have no text input yet, let it
	// through.
	if (m_buffer.empty() && !keyEvent.key().isSimple()) return;

	if (keyEvent.key().check(FcitxKey_Return)) {
		m_ic->commitString(m_buffer.userInput());
		reset();
	} else if (keyEvent.key().check(FcitxKey_space)) {
		m_ic->commitString(m_buffer.userInput());
		m_ic->commitString(" ");
		reset();
	} else if (keyEvent.key().check(FcitxKey_BackSpace))
		m_buffer.backspace();
	else if (keyEvent.key().isSimple())
		handleAlphaKey(keyEvent.key());
	//	m_buffer.type(keyEvent.key().sym());
	updateUI();

	keyEvent.filterAndAccept();
}

void SILState::updateUI()
{
	auto& inputPanel = m_ic->inputPanel();
	inputPanel.reset();

	if (m_ic->capabilityFlags().test(fcitx::CapabilityFlag::Preedit)) {
		fcitx::Text preedit(m_buffer.userInput(),
		                    fcitx::TextFormatFlag::HighLight);
		inputPanel.setClientPreedit(preedit);
	} else {
		fcitx::Text preedit(m_buffer.userInput());
		inputPanel.setPreedit(preedit);
	}
	m_ic->updateUserInterface(fcitx::UserInterfaceComponent::InputPanel);
	m_ic->updatePreedit();
}

SILEngine::SILEngine(fcitx::Instance* instance)
    : m_factory(
          [this](fcitx::InputContext& ic) { return new SILState(this, &ic); })
{
	instance->inputContextManager().registerProperty("silState", &m_factory);
}

void SILEngine::keyEvent(const fcitx::InputMethodEntry&,
                         fcitx::KeyEvent& keyEvent)
{
	if (keyEvent.isRelease() || keyEvent.key().states()) {
		return;
	}

	auto  ic    = keyEvent.inputContext();
	auto* state = ic->propertyFor(&m_factory);
	state->keyEvent(keyEvent);
}

void SILEngine::reset(const fcitx::InputMethodEntry&,
                      fcitx::InputContextEvent& event)
{
	auto* state = event.inputContext()->propertyFor(&m_factory);
	state->reset();
}

FCITX_ADDON_FACTORY(SILEngineFactory);

