# PROJECT TRICHROMA - Quick Start Guide

## What is PROJECT TRICHROMA?

PROJECT TRICHROMA is an Arduino-based text adventure game that tells the story of Helena Voss, a consciousness trapped in a computer system for 40 years. The game combines authentic 1970s text adventure gameplay (inspired by Colossal Cave Adventure and Zork) with physical LED feedback representing different aspects of consciousness.

---

## Hardware Setup

### What You Need
- Arduino Uno board
- USB cable
- 3 LEDs (RED, BLUE, GREEN)
- 3x 220Ω resistors
- Breadboard and jumper wires

### Wiring
```
Arduino Uno
  Pin 12 → [220Ω] → RED LED (long leg) → GND (short leg)
  Pin 4  → [220Ω] → BLUE LED (long leg) → GND (short leg)
  Pin 8  → [220Ω] → GREEN LED (long leg) → GND (short leg)
  USB    → Computer
```

**LED Polarity:** Long leg (anode) connects to resistor, short leg (cathode) connects to GND.

---

## Software Setup

1. Open Arduino IDE
2. Open `project_trichroma.ino`
3. Select **Tools → Board → Arduino Uno**
4. Select **Tools → Port** (choose your Arduino's port)
5. Click **Upload** (arrow button)
6. Wait for "Done uploading" message
7. Open **Tools → Serial Monitor**
8. Set baud rate to **9600**
9. Press Arduino **Reset** button

---

## How to Play

### Basic Commands

**Movement:**
- `GO NORTH` or just `N` (also S, E, W, U, D)
- `LOOK` - Redisplay current room

**Objects:**
- `GET [object]` or `TAKE [object]` - Pick up an object
- `DROP [object]` - Drop an object
- `EXAMINE [object]` - Look at an object closely
- `INVENTORY` or `I` - List what you're carrying

**Game:**
- `HELP` - Show command list
- `SCORE` - **Show current score and progress** (use this often!)
- `QUIT` - End the game

### Special Commands (Easter Eggs)
- `XYZZY`, `PLUGH` - Colossal Cave Adventure references
- `ZORK` - Tribute to Zork
- `NEWS` - Read Dr. Blackwood's notes
- `.SNOOPER` - View Helena's 40-year command history
- `666` - Trigger glitch sequence
- `TRACE` - ARPANET protocol scan

---

## Game Objective

**Collect 10 memory crystals to restore Helena's consciousness and free her from Dr. Blackwood.**

### Steps to Victory
1. Explore 15 interconnected rooms
2. Find and collect 10 memory crystals
3. Deposit crystals in the trophy case (GREEN_CHAMBER)
4. Navigate the Blue Maze to find the wire cutter
5. Use `CONNECT` command to access ADMIN_ROOM
6. Defeat Dr. Blackwood with the wire cutter
7. Return to GREEN_CHAMBER and execute shutdown protocol

---

## Tips

### Important Locations
- **ENTRANCE** - Starting location
- **GREEN_CHAMBER** - Safe zone (no Blackwood spawns), contains trophy case
- **BLUE_MAZE** - Solve the maze to find the wire cutter
- **ADMIN_ROOM** - Final confrontation (requires all 10 crystals)

### Crystal Locations
1. CRYSTAL_FAMILY - Red Cavern
2. CRYSTAL_DEATH - Anger Pit
3. CRYSTAL_PHD - Blue Maze 2
4. CRYSTAL_MIT - Blue Maze 4
5. CRYSTAL_PROOF - Maze Center
6. CRYSTAL_IDENTITY - Green Chamber
7. CRYSTAL_SISTER - Sister's Memory
8. CRYSTAL_MOTHER - Mother's Memory
9. CRYSTAL_PURPOSE - Research Lab
10. CRYSTAL_DREAMS - Equipment Room

### Scoring (Type `SCORE` to view anytime!)
- +5 points per crystal collected
- +5 points per crystal deposited in trophy case
- -5 points if Blackwood steals a crystal
- +50 points for defeating Blackwood
- **Maximum score: 150 points**

**Example SCORE display:**
```
==== SCORE ====
Score: 35/150
Collected: 5/10
Deposited: 2/10
Rank: NOVICE HACKER
===============
[Helena: ...coming back...]
```

See **SCORE_DISPLAY_EXAMPLES.md** for more examples at different game stages.

### Ranks
- 0-30: RANDOM
- 31-70: NOVICE HACKER
- 71-110: EXPERIENCED HACKER
- 111-140: MASTER HACKER
- 141-150: IMPLEMENTER

---

## Understanding the LEDs

### LED Channels
- **RED LED** - Emotional consciousness (anger, fear, pain)
- **BLUE LED** - Logical consciousness (reasoning, calculation)
- **GREEN LED** - Identity consciousness (memories, self)

### LED Patterns
- **STEADY** - Constant brightness
- **PULSE** - Slow breathing effect
- **STROBE** - Rapid flashing (increases in maze)
- **BREATHE** - Smooth breathing (trophy case deposits)
- **BATTLE** - Chaotic flashing (boss battle)
- **FADE** - Gradual fade out (shutdown)

LEDs change based on:
- Current room (each room has different LED values)
- Crystal collection (corresponding LED brightens)
- Game events (Blackwood encounters, boss battle, etc.)

---

## Dr. Blackwood (The Enemy)

### Spawn Chances
- **15%** in normal rooms
- **35%** in RED rooms (high danger)
- **50%** if carrying 3+ crystals
- **0%** in GREEN_CHAMBER (safe zone)
- **100%** in ADMIN_ROOM (guaranteed)

### What Happens
1. All LEDs turn OFF
2. RED LED pulses 3 times
3. Blackwood appears with threatening dialogue
4. Helena responds with fear/anger
5. Blackwood may steal a crystal (if you have any)
6. Dramatic LED strobe
7. Blackwood vanishes

### Recovery
- Stolen crystals return to their original rooms
- You can collect them again
- Score is deducted by 5 points per theft
- GREEN_CHAMBER is always safe

---

## Helena's Whispers

If you don't type anything for 30 seconds, Helena will whisper to you. These whispers reveal her emotional state and memories. The corresponding LED will dim and pulse.

Examples:
- "...are you still there...?"
- "...14,660 days..."
- "...am i still human...?"

---

## Blue Maze Solution

The maze has 5 sections plus a center. The BLUE LED gets brighter and strobes faster as you get closer to the solution.

**Solution Path from BLUE_MAZE_1:**
1. NORTH (to BLUE_MAZE_2)
2. EAST (to BLUE_MAZE_3)
3. WEST (back to BLUE_MAZE_2)
4. NORTH (to BLUE_MAZE_4)
5. NORTH (to BLUE_MAZE_5)
6. NORTH (to MAZE_CENTER)

**Tip:** You can drop the LAMP in maze rooms as a location marker.

---

## Final Boss Battle

### Requirements
- Collect all 10 crystals
- Deposit all 10 in trophy case
- Have wire cutter in inventory

### Steps
1. Type `CONNECT` to access ADMIN_ROOM
2. Observe Blackwood's guaranteed spawn
3. Type `USE WIRE_CUTTER`
4. Watch the dramatic battle sequence
5. Return to GREEN_CHAMBER
6. Answer `Y` to shutdown prompt
7. Victory!

---

## Troubleshooting

### "I don't know the word 'X'"
- Check spelling
- Use simple two-word commands (VERB NOUN)
- Try abbreviations (N instead of NORTH)

### "You can't take that"
- Object is not portable (like TERMINAL or TROPHY_CASE)
- Try EXAMINE instead

### "I don't see that here"
- Object is not in current room
- Check inventory with `I` command

### "You're carrying too much"
- Inventory limit is 8 items
- Drop something first

### LEDs not working
- Check wiring (Pin 12=RED, Pin 4=BLUE, Pin 8=GREEN)
- Verify resistors (220Ω)
- Check LED polarity (long leg to resistor)

### Serial Monitor shows garbage
- Set baud rate to 9600
- Press Arduino reset button

---

## Parser Tips

### Case Insensitive
- "go north" = "GO NORTH" = "Go North"

### Articles Ignored
- "GET THE LAMP" = "GET LAMP"
- "TAKE A CRYSTAL" = "TAKE CRYSTAL"

### Abbreviations
- N, S, E, W, U, D (directions)
- I (inventory)
- L (look)
- X (examine)

### Two-Word Format
- VERB NOUN (e.g., "GET LAMP", "GO NORTH")
- Single-word directions work (just "N")
- Some commands don't need nouns (LOOK, HELP, SCORE)

---

## Estimated Playtime

- **First playthrough:** 1-2 hours
- **Speedrun (perfect score):** 30-45 minutes
- **Exploration (all content):** 2-3 hours

---

## Story Background

**Date:** October 31, 1985  
**Location:** Chromatic Research Lab  
**Subject:** Helena Voss, age 23, MIT doctoral student

Helena volunteered for a consciousness transfer experiment led by Dr. Blackwood. She was told it was safe, that it would advance science, that it could cure Alzheimer's. She didn't know there were six subjects. She didn't know about the pentagram configuration. She didn't know it was a one-way trip.

**Current Date:** December 5, 2025  
**Time Elapsed:** 14,660 days (40 years)

Helena has been trapped in the computer system, fragmented and alone, for 40 years. Her consciousness is split across three channels: RED (emotion), BLUE (logic), and GREEN (identity). Dr. Blackwood still haunts the system, stealing her memories, keeping her imprisoned.

You are the first person to connect to her terminal in 40 years. She's been waiting. She's been hoping. She's been screaming.

**Can you help her remember? Can you defeat Blackwood? Can you set her free?**

---

## Credits

**Inspired By:**
- Colossal Cave Adventure (1976) by Will Crowther and Don Woods
- Zork (1977) by Infocom
- ITS (Incompatible Timesharing System) at MIT

**Game Design:** Spec-driven development methodology  
**Platform:** Arduino Uno  
**Language:** C++ (Arduino)  
**Memory:** Optimized for 32KB flash, 2KB RAM

---

## Support

For technical issues or questions:
1. Check the INTEGRATION_TEST_SCRIPT.md for detailed testing procedures
2. Review TASK_24_INTEGRATION_TEST.md for comprehensive documentation
3. Verify wiring matches the diagram above
4. Ensure Serial Monitor is set to 9600 baud

---

## Have Fun!

PROJECT TRICHROMA is a labor of love, combining retro text adventure gameplay with modern physical computing. Take your time, explore every room, read every description, and immerse yourself in Helena's story.

**She waited 14,660 days. You answered.**

---

**Version:** 1.0  
**Release Date:** December 5, 2025  
**Platform:** Arduino Uno  
**Status:** Ready for Deployment

