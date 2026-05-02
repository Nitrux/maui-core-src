# SPDX-FileCopyrightText: 2021 Camilo Higuita <milo.h@aol.com>
#
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)

set(AUTOMOC_MOC_OPTIONS -Muri=org.mauicore.power)

project(MauiCorePower LANGUAGES CXX VERSION ${MAUICORE_VERSION})

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/MauiCorePower")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/MauiCorePowerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCorePowerConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_PREFIX)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCorePowerConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCorePowerConfig.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel)

install(EXPORT MauiCorePowerTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE MauiCorePowerTargets.cmake
    NAMESPACE MauiCore::)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX ${PROJECT_NAME}
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mauicorepower_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/MauiCorePowerConfigVersion.cmake"
    SOVERSION ${PROJECT_VERSION_MAJOR})

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/mauicorepower_version.h"
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/Maui/Core/Power
    COMPONENT Devel)

find_package(Qt6 ${REQUIRED_QT_VERSION} COMPONENTS Core Qml Quick DBus Gui REQUIRED)
find_package(KF6 ${REQUIRED_KF_VERSION} REQUIRED COMPONENTS I18n Solid IdleTime CoreAddons Service)

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
