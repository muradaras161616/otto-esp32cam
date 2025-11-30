# 🎨 STL Dosyaları / STL Files

Bu klasör ESP32-CAM OTTO robot için 3D baskı modellerini içerir.

---

## 📦 Dosyalar / Files

### ESP32-CAM Modifiye Kafa / Modified Head

**`otto_head_esp32cam.stl`** - ESP32-CAM için özelleştirilmiş kafa modeli

> ⚠️ **Not:** Bu dosya şu anda placeholder'dır. Kendi modifikasyonunuzu yapmanız veya orijinal OTTO head'i manuel olarak modifiye etmeniz gerekebilir.

### Orijinal OTTO Parçaları / Original OTTO Parts

Aşağıdaki parçalar orijinal OTTO tasarımından alınmalıdır:

| Dosya | Açıklama |
|-------|----------|
| `otto_body.stl` | Ana gövde |
| `otto_leg_left.stl` | Sol bacak |
| `otto_leg_right.stl` | Sağ bacak |
| `otto_foot_left.stl` | Sol ayak |
| `otto_foot_right.stl` | Sağ ayak |

---

## 📥 Orijinal OTTO STL İndirme / Download Original OTTO STL

Orijinal OTTO STL dosyalarını şu kaynaklardan indirebilirsiniz:

1. **OttoDIY GitHub:**
   - 🔗 https://github.com/OttoDIY/DIY
   - `STL` klasörüne gidin

2. **Thingiverse:**
   - 🔗 https://www.thingiverse.com/thing:1568652
   - "Download All Files" butonuna tıklayın

3. **OttoDIY Website:**
   - 🔗 https://www.ottodiy.com/
   - Resources bölümünden indirin

---

## 🔧 ESP32-CAM Kafa Modifikasyonları

Orijinal OTTO head STL'ini alıp aşağıdaki modifikasyonları yapmanız gerekir:

### Kaldırılacaklar / To Remove

- ❌ Ultrasonik sensör (HC-SR04) delikleri

### Eklenecekler / To Add

#### 1. Kamera Lens Deliği / Camera Lens Hole
```
Pozisyon: Ön yüz ortası (burun/ağız bölgesi)
Boyut: 8mm çap dairesel delik
Konik genişleme: 66° açı (kamera görüş açısı için)
```

#### 2. ESP32-CAM Modül Yuvası / Module Slot
```
Pozisyon: Kafa içi
Boyut: 41mm x 28mm x 12mm derinlik
Vida delikleri: 4 adet M2 (2.2mm çap)
Vida pozisyonu: Köşelerden 2mm içeride
```

#### 3. Cherry MX Switch Deliği / Button Hole
```
Pozisyon: Kafa tepesi, ortada
Boyut: 14mm x 14mm kare
Derinlik: 5mm
PCB klip delikleri: 1.5mm çap
```

#### 4. WiFi Anten Slot
```
Pozisyon: Kafa arkası üst
Boyut: 3mm x 20mm yatay slot
```

#### 5. Havalandırma Delikleri / Ventilation
```
Yan taraflar: 3 adet 4mm çap (her iki yanda)
Arka: 2 adet 5mm çap
```

#### 6. Kablo Kanalları / Cable Channels
```
Servo kablo: 6mm x 4mm
I2C kablo: 4mm x 3mm  
Power kablo: 8mm x 5mm
USB erişim: 10mm x 5mm
```

#### 7. OLED Montaj / OLED Mount (Korunacak)
```
Pozisyon: Üst ön (göz bölgesi)
Pencere: 27mm x 27mm
Vida delikleri: 4 adet M2
```

---

## 🛠️ Modifikasyon Araçları

### CAD Yazılımları (Ücretsiz)

| Yazılım | Özellik | Link |
|---------|---------|------|
| FreeCAD | Parametrik, güçlü | https://www.freecad.org |
| Tinkercad | Web tabanlı, kolay | https://www.tinkercad.com |
| Blender | Mesh düzenleme | https://www.blender.org |
| OpenSCAD | Kod tabanlı | https://openscad.org |

### CAD Yazılımları (Ücretli)

| Yazılım | Özellik | Link |
|---------|---------|------|
| Fusion 360 | Hobi için ücretsiz | https://www.autodesk.com/fusion-360 |
| SolidWorks | Profesyonel | https://www.solidworks.com |
| Onshape | Web tabanlı | https://www.onshape.com |

---

## 📐 Boyutlar / Dimensions

### ESP32-CAM Modül Boyutları
```
Uzunluk: 40.5mm
Genişlik: 27mm
Yükseklik: 11mm (anten hariç)
Kamera lens çapı: 7mm
```

### Cherry MX Switch Boyutları
```
Footprint: 15.6mm x 15.6mm
Montaj deliği: 14mm x 14mm
Yükseklik: 11mm
PCB klip aralığı: Standart Cherry MX
```

### OLED Ekran Boyutları (0.96")
```
Dış boyut: 27mm x 27mm
Görüntü alanı: 26.5mm x 19mm
Kalınlık: 4mm
Vida deliği mesafesi: 23.5mm
```

---

## 🖨️ Baskı Ayarları

Detaylı baskı ayarları için [../docs/PRINTING.md](../docs/PRINTING.md) dosyasına bakın.

### Hızlı Referans

| Parametre | Değer |
|-----------|-------|
| Katman | 0.2mm |
| Doluluk | %20 |
| Destek | Kafa için gerekli |
| Malzeme | PLA / PETG |

---

## 🔨 Manuel Modifikasyon (3D Yazılım Kullanmadan)

3D modelleme yazılımı kullanmak istemiyorsanız, orijinal OTTO head'i basıp manuel olarak modifiye edebilirsiniz:

### Gerekli Araçlar
- Matkap ve uçları (2mm, 4mm, 5mm, 8mm)
- Dremel veya döner alet
- Kare eğe (14mm için)
- Zımpara kağıdı
- Cetvel ve kalem

### Adımlar
1. Orijinal OTTO head'i basın
2. Kamera deliği için 8mm ile delin
3. Cherry MX için kare eğe ile 14x14mm açın
4. Havalandırma için uygun bitleri delin
5. ESP32-CAM yuvası için içeriyi düzeltin
6. Tüm kenarları zımpara ile temizleyin

---

## 📝 Notlar

- STL dosyaları manifold (su geçirmez) olmalıdır
- Minimum duvar kalınlığı: 2mm
- Baskı yönlendirmesi optimize edilmiştir
- Orijinal OTTO dosyaları CC BY-SA lisansı altındadır

---

## 🔗 İlgili Dosyalar

- [PRINTING.md](../docs/PRINTING.md) - Baskı rehberi
- [ASSEMBLY.md](../docs/ASSEMBLY.md) - Montaj rehberi
- [BOM.md](../docs/BOM.md) - Malzeme listesi

---

*Bu README, ESP32-CAM OTTO robot STL dosyaları için hazırlanmıştır.*
