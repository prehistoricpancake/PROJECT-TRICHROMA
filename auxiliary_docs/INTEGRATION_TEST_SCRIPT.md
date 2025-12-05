# PROJECT TRICHROMA - Integration Test Script

## Purpose
This script provides a step-by-step manual test procedure for verifying the complete integration of PROJECT TRICHROMA on Arduino Uno hardware.

---

## Pre-Test Setup

### Hardware Requirements
- [ ] Arduino Uno board
- [ ] USB cable
- [ ] 3 LEDs (RED, BLUE, GREEN)
- [ ] 3x 220Ω resistors
- [ ] Breadboard and jumper wires

### Wiring Verification
```
Pin 12 → [220Ω] → RED LED (long leg) → GND (short leg)
Pin 4  → [220Ω] → BLUE LED (long leg) → GND (short leg)
Pin 8  → [220Ω] → GREEN LED (long leg) → GND (short leg)
USB    → Computer
```

### Software Setup
- [ ] Arduino IDE installed
- [ ] Serial Monitor set to 9600 baud
- [ ] project_trichroma.ino uploaded to Arduino Uno
- [ ] Upload successful (verify "Done uploading" message)

---

## Test 1: Boot Sequence (5 minutes)

### Expected Behavior
1. Open Serial Monitor (9600 baud)
2. Press Arduino reset button

### Verification Checklist
- [ ] "==== CHROMATIC LAB ====" header displays
- [ ] "PDP-10 Terminal v2.1" displays
- [ ] "(c) 1985 ChromaTech" displays
- [ ] "ITS host 70 via ARPANET" displays
- [ ] "Booting..." displays
- [ ] GREEN LED flickers during boot (8 flashes)
- [ ] "WARNING: Fragmentation" displays
- [ ] RED LED pulses 3 times
- [ ] "Last boot: 14,660 days" displays
- [ ] "Session HVOSS - idle 14,660 days" displays
- [ ] "[Helena: ...someone there...?]" displays
- [ ] ENTRANCE room description displays
- [ ] Prompt ">" appears
- [ ] LEDs settle to ENTRANCE values (dim RED, dim BLUE, medium GREEN)

**Result:** PASS / FAIL

---

## Test 2: Basic Navigation (10 minutes)

### Test Commands
```
LOOK
N
LOOK
S
E
N
S
W
GO NORTH
GO INVALID
```

### Verification Checklist
- [ ] LOOK redisplays current room
- [ ] N moves to RED_CAVERN
- [ ] Room description displays
- [ ] Helena's dialogue displays
- [ ] LEDs change to RED_CAVERN values (bright RED, dim BLUE, dim GREEN)
- [ ] S returns to ENTRANCE
- [ ] E moves to RESEARCH_LAB
- [ ] N moves to EQUIPMENT_ROOM
- [ ] S returns to RESEARCH_LAB
- [ ] W returns to ENTRANCE
- [ ] GO NORTH works same as N
- [ ] Invalid direction shows "You can't go that way."

**Result:** PASS / FAIL

---

## Test 3: Parser and Error Handling (10 minutes)

### Test Commands
```
HELP
I
INVENTORY
get lamp
GET THE LAMP
FOOBAR
GET
GO
XYZZY
PLUGH
ZORK
```

### Verification Checklist
- [ ] HELP displays command list and game objective
- [ ] I shows inventory (LAMP present)
- [ ] INVENTORY shows same result
- [ ] "get lamp" works (case-insensitive)
- [ ] "GET THE LAMP" works (article filtered)
- [ ] FOOBAR shows "I don't know the word 'FOOBAR'."
- [ ] GET shows "What do you want to get?"
- [ ] GO shows "What do you want to go?"
- [ ] XYZZY shows "Nothing happens. (Wrong adventure, friend.)"
- [ ] PLUGH shows "Nothing happens. (Still wrong adventure.)"
- [ ] ZORK shows tribute message

**Result:** PASS / FAIL

---

## Test 4: Object Manipulation (15 minutes)

### Test Commands
```
N
EXAMINE CRYSTAL_FAMILY
GET CRYSTAL_FAMILY
I
SCORE
DROP CRYSTAL_FAMILY
GET CRYSTAL_FAMILY
S
S
DROP CRYSTAL_FAMILY
EXAMINE TROPHY_CASE
GET TERMINAL
```

