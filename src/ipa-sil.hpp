*
 * SPDX-FileCopyrightText: 2023 Yuki Joou <yukijoou [a] kemonomimi [-] gay>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#pragma once

#include <fcitx-utils/inputbuffer.h>
#include <fcitx/addonfactory.h>
#include <fcitx/addonmanager.h>
#include <fcitx/inputcontextproperty.h>
#include <fcitx/inputmethodengine.h>
#include <fcitx/instance.h>

#include <optional>
#include <string>

class SILEngine;

class SILState : public fcitx::InputContextProperty
{
  public:
	SILState(SILEngine* engine, fcitx::InputContext* ic)
	    : m_engine(engine), m_ic(ic)
	{
	}

	void handleAlphaKey(fcitx::Key);
	void keyEvent(fcitx::KeyEvent& keyEvent);

	void updateUI();

	void reset()
	{
		m_buffer.clear();
		updateUI();
	}

  private:
	SILEngine*           m_engine;
	fcitx::InputContext* m_ic;
	fcitx::InputBuffer   m_buffer{{fcitx::InputBufferOption::NoOption}};

	std::optional<std::string> m_lastKey{};
};

class SILEngine : public fcitx::InputMethodEngineV2
{
  public:
	SILEngine(fcitx::Instance*);

	void keyEvent(const fcitx::InputMethodEntry&, fcitx::KeyEvent&) override;
	void reset(const fcitx::InputMethodEntry&,
	           fcitx::InputContextEvent&) override;

  private:
	fcitx::FactoryFor<SILState> m_factory;
};

class SILEngineFactory : public fcitx::AddonFactory
{
	fcitx::AddonInstance* create(fcitx::AddonManager* manager) override
	{
		FCITX_UNUSED(manager);
		return new SILEngine(manager->instance());
	}
};

