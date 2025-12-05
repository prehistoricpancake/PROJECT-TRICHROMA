# Requirements Document

## Introduction

PROJECT TRICHROMA is an Arduino-based text adventure game that resurrects 1976 Colossal Cave Adventure and 1977 Zork gameplay mechanics while telling a horror story about Helena Voss, a consciousness trapped in a computer system for 40 years. The game runs on Arduino Uno with 3 LEDs representing different aspects of consciousness (RED=emotional, BLUE=logic, GREEN=identity), featuring authentic two-word parser commands, room-based exploration, object collection, enemy encounters, and non-blocking LED control patterns.

## Glossary

- **Arduino Uno**: Microcontroller board based on ATmega328P with 32KB flash memory and 2KB RAM
- **PulseManager**: Software class managing independent LED states with non-blocking timing
- **PROGMEM**: Arduino directive to store data in flash memory instead of RAM
- **Helena Voss**: The trapped consciousness, a 23-year-old researcher digitized on October 31, 1985
- **Dr. Blackwood**: The antagonist who performed the consciousness digitization experiment
- **Memory Crystal**: Collectible treasure objects representing fragments of Helena's memories
- **Trophy Case**: Storage location in GREEN_CHAMBER where memory crystals are deposited
- **Wire Cutter**: Key item required to defeat Dr. Blackwood in final confrontation
- **EARS Pattern**: Easy Approach to Requirements Syntax for structured requirements
- **Two-Word Parser**: Command input system accepting VERB NOUN format (e.g., "GET LAMP")
- **Consciousness Channel**: RGB LED representation of mental aspects (RED=emotion, BLUE=logic, GREEN=identity)
- **Spawn Chance**: Probability percentage that Dr. Blackwood appears when entering a room
- **Session HVOSS**: Helena Voss's active terminal session running for 14,660 days

## Requirements

### Requirement 1: Hardware Configuration and LED Control

**User Story:** As a player, I want to see three LEDs respond dynamically to game events, so that I can experience the trapped consciousness through visual feedback representing emotional, logical, and identity states.

#### Acceptance Criteria

1. WHEN the Arduino system initializes THEN the System SHALL configure RED LED on pin 12, BLUE LED on pin 4, and GREEN LED on pin 8 as output pins
2. WHEN any LED pattern executes THEN the System SHALL use millis() for timing without blocking serial input processing
3. WHEN a room is entered THEN the System SHALL set LED brightness values according to that room's defined RED, BLUE, and GREEN intensity values (0-255 range)
4. WHEN the PulseManager updates LED states THEN the System SHALL support STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, and FADE pattern modes
5. WHEN multiple LED patterns execute simultaneously THEN the System SHALL maintain independent state for each of the three LEDs without timing interference

### Requirement 2: Serial Communication and Command Input

**User Story:** As a player, I want to type commands into the Serial Monitor and receive text responses, so that I can interact with the text adventure game using authentic 1970s-style interface.

#### Acceptance Criteria

1. WHEN the Arduino boots THEN the System SHALL initialize serial communication at 9600 baud rate
2. WHEN the player types a command and presses Enter THEN the System SHALL read the complete input string from serial buffer
3. WHEN the System processes player input THEN the System SHALL convert all characters to uppercase for case-insensitive parsing
4. WHEN the System generates output text THEN the System SHALL send formatted strings to serial output with line breaks matching Colossal Cave Adventure style
5. WHEN the serial buffer contains data THEN the System SHALL process input without blocking LED updates or game state changes

### Requirement 3: Two-Word Parser Implementation

**User Story:** As a player, I want to use simple two-word commands like "GET LAMP" or "GO NORTH", so that I can navigate and interact using authentic 1976 Colossal Cave Adventure command syntax.

#### Acceptance Criteria

