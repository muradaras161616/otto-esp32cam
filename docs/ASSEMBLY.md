# 🔧 Montaj Rehberi / Assembly Guide

Bu dokümanda ESP32-CAM OTTO robot için adım adım montaj talimatları yer almaktadır.

---

## 📋 Başlamadan Önce / Before You Start

### Gerekli Malzemeler
- Tüm 3D baskı parçalar (kafa, gövde, bacaklar, ayaklar)
- Tüm elektronik bileşenler ([BOM.md](BOM.md) listesine bakın)
- Lehim istasyonu ve lehim
- Küçük tornavidalar (Philips #0, #1)
- Pense/keski
- Sıcak silikon tabancası (isteğe bağlı)
- Multimetre (test için)

### Güvenlik Uyarıları
⚠️ Li-Po piller dikkatli kullanılmalıdır
⚠️ Lehim yaparken havalandırma sağlayın
⚠️ ESP32'yi programlarken kısa devre yapmayın

---

## 📸 Montaj Adımları / Assembly Steps

### Adım 1: 3D Baskı Parçaları Hazırlama

#### 1.1 Destek Temizliği
1. Kafa parçasından tüm destek yapılarını çıkarın
2. Pense ile büyük parçaları çıkarın
3. Keski ile kalan parçaları temizleyin
4. Zımpara ile pürüzleri giderin

#### 1.2 Delik Kontrolü
1. M2 vidaların girip girmediğini test edin
2. M3 vidaları servo delikleriyle kontrol edin
3. Gerekirse 2mm ve 2.5mm matkap ile genişletin

#### 1.3 Parça Uyumu
1. Tüm parçaları birbirine deneme takın
2. Servo motorları yuvalarına yerleştirin
3. Sıkı veya gevşek yerleri not alın

---

### Adım 2: Elektronik Hazırlık

#### 2.1 ESP32-CAM Test
1. ESP32-CAM'i USB-TTL ile bilgisayara bağlayın
   ```
   ESP32-CAM    USB-TTL
   GND    -->   GND
   5V     -->   5V
   U0R    -->   TX
   U0T    -->   RX
   GPIO0  -->   GND (sadece yükleme sırasında)
   ```
2. Arduino IDE'de "AI Thinker ESP32-CAM" seçin
3. Boş bir test kodu yükleyin
4. Serial monitörde çıktıyı kontrol edin

#### 2.2 Servo Test
1. Her servoyu tek tek ESP32'ye bağlayın
2. Test kodu ile 0°, 90°, 180° pozisyonlarını deneyin
3. Çalışmayan servoları işaretleyin

```cpp
// Servo test kodu
#include <ESP32Servo.h>
Servo testServo;

void setup() {
  testServo.attach(12); // Test edilecek pin
}

void loop() {
  testServo.write(0);   delay(1000);
  testServo.write(90);  delay(1000);
  testServo.write(180); delay(1000);
}
```

#### 2.3 OLED Test
1. OLED'i I2C pinlerine bağlayın
2. I2C Scanner kodu ile adres kontrolü yapın
3. Test görüntüsü gösterin

---

### Adım 3: Ayak Montajı

#### 3.1 Sol Ayak (Left Foot)
1. SG90 servoyu sol ayak yuvasına yerleştirin
2. Servo dişlisi ayak deliğine gelmeli
3. M3x10mm vidalarla sabitleyin (2 adet)
4. Servo kablosunu yukarı doğru yönlendirin

#### 3.2 Sağ Ayak (Right Foot)
1. Aynı adımları sağ ayak için tekrarlayın
2. Servo yönünün simetrik olduğundan emin olun

```
  Sol Ayak            Sağ Ayak
  ┌───────┐          ┌───────┐
  │ SERVO │          │ SERVO │
  │  ◄──  │          │  ──►  │
  │       │          │       │
  └───────┘          └───────┘
```

---

### Adım 4: Bacak Montajı

#### 4.1 Sol Bacak (Left Leg)
1. Bacak servo yuvasına SG90 yerleştirin
2. Servoyu M3 vidalarla sabitleyin
3. Servo boynuzunu (arm) bacağın alt deliğine takın
4. Ayak servosunun boynuzunu bacak bağlantı noktasına takın

#### 4.2 Sağ Bacak (Right Leg)
1. Aynı adımları sağ bacak için uygulayın

```
    Bacak Servosu
    ┌─────────┐
    │  SERVO  │ ← Bacak hareketi
    └────┬────┘
         │
    ┌────┴────┐
    │  BACAK  │
    │         │
    └────┬────┘
         │
    Ayak Servosu bağlantısı
```

---

### Adım 5: Gövde Montajı

#### 5.1 Servo Yerleştirme
1. Dört servoyu gövde içine düzenli yerleştirin
2. Kabloları arka tarafa doğru yönlendirin
3. Kabloların hareket özgürlüğü olmalı

#### 5.2 Bacak Bağlantısı
1. Sol bacak - gövde sol tarafına
2. Sağ bacak - gövde sağ tarafına
3. Servo boynuzlarını ilgili noktalara takın
4. M2 vidalarla sabitleyin

#### 5.3 Ayak Bağlantısı
1. Sol ayak - sol bacağa
2. Sağ ayak - sağ bacağa
3. Bağlantı noktalarını kontrol edin

---

### Adım 6: Kafa Elektroniği

#### 6.1 ESP32-CAM Montajı
1. ESP32-CAM'i kafa içindeki yuvaya yerleştirin
2. Kamera lensinin ön delikle hizalı olduğundan emin olun
3. M2 vidalarla 4 köşeden sabitleyin
4. Anten kablosunu anten slotundan geçirin

#### 6.2 OLED Montajı
1. OLED ekranı göz penceresine yerleştirin
2. Ekranın tam ortada olduğundan emin olun
3. M2 vidalarla sabitleyin
4. I2C kablolarını kablo kanalından geçirin

#### 6.3 Cherry MX Buton
1. Cherry MX switch'i tepe deliğine yerleştirin
2. Switch kliplerinin yerine oturduğundan emin olun
3. Keycap'i (varsa) takın
4. Kablo bağlantılarını lehimleyin

#### 6.4 Buzzer Montajı
1. Buzzer'ı gövde içinde uygun bir yere yapıştırın
2. Kablo bağlantılarını yapın

---

### Adım 7: Kablo Bağlantıları

#### 7.1 Pin Bağlantı Şeması

```
ESP32-CAM Pin --> Bileşen
━━━━━━━━━━━━━━━━━━━━━━━━
GPIO 12  -->  Servo YL (Sol Bacak) - Turuncu kablo
GPIO 13  -->  Servo YR (Sağ Bacak) - Turuncu kablo
GPIO 14  -->  Servo RL (Sol Ayak)  - Turuncu kablo
GPIO 15  -->  Servo RR (Sağ Ayak)  - Turuncu kablo
GPIO 2   -->  Buzzer (+)
GPIO 4   -->  Button (bir uç)
GPIO 3   -->  OLED SDA
GPIO 1   -->  OLED SCL
5V       -->  OLED VCC, Servo VCC (regülatör üzerinden)
GND      -->  OLED GND, Servo GND, Buzzer (-), Button (diğer uç)
```

#### 7.2 Güç Dağıtımı

```
Li-Po Pil (7.4V)
      │
      ├──► DC-DC Regülatör 1 ──► 5V ──► ESP32-CAM, OLED, Buzzer
      │
      └──► DC-DC Regülatör 2 ──► 5V ──► 4x Servo Motor
      
      GND ──────────────────────────► Ortak Toprak
```

#### 7.3 Lehimleme İpuçları
1. Önce kabloları ölçün ve kesin
2. Kablo uçlarını kalaylayın
3. Isı büzüşen makaron geçirin
4. Lehimleyin
5. Makaronu ısıtarak daraltın

---

### Adım 8: Kafa-Gövde Birleştirme

#### 8.1 Kablo Geçişi
1. Tüm kabloları kafadan gövdeye geçirin
2. Servo kabloları (4 adet)
3. OLED I2C kablosu
4. Buzzer kablosu
5. Buton kablosu

#### 8.2 Bağlantı
1. Kafayı gövdenin üstüne yerleştirin
2. Bağlantı noktalarını hizalayın
3. Gerekirse vida veya klip kullanın
4. Kabloların sıkışmadığından emin olun

---

### Adım 9: Güç Sistemi

#### 9.1 DC-DC Regülatör Ayarı
1. Regülatörleri pil bağlı değilken ayarlayın
2. Multimetre ile çıkış voltajını 5V olarak ayarlayın
3. Her iki regülatörü de aynı şekilde ayarlayın

#### 9.2 Pil Montajı
1. Pili gövde içine veya arkasına yerleştirin
2. Açma/kapama switch'ini bağlayın
3. Pil kablolarını regülatörlere bağlayın

#### 9.3 Test
1. Switch'i açmadan önce tüm bağlantıları kontrol edin
2. Multimetre ile kısa devre kontrolü yapın
3. Switch'i açın ve LED'leri kontrol edin
4. ESP32'nin başladığını doğrulayın

---

### Adım 10: Final Test ve Kalibrasyon

#### 10.1 Servo Kalibrasyon
1. `config.h` dosyasını açın
2. TRIM değerlerini ayarlayın
3. Robot düz durmalı
4. Her servoyu tek tek kalibre edin

```cpp
// config.h içinde
#define TRIM_YL 0   // Sol bacak düzeltmesi
#define TRIM_YR 0   // Sağ bacak düzeltmesi
#define TRIM_RL 0   // Sol ayak düzeltmesi
#define TRIM_RR 0   // Sağ ayak düzeltmesi
```

#### 10.2 Fonksiyon Testi
1. WiFi bağlantısını kontrol edin
2. Web arayüzünü açın
3. Her dans hareketini test edin
4. Kamera görüntüsünü kontrol edin
5. Ses efektlerini test edin
6. Buton fonksiyonunu test edin

#### 10.3 Sorun Giderme

| Sorun | Kontrol |
|-------|---------|
| Robot başlamıyor | Pil voltajı, regülatör çıkışı |
| Servo çalışmıyor | Pin bağlantısı, güç |
| Kamera yok | Pin çakışması, lens |
| OLED boş | I2C adresi, kablo |
| WiFi bağlanmıyor | SSID/şifre |

---

## 🎉 Tebrikler! / Congratulations!

OTTO ESP32-CAM robotunuz hazır! 🤖

### İlk Çalıştırma
1. Switch'i açın
2. OLED'de IP adresini görün
3. Tarayıcıda IP adresini açın
4. Dans ettirin!

### Bakım İpuçları
- Pili tamamen boşaltmayın
- Düşmelerden koruyun
- Servo dişlilerini kontrol edin
- Vidalarda gevşeme kontrolü yapın

---

## 📸 Montaj Görselleri

Detaylı görseller için `images/` klasörüne bakın:
- `assembly_step1.png` - Ayak montajı
- `assembly_step2.png` - Bacak montajı
- `assembly_step3.png` - Gövde montajı
- `assembly_step4.png` - Kafa montajı
- `assembly_step5.png` - Kablo bağlantıları
- `assembly_final.png` - Tamamlanmış robot

---

*Bu montaj rehberi ESP32-CAM OTTO robot projesi için hazırlanmıştır.*
