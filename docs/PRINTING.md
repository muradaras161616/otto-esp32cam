# 📐 3D Baskı Rehberi / 3D Printing Guide

Bu dokümanda OTTO ESP32-CAM robot için 3D baskı ayarları ve önerileri yer almaktadır.

---

## 🖨️ Yazıcı Ayarları / Printer Settings

### Genel Ayarlar / General Settings

| Parametre | Değer | Açıklama |
|-----------|-------|----------|
| Katman Yüksekliği | 0.2mm | Standart kalite |
| İlk Katman Yüksekliği | 0.3mm | Tablaya yapışma |
| Duvar Kalınlığı | 1.2mm (3 duvar) | Dayanıklılık |
| Üst/Alt Katman | 4 katman | Su geçirmezlik |
| Doluluk (Infill) | %20 | Ağırlık/dayanıklılık dengesi |
| Doluluk Deseni | Gyroid veya Grid | Yapısal dayanıklılık |

### Bambu Lab A1 Özel Ayarları

| Parametre | Değer |
|-----------|-------|
| Nozzle Sıcaklığı | 210°C (PLA) / 240°C (PETG) |
| Tabla Sıcaklığı | 60°C (PLA) / 80°C (PETG) |
| Baskı Hızı | 100mm/s |
| İlk Katman Hızı | 50mm/s |
| Retraction | 0.8mm @ 30mm/s |
| Z-Hop | 0.4mm |

---

## 📦 Parça Bazında Baskı Ayarları / Per-Part Settings

### 🤖 Otto Head (ESP32-CAM Modifiye) 

| Ayar | Değer | Not |
|------|-------|-----|
| Katman Yüksekliği | 0.2mm | |
| Doluluk | %20 | |
| Destek | ✅ Gerekli | Kamera ve switch delikleri için |
| Destek Tipi | Tree Supports | Kolay temizleme |
| Destek Açısı | 45° | |
| Baskı Yönü | Arka kısım tablada | Yüz kalitesi için |
| Baskı Süresi | ~3-4 saat | |

### 🦴 Otto Body

| Ayar | Değer | Not |
|------|-------|-----|
| Katman Yüksekliği | 0.2mm | |
| Doluluk | %20 | |
| Destek | ❌ Gerekli değil | |
| Baskı Yönü | Düz taban | |
| Baskı Süresi | ~2-3 saat | |

### 🦵 Otto Legs (Sol & Sağ)

| Ayar | Değer | Not |
|------|-------|-----|
| Katman Yüksekliği | 0.16mm | Daha pürüzsüz vida delikleri |
| Doluluk | %25 | Ekstra dayanıklılık |
| Destek | ❌ Gerekli değil | |
| Baskı Yönü | Servo yuvası yukarı | |
| Baskı Süresi | ~1 saat (her biri) | |

### 👟 Otto Feet (Sol & Sağ)

| Ayar | Değer | Not |
|------|-------|-----|
| Katman Yüksekliği | 0.2mm | |
| Doluluk | %30 | Zemin teması için sağlam |
| Destek | ❌ Gerekli değil | |
| Baskı Yönü | Taban aşağı | |
| Baskı Süresi | ~45 dakika (her biri) | |

---

## 🎨 Filament Önerileri / Filament Recommendations

### PLA (Önerilen Başlangıç)

| Marka | Renk | Not |
|-------|------|-----|
| Bambu Lab Basic PLA | Siyah | Kafa için |
| Bambu Lab Basic PLA | Beyaz | Gözler için şeffaf alternatif |
| Herhangi | Renkli | Gövde ve bacaklar |

**PLA Avantajları:**
- ✅ Kolay baskı
- ✅ İyi yüzey kalitesi
- ✅ Düşük warping
- ❌ Düşük ısı direnci

### PETG (İleri Seviye)

| Marka | Not |
|-------|-----|
| Bambu Lab PETG-HF | Hızlı baskı |
| eSun PETG | Ekonomik |

**PETG Avantajları:**
- ✅ Daha yüksek ısı direnci
- ✅ Daha dayanıklı
- ✅ Esneklik
- ❌ Stringing sorunları

---

## 📏 STL Dosyaları / STL Files

### Mevcut Dosyalar

| Dosya | Boyut | Açıklama |
|-------|-------|----------|
| `otto_head_esp32cam.stl` | ~50mm x 60mm x 50mm | ESP32-CAM uyumlu kafa |
| `otto_body.stl` | ~50mm x 50mm x 40mm | Ana gövde |
| `otto_leg_left.stl` | ~25mm x 20mm x 35mm | Sol bacak |
| `otto_leg_right.stl` | ~25mm x 20mm x 35mm | Sağ bacak |
| `otto_foot_left.stl` | ~35mm x 45mm x 15mm | Sol ayak |
| `otto_foot_right.stl` | ~35mm x 45mm x 15mm | Sağ ayak |

