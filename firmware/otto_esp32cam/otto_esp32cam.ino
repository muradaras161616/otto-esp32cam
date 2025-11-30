/**
 * ═══════════════════════════════════════════════════════════════════════════
 * ESP32-CAM OTTO Robot - Main Firmware
 * Kameralı Dans Robotu Ana Firmware'i
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * Features / Özellikler:
 * - ESP32-CAM camera integration / Kamera entegrasyonu
 * - 4 servo motor control / 4 servo motor kontrolü
 * - OLED eye animations / OLED göz animasyonları
 * - Dance movements / Dans hareketleri
 * - Music and sound effects / Müzik ve ses efektleri
 * - Web control interface / Web kontrol arayüzü
 * - Cherry MX button support / Cherry MX buton desteği
 * 
 * Author: OTTO ESP32-CAM Project
 * License: MIT
 */

#include "config.h"
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "esp_camera.h"

// ═══════════════════ PIN DEFINITIONS / PIN TANIMLARI ═══════════════════
// AI-Thinker ESP32-CAM module pin mapping
#define PIN_YL 12    // Left leg / Sol bacak (Y-Left)
#define PIN_YR 13    // Right leg / Sağ bacak (Y-Right)  
#define PIN_RL 14    // Left foot / Sol ayak (R-Left)
#define PIN_RR 15    // Right foot / Sağ ayak (R-Right)
#define PIN_BUZZER 2 // Passive buzzer
#define PIN_BUTTON 4 // Cherry MX button

// PWM channels for servos and buzzer
// Servo ve buzzer için PWM kanalları
#define PWM_CHANNEL_YL 0     // Left leg PWM channel
#define PWM_CHANNEL_YR 1     // Right leg PWM channel
#define PWM_CHANNEL_RL 2     // Left foot PWM channel
#define PWM_CHANNEL_RR 3     // Right foot PWM channel
#define PWM_CHANNEL_BUZZER 4 // Buzzer PWM channel

// I2C pins for OLED (using UART pins - disable serial for OLED)
// OLED için I2C pinleri (UART pinleri kullanılıyor - OLED için serial kapatılır)
// NOTE: This disables Serial debugging. Use GPIO 21/22 for I2C if debugging needed.
// NOT: Bu Serial debug'ı devre dışı bırakır. Debug gerekirse GPIO 21/22 kullanın.
#define PIN_SDA 3    // OLED I2C Data (GPIO 3 - U0RXD)
#define PIN_SCL 1    // OLED I2C Clock (GPIO 1 - U0TXD)

// Camera model definition / Kamera modeli tanımı
#define CAMERA_MODEL_AI_THINKER

// Camera pins for AI-Thinker ESP32-CAM
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// ═══════════════════ NOTE FREQUENCIES / NOTA FREKANSLARI ═══════════════════
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093

// ═══════════════════ ENUMS / ENUMLAR ═══════════════════
enum Mode {
  MODE_IDLE,        // Idle mode / Bekleme modu
  MODE_AUTO,        // Autonomous mode / Otonom mod
  MODE_DANCE,       // Dance mode / Dans modu
  MODE_PARTY,       // Party mode / Parti modu
  MODE_SLEEP,       // Sleep mode / Uyku modu
  MODE_MUSIC_DANCE  // Music dance mode / Müzikli dans modu
};

// ═══════════════════ GLOBAL VARIABLES / GLOBAL DEĞİŞKENLER ═══════════════════
Mode currentMode = MODE_IDLE;
WebServer server(WEB_SERVER_PORT);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

// Servo positions / Servo pozisyonları
int servoPos[4] = {90, 90, 90, 90};  // YL, YR, RL, RR

// Timing variables / Zamanlama değişkenleri
unsigned long lastButtonPress = 0;
unsigned long lastAutoAction = 0;
unsigned long lastIdleTime = 0;

// ═══════════════════ EYE BITMAPS / GÖZ BİTMAPLERİ ═══════════════════
// 32x32 pixel eye bitmaps for OLED display
// OLED ekran için 32x32 piksel göz bitmapleri

