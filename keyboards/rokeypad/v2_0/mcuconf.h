// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// for LCD backlight
#undef STM32_PWM_USE_TIM5
#define STM32_PWM_USE_TIM5 TRUE

// for RGB
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE