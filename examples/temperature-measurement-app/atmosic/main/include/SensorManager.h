/*
 *
 *    Copyright (c) 2023-2024 Project CHIP Authors
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

#include <stdbool.h>
#include <stdint.h>

#include <app-common/zap-generated/attributes/Accessors.h>
#include <lib/core/CHIPError.h>

class SensorManager
{
public:
    CHIP_ERROR Init();

    bool SampleTemp();
    int16_t GetMeasuredTemp();
    int16_t GetMinMeasuredTemp();
    int16_t GetMaxMeasuredTemp();

    int16_t GetMeasuredHumidity();

private:
    friend SensorManager & SensorMgr();

    int16_t mMeasuredTempCelsius;
    int16_t mMinMeasuredTempCelsius = -40;
    int16_t mMaxMeasuredTempCelsius = 120;
    int16_t mMeasuredHumidity;

    static SensorManager sSensorManager;
};

inline SensorManager & SensorMgr()
{
    return SensorManager::sSensorManager;
}