// Happy eyes / Mutlu gözler
const unsigned char eye_happy[] PROGMEM = {
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x01, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xC0,
  0x07, 0xFF, 0xFF, 0xE0, 0x0F, 0xFF, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xF8,
  0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0xFE,
  0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFC,
  0x3F, 0xFF, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xE0,
  0x03, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x80, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Sad eyes / Üzgün gözler
const unsigned char eye_sad[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x01, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xC0,
  0x07, 0xFF, 0xFF, 0xE0, 0x0F, 0xFF, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xF8,
  0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFE,
  0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFC,
  0x1F, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xE0,
  0x03, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x80, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Love eyes (heart) / Aşık gözler (kalp)
const unsigned char eye_love[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x03, 0xC0, 0x0F, 0xF0, 0x0F, 0xF0,
  0x1F, 0xF8, 0x1F, 0xF8, 0x3F, 0xFC, 0x3F, 0xFC, 0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFE,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFC,
  0x1F, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xE0, 0x03, 0xFF, 0xFF, 0xC0,
  0x01, 0xFF, 0xFF, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x3F, 0xFC, 0x00,
  0x00, 0x1F, 0xF8, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x03, 0xC0, 0x00,
  0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Angry eyes / Kızgın gözler
const unsigned char eye_angry[] PROGMEM = {
  0x7F, 0x00, 0x00, 0xFE, 0x3F, 0x80, 0x01, 0xFC, 0x1F, 0xC0, 0x03, 0xF8, 0x0F, 0xE0, 0x07, 0xF0,
  0x07, 0xF0, 0x0F, 0xE0, 0x03, 0xF8, 0x1F, 0xC0, 0x01, 0xFC, 0x3F, 0x80, 0x00, 0xFE, 0x7F, 0x00,
  0x00, 0x7F, 0xFE, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x0F, 0xF0, 0x00,
  0x00, 0x07, 0xE0, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
};

// ═══════════════════ FUNCTION DECLARATIONS / FONKSİYON TANIMLARI ═══════════════════
void initCamera();
void initOLED();
void initServos();
void initWiFi();
void initWebServer();
void checkButton();
void handleRoot();
void handleCamera();
void handleControl();
void handleStatus();
void showEyes(const unsigned char* leftEye, const unsigned char* rightEye);
void showText(String line1, String line2, String line3);
void resetEyes();
void blinkEyes();
void beep(int frequency, int duration);
void moveServo(int servo, int position);
void home();

// Dance functions / Dans fonksiyonları
void danceWalk(int steps, int speed);
void danceMoonwalk(int steps, int speed);
void danceSwing(int steps, int speed);
void danceCrusaito(int steps, int speed);
void danceFlapping(int steps, int speed);
void danceJump(int steps, int speed);
void danceShake(int steps, int speed);
void danceTurn(int steps, int speed, int direction);

// Sound functions / Ses fonksiyonları
void sndHappy();
void sndSad();
void sndR2D2();
void sndLaser();
void sndPolice();
void sndGameOver();
void sndStartup();

// Music dances / Müzikli danslar
void playBabyShark();
void playIfYoureHappy();
void playAnneniSeviyorsan();

// ═══════════════════ SETUP ═══════════════════
void setup() {
  // Initialize serial (if not using OLED on UART pins)
  // Serial.begin(115200);
  
  // Initialize I2C on custom pins
  Wire.begin(PIN_SDA, PIN_SCL);
  
  // Initialize components
  initOLED();
  showText("OTTO", "ESP32-CAM", "Starting...");
  delay(1000);
  
  initServos();
  showText("Servos", "OK", "");
  delay(500);
  
  #if ENABLE_CAMERA
  initCamera();
  showText("Camera", "OK", "");
  delay(500);
  #endif
  
  initWiFi();
  delay(500);
  
  initWebServer();
  showText("Web Server", "OK", "");
  delay(500);
  
  // Initialize button
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  
  // Initialize buzzer
  pinMode(PIN_BUZZER, OUTPUT);
  
  // Startup sound
  sndStartup();
  
  // Show ready status
  showText("OTTO Ready!", WiFi.localIP().toString(), "");
  delay(2000);
  
  // Show happy eyes
  resetEyes();
  
  lastIdleTime = millis();
}

// ═══════════════════ MAIN LOOP ═══════════════════
void loop() {
  server.handleClient();
  checkButton();
  
  // Handle different modes
  switch(currentMode) {
    case MODE_IDLE:
      // Blink eyes occasionally
      if (millis() - lastIdleTime > 5000) {
        blinkEyes();
        lastIdleTime = millis();
      }
      break;
      
    case MODE_AUTO:
      // Perform random actions
      if (millis() - lastAutoAction > AUTO_DANCE_INTERVAL) {
        int action = random(0, 8);
        switch(action) {
          case 0: danceWalk(4, DEFAULT_SPEED); break;
          case 1: danceMoonwalk(4, DEFAULT_SPEED); break;
          case 2: danceSwing(4, DEFAULT_SPEED); break;
          case 3: danceCrusaito(4, DEFAULT_SPEED); break;
          case 4: danceFlapping(4, DEFAULT_SPEED); break;
          case 5: danceJump(2, DEFAULT_SPEED); break;
          case 6: danceShake(4, DEFAULT_SPEED); break;
          case 7: danceTurn(4, DEFAULT_SPEED, random(0, 2)); break;
        }
        home();
        lastAutoAction = millis();
      }
      break;
      
    case MODE_DANCE:
      // Continuous dance
      danceSwing(2, DEFAULT_SPEED);
      break;
      
    case MODE_PARTY:
      // Random dances with sounds
      {
        int dance = random(0, 3);
        switch(dance) {
          case 0: playBabyShark(); break;
          case 1: playIfYoureHappy(); break;
          case 2: playAnneniSeviyorsan(); break;
        }
        home();
        delay(2000);
      }
      break;
      
    case MODE_SLEEP:
      // Sleep mode - minimal activity
      showText("Zzz...", "Sleeping", "");
      delay(5000);
      break;
      
    case MODE_MUSIC_DANCE:
      // Music dance mode
      playBabyShark();
      currentMode = MODE_IDLE;
      resetEyes();
      break;
  }
  
  delay(10);
}

// ═══════════════════ CAMERA FUNCTIONS / KAMERA FONKSİYONLARI ═══════════════════
void initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  
  // Adjust settings based on PSRAM availability
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    showText("Camera", "FAILED!", "");
    delay(2000);
  }
}

void takePhoto() {
  camera_fb_t * fb = esp_camera_fb_get();
  if(!fb) {
    showText("Photo", "Error!", "");
    return;
  }
  
  // Show feedback
  showText("Photo!", "Cheese! :)", "");
  beep(NOTE_C5, 100);
  delay(500);
  
  esp_camera_fb_return(fb);
  resetEyes();
}

// ═══════════════════ OLED FUNCTIONS / OLED FONKSİYONLARI ═══════════════════
void initOLED() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    // OLED initialization failed
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void showEyes(const unsigned char* leftEye, const unsigned char* rightEye) {
  display.clearDisplay();
  display.drawBitmap(0, 16, leftEye, 32, 32, SSD1306_WHITE);
  display.drawBitmap(96, 16, rightEye, 32, 32, SSD1306_WHITE);
  display.display();
}

void showText(String line1, String line2, String line3) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0, 0);
  display.println(line1);
  display.setCursor(0, 24);
  display.println(line2);
  display.setCursor(0, 48);
  display.println(line3);
  
  display.display();
}

