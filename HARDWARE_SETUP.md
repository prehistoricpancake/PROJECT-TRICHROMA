# PROJECT TRICHROMA - Hardware Setup Guide

## Required Components

### Essential Parts
- **1× Arduino Uno** (or compatible ATmega328P board)
- **1× Red LED** (5mm standard)
- **1× Blue LED** (5mm standard)
- **1× Green LED** (5mm standard)
- **3× 220Ω resistors** (red-red-brown-gold bands)
- **1× Breadboard** (400 or 830 tie-points)
- **Jumper wires** (male-to-male, various colors)
- **1× USB A-to-B cable** (for Arduino Uno)

### Optional Parts
- **LED holders** (5mm panel mount, if building enclosure)
- **Project enclosure** (for permanent installation)
- **Diffused LEDs** (for softer light effect)
- **Higher value resistors** (330Ω-470Ω if LEDs too bright)

---

## Component Specifications

### Arduino Uno
- **Microcontroller:** ATmega328P
- **Operating Voltage:** 5V
- **Flash Memory:** 32KB (0.5KB used by bootloader)
- **SRAM:** 2KB
- **Digital I/O Pins:** 14 (3 used for LEDs)
- **USB Connection:** Type B

### LEDs
- **Type:** 5mm standard LEDs
- **Forward Voltage:** ~2V (Red), ~3V (Blue/Green)
- **Forward Current:** 20mA (typical)
- **Polarity:** Long leg = Anode (+), Short leg = Cathode (-)

### Resistors
- **Value:** 220Ω (recommended)
- **Alternatives:** 330Ω (dimmer), 470Ω (much dimmer)
- **Power Rating:** 1/4W (standard)
- **Tolerance:** 5% (gold band)

---

## Wiring Diagram

### ASCII Diagram
```
                    Arduino Uno
                   ┌───────────┐
                   │           │
                   │    USB    │ ← Connect to computer
                   │           │
                   ├───────────┤
                   │           │
Pin 12 ────────────┤ D12       │
                   │           │
Pin 8  ────────────┤ D8        │
                   │           │
Pin 4  ────────────┤ D4        │
                   │           │
GND    ────────────┤ GND       │
                   │           │
                   └───────────┘

Pin 12 ──┬── [220Ω Resistor] ──┬── RED LED (long leg)
         │                      │
         │                      └── RED LED (short leg) ── GND
         │
Pin 8  ──┬── [220Ω Resistor] ──┬── GREEN LED (long leg)
         │                      │
         │                      └── GREEN LED (short leg) ── GND
         │
Pin 4  ──┬── [220Ω Resistor] ──┬── BLUE LED (long leg)
         │                      │
         │                      └── BLUE LED (short leg) ── GND
```

### Breadboard Layout
```
Arduino Uno                    Breadboard
┌─────────┐                   ┌──────────────────┐
│         │                   │ + Rail (unused)  │
│   D12 ──┼───────────────────┼─→ Row 10         │
│         │                   │                  │
│   D8  ──┼───────────────────┼─→ Row 15         │
│         │                   │                  │
│   D4  ──┼───────────────────┼─→ Row 20         │
│         │                   │                  │
│   GND ──┼───────────────────┼─→ - Rail (GND)   │
│         │                   │                  │
└─────────┘                   └──────────────────┘

Row 10: Pin 12 → [220Ω] → RED LED (+) → RED LED (-) → GND Rail
Row 15: Pin 8  → [220Ω] → GREEN LED (+) → GREEN LED (-) → GND Rail
Row 20: Pin 4  → [220Ω] → BLUE LED (+) → BLUE LED (-) → GND Rail
```

---

## Step-by-Step Assembly

### Step 1: Prepare Components
1. Identify LED polarity:
   - **Long leg** = Anode (positive, +)
   - **Short leg** = Cathode (negative, -)
   - **Flat edge** on LED body = Cathode side
2. Check resistor values (220Ω = red-red-brown-gold)
3. Ensure Arduino is **unpowered** during assembly

### Step 2: Insert LEDs into Breadboard
1. **RED LED:**
   - Long leg (anode) into Row 10, Column E
   - Short leg (cathode) into Row 11, Column E
2. **GREEN LED:**
   - Long leg (anode) into Row 15, Column E
   - Short leg (cathode) into Row 16, Column E
3. **BLUE LED:**
   - Long leg (anode) into Row 20, Column E
   - Short leg (cathode) into Row 21, Column E

