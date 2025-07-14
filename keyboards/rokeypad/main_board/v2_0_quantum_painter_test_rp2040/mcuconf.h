// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE

#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE

#include_next <mcuconf.h>