void resetEyes() {
  showEyes(eye_happy, eye_happy);
}

void blinkEyes() {
  display.clearDisplay();
  display.fillRect(0, 28, 32, 4, SSD1306_WHITE);
  display.fillRect(96, 28, 32, 4, SSD1306_WHITE);
  display.display();
  delay(100);
  resetEyes();
}

// ═══════════════════ SERVO FUNCTIONS / SERVO FONKSİYONLARI ═══════════════════
void initServos() {
  // Initialize PWM channels for servos (50Hz, 16-bit resolution)
  // PWM kanallarını servolar için başlat (50Hz, 16-bit çözünürlük)
  ledcSetup(PWM_CHANNEL_YL, 50, 16);
  ledcSetup(PWM_CHANNEL_YR, 50, 16);
  ledcSetup(PWM_CHANNEL_RL, 50, 16);
  ledcSetup(PWM_CHANNEL_RR, 50, 16);
  
  ledcAttachPin(PIN_YL, PWM_CHANNEL_YL);
  ledcAttachPin(PIN_YR, PWM_CHANNEL_YR);
  ledcAttachPin(PIN_RL, PWM_CHANNEL_RL);
  ledcAttachPin(PIN_RR, PWM_CHANNEL_RR);
  
  // Move to home position
  home();
}

