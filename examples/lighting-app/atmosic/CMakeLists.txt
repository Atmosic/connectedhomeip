#
#    Copyright (c) 2020-2024 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#
cmake_minimum_required(VERSION 3.13.1)

get_filename_component(CHIP_ROOT $ENV{ZEPHYR_BASE}/../modules/lib/matter REALPATH)
get_filename_component(ATMOSIC_COMMON ${CHIP_ROOT}/examples/platform/atmosic REALPATH)
get_filename_component(GEN_DIR ${CHIP_ROOT}/zzz_generated/ REALPATH)

include(${CHIP_ROOT}/config/atmosic/app/check-version.cmake)

# Set Kconfig root files that will be processed as a first Kconfig for used child images.
set(mcuboot_KCONFIG_ROOT ${CHIP_ROOT}/config/atmosic/chip-module/Kconfig.mcuboot.root)
set(multiprotocol_rpmsg_KCONFIG_ROOT ${CHIP_ROOT}/config/atmosic/chip-module/Kconfig.multiprotocol_rpmsg.root)
set(hci_rpmsg_KCONFIG_ROOT ${CHIP_ROOT}/config/atmosic/chip-module/Kconfig.hci_rpmsg.root)

if(NOT CONF_FILE STREQUAL "prj_no_dfu.conf")
    set(PM_STATIC_YML_FILE ${CMAKE_CURRENT_SOURCE_DIR}/configuration/${BOARD}/pm_static_dfu.yml)
endif()

list(APPEND ZEPHYR_EXTRA_MODULES ${CHIP_ROOT}/config/atmosic/chip-module)
find_package(Zephyr HINTS $ENV{ZEPHYR_BASE})

# -Wmaybe-uninitialized has too many false positives, including on std::optional
# and chip::Optional.  Make it nonfatal.
#
# See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=80635
target_compile_options(app PRIVATE -Werror -Wno-error=maybe-uninitialized)

project(chip-atmosic-lighting-example)

include(${CHIP_ROOT}/config/atmosic/app/enable-gnu-std.cmake)
include(${CHIP_ROOT}/config/atmosic/app/flashing.cmake)
include(${CHIP_ROOT}/src/app/chip_data_model.cmake)

target_include_directories(app PRIVATE
                           main/include
                           ${GEN_DIR}/app-common
                           ${GEN_DIR}/lighting-app
                           ${ATMOSIC_COMMON}/util/include
                           ${ATMOSIC_COMMON}/app/include)

target_sources(app PRIVATE
               main/AppTask.cpp
               main/ZclCallbacks.cpp
               ${ATMOSIC_COMMON}/common/mainCommon.cpp
               ${ATMOSIC_COMMON}/util/LEDWidget.cpp
               ${ATMOSIC_COMMON}/util/PWMDevice.cpp)

chip_configure_data_model(app
    INCLUDE_SERVER
    ZAP_FILE ${CHIP_ROOT}/examples/lighting-app/lighting-common/lighting-app.zap
)

if(CONFIG_CHIP_OTA_REQUESTOR OR CONFIG_MCUMGR_TRANSPORT_BT)
    target_sources(app PRIVATE ${ATMOSIC_COMMON}/util/OTAUtil.cpp)
endif()

if(CONFIG_MCUMGR_TRANSPORT_BT)
    target_sources(app PRIVATE ${ATMOSIC_COMMON}/util/DFUOverSMP.cpp)
endif()