**Spacing:** Leave 5 rows between each LED for clarity.

### Step 3: Insert Resistors
1. **RED LED Resistor:**
   - One leg into Row 10, Column C
   - Other leg into Row 8, Column C
2. **GREEN LED Resistor:**
   - One leg into Row 15, Column C
   - Other leg into Row 13, Column C
3. **BLUE LED Resistor:**
   - One leg into Row 20, Column C
   - Other leg into Row 18, Column C

**Note:** Resistor orientation doesn't matter (non-polarized).

### Step 4: Connect Arduino to Resistors
Use jumper wires:
1. **Pin 12 → RED resistor** (Row 8, Column C)
2. **Pin 8 → GREEN resistor** (Row 13, Column C)
3. **Pin 4 → BLUE resistor** (Row 18, Column C)

### Step 5: Connect Ground Rail
1. Connect breadboard **negative rail** to Arduino **GND** pin
2. Use jumper wires from LED cathodes to negative rail:
   - Row 11, Column E → Negative rail (RED LED cathode)
   - Row 16, Column E → Negative rail (GREEN LED cathode)
   - Row 21, Column E → Negative rail (BLUE LED cathode)

### Step 6: Verify Connections
Double-check:
- ✓ All LEDs have correct polarity (long leg to resistor)
- ✓ All resistors connected between Arduino pin and LED anode
- ✓ All LED cathodes connected to GND rail
- ✓ GND rail connected to Arduino GND
- ✓ No short circuits (wires touching)

---

## Pin Assignment Reference

| Arduino Pin | Component | LED Color | Consciousness Channel |
|-------------|-----------|-----------|----------------------|
| Pin 12 | RED LED | Red | Emotional State |
| Pin 8 | GREEN LED | Green | Identity/Self |
| Pin 4 | BLUE LED | Blue | Logic/Memory |
| GND | Common Ground | - | - |

**Why these pins?**
- Pins 12, 8, 4 don't have hardware PWM
- Software PWM implemented in code
- Pins chosen to avoid conflicts with Serial (0, 1) and SPI (10, 11, 13)

---

## Software Upload

### Step 1: Install Arduino IDE
1. Download from: https://www.arduino.cc/en/software
2. Install for your operating system
3. Launch Arduino IDE

