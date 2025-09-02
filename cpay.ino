//this is the ardunio code , compiled and uploaded in the money box machine 


#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <qrcode.h>

MCUFRIEND_kbv tft;

// Hardcoded password and keys
String password   = "mypassword";
String privateKey = "arduino-123";
String publicKey  = "PUBLIC_KEY_987654321";

// Example bitmap (replace with your own image)
// 16x16 simple pattern just for demo
const unsigned char myBitmap[] PROGMEM = {
  0xFF,0x81,0xBD,0xA5,0xA5,0xBD,0x81,0xFF,
  0xFF,0x81,0xBD,0xA5,0xA5,0xBD,0x81,0xFF
};

// Determine optimal QR version based on input length
int estimateQRVersion(int textLength) {
  if (textLength <= 20) return 1;
  if (textLength <= 47) return 2;
  if (textLength <= 77) return 3;
  if (textLength <= 114) return 4;
  if (textLength <= 154) return 5;
  if (textLength <= 195) return 6;
  if (textLength <= 224) return 7;
  if (textLength <= 279) return 8;
  if (textLength <= 335) return 9;
  // Add more versions if your display and library support it.
  return 9; // Fallback: max supported and reasonable
}

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(0xFFFF); // White background
  // Show default image (bitmap splash screen)
  tft.drawBitmap((tft.width() - 16) / 2, (tft.height() - 16) / 2, myBitmap, 16, 16, 0x0000);
  delay(2000); // keep splash for 2 seconds
  tft.fillScreen(0xFFFF);
  Serial.println("Ready for input...");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    Serial.print("Got: ");
    Serial.println(input);
    if (input.length() == 0) return;

    // Decide what to turn into QR
    String qrData;
    if (input.equals(password)) {
      Serial.println("Password correct → showing private key QR");
      qrData = privateKey;
    } else {
      qrData = input;
    }

    // Try smallest scale first; make QR as large as possible while still fitting the screen
    int qrVersion = estimateQRVersion(qrData.length());
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(qrVersion)];
    qrcode_initText(&qrcode, qrcodeData, qrVersion, 0, qrData.c_str());

    // Pick a starting scale (smaller than before)
    int scale = 8;
    int qrSize = qrcode.size * scale;

    // Try to automatically reduce scale if QR doesn't fit
    while ((qrSize > tft.width() || qrSize > tft.height()) && scale > 1) {
      scale--; // reduce scale until QR fits, or minimum=1
      qrSize = qrcode.size * scale;
    }

    if (qrSize > tft.width() || qrSize > tft.height()) {
      Serial.println("QR code too large for display! Try shorter text or larger display.");
      tft.fillScreen(0xFFFF); // White background
      tft.setTextColor(0x0000);
      tft.setCursor(10, tft.height()/2 - 16);
      tft.setTextSize(2);
      tft.println("QR too big");
      tft.setTextSize(1);
      tft.println("Shorten text.");
      delay(2000);
      return;
    }

    tft.fillScreen(0xFFFF);
    int xOffset = (tft.width() - qrSize) / 2;
    int yOffset = (tft.height() - qrSize) / 2;

    // Draw QR pixels
    for (uint8_t y = 0; y < qrcode.size; y++) {
      for (uint8_t x = 0; x < qrcode.size; x++) {
        if (qrcode_getModule(&qrcode, x, y)) {
          tft.fillRect(xOffset + x * scale, yOffset + y * scale, scale, scale, 0x0000); // Black
        } else {
          tft.fillRect(xOffset + x * scale, yOffset + y * scale, scale, scale, 0xFFFF); // White
        }
      }
    }
  }
}