void moveServo(int servo, int position) {
  // Clamp position to valid range
  position = constrain(position, 0, 180);
  
  // Apply trim values
  switch(servo) {
    case PWM_CHANNEL_YL: position += TRIM_YL; break;
    case PWM_CHANNEL_YR: position += TRIM_YR; break;
    case PWM_CHANNEL_RL: position += TRIM_RL; break;
    case PWM_CHANNEL_RR: position += TRIM_RR; break;
  }
  
  // Convert angle to PWM duty cycle
  // Servo typically: 500-2500us pulse width
  // 50Hz = 20ms period, 16-bit resolution = 65536
  // 500us = 1638, 2500us = 8192
  int duty = map(position, 0, 180, 1638, 8192);
  ledcWrite(servo, duty);
  
  servoPos[servo] = position;
}

void home() {
  moveServo(0, 90);
  moveServo(1, 90);
  moveServo(2, 90);
  moveServo(3, 90);
}

// ═══════════════════ WIFI FUNCTIONS / WIFI FONKSİYONLARI ═══════════════════
void initWiFi() {
  showText("Connecting", "WiFi...", WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  int timeout = 30; // 30 seconds timeout
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(1000);
    timeout--;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    showText("WiFi OK!", WiFi.localIP().toString(), "");
  } else {
    // Start AP mode if connection fails
    WiFi.softAP("OTTO-ESP32CAM", "12345678");
    showText("AP Mode", "OTTO-ESP32CAM", WiFi.softAPIP().toString());
  }
}

