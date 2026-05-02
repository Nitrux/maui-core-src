include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/code)

add_library(${PROJECT_NAME} SHARED)

set(power_SRCS
    code/powermanagementengine.cpp
    code/powermanagementjob.cpp
    code/brightnesscontrol.cpp
    code/batteryinfo.cpp
    code/powerprofile.cpp
    code/inhibitioncontrol.cpp)

set(plugin_SRCS
    code/powerplugin.cpp
    code/powerplugin.h)

ecm_add_qml_module(${PROJECT_NAME}
    URI "org.mauicore.power"
    VERSION 1.0
    CLASS_NAME PowerPlugin
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_PLUGIN_SOURCE)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${power_SRCS})

target_sources(${PROJECT_NAME}plugin
    PRIVATE
    ${plugin_SRCS})

add_library(MauiCore::Power ALIAS ${PROJECT_NAME})

generate_export_header(${PROJECT_NAME} BASE_NAME Power)
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME "Power")

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    KF6::Solid
    KF6::IdleTime
    KF6::CoreAddons
    KF6::I18n
    KF6::Service
    Qt6::DBus)

target_link_libraries(${PROJECT_NAME}plugin
    PRIVATE
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
    ${PROJECT_NAME})

ecm_finalize_qml_module(${PROJECT_NAME} DESTINATION ${KDE_INSTALL_QMLDIR})
ecm_generate_qmltypes(org.mauicore.power ${PROJECT_VERSION} DESTINATION ${KDE_INSTALL_QMLDIR}/org/mauicore/power)

install(TARGETS ${PROJECT_NAME} EXPORT MauiCorePowerTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/power_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power
    COMPONENT Devel)
