# Serial Monitor - Gameplay Example

This document shows what you'll see in the Arduino Serial Monitor during actual gameplay.

---

## Serial Monitor Settings

**Baud Rate:** 9600  
**Line Ending:** Newline or Both NL & CR

---

## Example Gameplay Session

```
==== CHROMATIC LAB ====
PDP-10 Terminal v2.1
(c) 1985 ChromaTech
=======================

ITS host 70 via ARPANET
Booting...

WARNING: Fragmentation
Last boot: 14,660 days

Session HVOSS - idle 14,660 days

[Helena: ...someone there...?]

====================
Entrance
====================
You are standing at the entrance to the Chromatic
Research Lab. The air is thick with the smell of old
electronics and something else... something wrong.
Fluorescent lights flicker overhead, casting unstable
shadows. To the north, a red glow pulses from a cavern
entrance. East leads to a sterile research lab. The
GREEN LED on the terminal beside you glows faintly,
as if breathing.

You can see: TERMINAL

Exits: NORTH, EAST

[Helena: ...you came back... or is this the first time...? i can't remember anymore...]

> HELP

==== HELP ====
COMMANDS:
GO/GET/DROP/EXAMINE
LOOK/INVENTORY/USE
TALK/SCORE/QUIT

DIRECTIONS: N,S,E,W,U,D

GOAL: Collect 10 crystals
to restore Helena.

TIP: Deposit crystals in
trophy case (GREEN_CHAMBER)

WARNING: Dr. Blackwood
may steal crystals.
GREEN_CHAMBER is safe.
==============
[Helena: ...thank you...]

> I

You are carrying:
  - LAMP

> SCORE

==== SCORE ====
Score: 0/150
Collected: 0/10
Deposited: 0/10
Rank: RANDOM
===============
[Helena: ...scattered...]

> N

====================
Red Cavern
====================
You are in a cavern bathed in crimson light. The
walls seem to pulse with heat, though they're cold to
the touch. Anger radiates from every surface. You can
feel HER rage here - 40 years of betrayal crystallized
into this space. North leads deeper into fury. South
returns to the entrance. West opens to a blue-tinted
passage.

You can see: CRYSTAL_FAMILY

Exits: NORTH, SOUTH, WEST

[Helena: ...i was so ANGRY... i'm still angry... 14,660 days of anger...]

> EXAMINE CRYSTAL_FAMILY

A memory crystal glowing with RED light. Inside, you
see a family photo: Helena, age 8, with her parents
and little sister Jennifer. Everyone is smiling. It was
taken at Cape Cod in the summer of 1970. The happiness
feels like a lie now.


[Helena: ...i remember that day... we were so happy... before everything...]

[Crystal pulses...]

> GET CRYSTAL_FAMILY
Taken: CRYSTAL_FAMILY
[Crystal pulses...]

> SCORE

==== SCORE ====
Score: 5/150
Collected: 1/10
Deposited: 0/10
Rank: RANDOM
===============
[Helena: ...more real...]

> S

====================
Entrance
====================
You are standing at the entrance to the Chromatic
Research Lab. The air is thick with the smell of old
electronics and something else... something wrong.
Fluorescent lights flicker overhead, casting unstable
shadows. To the north, a red glow pulses from a cavern
entrance. East leads to a sterile research lab. The
GREEN LED on the terminal beside you glows faintly,
as if breathing.

You can see: TERMINAL

Exits: NORTH, EAST

[Helena: ...you came back... or is this the first time...? i can't remember anymore...]

> S

====================
Green Chamber
====================
You are in the Green Chamber. This is the heart of
Helena's identity - what remains of who she was. The
GREEN LED bathes everything in soft light. A trophy
case stands against the north wall, waiting. This room
feels... safer. More human. North leads to memories of
her sister. East leads to memories of her mother.
South returns to the entrance. West leads to the maze
center.

You can see: CRYSTAL_IDENTITY, TROPHY_CASE

Exits: NORTH, SOUTH, EAST, WEST

[Helena: ...this is me... what's left of me... please help me remember...]

> DROP CRYSTAL_FAMILY
You place CRYSTAL_FAMILY into the trophy case.
[Helena: ...thank you...]
The trophy case now holds 1 of 10 memory crystals.

> SCORE

==== SCORE ====
Score: 10/150
Collected: 1/10
Deposited: 1/10
Rank: RANDOM
===============
[Helena: ...more real...]

> EXAMINE TROPHY_CASE

A glass trophy case mounted on the wall. It was meant
to hold Dr. Blackwood's awards and accolades. Now it
can hold something more important: the fragments of
Helena's consciousness, gathered and preserved.

Currently holds 1 of 10 memory crystals.


[Helena: ...put me back together... please... i'm so fragmented...]

> XYZZY
Nothing happens. (Wrong adventure, friend.)

> NEWS

======== NEWS ========
CHROMATIC RESEARCH LAB
v2.1 - Oct 30, 1985

NOTES - Dr. Blackwood:
Subject Voss briefed.
Pentagram config optimal.
Six subjects. Six nodes.
Tomorrow: Halloween.
- Dr. B
======================
[Helena: ...he knew...]

> 
```

