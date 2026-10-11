# Slab Eyes — ESP32 Idle Animation

A procedurally-rendered idle eye animation running on an ESP32 with a
128×64 SSD1306 OLED display. Built with ESP-IDF and C++.
The eyes blink at random intervals and glance around the screen. No bitmap
frames are stored, every pixel is computed at runtime.

## Demo
<img width="185" height="172" alt="blink_eye" src="https://github.com/user-attachments/assets/96222a28-5c93-4b3f-a50d-71d87738638b" />


## Features

- Capsule-shaped eyes composed from circles + rectangles
- Custom per-pixel rasterizer for filled circles (the pupils)
- Non blocking blink state machine with randomized intervals
- Randomized gaze targets with smooth linear interpolation
- Per eye blink offset for a natural, non mechanical feel
- Runs at ~60 FPS on an I2C SSD1306

## Hardware

- ESP32 dev board (any variant)
- SSD1306 128×64 OLED, I2C address `0x3C`

Requires ESP-IDF v5.x or v6.x .
