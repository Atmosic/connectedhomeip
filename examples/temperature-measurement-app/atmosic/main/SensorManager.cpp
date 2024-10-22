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

#include "SensorManager.h"
#include "AppConfig.h"
#include "AppTask.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

//LOG_MODULE_DECLARE(app, CONFIG_CHIP_APP_LOG_LEVEL);
LOG_MODULE_DECLARE(SensorMgr, LOG_LEVEL_INF);

using namespace chip;
using namespace ::chip::DeviceLayer;

SensorManager SensorManager::sSensorManager;

CHIP_ERROR SensorManager::Init()
{
    // TODO: Initialize temp sensor
    return CHIP_NO_ERROR;
}

bool SensorManager::SampleTemp()
{
    const struct device *const dev = DEVICE_DT_GET_ONE(ams_ens210);

    if (device_is_ready(dev)) {
	sensor_sample_fetch(dev);

	struct sensor_value temperature, humidity;
	sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
	sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
	LOG_DBG("Temperature: %d.%06d°C; Humidity: %d.%06d%%",
		temperature.val1, temperature.val2,
		humidity.val1, humidity.val2);

	// Per spec Application Clusters 2.3.4.1. : MeasuredValue = 100 x temperature [°C]
	sSensorManager.mMeasuredTempCelsius = (temperature.val1 * 100) + (temperature.val2 / 10000);
	sSensorManager.mMeasuredHumidity = (humidity.val1 * 100) + (humidity.val2 / 10000);
	return true;
    }

    return false;
}

int16_t SensorManager::GetMeasuredTemp()
{
    return mMeasuredTempCelsius;
}

int16_t SensorManager::GetMinMeasuredTemp()
{
    return mMinMeasuredTempCelsius;
}

int16_t SensorManager::GetMaxMeasuredTemp()
{
    return mMaxMeasuredTempCelsius;
}

int16_t SensorManager::GetMeasuredHumidity()
{
    return mMeasuredHumidity;
}
