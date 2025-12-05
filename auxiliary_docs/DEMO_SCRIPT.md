# PROJECT TRICHROMA - Demo Recording Script

## Quick Demo Version (2:45 for video)

This is a **manual command sequence** optimized for video recording. Type these commands with ~5 second pauses between each to show LED responses.

### Setup Before Recording
1. Upload `project_trichroma.ino` to Arduino
2. Open Serial Monitor (9600 baud)
3. Position camera to capture both Arduino LEDs and Serial Monitor
4. Wait for boot sequence to complete
5. Start recording

---

## Command Sequence (Copy-Paste Ready)

**IMPORTANT: For the first minute, play the REAL GAME (project_trichroma.ino) to show authentic gameplay and boot sequence. This script is for reference only during that minute.**

### Part 1: Introduction & Basic Gameplay (0:00-1:00)

**[Use REAL GAME - just play naturally]**

```
LOOK
```
*Pause 3 seconds - let viewers read room description*

```
GO WEST
```
*Watch GREEN LED increase brightness*

```
EXAMINE TROPHY_CASE
```
*Shows 0 of 10 crystals*

```
GET CRYSTAL
```
*Watch GREEN LED pulse slowly - this is the consciousness responding*

```
DROP CRYSTAL
```
*Watch GREEN LED breathe pattern - Helena feels safer*

```
GO EAST
```
*Back to entrance*

---

### Part 2: Red Zone & Enemy Encounter (1:00-1:30)

```
GO EAST
```
*Enter RED_CAVERN - watch RED LED increase*

```
GET CRYSTAL
```
*RED LED pulses*

```
GO EAST
```
*Enter ANGER_PIT - very high RED LED, dangerous area*

**If Blackwood spawns:** Watch the sequence (all LEDs OFF → RED pulse 3× → strobe)

**If Blackwood doesn't spawn:** Continue to next command

```
GO WEST
```
*Back to RED_CAVERN*

```
GO WEST
```
*Back to ENTRANCE*

---

### Part 3: Blue Maze & Easter Egg (1:30-2:00)

```
GO SOUTH
```
*Enter BLUE_MAZE_1 - watch BLUE LED blink*

```
GO SOUTH
```
*BLUE LED blinks faster as you get closer to solution*

```
GO NORTH
```
*Exit maze*

```
GO NORTH
```
*Back to ENTRANCE*

```
XYZZY
```
*Easter egg response*

---

### Part 4: Scoring & Wrap-up (2:00-2:30)

```
INVENTORY
```
*Show what you're carrying*

```
SCORE
```
*Show current score and progress*

```
GO WEST
```
*Back to GREEN_CHAMBER*

```
DROP CRYSTAL
```
*Deposit the red crystal*

```
EXAMINE TROPHY_CASE
```
*Shows 2 of 10 crystals*

---

### Part 5: Closing (2:30-2:45)

**Say your closing lines while showing the Arduino with LEDs visible**

---

## Alternative: Fast Demo (1:30 version)

If you need a shorter demo, use this sequence:

```
LOOK
GO WEST
GET CRYSTAL
DROP CRYSTAL
GO EAST
GO EAST
GET CRYSTAL
GO EAST
XYZZY
SCORE
```

---

## Tips for Recording

### Timing
- **3 seconds** after each command to show LED response
- **5 seconds** for important moments (crystal pickup, Blackwood encounter)
- **2 seconds** for quick commands (LOOK, INVENTORY)

### What to Highlight
- **Boot sequence** - Let it play fully, shows the 1985 terminal aesthetic
- **LED changes** - Point at LEDs when they change
- **Blackwood encounter** - If he spawns, this is the most dramatic moment
- **Easter eggs** - Shows depth of content

### Camera Position
```
     [Camera View]
         ↓
┌─────────────────────┐
│  Serial Monitor     │ ← Top 60% of frame
│  (readable text)    │
└─────────────────────┘
        ↓ ↓ ↓
   [Arduino + LEDs]    ← Bottom 40% of frame
   (clearly visible)
```

### If Something Goes Wrong

**Blackwood won't spawn:**
- Just continue - mention "he appears randomly"
- Or restart and try again (15% base chance)

**LED not visible on camera:**
- Adjust lighting (dim room slightly)
- Move camera closer to Arduino
- Mention what's happening verbally

**Command typo:**
- Just retype it - shows it's real gameplay
- Don't restart unless it breaks the demo

---

## Auto-Play Version (Advanced)

If you want fully automated demo, modify `project_trichroma.ino`:

1. Add this at the top of `loop()`:
```cpp
// Demo mode - auto-play commands
static int demoStep = 0;
static unsigned long lastDemoTime = 0;
const char* demoCommands[] = {
  "LOOK", "GO WEST", "GET CRYSTAL", "DROP CRYSTAL",
  "GO EAST", "GO EAST", "GET CRYSTAL", "XYZZY", "SCORE", NULL
};

if (millis() - lastDemoTime > 3000 && demoCommands[demoStep] != NULL) {
  Serial.print("> ");
  Serial.println(demoCommands[demoStep]);
  Command cmd = parser.parse(demoCommands[demoStep]);
  if (cmd.valid) processCommand(cmd);
  demoStep++;
  lastDemoTime = millis();
}
```

2. Upload and let it run automatically
3. Just record - no typing needed

---

## Backup Plan

If Arduino demo fails during recording:

1. **Show the code** - Open `project_trichroma.ino` in Arduino IDE
2. **Show the specs** - Open `.kiro/specs/` folder
3. **Show the documentation** - Open `PROJECT_TRICHROMA_COMPLETE_GUIDE.md`
4. **Explain verbally** what the game does while showing static content

The judges care more about the concept and Kiro usage than perfect demo execution.

---

**Good luck with your recording! 🎬**
