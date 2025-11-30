# 🤖 OTTO ESP32-CAM - Dancing Robot with Camera

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32--CAM-blue.svg)](https://www.espressif.com/)

OTTO dancing robot enhanced with ESP32-CAM module for camera capabilities!

🌐 **[Türkçe Versiyon](README.md)**

---

## ✨ Features

- 📸 **ESP32-CAM integration** - Live camera streaming and photo capture
- 🎭 **Rich eye animations** - 15+ expressions on OLED display (happy, sad, angry, love, etc.)
- 💃 **15+ dance moves** - Moonwalk, swing, crusaito, flapping, gangnam style and more
- 🎵 **Music dances** - Baby Shark, If You're Happy, and Turkish children's songs
- 🎮 **Web control** - Full control interface from browser
- 🔘 **Cherry MX button** - Physical mode switching button
- 🤖 **Autonomous mode** - Random dancing on its own
- 🎉 **Party mode** - Music with random dances
- 🔊 **Sound effects** - R2D2, laser, police, game over and more
- 📡 **WiFi connectivity** - Remote control and monitoring

---

## 📁 Project Structure

```
otto-esp32cam/
├── firmware/
│   └── otto_esp32cam/
│       ├── otto_esp32cam.ino    # Main firmware
│       └── config.h              # Configuration settings
├── stl/
│   ├── otto_head_esp32cam.stl   # Modified head for ESP32-CAM
│   ├── otto_body.stl            # Body
│   ├── otto_leg_left.stl        # Left leg
│   ├── otto_leg_right.stl       # Right leg
│   ├── otto_foot_left.stl       # Left foot
│   └── otto_foot_right.stl      # Right foot
├── docs/
│   ├── WIRING.md                # Wiring diagram
│   ├── PRINTING.md              # 3D printing guide
│   ├── BOM.md                   # Bill of Materials
│   └── ASSEMBLY.md              # Assembly guide
├── images/
│   └── ...                      # Project images
├── README.md                    # Turkish documentation
├── README_EN.md                 # This file (English)
├── platformio.ini               # PlatformIO configuration
└── LICENSE                      # MIT License
```

---

## 🛠️ Required Materials

See [docs/BOM.md](docs/BOM.md) for detailed list.

### Core Components

| Component | Qty | Description |
|-----------|-----|-------------|
| ESP32-CAM (AI-Thinker) | 1 | Main control board + camera |
| SG90 Servo Motor | 4 | Leg and foot movement |
| 0.96" OLED (SSD1306) | 1 | Eye animations |
| Cherry MX Switch | 1 | Mode switching button |
| Passive Buzzer | 1 | Sound effects |
| Li-Po Battery (7.4V) | 1 | Power supply |

---

## 📐 3D Printing

See [docs/PRINTING.md](docs/PRINTING.md) for print settings.

### Quick Print Settings

- **Layer height:** 0.2mm
- **Infill:** 20%
- **Supports:** Required (for head)
- **Filament:** PLA or PETG

---

## 🔌 Wiring Diagram

See [docs/WIRING.md](docs/WIRING.md) for detailed schematic.

### Pin Connections

| ESP32-CAM Pin | Component | Description |
|---------------|-----------|-------------|
| GPIO 12 | Servo YL | Left leg |
| GPIO 13 | Servo YR | Right leg |
| GPIO 14 | Servo RL | Left foot |
| GPIO 15 | Servo RR | Right foot |
| GPIO 2 | Buzzer | Passive buzzer |
| GPIO 4 | Button | Cherry MX switch |
| GPIO 3 (RX) | OLED SDA | I2C Data |
| GPIO 1 (TX) | OLED SCL | I2C Clock |

---

## 🚀 Installation

### 1. Arduino IDE Setup

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add to **File > Preferences > Additional Board URLs**:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools > Board > Boards Manager** > search "esp32" and install

### 2. Libraries

Install via **Tools > Manage Libraries**:
- `Adafruit SSD1306`
- `Adafruit GFX Library`

### 3. Configuration

Edit `firmware/otto_esp32cam/config.h`:

```cpp
const char* WIFI_SSID = "Your_WiFi_Name";
const char* WIFI_PASS = "Your_WiFi_Password";
```

### 4. Upload

1. **Tools > Board** > Select "AI Thinker ESP32-CAM"
2. **Tools > Port** > Select USB port
3. Click **Upload** button

> ⚠️ **Note:** You may need to connect GPIO0 to GND during upload.

### PlatformIO Alternative

If using PlatformIO:

```bash
cd firmware/otto_esp32cam
pio run -t upload
```

---

## 📷 Usage

### Web Interface

After the robot connects to WiFi, you can see the IP address on the OLED display.
Open in your browser:

- `http://<IP_ADDRESS>/` - Main control panel
- `http://<IP_ADDRESS>/camera` - Live camera view
- `http://<IP_ADDRESS>/status` - Status info (JSON)

### Cherry MX Button

Press the button on the head to cycle through modes:

1. **IDLE** - Standby mode
2. **AUTO** - Autonomous dancing
3. **DANCE** - Continuous dance
4. **PARTY** - Music party mode
5. **SLEEP** - Sleep mode
6. **MUSIC** - Song with dance

---

## 🎵 Sound and Dance

### Dance Moves

- Walk
- Moonwalk
- Swing
- Crusaito
- Flapping
- Jump
- Shake
- Turn

### Music Dances

- 🦈 Baby Shark
- 😊 If You're Happy
- ❤️ Turkish Children's Song

### Sound Effects

- Happy / Sad sounds
- R2D2 beeps
- Laser sound
- Police siren
- Game over melody

---

## 🔧 Troubleshooting

| Problem | Solution |
|---------|----------|
| WiFi not connecting | Check SSID/password, try Access Point mode |
| Camera not working | Check pin connections |
| Servo jittering | Check power supply, add capacitor |
| OLED not displaying | Check I2C address (0x3C or 0x3D) |
| Upload failed | GPIO0 to GND connection, try different USB cable |

---

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- [OttoDIY](https://www.ottodiy.com/) - Original OTTO robot design
- [Espressif](https://www.espressif.com/) - ESP32 platform
- ESP32-CAM community
- All contributors

---

## 🤝 Contributing

1. Fork the project
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## 📞 Contact

Feel free to open an issue or submit a pull request for any questions.

---

Made with ❤️ for robotics enthusiasts