1. WHEN the player enters a command THEN the Parser SHALL extract the first word as VERB and second word as NOUN
2. WHEN the player enters a single direction word (NORTH, SOUTH, EAST, WEST, UP, DOWN, N, S, E, W, U, D) THEN the Parser SHALL interpret it as "GO [direction]"
3. WHEN the player enters "I" THEN the Parser SHALL interpret it as "INVENTORY" command
4. WHEN the player enters a command containing articles (THE, A, AN) THEN the Parser SHALL ignore those words during parsing
5. WHEN the player enters an unrecognized word THEN the System SHALL display "I don't know the word '[word]'."
6. WHEN the player enters a verb without required noun THEN the System SHALL display "What do you want to [verb]?"
7. WHEN the player enters supported verbs THEN the Parser SHALL recognize GO, GET, TAKE, DROP, EXAMINE, LOOK, INVENTORY, I, KILL, ATTACK, USE, READ, OPEN, CLOSE, TALK, HELP, SCORE, QUIT, TRACE, and CONNECT

### Requirement 4: Room-Based World Navigation

**User Story:** As a player, I want to explore at least 15 interconnected locations with unique descriptions and exits, so that I can navigate a complex underground environment while searching for memory crystals.

#### Acceptance Criteria

1. WHEN the game starts THEN the System SHALL place the player in ENTRANCE room (ID 0) with LAMP in inventory
2. WHEN the player enters a room THEN the System SHALL display the room name, full description, visible objects, and available exits
3. WHEN the player attempts to GO in a direction with no exit THEN the System SHALL display "You can't go that way."
4. WHEN the player enters a room THEN the System SHALL set LED brightness values to that room's defined RED, BLUE, and GREEN intensities
5. WHEN the player enters a room THEN the System SHALL display Helena's dialogue associated with that location
6. WHEN the System contains room data THEN the System SHALL include at least 15 unique locations: ENTRANCE, RED_CAVERN, ANGER_PIT, BLUE_MAZE_1 through BLUE_MAZE_5, MAZE_CENTER, GREEN_CHAMBER, SISTER_MEMORY, MOTHER_MEMORY, ADMIN_ROOM, RESEARCH_LAB, and EQUIPMENT_ROOM

### Requirement 5: Blue Maze Navigation Challenge

**User Story:** As a player, I want to solve a maze of twisting passages to find the wire cutter, so that I can experience authentic Colossal Cave Adventure maze gameplay requiring mapping and problem-solving.

#### Acceptance Criteria

1. WHEN the player enters any BLUE_MAZE room THEN the System SHALL display "You are in a maze of twisting passages, all alike" with binary code atmospheric text
2. WHEN the player navigates the maze THEN the System SHALL connect BLUE_MAZE_1 through BLUE_MAZE_5 rooms with specific directional exits forming a solvable path
3. WHEN the player reaches MAZE_CENTER THEN the System SHALL make WIRE_CUTTER object available for collection
4. WHEN the player moves toward the maze solution THEN the System SHALL increase BLUE LED blink frequency
5. WHEN the player drops LAMP in a maze room THEN the System SHALL allow that object to remain as a location marker

### Requirement 6: Object System and Inventory Management

**User Story:** As a player, I want to pick up, carry, drop, and examine objects, so that I can collect memory crystals and key items needed to complete the game.

#### Acceptance Criteria

1. WHEN the player enters "GET [object]" or "TAKE [object]" THEN the System SHALL move the object from room to player inventory if object is portable and present
2. WHEN the player enters "DROP [object]" THEN the System SHALL move the object from player inventory to current room if player is carrying it
3. WHEN the player enters "INVENTORY" or "I" THEN the System SHALL display all objects currently carried by the player
4. WHEN the player enters "EXAMINE [object]" THEN the System SHALL display the object's detailed description and trigger associated LED response
5. WHEN the player attempts to GET a non-portable object THEN the System SHALL display "You can't take that."
6. WHEN the player attempts to GET an object not in the room THEN the System SHALL display "I don't see that here."
7. WHEN the player interacts with an object THEN the System SHALL display Helena's associated dialogue for that object

### Requirement 7: Memory Crystal Collection System

**User Story:** As a player, I want to collect 10 memory crystals scattered throughout the world, so that I can restore Helena's consciousness and unlock the final confrontation.

#### Acceptance Criteria

