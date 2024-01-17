add_library(ipa-sil SHARED ipa-sil.cpp)
target_link_libraries(ipa-sil PRIVATE Fcitx5::Core)
set_target_properties(ipa-sil PROPERTIES PREFIX "")
install(TARGETS ipa-sil DESTINATION "${FCITX_INSTALL_LIBDIR}/fcitx5")

# Addon config file
# We need additional layer of conversion because we want PROJECT_VERSION in it.
configure_file(ipa-sil-addon.conf.in ipa-sil-addon.conf)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ipa-sil-addon.conf" RENAME ipa-sil.conf DESTINATION "${FCITX_INSTALL_PKGDATADIR}/addon")

# Input Method registration file
install(FILES "ipa-sil.conf" DESTINATION "${FCITX_INSTALL_PKGDATADIR}/inputmethod")

