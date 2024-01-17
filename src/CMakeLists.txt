# Addon config file
# We need additional layer of conversion because we want PROJECT_VERSION in it.
configure_file(ipa-sil-addon.conf.in ipa-sil-addon.conf)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ipa-sil-addon.conf" RENAME ipa-sil.conf DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon")
# Make the dictionary
set(mb_file "${CMAKE_CURRENT_BINARY_DIR}/ipa-sil.main.dict")
add_custom_command(OUTPUT "ipa-sil.main.dict"
  DEPENDS "ipa-sil.txt"
  COMMAND LibIME::tabledict ARGS "${CMAKE_CURRENT_SOURCE_DIR}/ipa-sil.txt"
  "${CMAKE_CURRENT_BINARY_DIR}/ipa-sil.main.dict")
add_custom_target(table_data ALL DEPENDS "${mb_file}")

# Input Method registration file
install(FILES "ipa-sil.conf" DESTINATION "${FCITX_INSTALL_PKGDATADIR}/inputmethod")
# Table dictionary
install(FILES "${mb_file}" DESTINATION "${FCITX_INSTALL_PKGDATADIR}/table")
