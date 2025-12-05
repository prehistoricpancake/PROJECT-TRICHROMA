# Design Document

## Overview

PROJECT TRICHROMA is an Arduino Uno-based text adventure game combining authentic 1976 Colossal Cave Adventure and 1977 Zork gameplay mechanics with a horror narrative about Helena Voss, a consciousness trapped in a computer system for 40 years. The game uses three LEDs (RED, BLUE, GREEN) to represent consciousness aspects, creating a unique physical-digital storytelling experience.

The system prioritizes memory efficiency (32KB flash, 2KB RAM constraints) and non-blocking execution for smooth LED animations while processing player commands. Features include 15 interconnected rooms, 10 collectible memory crystals, two-word command parser, dynamic enemy encounters, and multiple endings.

## Architecture

### System Components

```
Arduino Main Loop (Non-blocking, millis()-based)
├── Serial Input Handler
├── LED Manager (PulseManager)
├── Command Parser (Two-word VERB NOUN)
├── Game State Manager
│   ├── Room System
│   ├── Object System
│   ├── Enemy System (Dr. Blackwood)
│   ├── Dialogue System
│   └── Scoring System
```

### Hardware Interface

- Pin 12: RED LED - Emotional consciousness channel
- Pin 4: BLUE LED - Logic consciousness channel
- Pin 8: GREEN LED - Identity consciousness channel
- Serial: USB at 9600 baud

