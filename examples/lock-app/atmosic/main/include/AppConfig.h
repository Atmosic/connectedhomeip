/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
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

#pragma once

#include "BoardUtil.h"

// ---- Lock Example App Config ----

#define FUNCTION_BUTTON 0

#if NUMBER_OF_BUTTONS == 2
#define BLE_ADVERTISEMENT_START_AND_LOCK_BUTTON 1
#else
#define LOCK_BUTTON 1
#define BLE_ADVERTISEMENT_START_BUTTON 3
#endif

#define SYSTEM_STATE_LED 0
#define LOCK_STATE_LED 1
#if NUMBER_OF_LEDS == 4
#define FACTORY_RESET_SIGNAL_LED 2
#define FACTORY_RESET_SIGNAL_LED1 3
#endif
