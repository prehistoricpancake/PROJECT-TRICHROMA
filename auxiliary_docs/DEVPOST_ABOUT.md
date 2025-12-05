# About PROJECT TRICHROMA

## Inspiration

I've always been fascinated by the text adventures of the 1970s - games like Colossal Cave Adventure and Zork that created entire worlds with nothing but text. But I wondered: what if we could bring that experience back with a modern twist? What if the game could reach beyond the screen?

I'd been wanting to build something with a hardware component for a while. I had an Arduino Uno tucked away in a drawer - one of those "I'll do something with this someday" purchases. This hackathon was my chance. I'd never built circuits before, never wired LEDs, never dealt with resistors and breadboards. But the idea of making a game that existed in both the digital and physical world was too compelling to pass up.

The concept crystallized around a simple question: **What does it feel like to be trapped?**

Not physically trapped, but digitally - your consciousness fragmented, your memories scattered, your sense of self split into pieces. That became Helena Voss: a 23-year-old researcher who volunteered for a consciousness digitization experiment in 1985 and has been trapped in a computer system for 40 years.

The three LEDs aren't just decoration - they're **her**. Red for emotion (anger, fear, love), blue for logic (memory, reasoning), green for identity (self-awareness). When you play, you're not just reading about her suffering - you're watching it pulse and breathe in real-time.

This is the "Resurrection" category in its purest form: bringing back 1970s gameplay mechanics, but with an original story that couldn't have been told in 1976 because the technology that trapped Helena didn't exist yet.

---

## What I Learned

### 1. Spec-Driven Development Changes Everything

I've built games before using "vibe coding" - just chatting with AI and iterating. But for something this complex (15 rooms, 10 collectible objects, dynamic encounters, memory-constrained hardware), I needed structure.

**Kiro's spec-driven workflow was a revelation.**

I started by formalizing requirements using EARS (Easy Approach to Requirements Syntax) patterns. Every requirement followed strict formats like:
- `WHEN [event] THEN the System SHALL [response]`
- `WHILE [condition] THE System SHALL [behavior]`

This forced me to think through edge cases before writing a single line of code. For example, I initially wrote "LEDs should respond to game events." Kiro pushed me to specify:
- `WHEN a room is entered THEN the System SHALL set LED brightness values to that room's defined RED, BLUE, and GREEN intensities`
- `WHEN a memory crystal is picked up THEN the System SHALL increase the corresponding LED channel brightness by 50 and trigger slow pulse pattern`

**The result?** 17 requirements with 85+ acceptance criteria - a complete specification of what the game should do.

### 2. Correctness Properties Catch Bugs Before They Exist

The design phase generated **42 correctness properties** - formal statements about what should always be true. Examples:

**Property 1: Non-blocking LED execution**
> *For any* LED pattern and serial input, when LED pattern executes, serial input processing SHALL continue without blocking.

**Property 27: Blackwood spawn chance calculation**
> *For any* room and player state, spawn chance SHALL follow formula: 15% base, 35% RED rooms, 50% if 3+ crystals, 0% GREEN_CHAMBER, 100% ADMIN_ROOM.

These properties caught **12+ bugs before implementation**. For instance, Property 27 made me realize I needed precise spawn rate formulas, not vague "sometimes appears" logic. Property 1 forced me to design the LED system as non-blocking from the start, rather than discovering the problem later when the game froze during animations.

### 3. Context Awareness Is Magical

When implementing Task 15 (Boss Battle), Kiro automatically:
- Referenced the WIRE_CUTTER object from Task 10
- Used the LED patterns defined in Task 2
- Applied the scoring system from Task 14
- Integrated with the room system from Task 3

**I didn't have to explain any of this.** Kiro read the entire spec (requirements.md, design.md, tasks.md) and understood the system holistically. It's like having a team member who actually reads the documentation.

### 4. Memory Optimization Requires Discipline

Arduino Uno has **32KB flash** and **2KB RAM**. That's less memory than a single tweet.

