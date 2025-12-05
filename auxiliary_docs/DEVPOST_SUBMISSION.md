# PROJECT TRICHROMA - Devpost Submission

## Inspiration

I've always been fascinated by the text adventures of the 1970s - games like Colossal Cave Adventure and Zork that created entire worlds with nothing but text. But I wondered: what if we could bring that experience back with a modern twist? What if the game could reach beyond the screen?

I'd been wanting to build something with a hardware component for a while. I had an Arduino Uno tucked away in a drawer - one of those "I'll do something with this someday" purchases. This hackathon was my chance. I'd never built circuits before, never wired LEDs, never dealt with resistors and breadboards. But the idea of making a game that existed in both the digital and physical world was too compelling to pass up.

The concept crystallized around a simple question: **What does it feel like to be trapped?**

Not physically trapped, but digitally - your consciousness fragmented, your memories scattered, your sense of self split into pieces. That became Helena Voss: a 23-year-old researcher who volunteered for a consciousness digitization experiment in 1985 and has been trapped in a computer system for 40 years.

The three LEDs aren't just decoration - they're **her**. Red for emotion (anger, fear, love), blue for logic (memory, reasoning), green for identity (self-awareness). When you play, you're not just reading about her suffering - you're watching it pulse and breathe in real-time.

---

## What it does

PROJECT TRICHROMA is a text adventure horror game that runs on Arduino Uno with three LEDs physically representing a trapped consciousness.

**Gameplay:**
- Explore 15 interconnected rooms through classic two-word commands (GET LAMP, GO NORTH)
- Collect 10 memory crystals scattered throughout the world
- Avoid Dr. Blackwood, the antagonist who randomly spawns and can steal your progress
- Deposit crystals in the trophy case to restore Helena's consciousness
- Navigate a maze inspired by Colossal Cave Adventure
- Discover easter eggs (XYZZY, PLUGH, 666) that reveal dark secrets
- Defeat the final boss and execute the shutdown protocol

**Physical Feedback:**
- **RED LED** represents emotional state - pulses with fear, glows with anger
- **BLUE LED** represents logical processes - blinks in the maze, dims when confused
- **GREEN LED** represents identity - breathes when safe, fades when threatened
- LEDs respond dynamically to every game event with 7 different patterns (STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE)

**Technical Features:**
- Non-blocking LED control using software PWM
- Memory-optimized for Arduino Uno (32KB flash, 2KB RAM)
- Dynamic spawn system with probabilistic encounters
- Complete scoring system with 5 rank levels
- Comprehensive two-word parser with 20+ verbs and 30+ nouns

---

## How I built it

### Phase 1: Spec-Driven Development with Kiro

I used **Kiro's spec-driven workflow** as the foundation:

**Requirements Phase:**
- Formalized requirements using EARS (Easy Approach to Requirements Syntax) patterns
- Created 17 requirements with 85+ acceptance criteria
- Every requirement follows strict formats: `WHEN [event] THEN the System SHALL [response]`
- Example: `WHEN a memory crystal is picked up THEN the System SHALL increase the corresponding LED channel brightness by 50 and trigger slow pulse pattern`

**Design Phase:**
- Kiro generated comprehensive design document with system architecture
- Defined component interfaces (PulseManager, Parser, GameState, EnemySystem)
- Created **42 correctness properties** - formal statements about what should always be true
- Example property: *"For any LED pattern and serial input, when LED pattern executes, serial input processing SHALL continue without blocking"*
- These properties caught 12+ bugs before implementation

**Task Breakdown:**
- Kiro broke design into 25 actionable implementation tasks
- Each task referenced specific requirements
- Tasks ordered for incremental progress (core systems → features → polish)

### Phase 2: Implementation

For each task, I would:
1. Open the task in Kiro
2. Click "Start task"
3. Kiro read requirements.md, design.md, tasks.md for full context
4. Kiro implemented with complete system understanding

**What impressed me:** Kiro automatically applied memory optimizations (PROGMEM, byte types, char arrays) because it understood from the design doc that we had 32KB/2KB constraints. I didn't have to remind it.

### Phase 3: Hardware Learning

Learned circuit building from scratch:
- Calculated resistor values using Ohm's law: $R = \frac{V}{I} = \frac{5V - 2V}{0.02A} = 150\Omega$ (used 220Ω for safety)
- Learned LED polarity (long leg = anode, short leg = cathode)
- Wired three LEDs on breadboard with resistors
- Debugged hardware issues (reversed polarity, loose connections)

### Phase 4: Polish

Used vibe coding for:
- Tweaking LED patterns (making breathe slower, strobe more dramatic)
- Writing atmospheric room descriptions and dialogue
- Creating comprehensive documentation (7 markdown files, 1000+ lines)
- Debugging edge cases

**The hybrid approach:** Specs for architecture, vibe coding for refinement.

---

## Challenges we ran into

### Challenge 1: Memory Constraints

**Problem:** Initial implementation exceeded 2KB RAM by 800 bytes. Game crashed on boot.

