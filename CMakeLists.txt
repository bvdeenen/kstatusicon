set(kstatusicon_SRCS toplevel.cpp main.cpp )

#kde4_add_ui_files(kstatusicon_SRCS settings.ui timeedit.ui)
kde4_add_app_icon(kstatusicon_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../data/icons/hi*-app-kstatusicon.png")
kde4_add_executable(kstatusicon ${kstatusicon_SRCS})
target_link_libraries(kstatusicon ${KDE4_KNOTIFYCONFIG_LIBS} ${KDE4_KDEUI_LIBS})

install( TARGETS kstatusicon ${INSTALL_TARGETS_DEFAULT_ARGS} )
install( FILES kstatusicon.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kstatusicon.notifyrc  DESTINATION ${DATA_INSTALL_DIR}/kstatusicon )
