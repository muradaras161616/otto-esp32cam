#ifndef CONFIG_H
#define CONFIG_H

// ═══════════════════════════════════════════════════════════════════════════
// ESP32-CAM OTTO Robot Configuration File
// ═══════════════════════════════════════════════════════════════════════════

// ═══════════════════ WIFI SETTINGS / WIFI AYARLARI ═══════════════════
// ⚠️ IMPORTANT: Change these values before uploading!
// ⚠️ ÖNEMLİ: Yüklemeden önce bu değerleri değiştirin!
const char* WIFI_SSID = "your_wifi_ssid";      // Your WiFi name / WiFi adınız
const char* WIFI_PASS = "your_wifi_password";  // Your WiFi password / WiFi şifreniz

// ═══════════════════ CAMERA SETTINGS / KAMERA AYARLARI ═══════════════════
#define ENABLE_CAMERA true                     // Enable camera / Kamerayı etkinleştir
#define ENABLE_FACE_DETECTION false            // Future feature / Gelecek özellik
#define CAMERA_FRAME_SIZE FRAMESIZE_SVGA       // Options: UXGA, SVGA, VGA, CIF

// ═══════════════════ SERVO CALIBRATION / SERVO KALİBRASYONU ═══════════════════
// Adjustment values for 90° straight position (-30 to +30)
// 90° düz pozisyon için ayarlama değerleri (-30 ile +30 arası)
#define TRIM_YL 0   // Left leg trim / Sol bacak trim
#define TRIM_YR 0   // Right leg trim / Sağ bacak trim
#define TRIM_RL 0   // Left foot trim / Sol ayak trim
#define TRIM_RR 0   // Right foot trim / Sağ ayak trim

// ═══════════════════ MOVEMENT SETTINGS / HAREKET AYARLARI ═══════════════════
#define DEFAULT_SPEED 1000  // Default movement speed in ms / Varsayılan hareket hızı (ms)
#define MIN_SPEED 300       // Minimum speed / Minimum hız
#define MAX_SPEED 3000      // Maximum speed / Maksimum hız

// ═══════════════════ OLED SETTINGS / OLED AYARLARI ═══════════════════
#define OLED_WIDTH 128      // OLED width in pixels / OLED genişliği (piksel)
#define OLED_HEIGHT 64      // OLED height in pixels / OLED yüksekliği (piksel)
#define OLED_ADDRESS 0x3C   // I2C address / I2C adresi

// ═══════════════════ BUTTON SETTINGS / BUTON AYARLARI ═══════════════════
#define BUTTON_DEBOUNCE 50  // Debounce time in ms / Debounce süresi (ms)
#define BUTTON_LONG_PRESS 1000  // Long press time in ms / Uzun basma süresi (ms)

// ═══════════════════ AUTONOMOUS MODE / OTONOM MOD ═══════════════════
#define AUTO_DANCE_INTERVAL 10000   // Auto dance interval in ms / Otomatik dans aralığı
#define AUTO_IDLE_TIMEOUT 30000     // Idle timeout before auto mode / Otonom mod öncesi bekleme

// ═══════════════════ SOUND SETTINGS / SES AYARLARI ═══════════════════
#define BUZZER_ENABLED true        // Enable buzzer / Buzzer'ı etkinleştir
#define DEFAULT_VOLUME 255         // Default volume (0-255) / Varsayılan ses (0-255)

// ═══════════════════ WEB SERVER / WEB SUNUCU ═══════════════════
#define WEB_SERVER_PORT 80         // Web server port / Web sunucu portu
#define ENABLE_STREAMING true      // Enable camera streaming / Kamera akışını etkinleştir

#endif // CONFIG_H
