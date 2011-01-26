project(kstatusicon)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

# Search KDE installation
find_package(KDE4 COMPONENTS )
include (KDE4Defaults)
include (MacroLibrary)

qt4_generate_dbus_interface(toplevel.h com.vandeenensupport.TopLevel.xml -A)

set(kstatusicon_SRCS toplevel.cpp main.cpp )
qt4_add_dbus_adaptor(kstatusicon_SRCS com.vandeenensupport.TopLevel.xml toplevel.h TopLevel)
add_definitions (${QT_DEFINITIONS} ${QT_QTDBUS_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories (${KDE4_INCLUDES})

kde4_add_executable(kstatusicon ${kstatusicon_SRCS})
target_link_libraries(kstatusicon ${KDE4_KNOTIFYCONFIG_LIBS} ${KDE4_KDEUI_LIBS})

