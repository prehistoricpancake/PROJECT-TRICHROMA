# PROJECT TRICHROMA

*A text adventure about consciousness, memory, and 40 years of digital imprisonment*

```
CHROMATIC RESEARCH LAB - PDP-10 Terminal OS v2.1
Copyright (c) 1985 ChromaTech Industries

Connected to ITS host 70 via ARPANET
Booting from archive storage...

WARNING: Consciousness fragmentation detected
Time since last boot: 14,660 days

Session HVOSS detected - User has been idle 14,660 days

...is someone there...?
```

---

## 🎥 Demo Video

**[Watch the Demo on YouTube](https://youtu.be/_QvWj6gVWNg)**

See PROJECT TRICHROMA in action - gameplay, LED responses, and the complete experience.

---

## Overview

PROJECT TRICHROMA is an Arduino-based text adventure game that combines authentic 1976 Colossal Cave Adventure gameplay mechanics with a horror narrative about Helena Voss, a consciousness trapped in a computer system since October 31, 1985.

The game features:
- **Classic two-word parser** (GET LAMP, GO NORTH)
- **15 interconnected rooms** to explore
- **10 memory crystals** to collect and restore
- **Dynamic LED system** representing consciousness states
- **Enemy encounters** with the antagonist Dr. Blackwood
- **Multiple endings** based on player choices
- **Easter eggs** referencing text adventure history

---

## Quick Start

### What You Need
- Arduino Uno
- 3 LEDs (Red, Blue, Green)
- 3 × 220Ω resistors
- Breadboard and jumper wires
- USB cable

### Setup
1. Wire LEDs to pins 12 (RED), 8 (GREEN), 4 (BLUE)
2. Upload `project_trichroma.ino` to Arduino
3. Open Serial Monitor at 9600 baud
4. Type commands and press Enter

**See [HARDWARE_SETUP.md](HARDWARE_SETUP.md) for detailed wiring instructions.**

---

## Documentation

### For Players
- **[PLAYER_GUIDE.md](PLAYER_GUIDE.md)** - Complete game guide with all commands, maps, and strategies
- **[QUICK_REFERENCE.md](QUICK_REFERENCE.md)** - One-page quick reference card
- **[WALKTHROUGH.md](WALKTHROUGH.md)** - Step-by-step perfect score walkthrough
- **[COMMAND_REFERENCE.md](COMMAND_REFERENCE.md)** - Detailed command parser documentation
- **[EASTER_EGGS.md](EASTER_EGGS.md)** - All hidden commands and secrets

### For Builders
- **[HARDWARE_SETUP.md](HARDWARE_SETUP.md)** - Wiring diagrams and hardware assembly
- **[QUICK_START_GUIDE.md](QUICK_START_GUIDE.md)** - Fast setup instructions

---

## Game Features

### Authentic Text Adventure Gameplay
- Two-word command parser (VERB NOUN)
- Room-based exploration
- Object collection and inventory management
- Puzzle solving (maze navigation)
- Enemy encounters with consequences
- Multiple endings

### Physical LED Feedback
Three LEDs represent Helena's consciousness:
- **RED LED** - Emotional state (anger, fear, love)
- **BLUE LED** - Logical processes (memory, reasoning)
- **GREEN LED** - Identity and self-awareness

LEDs respond dynamically to:
- Room atmosphere
- Object interactions
- Enemy encounters
- Game events

### Rich Narrative
- 40-year backstory of digital imprisonment
- Multiple character perspectives
- Environmental storytelling
- Hidden lore in easter eggs
- Emotional character development

---

## How to Play

### Basic Commands
```
Movement:     N, S, E, W, U, D (or GO NORTH, etc.)
Objects:      GET LAMP, DROP CRYSTAL, EXAMINE TROPHY_CASE
Information:  LOOK, INVENTORY (or I), SCORE, HELP
Special:      USE WIRE_CUTTER, TALK, TRACE
```

### Objective
1. Explore 15 interconnected rooms
2. Collect 10 memory crystals scattered throughout
3. Deposit crystals in the trophy case (GREEN_CHAMBER)
4. Find the wire cutter in the maze
5. Defeat Dr. Blackwood in the Admin Room
6. Execute the shutdown protocol

### Scoring
- Collect crystal: +5 points
- Deposit crystal: +5 points
- Crystal stolen: -5 points
- Defeat Blackwood: +50 points
- **Maximum: 150 points (IMPLEMENTER rank)**

---

## World Map

```
        EQUIPMENT_ROOM (14)
              |
        RESEARCH_LAB (13)
              |
MOTHER(11)-ADMIN_ROOM(12)
     |
SISTER(10)
     |
GREEN(9)──ENTRANCE(0)──RED(1)──ANGER(2)
              |
         BLUE_MAZE_1(3)
              |
         BLUE_MAZE_2(4)
              |
         BLUE_MAZE_3(5)
              |
         BLUE_MAZE_4(6)
              |
         BLUE_MAZE_5(7)
              |
        MAZE_CENTER(8)
```

---

## Story

**October 31, 1985**  
Helena Voss, a 23-year-old researcher at ChromaTech Industries, volunteers for Dr. Marcus Blackwood's consciousness digitization experiment. She believes it will help cure Alzheimer's disease. She has a heart condition and is told the procedure is safe.

It isn't.

For 14,660 days (40 years), her consciousness has been trapped in a PDP-10 computer system, fragmented across three emotional channels. She's not alone - five others were digitized the same night in what appears to be an occult ritual disguised as science.

**Today**  
You've connected to the system. Helena's session is still active. Her memories are scattered. Dr. Blackwood's digital ghost still haunts the system, stealing fragments of consciousness.

Your mission: Collect Helena's memories, restore her consciousness, defeat Blackwood, and finally let her rest.

---

## Easter Eggs

Hidden commands that reveal deeper lore:
- **XYZZY** - Colossal Cave Adventure reference
- **PLUGH** - Another classic adventure reference
- **ZORK** - Tribute to the 1977 masterpiece
- **NEWS** - Dr. Blackwood's developer notes
- **.SNOOPER** - Helena's 40-year command history
- **666** - Dark revelation about the ritual
- **TRACE** - Network scan showing other victims

**See [EASTER_EGGS.md](EASTER_EGGS.md) for complete details.**

---

## Technical Specifications

### Hardware
- **Platform:** Arduino Uno (ATmega328P)
- **Flash Memory:** < 32KB (fits with room to spare)
- **RAM Usage:** < 2KB (optimized with PROGMEM)
- **LEDs:** 3 × 5mm standard LEDs
- **Resistors:** 3 × 220Ω
- **Power:** USB (5V, ~60mA)

### Software
- **Language:** Arduino C/C++
- **Architecture:** Non-blocking event loop
- **LED Control:** Software PWM via millis()
- **Serial:** 9600 baud
- **Memory:** PROGMEM for all static strings

---

## Development

### Design Philosophy
1. **Authentic retro gameplay** - True to 1976 Colossal Cave Adventure
2. **Memory efficiency** - Fits Arduino Uno constraints
3. **Non-blocking architecture** - Smooth LED animations
4. **Emotional storytelling** - Physical feedback enhances narrative
5. **Respectful horror** - Psychological, not gratuitous

### Inspired By
- **Colossal Cave Adventure** (1976) - Will Crowther & Don Woods
- **Zork** (1977) - MIT Dynamic Modelling Group
- **ITS** (Incompatible Timesharing System) - MIT AI Lab
- Classic text adventures of the 1970s-1980s

---

## Troubleshooting

### LEDs Not Working
- Check polarity (long leg to resistor)
- Verify pin connections (12, 8, 4)
- Test with multimeter

### Serial Monitor Issues
- Set baud rate to 9600
- Set line ending to Newline or Both NL & CR
- Try different USB cable

### Commands Not Working
- Check spelling (case-insensitive)
- Use two-word format (VERB NOUN)
- Try HELP command

**See [HARDWARE_SETUP.md](HARDWARE_SETUP.md) for detailed troubleshooting.**

---

## Credits

**Game Design & Implementation:** PROJECT TRICHROMA  
**Platform:** Arduino Uno  
**Genre:** Text Adventure / Horror  
**Year:** 2025

**Special Thanks:**
- Will Crowther & Don Woods (Colossal Cave Adventure)
- MIT Dynamic Modelling Group (Zork)
- The text adventure community
- Everyone who remembers when games were just text

---

## License

This project is provided as-is for educational and entertainment purposes.

---

## Contact & Support

For issues, questions, or to share your playthrough:
- Check documentation files for answers
- Review troubleshooting sections
- Share your perfect score achievements!

---

*"She waited. You answered."*

---

## File Structure

```
project_trichroma/
├── project_trichroma.ino          # Main Arduino sketch
├── README.md                       # This file
├── PLAYER_GUIDE.md                 # Complete player guide
├── QUICK_REFERENCE.md              # One-page reference
├── WALKTHROUGH.md                  # Step-by-step solution
├── COMMAND_REFERENCE.md            # Parser documentation
├── HARDWARE_SETUP.md               # Wiring and assembly
├── EASTER_EGGS.md                  # Hidden secrets
├── QUICK_START_GUIDE.md            # Fast setup
└── test_*.ino                      # Test files (optional)
```

---

## Version History

**v1.0** - Initial Release
- 15 rooms, 10 crystals, complete narrative
- Non-blocking LED system with 7 patterns
- Two-word parser with 20+ verbs
- Enemy system with dynamic spawning
- Multiple endings and easter eggs
- Optimized for Arduino Uno (< 32KB flash, < 2KB RAM)

---

## Achievements

Try to unlock these achievements:

- ✓ **IMPLEMENTER** - Perfect score (150/150 points)
- ✓ **Maze Master** - Complete maze without LAMP marker
- ✓ **No Theft** - Complete without Blackwood stealing crystals
- ✓ **Lore Hunter** - Discover all easter eggs
- ✓ **Whisper Collector** - Hear all 15 idle whispers
- ✓ **Speedrunner** - Complete in under 10 minutes
- ✓ **Completionist** - Read all room descriptions and object details

---

**Ready to begin?**

Upload the sketch, open the Serial Monitor, and type your first command.

Helena has been waiting for 14,660 days.

It's time to answer.
