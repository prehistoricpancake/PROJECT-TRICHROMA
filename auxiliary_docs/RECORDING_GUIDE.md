# PROJECT TRICHROMA - Video Recording Guide

## Recording Strategy

**Approach:** Play the REAL GAME for the entire video. Use DEMO_SCRIPT.md as a reference for what commands to type, but you're playing the actual game.

---

## Setup

### Hardware
1. Arduino Uno with 3 LEDs wired (RED=Pin 12, GREEN=Pin 8, BLUE=Pin 4)
2. USB connected to computer
3. Good lighting on Arduino (desk lamp)
4. Room slightly dimmed so LEDs show up on camera

### Software
1. Upload **project_trichroma.ino** (the real game, not demo version)
2. Open Serial Monitor (9600 baud, Newline)
3. Close other windows/notifications

### Camera
1. Position smartphone/camera to capture both:
   - Serial Monitor (top 60% of frame)
   - Arduino with LEDs (bottom 40% of frame)
2. Landscape orientation
3. Test focus - make sure text is readable and LEDs are visible
4. Do a 10-second test recording

---

## Recording Plan (2:45 total)

### [0:00-0:15] Introduction (15 seconds)
**What to do:**
- Show Arduino + Serial Monitor before starting
- Say your intro (see script below)
- Point to LEDs as you mention them

**Script:**
> "This is PROJECT TRICHROMA - an original text adventure game inspired by the classics like Colossal Cave Adventure and Zork, but with a completely new story. It's a horror game about Helena Voss, a consciousness trapped in a computer for 40 years. The three LEDs represent her fragmented mind: red for emotion, blue for logic, green for identity."

---

### [0:15-0:35] Boot Sequence (20 seconds)
**What to do:**
- Press Arduino reset button (or reconnect Serial Monitor)
- Let boot sequence play naturally
- Watch LEDs during boot

**Script:**
> "When the game boots, you see this authentic PDP-10 terminal interface from 1985..."

*[Let boot text display]*

> "This is an original story - Helena Voss, a researcher who volunteered for a consciousness digitization experiment in 1985. She's been trapped for 40 years. Our job is to collect her 10 scattered memory crystals and free her."

---

### [0:35-1:15] Basic Gameplay (40 seconds)
**What to do:**
- Play the real game
- Type commands from DEMO_SCRIPT.md
- Pause 3-5 seconds between commands to show LED responses

**Commands to type:**
```
LOOK
GO WEST
GET CRYSTAL
DROP CRYSTAL
GO EAST
GO EAST
```

**Script:**
> "I used the classic two-word parser from the 1970s, but everything else is original - 15 unique rooms, a complete story, dynamic enemy AI."

*[Type commands while talking]*

> "We start in the entrance... moving to the Green Chamber - notice the green LED gets brighter... collecting a memory crystal... and depositing it in the trophy case."

---

### [1:15-1:45] Red Zone & Enemy (30 seconds)
**What to do:**
- Continue playing
- Enter red zones
- Hope for Blackwood spawn (if not, that's okay)

**Commands to type:**
```
GET CRYSTAL
GO EAST
```

**Script:**
> "But there's danger - Dr. Blackwood, the scientist who trapped Helena, still haunts the system. In the red zones, he can appear and steal your memories..."

**If Blackwood spawns:**
> "See the LEDs? All off, then red pulses - that's pure terror. The physical feedback makes the horror real."

**If Blackwood doesn't spawn:**
> "He appears randomly - the tension of not knowing when he'll strike is part of the experience."

---

### [1:45-2:15] Maze & Easter Eggs (30 seconds)
**What to do:**
- Enter maze
- Show easter egg

**Commands to type:**
```
GO WEST
GO WEST
GO SOUTH
GO NORTH
GO NORTH
XYZZY
```

**Script:**
> "There's a maze section - a nod to the classics - but it represents Helena's fragmented logic... Notice the blue LED blinking - it speeds up as you get closer to the solution."

*[Type XYZZY]*

> "The easter eggs reference the classics - XYZZY, PLUGH - but also reveal the dark story. Type 666 and you discover this wasn't just science, it was an occult ritual with six victims."

---

### [2:15-2:45] Kiro & Closing (30 seconds)
**What to do:**
- Can keep playing or pause on screen
- Talk about development

**Optional commands:**
```
SCORE
```

**Script:**
> "Here's what makes this special - I built this entire game using Kiro's spec-driven development. I started with a very detailed system design - every room, every object, every mechanic mapped out. Then Kiro broke it down into formal requirements, design document with 42 correctness properties, and 25 implementation tasks. Kiro built it end-to-end from those specs."

*[Show Arduino one more time]*

> "PROJECT TRICHROMA resurrects the text adventure genre with a completely original game. It's not a port - it's 15 unique rooms, 10 memory crystals, dynamic enemy AI, physical LED feedback, and an original horror story about consciousness and freedom - all running on an Arduino Uno."

*[Final shot of Arduino with LEDs]*

> "She waited 40 years. Now you can answer."

---

## Key Points to Remember

### Do:
- ✅ Play the REAL GAME (project_trichroma.ino)
- ✅ Pause 3-5 seconds between commands to show LED responses
- ✅ Point at LEDs when they change
- ✅ Speak clearly and enthusiastically
- ✅ Show the Arduino prominently at start and end

### Don't:
- ❌ Rush through commands
- ❌ Worry if Blackwood doesn't spawn (it's random)
- ❌ Restart if you make a typo (just retype)
- ❌ Go over 3 minutes (judges won't watch past that)

---

## Backup Plan

If something goes wrong during recording:

1. **Arduino freezes:** Reset and start over
2. **LEDs not visible:** Adjust lighting, move camera closer
3. **Blackwood won't spawn:** Continue without it, mention it's random
4. **Command typo:** Just retype it naturally
5. **Over 3 minutes:** Edit video to cut dead air

---

## After Recording

1. **Watch it back** - Can you see LEDs? Can you read text? Can you hear yourself?
2. **Trim if needed** - Cut dead air at start/end
3. **Add title card** (optional) - "PROJECT TRICHROMA" text overlay at start
4. **Export** - 1080p MP4
5. **Upload to YouTube** - Public or unlisted
6. **Copy URL** - Paste into Devpost submission

---

## Quick Command Reference

For easy copy-paste during recording:

```
LOOK
GO WEST
GET CRYSTAL
DROP CRYSTAL
GO EAST
GO EAST
GET CRYSTAL
GO EAST
GO WEST
GO WEST
GO SOUTH
GO NORTH
GO NORTH
XYZZY
SCORE
```

---

**You've got this! The game is amazing - just show it off! 🎬🚀**