### Orijinal OTTO STL Kaynakları

Orijinal OTTO parçaları için:
- 🔗 [OttoDIY GitHub](https://github.com/OttoDIY/DIY)
- 🔗 [Thingiverse](https://www.thingiverse.com/thing:1568652)

---

## 🔧 ESP32-CAM Kafa Modifikasyonları

Eğer kendi modifikasyonunuzu yapmak isterseniz, orijinal OTTO head STL'ini alın ve şu değişiklikleri yapın:

### Eklenecek Özellikler

#### 1. Kamera Lens Deliği
- **Pozisyon:** Ön yüz ortası (burun/ağız bölgesi)
- **Boyut:** 8mm çap dairesel delik
- **Konik genişleme:** 66° açı (kamera görüş açısı için)

#### 2. ESP32-CAM Modül Yuvası
- **Boyut:** 41mm x 28mm x 12mm derinlik
- **Vida delikleri:** 4 adet M2 (2.2mm çap)
- **Vida pozisyonu:** Köşelerden 2mm içeride

#### 3. Cherry MX Switch Deliği
- **Pozisyon:** Kafa tepesi, ortada
- **Boyut:** 14mm x 14mm kare
- **Derinlik:** 5mm
- **PCB klip delikleri:** 1.5mm çap

#### 4. WiFi Anten Slot
- **Pozisyon:** Kafa arkası üst
- **Boyut:** 3mm x 20mm yatay slot

#### 5. Havalandırma Delikleri
- **Yan:** Her iki yanda 3 adet 4mm delik
- **Arka:** 2 adet 5mm delik

#### 6. OLED Montaj (Korunacak)
- **Pozisyon:** Üst ön kısım (göz bölgesi)
- **Pencere:** 27mm x 27mm
- **Vida delikleri:** 4 adet M2

#### 7. Kablo Kanalları
- **Servo:** 6mm x 4mm
- **I2C:** 4mm x 3mm
- **Power:** 8mm x 5mm
- **USB:** 10mm x 5mm (programlama erişimi)

### Manuel Modifikasyon Alternatifleri

3D modelleme yazılımı kullanmıyorsanız, orijinal OTTO head basıp şu delikleri manuel açabilirsiniz:

1. **Kamera deliği:** 8mm matkap ucu ile
2. **Cherry MX:** Kare eğe ile 14x14mm
3. **Havalandırma:** 4mm ve 5mm matkap uçları
4. **Anten slot:** Dremel veya eğe ile

---

## ⚙️ Baskı Sonrası İşlemler / Post-Processing

### 1. Destek Temizliği
- Pense ile büyük parçaları çıkarın
- Keski veya bıçak ile kalanları temizleyin
- Zımpara ile pürüzleri giderin

### 2. Vida Delikleri
- M2 delikleri: 2mm matkap ile temizleyin
- M3 delikleri: 2.5mm matkap ile temizleyin
- Thread tap kullanırsanız daha iyi vida tutunması sağlanır

### 3. Servo Yuvaları
- Servoyu test edin, çok sıkıysa zımpara ile genişletin
- Çok gevşekse sıcak silikon ile sabitleyin

### 4. Yüzey İşleme (İsteğe Bağlı)
- PLA için: Sıcak hava tabancası ile hafif ütüleme
- Boya için: Primer uygulayın

---

## 📊 Malzeme Hesaplama / Material Calculation

### Toplam Filament Kullanımı (Tahmini)

| Parça | PLA (gram) | Baskı Süresi |
|-------|------------|--------------|
| Kafa | 35g | 3.5 saat |
| Gövde | 25g | 2.5 saat |
| Bacaklar (2x) | 15g | 2 saat |
| Ayaklar (2x) | 20g | 1.5 saat |
| **TOPLAM** | **~95g** | **~9.5 saat** |

---

## ❓ Sık Sorulan Sorular / FAQ

**S: Hangi renk filament kullanmalıyım?**
> Tercihinize göre. Klasik OTTO beyaz veya mavi. ESP32-CAM versiyonu için siyah kafa şık görünür.

**S: Destek hangi parçalar için gerekli?**
> Sadece kafa için gerekli. Diğer parçalar desteksiz basılabilir.

**S: PETG mi PLA mı?**
> Başlangıç için PLA. Robotunuzu açık havada kullanacaksanız PETG tercih edin.

**S: Baskı yönü neden önemli?**
> Katman yönü, parçanın mukavemetini ve yüzey kalitesini etkiler.

---

## 🔗 Faydalı Linkler

- [OttoDIY Assembly Guide](https://www.ottodiy.com/academy)
- [Bambu Lab Wiki](https://wiki.bambulab.com/)
- [PrusaSlicer Profiles](https://github.com/prusa3d/PrusaSlicer)

---

*Bu rehber ESP32-CAM OTTO robot projesi için hazırlanmıştır.*
