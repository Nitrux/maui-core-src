# Copyright 2018-2020 Camilo Higuita <milo.h@aol.com>
# Copyright 2018-2020 Nitrux Latinoamericana S.C.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

project(MauiCore VERSION ${MAUICORE_VERSION})

set(REQUIRED_QT_VERSION 6.4)
set(REQUIRED_KF_VERSION 5.240.0)

set(KDE_COMPILERSETTINGS_LEVEL "5.82")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ECM ${REQUIRED_KF_VERSION} NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)

include(GenerateExportHeader)
include(FeatureSummary)
include(CMakePackageConfigHelpers)

include(ECMSetupVersion)
include(ECMGenerateQmlTypes)
include(ECMFindQmlModule)
include(ECMQmlModule)

include(KDEPackageAppTemplates)
include(KDECompilerSettings)

##CMAKE PARTS
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/MauiCore")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/MauiCoreConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_PREFIX)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX MauiCore
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/mauicore_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/MauiCoreConfigVersion.cmake"
    SOVERSION ${PROJECT_VERSION_MAJOR})

add_subdirectory(audio)
add_subdirectory(notifications)
add_subdirectory(power)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