### Verification Checklist
- [ ] N moves to RED_CAVERN
- [ ] EXAMINE shows crystal description
- [ ] Helena's dialogue displays
- [ ] LED pulses (RED channel)
- [ ] GET CRYSTAL_FAMILY adds to inventory
- [ ] Score increases by 5 points
- [ ] "[Crystal pulses...]" message
- [ ] RED LED brightness increases
- [ ] I shows LAMP and CRYSTAL_FAMILY
- [ ] SCORE shows score: 5, collected: 1/10
- [ ] DROP places crystal in RED_CAVERN
- [ ] GET picks it up again
- [ ] S, S returns to ENTRANCE, then GREEN_CHAMBER
- [ ] DROP in GREEN_CHAMBER deposits in trophy case
- [ ] Score increases by 5 (total 10)
- [ ] GREEN LED BREATHE pattern
- [ ] Helena says "...thank you..."
- [ ] Trophy case shows "1 of 10 crystals"
- [ ] EXAMINE TROPHY_CASE shows count
- [ ] GET TERMINAL shows "You can't take that."

**Result:** PASS / FAIL

---

## Test 5: Blue Maze Navigation (15 minutes)

### Test Commands
```
(From ENTRANCE)
N
W
LOOK
N
E
W
N
N
LOOK
GET WIRE_CUTTER
DROP LAMP
LOOK
```

### Verification Checklist
- [ ] Navigate to BLUE_MAZE_1 (N from ENTRANCE, W from RED_CAVERN)
- [ ] "maze of twisting passages, all alike" displays
- [ ] Binary code displays
- [ ] BLUE LED brightness ~200
- [ ] Navigate through maze: N, E, W, N, N
- [ ] BLUE LED brightness increases at each step
- [ ] BLUE LED strobe frequency increases
- [ ] Final room is MAZE_CENTER
- [ ] WIRE_CUTTER available
- [ ] GET WIRE_CUTTER adds to inventory
- [ ] DROP LAMP places it in MAZE_CENTER
- [ ] LOOK shows LAMP in room

**Result:** PASS / FAIL

---

## Test 6: Special Commands (10 minutes)

### Test Commands
```
NEWS
.SNOOPER
666
TRACE
SCORE
```

### Verification Checklist
- [ ] NEWS displays Dr. Blackwood's notes
- [ ] Date: Oct 30, 1985
- [ ] Mentions pentagram and six subjects
- [ ] Helena's commentary displays
- [ ] .SNOOPER shows 40-year command history
- [ ] Timestamps from 10/31/85 to present
- [ ] Total: 847,392 commands
- [ ] 666 triggers glitch sequence
- [ ] 3 seconds rapid LED flashing
- [ ] Corrupted text displays
- [ ] PROJECT: HEXAGRAM revealed
- [ ] 6 subjects (3 stable, 3 failed)
- [ ] Helena's revelation about ritual
- [ ] LEDs restore to room state
- [ ] TRACE shows ARPANET scan
- [ ] 4 hosts listed (HVOSS, KMORI, Host 72, SCHEN)
- [ ] SCORE displays current progress

**Result:** PASS / FAIL

---

## Test 7: Idle Whisper System (5 minutes)

### Test Procedure
1. Stop typing commands
2. Wait 30 seconds
3. Observe output

### Verification Checklist
- [ ] After 30 seconds, whisper displays
- [ ] Format: "[Helena: ...text...]"
- [ ] LED dims and pulses in one channel
- [ ] Prompt ">" appears after whisper
- [ ] Type any command
- [ ] Timer resets (wait another 30 seconds for next whisper)

**Result:** PASS / FAIL

---

## Test 8: Blackwood Encounter (20 minutes)

### Test Procedure
1. Collect 3+ crystals
2. Navigate to RED rooms (RED_CAVERN, ANGER_PIT)
3. Move between rooms until Blackwood spawns
4. Observe encounter sequence

### Verification Checklist
- [ ] "!!! BLACKWOOD !!!" message displays
- [ ] All LEDs turn OFF for 1 second
- [ ] RED LED pulses 3 times
- [ ] Random Blackwood dialogue displays
- [ ] Random Helena fear response displays
- [ ] If carrying crystals: one is stolen
- [ ] Score decreases by 5 points
- [ ] Crystal returns to original room
- [ ] Dramatic strobe for 2 seconds
- [ ] Room LEDs restore
- [ ] Can recover stolen crystal from original room
- [ ] GREEN_CHAMBER is safe (no spawns)

**Result:** PASS / FAIL

