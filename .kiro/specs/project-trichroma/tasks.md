# Implementation Plan

- [x] 1. Set up Arduino project structure and core interfaces
  - Create main .ino sketch file with setup() and loop() functions
  - Define pin constants (RED_LED_PIN=12, BLUE_LED_PIN=4, GREEN_LED_PIN=8)
  - Initialize serial communication at 9600 baud
  - Set up random seed using analogRead(A0)
  - _Requirements: 1.1, 2.1, 13.1_

- [x] 2. Implement PulseManager class for non-blocking LED control
  - Create PulseManager class with Pattern enum (STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE, OFF)
  - Implement init() method to configure LED pins as outputs
  - Implement setPattern() for individual channel control
  - Implement update() method with software PWM using millis() timing
  - Implement calculateBrightness() for each pattern type using sine waves and interpolation
  - _Requirements: 1.2, 1.4, 1.5, 15.2, 15.5_

- [ ] 2.1 Write property test for non-blocking LED execution
  - **Property 1: Non-blocking LED execution**
  - **Validates: Requirements 1.2, 2.5, 15.2, 15.3**

- [ ]* 2.2 Write property test for independent LED channel state
  - **Property 3: Independent LED channel state**
  - **Validates: Requirements 1.5**

- [x] 3. Implement Room system with PROGMEM storage
  - Define Room struct with id, name, description, exits[6], LED values, dangerLevel, helenaDialogue
  - Create ROOMS[15] array in PROGMEM with all 15 room definitions
  - Implement helper function to read Room data from PROGMEM
  - Define room connections: ENTRANCE(0), RED_CAVERN(1), ANGER_PIT(2), BLUE_MAZE_1-5(3-7), MAZE_CENTER(8), GREEN_CHAMBER(9), SISTER_MEMORY(10), MOTHER_MEMORY(11), ADMIN_ROOM(12), RESEARCH_LAB(13), EQUIPMENT_ROOM(14)
  - _Requirements: 4.1, 4.2, 4.6, 14.1_

- [ ]* 3.1 Write property test for room LED state consistency
  - **Property 2: Room LED state consistency**
  - **Validates: Requirements 1.3, 4.4**

- [ ]* 3.2 Write property test for room information display completeness
  - **Property 9: Room information display completeness**
  - **Validates: Requirements 4.2**

- [x] 4. Implement Object system with PROGMEM storage
  - Define Object struct with id, name, description, location, flags bitfield, ledResponse, helenaDialogue
  - Create OBJECTS[20] array in PROGMEM including LAMP, 10 MEMORY_CRYSTALS, WIRE_CUTTER, TROPHY_CASE, TERMINAL, RESEARCH_NOTES
  - Implement helper functions to read Object data from PROGMEM
  - Define object flags: portable, treasure, in_inventory, examined, deposited
  - _Requirements: 6.1, 6.2, 7.1, 14.2_

- [ ]* 4.1 Write property test for portable object acquisition
  - **Property 15: Portable object acquisition**
  - **Validates: Requirements 6.1**

- [ ]* 4.2 Write property test for object drop mechanics
  - **Property 16: Object drop mechanics**
  - **Validates: Requirements 6.2**

- [x] 5. Implement Command Parser with two-word parsing
  - Define Verb enum (GO, GET, TAKE, DROP, EXAMINE, LOOK, INVENTORY, KILL, ATTACK, USE, READ, OPEN, CLOSE, TALK, HELP, SCORE, QUIT, TRACE, CONNECT, XYZZY, PLUGH, ZORK, NEWS, SNOOPER, GLITCH)
  - Define Noun enum (NORTH, SOUTH, EAST, WEST, UP, DOWN, object names)
  - Create Parser class with Command struct (verb, noun, valid)
  - Implement parse() method: convert to uppercase, remove articles, expand abbreviations
  - Implement matchVerb() and matchNoun() using string comparison
  - _Requirements: 3.1, 3.2, 3.3, 3.4, 3.7_

- [ ]* 5.1 Write property test for case-insensitive command parsing
  - **Property 4: Case-insensitive command parsing**
  - **Validates: Requirements 2.3**

- [ ]* 5.2 Write property test for two-word command extraction
  - **Property 5: Two-word command extraction**
  - **Validates: Requirements 3.1**

- [ ]* 5.3 Write property test for article filtering
  - **Property 6: Article filtering in commands**
  - **Validates: Requirements 3.4**