// ═══════════════════ WEB SERVER FUNCTIONS / WEB SUNUCU FONKSİYONLARI ═══════════════════
void initWebServer() {
  server.on("/", handleRoot);
  server.on("/camera", handleCamera);
  server.on("/control", handleControl);
  server.on("/status", handleStatus);
  server.begin();
}

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>OTTO ESP32-CAM Control</title>
  <style>
    body { font-family: Arial; text-align: center; background: #1a1a2e; color: white; margin: 0; padding: 20px; }
    .container { max-width: 800px; margin: 0 auto; }
    h1 { color: #00d4ff; }
    .btn { background: #0f3460; color: white; padding: 15px 30px; margin: 5px; border: none; 
           border-radius: 10px; cursor: pointer; font-size: 16px; transition: 0.3s; }
    .btn:hover { background: #00d4ff; }
    .btn:active { transform: scale(0.95); }
    .section { background: #16213e; padding: 20px; margin: 15px 0; border-radius: 15px; }
    .camera-view { width: 100%; max-width: 640px; height: auto; border-radius: 10px; }
    .grid { display: grid; grid-template-columns: repeat(3, 1fr); gap: 10px; }
    .grid-2 { display: grid; grid-template-columns: repeat(2, 1fr); gap: 10px; }
    .status { color: #00ff88; font-size: 14px; }
  </style>
</head>
<body>
  <div class="container">
    <h1>🤖 OTTO ESP32-CAM</h1>
    
    <div class="section">
      <h2>📸 Camera / Kamera</h2>
      <img class="camera-view" src="/camera" id="cameraImg" onclick="refreshCamera()">
      <br><button class="btn" onclick="refreshCamera()">🔄 Refresh / Yenile</button>
    </div>
    
    <div class="section">
      <h2>🎮 Mode / Mod</h2>
      <div class="grid-2">
        <button class="btn" onclick="sendCmd('mode_idle')">😐 IDLE</button>
        <button class="btn" onclick="sendCmd('mode_auto')">🤖 AUTO</button>
        <button class="btn" onclick="sendCmd('mode_dance')">💃 DANCE</button>
        <button class="btn" onclick="sendCmd('mode_party')">🎉 PARTY</button>
      </div>
    </div>
    
    <div class="section">
      <h2>💃 Dance / Dans</h2>
      <div class="grid">
        <button class="btn" onclick="sendCmd('walk')">🚶 Walk</button>
        <button class="btn" onclick="sendCmd('moonwalk')">🌙 Moonwalk</button>
        <button class="btn" onclick="sendCmd('swing')">💫 Swing</button>
        <button class="btn" onclick="sendCmd('crusaito')">🕺 Crusaito</button>
        <button class="btn" onclick="sendCmd('flapping')">🦋 Flapping</button>
        <button class="btn" onclick="sendCmd('jump')">⬆️ Jump</button>
        <button class="btn" onclick="sendCmd('shake')">🎵 Shake</button>
        <button class="btn" onclick="sendCmd('turn_left')">↩️ Turn Left</button>
        <button class="btn" onclick="sendCmd('turn_right')">↪️ Turn Right</button>
      </div>
    </div>
    
    <div class="section">
      <h2>🎵 Music Dance / Müzikli Dans</h2>
      <div class="grid">
        <button class="btn" onclick="sendCmd('baby_shark')">🦈 Baby Shark</button>
        <button class="btn" onclick="sendCmd('if_youre_happy')">😊 If You're Happy</button>
        <button class="btn" onclick="sendCmd('anneni_seviyorsan')">❤️ Anne Şarkısı</button>
      </div>
    </div>
    
    <div class="section">
      <h2>🔊 Sounds / Sesler</h2>
      <div class="grid">
        <button class="btn" onclick="sendCmd('snd_happy')">😊 Happy</button>
        <button class="btn" onclick="sendCmd('snd_sad')">😢 Sad</button>
        <button class="btn" onclick="sendCmd('snd_r2d2')">🤖 R2D2</button>
        <button class="btn" onclick="sendCmd('snd_laser')">⚡ Laser</button>
        <button class="btn" onclick="sendCmd('snd_police')">🚨 Police</button>
        <button class="btn" onclick="sendCmd('snd_gameover')">👾 Game Over</button>
      </div>
    </div>
    
    <div class="section">
      <h2>😊 Eyes / Gözler</h2>
      <div class="grid">
        <button class="btn" onclick="sendCmd('eye_happy')">😊 Happy</button>
        <button class="btn" onclick="sendCmd('eye_sad')">😢 Sad</button>
        <button class="btn" onclick="sendCmd('eye_angry')">😠 Angry</button>
        <button class="btn" onclick="sendCmd('eye_love')">😍 Love</button>
      </div>
    </div>
    
    <div class="status" id="status">Ready / Hazır</div>
  </div>
  
  <script>
    function sendCmd(cmd) {
      document.getElementById('status').textContent = 'Sending: ' + cmd;
      fetch('/control?cmd=' + cmd)
        .then(response => response.text())
        .then(data => {
          document.getElementById('status').textContent = 'OK: ' + cmd;
        })
        .catch(err => {
          document.getElementById('status').textContent = 'Error: ' + err;
        });
    }
    
    function refreshCamera() {
      document.getElementById('cameraImg').src = '/camera?' + Date.now();
    }
    
    // Auto refresh camera every 5 seconds
    // setInterval(refreshCamera, 5000);
  </script>
</body>
</html>
)rawliteral";
  
  server.send(200, "text/html", html);
}

void handleCamera() {
  #if ENABLE_CAMERA
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    server.send(500, "text/plain", "Camera error");
    return;
  }
  
  server.setContentLength(fb->len);
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  client.write(fb->buf, fb->len);
  esp_camera_fb_return(fb);
  #else
  server.send(200, "text/plain", "Camera disabled");
  #endif
}

void handleControl() {
  String cmd = server.arg("cmd");
  
  // Mode commands
  if (cmd == "mode_idle") currentMode = MODE_IDLE;
  else if (cmd == "mode_auto") currentMode = MODE_AUTO;
  else if (cmd == "mode_dance") currentMode = MODE_DANCE;
  else if (cmd == "mode_party") currentMode = MODE_PARTY;
  
  // Dance commands
  else if (cmd == "walk") { danceWalk(4, DEFAULT_SPEED); home(); }
  else if (cmd == "moonwalk") { danceMoonwalk(4, DEFAULT_SPEED); home(); }
  else if (cmd == "swing") { danceSwing(4, DEFAULT_SPEED); home(); }
  else if (cmd == "crusaito") { danceCrusaito(4, DEFAULT_SPEED); home(); }
  else if (cmd == "flapping") { danceFlapping(4, DEFAULT_SPEED); home(); }
  else if (cmd == "jump") { danceJump(2, DEFAULT_SPEED); home(); }
  else if (cmd == "shake") { danceShake(4, DEFAULT_SPEED); home(); }
  else if (cmd == "turn_left") { danceTurn(4, DEFAULT_SPEED, 0); home(); }
  else if (cmd == "turn_right") { danceTurn(4, DEFAULT_SPEED, 1); home(); }
  
  // Music dance commands
  else if (cmd == "baby_shark") { playBabyShark(); home(); }
  else if (cmd == "if_youre_happy") { playIfYoureHappy(); home(); }
  else if (cmd == "anneni_seviyorsan") { playAnneniSeviyorsan(); home(); }
  
  // Sound commands
  else if (cmd == "snd_happy") sndHappy();
  else if (cmd == "snd_sad") sndSad();
  else if (cmd == "snd_r2d2") sndR2D2();
  else if (cmd == "snd_laser") sndLaser();
  else if (cmd == "snd_police") sndPolice();
  else if (cmd == "snd_gameover") sndGameOver();
  
  // Eye commands
  else if (cmd == "eye_happy") showEyes(eye_happy, eye_happy);
  else if (cmd == "eye_sad") showEyes(eye_sad, eye_sad);
  else if (cmd == "eye_angry") showEyes(eye_angry, eye_angry);
  else if (cmd == "eye_love") showEyes(eye_love, eye_love);
  
  server.send(200, "text/plain", "OK: " + cmd);
}

void handleStatus() {
  String status = "{";
  status += "\"mode\":" + String(currentMode) + ",";
  status += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
  status += "\"rssi\":" + String(WiFi.RSSI());
  status += "}";
  
  server.send(200, "application/json", status);
}

// ═══════════════════ BUTTON FUNCTIONS / BUTON FONKSİYONLARI ═══════════════════
void checkButton() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    delay(BUTTON_DEBOUNCE); // debounce
    if (digitalRead(PIN_BUTTON) == LOW) {
      // Change mode
      currentMode = (Mode)((currentMode + 1) % 6);
      sndHappy();
      
      // Show mode on OLED
      switch(currentMode) {
        case MODE_IDLE: showText("Mode:", "IDLE", "Bekleme"); break;
        case MODE_AUTO: showText("Mode:", "AUTO", "Otonom"); break;
        case MODE_DANCE: showText("Mode:", "DANCE", "Dans"); break;
        case MODE_PARTY: showText("Mode:", "PARTY", "Parti"); break;
        case MODE_SLEEP: showText("Mode:", "SLEEP", "Uyku"); break;
        case MODE_MUSIC_DANCE: showText("Mode:", "MUSIC", "Muzikli Dans"); break;
      }
      delay(1000);
      resetEyes();
      
      // Wait for button release
      while(digitalRead(PIN_BUTTON) == LOW) delay(10);
    }
  }
}