---

## Test 9: Crystal Collection (30 minutes)

### Test Procedure
Collect all 10 crystals and deposit in trophy case:

1. CRYSTAL_FAMILY - RED_CAVERN
2. CRYSTAL_DEATH - ANGER_PIT
3. CRYSTAL_PHD - BLUE_MAZE_2
4. CRYSTAL_MIT - BLUE_MAZE_4
5. CRYSTAL_PROOF - MAZE_CENTER
6. CRYSTAL_IDENTITY - GREEN_CHAMBER
7. CRYSTAL_SISTER - SISTER_MEMORY
8. CRYSTAL_MOTHER - MOTHER_MEMORY
9. CRYSTAL_PURPOSE - RESEARCH_LAB
10. CRYSTAL_DREAMS - EQUIPMENT_ROOM

### Verification Checklist
- [ ] Each crystal has unique description
- [ ] Each crystal triggers LED response
- [ ] Score increases by 5 per pickup
- [ ] Corresponding LED channel increases by 50
- [ ] Can carry up to 8 items (inventory limit)
- [ ] "Carrying too much." if inventory full
- [ ] Deposit in GREEN_CHAMBER trophy case
- [ ] Score increases by 5 per deposit
- [ ] GREEN LED BREATHE pattern each time
- [ ] Trophy case count updates (X of 10)
- [ ] Final count: 10 of 10
- [ ] Total score: 100 points (if no thefts)

**Result:** PASS / FAIL

---

## Test 10: Boss Battle (15 minutes)

### Test Procedure
```
(After collecting all 10 crystals)
CONNECT
(Observe ADMIN_ROOM entry)
USE WIRE_CUTTER
(Observe battle sequence)
```

### Verification Checklist
- [ ] CONNECT requires 10 crystals deposited
- [ ] "Insufficient" message if < 10
- [ ] Access granted message displays
- [ ] Warning about Blackwood
- [ ] Helena's dialogue about wire cutter
- [ ] Transported to ADMIN_ROOM
- [ ] All LEDs at full brightness (255, 255, 255)
- [ ] Room description displays
- [ ] Blackwood encounter triggers immediately
- [ ] USE WIRE_CUTTER starts battle
- [ ] "==== CONFRONTATION ====" header
- [ ] Blackwood's final dialogue
- [ ] "You cut the cable." action
- [ ] 5 seconds chaotic BATTLE LED pattern
- [ ] All LEDs FADE to OFF
- [ ] 2 seconds darkness
- [ ] GREEN LED restores with PULSE
- [ ] Helena's relief dialogue
- [ ] +50 points added (total ~150)
- [ ] "Return to GREEN_CHAMBER" message

**Result:** PASS / FAIL

---

## Test 11: Victory Condition (10 minutes)

### Test Procedure
```
(After defeating Blackwood)
(Navigate back to GREEN_CHAMBER)
(Observe shutdown prompt)
Y
(Observe shutdown sequence)
```

### Verification Checklist
- [ ] Return to GREEN_CHAMBER triggers prompt
- [ ] "CONSCIOUSNESS INTEGRITY: 94%" displays
- [ ] "EXECUTE SHUTDOWN PROTOCOL? [Y/N]" displays
- [ ] Y executes shutdown
- [ ] N cancels (can test both)
- [ ] "==== SHUTDOWN ====" header
- [ ] Helena's farewell dialogue (multi-line)
- [ ] "Fading..." message
- [ ] All LEDs FADE to OFF over 5 seconds
- [ ] Status messages: "RED: offline", "BLUE: offline", "GREEN: offline"
- [ ] "All channels: OFFLINE"
- [ ] "==== TERMINATED ====" header
- [ ] "Session HVOSS ended."
- [ ] Date range displays
- [ ] "14,660 days."
- [ ] "She waited. You answered."
- [ ] Final score: X/150
- [ ] Rank displays (should be IMPLEMENTER if 150)
- [ ] Summary: Crystals, Blackwood, Helena status
- [ ] Thank you message
- [ ] Game stops responding (gameOver flag set)

**Result:** PASS / FAIL

---

## Test 12: LED Pattern Verification (15 minutes)

### Visual Inspection
Test each LED pattern by observing during gameplay:

