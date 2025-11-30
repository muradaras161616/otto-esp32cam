# 🤖 OTTO ESP32-CAM - Kameralı Dans Robotu

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32--CAM-blue.svg)](https://www.espressif.com/)

ESP32-CAM modülü ile geliştirilmiş, kamera özellikli OTTO dans robotu!

🌐 **[English Version](README_EN.md)**

---

## ✨ Özellikler

- 📸 **ESP32-CAM entegrasyonu** - Canlı kamera görüntüsü ve fotoğraf çekme
- 🎭 **Zengin göz animasyonları** - OLED ekranda 15+ farklı ifade (mutlu, üzgün, kızgın, aşık, vb.)
- 💃 **15+ dans hareketi** - Moonwalk, swing, crusaito, flapping, gangnam style ve daha fazlası
- 🎵 **Şarkılı danslar** - Baby Shark, If You're Happy, Anneni Seviyorsan
- 🎮 **Web kontrolü** - Tarayıcıdan tam kontrol arayüzü
- 🔘 **Cherry MX buton** - Fiziksel mod değiştirme butonu
- 🤖 **Otonom mod** - Kendi başına rastgele dans eder
- 🎉 **Parti modu** - Müzikli rastgele danslar
- 🔊 **Ses efektleri** - R2D2, laser, police, game over ve daha fazlası
- 📡 **WiFi bağlantısı** - Uzaktan kontrol ve izleme

---

## 📁 Proje Yapısı

```
otto-esp32cam/
├── firmware/
│   └── otto_esp32cam/
│       ├── otto_esp32cam.ino    # Ana firmware
│       └── config.h              # Yapılandırma ayarları
├── stl/
│   ├── otto_head_esp32cam.stl   # ESP32-CAM için modifiye kafa
│   ├── otto_body.stl            # Gövde
│   ├── otto_leg_left.stl        # Sol bacak
│   ├── otto_leg_right.stl       # Sağ bacak
│   ├── otto_foot_left.stl       # Sol ayak
│   └── otto_foot_right.stl      # Sağ ayak
├── docs/
│   ├── WIRING.md                # Bağlantı şeması
│   ├── PRINTING.md              # 3D baskı rehberi
│   ├── BOM.md                   # Malzeme listesi
│   └── ASSEMBLY.md              # Montaj rehberi
├── images/
│   └── ...                      # Proje görselleri
├── README.md                    # Bu dosya (Türkçe)
├── README_EN.md                 # İngilizce dokümantasyon
├── platformio.ini               # PlatformIO yapılandırması
└── LICENSE                      # MIT Lisansı
```

---

## 🛠️ Gerekli Malzemeler

Detaylı liste için [docs/BOM.md](docs/BOM.md) dosyasına bakın.

### Temel Bileşenler

| Bileşen | Adet | Açıklama |
|---------|------|----------|
| ESP32-CAM (AI-Thinker) | 1 | Ana kontrol kartı + kamera |
| SG90 Servo Motor | 4 | Bacak ve ayak hareketi |
| 0.96" OLED (SSD1306) | 1 | Göz animasyonları |
| Cherry MX Switch | 1 | Mod değiştirme butonu |
| Passive Buzzer | 1 | Ses efektleri |
| Li-Po Pil (7.4V) | 1 | Güç kaynağı |

---

## 📐 3D Baskı

Baskı ayarları için [docs/PRINTING.md](docs/PRINTING.md) dosyasına bakın.

### Hızlı Baskı Ayarları

- **Katman yüksekliği:** 0.2mm
- **Doluluk:** %20
- **Destek:** Gerekli (kafa için)
- **Filament:** PLA veya PETG

---

## 🔌 Bağlantı Şeması

Detaylı şema için [docs/WIRING.md](docs/WIRING.md) dosyasına bakın.

### Pin Bağlantıları

| ESP32-CAM Pin | Bileşen | Açıklama |
|---------------|---------|----------|
| GPIO 12 | Servo YL | Sol bacak |
| GPIO 13 | Servo YR | Sağ bacak |
| GPIO 14 | Servo RL | Sol ayak |
| GPIO 15 | Servo RR | Sağ ayak |
| GPIO 2 | Buzzer | Passive buzzer |
| GPIO 4 | Button | Cherry MX switch |
| GPIO 3 (RX) | OLED SDA | I2C Data |
| GPIO 1 (TX) | OLED SCL | I2C Clock |

---

## 🚀 Kurulum

### 1. Arduino IDE Kurulumu

1. [Arduino IDE](https://www.arduino.cc/en/software) indirin ve kurun
2. **File > Preferences > Additional Board URLs** kısmına ekleyin:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. **Tools > Board > Boards Manager** > "esp32" arayın ve kurun

### 2. Kütüphaneler

**Tools > Manage Libraries** ile yükleyin:
- `Adafruit SSD1306`
- `Adafruit GFX Library`

### 3. Yapılandırma

`firmware/otto_esp32cam/config.h` dosyasını düzenleyin:

```cpp
const char* WIFI_SSID = "WiFi_Adi";      // WiFi adınız
const char* WIFI_PASS = "WiFi_Sifresi";  // WiFi şifreniz
```

### 4. Yükleme

1. **Tools > Board** > "AI Thinker ESP32-CAM" seçin
2. **Tools > Port** > USB portunu seçin
3. **Upload** butonuna tıklayın

> ⚠️ **Not:** ESP32-CAM'e yükleme yaparken GPIO0'ı GND'ye bağlamanız gerekebilir.

### PlatformIO Alternatifi

PlatformIO kullanıyorsanız:

```bash
cd firmware/otto_esp32cam
pio run -t upload
```

---

## 📷 Kullanım

### Web Arayüzü

Robot WiFi'ye bağlandıktan sonra, IP adresini OLED ekranda görebilirsiniz.
Tarayıcınızda açın:

- `http://<IP_ADRESI>/` - Ana kontrol paneli
- `http://<IP_ADRESI>/camera` - Canlı kamera görüntüsü
- `http://<IP_ADRESI>/status` - Durum bilgisi (JSON)

### Cherry MX Buton

Kafadaki butona basarak modlar arasında geçiş yapın:

1. **IDLE** - Bekleme modu
2. **AUTO** - Otonom dans
3. **DANCE** - Sürekli dans
4. **PARTY** - Müzikli parti
5. **SLEEP** - Uyku modu
6. **MUSIC** - Şarkılı dans

---

## 🎵 Ses ve Dans

### Dans Hareketleri

- Walk (Yürüme)
- Moonwalk (Ay yürüyüşü)
- Swing (Sallanma)
- Crusaito (Çapraz)
- Flapping (Kanat çırpma)
- Jump (Zıplama)
- Shake (Titreme)
- Turn (Dönme)

### Şarkılı Danslar

- 🦈 Baby Shark
- 😊 If You're Happy
- ❤️ Anneni Seviyorsan (Anne Şarkısı)

### Ses Efektleri

- Happy / Sad sounds
- R2D2 beeps
- Laser sound
- Police siren
- Game over melody

---

## 🔧 Sorun Giderme

| Sorun | Çözüm |
|-------|-------|
| WiFi bağlanmıyor | SSID/şifre kontrolü, Access Point modunu deneyin |
| Kamera çalışmıyor | Pin bağlantılarını kontrol edin |
| Servo titriyor | Güç kaynağını kontrol edin, capacitor ekleyin |
| OLED görüntülenmiyor | I2C adresini kontrol edin (0x3C veya 0x3D) |
| Upload başarısız | GPIO0 GND bağlantısı, farklı USB kablosu deneyin |

---

## 📝 Lisans

Bu proje MIT Lisansı altında lisanslanmıştır - detaylar için [LICENSE](LICENSE) dosyasına bakın.

---

## 🙏 Teşekkürler

- [OttoDIY](https://www.ottodiy.com/) - Orijinal OTTO robot tasarımı
- [Espressif](https://www.espressif.com/) - ESP32 platformu
- ESP32-CAM topluluğu
- Tüm katkıda bulunanlar

---

## 🤝 Katkıda Bulunma

1. Fork yapın
2. Feature branch oluşturun (`git checkout -b feature/amazing-feature`)
3. Commit yapın (`git commit -m 'Add amazing feature'`)
4. Push yapın (`git push origin feature/amazing-feature`)
5. Pull Request açın

---

## 📞 İletişim

Sorularınız için issue açabilir veya pull request gönderebilirsiniz.

---

Made with ❤️ for robotics enthusiasts
