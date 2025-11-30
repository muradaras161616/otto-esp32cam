# 🔌 Bağlantı Şeması / Wiring Diagram

Bu dokümanda ESP32-CAM OTTO robot için tüm pin bağlantıları ve şemalar yer almaktadır.

---

## 📋 Pin Tablosu / Pin Table

### ESP32-CAM Pin Bağlantıları

| ESP32-CAM GPIO | Bileşen | Fonksiyon | Renk Önerisi |
|----------------|---------|-----------|--------------|
| GPIO 12 | Servo YL | Sol Bacak (Left Leg) | 🟡 Sarı |
| GPIO 13 | Servo YR | Sağ Bacak (Right Leg) | 🟠 Turuncu |
| GPIO 14 | Servo RL | Sol Ayak (Left Foot) | 🟢 Yeşil |
| GPIO 15 | Servo RR | Sağ Ayak (Right Foot) | 🔵 Mavi |
| GPIO 2 | Buzzer | Passive Buzzer | ⚫ Siyah |
| GPIO 4 | Button | Cherry MX Switch | ⚪ Beyaz |
| GPIO 3 (U0RXD) | OLED SDA | I2C Data | 🟣 Mor |
| GPIO 1 (U0TXD) | OLED SCL | I2C Clock | 🟤 Kahverengi |

---

## 🔋 Güç Bağlantıları / Power Connections

### ESP32-CAM Güç

| Pin | Bağlantı | Açıklama |
|-----|----------|----------|
| 5V | Li-Po + (5V Regulator çıkışı) | Ana güç |
| GND | Li-Po - / Ortak GND | Toprak |

### Servo Güç (Ayrı güç kaynağı önerilir)

| Servo Pin | Bağlantı | Açıklama |
|-----------|----------|----------|
| VCC (Kırmızı) | 5V-6V güç kaynağı | Servo besleme |
| GND (Kahve) | Ortak GND | Toprak |
| Signal (Turuncu) | ESP32 GPIO | Kontrol sinyali |

> ⚠️ **Önemli:** Servo motorlar için ayrı güç kaynağı kullanmanız şiddetle tavsiye edilir. ESP32-CAM tek başına 4 servo motoru besleyemez.

---

## 📊 Detaylı Bağlantı Şeması

```
                    ┌─────────────────────────────────────┐
                    │           ESP32-CAM                 │
                    │         (AI-Thinker)                │
                    │                                     │
                    │  ┌──────────┐     ┌──────────┐     │
                    │  │  CAMERA  │     │  ANTENNA │     │
                    │  └──────────┘     └──────────┘     │
                    │                                     │
    Servo YL ───────│── GPIO 12                          │
    Servo YR ───────│── GPIO 13                          │
    Servo RL ───────│── GPIO 14                          │
    Servo RR ───────│── GPIO 15                          │
                    │                                     │
    Buzzer ─────────│── GPIO 2                           │
    Button ─────────│── GPIO 4 ──┬── 10K Pull-up         │
                    │            │                       │
    OLED SDA ───────│── GPIO 3 (RX)                      │
    OLED SCL ───────│── GPIO 1 (TX)                      │
                    │                                     │
    5V ─────────────│── 5V                               │
    GND ────────────│── GND                              │
                    │                                     │
                    └─────────────────────────────────────┘
```

---

## 🦿 Servo Bağlantıları / Servo Connections

### SG90 Servo Motor Kablo Renkleri

| Kablo Rengi | Fonksiyon |
|-------------|-----------|
| Kahverengi | GND |
| Kırmızı | VCC (5-6V) |
| Turuncu/Sarı | Sinyal |

### Servo Pozisyonları

```
        ┌─────────────────────┐
        │    OTTO ÖN YÜZ      │
        │                     │
   ┌────┴────┐           ┌────┴────┐
   │ YL (12) │           │ YR (13) │  ← Bacak Servoları
   │ Sol Bacak│          │Sağ Bacak│    (Leg Servos)
   └────┬────┘           └────┬────┘
   ┌────┴────┐           ┌────┴────┐
   │ RL (14) │           │ RR (15) │  ← Ayak Servoları
   │ Sol Ayak│           │Sağ Ayak │    (Foot Servos)
   └─────────┘           └─────────┘
```

---

## 🖥️ OLED Bağlantısı / OLED Connection

### 0.96" SSD1306 OLED

