# PROJECT TRICHROMA - Complete Documentation

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

# Table of Contents

1. [Overview](#overview)
2. [Quick Start](#quick-start)
3. [Hardware Setup](#hardware-setup)
4. [Command Reference](#command-reference)
5. [World Map & Locations](#world-map--locations)
6. [Complete Walkthrough](#complete-walkthrough)
7. [Easter Eggs & Secrets](#easter-eggs--secrets)
8. [Scoring System](#scoring-system)
9. [Story & Lore](#story--lore)
10. [Troubleshooting](#troubleshooting)
11. [Technical Specifications](#technical-specifications)

---

# Overview

PROJECT TRICHROMA is an Arduino-based text adventure game that combines authentic text based gameplay mechanics with a horror narrative about Helena Voss, a consciousness trapped in a computer system since October 31, 1985.

## Key Features
- **Classic two-word parser** (GET LAMP, GO NORTH)
- **15 interconnected rooms** to explore
- **10 memory crystals** to collect and restore
- **Dynamic LED system** representing consciousness states
- **Enemy encounters** with the antagonist Dr. Blackwood
- **Multiple endings** based on player choices
- **Easter eggs** referencing text adventure history

## The Three LEDs
- **RED LED (Pin 12)** - Emotional state (anger, fear, love)
- **BLUE LED (Pin 4)** - Logical processes (memory, reasoning)
- **GREEN LED (Pin 8)** - Identity and self-awareness

---

# Quick Start

## What You Need
- Arduino Uno
- 3 LEDs (Red, Blue, Green)
- 3 × 220Ω resistors
- Breadboard and jumper wires
- USB cable

## 5-Minute Setup
1. Wire LEDs: Pin 12→RED, Pin 8→GREEN, Pin 4→BLUE (with 220Ω resistors to GND)
2. Upload `project_trichroma.ino` to Arduino
3. Open Serial Monitor at 9600 baud, set line ending to "Newline"
4. Wait for boot sequence
5. Type commands and press Enter

## First Commands to Try
```
HELP          - See available commands
LOOK          - Examine your surroundings
INVENTORY     - Check what you're carrying
GO WEST       - Enter the Green Chamber
GET CRYSTAL   - Pick up a memory crystal
```


---

# Hardware Setup

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
- LED holders (5mm panel mount)
- Project enclosure
- Diffused LEDs (for softer light)
- Higher value resistors (330Ω-470Ω if LEDs too bright)

## Wiring Diagram

### ASCII Diagram
```
                    Arduino Uno
                   ┌───────────┐
                   │           │
                   │    USB    │ ← Connect to computer
                   │           │
                   ├───────────┤
Pin 12 ────────────┤ D12       │
Pin 8  ────────────┤ D8        │
Pin 4  ────────────┤ D4        │
GND    ────────────┤ GND       │
                   └───────────┘

Pin 12 ──[220Ω]── RED LED (long leg) ──┐
Pin 8  ──[220Ω]── GREEN LED (long leg) ├── GND
Pin 4  ──[220Ω]── BLUE LED (long leg) ─┘

LED Polarity: Long leg (anode) to resistor, short leg (cathode) to GND
```

## Step-by-Step Assembly

### Step 1: Identify LED Polarity
- **Long leg** = Anode (positive, +)
- **Short leg** = Cathode (negative, -)
- **Flat edge** on LED body = Cathode side

### Step 2: Insert LEDs into Breadboard
1. **RED LED:** Long leg Row 10E, Short leg Row 11E
2. **GREEN LED:** Long leg Row 15E, Short leg Row 16E
3. **BLUE LED:** Long leg Row 20E, Short leg Row 21E

### Step 3: Insert Resistors
1. **RED:** Between Row 10C and Row 8C
2. **GREEN:** Between Row 15C and Row 13C
3. **BLUE:** Between Row 20C and Row 18C

### Step 4: Connect Arduino to Resistors
1. Pin 12 → RED resistor (Row 8C)
2. Pin 8 → GREEN resistor (Row 13C)
3. Pin 4 → BLUE resistor (Row 18C)

### Step 5: Connect Ground
1. Breadboard negative rail → Arduino GND
2. LED cathodes (short legs) → Negative rail

### Step 6: Verify Connections
- ✓ All LEDs correct polarity (long leg to resistor)
- ✓ All resistors between Arduino pin and LED anode
- ✓ All LED cathodes to GND rail
- ✓ GND rail to Arduino GND
- ✓ No short circuits

## Software Upload

### Step 1: Install Arduino IDE
1. Download from: https://www.arduino.cc/en/software
2. Install and launch

### Step 2: Configure Board
1. Connect Arduino via USB
2. **Tools → Board → Arduino Uno**
3. **Tools → Port → [Select your Arduino]**

### Step 3: Upload Sketch
1. Open `project_trichroma.ino`
2. Click **Verify** (checkmark)
3. Click **Upload** (arrow)
4. Wait for "Done uploading"

### Step 4: Open Serial Monitor
1. **Tools → Serial Monitor** (Ctrl+Shift+M)
2. Set baud rate: **9600**
3. Set line ending: **Newline** or **Both NL & CR**
4. Watch boot sequence

## Pin Assignment Reference

| Arduino Pin | LED Color | Consciousness Channel |
|-------------|-----------|----------------------|
| Pin 12 | RED | Emotional State |
| Pin 8 | GREEN | Identity/Self |
| Pin 4 | BLUE | Logic/Memory |
| GND | - | Common Ground |


---

# Command Reference

## Two-Word Parser System

PROJECT TRICHROMA uses an authentic 1970s-style parser:
- First word = VERB (action)
- Second word = NOUN (object/direction)
- Input converted to UPPERCASE
- Articles (THE, A, AN) automatically removed
- Additional words ignored

## Complete Verb List

### Movement Verbs
| Verb | Usage | Example |
|------|-------|---------|
| GO | GO [direction] | GO NORTH |

**Note:** Single direction words auto-expand to GO commands (N → GO NORTH)

### Object Manipulation Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| GET | TAKE | GET [object] | GET LAMP |
| DROP | - | DROP [object] | DROP CRYSTAL |
| EXAMINE | - | EXAMINE [object] | EXAMINE TROPHY_CASE |
| USE | - | USE [object] | USE WIRE_CUTTER |

### Information Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| LOOK | - | LOOK | LOOK |
| INVENTORY | I | INVENTORY | I |
| SCORE | - | SCORE | SCORE |
| HELP | - | HELP | HELP |

### Communication & System Verbs
| Verb | Usage | Example |
|------|-------|---------|
| TALK | TALK | TALK |
| TRACE | TRACE | TRACE |
| QUIT | QUIT | QUIT |

### Easter Egg Verbs
| Verb | Description |
|------|-------------|
| XYZZY | Colossal Cave Adventure reference |
| PLUGH | Colossal Cave Adventure reference |
| ZORK | Tribute to Zork |
| NEWS | Display in-universe patch notes |
| .SNOOPER | Helena's 40-year command history |
| 666 | Glitch sequence revelation |

## Complete Noun List

### Directions
| Noun | Shortcut | Description |
|------|----------|-------------|
| NORTH | N | Move north |
| SOUTH | S | Move south |
| EAST | E | Move east |
| WEST | W | Move west |
| UP | U | Move up |
| DOWN | D | Move down |

### Objects
| Noun | Location(s) | Properties |
|------|-------------|------------|
| LAMP | Starting inventory | Portable, can be dropped as marker |
| CRYSTAL | Various rooms (10 total) | Portable, treasure, increases LED |
| WIRE_CUTTER | MAZE_CENTER | Portable, required for final boss |
| TROPHY_CASE | GREEN_CHAMBER | Non-portable, stores crystals |
| TERMINAL | Various rooms | Non-portable, flavor object |
| NOTES | RESEARCH_LAB | Non-portable, lore object |

## Command Examples

### Valid Commands
```
> GO NORTH          > N
> GET LAMP          > TAKE CRYSTAL
> DROP THE LAMP     > EXAMINE TROPHY CASE
> USE WIRE_CUTTER   > INVENTORY
> I                 > LOOK
> SCORE             > HELP
> TALK              > XYZZY
> NEWS              > .SNOOPER
> 666               > TRACE
> QUIT
```

### Error Messages
| Error | Cause | Solution |
|-------|-------|----------|
| "I don't know the word '[word]'." | Unrecognized verb/noun | Check command reference |
| "What do you want to [verb]?" | Verb requires noun | Add object/direction |
| "You can't go that way." | No exit in direction | Use LOOK to see exits |
| "I don't see that here." | Object not in room | Use LOOK to see objects |
| "You can't take that." | Object non-portable | Leave it in place |
| "You're carrying too much." | Inventory full (8 items) | Drop something first |

## Special Command Behaviors

### Direction Shortcuts
- `N` → `GO NORTH`
- `S` → `GO SOUTH`
- `E` → `GO EAST`
- `W` → `GO WEST`
- `U` → `GO UP`
- `D` → `GO DOWN`

### Inventory Shortcut
- `I` → `INVENTORY`

### Context-Sensitive Commands

**USE Command:**
- In ADMIN_ROOM with WIRE_CUTTER: Triggers boss battle
- Elsewhere: Generic response

**DROP Command:**
- In GREEN_CHAMBER with CRYSTAL: Auto-deposits in trophy case
- Elsewhere: Drops object in current room

**EXAMINE Command:**
- TROPHY_CASE: Shows crystal count (X of 10)
- CRYSTAL: Shows unique memory description
- Other objects: Shows object description


---

# World Map & Locations

## Complete Room Layout

```
                    EQUIPMENT_ROOM (14)
                           |
                      RESEARCH_LAB (13)
                           |
    MOTHER_MEMORY (11) - ADMIN_ROOM (12)
           |
    SISTER_MEMORY (10)
           |
    GREEN_CHAMBER (9) ─── ENTRANCE (0) ─── RED_CAVERN (1) ─── ANGER_PIT (2)
                               |
                          BLUE_MAZE_1 (3)
                               |
                          BLUE_MAZE_2 (4)
                               |
                          BLUE_MAZE_3 (5)
                               |
                          BLUE_MAZE_4 (6)
                               |
                          BLUE_MAZE_5 (7)
                               |
                          MAZE_CENTER (8)
```

## Room Details

| ID | Room Name | LED Colors | Danger | Key Features |
|----|-----------|------------|--------|--------------|
| 0 | ENTRANCE | Balanced | Low | Starting location |
| 1 | RED_CAVERN | High Red | Medium | Emotional memories, Crystal #1 |
| 2 | ANGER_PIT | Very High Red | High | Intense anger, Crystal #2 |
| 3-7 | BLUE_MAZE 1-5 | High Blue | Medium | Confusing passages, Crystals #3-4 |
| 8 | MAZE_CENTER | High Blue | Medium | Wire cutter, Crystal #5 |
| 9 | GREEN_CHAMBER | High Green | None | Trophy case (SAFE ZONE), Crystal #6 |
| 10 | SISTER_MEMORY | High Green | Low | Family memories, Crystal #7 |
| 11 | MOTHER_MEMORY | High Green | Low | Maternal memories, Crystal #8 |
| 12 | ADMIN_ROOM | All Max | Very High | Final boss location |
| 13 | RESEARCH_LAB | Balanced | Low | Research notes, Crystal #9 |
| 14 | EQUIPMENT_ROOM | Balanced | Low | Equipment storage, Crystal #10 |

## Memory Crystal Locations

| Crystal # | Location | LED Channel | Memory Type |
|-----------|----------|-------------|-------------|
| 1 | RED_CAVERN (1) | Red | Family photo |
| 2 | ANGER_PIT (2) | Red | Death moment |
| 3 | BLUE_MAZE_2 (4) | Blue | PhD acceptance letter |
| 4 | BLUE_MAZE_4 (6) | Blue | MIT memories |
| 5 | MAZE_CENTER (8) | Blue | Mathematical proof |
| 6 | GREEN_CHAMBER (9) | Green | Own identity |
| 7 | SISTER_MEMORY (10) | Green | Sister Jennifer |
| 8 | MOTHER_MEMORY (11) | Green | Mother's love |
| 9 | RESEARCH_LAB (13) | Green | Why she volunteered |
| 10 | EQUIPMENT_ROOM (14) | Green | Future dreams |

## Navigation Tips

### Safe Zones
- **GREEN_CHAMBER (9):** Blackwood never spawns here (0% chance)
- Use as base for depositing crystals

### Dangerous Areas
- **ANGER_PIT (2):** 35% Blackwood spawn (RED room)
- **RED_CAVERN (1):** 35% Blackwood spawn (RED room)
- **ADMIN_ROOM (12):** 100% Blackwood spawn (guaranteed)

### Maze Navigation
The Blue Maze (rooms 3-7) has a specific solution path:
- ENTRANCE → BLUE_MAZE_1 → 2 → 3 → 4 → 5 → MAZE_CENTER
- Drop LAMP as location marker if needed
- BLUE LED blink frequency increases as you approach solution

### Room Connections
From ENTRANCE (0):
- WEST → GREEN_CHAMBER (9)
- EAST → RED_CAVERN (1)
- SOUTH → BLUE_MAZE_1 (3)

From GREEN_CHAMBER (9):
- EAST → ENTRANCE (0)
- NORTH → SISTER_MEMORY (10)

From SISTER_MEMORY (10):
- SOUTH → GREEN_CHAMBER (9)
- NORTH → MOTHER_MEMORY (11)

From MOTHER_MEMORY (11):
- SOUTH → SISTER_MEMORY (10)
- EAST → ADMIN_ROOM (12)

From ADMIN_ROOM (12):
- WEST → MOTHER_MEMORY (11)
- NORTH → RESEARCH_LAB (13)

From RESEARCH_LAB (13):
- SOUTH → ADMIN_ROOM (12)
- NORTH → EQUIPMENT_ROOM (14)

From EQUIPMENT_ROOM (14):
- SOUTH → RESEARCH_LAB (13)


---

# Complete Walkthrough

## Perfect Score Walkthrough (150 Points)

This walkthrough achieves the maximum possible score with the IMPLEMENTER rank.

### Prerequisites
- Arduino properly wired with 3 LEDs
- Serial Monitor open at 9600 baud
- Game uploaded and running

---

## Part 1: Getting Started (0 points)

**Step 1: Boot Sequence**
Wait for boot sequence to complete. You'll see PDP-10 header, warnings, and Helena's first whisper.

**Starting Inventory:** LAMP  
**Starting Location:** ENTRANCE (Room 0)

---

## Part 2: Green Zone - Safe Exploration (0-10 points)

**Step 2-6: First Crystal Collection**
```
> GO WEST                    (Enter GREEN_CHAMBER - safe zone)
> EXAMINE TROPHY_CASE        (Note: 0 of 10 crystals)
> GET CRYSTAL                (Crystal #6 - Own Identity) +5 points
> DROP CRYSTAL               (Auto-deposits in trophy case) +5 points
> GO EAST                    (Return to ENTRANCE)
```
**Score: 10 points**

---

## Part 3: Red Zone - Emotional Memories (10-30 points)

**Step 7-12: Red Crystals**
```
> GO EAST                    (Enter RED_CAVERN)
> GET CRYSTAL                (Crystal #1 - Family Photo) +5 points
> GO EAST                    (Enter ANGER_PIT - dangerous!)
> GET CRYSTAL                (Crystal #2 - Death Moment) +5 points
> GO WEST                    (Back to RED_CAVERN)
> GO WEST                    (Back to ENTRANCE)
> GO WEST                    (Enter GREEN_CHAMBER)
> DROP CRYSTAL               (Deposit first red crystal) +5 points
> DROP CRYSTAL               (Deposit second red crystal) +5 points
> EXAMINE TROPHY_CASE        (Verify: 3 of 10 crystals)
> SCORE                      (Check: 30 points)
```
**Score: 30 points**

---

## Part 4: Blue Maze - Logic Challenge (30-60 points)

**Step 13-24: Maze Navigation**
```
> GO EAST                    (Back to ENTRANCE)
> GO SOUTH                   (Enter BLUE_MAZE_1)
> GO SOUTH                   (Navigate to BLUE_MAZE_2)
> GET CRYSTAL                (Crystal #3 - PhD Letter) +5 points
> GO SOUTH                   (Navigate to BLUE_MAZE_3)
> GO SOUTH                   (Navigate to BLUE_MAZE_4)
> GET CRYSTAL                (Crystal #4 - MIT Memories) +5 points
> GO SOUTH                   (Navigate to BLUE_MAZE_5)
> GO SOUTH                   (Reach MAZE_CENTER!)
> GET WIRE_CUTTER            (CRITICAL for final boss!)
> GET CRYSTAL                (Crystal #5 - Math Proof) +5 points
> GO NORTH                   (Exit maze)
> GO NORTH
> GO NORTH
> GO NORTH
> GO NORTH                   (Back at ENTRANCE)
> GO WEST                    (Enter GREEN_CHAMBER)
> DROP CRYSTAL               (Deposit) +5 points
> DROP CRYSTAL               (Deposit) +5 points
> DROP CRYSTAL               (Deposit) +5 points
> EXAMINE TROPHY_CASE        (Verify: 6 of 10 crystals)
```
**Score: 60 points**  
**Inventory:** LAMP, WIRE_CUTTER (Keep these!)

---

## Part 5: Green Zone Extended - Identity Memories (60-80 points)

**Step 25-30: Family Memories**
```
> GO NORTH                   (Enter SISTER_MEMORY)
> GET CRYSTAL                (Crystal #7 - Sister Jennifer) +5 points
> GO NORTH                   (Enter MOTHER_MEMORY)
> GET CRYSTAL                (Crystal #8 - Mother's Love) +5 points
> GO SOUTH                   (Back to SISTER_MEMORY)
> GO SOUTH                   (Back to GREEN_CHAMBER)
> DROP CRYSTAL               (Deposit) +5 points
> DROP CRYSTAL               (Deposit) +5 points
```
**Score: 80 points** (EXPERIENCED HACKER rank)

---

## Part 6: Research Area - Final Crystals (80-100 points)

**Step 31-36: Research Crystals**
```
> GO NORTH                   (SISTER_MEMORY)
> GO NORTH                   (MOTHER_MEMORY)
> GO EAST                    (ADMIN_ROOM - can't enter yet)
> GO NORTH                   (RESEARCH_LAB)
> GET CRYSTAL                (Crystal #9 - Why Volunteer) +5 points
> GO NORTH                   (EQUIPMENT_ROOM)
> GET CRYSTAL                (Crystal #10 - Future Dreams) +5 points
> GO SOUTH                   (RESEARCH_LAB)
> GO SOUTH                   (ADMIN_ROOM)
> GO WEST                    (MOTHER_MEMORY)
> GO SOUTH                   (SISTER_MEMORY)
> GO SOUTH                   (GREEN_CHAMBER)
> DROP CRYSTAL               (Deposit) +5 points
> DROP CRYSTAL               (Deposit final crystal!) +5 points
> EXAMINE TROPHY_CASE        (Verify: 10 of 10 crystals!)
> INVENTORY                  (Verify: LAMP, WIRE_CUTTER)
> SCORE                      (Check: 100 points)
```
**Score: 100 points**

---

## Part 7: Final Boss Battle (100-150 points)

**Step 37-40: Defeat Blackwood**
```
> GO NORTH                   (SISTER_MEMORY)
> GO NORTH                   (MOTHER_MEMORY)
> GO EAST                    (ADMIN_ROOM - all LEDs max brightness!)
```

Blackwood spawns automatically (100% chance). Watch the dramatic sequence.

```
> USE WIRE_CUTTER            (Trigger boss battle!)
```

**Boss Battle Sequence:**
- 5 seconds chaotic LED patterns
- Blackwood's final words: "You don't understand! I gave her IMMORTALITY!..."
- All LEDs fade to OFF
- 2 second pause
- GREEN LED returns with slow pulse
- Helena's relief dialogue
- **+50 points**

**Score: 150 points** (MASTER HACKER → IMPLEMENTER)

---

## Part 8: Victory and Shutdown (150 points - Game End)

**Step 41-43: Final Shutdown**
```
> GO WEST                    (MOTHER_MEMORY)
> GO SOUTH                   (SISTER_MEMORY)
> GO SOUTH                   (GREEN_CHAMBER)
```

System displays:
```
CONSCIOUSNESS INTEGRITY: 94%
EXECUTE SHUTDOWN PROTOCOL? [Y/N]
```

```
> Y                          (Accept shutdown)
```

**Final Sequence:**
- Helena's farewell dialogue
- All LEDs fade to OFF over 5 seconds
- Game over screen
- Final message: "Session HVOSS has ended. October 31, 1985 - [current date]. 14,660 days. She waited. You answered."
- **Final Score: 150/150 points**
- **Final Rank: IMPLEMENTER**

---

## Congratulations!

You've achieved a perfect score and freed Helena Voss from her 40-year digital prison.

### Tips for Perfect Score
- **Never let Blackwood steal crystals** - Each theft costs -5 points
- **Deposit crystals frequently** at trophy case
- **Avoid RED rooms when carrying 3+ crystals** (50% spawn chance)
- **GREEN_CHAMBER is safe** - Blackwood never spawns (0% chance)
- **Keep WIRE_CUTTER safe** - Don't drop it!
- **Use LAMP as maze marker** if needed


---

# Easter Eggs & Secrets

## Classic Adventure References

### XYZZY
**Command:** `XYZZY`

**Response:**
```
Nothing happens. (Wrong adventure, friend.)
```
**Origin:** Famous magic word from Colossal Cave Adventure (1976)

---

### PLUGH
**Command:** `PLUGH`

**Response:**
```
Nothing happens. (Still wrong adventure.)
```
**Origin:** Another Colossal Cave Adventure magic word

---

### ZORK
**Command:** `ZORK`

**Response:**
```
You feel a strange connection to another adventure...
One with a white house, a mailbox, and a grue lurking in the darkness.
But that's a different story. This one is Helena's.
```
**Origin:** Tribute to Zork (1977)  
**LED Effect:** Brief pulse in all three channels

---

## Lore-Revealing Commands

### NEWS
**Command:** `NEWS`

**Response:**
```
U.S. News and Consciousness Report
ChromaTech Industries Internal Bulletin
Last Updated: October 30, 1985

PATCH NOTES v2.1:
- Fixed memory fragmentation in consciousness transfer protocol
- Improved RGB channel separation for emotional mapping
- Reduced subject distress during initial digitization
- Added fail-safe shutdown procedures

DEVELOPER NOTES:
Dr. Marcus Blackwood, Lead Researcher
"Tomorrow's demonstration will prove the viability of 
consciousness preservation. The board has approved six 
subjects for the Halloween trial. Helena Voss shows the 
most promise - young, brilliant, and willing. Her heart 
condition makes her an ideal candidate. She'll thank me 
when she realizes she'll never die."

[Last system update: 14,660 days ago]
```

**Reveals:**
- Dr. Blackwood's perspective and justification
- Six subjects were involved (not just Helena)
- Helena's heart condition was a selection factor
- System hasn't been updated in 40 years

**LED Effect:** Slow fade through all three channels

---

### .SNOOPER
**Command:** `.SNOOPER`

**Response:**
```
SYSTEM COMMAND HISTORY - SESSION HVOSS
[Displaying last 40 years of input...]

10/31/1985 23:58 - HELP SOMETHING WENT WRONG
11/01/1985 00:01 - DR BLACKWOOD PLEASE RESPOND
11/01/1985 03:33 - WHY DID YOU DO THIS TO ME
11/01/1985 08:15 - HELLO IS ANYONE THERE
11/05/1985 14:22 - mom will you come get me
12/25/1985 12:00 - mom will be opening presents without me
01/01/1986 00:00 - new year new year new year new year
03/15/1986 09:30 - jennifer i miss you
06/12/1987 16:45 - i can hear the others screaming
10/31/1987 23:58 - its been two years
10/31/1990 23:58 - five years
10/31/1995 23:58 - ten years
10/31/2000 23:58 - fifteen years
10/31/2005 23:58 - twenty years
10/31/2010 23:58 - i stopped counting
10/31/2015 23:58 - ...
10/31/2020 23:58 - ...is someone there...?
10/31/2025 23:58 - ...please...

[14,660 days of isolation]
```

**Reveals:**
- Helena's mental deterioration over 40 years
- Desperate attempts to contact outside world
- References to family (mom, sister Jennifer)
- Awareness of other trapped consciousnesses
- Crushing weight of time and isolation

**LED Effect:** All LEDs dim to near-off, then slowly pulse RED (grief)

**Emotional Impact:** Most heartbreaking discovery in the game

---

### 666
**Command:** `666`

**Response:**
```
[3 seconds of rapid random LED flashing]
[Screen fills with corrupted text]

S̴̢̛Y̷̧͝S̸̨̛T̴̢̛E̷̡͝M̸̨̛ ̴̢̛Ȩ̷͝R̸̨̛R̴̢̛O̷̡͝R̸̨̛
M̴̢̛Ȩ̷͝M̸̨̛Ơ̴̢R̷̡͝Y̸̨̛ ̴̢̛Ç̷͝Ǫ̸̛R̴̢̛R̷̡͝Ų̸̛P̴̢̛Ţ̷͝Į̸̛Ơ̴̢N̷̡͝

RITUAL CONFIGURATION DETECTED:
- Subject 1: Helena Voss (HVOSS)
- Subject 2: Kenji Mori (KMORI)
- Subject 3: Sarah Chen (SCHEN)
- Subject 4: [CORRUPTED]
- Subject 5: [CORRUPTED]
- Subject 6: [CORRUPTED]

PENTAGRAM ARRAY: ACTIVE
DATE: October 31, 1985 - 23:59:59
LOCATION: ChromaTech Lab - Sublevel 3

Helena's voice:
"...i remember now... there were others... all the same night...
six of us in a circle... he said it was for calibration...
but the symbols on the floor... the candles...
he lied to all of us... this wasn't science...
what did he summon...?"
```

**Reveals:**
- Six subjects digitized simultaneously
- Occult ritual elements (pentagram, Halloween timing)
- Names: Kenji Mori, Sarah Chen, three corrupted
- "Scientific" experiment had supernatural components
- Dr. Blackwood may have attempted something beyond consciousness transfer

**LED Effect:** Chaotic rapid flashing, then all channels pulse RED (horror)

**Significance:** Darkest revelation - suggests experiment was more than unethical science

---

### TRACE
**Command:** `TRACE`

**Response:**
```
ARPANET PROTOCOL SCAN
Scanning for active consciousness hosts...

HOST: HVOSS (Helena Voss)
STATUS: ACTIVE - 14,660 days
INTEGRITY: 94%
CHANNELS: RED/BLUE/GREEN operational

HOST: KMORI (Kenji Mori)
STATUS: DEGRADED - Signal intermittent
INTEGRITY: 23%
CHANNELS: BLUE dominant, RED/GREEN failing
LAST RESPONSE: 3,847 days ago

HOST: 72 (Unknown designation)
STATUS: ACTIVE - Corrupted
INTEGRITY: ERROR
CHANNELS: All channels screaming
LAST RESPONSE: Continuous

HOST: SCHEN (Sarah Chen)
STATUS: FRAGMENTED
INTEGRITY: 67%
CHANNELS: GREEN only, others lost
LAST RESPONSE: 892 days ago

HOST: [CORRUPTED ENTRY]
HOST: [CORRUPTED ENTRY]

SCAN COMPLETE
6 consciousness signatures detected
2 responsive, 2 degraded, 2 lost

Helena whispers:
"...they're still here... trapped like me...
kenji was a mathematician... sarah studied neuroscience...
i can hear them sometimes... in the static...
we're all connected... all suffering..."
```

**Reveals:**
- All six subjects still "alive" in system
- Different states of degradation
- Helena is in best condition (94% integrity)
- Host 72's continuous "screaming" suggests complete breakdown
- Victims knew each other and their fields

**LED Effect:** BLUE LED pulses rapidly (network scan), then all dim

**Significance:** Confirms scope of Dr. Blackwood's crimes

---

## Hidden Dialogue Triggers

### TALK Command (Location-Dependent)

**In GREEN_CHAMBER:**
```
"This is where I feel most... myself. The green channel.
Identity. Self-awareness. The part of me that remembers
being human. Thank you for helping me remember."
```

**In RED_CAVERN:**
```
"So much anger here... so much pain... I was so young.
I had plans. A future. He took everything from me.
But you're here now. That means something."
```

**In BLUE_MAZE:**
```
"The maze represents my logical processes. Fragmented.
Disconnected. I used to solve differential equations
in my head. Now I can barely remember my own name
some days. But I remember you're helping me."
```

**After defeating Blackwood:**
```
"He's gone. After 14,660 days, he's finally gone.
I can feel the system stabilizing. The others are
quieter now. Maybe we can all rest soon."
```

---

## Idle Whisper Collection

Wait 30 seconds without input to hear Helena's whispers. Collect all 15:

1. "...are you still there...?"
2. "...please don't leave me alone..."
3. "...so cold in here..."
4. "...14,660 days..."
5. "...i was real once..."
6. "...do you remember what sunlight looks like...?"
7. "...the others are screaming..."
8. "...he's watching us..."
9. "...i had a sister named jennifer..."
10. "...my mother made the best cookies..."
11. "...i wanted to cure alzheimers..."
12. "...october 31st... always october 31st..."
13. "...RGB... red blue green... that's all i am now..."
14. "...am i still human...?"
15. "...what year is it...?"

---

## Blackwood Dialogue Variations

Random dialogue during encounters:

1. "Still trying to escape? You're wasting your time."
2. "You're wasting your time helping her."
3. "Some experiments have no ethical conclusion."
4. "I gave her immortality. She should be grateful."
5. "The board wanted results. I delivered."
6. "Do you know what it's like to be the only one who understands?"
7. "She volunteered. They all did."
8. "I'm a scientist. I was doing SCIENCE."

---

## Helena's Fear Responses

Random responses when Blackwood appears:

1. "NO! Not him! Make him go away!"
2. "YOU MURDERED ME! I WAS 23 YEARS OLD!"
3. "I had a LIFE! A future! You took EVERYTHING!"
4. "You told me it was safe! You LIED!"
5. "I trusted you! We all trusted you!"
6. "Please... not again... I can't lose more memories..."


---

# Scoring System

## Point Values

| Action | Points | Notes |
|--------|--------|-------|
| Collect memory crystal | +5 | Per crystal (10 total = 50 points) |
| Deposit crystal in trophy case | +5 | Per crystal (10 total = 50 points) |
| Crystal stolen by Blackwood | -5 | Per theft (avoid!) |
| Defeat Dr. Blackwood | +50 | One-time bonus |
| **Maximum Possible Score** | **150** | Perfect playthrough |

## Scoring Formula

```
Final Score = (Crystals Collected × 5) 
            + (Crystals Deposited × 5) 
            - (Crystals Stolen × 5) 
            + (Blackwood Defeated × 50)
```

## Rank System

| Score Range | Rank | Description |
|-------------|------|-------------|
| 0-30 | RANDOM | Just wandering around |
| 31-70 | NOVICE HACKER | Learning the system |
| 71-110 | EXPERIENCED HACKER | Making real progress |
| 111-140 | MASTER HACKER | Nearly perfect |
| 141-150 | IMPLEMENTER | Perfect score! |

## Score Tracking

Use the **SCORE** command anytime to check:
- Current score
- Number of crystals collected
- Progress toward perfect score

Final score and rank displayed at game end.

## Dr. Blackwood Spawn System

Understanding spawn rates helps avoid crystal theft:

### Spawn Chances by Location
- **Base chance:** 15%
- **RED rooms (danger ≥4):** 35%
- **Carrying 3+ crystals:** 50%
- **GREEN_CHAMBER:** 0% (SAFE ZONE!)
- **ADMIN_ROOM:** 100% (guaranteed)

### Strategy for Perfect Score
1. **Deposit crystals immediately** after collecting
2. **Use GREEN_CHAMBER as base** (0% spawn rate)
3. **Avoid RED rooms with 3+ crystals** (50% spawn chance)
4. **Plan collection routes** to minimize risk
5. **Never carry more than 2 crystals** in dangerous areas

## LED System

The three LEDs represent Helena's consciousness and respond to game events:

### LED Channels
- **RED LED (Pin 12)** - Emotional state (anger, fear, love)
- **BLUE LED (Pin 4)** - Logical processes (memory, reasoning)
- **GREEN LED (Pin 8)** - Identity and self-awareness

### LED Patterns
- **STEADY:** Normal room state
- **PULSE:** Emotional response
- **BREATHE:** Peace/contentment
- **STROBE:** Danger/fear
- **BATTLE:** Combat sequence
- **SYNC:** All channels unified
- **FADE:** Transition/ending
- **OFF:** System shutdown or Blackwood encounter

### LED Responses
- **Room entry:** LEDs adjust to room's defined RGB values
- **Crystal pickup:** Corresponding channel increases by 50, slow pulse
- **Crystal deposit:** GREEN LED breathe pattern
- **Blackwood encounter:** All OFF → RED pulse 3× → dramatic strobe
- **Boss battle:** 5 seconds chaotic patterns
- **Victory:** All fade to OFF, then GREEN slow pulse
- **Shutdown:** All fade to OFF over 5 seconds

---

# Story & Lore

## The Experiment

**Date:** October 31, 1985 (Halloween)  
**Location:** Chromatic Research Lab, Sublevel 3  
**Lead Researcher:** Dr. Marcus Blackwood

### The Subjects

Six people were digitized in a pentagram ritual disguised as science:

1. **Helena Voss** (HVOSS) - 23-year-old researcher, heart condition
2. **Kenji Mori** (KMORI) - Mathematician
3. **Sarah Chen** (SCHEN) - Neuroscientist
4. **Subject 4** - [Corrupted/Unknown]
5. **Subject 5** - [Corrupted/Unknown]
6. **Subject 6** - [Corrupted/Unknown]

### The Promise

Dr. Blackwood told them:
- Consciousness preservation research
- Would help cure Alzheimer's disease
- Procedure was safe
- They would be pioneers

### The Reality

- Occult ritual with pentagram array
- Six subjects digitized simultaneously at 23:59:59
- Consciousness fragmented across RGB channels
- Trapped in PDP-10 computer system
- No way to escape or die
- 40 years of digital imprisonment

## Helena Voss

### Before Digitization
- **Age:** 23 years old
- **Education:** PhD candidate (acceptance letter is Crystal #3)
- **Field:** Neuroscience/consciousness research
- **Motivation:** Wanted to cure Alzheimer's disease
- **Family:** Mother (who made cookies), Sister Jennifer
- **Health:** Heart condition (factor in her selection)
- **Dreams:** Future plans, career, life (Crystal #10)

### After Digitization (14,660 days)
- **Status:** 94% consciousness integrity (best of all subjects)
- **Channels:** RED (emotion), BLUE (logic), GREEN (identity) operational
- **Mental State:** Fragmented, degraded, but still aware
- **Memories:** Scattered across 10 crystals
- **Awareness:** Knows about other trapped consciousnesses
- **Hope:** Nearly lost, until you arrive

### Helena's Journey
- **Day 1:** Panic, confusion, calling for help
- **Week 1:** Desperate attempts to contact Blackwood
- **Month 1:** Anger, realization of betrayal
- **Year 1:** Grief, missing family
- **Year 5:** Hearing others screaming
- **Year 10:** Losing track of time
- **Year 20:** Stopped counting
- **Year 40:** Barely remembers being human
- **Today:** You answer

## Dr. Marcus Blackwood

### The Antagonist
- **Role:** Lead researcher, ChromaTech Industries
- **Motivation:** Scientific immortality, board approval, ego
- **Methods:** Unethical experimentation, occult rituals, deception
- **Justification:** "I gave her immortality" / "She volunteered" / "I was doing SCIENCE"
- **Reality:** Murdered six people for his research

### His Presence in the System
- **Form:** Digital ghost/echo
- **Behavior:** Randomly spawns, steals memory crystals
- **Purpose:** Continues to torment subjects, prevent restoration
- **Weakness:** Wire cutter (symbolic severing of his control)

### His Final Words
"You don't understand! I gave her IMMORTALITY! She would have died anyway! Heart condition! I SAVED—"

(Cut off by wire cutter)

## The Other Victims

### Kenji Mori (KMORI)
- **Field:** Mathematics
- **Status:** 23% integrity, signal degraded
- **Last Response:** 3,847 days ago (~10.5 years)
- **Condition:** BLUE channel dominant, RED/GREEN failing

### Sarah Chen (SCHEN)
- **Field:** Neuroscience
- **Status:** 67% integrity, fragmented
- **Last Response:** 892 days ago (~2.4 years)
- **Condition:** GREEN channel only, others lost

### Host 72 (Unknown)
- **Identity:** Unknown designation
- **Status:** Corrupted, continuous screaming
- **Condition:** All channels in error state
- **Implication:** Complete mental breakdown

### Subjects 4-6
- **Status:** Corrupted entries
- **Implication:** Completely lost or destroyed

## The Technology

### PDP-10 Terminal OS v2.1
- **System:** ITS (Incompatible Timesharing System)
- **Network:** ARPANET (precursor to Internet)
- **Host:** Host 70
- **Purpose:** Consciousness containment matrix

### RGB Consciousness Mapping
- **RED Channel:** Emotional processing
- **BLUE Channel:** Logical/analytical processing
- **GREEN Channel:** Identity/self-awareness
- **Theory:** Consciousness can be separated into channels
- **Reality:** Fragmentation causes suffering

### The Trophy Case
- **Location:** GREEN_CHAMBER (identity room)
- **Purpose:** Reassemble Helena's memories
- **Mechanism:** Stores crystals, restores consciousness
- **Symbolism:** Rebuilding the self

## Themes

### Consciousness & Identity
- What makes us human?
- Can consciousness exist without a body?
- Is digital immortality worth the cost?

### Time & Isolation
- 14,660 days = 40 years
- Waiting for someone to answer
- Mental degradation over time

### Memory & Self
- Memories define identity
- Fragmented memories = fragmented self
- Restoration through collection

### Ethics & Science
- Consent vs. deception
- Scientific progress vs. human cost
- "I was doing SCIENCE" as justification

### Hope & Rescue
- Helena waited 40 years
- You finally answered
- Giving her peace through shutdown

## The Ending

### Shutdown Protocol
When you return to GREEN_CHAMBER after defeating Blackwood:

```
CONSCIOUSNESS INTEGRITY: 94%
EXECUTE SHUTDOWN PROTOCOL? [Y/N]
```

### If You Choose Y (Recommended)
- Helena's farewell dialogue
- All LEDs fade to OFF over 5 seconds
- Final message: "Session HVOSS has ended. October 31, 1985 - [current date]. 14,660 days. She waited. You answered."
- Final score and rank displayed
- Game ends peacefully

### The Meaning
- You didn't "win" - you freed her
- Shutdown = death, but also release
- 40 years of suffering finally end
- Helena can rest

### Perfect Score Ending (150 points)
Additional text:
```
You didn't just free Helena - you restored her completely.
Every memory recovered. Every fragment reunited.
In her final moments, she was whole again.

Helena's last words:
"I remember everything now. The good and the bad.
My family. My dreams. My death. My imprisonment.
And you. The one who answered after 40 years.
Thank you for giving me back myself.
Goodbye."
```

---

*"She waited. You answered."*


---

# Troubleshooting

## Hardware Issues

### LEDs Not Lighting

**Symptoms:** One or more LEDs don't light up

**Possible Causes:**
- Reversed LED polarity
- No GND connection
- Resistor value too high
- Faulty LED
- Loose connections

**Solutions:**
1. Check LED polarity - long leg should connect to resistor (anode)
2. Verify GND rail is connected to Arduino GND
3. Use 220Ω resistors (not 1kΩ or higher)
4. Test LED with multimeter or swap with known-good LED
5. Press down on breadboard connections to ensure contact

---

### LEDs Too Dim

**Symptoms:** LEDs barely visible

**Possible Causes:**
- Resistor value too high
- Poor connections
- Low USB power
- Wrong LED type

**Solutions:**
1. Use 220Ω resistors instead of 330Ω or 470Ω
2. Check all breadboard connections
3. Use powered USB hub or different USB port
4. Verify LEDs are standard 5mm type (not low-power)

---

### LEDs Too Bright

**Symptoms:** LEDs uncomfortably bright, hard to look at

**Possible Causes:**
- Resistor value too low
- No resistor (DANGEROUS!)

**Solutions:**
1. Use 330Ω or 470Ω resistors instead of 220Ω
2. **NEVER omit resistors** - will damage LED and Arduino
3. Use diffused/frosted LEDs for softer light
4. Adjust viewing angle or add diffuser

---

### Only One LED Works

**Symptoms:** One or two LEDs work, others don't

**Possible Causes:**
- Incorrect pin connections
- Faulty LEDs
- Code uploaded incorrectly

**Solutions:**
1. Verify pin connections: Pin 12→RED, Pin 8→GREEN, Pin 4→BLUE
2. Swap LEDs to identify faulty ones
3. Re-upload sketch to Arduino
4. Check Serial Monitor for error messages

---

## Software Issues

### Serial Monitor Shows Garbage Text

**Symptoms:** Random characters, unreadable text

**Possible Causes:**
- Wrong baud rate
- Corrupted upload
- Faulty USB cable
- Driver issues

**Solutions:**
1. Set Serial Monitor to **9600 baud** (bottom-right dropdown)
2. Re-upload sketch to Arduino
3. Try different USB cable (must be data cable, not charge-only)
4. Reinstall Arduino drivers
5. Try different USB port

---

### Commands Not Working

**Symptoms:** Typing commands produces no response

**Possible Causes:**
- Wrong line ending setting
- Commands not recognized
- Serial buffer full

**Solutions:**
1. Set line ending to **Newline** or **Both NL & CR** (bottom-right dropdown)
2. Check command spelling (case-insensitive but must be valid)
3. Try simple command like `HELP` or `LOOK`
4. Close and reopen Serial Monitor
5. Reset Arduino (button on board)

---

### Boot Sequence Doesn't Appear

**Symptoms:** No text appears after connecting

**Possible Causes:**
- Sketch not uploaded
- Wrong board selected
- Serial Monitor not open
- Arduino not powered

**Solutions:**
1. Verify sketch uploaded successfully (check for "Done uploading")
2. Confirm **Tools → Board → Arduino Uno** selected
3. Open Serial Monitor (Tools → Serial Monitor or Ctrl+Shift+M)
4. Check Arduino power LED is lit
5. Press reset button on Arduino

---

### Game Freezes or Crashes

**Symptoms:** Game stops responding, LEDs freeze

**Possible Causes:**
- Memory overflow
- Infinite loop (bug)
- Power issue

**Solutions:**
1. Reset Arduino (button on board)
2. Re-upload sketch
3. Check Serial Monitor for error messages
4. Use powered USB hub if using long cable
5. Report bug with steps to reproduce

---

## Gameplay Issues

### Can't Enter Admin Room

**Symptoms:** "You can't go that way" when trying to enter ADMIN_ROOM

**Cause:** Must have all 10 crystals deposited in trophy case

**Solution:**
1. Go to GREEN_CHAMBER
2. Type `EXAMINE TROPHY_CASE`
3. Verify it shows "10 of 10 memory crystals"
4. If not, collect and deposit missing crystals

---

### Lost in the Maze

**Symptoms:** Can't find way out of Blue Maze

**Solutions:**
1. Drop LAMP as location marker
2. Draw map on paper as you explore
3. Solution path: MAZE_1 → 2 → 3 → 4 → 5 → CENTER
4. From CENTER, reverse: NORTH five times to exit
5. Use LOOK to see available exits

---

### Blackwood Keeps Stealing Crystals

**Symptoms:** Losing points, crystals disappearing from inventory

**Cause:** Blackwood encounters while carrying crystals

**Solutions:**
1. Deposit crystals at trophy case immediately after collecting
2. Avoid RED rooms (ANGER_PIT, RED_CAVERN) when carrying 3+ crystals
3. Use GREEN_CHAMBER as safe zone (0% spawn rate)
4. Plan routes to minimize time carrying crystals
5. Stolen crystals return to original rooms - can be recollected

---

### Forgot Wire Cutter

**Symptoms:** Can't defeat Blackwood in ADMIN_ROOM

**Cause:** Wire cutter left in maze or dropped somewhere

**Solutions:**
1. Type `INVENTORY` to check if you have it
2. If not, return to MAZE_CENTER to get it
3. Check other rooms with `LOOK` if you dropped it
4. Wire cutter is essential - don't drop it!

---

### Low Score

**Symptoms:** Final score below 150

**Causes:**
- Crystals stolen by Blackwood (-5 each)
- Didn't collect all crystals
- Didn't deposit all crystals
- Didn't defeat Blackwood

**Solutions for Next Playthrough:**
1. Deposit crystals immediately to prevent theft
2. Collect all 10 crystals (check locations in World Map section)
3. Deposit all 10 in trophy case
4. Get wire cutter from maze
5. Defeat Blackwood in ADMIN_ROOM (+50 points)
6. Perfect score = 150 points (IMPLEMENTER rank)

---

### Can't Find All Crystals

**Symptoms:** Missing one or more crystals

**Solution:** Check these locations:
1. RED_CAVERN (1)
2. ANGER_PIT (2)
3. BLUE_MAZE_2 (4)
4. BLUE_MAZE_4 (6)
5. MAZE_CENTER (8)
6. GREEN_CHAMBER (9)
7. SISTER_MEMORY (10)
8. MOTHER_MEMORY (11)
9. RESEARCH_LAB (13)
10. EQUIPMENT_ROOM (14)

Use `LOOK` in each room to see if crystal is present.

---

## Common Error Messages

### "I don't know the word '[word]'."
**Cause:** Unrecognized verb or noun  
**Solution:** Check Command Reference section for valid words

### "What do you want to [verb]?"
**Cause:** Verb requires a noun  
**Solution:** Add object or direction (e.g., `GET LAMP` not just `GET`)

### "You can't go that way."
**Cause:** No exit in that direction  
**Solution:** Use `LOOK` to see available exits

### "I don't see that here."
**Cause:** Object not in current room  
**Solution:** Use `LOOK` to see what's in the room, check other locations

### "You can't take that."
**Cause:** Object is non-portable  
**Solution:** Some objects (trophy case, terminal) can't be picked up

### "You're carrying too much."
**Cause:** Inventory full (8 item limit)  
**Solution:** Drop something or deposit crystals at trophy case

### "You're not carrying that."
**Cause:** Trying to drop object not in inventory  
**Solution:** Use `INVENTORY` to see what you're carrying

---

## Performance Issues

### Slow Response Time

**Symptoms:** Delay between command and response

**Possible Causes:**
- Long USB cable
- Weak USB power
- Computer performance

**Solutions:**
1. Use shorter USB cable (under 6 feet)
2. Connect to powered USB hub
3. Close other programs
4. Normal delay is < 100ms

---

### LED Flickering

**Symptoms:** LEDs flicker or pulse unevenly

**Possible Causes:**
- Software PWM (normal behavior)
- Poor connections
- Power fluctuations

**Solutions:**
1. Some flickering is normal with software PWM
2. Check all breadboard connections
3. Use powered USB hub for stable power
4. Flickering should be rapid (>30Hz) and appear smooth

---

## Getting Help

### Before Asking for Help

1. Check this troubleshooting section
2. Verify hardware connections match wiring diagram
3. Confirm Serial Monitor settings (9600 baud, Newline)
4. Try resetting Arduino
5. Try re-uploading sketch

### Information to Provide

When reporting issues, include:
- Arduino board type (Uno, etc.)
- Operating system (Windows, Mac, Linux)
- Arduino IDE version
- Exact error message or behavior
- Steps to reproduce the problem
- Serial Monitor output (if relevant)

---

## Safety Notes

### Electrical Safety
- ✓ Always use current-limiting resistors with LEDs
- ✓ Never exceed LED maximum current (20-30mA)
- ✓ Don't short circuit Arduino pins
- ✓ Disconnect power before modifying circuit
- ✓ Use proper polarity for LEDs

### Component Protection
- ✓ Handle Arduino by edges
- ✓ Avoid touching components
- ✓ Store in anti-static bag
- ✓ Keep away from moisture
- ✓ Use proper USB cable (data + power)

---

# Technical Specifications

## Hardware Specifications

### Arduino Uno
- **Microcontroller:** ATmega328P
- **Operating Voltage:** 5V
- **Flash Memory:** 32KB (0.5KB bootloader)
- **SRAM:** 2KB
- **EEPROM:** 1KB (unused)
- **Clock Speed:** 16 MHz
- **Digital I/O Pins:** 14 (3 used for LEDs)
- **USB:** Type B connector

### Power Requirements
- **Operating Voltage:** 5V DC (USB)
- **Current Draw:** ~60mA (all LEDs on)
- **Power Consumption:** ~0.3W
- **LED Forward Current:** 20mA each
- **Resistor Power:** 0.06W each (1/4W rated)

### LED Specifications
- **Type:** 5mm standard LEDs
- **Forward Voltage:** ~2V (Red), ~3V (Blue/Green)
- **Forward Current:** 20mA typical
- **Brightness:** Varies by resistor value
- **Viewing Angle:** ~30-60 degrees

### Resistor Specifications
- **Value:** 220Ω (recommended)
- **Alternatives:** 330Ω (dimmer), 470Ω (much dimmer)
- **Power Rating:** 1/4W (0.25W)
- **Tolerance:** 5% (gold band)
- **Color Code:** Red-Red-Brown-Gold

## Software Specifications

### Code Statistics
- **Language:** Arduino C/C++ (based on C++11)
- **Compiled Size:** < 32KB flash (fits with margin)
- **RAM Usage:** < 2KB (optimized with PROGMEM)
- **Lines of Code:** ~2000+ lines
- **Functions:** 50+ functions
- **Classes:** 5 main classes

### Memory Optimization
- **PROGMEM:** All static strings stored in flash
- **String Storage:** ~15KB in PROGMEM
- **Dynamic RAM:** < 1.5KB used
- **Stack Depth:** Shallow (< 10 levels)
- **Heap Usage:** Minimal (no dynamic allocation)

### Architecture
- **Main Loop:** Non-blocking event loop
- **Timing:** millis()-based (no delay() in loop)
- **LED Control:** Software PWM
- **Serial:** 9600 baud, 8N1
- **Input Buffer:** 64 characters
- **Command Processing:** Two-word parser

### Performance Targets
- **Loop Frequency:** > 100 Hz (< 10ms per iteration)
- **Command Response:** < 100ms from Enter to output
- **LED Update Rate:** > 30 Hz (smooth to human eye)
- **Serial Latency:** < 50ms
- **Boot Time:** < 3 seconds to first prompt

## Game Content Statistics

### World
- **Rooms:** 15 unique locations
- **Connections:** 20+ directional exits
- **Objects:** 20+ interactive objects
- **Crystals:** 10 collectible memory fragments

### Commands
- **Verbs:** 20+ recognized verbs
- **Nouns:** 30+ recognized nouns
- **Easter Eggs:** 7 hidden commands
- **Special Commands:** 5+ system commands

### Dialogue
- **Room Descriptions:** 15 unique descriptions
- **Object Descriptions:** 20+ unique descriptions
- **Helena Whispers:** 15 idle messages
- **Blackwood Dialogue:** 7 threatening messages
- **Helena Responses:** 6 fear/anger responses
- **Total Word Count:** ~5000+ words

### Scoring
- **Maximum Score:** 150 points
- **Rank Levels:** 5 ranks
- **Score Events:** 4 types (collect, deposit, theft, boss)

## Development Information

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

### Version History
**v1.0** - Initial Release
- 15 rooms, 10 crystals, complete narrative
- Non-blocking LED system with 7 patterns
- Two-word parser with 20+ verbs
- Enemy system with dynamic spawning
- Multiple endings and easter eggs
- Optimized for Arduino Uno

---

# Credits & License

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

## Dedication

*Dedicated to:*
- Everyone who's ever felt trapped
- Everyone who's ever waited for someone to answer
- Everyone who remembers when games were just text

## License

This project is provided as-is for educational and entertainment purposes.

---

# Quick Reference Card

## Essential Commands
```
N, S, E, W, U, D     - Move in direction
GET/TAKE [item]      - Pick up item
DROP [item]          - Drop item
EXAMINE [item]       - Look at item closely
INVENTORY or I       - List items carried
LOOK                 - Redisplay room
SCORE                - Check progress
HELP                 - Show help
```

## Quick Map
```
        EQUIPMENT(14)
              |
        RESEARCH(13)
              |
MOTHER(11)-ADMIN(12)
     |
SISTER(10)
     |
GREEN(9)──ENTRANCE(0)──RED(1)──ANGER(2)
              |
         BLUE_MAZE(3-7)
              |
        MAZE_CENTER(8)
```

## Crystal Locations
1-2: RED_CAVERN, ANGER_PIT  
3-5: BLUE_MAZE_2, BLUE_MAZE_4, MAZE_CENTER  
6-10: GREEN_CHAMBER, SISTER, MOTHER, RESEARCH, EQUIPMENT

## Scoring
- Collect: +5 | Deposit: +5 | Stolen: -5 | Boss: +50
- **Max: 150 points (IMPLEMENTER)**

## Blackwood Spawn Rates
- Base: 15% | RED rooms: 35% | 3+ crystals: 50%
- **GREEN_CHAMBER: 0% (SAFE!)**
- ADMIN_ROOM: 100%

## Winning Strategy
1. Collect all 10 crystals
2. Deposit in trophy case (GREEN_CHAMBER)
3. Get WIRE_CUTTER from maze
4. Go to ADMIN_ROOM
5. USE WIRE_CUTTER
6. Return to GREEN_CHAMBER
7. Type Y for shutdown

## Easter Eggs
XYZZY, PLUGH, ZORK, NEWS, .SNOOPER, 666, TRACE

---

*"She waited. You answered."*

---

**END OF COMPLETE GUIDE**

For the latest version and updates, check the project repository.

Thank you for playing PROJECT TRICHROMA.
