#pragma once

#include <BleKeyboard.h>

// Matrix dimensions
#define ROWS 4
#define COLS 4

// Row pins (active-low outputs during scan)
const uint8_t ROW_PINS[ROWS] = {32, 33, 25, 26};

// Column pins (inputs with internal pull-up)
const uint8_t COL_PINS[COLS] = {27, 14, 12, 13};

// OLED (SPI: 4-wire, write-only)
#define OLED_CLK  22   // display "SCK" pin
#define OLED_MOSI 21   // display "SDA" pin
#define OLED_RES  19   // display "RES" pin
#define OLED_DC   18   // display "DC" pin
#define OLED_CS    5   // display "CS" pin

// Rotary encoder (hardware debounce, no internal pull-up needed)
#define ENC_A 34
#define ENC_B 35

// Debounce time in milliseconds
#define DEBOUNCE_MS 10

// Scan interval in microseconds
#define SCAN_INTERVAL_US 1000

// Key map: keycodes sent over BLE HID for each matrix position.
// Row 0, Col 3 is not a physical key — mapped to 0 (no-op).
//
// Default layout (edit to match your caps):
//
//   [1] [2] [3] [x]
//   [4] [5] [6] [7]
//   [8] [9] [0] [+]
//   [.] [Enter] [Bksp] [Esc]
//
const uint8_t KEYMAP[ROWS][COLS] = {
    {'1',  '2',     '3',    0},        // Row 0  (Col 3 = no key)
    {'4',  '5',     '6',    '7'},      // Row 1
    {'8',  '9',     '0',    '+'},      // Row 2
    {'.',  KEY_RETURN, KEY_BACKSPACE, KEY_ESC}  // Row 3
};