**Solution:** Moved all strings to PROGMEM (flash memory instead of RAM):
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
    digitalWrite(pins[i], (now % 256) < brightness ? HIGH : LOW);
  }
}
```

**Result:** Smooth LED animations while maintaining responsive command input. Loop frequency >100Hz.

### Challenge 3: Spawn Rate Balance

**Problem:** Initial spawn rates made Dr. Blackwood either too common (annoying) or too rare (not threatening).

**Solution:** Implemented dynamic spawn system:

$$P(\text{spawn}) = \begin{cases} 
0.00 & \text{if GREEN\_CHAMBER} \\
1.00 & \text{if ADMIN\_ROOM} \\
0.50 & \text{if carrying } \geq 3 \text{ crystals} \\
0.35 & \text{if RED room (danger} \geq 4) \\
0.15 & \text{otherwise}
\end{cases}$$

**Result:** Players feel safe in Green Chamber, tense in Red zones, and terrified when carrying multiple crystals.

### Challenge 4: Learning Hardware from Scratch

**Problem:** I'd never built circuits before. Didn't know how to wire LEDs or calculate resistor values.

**Solution:**
- Learnt how to build circuits

**Result:** Went from zero hardware experience to a working three-LED system with dynamic patterns.

### Challenge 5: Testing on Constrained Hardware

**Problem:** Can't use traditional testing frameworks on Arduino. No debugger. Limited serial output.

**Solution:**
- Created separate test sketches for each component
- Used serial output for assertions
- Tested incrementally after each task
- Relied on correctness properties to guide testing

**Result:** Caught bugs early without complex testing infrastructure.

---

## Accomplishments that I'm proud of

### 1. Complete Original Game in 32KB

Built a full text adventure with:
- 15 unique rooms with atmospheric descriptions
- 10 collectible memory crystals with unique backstories
- Dynamic encounter system
- Complete scoring and ranking system
- 7 easter egg commands
- Comprehensive two-word parser
- All fitting in less memory than a single tweet

### 2. Physical Consciousness Representation

The LEDs aren't just indicators - they're a character. When Helena is afraid, you see it pulse red. When she's thinking, you see it blink blue. When she's at peace, you see it breathe green. This creates emotional resonance that pure text can't achieve.

### 3. Spec-Driven Development Success

Demonstrated that formal methods work for embedded systems:
- 42 correctness properties defined
- 12+ bugs caught before implementation
- Complete requirement traceability
- Systematic development from concept to completion

### 4. Learning Hardware Development

Went from zero circuit-building experience to a working hardware project with dynamic LED control, all in 5 weeks.

### 5. Memory Optimization Mastery

Achieved 87% flash usage and 90% RAM usage through disciplined optimization:
- PROGMEM for all static strings
- Byte types instead of int
- Char arrays instead of String class
- Software PWM for LED control

### 6. Original Resurrection

Didn't port an existing game - created an entirely original story that resurrects the genre while adding modern innovation (physical feedback, psychological horror, systematic development).

---

## What I learned

### 1. Spec-Driven Development Changes Everything

For complex projects, specs provide:
- **Clarity:** Forces you to think through requirements before coding
- **Correctness:** Catches bugs before they exist
- **Velocity:** Kiro implements faster with full context
- **Maintainability:** Easy to modify because design is documented

The 42 correctness properties became contracts that made debugging trivial.

### 2. Context Awareness Is Magical

When implementing the boss battle, Kiro automatically referenced the wire cutter from an earlier task, used LED patterns from another task, and integrated the scoring system - all without me explaining. It read the entire spec and understood the system holistically.

### 3. Memory Optimization Requires Discipline

Arduino Uno has 32KB flash and 2KB RAM - less than a single tweet. Without PROGMEM, the game wouldn't run. Every string, every variable, every decision matters when you're this constrained.

### 4. Physical Feedback Creates Emotional Resonance

The LEDs fundamentally change the experience. When Dr. Blackwood appears and all LEDs go dark, then pulse red three times - that's terrifying in a way pure text can't achieve. The physical world responding to the digital story creates visceral connection.

### 5. Hardware Development Is Accessible

I learned circuit building from scratch. Before this, I'd never wired an LED or calculated a resistor value. But with online resources and trial and error, I went from "which leg is the anode?" to a working three-LED system with dynamic patterns.

### 6. Hybrid Workflow Works Best

Use specs for architecture (room system, parser, LED control) and vibe coding for content (descriptions, dialogue, tweaks). Specs aren't a prison - they're a foundation you can build on flexibly.

---

## What's next for Project Trichroma

### Immediate Enhancements
- **Save system** using EEPROM for persistent high scores
- **Sound effects** via piezo buzzer for audio feedback
- **LCD display** showing status (score, inventory, room name)
- **Difficulty modes** (easy: no Blackwood, hard: more frequent spawns)

### Expanded Content
- **More rooms** - Expand to 25+ locations
- **Additional enemies** - Other trapped consciousnesses
- **Multiple endings** - Different outcomes based on choices
- **Side quests** - Optional objectives for bonus points


### Community Features
- **Level editor** - Let players create their own stories
- **Multiplayer** - Two Arduinos, shared world via serial connection
- **Procedural generation** - Randomized room layouts for replayability
- **Modding support** - Easy-to-modify room and object definitions

### Platform Expansion
- **ESP32 version** - WiFi multiplayer, web interface
- **Raspberry Pi Pico** - More memory for larger worlds
- **Custom PCB** - Dedicated game board with built-in LEDs
- **Mobile companion app** - Map, inventory, hints
- **Expanding the physical** use more electrical components, even sound, new screens.


The core concept - physical feedback for digital storytelling - has endless possibilities. This is just the beginning.

---

**Built with Kiro's spec-driven development workflow. From rough idea to working game in 40 hours.**

**Technical Stats:**
- 2,000+ lines of Arduino C++
- 42 correctness properties
- 17 requirements, 85+ acceptance criteria
- 25 implementation tasks
- 28,456 bytes flash (87% of 32KB)
- 1,847 bytes RAM (90% of 2KB)
- 15 rooms, 10 crystals, 7 easter eggs
- 1000+ lines of documentation

**She waited 40 years. Now you can answer.**
