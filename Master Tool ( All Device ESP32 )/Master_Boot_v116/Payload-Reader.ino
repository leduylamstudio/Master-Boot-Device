void executeBadUSB() {
  tft.fillScreen(MATRIX_BLACK);
  tft.setTextColor(MATRIX_PURPLE);
  tft.println("OPENING: Update.txt...");

  File script = SD.open("/Update.txt"); // This must match the SD filename!
  
  if (script) {
    tft.println("RUNNING PAYLOAD...");
    while (script.available()) {
      String line = script.readStringUntil('\n');
      // ... (parsing logic we discussed earlier)
    }
    script.close();
  } else {
    tft.setTextColor(TFT_RED);
    tft.println("FILE NOT FOUND!");
    tft.println("CHECK SD FILENAME!");
  }
}