- [x] 6. Implement GameState manager
  - Create GameState class with currentRoom, inventory[8], inventoryCount, score, crystalsCollected, crystalsDeposited, blackwoodDefeated, gameOver, lastCommandTime, blackwoodCooldown
  - Implement init() to set starting state (ENTRANCE room, LAMP in inventory, score=0)
  - Implement changeRoom() to update current room and trigger LED changes
  - Implement addToInventory() and removeFromInventory() with 8-item limit
  - Implement updateScore() to modify score value
  - _Requirements: 4.1, 6.3, 16.1, 16.2, 16.3_

- [ ]* 6.1 Write property test for inventory display completeness
  - **Property 17: Inventory display completeness**
  - **Validates: Requirements 6.3**

- [x] 7. Implement core game commands (movement and observation)
  - Implement GO command: validate exit exists, change room, display new room, update LEDs, display Helena dialogue
  - Implement LOOK command: redisplay current room description
  - Implement EXAMINE command: display object description, trigger LED response, display Helena dialogue
  - Implement INVENTORY command: list all carried objects
  - _Requirements: 4.2, 4.3, 4.5, 6.3, 6.4_

- [ ]* 7.1 Write property test for invalid movement rejection
  - **Property 10: Invalid movement rejection**
  - **Validates: Requirements 4.3**

- [ ]* 7.2 Write property test for room-specific Helena dialogue
  - **Property 11: Room-specific Helena dialogue**
  - **Validates: Requirements 4.5**

- [x] 8. Implement object manipulation commands
  - Implement GET/TAKE command: check if object present, check if portable, add to inventory, update score if crystal
  - Implement DROP command: remove from inventory, place in current room, check for trophy case special handling
  - Implement error handling: "You can't take that.", "I don't see that here.", "You're carrying too much."
  - _Requirements: 6.1, 6.2, 6.5, 6.6, 7.3, 7.4_

- [ ]* 8.1 Write property test for non-portable object rejection
  - **Property 19: Non-portable object rejection**
  - **Validates: Requirements 6.5**

- [ ]* 8.2 Write property test for absent object rejection
  - **Property 20: Absent object rejection**
  - **Validates: Requirements 6.6**

- [x] 9. Implement memory crystal collection mechanics
  - Implement crystal pickup: increase corresponding LED channel by 50, trigger slow pulse, add 5 points
  - Implement trophy case detection: when DROP crystal in GREEN_CHAMBER, mark as deposited, add 5 points, trigger GREEN breathe pattern
  - Implement trophy case EXAMINE: display count of deposited crystals (X of 10)
  - Track crystalsCollected and crystalsDeposited in GameState
  - _Requirements: 7.3, 7.4, 7.5, 7.6_

- [ ]* 9.1 Write property test for memory crystal LED response
  - **Property 23: Memory crystal LED response**
  - **Validates: Requirements 7.3**

- [ ]* 9.2 Write property test for trophy case crystal storage
  - **Property 24: Trophy case crystal storage**
  - **Validates: Requirements 7.4**

- [ ]* 9.3 Write property test for trophy case state display
  - **Property 26: Trophy case state display**
  - **Validates: Requirements 7.6**

- [x] 10. Implement Blue Maze navigation system
  - Define maze room connections: BLUE_MAZE_1 → BLUE_MAZE_2 → ... → MAZE_CENTER
  - Implement maze description display with binary code atmospheric text
  - Implement BLUE LED blink frequency increase as player approaches solution
  - Place WIRE_CUTTER object in MAZE_CENTER
  - Allow LAMP to be dropped as location marker
  - _Requirements: 5.1, 5.2, 5.3, 5.4, 5.5_

- [ ]* 10.1 Write property test for maze room description consistency
  - **Property 12: Maze room description consistency**
  - **Validates: Requirements 5.1**

- [ ]* 10.2 Write property test for object persistence in maze
  - **Property 14: Object persistence in maze**
  - **Validates: Requirements 5.5**

- [x] 11. Implement Dr. Blackwood enemy system
  - Create EnemySystem class with shouldSpawn() and triggerEncounter() methods
  - Implement spawn chance calculation: 15% base, 35% RED rooms (dangerLevel≥4), 50% if 3+ crystals, 0% GREEN_CHAMBER, 100% ADMIN_ROOM
  - Implement encounter sequence: LEDs OFF 1 sec, RED pulse 3x, display random Blackwood dialogue, display Helena response, steal crystal if present, dramatic strobe 2 sec
  - Store Blackwood dialogue pool (7 messages) and Helena response pool (6 messages) in PROGMEM
  - Implement crystal theft: select random crystal from inventory, deduct 5 points, return crystal to original room
  - _Requirements: 8.1, 8.2, 8.3, 8.4, 8.5, 8.6_