// ═══════════════════ SOUND FUNCTIONS / SES FONKSİYONLARI ═══════════════════
void beep(int frequency, int duration) {
  #if BUZZER_ENABLED
  // ESP32 compatible tone using ledcWrite
  // ESP32 uyumlu ton üretimi ledcWrite ile
  ledcSetup(PWM_CHANNEL_BUZZER, frequency, 8);  // 8-bit resolution
  ledcAttachPin(PIN_BUZZER, PWM_CHANNEL_BUZZER);
  ledcWrite(PWM_CHANNEL_BUZZER, 128);  // 50% duty cycle for tone
  delay(duration);
  ledcWrite(PWM_CHANNEL_BUZZER, 0);    // Stop tone
  ledcDetachPin(PIN_BUZZER);
  #endif
}

void sndHappy() {
  beep(NOTE_C5, 100);
  beep(NOTE_E5, 100);
  beep(NOTE_G5, 100);
  beep(NOTE_C6, 200);
}

void sndSad() {
  beep(NOTE_C5, 200);
  beep(NOTE_B4, 200);
  beep(NOTE_A4, 200);
  beep(NOTE_G4, 400);
}

void sndR2D2() {
  for(int i = 0; i < 5; i++) {
    beep(random(1000, 3000), random(50, 150));
    delay(50);
  }
}

