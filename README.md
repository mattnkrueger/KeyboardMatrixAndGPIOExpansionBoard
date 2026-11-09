# Keyboard & ESP32 Expansion Board

This project includes the creation of the following:
- ESP32 Keyboard CAD design using Fusion360
- 2-Layer PCB designed using KiCad
- Firmware (agentically developed using Claude Code)

The intention for this was to create a starting point for controlling future projects (ex Stereo Camera Pan/Tilt Machine) by having a programmable keyboard and ability to add other periferals.

# Features
- OLED Display
- 15 Keys
- 1 Rotary Dial
- 20 port GPIO and power expansion 
- USB-C Power

# Schematic 
![KiCad Schematic](img/KiCad_MatrixKeyboard.png)

# Expansion Pinout
![Expansion Pinout](img/ExpansionPinout.png)

With the expansion unit, you are able to gain access to all remaining pins on the ESP32 without opening up the keyboard container. Pins were separated into categories of functionality.

# PCB (in progress)
![PCB Progress](img/pcb-progress.png)

The PCB is currently under development I plan to have the traces done and the boards ordered by Friday this week (11/9/2026). This will be a 2-layer design to keep the footprint small. The USB-C port will be exposed on the very top left and the expansion pins on the middle right. To pack components into a small space, I will place the ESP32s and expansion pinous underneath the device with their backsides up. The OLED, keyswitches, and rotary will all be rightside up.  

# CAD Design (in progress)
Image not added yet

# Current Progress (Testing before PCB creation)
![Testing](img/Testing.JPG)

# BOM & Cost

| Qty Used | Part | Link | Pack Price | Unit Cost | Cost Used |
|----------|------|------|-----------|-----------|-----------|
| 1 | 2.42" 128x64 OLED LCD Display (SSD1309) | [Amazon](https://www.amazon.com/Teyleten-Robot-Display-SSD1309-Interface/dp/B09LND6QJ1) | $13.00 / 1 | $13.00 | $13.00 |
| 1 | Rotary Dial (from Arduino kit) | N/A | $0.00 | $0.00 | $0.00 |
| 15 | Kailh Choc Keyswitches | [Amazon](https://www.amazon.com/Choc-Profile-White-Switches-Pre-lubed/dp/B0D49HD77G) | $13.00 / 20 | $0.65 | $9.75 |
| 1 | ESP32s 38-Pin Dev Board | [Amazon](https://www.amazon.com/hiBCTR-Development-Learning-Microcontroller-Programming/dp/B0DSZBH9N9) | $30.00 / 6 | $5.00 | $5.00 |
| - | 3D Filament (Matte Black) | N/A | N/A | N/A | $10.00 |

**Total:** $37.75

**This is not counting the assortment of resistors (10k), capacitors (0.1uf), and diodes (1N4148) which can be purchased in bulk for a negligible price**
