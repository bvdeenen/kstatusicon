project(kstatusicon)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

# Search KDE installation
find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include (MacroLibrary)

qt4_generate_dbus_interface("toplevel.h" A)
add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${KDE4_INCLUDES})

set(kstatusicon_SRCS toplevel.cpp main.cpp )
qt4_add_dbus_adaptor(kstatusicon_SRCS com.vandeenensupport.TopLevel.xml toplevel.h TopLevel)

#kde4_add_ui_files(kstatusicon_SRCS settings.ui timeedit.ui)
kde4_add_app_icon(kstatusicon_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/../data/icons/hi*-app-kstatusicon.png")
kde4_add_executable(kstatusicon ${kstatusicon_SRCS})
target_link_libraries(kstatusicon ${KDE4_KNOTIFYCONFIG_LIBS} ${KDE4_KDEUI_LIBS})

#install( TARGETS kstatusicon ${INSTALL_TARGETS_DEFAULT_ARGS} )
#install( FILES kstatusicon.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
#install( FILES kstatusicon.notifyrc  DESTINATION ${DATA_INSTALL_DIR}/kstatusicon )
