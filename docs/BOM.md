# 📋 Malzeme Listesi / Bill of Materials (BOM)

Bu dokümanda ESP32-CAM OTTO robot için gerekli tüm malzemeler ve tahmini fiyatlar yer almaktadır.

---

## 🔌 Elektronik Bileşenler / Electronic Components

### Ana Kart / Main Board

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Link |
|---------|-------|------|------------|-------------|------|
| ESP32-CAM | AI-Thinker | 1 | ~150₺ | ~$5 | [AliExpress](https://aliexpress.com) |
| USB-TTL Dönüştürücü | FT232RL / CH340G | 1 | ~30₺ | ~$2 | Programlama için |

### Servo Motorlar / Servo Motors

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| Servo Motor | SG90 (9g) | 4 | ~120₺ | ~$4 | Mikro servo |
| Alternatif | MG90S | 4 | ~200₺ | ~$8 | Metal dişli, daha dayanıklı |

### Ekran / Display

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| OLED Ekran | 0.96" SSD1306 I2C | 1 | ~40₺ | ~$2 | 128x64 piksel |
| Alternatif | 1.3" SH1106 | 1 | ~50₺ | ~$3 | Daha büyük |

### Ses / Sound

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| Buzzer | Passive Buzzer 5V | 1 | ~5₺ | ~$0.50 | Farklı tonlar |
| Alternatif | Active Buzzer | 1 | ~5₺ | ~$0.50 | Tek ton |

### Buton / Button

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| Mekanik Buton | Cherry MX (Herhangi) | 1 | ~30₺ | ~$1 | Blue, Red, Brown |
| Keycap | Cherry MX Keycap | 1 | ~10₺ | ~$0.50 | İsteğe bağlı |
| Alternatif | Tactile Button 6x6mm | 1 | ~2₺ | ~$0.10 | Daha ucuz |

---

## 🔋 Güç Sistemi / Power System

### Pil / Battery

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| Li-Po Pil | 7.4V 2S 1000mAh | 1 | ~150₺ | ~$8 | Ana güç |
| Alternatif | 18650 Li-ion (2x) | 2 | ~100₺ | ~$6 | Pil tutucu gerekli |
| Pil Tutucu | 18650 2S | 1 | ~20₺ | ~$1 | 18650 için |

### Güç Regülasyonu / Power Regulation

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| DC-DC Converter | LM2596 (Ayarlanabilir) | 2 | ~30₺ | ~$2 | 5V çıkış |
| Alternatif | 7805 Linear | 2 | ~10₺ | ~$0.50 | Daha fazla ısı |
| Açma/Kapama | Slide Switch | 1 | ~5₺ | ~$0.30 | Güç anahtarı |

### Koruma / Protection

| Bileşen | Model | Adet | Fiyat (TL) | Fiyat (USD) | Not |
|---------|-------|------|------------|-------------|-----|
| Kapasitör | 100µF 16V | 2 | ~5₺ | ~$0.30 | Güç stabilizasyonu |
| Kapasitör | 1000µF 16V | 1 | ~5₺ | ~$0.30 | Servo hattı |

---

## 🔩 Mekanik Parçalar / Mechanical Parts

### Vidalar ve Somunlar / Screws and Nuts

| Bileşen | Boyut | Adet | Fiyat (TL) | Not |
|---------|-------|------|------------|-----|
| M2 Vida | M2x8mm | 8 | ~5₺ | OLED, ESP32-CAM |
| M2 Somun | M2 | 8 | ~3₺ | |
| M3 Vida | M3x10mm | 8 | ~5₺ | Servo montajı |
| M3 Somun | M3 | 8 | ~3₺ | |
| Self-tap Vida | 2x8mm | 8 | ~3₺ | Plastik montaj |

### 3D Baskı / 3D Printing

| Malzeme | Miktar | Fiyat (TL) | Not |
|---------|--------|------------|-----|
| PLA Filament | ~100g | ~50₺ | 1kg = ~500₺ |
| PETG Filament | ~100g | ~60₺ | Alternatif |

---

## 🔌 Kablolama / Wiring

| Bileşen | Miktar | Fiyat (TL) | Not |
|---------|--------|------------|-----|
| Jumper Kablo (Dişi-Dişi) | 20 adet | ~15₺ | Bağlantılar |
| Jumper Kablo (Erkek-Dişi) | 10 adet | ~10₺ | |
| Isı Büzüşen Makaron | Set | ~15₺ | Kablo koruması |
| Lehim | 20g | ~20₺ | |

---

## 🛠️ Araçlar / Tools (Tek Seferlik)

| Araç | Fiyat (TL) | Not |
|------|------------|-----|
| Lehim Havyası | ~150₺ | 60W önerilir |
| Lehim Seti | ~50₺ | Flux, temizleyici |
| Küçük Tornavida Seti | ~30₺ | Philips + Düz |
| Pense/Keski | ~30₺ | Destek temizliği |
| Multimetre | ~100₺ | Ölçüm ve debug |
| Matkap (İsteğe bağlı) | ~200₺ | Delik genişletme |

---

## 💰 Toplam Maliyet Özeti / Total Cost Summary

### Minimum Bütçe (Temel Yapı)

| Kategori | Fiyat (TL) | Fiyat (USD) |
|----------|------------|-------------|
| Elektronik | ~350₺ | ~$15 |
| Güç Sistemi | ~200₺ | ~$10 |
| Mekanik | ~70₺ | ~$3 |
| **TOPLAM** | **~620₺** | **~$28** |

### Önerilen Bütçe (Kaliteli Parçalar)

| Kategori | Fiyat (TL) | Fiyat (USD) |
|----------|------------|-------------|
| Elektronik | ~450₺ | ~$20 |
| Güç Sistemi | ~250₺ | ~$12 |
| Mekanik | ~100₺ | ~$5 |
| Araçlar (varsa) | ~0₺ | ~$0 |
| **TOPLAM** | **~800₺** | **~$37** |

### Premium Bütçe (En İyi Parçalar)

| Kategori | Fiyat (TL) | Fiyat (USD) |
|----------|------------|-------------|
| Elektronik (MG90S) | ~550₺ | ~$25 |
| Güç Sistemi (Kaliteli Li-Po) | ~350₺ | ~$15 |
| Mekanik (PETG) | ~150₺ | ~$7 |
| **TOPLAM** | **~1050₺** | **~$47** |

---

## 🛒 Nereden Alınır? / Where to Buy?

### Türkiye

| Mağaza | Ürün Grubu | Link |
|--------|------------|------|
| Direnc.net | Elektronik, Servo | [direnc.net](https://www.direnc.net) |
| Robotistan | ESP32, Sensör | [robotistan.com](https://www.robotistan.com) |
| F1 Dekan | Filament | [f1dekan.com](https://www.f1dekan.com) |
| n11/Trendyol | Genel | Fiyat karşılaştırma |

### Uluslararası / International

| Mağaza | Ürün Grubu | Link |
|--------|------------|------|
| AliExpress | Her şey | [aliexpress.com](https://www.aliexpress.com) |
| Banggood | Elektronik | [banggood.com](https://www.banggood.com) |
| Amazon | Hızlı teslimat | [amazon.com](https://www.amazon.com) |

---

## 📝 Satın Alma İpuçları / Purchasing Tips

1. **Toplu alın:** Aynı mağazadan çoklu ürün alın, kargo tasarrufu yapın
2. **Yedek bulundurun:** Servo ve ESP32'den birer tane fazla alın
3. **Fiyat takibi:** Kampanya dönemlerini bekleyin (11.11, Black Friday)
4. **Kalite kontrolü:** Çok ucuz parçalardan kaçının
5. **Kargo süresi:** AliExpress 2-4 hafta sürebilir

---

## ✅ Alışveriş Kontrol Listesi / Shopping Checklist

```
□ ESP32-CAM (AI-Thinker)
□ USB-TTL Dönüştürücü
□ SG90 Servo Motor x4
□ 0.96" OLED SSD1306
□ Passive Buzzer
□ Cherry MX Switch
□ Li-Po Pil 7.4V
□ LM2596 DC-DC x2
□ Açma/Kapama Switch
□ Kapasitör (100µF x2, 1000µF x1)
□ M2 Vida/Somun Seti
□ M3 Vida/Somun Seti
□ Jumper Kablo Seti
□ PLA Filament (~100g)
```

---

## 🔄 Alternatif Bileşenler / Alternative Components

| Orijinal | Alternatif | Not |
|----------|------------|-----|
| ESP32-CAM | ESP32 + OV2640 | Ayrı kamera modülü |
| SG90 | SG92R, MG90S | Daha dayanıklı |
| Cherry MX | Gateron, Outemu | Uyumlu |
| SSD1306 | SH1106 | Farklı driver |
| Li-Po 7.4V | 4xAA NiMH | Daha güvenli |

---

*Bu BOM listesi ESP32-CAM OTTO robot projesi için hazırlanmıştır. Fiyatlar tahmini olup değişiklik gösterebilir.*