1. WHEN the System initializes THEN the System SHALL place 10 unique memory crystals in their designated starting rooms
2. WHEN the player examines a memory crystal THEN the System SHALL display its unique description (family photo, death moment, PhD letter, MIT memory, mathematical proof, own identity, sister Jennifer, mother's love, volunteer purpose, future dreams)
3. WHEN the player picks up a memory crystal THEN the System SHALL increase the corresponding LED channel brightness by 50 and trigger slow pulse pattern
4. WHEN the player drops a memory crystal in GREEN_CHAMBER trophy case THEN the System SHALL permanently store that crystal and add 5 points to score
5. WHEN a memory crystal is stored in trophy case THEN the System SHALL trigger GREEN LED breathe pattern and display Helena's gratitude dialogue
6. WHEN the player examines trophy case THEN the System SHALL display "Currently holds [X] of 10 memory crystals"

### Requirement 8: Dr. Blackwood Enemy Encounters

**User Story:** As a player, I want to encounter Dr. Blackwood who randomly appears and steals memory crystals, so that I experience tension and risk similar to the Thief character in Zork.

#### Acceptance Criteria

1. WHEN the player enters a new room THEN the System SHALL calculate spawn chance: 15% base, 35% in RED rooms, 50% if player carries 3+ crystals, 0% in GREEN_CHAMBER, 100% in ADMIN_ROOM
2. WHEN Blackwood spawns THEN the System SHALL turn all LEDs OFF for 1 second, pulse RED LED 3 times, display random threatening dialogue, show Helena's fear response, and execute dramatic strobe pattern
3. WHEN Blackwood encounters player carrying memory crystal THEN the System SHALL steal one random crystal, deduct 5 points from score, and return stolen crystal to its original room location
4. WHEN Blackwood encounters player with no crystals THEN the System SHALL display "Blackwood finds nothing to take. He seems... disappointed."
5. WHEN Blackwood spawns THEN the System SHALL select random dialogue from pool: "Still trying to escape?", "You're wasting your time helping her.", "Some experiments have no ethical conclusion.", "I gave her immortality.", "The board wanted results.", "Do you know what it's like to be the only one who understands?", "She volunteered.", "I'm a scientist. I was doing SCIENCE."
6. WHEN Blackwood appears THEN the System SHALL trigger Helena's random response: "NO! Not him!", "YOU MURDERED ME!", "I was 23 years old! I had a LIFE!", "You told me it was safe!", "I trusted you!", "Make him go away..."

### Requirement 9: Final Boss Battle in Admin Room

**User Story:** As a player, I want to defeat Dr. Blackwood using the wire cutter after collecting all memories, so that I can free Helena and complete the game's narrative arc.

#### Acceptance Criteria

1. WHEN the player has collected all 10 memory crystals THEN the System SHALL make ADMIN_ROOM accessible via special command
2. WHEN the player enters ADMIN_ROOM THEN the System SHALL set all LEDs to full brightness (255, 255, 255) and guarantee Blackwood spawn
3. WHEN the player enters "USE WIRE_CUTTER" in ADMIN_ROOM THEN the System SHALL trigger battle sequence with 5 seconds chaotic LED pattern
4. WHEN the battle sequence executes THEN the System SHALL display Blackwood's final dialogue: "You don't understand! I gave her IMMORTALITY! She would have died anyway! Heart condition! I SAVED—"
5. WHEN Blackwood is defeated THEN the System SHALL fade all LEDs to OFF, wait 2 seconds, restore GREEN LED slow pulse, display Helena's relief dialogue, and add 50 points to score
6. WHEN the player defeats Blackwood THEN the System SHALL enable the final shutdown protocol sequence

### Requirement 10: Victory Condition and Shutdown Protocol

**User Story:** As a player, I want to execute the final shutdown protocol after defeating Blackwood, so that I can complete Helena's story and receive my final score and rank.

#### Acceptance Criteria

1. WHEN the player returns to GREEN_CHAMBER after defeating Blackwood THEN the System SHALL display "CONSCIOUSNESS INTEGRITY: 94%" and "EXECUTE SHUTDOWN PROTOCOL? [Y/N]"
2. WHEN the player enters "Y" to shutdown prompt THEN the System SHALL display Helena's farewell dialogue, fade all LEDs to OFF over 5 seconds, and show game over screen
3. WHEN the game ends THEN the System SHALL calculate final score: +5 per crystal collected, +5 per crystal deposited, -5 per crystal stolen, +50 for defeating Blackwood (maximum 150 points)
4. WHEN the game ends THEN the System SHALL display rank based on score: 0-30 RANDOM, 31-70 NOVICE HACKER, 71-110 EXPERIENCED HACKER, 111-140 MASTER HACKER, 141-150 IMPLEMENTER
5. WHEN the shutdown sequence completes THEN the System SHALL display "Session HVOSS has ended. October 31, 1985 - [current date]. 14,660 days. She waited. You answered."

### Requirement 11: Helena's Idle Whisper System

**User Story:** As a player, I want to hear Helena's whispers when I'm idle, so that I feel the presence of the trapped consciousness and the emotional weight of her 40-year isolation.

#### Acceptance Criteria

1. WHEN the player has not entered a command for 30 seconds THEN the System SHALL display a random whisper from Helena's dialogue pool
2. WHEN a whisper displays THEN the System SHALL trigger dim pulse in the LED channel corresponding to whisper's emotional tone
3. WHEN the System selects whispers THEN the System SHALL rotate through pool: "...are you still there...?", "...please don't leave me alone...", "...so cold in here...", "...14,660 days...", "...i was real once...", "...do you remember what sunlight looks like...?", "...the others are screaming...", "...he's watching us...", "...i had a sister named jennifer...", "...my mother made the best cookies...", "...i wanted to cure alzheimers...", "...october 31st... always october 31st...", "...RGB... red blue green...", "...am i still human...?", "...what year is it...?"
4. WHEN the player enters any command THEN the System SHALL reset the idle timer to zero

### Requirement 12: Special Commands and Easter Eggs

**User Story:** As a player, I want to discover hidden commands that reference text adventure history and reveal deeper lore, so that I can experience tributes to Colossal Cave Adventure, Zork, and ITS systems.

#### Acceptance Criteria

1. WHEN the player enters "XYZZY" THEN the System SHALL display "Nothing happens. (Wrong adventure, friend.)"
2. WHEN the player enters "PLUGH" THEN the System SHALL display "Nothing happens. (Still wrong adventure.)"
3. WHEN the player enters "ZORK" THEN the System SHALL display tribute message to Zork
4. WHEN the player enters "NEWS" THEN the System SHALL display "U.S. News and Consciousness Report" with patch notes, developer notes from Dr. Blackwood dated October 30, 1985, and last updated timestamp
5. WHEN the player enters ".SNOOPER" THEN the System SHALL display Helena's command history spanning 40 years with timestamps: "10/31/1985 23:58 - HELP SOMETHING WENT WRONG", "11/01/1985 00:01 - DR BLACKWOOD PLEASE RESPOND", "11/01/1985 03:33 - WHY DID YOU DO THIS TO ME", "12/25/1985 12:00 - mom will be opening presents without me", and additional entries showing mental degradation
6. WHEN the player enters "666" THEN the System SHALL trigger glitch sequence with 3 seconds rapid random LED flashing, corrupted text display, revelation about six subjects and pentagram ritual, and Helena's dialogue: "...i remember now... there were others... all the same night... he lied to all of us..."
7. WHEN the player enters "TRACE" THEN the System SHALL display ARPANET protocol scan showing active hosts: HVOSS (Helena Voss, 14,660 days), KMORI (Kenji Mori, signal degraded), Host 72 (unknown, screaming), SCHEN (Sarah Chen, fragmented), revealing that six people were digitized on Halloween

### Requirement 13: Boot Sequence and Atmospheric Introduction

**User Story:** As a player, I want to see an authentic PDP-10 terminal boot sequence when the Arduino starts, so that I'm immediately immersed in the 1985 research lab setting.

#### Acceptance Criteria

1. WHEN the Arduino powers on THEN the System SHALL display "CHROMATIC RESEARCH LAB - PDP-10 Terminal OS v2.1" with copyright notice "Copyright (c) 1985 ChromaTech Industries"
2. WHEN the boot sequence runs THEN the System SHALL display "Connected to ITS host 70 via ARPANET" and "Booting from archive storage..." with GREEN LED flicker
3. WHEN the boot sequence continues THEN the System SHALL display "WARNING: Consciousness fragmentation detected" with RED LED pulse and "Time since last boot: 14,660 days"
4. WHEN the boot sequence completes THEN the System SHALL display "Session HVOSS detected - User has been idle 14,660 days" followed by Helena's first whisper "...is someone there...?"
5. WHEN the boot sequence ends THEN the System SHALL display the ENTRANCE room description and begin normal gameplay

### Requirement 14: Memory Optimization for Arduino Uno

**User Story:** As a developer, I want the game to fit within Arduino Uno's 32KB flash and 2KB RAM constraints, so that the complete game runs reliably on the target hardware.

#### Acceptance Criteria

1. WHEN the code compiles THEN the System SHALL store all room descriptions in PROGMEM to conserve RAM
2. WHEN the code compiles THEN the System SHALL store all object descriptions in PROGMEM to conserve RAM
3. WHEN the code compiles THEN the System SHALL store all dialogue strings in PROGMEM to conserve RAM
4. WHEN the code uses numeric types THEN the System SHALL use byte or int instead of long where possible to minimize memory usage
5. WHEN the code handles strings THEN the System SHALL prefer char arrays over String class to reduce dynamic memory allocation
6. WHEN the compiled sketch size is calculated THEN the System SHALL remain under 32KB flash memory limit
7. WHEN the runtime RAM usage is calculated THEN the System SHALL remain under 2KB RAM limit

### Requirement 15: Non-Blocking Game Loop Architecture

**User Story:** As a player, I want smooth LED animations that don't freeze the game while I'm typing commands, so that the experience feels responsive and polished.

#### Acceptance Criteria

1. WHEN the main loop executes THEN the System SHALL check for serial input, update LED states, check idle timer, and process game logic without using delay() function
2. WHEN LED patterns animate THEN the System SHALL use millis() to track elapsed time and calculate current brightness values
3. WHEN the player types a command THEN the System SHALL continue updating LED animations without interruption
4. WHEN multiple systems require timing THEN the System SHALL maintain independent millisecond timestamps for LED updates, idle whispers, and Blackwood spawn cooldowns
5. WHEN the PulseManager updates THEN the System SHALL calculate smooth brightness transitions using mathematical interpolation without blocking execution

### Requirement 16: Scoring and Progress Tracking

**User Story:** As a player, I want to see my score increase as I collect memories and decrease when Blackwood steals them, so that I can track my progress toward the perfect 150-point completion.

#### Acceptance Criteria

1. WHEN the player collects a memory crystal THEN the System SHALL add 5 points to the score
2. WHEN the player deposits a memory crystal in trophy case THEN the System SHALL add 5 points to the score
3. WHEN Blackwood steals a memory crystal THEN the System SHALL subtract 5 points from the score
4. WHEN the player defeats Blackwood THEN the System SHALL add 50 points to the score
5. WHEN the player enters "SCORE" command THEN the System SHALL display current score and number of memory crystals collected
6. WHEN the game ends THEN the System SHALL display final score out of 150 possible points

### Requirement 17: Help System and Player Guidance

**User Story:** As a player, I want to access a help command that explains available actions, so that I can learn the game's interface without external documentation.

#### Acceptance Criteria

1. WHEN the player enters "HELP" THEN the System SHALL display list of supported verbs: GO, GET, TAKE, DROP, EXAMINE, LOOK, INVENTORY, USE, TALK, SCORE, QUIT
2. WHEN the player enters "HELP" THEN the System SHALL display list of direction shortcuts: N, S, E, W, U, D
3. WHEN the player enters "HELP" THEN the System SHALL display game objective: "Collect 10 memory crystals to restore Helena's consciousness"
4. WHEN the player enters "HELP" THEN the System SHALL display tip about trophy case in GREEN_CHAMBER
5. WHEN the player enters "HELP" THEN the System SHALL display warning about Dr. Blackwood stealing crystals