void sndLaser() {
  for(int i = 3000; i > 500; i -= 100) {
    beep(i, 10);
  }
}

void sndPolice() {
  for(int i = 0; i < 3; i++) {
    for(int j = 800; j < 1200; j += 50) {
      beep(j, 30);
    }
    for(int j = 1200; j > 800; j -= 50) {
      beep(j, 30);
    }
  }
}

void sndGameOver() {
  beep(NOTE_C5, 200);
  beep(NOTE_G4, 200);
  beep(NOTE_E4, 200);
  beep(NOTE_A4, 300);
  beep(NOTE_B4, 300);
  beep(NOTE_A4, 300);
  beep(NOTE_GS4, 150);
  beep(NOTE_AS4, 150);
  beep(NOTE_GS4, 300);
  delay(200);
  beep(NOTE_G4, 200);
  beep(NOTE_D4, 200);
  beep(NOTE_B3, 200);
}

void sndStartup() {
  beep(NOTE_C4, 100);
  beep(NOTE_E4, 100);
  beep(NOTE_G4, 100);
  beep(NOTE_C5, 200);
  delay(100);
  beep(NOTE_G4, 100);
  beep(NOTE_C5, 300);
}

// ═══════════════════ DANCE FUNCTIONS / DANS FONKSİYONLARI ═══════════════════
void danceWalk(int steps, int speed) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    // Lift left foot
    moveServo(2, 60);
    delay(speed/4);
    // Move left leg forward
    moveServo(0, 120);
    delay(speed/4);
    // Put left foot down
    moveServo(2, 90);
    delay(speed/4);
    
    // Lift right foot
    moveServo(3, 120);
    delay(speed/4);
    // Move right leg forward
    moveServo(1, 60);
    delay(speed/4);
    // Put right foot down
    moveServo(3, 90);
    delay(speed/4);
    
    // Return to center
    moveServo(0, 90);
    moveServo(1, 90);
    delay(speed/4);
  }
}

void danceMoonwalk(int steps, int speed) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    moveServo(2, 60);
    moveServo(3, 120);
    delay(speed/2);
    moveServo(0, 60);
    moveServo(1, 120);
    delay(speed/2);
    moveServo(2, 90);
    moveServo(3, 90);
    delay(speed/4);
    moveServo(0, 90);
    moveServo(1, 90);
    delay(speed/4);
  }
}

void danceSwing(int steps, int speed) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    moveServo(0, 70);
    moveServo(1, 110);
    delay(speed/2);
    moveServo(0, 110);
    moveServo(1, 70);
    delay(speed/2);
  }
  moveServo(0, 90);
  moveServo(1, 90);
}

