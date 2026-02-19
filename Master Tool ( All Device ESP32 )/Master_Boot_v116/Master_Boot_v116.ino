/*
 * MASTER BOOT DEVICE-v116: MATRIX EDITION
 * Optimized for 7GB SD & Matrix Green GUI
 */

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <WiFi.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <WireGuard-ESP32.h>

// --- Colors & Pins ---
#define MATRIX_GREEN  0x07E0
#define MATRIX_BLACK  0x0000
#define TFT_BL 21
#define XPT2046_CS 33

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(XPT2046_CS);
bool headlessMode = false;
int selectedApp = 0;
const char* apps[] = {"CONFIG", "WIFI SNIFF", "BAD USB", "VPN TUNNEL", "STORAGE"};

// --- 1. BATTERY LOGIC ---
int getBat() {
  uint16_t v = analogRead(34);
  float voltage = ((float)v / 4095.0) * 2.0 * 3.3 * 1.1;
  int p = map(voltage * 100, 320, 420, 0, 100);
  return constrain(p, 0, 100);
}

// --- 2. MATRIX RAIN EFFECT ---
void matrixRain(int duration) {
  unsigned long start = millis();
  int y[20]; 
  for (int i = 0; i < 20; i++) y[i] = random(-20, 0);
  while (millis() - start < duration) {
    for (int i = 0; i < 20; i++) {
      tft.setTextColor(MATRIX_GREEN, MATRIX_BLACK);
      tft.setCursor(i * 16, y[i] * 12);
      tft.print((char)random(33, 126));
      y[i]++;
      if (y[i] > 20) {
        tft.fillRect(i*16, 0, 16, 240, MATRIX_BLACK);
        y[i] = 0;
      }
    }
    delay(30);
  }
}

// --- 3. BOOT SEQUENCE ---
void bootSequence() {
  tft.fillScreen(MATRIX_BLACK);
  tft.setTextColor(MATRIX_GREEN);
  tft.setTextSize(1);
  const char* logs[] = {"INIT KERNEL...", "SD 7GB MOUNTED", "JSON LOADED", "VPN READY", "BLE READY"};
  for(int i=0; i<5; i++) {
    tft.setCursor(10, 20 + (i*15));
    tft.println(logs[i]);
    delay(400);
  }
  matrixRain(2000);
  tft.fillScreen(MATRIX_BLACK);
  tft.drawRoundRect(40, 70, 240, 80, 10, MATRIX_GREEN);
  tft.setTextSize(2);
  tft.drawCentreString("MASTER BOOT DEVICE", 160, 90, 1);
  tft.drawCentreString("v116.0", 160, 120, 1);
  delay(1500);
}

// --- 4. HEADER & GUI ---
void drawHeader() {
  tft.fillRect(0, 0, 320, 25, MATRIX_BLACK);
  tft.drawFastHLine(0, 25, 320, MATRIX_GREEN);
  tft.setTextColor(MATRIX_GREEN);
  tft.setTextSize(1);
  tft.setCursor(5, 8); tft.print("12:34:46");
  tft.setCursor(80, 8); tft.print(headlessMode ? "[LOCKED]" : "[ACTIVE]");
  tft.setCursor(270, 8); tft.printf("%d%%", getBat());
  tft.drawRect(300, 6, 15, 10, MATRIX_GREEN);
}

void drawMainGUI() {
  if(headlessMode) return;
  tft.fillScreen(MATRIX_BLACK);
  drawHeader();
  tft.drawRoundRect(5, 30, 310, 205, 8, MATRIX_GREEN);
  
  // Gear Icon
  int cx = 160, cy = 115;
  tft.drawCircle(cx, cy, 30, MATRIX_GREEN);
  for(int i=0; i<360; i+=45) {
    float r = i * 0.01745;
    tft.fillRect(cx + cos(r)*35 - 5, cy + sin(r)*35 - 5, 10, 10, MATRIX_GREEN);
  }
  
  tft.setTextSize(3);
  tft.setCursor(25, 105); tft.print("<");
  tft.setCursor(280, 105); tft.print(">");
  tft.setTextSize(2);
  tft.drawCentreString(apps[selectedApp], 160, 185, 1);
}

void toggleHeadless() {
  headlessMode = !headlessMode;
  digitalWrite(TFT_BL, headlessMode ? LOW : HIGH);
  if(!headlessMode) drawMainGUI();
}

// --- 5. CORE SETUP & LOOP ---
void setup() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  tft.init(); tft.setRotation(1);
  
  SPIClass* hspi = new SPIClass(HSPI);
  hspi->begin(25, 39, 32, 33);
  touch.begin(*hspi);
  
  SD.begin(5);
  bootSequence();
  drawMainGUI();
}

void loop() {
  if (touch.touched()) {
    TS_Point p = touch.getPoint();
    // Map touch coordinates (Adjust if arrows don't work)
    if (p.y < 800) { toggleHeadless(); delay(500); }
    else if (!headlessMode) {
      if (p.x < 1200) { selectedApp = (selectedApp > 0) ? selectedApp - 1 : 4; drawMainGUI(); }
      else if (p.x > 2800) { selectedApp = (selectedApp < 4) ? selectedApp + 1 : 0; drawMainGUI(); }
    }
    delay(200);
  }
}