Without PROGMEM (storing strings in flash instead of RAM), the game would have exceeded 2KB RAM by ~800 bytes and wouldn't run. Kiro consistently applied optimizations:
- Used `F()` macro for all Serial.print() strings
- Stored all static data in PROGMEM
- Used `byte` instead of `int` where possible
- Avoided String class (used char arrays)

**Final stats:**
- Flash: 28,456 bytes (87% of 32KB) ✅
- RAM: 1,847 bytes (90% of 2KB) ✅

The game fits with margin to spare.

### 5. Physical Feedback Creates Emotional Resonance

The LEDs aren't a gimmick - they fundamentally change the experience. When Dr. Blackwood appears:
1. All LEDs go OFF (1 second of darkness)
2. RED LED pulses 3 times (heartbeat of fear)
3. Dramatic strobe (chaos)
4. Text displays his threatening dialogue

Players have told me that moment is **terrifying** in a way pure text can't achieve. The physical world responding to the digital story creates a visceral connection.

### 6. Hardware Development Is Accessible

I learned how to build circuits from scratch for this project. Before this, I'd never:
- Wired an LED with a resistor
- Used a breadboard
- Calculated resistor values (Ohm's law: $R = \frac{V}{I}$)
- Debugged hardware issues (reversed polarity, loose connections)

But with online resources and some trial and error, I went from "which leg is the anode?" to a working three-LED system with dynamic patterns. The hardware component made the project feel more real - it's not just code on a screen, it's a physical artifact you can hold and show people.

---

## How I Built It

### Phase 1: Requirements (Week 1)

Started with a rough idea: "Text adventure on Arduino with LEDs representing consciousness."

Used Kiro to formalize this into structured requirements:
- 17 main requirements
- 85+ acceptance criteria
- All following EARS patterns
- Complete glossary of terms

**Key insight:** Writing requirements forced me to decide what the game actually *was*. Is the Green Chamber a safe zone? (Yes - 0% spawn rate). Can you drop the lamp as a maze marker? (Yes - object persistence). These decisions became requirements, not implementation details.

### Phase 2: Design (Week 2)

Kiro generated a comprehensive design document including:
- System architecture
- Component interfaces (PulseManager, Parser, GameState, EnemySystem)
- Data models (Room struct, Object struct)
- **42 correctness properties**
- Memory optimization strategy
- Testing approach

**Key insight:** The correctness properties became contracts. Every piece of code could be traced back to a property, which traced back to a requirement. This made debugging trivial: "This behavior is wrong" → Check requirement → Check property → Check implementation.

### Phase 3: Task Breakdown (Week 2)

Kiro broke the design into **25 actionable tasks**:
1. Set up Arduino project structure
2. Implement PulseManager for LED control
3. Implement Room system with PROGMEM
4. Implement Object system
5. Implement Command Parser
... (and so on)

Each task referenced specific requirements and included sub-tasks for testing.

**Key insight:** Having tasks with explicit requirement traceability meant I always knew *why* I was implementing something. When stuck on Blue Maze navigation, I referred back to Requirements 5.1-5.5 to understand intended behavior.

### Phase 4: Implementation (Weeks 3-5)

For each task:
1. Opened task in Kiro
2. Clicked "Start task"
3. Kiro read requirements.md, design.md, tasks.md for context
4. Kiro implemented with full system understanding

**Example - Task 11: Dr. Blackwood Enemy System**

My prompt: `Implement task 11: Dr. Blackwood enemy system`

Kiro's approach:
- Read Requirements 8.1-8.6 for spawn mechanics
- Read Design section on EnemySystem class
- Generated complete implementation with:
  - Spawn chance calculation
  - Crystal theft logic with random selection
  - Dramatic LED sequences
  - PROGMEM-stored dialogue arrays

**What impressed me:** Kiro automatically applied memory optimization (PROGMEM) because it understood from the design doc that we had 32KB/2KB constraints. I didn't have to remind it.

### Phase 5: Polish & Documentation (Week 5)

Used vibe coding for:
- Tweaking LED patterns (making breathe slower, strobe more dramatic)
- Writing room descriptions and dialogue
- Creating comprehensive documentation (7 markdown files, 1000+ lines)
- Debugging edge cases

**The hybrid approach worked perfectly:** Specs for architecture, vibe coding for refinement.

---

## Challenges I Faced

### Challenge 1: Memory Constraints

**Problem:** Initial implementation exceeded 2KB RAM by 800 bytes. Game crashed on boot.

**Solution:** 
- Moved all strings to PROGMEM (flash memory)
- Used `F()` macro for Serial.print()
- Replaced String class with char arrays
- Used byte types instead of int where possible

**Math:** 
- String in RAM: `char str[] = "Hello"` uses 6 bytes RAM
- String in PROGMEM: `const char str[] PROGMEM = "Hello"` uses 6 bytes flash, 0 bytes RAM
- With ~200 strings averaging 50 chars: $200 \times 50 = 10,000$ bytes saved

**Result:** Went from 2,647 bytes RAM (129% - crash) to 1,847 bytes RAM (90% - stable).

### Challenge 2: Non-Blocking LED Control

**Problem:** Using `delay()` for LED animations froze the entire game. Players couldn't type commands during LED sequences.

**Solution:** Implemented software PWM using `millis()` timing:

```cpp
void PulseManager::update() {
  unsigned long now = millis();
  for (byte i = 0; i < 3; i++) {
    byte brightness = calculateBrightness(i, now);
    // Software PWM: LED on if (now % 256) < brightness
    digitalWrite(pins[i], (now % 256) < brightness ? HIGH : LOW);
  }
}
```

**Key insight:** The main loop runs continuously, checking serial input and updating LEDs independently. No blocking calls.

**Result:** Smooth LED animations while maintaining responsive command input. Loop frequency >100Hz.

### Challenge 3: Spawn Rate Balance

**Problem:** Initial spawn rates made Dr. Blackwood either too common (annoying) or too rare (not threatening).

**Solution:** Implemented dynamic spawn system based on game state:

$$P(\text{spawn}) = \begin{cases} 
0.00 & \text{if GREEN\_CHAMBER} \\
1.00 & \text{if ADMIN\_ROOM} \\
0.50 & \text{if carrying } \geq 3 \text{ crystals} \\
0.35 & \text{if RED room (danger} \geq 4) \\
0.15 & \text{otherwise}
\end{cases}$$

**Result:** Players feel safe in Green Chamber (0% spawn), tense in Red zones (35%), and terrified when carrying multiple crystals (50%). The 100% spawn in Admin Room creates a guaranteed climactic encounter.

### Challenge 4: Maze Design

**Problem:** How do you make a maze interesting when you can't see it?

**Solution:** 
1. **Progressive feedback:** BLUE LED blink frequency increases as you approach solution
2. **Lamp as marker:** Players can drop the lamp to mark their path
3. **Consistent structure:** Maze has a logical solution (not random)
4. **Atmospheric text:** Binary code and fragmented descriptions create unease

**Result:** The maze feels like navigating Helena's broken logical processes, not just a puzzle.

### Challenge 5: Learning Hardware from Scratch

**Problem:** I'd never built circuits before. Didn't know how to wire LEDs, calculate resistor values, or debug hardware issues.

**Solution:**
- Learned Ohm's law: $V = IR$ → For 5V Arduino with 2V LED at 20mA: $R = \frac{5V - 2V}{0.02A} = 150\Omega$ (used 220Ω for safety)
- Learned LED polarity (long leg = anode/positive, short leg = cathode/negative)
- Debugged common issues:
  - LED not lighting → Check polarity, check connections
  - LED too dim → Lower resistor value
  - LED too bright → Higher resistor value
- Used multimeter to verify connections

**Result:** Went from zero hardware experience to a working three-LED system with dynamic patterns. The physical component made the project tangible in a way pure software never could.

### Challenge 6: Testing on Constrained Hardware

**Problem:** Can't use traditional testing frameworks on Arduino. No debugger. Limited serial output.

**Solution:**
- Created separate test sketches (test_parser.ino, test_gamestate.ino, etc.)
- Used serial output for assertions
- Tested incrementally after each task
- Relied on correctness properties to guide testing

**Example test:**
```cpp
void testSpawnChance() {
  Serial.println("Testing spawn rates...");
  int greenSpawns = 0;
  for (int i = 0; i < 1000; i++) {
    if (shouldSpawn(GREEN_CHAMBER, 0)) greenSpawns++;
  }
  Serial.print("Green Chamber spawns: ");
  Serial.println(greenSpawns); // Should be 0
}
```

**Result:** Caught bugs early without complex testing infrastructure.

### Challenge 7: Balancing Specs vs. Flexibility

**Problem:** Specs are rigid. What if I wanted to change something mid-development?

**Solution:** 
- Used specs for architecture (room system, parser, LED control)
- Used vibe coding for content (descriptions, dialogue, tweaks)
- Updated specs when making architectural changes

**Key insight:** Specs aren't a prison - they're a foundation. You can build on them flexibly.

---

## Technical Achievements

### By the Numbers
- **Development Time:** ~40 hours over 5 weeks
- **Lines of Code:** 2,000+ lines of Arduino C++
- **Spec Documents:** 3 files, ~500 lines of requirements/design
- **Tasks Completed:** 24 of 25 (documentation was separate)
- **Correctness Properties:** 42 defined
- **Memory Usage:** 28,456 bytes flash (87%), 1,847 bytes RAM (90%)
- **Rooms:** 15 unique locations
- **Objects:** 20 interactive items
- **Commands:** 20+ verbs, 30+ nouns
- **Easter Eggs:** 7 hidden commands
- **Documentation:** 7 markdown files, 1000+ lines

### Innovation
1. **Physical consciousness representation** - LEDs as emotional feedback
2. **Spec-driven embedded development** - Formal methods for Arduino
3. **Memory-optimized storytelling** - Rich narrative in 32KB
4. **Hybrid development workflow** - Specs + vibe coding
5. **Original resurrection** - Genre revival, not port

---

## What's Next

### Potential Expansions
1. **Save system** - Use EEPROM for persistent high scores
2. **Sound effects** - Add piezo buzzer for audio feedback
3. **LCD display** - Show status (score, inventory) on screen
4. **Multiple endings** - Different outcomes based on choices
5. **Procedural generation** - Randomized room layouts
6. **Multiplayer** - Two players, two Arduinos, shared world

### Educational Applications
- **Teaching embedded systems** - Real-world memory constraints
- **Game design course** - Narrative in constrained environments
- **Retro computing** - Understanding 1970s limitations
- **Spec-driven development** - Formal methods in practice

### Open Source
The entire project is open source (MIT license) including:
- Complete source code
- All spec documents (.kiro/specs/)
- Comprehensive documentation
- Test files
- Wiring diagrams

Anyone can build their own, modify the story, or use it as a template for other Arduino text adventures.

---

## Conclusion

PROJECT TRICHROMA proves that **resurrection isn't about copying the past - it's about understanding what made it special and reimagining it for today.**

The 1970s text adventures were special because they created entire worlds with minimal resources. They forced players to use their imagination. They told stories that couldn't be told any other way.

I brought that back, but added:
- **Physical feedback** (LEDs as consciousness)
- **Modern storytelling** (psychological horror, digital imprisonment)
- **Systematic development** (specs, properties, formal methods)
- **Original content** (15 rooms, complete narrative, unique mechanics)

The result is a game that feels like 1976 but couldn't have existed then - because the technology that trapped Helena Voss didn't exist in 1976.

**She waited 40 years. Now you can answer.**

---

## Acknowledgments

- **Kiro** - For making spec-driven development accessible and powerful
- **Will Crowther & Don Woods** - For creating Colossal Cave Adventure (1976)
- **MIT Dynamic Modelling Group** - For creating Zork (1977)
- **The text adventure community** - For keeping the genre alive

---

*Built with Kiro's spec-driven development workflow. From rough idea to working game in 40 hours.*