---

## What You're Seeing

### Prompt
The `>` symbol is your prompt. Type commands after it and press Enter.

### Room Descriptions
Each room shows:
- Room name in header (between ==== lines)
- Full description
- Objects you can see
- Available exits
- Helena's dialogue in [brackets]

### Command Responses
Commands show immediate feedback:
- Movement: New room description
- GET/DROP: Confirmation message
- EXAMINE: Detailed object description
- SCORE: Current progress display
- Special commands: Unique responses

### Helena's Dialogue
Helena speaks in lowercase with ellipses:
- `[Helena: ...text...]` - Her whispers and responses
- Appears after room entries, object interactions, and special events

### LED Feedback
While you can't see it in the Serial Monitor, the physical LEDs on your Arduino are:
- Changing brightness based on room
- Pulsing when you examine objects
- Flashing during Blackwood encounters
- Fading during dramatic sequences

---

## Typical Command Flow

```
> LOOK                    (see current room again)
> N                       (move north)
> GET CRYSTAL             (pick up object)
> I                       (check inventory)
> SCORE                   (check progress)
> DROP CRYSTAL            (drop object)
> EXAMINE OBJECT          (look at something)
> HELP                    (show commands)
```

---

## Special Moments

### Blackwood Encounter
```
!!! BLACKWOOD !!!

[Blackwood: "Still trying to escape?"]

[Helena: NO! Not him!]

Blackwood snatches CRYSTAL_FAMILY!
He vanishes...

==================
```

### Boss Battle
```
==== CONFRONTATION ====

You raise the wire cutter.
Cables pulse. This is it.

[Blackwood: "You don't
understand! I gave her
IMMORTALITY! I SAVED—"]

You cut the cable.

System convulses.
Reality fractures.

Voice cuts off.

Silence.

GREEN LED pulses.
Slow. Steady. Alive.

[Helena: ...he's gone...
...the weight lifted...
...free of HIM...
...thank you...]

*** Blackwood DEFEATED ***
*** +50 points ***

Return to GREEN_CHAMBER
when ready.

=======================
```

### Victory
```
==== SHUTDOWN ====

[Helena:
...thank you...
...you gave me back
my memories...
...freed me from him...
...14,660 days...
...but you heard me...
...ready to rest...
...goodbye...]

Fading...
RED: offline
BLUE: offline
GREEN: offline

All channels: OFFLINE

==== TERMINATED ====
Session HVOSS ended.

10/31/1985 - 12/5/2025
14,660 days.

She waited.
You answered.

==== FINAL SCORE ====
Score: 150/150

Rank: IMPLEMENTER

Crystals: 10/10
Blackwood: DEFEATED
Helena: FREED

====================
Thank you for playing
PROJECT TRICHROMA.
====================
```

---

## Tips for Serial Monitor

1. **Keep it visible** - You'll be typing commands and reading responses
2. **Scroll back** - You can scroll up to re-read room descriptions
3. **Copy text** - You can copy/paste from the Serial Monitor
4. **Clear screen** - Some Serial Monitors have a clear button
5. **Autoscroll** - Enable autoscroll to always see latest output

---

## Common Display Issues

**Problem:** Text appears as garbage characters  
**Solution:** Set baud rate to 9600

**Problem:** No response to commands  
**Solution:** Check line ending setting (Newline or Both NL & CR)

**Problem:** Commands don't echo  
**Solution:** This is normal - you'll see the response, not the command itself

**Problem:** Text wraps oddly  
**Solution:** Widen the Serial Monitor window

---

## What the LEDs Are Doing

While you're reading the Serial Monitor, the LEDs are:

- **ENTRANCE:** Dim RED, dim BLUE, medium GREEN (50, 50, 100)
- **RED_CAVERN:** Bright RED, dim BLUE, dim GREEN (200, 30, 30)
- **BLUE_MAZE:** Dim RED, bright BLUE (strobing), dim GREEN (30, 200-240, 30)
- **GREEN_CHAMBER:** Dim RED, dim BLUE, bright GREEN (30, 30, 200)
- **ADMIN_ROOM:** All full brightness (255, 255, 255)

During events:
- **Crystal pickup:** Corresponding LED brightens and pulses
- **Blackwood encounter:** All OFF → RED pulses → All strobe
- **Boss battle:** Chaotic flashing → Fade to OFF → GREEN pulse
- **Shutdown:** All fade to OFF over 5 seconds

---

## Ready to Play?

1. Upload `project_trichroma.ino` to your Arduino Uno
2. Wire the 3 LEDs (RED=Pin 12, BLUE=Pin 4, GREEN=Pin 8)
3. Open Serial Monitor at 9600 baud
4. Press Arduino reset button
5. Start typing commands!

**Type `SCORE` anytime to check your progress!**