### Step 2: Configure Board
1. Connect Arduino Uno via USB
2. In Arduino IDE:
   - **Tools → Board → Arduino AVR Boards → Arduino Uno**
   - **Tools → Port → [Select your Arduino's port]**
     - macOS: `/dev/cu.usbmodem*` or `/dev/cu.usbserial*`
     - Windows: `COM3`, `COM4`, etc.
     - Linux: `/dev/ttyACM0` or `/dev/ttyUSB0`

### Step 3: Upload Sketch
1. Open `project_trichroma.ino`
2. Click **Verify** (checkmark icon) to compile
3. Check compilation output:
   - Sketch size should be < 32KB
   - RAM usage should be < 2KB
4. Click **Upload** (arrow icon)
5. Wait for "Done uploading" message

### Step 4: Open Serial Monitor
1. **Tools → Serial Monitor** (or Ctrl+Shift+M / Cmd+Shift+M)
2. Set baud rate: **9600**
3. Set line ending: **Newline** or **Both NL & CR**
4. Watch boot sequence begin

---

## Testing and Troubleshooting

### Initial Power-On Test
1. Connect Arduino via USB
2. All three LEDs should light up during boot sequence
3. Serial Monitor should display PDP-10 boot text
4. LEDs should respond to room changes

### LED Testing

#### Test 1: All LEDs Light
**Expected:** All three LEDs illuminate during boot  
**If not:**
- Check LED polarity (swap if backwards)
- Check resistor connections
- Verify GND connections

#### Test 2: Individual LED Control
**Expected:** LEDs change brightness independently  
**If not:**
- Check pin assignments in code match wiring
- Verify no crossed wires
- Test with multimeter (continuity mode)

#### Test 3: LED Patterns
**Expected:** Smooth pulsing, breathing, strobing  
**If not:**
- LEDs may be too dim (use lower resistor value)
- LEDs may be too bright (use higher resistor value)
- Check software PWM implementation

### Serial Communication Testing

#### Test 1: Boot Sequence
**Expected:** PDP-10 header, warnings, room description  
**If not:**
- Check baud rate is 9600
- Check line ending setting
- Try different USB cable
- Restart Arduino

#### Test 2: Command Input
**Expected:** Commands processed and responded to  
**If not:**
- Verify line ending is Newline or Both NL & CR
- Check for typos in commands
- Try simple command like `HELP`

### Common Issues

#### Issue: LEDs Don't Light
**Causes:**
- Reversed LED polarity
- No GND connection
- Resistor value too high
- Faulty LED

**Solutions:**
- Swap LED legs
- Check GND rail continuity
- Use 220Ω resistors
- Test LED with multimeter

#### Issue: LEDs Too Dim
**Causes:**
- Resistor value too high
- Poor connections
- Low USB power

**Solutions:**
- Use 220Ω instead of 330Ω or 470Ω
- Check all connections
- Use powered USB hub

#### Issue: LEDs Too Bright
**Causes:**
- Resistor value too low
- No resistor (dangerous!)

**Solutions:**
- Use 330Ω or 470Ω resistors
- Never omit resistors (will damage LED/Arduino)

#### Issue: Serial Monitor Shows Garbage
**Causes:**
- Wrong baud rate
- Corrupted upload
- Faulty USB cable

**Solutions:**
- Set to 9600 baud
- Re-upload sketch
- Try different cable

#### Issue: Commands Not Working
**Causes:**
- Wrong line ending setting
- Case sensitivity (shouldn't matter)
- Typos

**Solutions:**
- Set to Newline or Both NL & CR
- Check command spelling
- Try uppercase commands

---

## Advanced Modifications

### Brightness Adjustment
To change LED brightness, modify resistor values:
- **Brighter:** 150Ω-220Ω (more current)
- **Standard:** 220Ω-330Ω (recommended)
- **Dimmer:** 470Ω-1kΩ (less current)

**Formula:** R = (Vsupply - Vled) / Iled
- Vsupply = 5V (Arduino)
- Vled = 2V (Red), 3V (Blue/Green)
- Iled = 20mA (0.02A) typical

### Diffused LEDs
Replace standard LEDs with diffused/frosted LEDs for:
- Softer light
- Better ambient effect
- Less harsh brightness

### LED Positioning
For better visual effect:
- Space LEDs 2-3 inches apart
- Mount in enclosure with diffuser
- Angle toward viewing area
- Use colored acrylic for glow effect

### External Power
For brighter LEDs or more components:
1. Use external 5V power supply
2. Connect to Arduino Vin pin
3. Share common ground
4. Don't exceed 500mA total current

---

## Safety Notes

### Electrical Safety
- ✓ Always use current-limiting resistors with LEDs
- ✓ Never exceed LED maximum current (typically 20-30mA)
- ✓ Don't short circuit Arduino pins
- ✓ Disconnect power before modifying circuit
- ✓ Use proper polarity for LEDs

### Component Protection
- ✓ Handle Arduino by edges, avoid touching components
- ✓ Store in anti-static bag when not in use
- ✓ Don't expose to moisture or extreme temperatures
- ✓ Use proper USB cable (data + power, not charge-only)

---

## Enclosure Ideas

### Simple Enclosure
- Cardboard box with LED holes
- Black interior for better LED visibility
- USB cable exit hole

### Advanced Enclosure
- 3D printed case with diffusers
- Acrylic front panel (frosted)
- Labeled LED channels (RED/BLUE/GREEN)
- Ventilation holes for Arduino

### Artistic Enclosure
- Vintage computer aesthetic
- Retro terminal styling
- "CHROMATIC RESEARCH LAB" label
- Warning stickers ("CONSCIOUSNESS CONTAINMENT")

---

## Maintenance

### Regular Checks
- Inspect connections for looseness
- Check for oxidation on breadboard contacts
- Verify USB cable integrity
- Test all three LEDs periodically

### Long-Term Storage
- Disconnect power
- Store in dry location
- Protect from dust
- Keep away from magnetic fields

---

## Specifications Summary

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC (USB) |
| Current Draw | ~60mA (all LEDs on) |
| Power Consumption | ~0.3W |
| LED Forward Current | 20mA each |
| Resistor Power | 0.06W each (1/4W rated) |
| Operating Temperature | 0-50°C |
| Dimensions | Depends on breadboard/enclosure |

---

*For software setup and gameplay, see PLAYER_GUIDE.md*  
*For troubleshooting gameplay issues, see WALKTHROUGH.md*
