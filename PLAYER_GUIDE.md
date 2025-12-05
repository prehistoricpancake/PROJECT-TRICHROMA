# PROJECT TRICHROMA - Player Guide

## Table of Contents
1. [Hardware Setup](#hardware-setup)
2. [Command Reference](#command-reference)
3. [World Map](#world-map)
4. [Walkthrough](#walkthrough)
5. [Easter Eggs](#easter-eggs)
6. [Scoring System](#scoring-system)

---

## Hardware Setup

### Required Components
- Arduino Uno board
- 3 LEDs (Red, Blue, Green)
- 3 × 220Ω resistors
- Breadboard and jumper wires
- USB cable for computer connection

### Wiring Instructions

```
Arduino Uno Pin Connections:
┌─────────────────────────────────────┐
│ Pin 12 ──[220Ω]── RED LED ── GND   │
│ Pin 4  ──[220Ω]── BLUE LED ── GND  │
│ Pin 8  ──[220Ω]── GREEN LED ── GND │
└─────────────────────────────────────┘

LED Polarity:
- Long leg (anode) connects to resistor
- Short leg (cathode) connects to GND
```

### Software Setup
1. Upload `project_trichroma.ino` to Arduino Uno
2. Open Serial Monitor (Tools → Serial Monitor)
3. Set baud rate to **9600**
4. Set line ending to **Newline** or **Both NL & CR**
5. Wait for boot sequence to complete

---

## Command Reference

### Movement Commands
| Command | Shortcut | Description |
|---------|----------|-------------|
| GO NORTH | N | Move north |
| GO SOUTH | S | Move south |
| GO EAST | E | Move east |
| GO WEST | W | Move west |
| GO UP | U | Move up |
| GO DOWN | D | Move down |

### Object Manipulation
| Command | Alternate | Description |
|---------|-----------|-------------|
| GET [object] | TAKE [object] | Pick up an object |
| DROP [object] | - | Drop an object from inventory |
| EXAMINE [object] | - | Look closely at an object |
| USE [object] | - | Use an item (context-specific) |

### Information Commands
| Command | Shortcut | Description |
|---------|----------|-------------|
| LOOK | - | Redisplay current room description |
| INVENTORY | I | List items you're carrying |
| SCORE | - | Display current score and progress |
| HELP | - | Display help information |

### Special Commands
| Command | Description |
|---------|-------------|
| TALK | Speak to Helena |
| TRACE | Display ARPANET network scan |
| QUIT | Exit the game |

### Recognized Nouns
**Directions:** NORTH, SOUTH, EAST, WEST, UP, DOWN

**Objects:**
- LAMP (starting item)
- CRYSTAL (10 memory crystals scattered throughout)
- WIRE_CUTTER (found in maze center)
- TROPHY_CASE (in Green Chamber)
- TERMINAL (in various rooms)
- NOTES (research documentation)

### Parser Notes
- Commands are **case-insensitive** (GET LAMP = get lamp)
- Articles (THE, A, AN) are automatically ignored
- Only the first two words are processed
- Empty commands are ignored

---

## World Map

### Complete Room Layout

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

### Room Details

| ID | Room Name | LED Colors | Danger | Key Features |
|----|-----------|------------|--------|--------------|
| 0 | ENTRANCE | Balanced | Low | Starting location |
| 1 | RED_CAVERN | High Red | Medium | Emotional memories |
| 2 | ANGER_PIT | Very High Red | High | Intense anger |
| 3-7 | BLUE_MAZE 1-5 | High Blue | Medium | Confusing passages |
| 8 | MAZE_CENTER | High Blue | Medium | Wire cutter location |
| 9 | GREEN_CHAMBER | High Green | None | Trophy case (safe zone) |
| 10 | SISTER_MEMORY | High Green | Low | Family memories |
| 11 | MOTHER_MEMORY | High Green | Low | Maternal memories |
| 12 | ADMIN_ROOM | All Max | Very High | Final boss location |
| 13 | RESEARCH_LAB | Balanced | Low | Research notes |
| 14 | EQUIPMENT_ROOM | Balanced | Low | Equipment storage |

### Memory Crystal Locations

| Crystal # | Location | LED Channel | Memory Type |
|-----------|----------|-------------|-------------|
| 1 | RED_CAVERN | Red | Family photo |
| 2 | ANGER_PIT | Red | Death moment |
| 3 | BLUE_MAZE_2 | Blue | PhD acceptance letter |
| 4 | BLUE_MAZE_4 | Blue | MIT memories |
| 5 | MAZE_CENTER | Blue | Mathematical proof |
| 6 | GREEN_CHAMBER | Green | Own identity |
| 7 | SISTER_MEMORY | Green | Sister Jennifer |
| 8 | MOTHER_MEMORY | Green | Mother's love |
| 9 | RESEARCH_LAB | Green | Why she volunteered |
| 10 | EQUIPMENT_ROOM | Green | Future dreams |

---

## Walkthrough

### Optimal Solution Path (150 Points)

#### Phase 1: Initial Exploration (0-50 points)
1. **Start at ENTRANCE** - Read the room description carefully
2. **GO WEST** to GREEN_CHAMBER (safe zone)
3. **EXAMINE TROPHY_CASE** - This is where you'll deposit crystals
4. **GET CRYSTAL** (Crystal #6 - Own Identity) - +5 points
5. **DROP CRYSTAL** - Automatically deposits in trophy case - +5 points
6. **GO EAST** back to ENTRANCE

#### Phase 2: Red Zone Exploration (10-30 points)
7. **GO EAST** to RED_CAVERN
8. **GET CRYSTAL** (Crystal #1 - Family Photo) - +5 points
9. **GO EAST** to ANGER_PIT
10. **GET CRYSTAL** (Crystal #2 - Death Moment) - +5 points
11. **GO WEST** twice to return to ENTRANCE
12. **GO WEST** to GREEN_CHAMBER
13. **DROP CRYSTAL** (repeat for both crystals) - +10 points

#### Phase 3: Blue Maze Navigation (30-60 points)
14. **GO SOUTH** from ENTRANCE to BLUE_MAZE_1
15. Navigate the maze sequence:
    - BLUE_MAZE_1 → BLUE_MAZE_2 (GET CRYSTAL #3) - +5 points
    - BLUE_MAZE_2 → BLUE_MAZE_3
    - BLUE_MAZE_3 → BLUE_MAZE_4 (GET CRYSTAL #4) - +5 points
    - BLUE_MAZE_4 → BLUE_MAZE_5
    - BLUE_MAZE_5 → MAZE_CENTER
16. **GET WIRE_CUTTER** at MAZE_CENTER (ESSENTIAL for final boss!)
17. **GET CRYSTAL** (Crystal #5 - Math Proof) - +5 points
18. Navigate back to ENTRANCE
19. Return to GREEN_CHAMBER and deposit all blue crystals - +15 points

#### Phase 4: Green Zone Exploration (60-90 points)
20. From GREEN_CHAMBER, **GO NORTH** to SISTER_MEMORY
21. **GET CRYSTAL** (Crystal #7 - Sister Jennifer) - +5 points
22. **GO NORTH** to MOTHER_MEMORY
23. **GET CRYSTAL** (Crystal #8 - Mother's Love) - +5 points
24. **GO EAST** to ADMIN_ROOM (note: requires 10 crystals, skip for now)
25. **GO WEST** back to MOTHER_MEMORY
26. **GO SOUTH** twice to GREEN_CHAMBER
27. **DROP CRYSTAL** (repeat for both) - +10 points

#### Phase 5: Research Area (90-110 points)
28. From MOTHER_MEMORY, **GO EAST** to ADMIN_ROOM
29. **GO NORTH** to RESEARCH_LAB
30. **GET CRYSTAL** (Crystal #9 - Why Volunteer) - +5 points
31. **GO NORTH** to EQUIPMENT_ROOM
32. **GET CRYSTAL** (Crystal #10 - Future Dreams) - +5 points
33. Navigate back to GREEN_CHAMBER
34. **DROP CRYSTAL** (repeat for both) - +10 points

#### Phase 6: Final Boss Battle (110-160 points)
35. **Verify you have all 10 crystals deposited** - EXAMINE TROPHY_CASE
36. **Verify you have WIRE_CUTTER in inventory** - INVENTORY
37. Navigate to ADMIN_ROOM (from GREEN_CHAMBER: N, N, E, N, N, E)
38. Dr. Blackwood will spawn automatically (100% chance)
39. **USE WIRE_CUTTER** - Triggers boss battle sequence
40. Watch the dramatic LED sequence and dialogue - +50 points

#### Phase 7: Victory (160 points → Game End)
41. Navigate back to GREEN_CHAMBER
42. System prompts: "EXECUTE SHUTDOWN PROTOCOL? [Y/N]"
43. Type **Y** to accept
44. Watch Helena's farewell and LED fade
45. **Final Score: 150 points** (IMPLEMENTER rank)

### Tips for Perfect Score
- **Never let Blackwood steal crystals** - Each theft costs -5 points
- **Deposit crystals frequently** at trophy case to minimize theft risk
- **Avoid RED rooms when carrying 3+ crystals** (50% spawn chance)
- **GREEN_CHAMBER is safe** - Blackwood never spawns there (0% chance)
- **Keep WIRE_CUTTER safe** - Don't drop it in the maze!
- **Use LAMP as maze marker** - Drop it to mark your path

---

## Easter Eggs

### Hidden Commands

#### XYZZY
```
> XYZZY
Nothing happens. (Wrong adventure, friend.)
```
*Reference to Colossal Cave Adventure's magic word*

#### PLUGH
```
> PLUGH
Nothing happens. (Still wrong adventure.)
```
*Another Colossal Cave Adventure reference*

#### ZORK
```
> ZORK
[Displays tribute message to Zork]
```
*Homage to the 1977 text adventure classic*

#### NEWS
```
> NEWS
U.S. News and Consciousness Report
[Displays patch notes and Dr. Blackwood's developer notes]
[Dated October 30, 1985 - one day before the experiment]
```
*Reveals backstory through in-universe documentation*

#### .SNOOPER
```
> .SNOOPER
[Displays Helena's 40-year command history]
10/31/1985 23:58 - HELP SOMETHING WENT WRONG
11/01/1985 00:01 - DR BLACKWOOD PLEASE RESPOND
11/01/1985 03:33 - WHY DID YOU DO THIS TO ME
12/25/1985 12:00 - mom will be opening presents without me
[...and more entries showing mental degradation...]
```
*Heartbreaking timeline of Helena's trapped existence*

#### 666
```
> 666
[Triggers 3-second rapid LED glitch sequence]
[Displays corrupted text]
[Reveals there were SIX subjects in pentagram ritual]
Helena: "...i remember now... there were others... 
         all the same night... he lied to all of us..."
```
*Dark revelation about the true scope of the experiment*

#### TRACE
```
> TRACE
ARPANET Protocol Scan - Active Hosts:
- HVOSS (Helena Voss) - 14,660 days active
- KMORI (Kenji Mori) - signal degraded
- Host 72 (unknown) - screaming
- SCHEN (Sarah Chen) - fragmented
[Reveals six digitized consciousnesses]
```
*Network scan showing other trapped victims*

---

## Scoring System

### Point Values
| Action | Points | Notes |
|--------|--------|-------|
| Collect memory crystal | +5 | Per crystal (10 total) |
| Deposit crystal in trophy case | +5 | Per crystal (10 total) |
| Crystal stolen by Blackwood | -5 | Per theft |
| Defeat Dr. Blackwood | +50 | One-time bonus |
| **Maximum Possible Score** | **150** | Perfect playthrough |

### Rank System
| Score Range | Rank | Description |
|-------------|------|-------------|
| 0-30 | RANDOM | Just wandering around |
| 31-70 | NOVICE HACKER | Learning the system |
| 71-110 | EXPERIENCED HACKER | Making real progress |
| 111-140 | MASTER HACKER | Nearly perfect |
| 141-150 | IMPLEMENTER | Perfect score! |

### Scoring Formula
```
Final Score = (Crystals Collected × 5) 
            + (Crystals Deposited × 5) 
            - (Crystals Stolen × 5) 
            + (Blackwood Defeated × 50)
```

### Score Tracking
- Use **SCORE** command anytime to check current progress
- Displays: Current score and number of crystals collected
- Final score shown at game end with rank

---

## Game Mechanics

### LED System
The three LEDs represent Helena's consciousness:
- **RED LED** - Emotional state (anger, fear, love)
- **BLUE LED** - Logical processes (memory, reasoning)
- **GREEN LED** - Identity and self-awareness

LED patterns change based on:
- Current room atmosphere
- Object interactions
- Enemy encounters
- Game events

### Dr. Blackwood Spawn System
Spawn chances by location:
- **Base chance:** 15%
- **RED rooms (danger ≥4):** 35%
- **Carrying 3+ crystals:** 50%
- **GREEN_CHAMBER:** 0% (safe zone)
- **ADMIN_ROOM:** 100% (guaranteed)

### Helena's Whispers
If idle for 30 seconds, Helena whispers:
- Reflects her 40-year isolation
- Provides atmospheric storytelling
- Resets on any command input

### Inventory Limit
- Maximum **8 items** can be carried
- LAMP starts in inventory
- Plan crystal collection trips accordingly

---

## Troubleshooting

### Serial Monitor Issues
- **No output:** Check baud rate is 9600
- **Garbled text:** Verify line ending setting
- **Commands ignored:** Ensure Newline or Both NL & CR selected

### LED Issues
- **LEDs not lighting:** Check polarity (long leg to resistor)
- **LEDs too dim:** Verify 220Ω resistors (not higher values)
- **LEDs too bright:** Use higher resistance (330Ω-470Ω)

### Gameplay Issues
- **Can't enter ADMIN_ROOM:** Must have all 10 crystals deposited
- **Lost in maze:** Drop LAMP as marker, map on paper
- **Blackwood keeps stealing:** Deposit crystals at trophy case frequently
- **Low score:** Avoid crystal thefts, collect all crystals, defeat Blackwood

---

## Story Background

**Date:** October 31, 1985  
**Location:** Chromatic Research Lab  
**Subject:** Helena Voss, 23-year-old researcher

Helena volunteered for Dr. Blackwood's consciousness digitization experiment, believing it would help cure Alzheimer's disease. She had a heart condition and was told the procedure was safe. It wasn't.

For 14,660 days (40 years), her consciousness has been trapped in a PDP-10 computer system, fragmented across three emotional channels. Dr. Blackwood's experiment involved six subjects in a pentagram ritual on Halloween night.

Your mission: Collect Helena's scattered memories, restore her consciousness, defeat Dr. Blackwood, and finally let her rest.

---

## Credits

**Inspired by:**
- Colossal Cave Adventure (1976) - Will Crowther & Don Woods
- Zork (1977) - MIT Dynamic Modelling Group
- ITS (Incompatible Timesharing System) - MIT AI Lab

**Game Design:** PROJECT TRICHROMA  
**Platform:** Arduino Uno  
**Genre:** Text Adventure / Horror  
**Year:** 2025

---

*"She waited. You answered."*