| OLED Pin | ESP32-CAM Pin | Açıklama |
|----------|---------------|----------|
| VCC | 3.3V | Güç (3.3V kullanın!) |
| GND | GND | Toprak |
| SDA | GPIO 3 (RX) | I2C Data |
| SCL | GPIO 1 (TX) | I2C Clock |

> ⚠️ **Not:** GPIO 1 ve 3 normalde Serial için kullanılır. OLED kullandığınızda Serial debug devre dışı kalır.

---

## 🔔 Buzzer Bağlantısı / Buzzer Connection

### Passive Buzzer

| Buzzer Pin | Bağlantı |
|------------|----------|
| + | GPIO 2 |
| - | GND |

> 💡 **İpucu:** Active buzzer da kullanabilirsiniz, ancak passive buzzer farklı tonlar çalabilir.

---

## 🔘 Buton Bağlantısı / Button Connection

### Cherry MX Switch

```
        Cherry MX Switch
        ┌─────────────┐
        │             │
        │    ┌───┐    │
        │    │ ▼ │    │
        │    └───┘    │
        │             │
        └──┬─────┬────┘
           │     │
           │     └─────── GND
           │
           ├──── GPIO 4
           │
           └──── 10K ohm ──── 3.3V (Pull-up)
```

> 💡 **Not:** ESP32 dahili pull-up direnci kullanılabilir (`INPUT_PULLUP`), ancak harici 10K direnç daha stabil çalışır.

---

## 🔌 Güç Şeması / Power Schematic

### Önerilen Güç Yapılandırması

```
    Li-Po Batarya (7.4V 2S)
            │
            ├──────────────────┬──────────────────┐
            │                  │                  │
            ▼                  ▼                  │
    ┌───────────────┐  ┌───────────────┐         │
    │ 5V Regulator  │  │ 5V Regulator  │         │
    │ (ESP32-CAM)   │  │ (Servolar)    │         │
    │   AMS1117     │  │   7805/LM2596 │         │
    └───────┬───────┘  └───────┬───────┘         │
            │                  │                  │
            ▼                  ▼                  │
       ESP32-CAM         Servo x4                │
       OLED                                       │
       Buzzer                                     │
       Button                                     │
            │                  │                  │
            └──────────────────┴──────────────────┘
                         GND (Ortak)
```

---

## 📏 Kablo Uzunlukları / Cable Lengths

| Bağlantı | Önerilen Uzunluk |
|----------|------------------|
| Bacak Servoları → ESP32 | 8-10 cm |
| Ayak Servoları → ESP32 | 10-12 cm |
| OLED → ESP32 | 5-7 cm |
| Buzzer → ESP32 | 4-5 cm |
| Buton → ESP32 | 3-4 cm |
| Pil → Regulatörler | 5-6 cm |

---

## ⚡ Elektriksel Özellikler / Electrical Specs

| Parametre | Değer |
|-----------|-------|
| ESP32-CAM çalışma gerilimi | 5V |
| OLED çalışma gerilimi | 3.3V |
| Servo çalışma gerilimi | 4.8-6V |
| Buzzer çalışma gerilimi | 3-5V |
| Toplam akım (pik) | ~1.5A |
| Toplam akım (ortalama) | ~500mA |

---

## 🛡️ Koruma Önerileri / Protection Tips

1. **Servo güç hattına 100-1000µF kapasitör ekleyin** - Servo kaynaklı gürültüyü azaltır
2. **ESP32 güç hattına 100µF kapasitör ekleyin** - Güç stabilizasyonu
3. **Servo sinyal hatlarına 100 ohm direnç ekleyin** - EMI koruması
4. **Pil düşük gerilim koruması kullanın** - Li-Po güvenliği

---

## 🔧 Sorun Giderme / Troubleshooting

| Sorun | Olası Sebep | Çözüm |
|-------|-------------|-------|
| Servo titriyor | Yetersiz güç | Ayrı güç kaynağı kullanın |
| OLED görüntü yok | Yanlış I2C adresi | 0x3C veya 0x3D deneyin |
| ESP32 sıfırlanıyor | Güç dalgalanması | Kapasitör ekleyin |
| Kamera çalışmıyor | Pin çakışması | Kamera pinlerini kontrol edin |

---

## 📸 Görsel Şema / Visual Diagram

Detaylı görsel şema için `images/wiring_diagram.png` dosyasına bakın.

---

*Bu dokümantasyon ESP32-CAM OTTO robot projesi için hazırlanmıştır.*