Software PWM implementation (pins don't support hardware PWM).

### Memory Management

1. PROGMEM for all static strings
2. Byte types for IDs and flags
3. Char arrays instead of String class
4. Minimal globals
5. Shallow call depth

## Components and Interfaces

### PulseManager Class

```cpp
class PulseManager {
  enum Pattern { STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE, OFF };
  void init(byte redPin, byte bluePin, byte greenPin);
  void setPattern(byte channel, Pattern pattern, byte targetBrightness);
  void update(); // Non-blocking
};
```

### Room System

```cpp
struct Room {
  byte id;
  const char* name;        // PROGMEM
  const char* description; // PROGMEM
  byte exits[6];          // N,S,E,W,U,D (255=no exit)
  byte ledRed, ledBlue, ledGreen;
  byte dangerLevel;       // 0-5
  const char* helenaDialogue; // PROGMEM
};
```

15 rooms: ENTRANCE, RED_CAVERN, ANGER_PIT, BLUE_MAZE_1-5, MAZE_CENTER, GREEN_CHAMBER, SISTER_MEMORY, MOTHER_MEMORY, ADMIN_ROOM, RESEARCH_LAB, EQUIPMENT_ROOM.

### Object System

```cpp
struct Object {
  byte id;
  const char* name;        // PROGMEM
  const char* description; // PROGMEM
  byte location;          // Room ID or 255=inventory
  byte flags;             // Bitfield
  byte ledResponse;       // 0=RED, 1=BLUE, 2=GREEN, 3=ALL
  const char* helenaDialogue; // PROGMEM
};
```

Key objects: LAMP, 10 MEMORY_CRYSTALS, WIRE_CUTTER, TROPHY_CASE, TERMINAL, RESEARCH_NOTES.

### Command Parser

```cpp
class Parser {
  struct Command {
    byte verb, noun;
    bool valid;
  };
  Command parse(const char* input);
};
```

Supports: GO, GET, TAKE, DROP, EXAMINE, LOOK, INVENTORY, USE, TALK, HELP, SCORE, QUIT, TRACE, CONNECT, plus special commands (XYZZY, PLUGH, ZORK, NEWS, .SNOOPER, 666).

### Game State Manager

```cpp
class GameState {
  byte currentRoom;
  byte inventory[8];
  int score;
  byte crystalsCollected, crystalsDeposited;
  bool blackwoodDefeated, gameOver;
  unsigned long lastCommandTime, blackwoodCooldown;
};
```

### Enemy System

```cpp
class EnemySystem {
  bool shouldSpawn(byte roomId, byte crystalCount);
  void triggerEncounter(GameState& state, PulseManager& leds);
};
```

Spawn chances: 15% base, 35% RED rooms, 50% if 3+ crystals, 0% GREEN_CHAMBER, 100% ADMIN_ROOM.

## Data Models

### Memory Crystal Mapping

| ID | Location | LED | Memory Type |
|----|----------|-----|-------------|
| 1 | RED_CAVERN | RED | Family photo |
| 2 | ANGER_PIT | RED | Death moment |
| 3 | BLUE_MAZE_2 | BLUE | PhD letter |
| 4 | BLUE_MAZE_4 | BLUE | MIT memory |
| 5 | MAZE_CENTER | BLUE | Math proof |
| 6 | GREEN_CHAMBER | GREEN | Own identity |
| 7 | SISTER_MEMORY | GREEN | Sister Jennifer |
| 8 | MOTHER_MEMORY | GREEN | Mother's love |
| 9 | RESEARCH_LAB | GREEN | Why volunteer |
| 10 | EQUIPMENT_ROOM | GREEN | Future dreams |


## Correctness Properties

*A property is a characteristic or behavior that should hold true across all valid executions of a system—essentially, a formal statement about what the system should do. Properties serve as the bridge between human-readable specifications and machine-verifiable correctness guarantees.*

### Property 1: Non-blocking LED execution
*For any* LED pattern and serial input, when LED pattern executes, serial input processing SHALL continue without blocking.
**Validates: Requirements 1.2, 2.5, 15.2, 15.3**

### Property 2: Room LED state consistency
*For any* room entered, LED brightness values SHALL match room's defined RED, BLUE, GREEN intensities.
**Validates: Requirements 1.3, 4.4**

### Property 3: Independent LED channel state
*For any* LED pattern combination on three channels, each SHALL maintain independent state without timing interference.
**Validates: Requirements 1.5**

### Property 4: Case-insensitive command parsing
*For any* input string, all characters SHALL be converted to uppercase before parsing.
**Validates: Requirements 2.3**

### Property 5: Two-word command extraction
*For any* command input, parser SHALL extract first word as VERB and second as NOUN.
**Validates: Requirements 3.1**

### Property 6: Article filtering
*For any* command with articles (THE, A, AN), parser SHALL ignore them during parsing.
**Validates: Requirements 3.4**

### Property 7: Unknown word error
*For any* unrecognized word, system SHALL display "I don't know the word '[word]'."
**Validates: Requirements 3.5**

### Property 8: Incomplete command error
*For any* verb requiring noun, when entered without noun, system SHALL display "What do you want to [verb]?"
**Validates: Requirements 3.6**

### Property 9: Room information completeness
*For any* room entered, system SHALL display name, description, objects, and exits.
**Validates: Requirements 4.2**

### Property 10: Invalid movement rejection
*For any* room and invalid direction, system SHALL display "You can't go that way."
**Validates: Requirements 4.3**

### Property 11: Room-specific Helena dialogue
*For any* room entered, system SHALL display Helena's associated dialogue.
**Validates: Requirements 4.5**

### Property 12: Maze room description
*For any* BLUE_MAZE room entered, system SHALL display "You are in a maze of twisting passages, all alike" with binary code text.
**Validates: Requirements 5.1**

### Property 13: Maze navigation feedback
*For any* move toward maze solution, system SHALL increase BLUE LED blink frequency.
**Validates: Requirements 5.4**

### Property 14: Object persistence in maze
*For any* maze room, when LAMP dropped, object SHALL remain as location marker.
**Validates: Requirements 5.5**

### Property 15: Portable object acquisition
*For any* portable object in room, GET/TAKE SHALL move object to inventory.
**Validates: Requirements 6.1**

### Property 16: Object drop mechanics
*For any* object in inventory, DROP SHALL move object to current room.
**Validates: Requirements 6.2**

### Property 17: Inventory display completeness
*For any* inventory state, INVENTORY/I SHALL display all carried objects.
**Validates: Requirements 6.3**

### Property 18: Object examination with LED
*For any* examinable object, EXAMINE SHALL display description and trigger LED response.
**Validates: Requirements 6.4**

### Property 19: Non-portable object rejection
*For any* non-portable object, GET SHALL display "You can't take that."
**Validates: Requirements 6.5**

### Property 20: Absent object rejection
*For any* object not in room, GET SHALL display "I don't see that here."
**Validates: Requirements 6.6**

### Property 21: Object interaction dialogue
*For any* object with dialogue, interaction SHALL display Helena's dialogue.
**Validates: Requirements 6.7**

### Property 22: Memory crystal unique descriptions
*For any* memory crystal examined, system SHALL display unique description for its memory type.
**Validates: Requirements 7.2**

### Property 23: Memory crystal LED response
*For any* memory crystal picked up, system SHALL increase corresponding LED channel by 50 and trigger slow pulse.
**Validates: Requirements 7.3**

### Property 24: Trophy case crystal storage
*For any* memory crystal dropped in GREEN_CHAMBER trophy case, system SHALL store permanently and add 5 points.
**Validates: Requirements 7.4**

### Property 25: Trophy case storage feedback
*For any* crystal stored, system SHALL trigger GREEN LED breathe pattern and display Helena's gratitude.
**Validates: Requirements 7.5**

### Property 26: Trophy case state display
*For any* trophy case state (0-10 crystals), EXAMINE SHALL display "Currently holds [X] of 10 memory crystals" with correct count.
**Validates: Requirements 7.6**

### Property 27: Blackwood spawn calculation
*For any* room and player state, spawn chance SHALL follow formula: 15% base, 35% RED rooms, 50% if 3+ crystals, 0% GREEN_CHAMBER, 100% ADMIN_ROOM.
**Validates: Requirements 8.1**

### Property 28: Blackwood crystal theft
*For any* crystal in inventory when Blackwood encounters player, system SHALL steal random crystal, deduct 5 points, return to original room.
**Validates: Requirements 8.3**

### Property 29: Blackwood dialogue selection
*For any* Blackwood spawn, system SHALL select dialogue from defined threatening message pool.
**Validates: Requirements 8.5**

### Property 30: Helena fear response
*For any* Blackwood appearance, system SHALL trigger Helena's fear/anger response from defined pool.
**Validates: Requirements 8.6**

### Property 31: Final score calculation
*For any* game end state, system SHALL calculate score: +5 per crystal collected, +5 per deposited, -5 per stolen, +50 for defeating Blackwood (max 150).
**Validates: Requirements 10.3**

### Property 32: Rank assignment
*For any* final score, system SHALL display rank: 0-30 RANDOM, 31-70 NOVICE HACKER, 71-110 EXPERIENCED HACKER, 111-140 MASTER HACKER, 141-150 IMPLEMENTER.
**Validates: Requirements 10.4**

### Property 33: Idle whisper timing
*For any* 30-second period without input, system SHALL display random whisper from Helena's pool.
**Validates: Requirements 11.1**

### Property 34: Whisper LED response
*For any* whisper displayed, system SHALL trigger dim pulse in LED channel matching emotional tone.
**Validates: Requirements 11.2**

### Property 35: Whisper pool selection
*For any* whisper event, system SHALL select from defined 15-message pool.
**Validates: Requirements 11.3**

### Property 36: Idle timer reset
*For any* command entered, system SHALL reset idle timer to zero.
**Validates: Requirements 11.4**

### Property 37: Independent timing systems
*For any* active timing systems (LED updates, idle whispers, Blackwood cooldowns), each SHALL maintain independent timestamps without interference.
**Validates: Requirements 15.4**

### Property 38: Smooth LED transitions
*For any* LED brightness transition, PulseManager SHALL calculate smooth changes using mathematical interpolation without blocking.
**Validates: Requirements 15.5**

### Property 39: Crystal collection scoring
*For any* memory crystal collected, system SHALL add 5 points to score.
**Validates: Requirements 16.1**

### Property 40: Crystal deposit scoring
*For any* memory crystal deposited in trophy case, system SHALL add 5 points to score.
**Validates: Requirements 16.2**

### Property 41: Crystal theft scoring
*For any* memory crystal stolen by Blackwood, system SHALL subtract 5 points from score.
**Validates: Requirements 16.3**

### Property 42: Score command display
*For any* game state, SCORE command SHALL display current score and crystal count.
**Validates: Requirements 16.5**


## Error Handling

### Serial Communication
- Buffer overflow: Truncate to 64 chars
- Invalid characters: Filter non-printable
- Empty input: Ignore silently

### Parser Errors
- Unknown verb/noun: "I don't know the word '[word]'."
- Missing noun: "What do you want to [verb]?"

### Game State
- Inventory full (8 items): "You're carrying too much."
- Object not found: "I don't see that here."
- Invalid action: "You can't do that."
- No exit: "You can't go that way."

### LED System
- Brightness clamping: 0-255 range
- millis() overflow: Handled by unsigned arithmetic (wraps at 49.7 days)

### Memory
- Stack overflow: Prevented by shallow call depth
- Heap fragmentation: Prevented by avoiding dynamic allocation

## Testing Strategy

### Unit Testing

**Parser Tests:**
- Each supported verb recognized
- Direction abbreviations expand correctly
- Article filtering works
- "I" expands to "INVENTORY"
- Error messages for unknown words

**Room Navigation Tests:**
- Starting position is ENTRANCE with LAMP
- Each room displays correct information
- Invalid directions show error
- All 15 rooms accessible
- ADMIN_ROOM requires 10 crystals

**Object System Tests:**
- GET moves portable object to inventory
- DROP moves object to room
- Non-portable objects rejected
- EXAMINE displays description
- Inventory limit (8 items)

**Scoring Tests:**
- Initial score is 0
- Crystal collection adds 5 points
- Crystal deposit adds 5 points
- Blackwood theft subtracts 5 points
- Blackwood defeat adds 50 points
- Rank assignment for boundary scores

**LED Pattern Tests:**
- Each pattern mode works (STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE)
- Brightness clamping (0-255)
- Pattern transitions

**Special Command Tests:**
- XYZZY, PLUGH, ZORK easter eggs
- NEWS displays report
- .SNOOPER displays command history
- 666 triggers glitch sequence
- TRACE displays ARPANET scan
- HELP displays all information

**Boot Sequence Tests:**
- Boot displays PDP-10 header
- Boot displays warnings
- Boot ends with ENTRANCE description

**Edge Cases:**
- Empty inventory display
- Full inventory (8 items)
- Blackwood encounter with no crystals
- Dropping LAMP in maze rooms
- Trophy case with 0, 5, 10 crystals

### Property-Based Testing

Using lightweight PBT framework adapted for Arduino. Each test runs minimum 100 iterations.

**Property Test 1: Non-blocking LED execution**
- Generate: Random LED patterns, random serial inputs
- Property: Serial input processed within 100ms regardless of LED state
- **Feature: project-trichroma, Property 1: Non-blocking LED execution**

**Property Test 2: Room LED state consistency**
- Generate: Random room IDs (0-14)
- Property: After entering room, LED values match room definition
- **Feature: project-trichroma, Property 2: Room LED state consistency**

**Property Test 3: Independent LED channel state**
- Generate: Random pattern combinations for 3 channels
- Property: Each channel maintains independent timing
- **Feature: project-trichroma, Property 3: Independent LED channel state**

**Property Test 4: Case-insensitive parsing**
- Generate: Random commands with mixed case
- Property: Parsing result identical to uppercase version
- **Feature: project-trichroma, Property 4: Case-insensitive command parsing**

**Property Test 5: Two-word extraction**
- Generate: Random two-word commands
- Property: First word as verb, second as noun
- **Feature: project-trichroma, Property 5: Two-word command extraction**

**Property Test 6: Article filtering**
- Generate: Commands with articles in various positions
- Property: Articles removed before matching
- **Feature: project-trichroma, Property 6: Article filtering in commands**

**Property Test 7: Room information completeness**
- Generate: Random room IDs
- Property: Display includes name, description, objects, exits
- **Feature: project-trichroma, Property 9: Room information display completeness**

**Property Test 8: Invalid movement rejection**
- Generate: Random room IDs, random invalid directions
- Property: Error message displayed, room unchanged
- **Feature: project-trichroma, Property 10: Invalid movement rejection**

**Property Test 9: Object acquisition and drop round-trip**
- Generate: Random portable objects, random rooms
- Property: GET then DROP returns object to room
- **Feature: project-trichroma, Property 15 & 16: Object acquisition and drop**

**Property Test 10: Inventory display completeness**
- Generate: Random inventory states (0-8 items)
- Property: All items displayed
- **Feature: project-trichroma, Property 17: Inventory display completeness**

**Property Test 11: Trophy case state accuracy**
- Generate: Random crystals deposited (0-10)
- Property: Display shows correct count
- **Feature: project-trichroma, Property 26: Trophy case state display**

**Property Test 12: Blackwood spawn calculation**
- Generate: Random rooms, random crystal counts
- Property: Spawn chance matches formula
- **Feature: project-trichroma, Property 27: Blackwood spawn chance calculation**

**Property Test 13: Score calculation**
- Generate: Random game states
- Property: Final score matches formula
- **Feature: project-trichroma, Property 31: Final score calculation**

**Property Test 14: Rank assignment**
- Generate: Random scores (0-150)
- Property: Rank matches score range
- **Feature: project-trichroma, Property 32: Rank assignment by score**

**Property Test 15: Idle timer reset**
- Generate: Random commands
- Property: Any command resets idle timer to 0
- **Feature: project-trichroma, Property 36: Idle timer reset**

### Integration Testing

1. **Complete Playthrough**: Simulate optimal path from start to victory
2. **Blackwood Encounter**: Verify theft and recovery mechanics
3. **Maze Solution**: Verify path from ENTRANCE to MAZE_CENTER
4. **Memory Collection**: Collect all 10 crystals, verify trophy case
5. **Final Boss**: Verify ADMIN_ROOM access and battle sequence
6. **Shutdown Protocol**: Verify victory condition and game end

### Hardware Testing

1. **LED Visibility**: All three LEDs visible and distinguishable
2. **LED Patterns**: Each pattern produces expected visual effect
3. **Serial Communication**: Commands processed correctly at 9600 baud
4. **Memory Constraints**: Sketch fits in 32KB flash, runs within 2KB RAM
5. **Timing Accuracy**: millis()-based timing produces smooth animations
6. **Long-Running Stability**: Game runs for extended periods without crashes

## Implementation Notes

### Memory Optimization
- Use F() macro for Serial.print() strings
- Reuse common strings
- Use bitfields for boolean flags
- Pre-allocate fixed buffers (64 bytes for input)
- Mark all read-only data as const

### Non-Blocking Architecture

```cpp
void loop() {
  unsigned long currentMillis = millis();
  
  pulseManager.update();  // Update LEDs
  
  if (Serial.available()) {
    readCommand();
    processCommand();
    lastCommandTime = currentMillis;
  }
  
  if (currentMillis - lastCommandTime > 30000) {
    displayWhisper();
    lastCommandTime = currentMillis;
  }
  
  updateGameState();
}
```

### LED Software PWM

```cpp
void PulseManager::update() {
  unsigned long now = millis();
  for (byte i = 0; i < 3; i++) {
    byte target = calculateBrightness(i, now);
    if ((now % 256) < target) {
      digitalWrite(pins[i], HIGH);
    } else {
      digitalWrite(pins[i], LOW);
    }
  }
}
```

### Random Number Generation

```cpp
void setup() {
  randomSeed(analogRead(A0));  // Seed with noise from floating pin
}
```

### PROGMEM String Access

```cpp
void printProgmemString(const char* str) {
  char c;
  while ((c = pgm_read_byte(str++))) {
    Serial.print(c);
  }
}
```

### Wiring Diagram

```
Arduino Uno
  Pin 12 ──── [220Ω] ──── RED LED ──── GND
  Pin 4  ──── [220Ω] ──── BLUE LED ─── GND
  Pin 8  ──── [220Ω] ──── GREEN LED ── GND
  USB    ──── Computer (Serial Monitor)

LED Polarity: Long leg (anode) to resistor, short leg (cathode) to GND
```

### Performance Targets

- Loop Frequency: > 100 Hz (< 10ms per iteration)
- Command Response: < 100ms from Enter to output
- LED Update Rate: > 30 Hz (smooth to human eye)
- Memory Usage: < 28KB flash, < 1.5KB RAM (safety margin)
- Boot Time: < 3 seconds to first prompt

### Known Limitations

1. **No Save System**: Game state lost on power cycle (by design, fits narrative)
2. **Limited Inventory**: Maximum 8 items (RAM constraint)
3. **Text-Only**: No graphics (hardware limitation)
4. **Single Player**: No multiplayer (hardware limitation)
5. **Fixed Content**: No procedural generation (memory constraint)

### Future Enhancements (Out of Scope)

- EEPROM save system for high scores
- Sound effects via piezo buzzer
- LCD display for status
- Multiple difficulty levels
- Expanded world with more rooms
- Additional enemy types
