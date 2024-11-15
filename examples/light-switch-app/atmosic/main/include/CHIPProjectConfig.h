/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Example project configuration file for CHIP.
 *
 *          This is a place to put application or project-specific overrides
 *          to the default configuration values for general CHIP features.
 *
 */

#pragma once

#define CHIP_CONFIG_CONTROLLER_MAX_ACTIVE_DEVICES 2

#define CHIP_DEVICE_CONFIG_USE_TEST_SETUP_PIN_CODE CONFIG_CHIP_DEVICE_SPAKE2_PASSCODE
#define CHIP_DEVICE_CONFIG_USE_TEST_SETUP_DISCRIMINATOR CONFIG_CHIP_DEVICE_DISCRIMINATOR

#define CHIP_DEVICE_CONFIG_TEST_SERIAL_NUMBER "TEST_SN_LAB100"