void danceCrusaito(int steps, int speed) {
  showEyes(eye_love, eye_love);
  for(int i = 0; i < steps; i++) {
    moveServo(2, 60);
    moveServo(3, 60);
    delay(speed/2);
    moveServo(2, 120);
    moveServo(3, 120);
    delay(speed/2);
  }
  moveServo(2, 90);
  moveServo(3, 90);
}

void danceFlapping(int steps, int speed) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    moveServo(2, 60);
    moveServo(3, 120);
    delay(speed/4);
    moveServo(2, 120);
    moveServo(3, 60);
    delay(speed/4);
  }
  moveServo(2, 90);
  moveServo(3, 90);
}

void danceJump(int steps, int speed) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    // Crouch
    moveServo(2, 60);
    moveServo(3, 120);
    delay(speed/2);
    // Jump
    moveServo(2, 120);
    moveServo(3, 60);
    beep(NOTE_C5, 100);
    delay(speed/2);
    // Land
    moveServo(2, 90);
    moveServo(3, 90);
    delay(speed/2);
  }
}

void danceShake(int steps, int speed) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    moveServo(0, 70);
    moveServo(1, 70);
    moveServo(2, 110);
    moveServo(3, 110);
    delay(speed/4);
    moveServo(0, 110);
    moveServo(1, 110);
    moveServo(2, 70);
    moveServo(3, 70);
    delay(speed/4);
  }
  home();
}

void danceTurn(int steps, int speed, int direction) {
  showEyes(eye_happy, eye_happy);
  for(int i = 0; i < steps; i++) {
    if(direction == 0) { // Turn left
      moveServo(2, 60);
      delay(speed/4);
      moveServo(0, 60);
      delay(speed/4);
      moveServo(2, 90);
      moveServo(0, 90);
      delay(speed/4);
    } else { // Turn right
      moveServo(3, 120);
      delay(speed/4);
      moveServo(1, 120);
      delay(speed/4);
      moveServo(3, 90);
      moveServo(1, 90);
      delay(speed/4);
    }
  }
}

// ═══════════════════ MUSIC DANCES / MÜZİKLİ DANSLAR ═══════════════════
void playBabyShark() {
  showText("Baby Shark", "Doo doo doo", "doo doo doo!");
  showEyes(eye_love, eye_love);
  
  // Baby Shark melody simplified
  int melody[] = {NOTE_C4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
                  NOTE_C4, NOTE_D4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4};
  int durations[] = {300, 300, 300, 200, 200, 200, 200, 300,
                     300, 300, 300, 200, 200, 200, 600};
  
  for(int i = 0; i < 15; i++) {
    beep(melody[i], durations[i]);
    if(i % 2 == 0) {
      danceFlapping(1, 400);
    }
    delay(50);
  }
  resetEyes();
}

void playIfYoureHappy() {
  showText("If You're", "Happy!", "Clap hands!");
  showEyes(eye_happy, eye_happy);
  
  // If You're Happy melody simplified
  int melody[] = {NOTE_C4, NOTE_C4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4,
                  NOTE_G4, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_F4};
  int durations[] = {300, 300, 200, 200, 200, 200, 200, 300,
                     300, 300, 200, 200, 200, 200, 200, 600};
  
  for(int i = 0; i < 16; i++) {
    beep(melody[i], durations[i]);
    if(i % 4 == 0) {
      danceSwing(1, 300);
    }
    delay(50);
  }
  resetEyes();
}

void playAnneniSeviyorsan() {
  showText("Anneni", "Seviyorsan", "Alkis!");
  showEyes(eye_love, eye_love);
  
  // Turkish children's song simplified
  int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4,
                  NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4};
  int durations[] = {300, 300, 300, 300, 400, 400,
                     300, 300, 400, 300, 300, 300, 600};
  
  for(int i = 0; i < 13; i++) {
    beep(melody[i], durations[i]);
    if(i % 3 == 0) {
      danceJump(1, 400);
    }
    delay(50);
  }
  resetEyes();
}