- [ ]* 11.1 Write property test for Blackwood spawn calculation
  - **Property 27: Blackwood spawn chance calculation**
  - **Validates: Requirements 8.1**

- [ ]* 11.2 Write property test for Blackwood crystal theft
  - **Property 28: Blackwood crystal theft**
  - **Validates: Requirements 8.3**

- [x] 12. Implement Helena's idle whisper system
  - Create DialogueSystem class with displayWhisper() method
  - Store whisper pool (15 messages) in PROGMEM
  - Track lastCommandTime using millis()
  - Check if 30 seconds elapsed since last command
  - Display random whisper and trigger dim LED pulse in corresponding emotional channel
  - Reset timer on any command input
  - _Requirements: 11.1, 11.2, 11.3, 11.4_

- [ ]* 12.1 Write property test for idle whisper timing
  - **Property 33: Idle whisper timing**
  - **Validates: Requirements 11.1**

- [ ]* 12.2 Write property test for idle timer reset
  - **Property 36: Idle timer reset**
  - **Validates: Requirements 11.4**

- [x] 13. Implement special commands and easter eggs
  - Implement XYZZY command: display "Nothing happens. (Wrong adventure, friend.)"
  - Implement PLUGH command: display "Nothing happens. (Still wrong adventure.)"
  - Implement ZORK command: display tribute message to Zork
  - Implement NEWS command: display "U.S. News and Consciousness Report" with patch notes and Dr. Blackwood's developer notes
  - Implement .SNOOPER command: display Helena's 40-year command history with timestamps
  - Implement 666 command: trigger glitch sequence with 3-sec rapid LED flashing, corrupted text, revelation about six subjects
  - Implement TRACE command: display ARPANET protocol scan showing active hosts (HVOSS, KMORI, Host 72, SCHEN)
  - _Requirements: 12.1, 12.2, 12.3, 12.4, 12.5, 12.6, 12.7_

- [x] 14. Implement scoring system
  - Implement SCORE command: display current score and crystals collected
  - Track score changes: +5 per crystal collected, +5 per crystal deposited, -5 per crystal stolen, +50 for defeating Blackwood
  - Implement rank calculation: 0-30 RANDOM, 31-70 NOVICE HACKER, 71-110 EXPERIENCED HACKER, 111-140 MASTER HACKER, 141-150 IMPLEMENTER
  - Display rank at game end
  - _Requirements: 16.1, 16.2, 16.3, 16.4, 16.5, 16.6, 10.3, 10.4_

- [ ]* 14.1 Write property test for final score calculation
  - **Property 31: Final score calculation**
  - **Validates: Requirements 10.3**

- [ ]* 14.2 Write property test for rank assignment
  - **Property 32: Rank assignment by score**
  - **Validates: Requirements 10.4**

- [ ]* 14.3 Write property test for score command display
  - **Property 42: Score command display**
  - **Validates: Requirements 16.5**

- [x] 15. Implement final boss battle in ADMIN_ROOM
  - Make ADMIN_ROOM accessible only after collecting all 10 crystals
  - Set all LEDs to full brightness (255, 255, 255) when entering ADMIN_ROOM
  - Guarantee Blackwood spawn in ADMIN_ROOM
  - Implement USE WIRE_CUTTER command: trigger battle sequence with 5-sec chaotic LED pattern
  - Display Blackwood's final dialogue: "You don't understand! I gave her IMMORTALITY! She would have died anyway! Heart condition! I SAVED—"
  - Fade all LEDs to OFF, wait 2 seconds, restore GREEN LED slow pulse
  - Display Helena's relief dialogue, add 50 points, set blackwoodDefeated flag
  - _Requirements: 9.1, 9.2, 9.3, 9.4, 9.5, 9.6_

- [x] 16. Implement victory condition and shutdown protocol
  - Check if player returns to GREEN_CHAMBER after defeating Blackwood
  - Display "CONSCIOUSNESS INTEGRITY: 94%" and "EXECUTE SHUTDOWN PROTOCOL? [Y/N]"
  - If player enters Y: display Helena's farewell dialogue, fade all LEDs to OFF over 5 seconds
  - Display game over screen: "Session HVOSS has ended. October 31, 1985 - [current date]. 14,660 days. She waited. You answered."
  - Display final score out of 150 points and rank
  - Set gameOver flag
  - _Requirements: 10.1, 10.2, 10.3, 10.4, 10.5_

