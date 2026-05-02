# SPDX-FileCopyrightText: 2020 Carl Schwan <carl@carlschwan.eu>
#
# SPDX-License-Identifier: BSD-2-Clause

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/code)

add_library(${PROJECT_NAME} SHARED)

ecm_add_qml_module(${PROJECT_NAME}
    URI "org.mauicore.notifications"
    VERSION 1.0
    CLASS_NAME NotificationsPlugin
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_PLUGIN_SOURCE)

set(SRCS
    code/notificationimagesstorage.cpp
    code/notificationserver.cpp
    code/notifications.cpp
    code/notificationsimageutils.cpp
    code/notificationsimageprovider.cpp
    code/notifications_plugin.cpp
    code/notification.cpp
    code/notificationsmodel.cpp
    code/historymodel.cpp
    code/datehelper.cpp)

set(headers
    code/notificationimagesstorage.h
    code/notificationserver.h
    code/notifications.h
    code/notificationsimageutils.h
    code/notificationsimageprovider.h
    code/notification.h
    code/notificationsmodel.h
    code/historymodel.h
    code/datehelper.h)

qt_add_dbus_interface(SRCS code/org.freedesktop.Notifications.xml notifications_interface)
qt_add_dbus_adaptor(SRCS code/org.freedesktop.Notifications.xml code/notificationserver.h NotificationServer notifications_adaptor)

target_sources(${PROJECT_NAME}plugin
    PRIVATE
    ${SRCS}
    ${headers})

add_library(MauiCore::Notifications ALIAS ${PROJECT_NAME})

generate_export_header(${PROJECT_NAME} BASE_NAME Notifications)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME Notifications)

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Notifications>")

target_include_directories(${PROJECT_NAME}  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

target_link_libraries(${PROJECT_NAME}plugin
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::DBus
    Qt6::Gui
    KF6::I18n)

ecm_finalize_qml_module(${PROJECT_NAME} DESTINATION ${KDE_INSTALL_QMLDIR})

install(TARGETS ${PROJECT_NAME} EXPORT MauiCoreNotificationsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    ${headers}
    ${CMAKE_CURRENT_BINARY_DIR}/notifications_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Notifications
    COMPONENT Devel)
