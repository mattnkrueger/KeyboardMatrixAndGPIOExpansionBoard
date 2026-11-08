#include <Arduino.h>
#include <U8g2lib.h>
#include "keymap.h"

// Software SPI — uses exact pin assignments, no remapping issues
U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R2, OLED_CLK, OLED_MOSI, OLED_CS, OLED_DC, OLED_RES);

bool keyState[ROWS][COLS] = {};
bool keyRaw[ROWS][COLS]   = {};
uint32_t debounceTime[ROWS][COLS] = {};
bool displayDirty = true;

// Encoder state
volatile int encoderPos = 0;
int lastEncoderPos = 0;
bool lastA = false;
bool showFullWhite = false;

void IRAM_ATTR encoderISR() {
    bool a = digitalRead(ENC_A);
    bool b = digitalRead(ENC_B);
    if (a != lastA) {
        encoderPos += (a != b) ? 1 : -1;
        lastA = a;
    }
}

void setupPins() {
    for (int r = 0; r < ROWS; r++) {
        pinMode(ROW_PINS[r], OUTPUT);
        digitalWrite(ROW_PINS[r], HIGH);
    }
    for (int c = 0; c < COLS; c++) {
        pinMode(COL_PINS[c], INPUT_PULLUP);
    }
    pinMode(ENC_A, INPUT);
    pinMode(ENC_B, INPUT);
    lastA = digitalRead(ENC_A);
    attachInterrupt(digitalPinToInterrupt(ENC_A), encoderISR, CHANGE);
}

void scanMatrix() {
    uint32_t now = millis();

    for (int r = 0; r < ROWS; r++) {
        digitalWrite(ROW_PINS[r], LOW);
        delayMicroseconds(20);

        for (int c = 0; c < COLS; c++) {
            bool pressed = (digitalRead(COL_PINS[c]) == LOW);

            if (pressed != keyRaw[r][c]) {
                keyRaw[r][c] = pressed;
                debounceTime[r][c] = now;
            }

            if ((now - debounceTime[r][c]) >= DEBOUNCE_MS) {
                if (pressed != keyState[r][c]) {
                    keyState[r][c] = pressed;
                    displayDirty = true;
                    Serial.printf("Key %s: R%d C%d\n",
                                  pressed ? "DOWN" : "UP", r, c);
                }
            }
        }

        digitalWrite(ROW_PINS[r], HIGH);
    }
}

void drawMatrixDisplay() {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_7x14B_tr);

    // Title
    u8g2.drawStr(16, 12, "MATRIX  TEST");
    u8g2.drawHLine(0, 14, 128);

    // 4x4 grid of key boxes
    // Each cell: 28x10 pixels, with 4px gap
    const int startX = 4;
    const int startY = 18;
    const int cellW = 28;
    const int cellH = 10;
    const int gapX = 4;
    const int gapY = 2;

    u8g2.setFont(u8g2_font_6x10_tr);

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            int x = startX + c * (cellW + gapX);
            int y = startY + r * (cellH + gapY);

            if (keyState[r][c]) {
                // Pressed: filled box with inverted "X"
                u8g2.drawBox(x, y, cellW, cellH);
                u8g2.setDrawColor(0);
                u8g2.drawStr(x + 10, y + 9, "X");
                u8g2.setDrawColor(1);
            } else if (r == 0 && c == 3) {
                // Rotary position: shows current mode
                u8g2.drawFrame(x, y, cellW, cellH);
                const char *label = "ROT";
                int tw = u8g2.getStrWidth(label);
                u8g2.drawStr(x + (cellW - tw) / 2, y + 9, label);
            } else {
                // Not pressed: outline with dot
                u8g2.drawFrame(x, y, cellW, cellH);
                u8g2.drawStr(x + 10, y + 9, ".");
            }
        }
    }

    u8g2.sendBuffer();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Matrix Test Mode");

    u8g2.begin();
    Serial.println("OLED OK");

    setupPins();

    // Diagnostic: read all column pins with all rows HIGH (no scan)
    Serial.println("Column pin states (expect all HIGH):");
    for (int c = 0; c < COLS; c++) {
        Serial.printf("  Col%d (GPIO%d): %d\n", c, COL_PINS[c], digitalRead(COL_PINS[c]));
    }
    Serial.println("Row pin states:");
    for (int r = 0; r < ROWS; r++) {
        Serial.printf("  Row%d (GPIO%d): %d\n", r, ROW_PINS[r], digitalRead(ROW_PINS[r]));
    }
    Serial.println("Ready. Press keys.");
}

void loop() {
    scanMatrix();

    int pos = encoderPos;
    if (pos != lastEncoderPos) {
        lastEncoderPos = pos;
        showFullWhite = !showFullWhite;
        displayDirty = true;
        Serial.printf("Display: %s\n", showFullWhite ? "FULL WHITE" : "MATRIX");
    }

    if (displayDirty) {
        if (showFullWhite) {
            u8g2.clearBuffer();
            u8g2.drawBox(0, 0, 128, 64);
            u8g2.sendBuffer();
        } else {
            drawMatrixDisplay();
        }
        displayDirty = false;
    }

    delayMicroseconds(SCAN_INTERVAL_US);
}