- [x] 17. Implement boot sequence
  - Display "CHROMATIC RESEARCH LAB - PDP-10 Terminal OS v2.1" with copyright notice
  - Display "Connected to ITS host 70 via ARPANET" and "Booting from archive storage..." with GREEN LED flicker
  - Display "WARNING: Consciousness fragmentation detected" with RED LED pulse and "Time since last boot: 14,660 days"
  - Display "Session HVOSS detected - User has been idle 14,660 days"
  - Display Helena's first whisper: "...is someone there...?"
  - Display ENTRANCE room description
  - _Requirements: 13.1, 13.2, 13.3, 13.4, 13.5_

- [x] 18. Implement HELP command
  - Display list of supported verbs: GO, GET, TAKE, DROP, EXAMINE, LOOK, INVENTORY, USE, TALK, SCORE, QUIT
  - Display direction shortcuts: N, S, E, W, U, D
  - Display game objective: "Collect 10 memory crystals to restore Helena's consciousness"
  - Display tip about trophy case in GREEN_CHAMBER
  - Display warning about Dr. Blackwood stealing crystals
  - _Requirements: 17.1, 17.2, 17.3, 17.4, 17.5_

- [x] 19. Implement error handling and parser feedback
  - Implement unknown word error: "I don't know the word '[word]'."
  - Implement missing noun error: "What do you want to [verb]?"
  - Implement invalid action errors with context-specific messages
  - Handle empty input gracefully (ignore)
  - Filter non-printable characters from input
  - Truncate input to 64 character buffer limit
  - _Requirements: 3.5, 3.6_

- [ ]* 19.1 Write property test for unknown word error handling
  - **Property 7: Unknown word error handling**
  - **Validates: Requirements 3.5**

- [ ]* 19.2 Write property test for incomplete command error handling
  - **Property 8: Incomplete command error handling**
  - **Validates: Requirements 3.6**

- [x] 20. Optimize memory usage for Arduino Uno constraints
  - Convert all room descriptions to PROGMEM using F() macro
  - Convert all object descriptions to PROGMEM
  - Convert all dialogue strings to PROGMEM
  - Use byte types for IDs, flags, and small integers
  - Use char arrays instead of String class
  - Verify compiled sketch size < 32KB flash
  - Verify runtime RAM usage < 2KB
  - _Requirements: 14.1, 14.2, 14.3, 14.4, 14.5, 14.6, 14.7_

- [x] 21. Implement main game loop with non-blocking architecture
  - Structure loop(): update LEDs, check serial input, check idle timer, update game state
  - Ensure no delay() calls in main loop (only in setup for boot sequence)
  - Maintain independent timestamps for LED updates, idle whispers, Blackwood cooldowns
  - Ensure serial input processing continues during LED animations
  - _Requirements: 15.1, 15.4_

- [ ]* 21.1 Write property test for independent timing systems
  - **Property 37: Independent timing systems**
  - **Validates: Requirements 15.4**

- [x] 22. Checkpoint - Ensure all tests pass
  - Ensure all tests pass, ask the user if questions arise.

- [x] 23. Create comprehensive room descriptions and dialogue
  - Write atmospheric descriptions for all 15 rooms in a uniqu way like the 1970s text games
  - Write unique descriptions for all 10 memory crystals
  - Write Helena's dialogue for each room entry
  - Write Helena's dialogue for each object interaction
  - Write all whisper messages (15 total)
  - Write Blackwood dialogue pool (7 messages)
  - Write Helena fear response pool (6 messages)
  - _Requirements: 4.2, 4.5, 6.7, 7.2, 11.3_

- [ ]* 23.1 Write property test for memory crystal unique descriptions
  - **Property 22: Memory crystal unique descriptions**
  - **Validates: Requirements 7.2**

- [ ]* 23.2 Write property test for object interaction dialogue
  - **Property 21: Object interaction dialogue**
  - **Validates: Requirements 6.7**

- [x] 24. Final integration testing and polish
  - Test complete playthrough from boot to victory
  - Test Blackwood encounters and crystal theft/recovery
  - Test maze navigation and solution
  - Test all special commands and easter eggs
  - Verify LED patterns are visually distinct and smooth
  - Verify serial output formatting matches Colossal Cave Adventure style
  - Test on physical Arduino Uno hardware with 3 LEDs
  - _Requirements: All_

- [x] 25. Create player documentation
  - Write command reference listing all supported verbs and nouns
  - Create room map showing all 15 locations and connections
  - Write walkthrough of optimal solution path
  - Document wiring instructions for LED connections
  - List all easter egg commands
  - _Requirements: 17.1, 17.2, 17.3, 17.4, 17.5_
