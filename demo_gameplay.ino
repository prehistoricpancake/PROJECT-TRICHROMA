/*
 * PROJECT TRICHROMA - Demo Gameplay Script
 * 
 * This is a DEMO-ONLY version that automatically plays through key moments
 * for video recording purposes. It simulates player input to showcase:
 * - Boot sequence
 * - Basic gameplay (movement, crystal collection)
 * - LED responses
 * - Enemy encounter (if spawns)
 * - Easter egg (XYZZY)
 * - Scoring
 * 
 * Upload this instead of project_trichroma.ino for demo recording.
 * Then just let it run - it will auto-play through the demo sequence.
 */

// Include all the same code from project_trichroma.ino
// (Copy all classes, structs, and functions here)
// Then add the demo automation below

// Demo state
unsigned long lastCommandTime = 0;
int demoStep = 0;
const int COMMAND_DELAY = 3000; // 3 seconds between commands (adjust for video pacing)

// Demo command sequence
const char* demoCommands[] = {
  "LOOK",                    // 0: Show starting room
  "GO WEST",                 // 1: Enter Green Chamber
  "EXAMINE TROPHY_CASE",     // 2: Show trophy case
  "GET CRYSTAL",             // 3: Pick up crystal (watch GREEN LED)
  "DROP CRYSTAL",            // 4: Deposit crystal (watch GREEN LED breathe)
  "GO EAST",                 // 5: Back to entrance
  "GO EAST",                 // 6: Enter Red Cavern (watch RED LED)
  "GET CRYSTAL",             // 7: Pick up red crystal
  "GO EAST",                 // 8: Enter Anger Pit (high danger - Blackwood might spawn)
  "GO WEST",                 // 9: Back to Red Cavern
  "GO WEST",                 // 10: Back to Entrance
  "GO SOUTH",                // 11: Enter Blue Maze (watch BLUE LED blink)
  "GO NORTH",                // 12: Exit maze
  "XYZZY",                   // 13: Easter egg
  "INVENTORY",               // 14: Show inventory
  "SCORE",                   // 15: Show score
  "GO WEST",                 // 16: Back to Green Chamber
  "DROP CRYSTAL",            // 17: Deposit red crystal
  "EXAMINE TROPHY_CASE",     // 18: Show progress
  NULL                       // End of demo
};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  
  // Initialize all game systems
  pulseManager.init(RED_LED_PIN, BLUE_LED_PIN, GREEN_LED_PIN);
  gameState.init();
  
  // Display boot sequence
  displayBootSequence();
  
  // Display starting room
  displayRoom(gameState.currentRoom);
  
  lastCommandTime = millis();
}

void loop() {
  // Update LEDs (non-blocking)
  pulseManager.update();
  
  // Check if it's time for next demo command
  unsigned long currentTime = millis();
  
  if (currentTime - lastCommandTime >= COMMAND_DELAY) {
    if (demoCommands[demoStep] != NULL) {
      // Display the command being "typed"
      Serial.println();
      Serial.print("> ");
      Serial.println(demoCommands[demoStep]);
      
      // Process the command
      Command cmd = parser.parse(demoCommands[demoStep]);
      if (cmd.valid) {
        processCommand(cmd);
      }
      
      // Move to next command
      demoStep++;
      lastCommandTime = currentTime;
    } else {
      // Demo complete - show final message
      if (demoStep == (sizeof(demoCommands) / sizeof(demoCommands[0]) - 1)) {
        Serial.println();
        Serial.println(F("=== DEMO COMPLETE ==="));
        Serial.println(F("This was an automated demo showcasing key features."));
        Serial.println(F("Upload project_trichroma.ino to play the full game!"));
        Serial.println();
        demoStep++; // Prevent repeating this message
      }
    }
  }
  
  // Check for idle whispers (still works during demo)
  if (currentTime - gameState.lastCommandTime > 30000) {
    dialogueSystem.displayWhisper();
    gameState.lastCommandTime = currentTime;
  }
}

// Copy all other functions from project_trichroma.ino below this line
// (displayBootSequence, displayRoom, processCommand, etc.)
