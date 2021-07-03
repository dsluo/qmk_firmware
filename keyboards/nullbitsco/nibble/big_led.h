/* Copyright 2020 Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"
#include "fast_hsv2rgb.h"

/* Optional big LED pins */
#define BIG_LED_R_PIN D7
#define BIG_LED_G_PIN C6
#define BIG_LED_B_PIN D0

void
  set_big_LED_rgb(uint8_t red, uint8_t green, uint8_t blue),
  cycle_rgb(void),
  set_big_LED_r(uint8_t level),
  set_big_LED_g(uint8_t level),
  set_big_LED_b(uint8_t level);