### Verification Checklist
- [ ] **STEADY**: Constant brightness, no flicker
- [ ] **PULSE**: Slow sine wave, 2-second period, smooth
- [ ] **STROBE**: Rapid on/off, frequency varies in maze
- [ ] **BREATHE**: Smooth breathing, 4-second period
- [ ] **BATTLE**: Chaotic rapid changes, random
- [ ] **SYNC**: All LEDs pulse together
- [ ] **FADE**: Gradual transition, 1 second
- [ ] **OFF**: LED completely off
- [ ] Patterns are visually distinct from each other
- [ ] No visible flicker in STEADY mode
- [ ] Smooth transitions between patterns
- [ ] Independent channel control (different patterns on different LEDs)
- [ ] LEDs update smoothly while typing commands

**Result:** PASS / FAIL

---

## Test 13: Non-Blocking Architecture (10 minutes)

### Test Procedure
1. Start typing a command slowly (one character per second)
2. Observe LED animations during typing
3. Leave command incomplete for 30 seconds
4. Observe idle whisper

### Verification Checklist
- [ ] LEDs continue animating while typing
- [ ] No lag or delay when typing characters
- [ ] Characters echo immediately
- [ ] Backspace works smoothly
- [ ] LED patterns don't freeze during command processing
- [ ] Idle whisper displays even with incomplete command
- [ ] Can continue typing after whisper
- [ ] No visible blocking or stuttering

**Result:** PASS / FAIL

---

## Test 14: Memory and Stability (30 minutes)

### Test Procedure
1. Play through complete game (boot to victory)
2. Monitor for crashes, freezes, or errors
3. Test edge cases

### Verification Checklist
- [ ] No crashes during complete playthrough
- [ ] No freezes or hangs
- [ ] No corrupted text output
- [ ] No LED glitches or stuck states
- [ ] Inventory limit enforced (8 items max)
- [ ] Input buffer limit enforced (64 chars max)
- [ ] Long gameplay session stable (30+ minutes)
- [ ] Multiple Blackwood encounters work correctly
- [ ] All 15 rooms accessible
- [ ] All 15 objects functional
- [ ] Score calculations correct
- [ ] No memory overflow errors

**Result:** PASS / FAIL

---

## Test 15: Edge Cases (15 minutes)

### Test Commands
```
(Empty input - just press Enter)
(Type 100 characters)
GET CRYSTAL_FAMILY (when not in room)
GET TERMINAL (non-portable)
DROP LAMP (when not carrying)
USE WIRE_CUTTER (outside ADMIN_ROOM)
CONNECT (before collecting all crystals)
GO UP (in ENTRANCE)
EXAMINE TROPHY_CASE (with 0, 5, 10 crystals)
```

### Verification Checklist
- [ ] Empty input ignored gracefully
- [ ] Long input truncated at 64 characters
- [ ] GET object not present: "I don't see that here."
- [ ] GET non-portable: "You can't take that."
- [ ] DROP not carrying: "You're not carrying that."
- [ ] USE WIRE_CUTTER wrong room: "Nothing to cut."
- [ ] CONNECT insufficient crystals: "Insufficient" message
- [ ] Invalid direction: "You can't go that way."
- [ ] Trophy case shows correct count at all stages

**Result:** PASS / FAIL

---

## Test Summary

### Results
- Test 1 (Boot Sequence): ___________
- Test 2 (Basic Navigation): ___________
- Test 3 (Parser): ___________
- Test 4 (Object Manipulation): ___________
- Test 5 (Blue Maze): ___________
- Test 6 (Special Commands): ___________
- Test 7 (Idle Whispers): ___________
- Test 8 (Blackwood): ___________
- Test 9 (Crystal Collection): ___________
- Test 10 (Boss Battle): ___________
- Test 11 (Victory): ___________
- Test 12 (LED Patterns): ___________
- Test 13 (Non-Blocking): ___________
- Test 14 (Stability): ___________
- Test 15 (Edge Cases): ___________

### Overall Status
**PASS** / **FAIL**

### Issues Found
(List any issues discovered during testing)

---

### Notes
(Additional observations or comments)

---

### Tester Information
- **Name:** ___________________________
- **Date:** ___________________________
- **Arduino IDE Version:** ___________________________
- **Board:** Arduino Uno
- **Sketch Size:** _________ bytes / 32256 bytes
- **RAM Usage:** _________ bytes / 2048 bytes

---

## Conclusion

This integration test script validates all requirements and ensures PROJECT TRICHROMA functions correctly on Arduino Uno hardware. All tests must pass before the project is considered complete and ready for deployment.

**Estimated Total Test Time:** 3-4 hours

