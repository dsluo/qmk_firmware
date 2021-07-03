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
#include "quantum.h"
#include "big_led.h"

static uint16_t s_duty_pattern_r = 0;
static uint16_t s_duty_pattern_g = 0;
static uint16_t s_duty_pattern_b = 0;

static uint8_t red = 0;
static uint8_t green = 0;
static uint8_t blue = 0;

// static const uint16_t led_duty_table[] = {
//     0b0000000000000000,
//     0b1000000000000000,
//     0b1000000010000000,
//     0b1000001000010000,
//     0b1000100010001000,
//     0b1001001001001000,
//     0b1010101010101010,
//     0b1110111011101110,
//     0b1111111111111111,
// };
static const uint32_t led_duty_table[] = {
    0b00000000000000000000000000000000,
    0b10000000000000000000000000000000,
    0b10000000000000001000000000000000,
    0b10000000001000000000010000000000,
    0b10000000100000001000000010000000,
    0b10000010000010000001000001000000,
    0b10000100001000001000010000100000,
    0b10001000010001000010001000010000,
    0b10001000100010001000100010001000,
    0b10010001001000100100010010001000,
    0b10010010010010001001001001001000,
    0b10100100100100100100100100100100,
    0b10100100101001001010010010100100,
    0b10101001010010100101001010010100,
    0b10101010010101001010101001010100,
    0b10101010101010100101010101010100,
    0b10101010101010101010101010101010,
    0b11010101010101011010101010101010,
    0b11010101101010101101010110101010,
    0b11010110101101011010110101101010,
    0b11011010110110101101101011011010,
    0b11011011011011011011011011011010,
    0b11101101101101101110110110110110,
    0b11101110110111011011101101110110,
    0b11101110111011101110111011101110,
    0b11110111101110111101110111101110,
    0b11111011110111101111101111011110,
    0b11111101111101111110111110111110,
    0b11111110111111101111111011111110,
    0b11111111110111111111101111111110,
    0b11111111111111101111111111111110,
    0b11111111111111111111111111111110,
    0b11111111111111111111111111111111,
};
#define led_duty_table_size (sizeof(led_duty_table) / sizeof(led_duty_table[0]))

static uint8_t scale_led(uint8_t v) {
    return v * (led_duty_table_size - 1) / 256;
}

void cycle_rgb(void) {
    static uint16_t hue = HSV_HUE_MIN;
    
    uint8_t r, g, b;
    fast_hsv2rgb_8bit(hue, HSV_SAT_MAX, HSV_VAL_MAX, &r, &g, &b);
    set_big_LED_rgb(r, g, b);

    if (hue + 1 > HSV_HUE_MAX) {
        hue = HSV_HUE_MIN;
    } else {
        hue++;
    }
}

void set_big_LED_rgb(uint8_t red, uint8_t green, uint8_t blue) {
    set_big_LED_r(red);
    set_big_LED_g(green);
    set_big_LED_b(blue);
}

void set_big_LED_r(uint8_t level) {
    red = level;
    s_duty_pattern_r = led_duty_table[scale_led(level)];
}

void set_big_LED_g(uint8_t level) {
    green = level;
    s_duty_pattern_g = led_duty_table[scale_led(level)];
}

void set_big_LED_b(uint8_t level) {
    blue = level;
    s_duty_pattern_b = led_duty_table[scale_led(level)];
}

void led_task_r(void) {
    static uint8_t led_tick_r = 0;

    if (s_duty_pattern_r & ((uint16_t) 1 << led_tick_r)) {
        writePinHigh(BIG_LED_R_PIN);
    } else {
        writePinLow(BIG_LED_R_PIN);
    }

    led_tick_r = (led_tick_r + 1) % 16;
}

void led_task_b(void) {
    static uint8_t led_tick_b = 0;

    if (s_duty_pattern_b & ((uint16_t) 1 << led_tick_b)) {
        writePinHigh(BIG_LED_B_PIN);
    } else {
        writePinLow(BIG_LED_B_PIN);
    }

    led_tick_b = (led_tick_b + 1) % 16;
}

void led_task_g(void) {
    static uint8_t led_tick_g = 0;

    if (s_duty_pattern_g & ((uint16_t) 1 << led_tick_g)) {
        writePinHigh(BIG_LED_G_PIN);
    } else {
        writePinLow(BIG_LED_G_PIN);
    }

    led_tick_g = (led_tick_g + 1) % 16;
}

void led_task(void) {
    led_task_r();
    led_task_b();
    led_task_g();
}

void keyboard_pre_init_user(void) {
    setPinOutput(BIG_LED_R_PIN);
    setPinOutput(BIG_LED_G_PIN);
    setPinOutput(BIG_LED_B_PIN);
}

void housekeeping_task_user(void) {
    led_task();
}