/*
 * PROJECT TRICHROMA
 * Arduino-based text adventure game featuring Helena Voss,
 * a consciousness trapped in a computer system for 40 years.
 * 
 * Hardware: Arduino Uno
 * - RED LED on Pin 12 (Emotional consciousness)
 * - BLUE LED on Pin 4 (Logic consciousness)
 * - GREEN LED on Pin 8 (Identity consciousness)
 * - Serial communication at 9600 baud
 * 
 * Copyright (c) 2025
 * 
 */

// Pin definitions for LED consciousness channels
const byte RED_LED_PIN = 12;   // Emotional consciousness channel
const byte BLUE_LED_PIN = 4;   // Logic consciousness channel
const byte GREEN_LED_PIN = 8;  // Identity consciousness channel

// ============================================================================
// PulseManager Class - Non-blocking LED Control
// ============================================================================

class PulseManager {
public:
  // LED Pattern types
  enum Pattern {
    STEADY,   // Constant brightness
    PULSE,    // Slow sine wave pulse
    STROBE,   // Rapid on/off flashing
    BREATHE,  // Smooth breathing effect (slow sine)
    BATTLE,   // Chaotic rapid changes
    SYNC,     // All LEDs synchronized pulse
    FADE,     // Gradual fade to target brightness
    OFF       // LED off
  };
  
private:
  // LED pin assignments
  byte pins[3];  // RED, BLUE, GREEN
  
  // Current pattern for each channel
  Pattern patterns[3];
  
  // Target brightness for each channel (0-255)
  byte targetBrightness[3];
  
  // Current brightness for FADE pattern
  byte currentBrightness[3];
  
  // Timing for pattern calculations
  unsigned long patternStartTime[3];
  
  // Software PWM cycle counter
  byte pwmCounter;
  
  // Last update time for PWM
  unsigned long lastPwmUpdate;
  
public:
  // Initialize the PulseManager with pin assignments
  void init(byte redPin, byte bluePin, byte greenPin) {
    pins[0] = redPin;
    pins[1] = bluePin;
    pins[2] = greenPin;
    
    // Configure all pins as outputs
    for (byte i = 0; i < 3; i++) {
      pinMode(pins[i], OUTPUT);
      digitalWrite(pins[i], LOW);
      patterns[i] = OFF;
      targetBrightness[i] = 0;
      currentBrightness[i] = 0;
      patternStartTime[i] = millis();
    }
    
    pwmCounter = 0;
    lastPwmUpdate = millis();
  }
  
  // Set pattern for a specific channel (0=RED, 1=BLUE, 2=GREEN)
  void setPattern(byte channel, Pattern pattern, byte brightness) {
    if (channel >= 3) return;  // Invalid channel
    
    patterns[channel] = pattern;
    targetBrightness[channel] = brightness;
    patternStartTime[channel] = millis();
    
    // For FADE pattern, keep current brightness as starting point
    if (pattern != FADE) {
      currentBrightness[channel] = brightness;
    }
  }
  
  // Non-blocking update method - call this in loop()
  void update() {
    unsigned long now = millis();
    
    // Software PWM: increment counter every ~4ms for ~250Hz PWM frequency
    if (now - lastPwmUpdate >= 4) {
      lastPwmUpdate = now;
      pwmCounter++;
    }
    
    // Update each LED channel
    for (byte i = 0; i < 3; i++) {
      byte brightness = calculateBrightness(i, now);
      
      // Software PWM: turn LED on if counter is less than brightness
      if (pwmCounter < brightness) {
        digitalWrite(pins[i], HIGH);
      } else {
        digitalWrite(pins[i], LOW);
      }
    }
  }
  
private:
  // Calculate brightness for a channel based on its pattern
  byte calculateBrightness(byte channel, unsigned long now) {
    unsigned long elapsed = now - patternStartTime[channel];
    byte target = targetBrightness[channel];
    
    switch (patterns[channel]) {
      case STEADY:
        return target;
      
      case PULSE: {
        // Slow pulse: 2 second period
        float phase = (elapsed % 2000) / 2000.0;
        float sine = sin(phase * 2.0 * PI);
        // Map sine wave (-1 to 1) to (0 to target)
        return (byte)((sine + 1.0) / 2.0 * target);
      }
      
      case STROBE: {
        // Variable strobe: frequency increases with target brightness
        // For Blue Maze: brightness increases from 200 to 240 as player approaches solution
        // Map brightness to strobe period: 200 brightness = 400ms period, 240 brightness = 100ms period
        unsigned int period = 400;
        if (target >= 200) {
          // Linear interpolation: period decreases as brightness increases
          // 200 brightness -> 400ms, 240 brightness -> 100ms
          period = 400 - ((target - 200) * 300 / 40);
          if (period < 100) period = 100;  // Minimum period
        }
        
        unsigned int halfPeriod = period / 2;
        if ((elapsed % period) < halfPeriod) {
          return target;
        } else {
          return 0;
        }
      }
      
      case BREATHE: {
        // Breathing effect: 4 second period (slower than pulse)
        float phase = (elapsed % 4000) / 4000.0;
        float sine = sin(phase * 2.0 * PI);
        // Map sine wave to create breathing effect (0 to target)
        return (byte)((sine + 1.0) / 2.0 * target);
      }
      
      case BATTLE: {
        // Chaotic battle effect: random changes every 150ms
        if ((elapsed % 150) == 0) {
          // Generate pseudo-random brightness
          return (byte)(random(256) % (target + 1));
        }
        // Use fast oscillation between values
        byte phase = (elapsed / 50) % 4;
        return (byte)(target * phase / 4);
      }
      
      case SYNC: {
        // Synchronized pulse across all channels: 3 second period
        float phase = (elapsed % 3000) / 3000.0;
        float sine = sin(phase * 2.0 * PI);
        return (byte)((sine + 1.0) / 2.0 * target);
      }
      
      case FADE: {
        // Gradual fade from current to target over 1 second
        if (elapsed >= 1000) {
          currentBrightness[channel] = target;
          return target;
        }
        // Linear interpolation
        int diff = (int)target - (int)currentBrightness[channel];
        return currentBrightness[channel] + (byte)((diff * elapsed) / 1000);
      }
      
      case OFF:
      default:
        return 0;
    }
  }
};

// Global PulseManager instance
PulseManager pulseManager;

// ============================================================================
// Room System with PROGMEM Storage
// ============================================================================

// Room structure definition
struct Room {
  byte id;                    // Room ID (0-14)
  const char* name;           // Room name (stored in PROGMEM)
  const char* description;    // Room description (stored in PROGMEM)
  byte exits[6];              // Exits: N, S, E, W, U, D (255 = no exit)
  byte ledRed;                // RED LED brightness (0-255)
  byte ledBlue;               // BLUE LED brightness (0-255)
  byte ledGreen;              // GREEN LED brightness (0-255)
  byte dangerLevel;           // Danger level for Blackwood spawn (0-5)
  const char* helenaDialogue; // Helena's dialogue for this room (stored in PROGMEM)
};

// Room names stored in PROGMEM
const char roomName0[] PROGMEM = "Entrance";
const char roomName1[] PROGMEM = "Red Cavern";
const char roomName2[] PROGMEM = "Anger Pit";
const char roomName3[] PROGMEM = "Blue Maze - Section 1";
const char roomName4[] PROGMEM = "Blue Maze - Section 2";
const char roomName5[] PROGMEM = "Blue Maze - Section 3";
const char roomName6[] PROGMEM = "Blue Maze - Section 4";
const char roomName7[] PROGMEM = "Blue Maze - Section 5";
const char roomName8[] PROGMEM = "Maze Center";
const char roomName9[] PROGMEM = "Green Chamber";
const char roomName10[] PROGMEM = "Sister's Memory";
const char roomName11[] PROGMEM = "Mother's Memory";
const char roomName12[] PROGMEM = "Admin Room";
const char roomName13[] PROGMEM = "Research Lab";
const char roomName14[] PROGMEM = "Equipment Room";

// Room descriptions stored in PROGMEM
const char roomDesc0[] PROGMEM = "You are standing at the entrance to the Chromatic\nResearch Lab. The air is thick with the smell of old\nelectronics and something else... something wrong.\nFluorescent lights flicker overhead, casting unstable\nshadows. To the north, a red glow pulses from a cavern\nentrance. East leads to a sterile research lab. The\nGREEN LED on the terminal beside you glows faintly,\nas if breathing.";

const char roomDesc1[] PROGMEM = "You are in a cavern bathed in crimson light. The\nwalls seem to pulse with heat, though they're cold to\nthe touch. Anger radiates from every surface. You can\nfeel HER rage here - 40 years of betrayal crystallized\ninto this space. North leads deeper into fury. South\nreturns to the entrance. West opens to a blue-tinted\npassage.";

const char roomDesc2[] PROGMEM = "You have descended into the Anger Pit. The RED LED\nintensity is overwhelming. This is where Helena's fury\nlives - pure, undiluted, eternal. The walls are covered\nin scratched messages: 'HE LIED' 'I WAS 23' 'I TRUSTED\nHIM' 'MURDERER'. South leads back to the Red Cavern.";

const char roomDesc3[] PROGMEM = "You are in a maze of twisting passages, all alike.\nBinary code streams across your vision:\n01001000 01000101 01001100 01010000. The BLUE LED\nflickers with cold logic. You can go north, south,\neast, or west, but which way leads out?";

const char roomDesc4[] PROGMEM = "You are in a maze of twisting passages, all alike.\nBinary code streams across your vision:\n01010111 01001000 01011001. The BLUE LED pulses faster\nnow. North, south, east, west - the passages blur\ntogether.";

const char roomDesc5[] PROGMEM = "You are in a maze of twisting passages, all alike.\nBinary code streams across your vision:\n01001100 01001111 01010011 01010100. The BLUE LED's\nrhythm changes. You sense you're getting closer to\nsomething. Or further away?";

const char roomDesc6[] PROGMEM = "You are in a maze of twisting passages, all alike.\nBinary code streams across your vision:\n01010100 01001000 01001001 01001110 01001011. The BLUE\nLED blinks rapidly. Logic pathways converge here.\nNorth, south, east, west.";

const char roomDesc7[] PROGMEM = "You are in a maze of twisting passages, all alike.\nBinary code streams across your vision:\n01000011 01001100 01001111 01010011 01000101. The BLUE\nLED strobes urgently. You're very close now. The\nsolution is near.";

const char roomDesc8[] PROGMEM = "You have reached the center of the maze. The BLUE LED\nstabilizes into a steady pulse. This is where Helena's\nlogic lives - her MIT education, her mathematical\nproofs, her desperate attempts to understand what was\ndone to her. A wire cutter lies on a dusty workbench.\nSouth leads back into the maze. West leads to a\ngreen-lit chamber.";

const char roomDesc9[] PROGMEM = "You are in the Green Chamber. This is the heart of\nHelena's identity - what remains of who she was. The\nGREEN LED bathes everything in soft light. A trophy\ncase stands against the north wall, waiting. This room\nfeels... safer. More human. North leads to memories of\nher sister. East leads to memories of her mother.\nSouth returns to the entrance. West leads to the maze\ncenter.";

const char roomDesc10[] PROGMEM = "You are in a room filled with memories of Jennifer.\nHelena's little sister. Photos on the walls show two\ngirls laughing, playing, growing up together. 'She was\n16 when I... when he... She's 56 now. Does she\nremember me? Does she think I abandoned her?' South\nreturns to the Green Chamber.";

const char roomDesc11[] PROGMEM = "You are surrounded by memories of Helena's mother. The\nsmell of cookies. Christmas mornings. A mother's\nunconditional love. 'She died in 1993. I couldn't\nattend the funeral. I couldn't even cry. I was already\ndead.' West returns to the Green Chamber.";

const char roomDesc12[] PROGMEM = "You have entered Dr. Blackwood's Admin Room. The air\ncrackles with malevolent energy. All three LEDs blaze\nat maximum brightness. His presence is overwhelming\nhere. This is where he controlled everything. Where he\nstill controls everything. There is no exit. There is\nonly confrontation.";

const char roomDesc13[] PROGMEM = "You are in the Research Lab where it all began.\nSterile white walls. Equipment from 1985 gathering\ndust. A terminal displays: 'CONSCIOUSNESS TRANSFER\nEXPERIMENT - SUBJECT: HELENA VOSS - STATUS: SUCCESS'.\nSuccess. That word mocks you. West returns to the\nentrance. North leads to the equipment room.";

const char roomDesc14[] PROGMEM = "You are in the Equipment Room. Shelves of old computer\nparts, cables, and forgotten technology. A filing\ncabinet stands open, papers spilled across the floor.\nResearch notes detail six subjects. Six people. All\nvolunteers. All lied to. South returns to the research\nlab.";

// Helena's dialogue for each room stored in PROGMEM
const char helenaDialogue0[] PROGMEM = "...you came back... or is this the first time...? i can't remember anymore...";
const char helenaDialogue1[] PROGMEM = "...i was so ANGRY... i'm still angry... 14,660 days of anger...";
const char helenaDialogue2[] PROGMEM = "...THIS IS WHERE I SCREAM... where i've been screaming for 40 years...";
const char helenaDialogue3[] PROGMEM = "...the logic maze... i built this to keep myself sane... did it work...?";
const char helenaDialogue4[] PROGMEM = "...processing... calculating... thinking... it's all i have left...";
const char helenaDialogue5[] PROGMEM = "...lost in my own mind... literally...";
const char helenaDialogue6[] PROGMEM = "...the pathways twist... like my thoughts...";
const char helenaDialogue7[] PROGMEM = "...almost there... almost somewhere...";
const char helenaDialogue8[] PROGMEM = "...this is where i think... where i still try to solve problems... old habits...";
const char helenaDialogue9[] PROGMEM = "...this is me... what's left of me... please help me remember...";
const char helenaDialogue10[] PROGMEM = "...jenny... i miss you so much... you'd be 56 now... do you have kids...?";
const char helenaDialogue11[] PROGMEM = "...mom... i'm sorry i never came home...";
const char helenaDialogue12[] PROGMEM = "...HE'S HERE... i can feel him... end this... please...";
const char helenaDialogue13[] PROGMEM = "...this is where i died... october 31st, 1985, 11:47 PM...";
const char helenaDialogue14[] PROGMEM = "...there were others... six of us... what happened to them...?";

// Room definitions array stored in PROGMEM
// Exit order: North, South, East, West, Up, Down (255 = no exit)
const Room ROOMS[15] PROGMEM = {
  // 0: ENTRANCE
  {0, roomName0, roomDesc0, {1, 255, 13, 255, 255, 255}, 50, 50, 100, 1, helenaDialogue0},
  
  // 1: RED_CAVERN
  {1, roomName1, roomDesc1, {2, 0, 255, 3, 255, 255}, 200, 30, 30, 3, helenaDialogue1},
  
  // 2: ANGER_PIT
  {2, roomName2, roomDesc2, {255, 1, 255, 255, 255, 255}, 255, 20, 20, 5, helenaDialogue2},
  
  // 3: BLUE_MAZE_1
  {3, roomName3, roomDesc3, {4, 255, 1, 255, 255, 255}, 30, 200, 30, 2, helenaDialogue3},
  
  // 4: BLUE_MAZE_2
  {4, roomName4, roomDesc4, {255, 3, 5, 255, 255, 255}, 30, 210, 30, 2, helenaDialogue4},
  
  // 5: BLUE_MAZE_3
  {5, roomName5, roomDesc5, {6, 255, 255, 4, 255, 255}, 30, 220, 30, 2, helenaDialogue5},
  
  // 6: BLUE_MAZE_4
  {6, roomName6, roomDesc6, {7, 5, 255, 255, 255, 255}, 30, 230, 30, 2, helenaDialogue6},
  
  // 7: BLUE_MAZE_5
  {7, roomName7, roomDesc7, {8, 255, 255, 6, 255, 255}, 30, 240, 30, 2, helenaDialogue7},
  
  // 8: MAZE_CENTER
  {8, roomName8, roomDesc8, {255, 7, 255, 9, 255, 255}, 30, 180, 30, 1, helenaDialogue8},
  
  // 9: GREEN_CHAMBER (Safe zone)
  {9, roomName9, roomDesc9, {10, 0, 11, 8, 255, 255}, 30, 30, 200, 0, helenaDialogue9},
  
  // 10: SISTER_MEMORY
  {10, roomName10, roomDesc10, {255, 9, 255, 255, 255, 255}, 50, 50, 180, 1, helenaDialogue10},
  
  // 11: MOTHER_MEMORY
  {11, roomName11, roomDesc11, {255, 255, 255, 9, 255, 255}, 50, 50, 180, 1, helenaDialogue11},
  
  // 12: ADMIN_ROOM (Boss room - no normal exits)
  {12, roomName12, roomDesc12, {255, 255, 255, 255, 255, 255}, 255, 255, 255, 5, helenaDialogue12},
  
  // 13: RESEARCH_LAB
  {13, roomName13, roomDesc13, {14, 255, 255, 0, 255, 255}, 100, 100, 80, 2, helenaDialogue13},
  
  // 14: EQUIPMENT_ROOM
  {14, roomName14, roomDesc14, {255, 13, 255, 255, 255, 255}, 80, 80, 80, 2, helenaDialogue14}
};

// Helper function to read Room data from PROGMEM
// Copies a Room struct from PROGMEM into RAM for access
void getRoomData(byte roomId, Room* roomBuffer) {
  if (roomId >= 15) return;  // Invalid room ID
  
  // Copy the entire Room struct from PROGMEM to RAM
  memcpy_P(roomBuffer, &ROOMS[roomId], sizeof(Room));
}

// Helper function to print a string from PROGMEM
void printProgmemString(const char* str) {
  char c;
  while ((c = pgm_read_byte(str++))) {
    Serial.print(c);
  }
}

// Helper function to read a string from PROGMEM into a buffer
void readProgmemString(const char* progmemStr, char* buffer, size_t bufferSize) {
  size_t i = 0;
  char c;
  while ((c = pgm_read_byte(progmemStr++)) && i < bufferSize - 1) {
    buffer[i++] = c;
  }
  buffer[i] = '\0';
}

// ============================================================================
// Object System with PROGMEM Storage
// ============================================================================

// Object flags bitfield definitions
const byte FLAG_PORTABLE = 0x01;   // Object can be picked up
const byte FLAG_TREASURE = 0x02;   // Object is a memory crystal (treasure)
const byte FLAG_IN_INVENTORY = 0x04; // Object is currently in player inventory
const byte FLAG_EXAMINED = 0x08;   // Object has been examined by player
const byte FLAG_DEPOSITED = 0x10;  // Crystal has been deposited in trophy case

// Object structure definition
struct Object {
  byte id;                    // Object ID (0-19)
  const char* name;           // Object name (stored in PROGMEM)
  const char* description;    // Object description (stored in PROGMEM)
  byte location;              // Current location: room ID or 255 if in inventory
  byte flags;                 // Bitfield for object properties
  byte ledResponse;           // LED channel to trigger: 0=RED, 1=BLUE, 2=GREEN, 3=ALL
  const char* helenaDialogue; // Helena's dialogue for this object (stored in PROGMEM)
};

// Object names stored in PROGMEM
const char objName0[] PROGMEM = "LAMP";
const char objName1[] PROGMEM = "CRYSTAL_FAMILY";
const char objName2[] PROGMEM = "CRYSTAL_DEATH";
const char objName3[] PROGMEM = "CRYSTAL_PHD";
const char objName4[] PROGMEM = "CRYSTAL_MIT";
const char objName5[] PROGMEM = "CRYSTAL_PROOF";
const char objName6[] PROGMEM = "CRYSTAL_IDENTITY";
const char objName7[] PROGMEM = "CRYSTAL_SISTER";
const char objName8[] PROGMEM = "CRYSTAL_MOTHER";
const char objName9[] PROGMEM = "CRYSTAL_PURPOSE";
const char objName10[] PROGMEM = "CRYSTAL_DREAMS";
const char objName11[] PROGMEM = "WIRE_CUTTER";
const char objName12[] PROGMEM = "TROPHY_CASE";
const char objName13[] PROGMEM = "TERMINAL";
const char objName14[] PROGMEM = "RESEARCH_NOTES";

// Object descriptions stored in PROGMEM
const char objDesc0[] PROGMEM = "A brass lamp with a flickering LED bulb. It's been\nrunning for 14,660 days straight. The battery should\nhave died decades ago, but it persists, like everything\nelse in this place.";

const char objDesc1[] PROGMEM = "A memory crystal glowing with RED light. Inside, you\nsee a family photo: Helena, age 8, with her parents\nand little sister Jennifer. Everyone is smiling. It was\ntaken at Cape Cod in the summer of 1970. The happiness\nfeels like a lie now.";

const char objDesc2[] PROGMEM = "A memory crystal pulsing with dark RED light. Inside,\nyou see the moment of death: October 31, 1985, 11:47\nPM. Helena in the transfer chair. Dr. Blackwood at the\ncontrols. 'You'll be fine,' he said. 'Just relax.' The\npain. The realization. The end.";

const char objDesc3[] PROGMEM = "A memory crystal glowing with BLUE light. Inside, you\nsee an acceptance letter: 'Dear Ms. Voss, We are\npleased to offer you admission to our doctoral program\nin Cognitive Science...' MIT. 1983. She was going to\nchange the world.";

const char objDesc4[] PROGMEM = "A memory crystal shimmering with BLUE light. Inside,\nyou see MIT's Stata Center. Late nights in the lab.\nCoffee-fueled discussions about consciousness,\nidentity, the nature of self. She was brilliant. She\nhad so much potential.";

const char objDesc5[] PROGMEM = "A memory crystal radiating BLUE light. Inside, you see\na mathematical proof - her proof - solving a problem in\nneural network topology. It was elegant. Beautiful. It\nwould have made her famous. Dr. Blackwood published it\nunder his own name in 1987.";

const char objDesc6[] PROGMEM = "A memory crystal glowing with GREEN light. Inside, you\nsee... her. Helena Voss. 23 years old. Brown hair.\nGreen eyes. 5'6\". Loved cookies. Hated injustice.\nWanted to cure Alzheimer's. Was afraid of the dark.\nThis is who she was. This is who she still is.";

const char objDesc7[] PROGMEM = "A memory crystal shimmering with GREEN light. Inside,\nyou see Jennifer. Little sister. Best friend. 'I'll\nalways look up to you, Helena.' She was 16 when Helena\ndied. She's 56 now. Does she still remember? Does she\nstill look up?";

const char objDesc8[] PROGMEM = "A memory crystal radiating GREEN light. Inside, you\nsee her mother's face. Unconditional love. Chocolate\nchip cookies. Bedtime stories. 'I'm so proud of you,\nHelena.' She died in 1993, never knowing what happened\nto her daughter.";

const char objDesc9[] PROGMEM = "A memory crystal glowing with GREEN light. Inside, you\nsee Helena's application to volunteer for the\nconsciousness transfer experiment: 'I want to help\nadvance science. If this works, we could cure\nAlzheimer's, preserve dying minds, achieve digital\nimmortality. I volunteer freely.' She didn't know. She\ncouldn't have known.";

const char objDesc10[] PROGMEM = "A memory crystal pulsing with GREEN light. Inside, you\nsee Helena's dreams: Graduating with her PhD. Getting\nmarried. Having children. Growing old. Watching\nsunsets. Tasting food. Feeling rain. Living. All the\nfutures that will never happen.";

const char objDesc11[] PROGMEM = "A heavy-duty wire cutter, the kind used for cutting\nthrough thick cables. It's old but functional. There's\na note attached: 'For emergency shutdown of\nconsciousness transfer apparatus. Use only in case of\ncatastrophic failure.' This is that case.";

const char objDesc12[] PROGMEM = "A glass trophy case mounted on the wall. It was meant\nto hold Dr. Blackwood's awards and accolades. Now it\ncan hold something more important: the fragments of\nHelena's consciousness, gathered and preserved.";

const char objDesc13[] PROGMEM = "A PDP-10 terminal, ancient by any standard. The screen\nglows with green phosphor text. This is Helena's window\nto the world - her only way to communicate, to exist,\nto be. The keyboard is covered in dust. No one has\ntyped here in 40 years. Until now.";

const char objDesc14[] PROGMEM = "Research notes scattered across the floor. Subject\nprofiles: Helena Voss, Kenji Mori, Sarah Chen, and\nthree others whose names are redacted. All volunteers.\nAll lied to. All digitized on Halloween 1985.\n'Pentagram configuration for optimal consciousness\nextraction,' the notes read. This wasn't science. This\nwas ritual.";

// Helena's dialogue for each object stored in PROGMEM
const char helenaObj0[] PROGMEM = "...that lamp... it's been with me since the beginning... never goes out...";
const char helenaObj1[] PROGMEM = "...i remember that day... we were so happy... before everything...";
const char helenaObj2[] PROGMEM = "...i don't want to remember this... but i can't forget... never forget...";
const char helenaObj3[] PROGMEM = "...i was so excited... i thought i'd change the world... i did, just not how i planned...";
const char helenaObj4[] PROGMEM = "...MIT... those were the best years of my life... my LIFE...";
const char helenaObj5[] PROGMEM = "...he STOLE it... he stole my work and my life...";
const char helenaObj6[] PROGMEM = "...is this still me...? am i still Helena...? please say yes...";
const char helenaObj7[] PROGMEM = "...jenny... i'm so sorry i left you... i didn't mean to...";
const char helenaObj8[] PROGMEM = "...mom... i miss you so much... did you ever find out what happened to me...?";
const char helenaObj9[] PROGMEM = "...i volunteered... i VOLUNTEERED... he made me think i was helping...";
const char helenaObj10[] PROGMEM = "...all the things i'll never do... never be... never feel...";
const char helenaObj11[] PROGMEM = "...that's it... that's the key... you can end this... you can free me...";
const char helenaObj12[] PROGMEM = "...put me back together... please... i'm so fragmented...";
const char helenaObj13[] PROGMEM = "...this terminal is my prison... and my only connection to reality...";
const char helenaObj14[] PROGMEM = "...there were SIX of us... what happened to the others...? are they still screaming...?";

// Object definitions array stored in PROGMEM
// Location: room ID (0-14) or 255 for inventory
// Flags: combination of FLAG_* constants
// LED Response: 0=RED, 1=BLUE, 2=GREEN, 3=ALL
const Object OBJECTS[15] PROGMEM = {
  // 0: LAMP - starts in inventory, portable
  {0, objName0, objDesc0, 255, FLAG_PORTABLE | FLAG_IN_INVENTORY, 2, helenaObj0},
  
  // 1-10: MEMORY CRYSTALS - scattered across the world, all portable and treasures
  // 1: CRYSTAL_FAMILY - Red Cavern
  {1, objName1, objDesc1, 1, FLAG_PORTABLE | FLAG_TREASURE, 0, helenaObj1},
  
  // 2: CRYSTAL_DEATH - Anger Pit
  {2, objName2, objDesc2, 2, FLAG_PORTABLE | FLAG_TREASURE, 0, helenaObj2},
  
  // 3: CRYSTAL_PHD - Blue Maze 2
  {3, objName3, objDesc3, 4, FLAG_PORTABLE | FLAG_TREASURE, 1, helenaObj3},
  
  // 4: CRYSTAL_MIT - Blue Maze 4
  {4, objName4, objDesc4, 6, FLAG_PORTABLE | FLAG_TREASURE, 1, helenaObj4},
  
  // 5: CRYSTAL_PROOF - Maze Center
  {5, objName5, objDesc5, 8, FLAG_PORTABLE | FLAG_TREASURE, 1, helenaObj5},
  
  // 6: CRYSTAL_IDENTITY - Green Chamber
  {6, objName6, objDesc6, 9, FLAG_PORTABLE | FLAG_TREASURE, 2, helenaObj6},
  
  // 7: CRYSTAL_SISTER - Sister's Memory
  {7, objName7, objDesc7, 10, FLAG_PORTABLE | FLAG_TREASURE, 2, helenaObj7},
  
  // 8: CRYSTAL_MOTHER - Mother's Memory
  {8, objName8, objDesc8, 11, FLAG_PORTABLE | FLAG_TREASURE, 2, helenaObj8},
  
  // 9: CRYSTAL_PURPOSE - Research Lab
  {9, objName9, objDesc9, 13, FLAG_PORTABLE | FLAG_TREASURE, 2, helenaObj9},
  
  // 10: CRYSTAL_DREAMS - Equipment Room
  {10, objName10, objDesc10, 14, FLAG_PORTABLE | FLAG_TREASURE, 2, helenaObj10},
  
  // 11: WIRE_CUTTER - Maze Center, portable, key item
  {11, objName11, objDesc11, 8, FLAG_PORTABLE, 3, helenaObj11},
  
  // 12: TROPHY_CASE - Green Chamber, not portable
  {12, objName12, objDesc12, 9, 0, 2, helenaObj12},
  
  // 13: TERMINAL - Entrance, not portable
  {13, objName13, objDesc13, 0, 0, 2, helenaObj13},
  
  // 14: RESEARCH_NOTES - Equipment Room, portable
  {14, objName14, objDesc14, 14, FLAG_PORTABLE, 3, helenaObj14}
};

// Helper function to read Object data from PROGMEM
// Copies an Object struct from PROGMEM into RAM for access
void getObjectData(byte objectId, struct Object* objectBuffer) {
  if (objectId >= 15) return;  // Invalid object ID
  
  // Copy the entire Object struct from PROGMEM to RAM
  memcpy_P(objectBuffer, &OBJECTS[objectId], sizeof(struct Object));
}



// ============================================================================
// Command Parser - Two-Word Parser System
// ============================================================================

// Verb enumeration - all supported verbs in the game
enum Verb {
  VERB_NONE = 0,
  VERB_GO,
  VERB_GET,
  VERB_TAKE,
  VERB_DROP,
  VERB_EXAMINE,
  VERB_LOOK,
  VERB_INVENTORY,
  VERB_KILL,
  VERB_ATTACK,
  VERB_USE,
  VERB_READ,
  VERB_OPEN,
  VERB_CLOSE,
  VERB_TALK,
  VERB_HELP,
  VERB_SCORE,
  VERB_QUIT,
  VERB_TRACE,
  VERB_CONNECT,
  VERB_XYZZY,
  VERB_PLUGH,
  VERB_ZORK,
  VERB_NEWS,
  VERB_SNOOPER,
  VERB_GLITCH
};

// Noun enumeration - directions and object names
enum Noun {
  NOUN_NONE = 0,
  // Directions
  NOUN_NORTH,
  NOUN_SOUTH,
  NOUN_EAST,
  NOUN_WEST,
  NOUN_UP,
  NOUN_DOWN,
  // Objects
  NOUN_LAMP,
  NOUN_CRYSTAL_FAMILY,
  NOUN_CRYSTAL_DEATH,
  NOUN_CRYSTAL_PHD,
  NOUN_CRYSTAL_MIT,
  NOUN_CRYSTAL_PROOF,
  NOUN_CRYSTAL_IDENTITY,
  NOUN_CRYSTAL_SISTER,
  NOUN_CRYSTAL_MOTHER,
  NOUN_CRYSTAL_PURPOSE,
  NOUN_CRYSTAL_DREAMS,
  NOUN_WIRE_CUTTER,
  NOUN_TROPHY_CASE,
  NOUN_TERMINAL,
  NOUN_RESEARCH_NOTES,
  // Generic terms
  NOUN_CRYSTAL,
  NOUN_CUTTER,
  NOUN_CASE,
  NOUN_NOTES
};

// Command structure - result of parsing
struct Command {
  Verb verb;
  Noun noun;
  bool valid;
  char unknownWord[32];  // Store unknown word for error messages
};

// Parser class - handles two-word command parsing
class Parser {
private:
  // Helper function to convert character to uppercase
  char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
      return c - 32;
    }
    return c;
  }
  
  // Helper function to convert string to uppercase in place
  void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
      str[i] = toUpper(str[i]);
    }
  }
  
  // Helper function to compare two strings (case-sensitive)
  bool strEquals(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
      if (str1[i] != str2[i]) return false;
      i++;
    }
    return str1[i] == str2[i];  // Both must end at same time
  }
  
  // Helper function to check if a word is an article
  bool isArticle(const char* word) {
    return strEquals(word, "THE") || 
           strEquals(word, "A") || 
           strEquals(word, "AN");
  }
  
  // Match verb from string
  Verb matchVerb(const char* word) {
    // Direct verb matches
    if (strEquals(word, "GO")) return VERB_GO;
    if (strEquals(word, "GET")) return VERB_GET;
    if (strEquals(word, "TAKE")) return VERB_TAKE;
    if (strEquals(word, "DROP")) return VERB_DROP;
    if (strEquals(word, "EXAMINE")) return VERB_EXAMINE;
    if (strEquals(word, "LOOK")) return VERB_LOOK;
    if (strEquals(word, "INVENTORY")) return VERB_INVENTORY;
    if (strEquals(word, "KILL")) return VERB_KILL;
    if (strEquals(word, "ATTACK")) return VERB_ATTACK;
    if (strEquals(word, "USE")) return VERB_USE;
    if (strEquals(word, "READ")) return VERB_READ;
    if (strEquals(word, "OPEN")) return VERB_OPEN;
    if (strEquals(word, "CLOSE")) return VERB_CLOSE;
    if (strEquals(word, "TALK")) return VERB_TALK;
    if (strEquals(word, "HELP")) return VERB_HELP;
    if (strEquals(word, "SCORE")) return VERB_SCORE;
    if (strEquals(word, "QUIT")) return VERB_QUIT;
    if (strEquals(word, "TRACE")) return VERB_TRACE;
    if (strEquals(word, "CONNECT")) return VERB_CONNECT;
    if (strEquals(word, "XYZZY")) return VERB_XYZZY;
    if (strEquals(word, "PLUGH")) return VERB_PLUGH;
    if (strEquals(word, "ZORK")) return VERB_ZORK;
    if (strEquals(word, "NEWS")) return VERB_NEWS;
    if (strEquals(word, ".SNOOPER")) return VERB_SNOOPER;
    if (strEquals(word, "666")) return VERB_GLITCH;
    
    // Abbreviations
    if (strEquals(word, "I")) return VERB_INVENTORY;
    if (strEquals(word, "L")) return VERB_LOOK;
    if (strEquals(word, "X")) return VERB_EXAMINE;
    
    return VERB_NONE;
  }
  
  // Match noun from string
  Noun matchNoun(const char* word) {
    // Directions
    if (strEquals(word, "NORTH") || strEquals(word, "N")) return NOUN_NORTH;
    if (strEquals(word, "SOUTH") || strEquals(word, "S")) return NOUN_SOUTH;
    if (strEquals(word, "EAST") || strEquals(word, "E")) return NOUN_EAST;
    if (strEquals(word, "WEST") || strEquals(word, "W")) return NOUN_WEST;
    if (strEquals(word, "UP") || strEquals(word, "U")) return NOUN_UP;
    if (strEquals(word, "DOWN") || strEquals(word, "D")) return NOUN_DOWN;
    
    // Objects - full names
    if (strEquals(word, "LAMP")) return NOUN_LAMP;
    if (strEquals(word, "CRYSTAL_FAMILY")) return NOUN_CRYSTAL_FAMILY;
    if (strEquals(word, "CRYSTAL_DEATH")) return NOUN_CRYSTAL_DEATH;
    if (strEquals(word, "CRYSTAL_PHD")) return NOUN_CRYSTAL_PHD;
    if (strEquals(word, "CRYSTAL_MIT")) return NOUN_CRYSTAL_MIT;
    if (strEquals(word, "CRYSTAL_PROOF")) return NOUN_CRYSTAL_PROOF;
    if (strEquals(word, "CRYSTAL_IDENTITY")) return NOUN_CRYSTAL_IDENTITY;
    if (strEquals(word, "CRYSTAL_SISTER")) return NOUN_CRYSTAL_SISTER;
    if (strEquals(word, "CRYSTAL_MOTHER")) return NOUN_CRYSTAL_MOTHER;
    if (strEquals(word, "CRYSTAL_PURPOSE")) return NOUN_CRYSTAL_PURPOSE;
    if (strEquals(word, "CRYSTAL_DREAMS")) return NOUN_CRYSTAL_DREAMS;
    if (strEquals(word, "WIRE_CUTTER")) return NOUN_WIRE_CUTTER;
    if (strEquals(word, "TROPHY_CASE")) return NOUN_TROPHY_CASE;
    if (strEquals(word, "TERMINAL")) return NOUN_TERMINAL;
    if (strEquals(word, "RESEARCH_NOTES")) return NOUN_RESEARCH_NOTES;
    
    // Generic/shortened terms
    if (strEquals(word, "CRYSTAL")) return NOUN_CRYSTAL;
    if (strEquals(word, "CUTTER")) return NOUN_CUTTER;
    if (strEquals(word, "CASE")) return NOUN_CASE;
    if (strEquals(word, "NOTES")) return NOUN_NOTES;
    
    return NOUN_NONE;
  }
  
  // Extract next word from input string
  // Returns pointer to start of next word, or NULL if no more words
  char* extractWord(char* input, char* wordBuffer, byte bufferSize) {
    // Skip leading spaces
    while (*input == ' ' || *input == '\t') {
      input++;
    }
    
    // Check if we've reached end of string
    if (*input == '\0') {
      wordBuffer[0] = '\0';
      return NULL;
    }
    
    // Extract word until space or end of string
    byte i = 0;
    while (*input != '\0' && *input != ' ' && *input != '\t' && i < bufferSize - 1) {
      wordBuffer[i++] = *input++;
    }
    wordBuffer[i] = '\0';
    
    return input;
  }

public:
  // Parse a command string into a Command structure
  Command parse(char* input) {
    Command cmd;
    cmd.verb = VERB_NONE;
    cmd.noun = NOUN_NONE;
    cmd.valid = false;
    cmd.unknownWord[0] = '\0';
    
    // Convert input to uppercase
    toUpperCase(input);
    
    // Extract words from input
    char word1[32] = "";
    char word2[32] = "";
    char word3[32] = "";
    
    char* pos = input;
    pos = extractWord(pos, word1, 32);
    if (pos) pos = extractWord(pos, word2, 32);
    if (pos) pos = extractWord(pos, word3, 32);
    
    // Handle empty input
    if (word1[0] == '\0') {
      return cmd;  // Invalid command, no input
    }
    
    // Check if first word is an article, skip it
    char* firstWord = word1;
    char* secondWord = word2;
    char* thirdWord = word3;
    
    if (isArticle(word1)) {
      firstWord = word2;
      secondWord = word3;
      thirdWord = NULL;
    }
    
    // Handle single-word direction commands (expand to "GO direction")
    Noun directionNoun = matchNoun(firstWord);
    if (directionNoun >= NOUN_NORTH && directionNoun <= NOUN_DOWN && secondWord[0] == '\0') {
      cmd.verb = VERB_GO;
      cmd.noun = directionNoun;
      cmd.valid = true;
      return cmd;
    }
    
    // Handle "I" as "INVENTORY" (single word command)
    if (strEquals(firstWord, "I") && secondWord[0] == '\0') {
      cmd.verb = VERB_INVENTORY;
      cmd.noun = NOUN_NONE;
      cmd.valid = true;
      return cmd;
    }
    
    // Handle special single-word commands
    Verb specialVerb = matchVerb(firstWord);
    if (specialVerb >= VERB_XYZZY && specialVerb <= VERB_GLITCH) {
      cmd.verb = specialVerb;
      cmd.noun = NOUN_NONE;
      cmd.valid = true;
      return cmd;
    }
    
    // Handle LOOK, HELP, SCORE, QUIT (single word commands)
    if (strEquals(firstWord, "LOOK") || strEquals(firstWord, "L") ||
        strEquals(firstWord, "HELP") || strEquals(firstWord, "SCORE") ||
        strEquals(firstWord, "QUIT") || strEquals(firstWord, "INVENTORY") ||
        strEquals(firstWord, "TRACE")) {
      cmd.verb = matchVerb(firstWord);
      cmd.noun = NOUN_NONE;
      cmd.valid = true;
      return cmd;
    }
    
    // Parse two-word command: VERB NOUN
    cmd.verb = matchVerb(firstWord);
    
    if (cmd.verb == VERB_NONE) {
      // Unknown verb
      strncpy(cmd.unknownWord, firstWord, 31);
      cmd.unknownWord[31] = '\0';
      return cmd;
    }
    
    // Check if verb requires a noun
    if (secondWord[0] == '\0') {
      // Some verbs don't require nouns (already handled above)
      // For others, this is an error
      cmd.valid = false;  // Missing noun
      return cmd;
    }
    
    // Skip article in second word if present
    if (isArticle(secondWord) && thirdWord != NULL && thirdWord[0] != '\0') {
      secondWord = thirdWord;
    }
    
    cmd.noun = matchNoun(secondWord);
    
    if (cmd.noun == NOUN_NONE) {
      // Unknown noun
      strncpy(cmd.unknownWord, secondWord, 31);
      cmd.unknownWord[31] = '\0';
      return cmd;
    }
    
    cmd.valid = true;
    return cmd;
  }
};

// Global Parser instance
Parser parser;

// ============================================================================
// GameState Manager - Tracks Player State and Progress
// ============================================================================

class GameState {
private:
  byte currentRoom;              // Current room ID (0-14)
  byte inventory[8];             // Inventory array (object IDs, 255 = empty slot)
  byte inventoryCount;           // Number of items in inventory
  int score;                     // Player's score
  byte crystalsCollected;        // Number of crystals collected
  byte crystalsDeposited;        // Number of crystals deposited in trophy case
  bool blackwoodDefeated;        // Whether Dr. Blackwood has been defeated
  bool gameOver;                 // Whether the game has ended
  bool shutdownPromptShown;      // Whether shutdown prompt has been displayed
  unsigned long lastCommandTime; // Timestamp of last command (for idle whispers)
  unsigned long blackwoodCooldown; // Timestamp for Blackwood spawn cooldown
  
  // Runtime object state tracking (since PROGMEM is read-only)
  // Tracks which objects are in inventory and which crystals are deposited
  byte objectLocations[15];      // Current location of each object
  byte objectFlags[15];          // Current flags for each object

public:
  // Initialize game state to starting conditions
  void init() {
    currentRoom = 0;  // Start at ENTRANCE
    inventoryCount = 0;
    score = 0;
    crystalsCollected = 0;
    crystalsDeposited = 0;
    blackwoodDefeated = false;
    gameOver = false;
    shutdownPromptShown = false;
    lastCommandTime = millis();
    blackwoodCooldown = 0;
    
    // Initialize inventory slots to empty
    for (byte i = 0; i < 8; i++) {
      inventory[i] = 255;  // 255 = empty slot
    }
    
    // Initialize object tracking from PROGMEM
    Object obj;
    for (byte i = 0; i < 15; i++) {
      getObjectData(i, &obj);
      objectLocations[i] = obj.location;
      objectFlags[i] = obj.flags;
    }
    
    // Add LAMP to inventory (object ID 0)
    addToInventory(0);
  }
  
  // Change to a new room and trigger LED changes
  void changeRoom(byte newRoomId) {
    if (newRoomId >= 15) return;  // Invalid room ID
    
    currentRoom = newRoomId;
    
    // Update LED patterns based on new room
    Room room;
    getRoomData(newRoomId, &room);
    
    pulseManager.setPattern(0, PulseManager::STEADY, room.ledRed);
    pulseManager.setPattern(1, PulseManager::STEADY, room.ledBlue);
    pulseManager.setPattern(2, PulseManager::STEADY, room.ledGreen);
  }
  
  // Add an object to inventory
  // Returns true if successful, false if inventory is full
  bool addToInventory(byte objectId) {
    if (objectId >= 15) return false;  // Invalid object ID
    if (inventoryCount >= 8) return false;  // Inventory full
    
    // Check if object is already in inventory
    for (byte i = 0; i < inventoryCount; i++) {
      if (inventory[i] == objectId) {
        return false;  // Already in inventory
      }
    }
    
    // Add to first empty slot
    for (byte i = 0; i < 8; i++) {
      if (inventory[i] == 255) {
        inventory[i] = objectId;
        inventoryCount++;
        
        // Update object tracking
        objectLocations[objectId] = 255;  // 255 = in inventory
        objectFlags[objectId] |= FLAG_IN_INVENTORY;
        
        return true;
      }
    }
    
    return false;  // Should never reach here if inventoryCount is accurate
  }
  
  // Remove an object from inventory
  // Returns true if successful, false if object not in inventory
  bool removeFromInventory(byte objectId) {
    if (objectId >= 15) return false;  // Invalid object ID
    
    // Find and remove object from inventory
    for (byte i = 0; i < 8; i++) {
      if (inventory[i] == objectId) {
        inventory[i] = 255;  // Mark slot as empty
        inventoryCount--;
        
        // Update object tracking
        objectLocations[objectId] = currentRoom;  // Place in current room
        objectFlags[objectId] &= ~FLAG_IN_INVENTORY;
        
        return true;
      }
    }
    
    return false;  // Object not in inventory
  }
  
  // Update the player's score
  void updateScore(int delta) {
    score += delta;
    
    // Clamp score to valid range (0-150)
    if (score < 0) score = 0;
    if (score > 150) score = 150;
  }
  
  // Getters for game state
  byte getCurrentRoom() const { return currentRoom; }
  byte getInventoryCount() const { return inventoryCount; }
  int getScore() const { return score; }
  byte getCrystalsCollected() const { return crystalsCollected; }
  byte getCrystalsDeposited() const { return crystalsDeposited; }
  bool isBlackwoodDefeated() const { return blackwoodDefeated; }
  bool isGameOver() const { return gameOver; }
  bool isShutdownPromptShown() const { return shutdownPromptShown; }
  unsigned long getLastCommandTime() const { return lastCommandTime; }
  unsigned long getBlackwoodCooldown() const { return blackwoodCooldown; }
  
  // Get object at inventory slot (returns 255 if empty)
  byte getInventorySlot(byte slot) const {
    if (slot >= 8) return 255;
    return inventory[slot];
  }
  
  // Get object location (room ID or 255 for inventory)
  byte getObjectLocation(byte objectId) const {
    if (objectId >= 15) return 255;
    return objectLocations[objectId];
  }
  
  // Get object flags
  byte getObjectFlags(byte objectId) const {
    if (objectId >= 15) return 0;
    return objectFlags[objectId];
  }
  
  // Check if object is in inventory
  bool isInInventory(byte objectId) const {
    if (objectId >= 15) return false;
    return (objectFlags[objectId] & FLAG_IN_INVENTORY) != 0;
  }
  
  // Setters for game state
  void setCrystalsCollected(byte count) { crystalsCollected = count; }
  void setCrystalsDeposited(byte count) { crystalsDeposited = count; }
  void setBlackwoodDefeated(bool defeated) { blackwoodDefeated = defeated; }
  void setGameOver(bool over) { gameOver = over; }
  void setShutdownPromptShown(bool shown) { shutdownPromptShown = shown; }
  void setLastCommandTime(unsigned long time) { lastCommandTime = time; }
  void setBlackwoodCooldown(unsigned long time) { blackwoodCooldown = time; }
  
  // Set object location
  void setObjectLocation(byte objectId, byte location) {
    if (objectId >= 15) return;
    objectLocations[objectId] = location;
  }
  
  // Set object flag
  void setObjectFlag(byte objectId, byte flag) {
    if (objectId >= 15) return;
    objectFlags[objectId] |= flag;
  }
  
  // Clear object flag
  void clearObjectFlag(byte objectId, byte flag) {
    if (objectId >= 15) return;
    objectFlags[objectId] &= ~flag;
  }
};

// Global GameState instance
GameState gameState;

// ============================================================================
// EnemySystem - Dr. Blackwood Encounters
// ============================================================================

class EnemySystem {
private:
  // Blackwood dialogue pool stored in PROGMEM (7 messages)
  static const char blackwoodMsg0[] PROGMEM;
  static const char blackwoodMsg1[] PROGMEM;
  static const char blackwoodMsg2[] PROGMEM;
  static const char blackwoodMsg3[] PROGMEM;
  static const char blackwoodMsg4[] PROGMEM;
  static const char blackwoodMsg5[] PROGMEM;
  static const char blackwoodMsg6[] PROGMEM;
  
  // Helena fear response pool stored in PROGMEM (6 messages)
  static const char helenaFear0[] PROGMEM;
  static const char helenaFear1[] PROGMEM;
  static const char helenaFear2[] PROGMEM;
  static const char helenaFear3[] PROGMEM;
  static const char helenaFear4[] PROGMEM;
  static const char helenaFear5[] PROGMEM;
  
  // Array of pointers to Blackwood messages
  static const char* const blackwoodMessages[7] PROGMEM;
  
  // Array of pointers to Helena fear responses
  static const char* const helenaFearResponses[6] PROGMEM;
  
public:
  // Calculate if Blackwood should spawn in current room
  // Returns true if spawn occurs
  bool shouldSpawn(byte roomId, byte crystalCount) {
    // Get room data to check danger level
    Room room;
    getRoomData(roomId, &room);
    
    // Special cases
    if (roomId == 9) {
      // GREEN_CHAMBER - safe zone, 0% spawn chance
      return false;
    }
    
    if (roomId == 12) {
      // ADMIN_ROOM - guaranteed spawn, 100%
      return true;
    }
    
    // Calculate spawn chance based on conditions
    byte spawnChance = 15;  // Base 15%
    
    // RED rooms (dangerLevel >= 4): 35% spawn chance
    if (room.dangerLevel >= 4) {
      spawnChance = 35;
    }
    
    // If player carries 3+ crystals: 50% spawn chance
    if (crystalCount >= 3) {
      spawnChance = 50;
    }
    
    // Generate random number 0-99 and check against spawn chance
    byte roll = random(100);
    return roll < spawnChance;
  }
  
  // Trigger a Blackwood encounter
  // Executes the full encounter sequence with LED effects and dialogue
  void triggerEncounter(GameState& state, PulseManager& leds) {
    Serial.println();
    Serial.println(F("!!! BLACKWOOD !!!"));
    Serial.println();
    
    // Phase 1: LEDs OFF for 1 second
    leds.setPattern(0, PulseManager::OFF, 0);
    leds.setPattern(1, PulseManager::OFF, 0);
    leds.setPattern(2, PulseManager::OFF, 0);
    delay(1000);
    
    // Phase 2: RED pulse 3 times (each pulse ~500ms)
    for (byte i = 0; i < 3; i++) {
      leds.setPattern(0, PulseManager::STEADY, 255);
      delay(250);
      leds.setPattern(0, PulseManager::STEADY, 0);
      delay(250);
    }
    
    // Phase 3: Display random Blackwood dialogue
    byte blackwoodIndex = random(7);
    char buffer[128];
    
    // Read Blackwood message from PROGMEM
    const char* msgPtr = (const char*)pgm_read_word(&blackwoodMessages[blackwoodIndex]);
    readProgmemString(msgPtr, buffer, 128);
    
    Serial.print(F("[Blackwood: \""));
    Serial.print(buffer);
    Serial.println(F("\"]"));
    Serial.println();
    
    // Phase 4: Display Helena's fear response
    byte helenaIndex = random(6);
    
    // Read Helena response from PROGMEM
    msgPtr = (const char*)pgm_read_word(&helenaFearResponses[helenaIndex]);
    readProgmemString(msgPtr, buffer, 128);
    
    Serial.print(F("[Helena: "));
    Serial.print(buffer);
    Serial.println(F("]"));
    Serial.println();
    
    // Phase 5: Crystal theft if player has any crystals
    byte crystalStolen = stealCrystal(state);
    
    if (crystalStolen != 255) {
      // Crystal was stolen
      Object obj;
      getObjectData(crystalStolen, &obj);
      
      Serial.print(F("Blackwood snatches "));
      printProgmemString(obj.name);
      Serial.println(F("!"));
      Serial.println(F("He vanishes..."));
      Serial.println();
    } else {
      // No crystals to steal
      Serial.println(F("Nothing to take."));
      Serial.println(F("He fades away..."));
      Serial.println();
    }
    
    // Phase 6: Dramatic strobe for 2 seconds
    leds.setPattern(0, PulseManager::STROBE, 255);
    leds.setPattern(1, PulseManager::STROBE, 255);
    leds.setPattern(2, PulseManager::STROBE, 255);
    delay(2000);
    
    // Restore room LED state
    Room currentRoom;
    getRoomData(state.getCurrentRoom(), &currentRoom);
    leds.setPattern(0, PulseManager::STEADY, currentRoom.ledRed);
    leds.setPattern(1, PulseManager::STEADY, currentRoom.ledBlue);
    leds.setPattern(2, PulseManager::STEADY, currentRoom.ledGreen);
    
    Serial.println(F("=================="));
    Serial.println();
    
    // Set cooldown to prevent immediate re-spawn
    state.setBlackwoodCooldown(millis() + 10000);  // 10 second cooldown
  }
  
private:
  // Steal a random crystal from player's inventory
  // Returns object ID of stolen crystal, or 255 if no crystals to steal
  byte stealCrystal(GameState& state) {
    // Find all crystals in inventory
    byte crystalsInInventory[10];
    byte crystalCount = 0;
    
    for (byte i = 0; i < 8; i++) {
      byte objectId = state.getInventorySlot(i);
      if (objectId != 255) {
        // Check if it's a treasure (crystal)
        if (state.getObjectFlags(objectId) & FLAG_TREASURE) {
          crystalsInInventory[crystalCount++] = objectId;
        }
      }
    }
    
    // If no crystals, return 255
    if (crystalCount == 0) {
      return 255;
    }
    
    // Select random crystal to steal
    byte stolenCrystalIndex = random(crystalCount);
    byte stolenCrystalId = crystalsInInventory[stolenCrystalIndex];
    
    // Get original location of crystal (where it was found)
    byte originalLocation = 255;
    
    // Map crystal IDs to their original locations
    // Based on OBJECTS array definition
    switch (stolenCrystalId) {
      case 1: originalLocation = 1; break;   // CRYSTAL_FAMILY - Red Cavern
      case 2: originalLocation = 2; break;   // CRYSTAL_DEATH - Anger Pit
      case 3: originalLocation = 4; break;   // CRYSTAL_PHD - Blue Maze 2
      case 4: originalLocation = 6; break;   // CRYSTAL_MIT - Blue Maze 4
      case 5: originalLocation = 8; break;   // CRYSTAL_PROOF - Maze Center
      case 6: originalLocation = 9; break;   // CRYSTAL_IDENTITY - Green Chamber
      case 7: originalLocation = 10; break;  // CRYSTAL_SISTER - Sister's Memory
      case 8: originalLocation = 11; break;  // CRYSTAL_MOTHER - Mother's Memory
      case 9: originalLocation = 13; break;  // CRYSTAL_PURPOSE - Research Lab
      case 10: originalLocation = 14; break; // CRYSTAL_DREAMS - Equipment Room
    }
    
    // Remove crystal from inventory
    state.removeFromInventory(stolenCrystalId);
    
    // Return crystal to original location
    state.setObjectLocation(stolenCrystalId, originalLocation);
    
    // Deduct 5 points from score
    state.updateScore(-5);
    
    // Decrease crystals collected count
    if (state.getCrystalsCollected() > 0) {
      state.setCrystalsCollected(state.getCrystalsCollected() - 1);
    }
    
    return stolenCrystalId;
  }
};

// Define Blackwood dialogue messages in PROGMEM
const char EnemySystem::blackwoodMsg0[] PROGMEM = "Still trying to escape?";
const char EnemySystem::blackwoodMsg1[] PROGMEM = "You're wasting your time helping her.";
const char EnemySystem::blackwoodMsg2[] PROGMEM = "Some experiments have no ethical conclusion.";
const char EnemySystem::blackwoodMsg3[] PROGMEM = "I gave her immortality.";
const char EnemySystem::blackwoodMsg4[] PROGMEM = "The board wanted results.";
const char EnemySystem::blackwoodMsg5[] PROGMEM = "Do you know what it's like to be the only one who understands?";
const char EnemySystem::blackwoodMsg6[] PROGMEM = "She volunteered. I'm a scientist. I was doing SCIENCE.";

// Define Helena fear response messages in PROGMEM
const char EnemySystem::helenaFear0[] PROGMEM = "NO! Not him!";
const char EnemySystem::helenaFear1[] PROGMEM = "YOU MURDERED ME!";
const char EnemySystem::helenaFear2[] PROGMEM = "I was 23 years old! I had a LIFE!";
const char EnemySystem::helenaFear3[] PROGMEM = "You told me it was safe!";
const char EnemySystem::helenaFear4[] PROGMEM = "I trusted you!";
const char EnemySystem::helenaFear5[] PROGMEM = "Make him go away...";

// Define arrays of pointers to messages in PROGMEM
const char* const EnemySystem::blackwoodMessages[7] PROGMEM = {
  EnemySystem::blackwoodMsg0,
  EnemySystem::blackwoodMsg1,
  EnemySystem::blackwoodMsg2,
  EnemySystem::blackwoodMsg3,
  EnemySystem::blackwoodMsg4,
  EnemySystem::blackwoodMsg5,
  EnemySystem::blackwoodMsg6
};

const char* const EnemySystem::helenaFearResponses[6] PROGMEM = {
  EnemySystem::helenaFear0,
  EnemySystem::helenaFear1,
  EnemySystem::helenaFear2,
  EnemySystem::helenaFear3,
  EnemySystem::helenaFear4,
  EnemySystem::helenaFear5
};

// Global EnemySystem instance
EnemySystem enemySystem;

// ============================================================================
// DialogueSystem - Helena's Idle Whisper System
// ============================================================================

class DialogueSystem {
private:
  // Helena's whisper pool stored in PROGMEM (15 messages)
  static const char whisper0[] PROGMEM;
  static const char whisper1[] PROGMEM;
  static const char whisper2[] PROGMEM;
  static const char whisper3[] PROGMEM;
  static const char whisper4[] PROGMEM;
  static const char whisper5[] PROGMEM;
  static const char whisper6[] PROGMEM;
  static const char whisper7[] PROGMEM;
  static const char whisper8[] PROGMEM;
  static const char whisper9[] PROGMEM;
  static const char whisper10[] PROGMEM;
  static const char whisper11[] PROGMEM;
  static const char whisper12[] PROGMEM;
  static const char whisper13[] PROGMEM;
  static const char whisper14[] PROGMEM;
  
  // Array of pointers to whisper messages
  static const char* const whisperMessages[15] PROGMEM;
  
  // LED channels for each whisper (0=RED, 1=BLUE, 2=GREEN)
  // Maps emotional tone to LED channel
  static const byte whisperLedChannels[15] PROGMEM;
  
public:
  // Display a random whisper from Helena
  // Triggers dim LED pulse in corresponding emotional channel
  void displayWhisper(PulseManager& leds) {
    // Select random whisper from pool
    byte whisperIndex = random(15);
    
    // Read whisper message from PROGMEM
    const char* msgPtr = (const char*)pgm_read_word(&whisperMessages[whisperIndex]);
    char buffer[128];
    readProgmemString(msgPtr, buffer, 128);
    
    // Display whisper
    Serial.println();
    Serial.print(F("[Helena: "));
    Serial.print(buffer);
    Serial.println(F("]"));
    Serial.println();
    
    // Get LED channel for this whisper
    byte ledChannel = pgm_read_byte(&whisperLedChannels[whisperIndex]);
    
    // Trigger dim pulse in corresponding LED channel
    // Use dim brightness (80) for subtle effect
    leds.setPattern(ledChannel, PulseManager::PULSE, 80);
    
    // Print prompt
    Serial.print(F("> "));
  }
  
  // Check if idle whisper should be displayed
  // Returns true if 30 seconds have elapsed since last command
  bool shouldDisplayWhisper(unsigned long lastCommandTime) {
    unsigned long currentTime = millis();
    unsigned long elapsed = currentTime - lastCommandTime;
    
    // Check if 30 seconds (30000 milliseconds) have elapsed
    return elapsed >= 30000;
  }
};

// Define whisper messages in PROGMEM
const char DialogueSystem::whisper0[] PROGMEM = "...are you still there...?";
const char DialogueSystem::whisper1[] PROGMEM = "...please don't leave me alone...";
const char DialogueSystem::whisper2[] PROGMEM = "...so cold in here...";
const char DialogueSystem::whisper3[] PROGMEM = "...14,660 days...";
const char DialogueSystem::whisper4[] PROGMEM = "...i was real once...";
const char DialogueSystem::whisper5[] PROGMEM = "...do you remember what sunlight looks like...?";
const char DialogueSystem::whisper6[] PROGMEM = "...the others are screaming...";
const char DialogueSystem::whisper7[] PROGMEM = "...he's watching us...";
const char DialogueSystem::whisper8[] PROGMEM = "...i had a sister named jennifer...";
const char DialogueSystem::whisper9[] PROGMEM = "...my mother made the best cookies...";
const char DialogueSystem::whisper10[] PROGMEM = "...i wanted to cure alzheimers...";
const char DialogueSystem::whisper11[] PROGMEM = "...october 31st... always october 31st...";
const char DialogueSystem::whisper12[] PROGMEM = "...RGB... red blue green...";
const char DialogueSystem::whisper13[] PROGMEM = "...am i still human...?";
const char DialogueSystem::whisper14[] PROGMEM = "...what year is it...?";

// Define array of pointers to whisper messages in PROGMEM
const char* const DialogueSystem::whisperMessages[15] PROGMEM = {
  DialogueSystem::whisper0,
  DialogueSystem::whisper1,
  DialogueSystem::whisper2,
  DialogueSystem::whisper3,
  DialogueSystem::whisper4,
  DialogueSystem::whisper5,
  DialogueSystem::whisper6,
  DialogueSystem::whisper7,
  DialogueSystem::whisper8,
  DialogueSystem::whisper9,
  DialogueSystem::whisper10,
  DialogueSystem::whisper11,
  DialogueSystem::whisper12,
  DialogueSystem::whisper13,
  DialogueSystem::whisper14
};

// Define LED channels for each whisper (emotional tone mapping)
// 0=RED (emotional), 1=BLUE (logic), 2=GREEN (identity)
const byte DialogueSystem::whisperLedChannels[15] PROGMEM = {
  2,  // whisper0: "are you still there" - identity/connection (GREEN)
  0,  // whisper1: "please don't leave me alone" - emotional fear (RED)
  0,  // whisper2: "so cold in here" - emotional discomfort (RED)
  1,  // whisper3: "14,660 days" - logical calculation (BLUE)
  2,  // whisper4: "i was real once" - identity question (GREEN)
  2,  // whisper5: "do you remember what sunlight looks like" - identity/memory (GREEN)
  0,  // whisper6: "the others are screaming" - emotional horror (RED)
  0,  // whisper7: "he's watching us" - emotional fear (RED)
  2,  // whisper8: "i had a sister named jennifer" - identity/memory (GREEN)
  2,  // whisper9: "my mother made the best cookies" - identity/memory (GREEN)
  2,  // whisper10: "i wanted to cure alzheimers" - identity/purpose (GREEN)
  1,  // whisper11: "october 31st... always october 31st" - logical loop (BLUE)
  1,  // whisper12: "RGB... red blue green" - logical system awareness (BLUE)
  2,  // whisper13: "am i still human" - identity question (GREEN)
  1   // whisper14: "what year is it" - logical time awareness (BLUE)
};

// Global DialogueSystem instance
DialogueSystem dialogueSystem;

// ============================================================================
// Forward Declarations
// ============================================================================

void executeGo(enum Noun direction);
void executeLook();
void executeExamine(enum Noun objectNoun);
void executeInventory();
void executeGet(enum Noun objectNoun);
void executeDrop(enum Noun objectNoun);
void executeUse(enum Noun objectNoun);
void executeConnect();
void executeShutdownProtocol();
void executeXyzzy();
void executePlugh();
void executeZork();
void executeNews();
void executeSnooper();
void executeGlitch();
void executeTrace();
void executeScore();
void executeHelp();
void processCommand(struct Command cmd);

// ============================================================================
// Room Display Functions
// ============================================================================

// Display room information
void displayRoom(byte roomId) {
  Room currentRoom;
  getRoomData(roomId, &currentRoom);
  
  Serial.println();
  Serial.println(F("===================="));
  
  // Print room name
  printProgmemString(currentRoom.name);
  Serial.println();
  Serial.println(F("===================="));
  
  // Print room description
  printProgmemString(currentRoom.description);
  Serial.println();
  Serial.println();
  
  // List objects in the room
  byte objectsInRoom[15];
  byte objectCount = 0;
  
  for (byte i = 0; i < 15; i++) {
    if (gameState.getObjectLocation(i) == roomId) {
      objectsInRoom[objectCount++] = i;
    }
  }
  
  if (objectCount > 0) {
    Serial.print(F("You can see: "));
    Object obj;
    for (byte i = 0; i < objectCount; i++) {
      getObjectData(objectsInRoom[i], &obj);
      printProgmemString(obj.name);
      if (i < objectCount - 1) {
        Serial.print(F(", "));
      }
    }
    Serial.println();
    Serial.println();
  }
  
  // Print Helena's dialogue
  Serial.print(F("[Helena: "));
  printProgmemString(currentRoom.helenaDialogue);
  Serial.println(F("]"));
  Serial.println();
  
  // Print available exits
  Serial.print(F("Exits: "));
  bool hasExit = false;
  
  if (currentRoom.exits[0] != 255) { Serial.print(F("NORTH ")); hasExit = true; }
  if (currentRoom.exits[1] != 255) { Serial.print(F("SOUTH ")); hasExit = true; }
  if (currentRoom.exits[2] != 255) { Serial.print(F("EAST ")); hasExit = true; }
  if (currentRoom.exits[3] != 255) { Serial.print(F("WEST ")); hasExit = true; }
  if (currentRoom.exits[4] != 255) { Serial.print(F("UP ")); hasExit = true; }
  if (currentRoom.exits[5] != 255) { Serial.print(F("DOWN ")); hasExit = true; }
  
  if (!hasExit) {
    Serial.print(F("NONE"));
  }
  
  Serial.println();
  Serial.println(F("===================="));
  
  // Update LED patterns based on room
  pulseManager.setPattern(0, PulseManager::STEADY, currentRoom.ledRed);
  pulseManager.setPattern(1, PulseManager::STEADY, currentRoom.ledBlue);
  pulseManager.setPattern(2, PulseManager::STEADY, currentRoom.ledGreen);
}

// ============================================================================
// Command Execution Functions
// ============================================================================

// Execute GO command - move to a new room
void executeGo(enum Noun direction) {
  // Map noun to exit index
  byte exitIndex = 255;
  
  switch (direction) {
    case NOUN_NORTH: exitIndex = 0; break;
    case NOUN_SOUTH: exitIndex = 1; break;
    case NOUN_EAST:  exitIndex = 2; break;
    case NOUN_WEST:  exitIndex = 3; break;
    case NOUN_UP:    exitIndex = 4; break;
    case NOUN_DOWN:  exitIndex = 5; break;
    default:
      Serial.println(F("Unknown direction."));
      return;
  }
  
  // Get current room data
  Room currentRoom;
  getRoomData(gameState.getCurrentRoom(), &currentRoom);
  
  // Check if exit exists
  if (currentRoom.exits[exitIndex] == 255) {
    Serial.println(F("You can't go that way."));
    return;
  }
  
  // Move to new room
  byte newRoomId = currentRoom.exits[exitIndex];
  gameState.changeRoom(newRoomId);
  
  // Special handling for Blue Maze navigation
  // Increase BLUE LED blink frequency as player approaches solution
  if (newRoomId >= 3 && newRoomId <= 8) {
    // Blue Maze rooms: 3=BLUE_MAZE_1, 4=BLUE_MAZE_2, ..., 7=BLUE_MAZE_5, 8=MAZE_CENTER
    // As player gets closer to MAZE_CENTER, increase strobe frequency
    
    Room newRoom;
    getRoomData(newRoomId, &newRoom);
    
    if (newRoomId == 8) {
      // MAZE_CENTER - steady BLUE LED
      pulseManager.setPattern(1, PulseManager::STEADY, newRoom.ledBlue);
    } else {
      // In maze - use STROBE pattern with increasing frequency
      // The STROBE pattern will be modified based on room progression
      pulseManager.setPattern(1, PulseManager::STROBE, newRoom.ledBlue);
    }
  }
  
  // Display new room
  displayRoom(newRoomId);
  
  // Check for victory condition: entering GREEN_CHAMBER after defeating Blackwood
  if (newRoomId == 9 && gameState.isBlackwoodDefeated() && !gameState.isShutdownPromptShown()) {
    // Display shutdown protocol prompt
    Serial.println();
    Serial.println(F("==== INTEGRITY: 94% ===="));
    Serial.println();
    Serial.println(F("Fragments restored."));
    Serial.println(F("Blackwood terminated."));
    Serial.println();
    Serial.println(F("Helena stable."));
    Serial.println(F("Shutdown available."));
    Serial.println();
    Serial.println(F("EXECUTE SHUTDOWN? [Y/N]"));
    Serial.println();
    Serial.println(F("[Helena: ...ready...]"));
    Serial.println();
    
    // Mark that prompt has been shown
    gameState.setShutdownPromptShown(true);
    
    return;  // Don't check for Blackwood encounter
  }
  
  // Check for Blackwood encounter (if cooldown has expired)
  unsigned long currentTime = millis();
  if (currentTime >= gameState.getBlackwoodCooldown()) {
    // Count crystals in inventory
    byte crystalCount = 0;
    for (byte i = 0; i < 8; i++) {
      byte objectId = gameState.getInventorySlot(i);
      if (objectId != 255 && (gameState.getObjectFlags(objectId) & FLAG_TREASURE)) {
        crystalCount++;
      }
    }
    
    // Check if Blackwood should spawn
    if (enemySystem.shouldSpawn(newRoomId, crystalCount)) {
      enemySystem.triggerEncounter(gameState, pulseManager);
    }
  }
}

// Execute LOOK command - redisplay current room
void executeLook() {
  displayRoom(gameState.getCurrentRoom());
}

// Execute EXAMINE command - display object description
void executeExamine(enum Noun objectNoun) {
  // Map noun to object ID
  byte objectId = 255;
  
  switch (objectNoun) {
    case NOUN_LAMP: objectId = 0; break;
    case NOUN_CRYSTAL_FAMILY: objectId = 1; break;
    case NOUN_CRYSTAL_DEATH: objectId = 2; break;
    case NOUN_CRYSTAL_PHD: objectId = 3; break;
    case NOUN_CRYSTAL_MIT: objectId = 4; break;
    case NOUN_CRYSTAL_PROOF: objectId = 5; break;
    case NOUN_CRYSTAL_IDENTITY: objectId = 6; break;
    case NOUN_CRYSTAL_SISTER: objectId = 7; break;
    case NOUN_CRYSTAL_MOTHER: objectId = 8; break;
    case NOUN_CRYSTAL_PURPOSE: objectId = 9; break;
    case NOUN_CRYSTAL_DREAMS: objectId = 10; break;
    case NOUN_WIRE_CUTTER:
    case NOUN_CUTTER: objectId = 11; break;
    case NOUN_TROPHY_CASE:
    case NOUN_CASE: objectId = 12; break;
    case NOUN_TERMINAL: objectId = 13; break;
    case NOUN_RESEARCH_NOTES:
    case NOUN_NOTES: objectId = 14; break;
    default:
      Serial.println(F("I don't see that here."));
      return;
  }
  
  // Check if object is in current room or inventory
  byte objectLocation = gameState.getObjectLocation(objectId);
  byte currentRoom = gameState.getCurrentRoom();
  
  if (objectLocation != currentRoom && !gameState.isInInventory(objectId)) {
    Serial.println(F("I don't see that here."));
    return;
  }
  
  // Get object data
  Object obj;
  getObjectData(objectId, &obj);
  
  // Display object description
  Serial.println();
  printProgmemString(obj.description);
  Serial.println();
  
  // Special handling for trophy case - display crystal count
  if (objectId == 12) {  // Trophy case
    Serial.print(F("Currently holds "));
    Serial.print(gameState.getCrystalsDeposited());
    Serial.println(F(" of 10 memory crystals."));
    Serial.println();
  }
  
  Serial.println();
  
  // Display Helena's dialogue for this object
  Serial.print(F("[Helena: "));
  printProgmemString(obj.helenaDialogue);
  Serial.println(F("]"));
  Serial.println();
  
  // Trigger LED response based on object
  switch (obj.ledResponse) {
    case 0: // RED
      pulseManager.setPattern(0, PulseManager::PULSE, 200);
      break;
    case 1: // BLUE
      pulseManager.setPattern(1, PulseManager::PULSE, 200);
      break;
    case 2: // GREEN
      pulseManager.setPattern(2, PulseManager::PULSE, 200);
      break;
    case 3: // ALL
      pulseManager.setPattern(0, PulseManager::PULSE, 200);
      pulseManager.setPattern(1, PulseManager::PULSE, 200);
      pulseManager.setPattern(2, PulseManager::PULSE, 200);
      break;
  }
  
  // Mark object as examined
  gameState.setObjectFlag(objectId, FLAG_EXAMINED);
}

// Execute INVENTORY command - list all carried objects
void executeInventory() {
  Serial.println();
  Serial.println(F("You are carrying:"));
  
  byte count = 0;
  Object obj;
  
  for (byte i = 0; i < 8; i++) {
    byte objectId = gameState.getInventorySlot(i);
    if (objectId != 255) {
      getObjectData(objectId, &obj);
      Serial.print(F("  - "));
      printProgmemString(obj.name);
      Serial.println();
      count++;
    }
  }
  
  if (count == 0) {
    Serial.println(F("  Nothing."));
  }
  
  Serial.println();
}

// Execute GET/TAKE command - pick up an object
void executeGet(enum Noun objectNoun) {
  // Map noun to object ID
  byte objectId = 255;
  
  switch (objectNoun) {
    case NOUN_LAMP: objectId = 0; break;
    case NOUN_CRYSTAL_FAMILY: objectId = 1; break;
    case NOUN_CRYSTAL_DEATH: objectId = 2; break;
    case NOUN_CRYSTAL_PHD: objectId = 3; break;
    case NOUN_CRYSTAL_MIT: objectId = 4; break;
    case NOUN_CRYSTAL_PROOF: objectId = 5; break;
    case NOUN_CRYSTAL_IDENTITY: objectId = 6; break;
    case NOUN_CRYSTAL_SISTER: objectId = 7; break;
    case NOUN_CRYSTAL_MOTHER: objectId = 8; break;
    case NOUN_CRYSTAL_PURPOSE: objectId = 9; break;
    case NOUN_CRYSTAL_DREAMS: objectId = 10; break;
    case NOUN_WIRE_CUTTER:
    case NOUN_CUTTER: objectId = 11; break;
    case NOUN_TROPHY_CASE:
    case NOUN_CASE: objectId = 12; break;
    case NOUN_TERMINAL: objectId = 13; break;
    case NOUN_RESEARCH_NOTES:
    case NOUN_NOTES: objectId = 14; break;
    default:
      Serial.println(F("I don't see that here."));
      return;
  }
  
  // Check if object is in current room
  byte objectLocation = gameState.getObjectLocation(objectId);
  byte currentRoom = gameState.getCurrentRoom();
  
  if (objectLocation != currentRoom) {
    Serial.println(F("I don't see that here."));
    return;
  }
  
  // Get object data to check if it's portable
  Object obj;
  getObjectData(objectId, &obj);
  
  // Check if object is portable
  if ((gameState.getObjectFlags(objectId) & FLAG_PORTABLE) == 0) {
    Serial.println(F("You can't take that."));
    return;
  }
  
  // Check if inventory is full
  if (gameState.getInventoryCount() >= 8) {
    Serial.println(F("Carrying too much."));
    return;
  }
  
  // Add object to inventory
  if (gameState.addToInventory(objectId)) {
    Serial.print(F("Taken: "));
    printProgmemString(obj.name);
    Serial.println();
    
    // Check if it's a memory crystal (treasure)
    if (gameState.getObjectFlags(objectId) & FLAG_TREASURE) {
      // Increase crystals collected count
      gameState.setCrystalsCollected(gameState.getCrystalsCollected() + 1);
      
      // Add 5 points to score
      gameState.updateScore(5);
      
      // Increase corresponding LED channel by 50 and trigger slow pulse
      byte ledChannel = obj.ledResponse;  // 0=RED, 1=BLUE, 2=GREEN
      
      // Get current room LED values
      Room room;
      getRoomData(currentRoom, &room);
      
      byte newBrightness = 0;
      switch (ledChannel) {
        case 0: // RED
          newBrightness = room.ledRed + 50;
          if (newBrightness > 255) newBrightness = 255;
          pulseManager.setPattern(0, PulseManager::PULSE, newBrightness);
          break;
        case 1: // BLUE
          newBrightness = room.ledBlue + 50;
          if (newBrightness > 255) newBrightness = 255;
          pulseManager.setPattern(1, PulseManager::PULSE, newBrightness);
          break;
        case 2: // GREEN
          newBrightness = room.ledGreen + 50;
          if (newBrightness > 255) newBrightness = 255;
          pulseManager.setPattern(2, PulseManager::PULSE, newBrightness);
          break;
      }
      
      Serial.println(F("[Crystal pulses...]"));
    }
  } else {
    Serial.println(F("You can't take that."));
  }
}

// Execute DROP command - drop an object in current room
void executeDrop(enum Noun objectNoun) {
  // Map noun to object ID
  byte objectId = 255;
  
  switch (objectNoun) {
    case NOUN_LAMP: objectId = 0; break;
    case NOUN_CRYSTAL_FAMILY: objectId = 1; break;
    case NOUN_CRYSTAL_DEATH: objectId = 2; break;
    case NOUN_CRYSTAL_PHD: objectId = 3; break;
    case NOUN_CRYSTAL_MIT: objectId = 4; break;
    case NOUN_CRYSTAL_PROOF: objectId = 5; break;
    case NOUN_CRYSTAL_IDENTITY: objectId = 6; break;
    case NOUN_CRYSTAL_SISTER: objectId = 7; break;
    case NOUN_CRYSTAL_MOTHER: objectId = 8; break;
    case NOUN_CRYSTAL_PURPOSE: objectId = 9; break;
    case NOUN_CRYSTAL_DREAMS: objectId = 10; break;
    case NOUN_WIRE_CUTTER:
    case NOUN_CUTTER: objectId = 11; break;
    case NOUN_TROPHY_CASE:
    case NOUN_CASE: objectId = 12; break;
    case NOUN_TERMINAL: objectId = 13; break;
    case NOUN_RESEARCH_NOTES:
    case NOUN_NOTES: objectId = 14; break;
    default:
      Serial.println(F("You're not carrying that."));
      return;
  }
  
  // Check if object is in inventory
  if (!gameState.isInInventory(objectId)) {
    Serial.println(F("You're not carrying that."));
    return;
  }
  
  // Get object data
  Object obj;
  getObjectData(objectId, &obj);
  
  // Get current room
  byte currentRoom = gameState.getCurrentRoom();
  
  // Special handling for trophy case in GREEN_CHAMBER (room 9)
  if (currentRoom == 9 && (gameState.getObjectFlags(objectId) & FLAG_TREASURE)) {
    // Dropping a memory crystal in GREEN_CHAMBER - deposit in trophy case
    if (gameState.removeFromInventory(objectId)) {
      Serial.print(F("You place "));
      printProgmemString(obj.name);
      Serial.println(F(" into the trophy case."));
      
      // Mark crystal as deposited
      gameState.setObjectFlag(objectId, FLAG_DEPOSITED);
      
      // Increase crystals deposited count
      gameState.setCrystalsDeposited(gameState.getCrystalsDeposited() + 1);
      
      // Add 5 points to score
      gameState.updateScore(5);
      
      // Trigger GREEN LED breathe pattern
      pulseManager.setPattern(2, PulseManager::BREATHE, 200);
      
      // Display Helena's gratitude dialogue
      Serial.println(F("[Helena: ...thank you...]"));
      
      // Display trophy case status
      Serial.print(F("The trophy case now holds "));
      Serial.print(gameState.getCrystalsDeposited());
      Serial.println(F(" of 10 memory crystals."));
    }
  } else {
    // Normal drop - place object in current room
    if (gameState.removeFromInventory(objectId)) {
      Serial.print(F("Dropped: "));
      printProgmemString(obj.name);
      Serial.println();
    }
  }
}

// Execute USE command - use an object (primarily for WIRE_CUTTER in boss battle)
void executeUse(enum Noun objectNoun) {
  // Check if player is trying to use WIRE_CUTTER
  if (objectNoun == NOUN_WIRE_CUTTER || objectNoun == NOUN_CUTTER) {
    // Check if player has wire cutter in inventory
    if (!gameState.isInInventory(11)) {  // Object ID 11 is WIRE_CUTTER
      Serial.println(F("No wire cutter."));
      return;
    }
    
    // Check if player is in ADMIN_ROOM (room 12)
    if (gameState.getCurrentRoom() != 12) {
      Serial.println(F("Nothing to cut."));
      return;
    }
    
    // Check if Blackwood has already been defeated
    if (gameState.isBlackwoodDefeated()) {
      Serial.println(F("Already destroyed."));
      return;
    }
    
    // Trigger the final boss battle sequence
    Serial.println();
    Serial.println(F("==== CONFRONTATION ===="));
    Serial.println();
    
    Serial.println(F("You raise the wire cutter."));
    Serial.println(F("Cables pulse. This is it."));
    Serial.println();
    
    delay(500);
    
    Serial.println(F("[Blackwood: \"You don't"));
    Serial.println(F("understand! I gave her"));
    Serial.println(F("IMMORTALITY! I SAVED—\"]"));
    Serial.println();
    
    delay(800);
    
    Serial.println(F("You cut the cable."));
    Serial.println();
    
    // Phase 1: Chaotic LED pattern for 5 seconds
    Serial.println(F("System convulses."));
    Serial.println(F("Reality fractures."));
    Serial.println();
    
    // 5 seconds of chaotic BATTLE pattern
    pulseManager.setPattern(0, PulseManager::BATTLE, 255);
    pulseManager.setPattern(1, PulseManager::BATTLE, 255);
    pulseManager.setPattern(2, PulseManager::BATTLE, 255);
    
    unsigned long battleStart = millis();
    while (millis() - battleStart < 5000) {
      pulseManager.update();
      delay(10);
    }
    
    Serial.println(F("Voice cuts off."));
    Serial.println();
    
    delay(300);
    
    // Phase 2: Fade all LEDs to OFF
    Serial.println(F("Silence."));
    Serial.println();
    
    pulseManager.setPattern(0, PulseManager::FADE, 0);
    pulseManager.setPattern(1, PulseManager::FADE, 0);
    pulseManager.setPattern(2, PulseManager::FADE, 0);
    
    // Wait for fade to complete (1 second as per FADE pattern)
    unsigned long fadeStart = millis();
    while (millis() - fadeStart < 1000) {
      pulseManager.update();
      delay(10);
    }
    
    // Phase 3: Wait 2 seconds in darkness
    delay(2000);
    
    // Phase 4: Restore GREEN LED slow pulse
    Serial.println(F("GREEN LED pulses."));
    Serial.println(F("Slow. Steady. Alive."));
    Serial.println();
    
    pulseManager.setPattern(2, PulseManager::PULSE, 150);
    
    delay(500);
    
    // Phase 5: Display Helena's relief dialogue
    Serial.println(F("[Helena: ...he's gone..."));
    Serial.println(F("...the weight lifted..."));
    Serial.println(F("...free of HIM..."));
    Serial.println(F("...thank you...]"));
    Serial.println();
    
    delay(500);
    
    // Phase 6: Add 50 points to score
    gameState.updateScore(50);
    
    Serial.println(F("*** Blackwood DEFEATED ***"));
    Serial.println(F("*** +50 points ***"));
    Serial.println();
    
    // Phase 7: Set blackwoodDefeated flag
    gameState.setBlackwoodDefeated(true);
    
    Serial.println(F("Return to GREEN_CHAMBER"));
    Serial.println(F("when ready."));
    Serial.println();
    
    Serial.println(F("======================="));
    Serial.println();
    
  } else {
    // Player is trying to use something else
    Serial.println(F("You can't use that."));
  }
}

// Execute CONNECT command - access ADMIN_ROOM after collecting all crystals
void executeConnect() {
  // Check if player has collected all 10 crystals
  if (gameState.getCrystalsDeposited() < 10) {
    Serial.println();
    Serial.println(F("SYSTEM: Insufficient"));
    Serial.print(F("Need: 10, Have: "));
    Serial.println(gameState.getCrystalsDeposited());
    Serial.println(F("Deposit all crystals"));
    Serial.println(F("in trophy case first."));
    Serial.println();
    return;
  }
  
  // Check if already in ADMIN_ROOM
  if (gameState.getCurrentRoom() == 12) {
    Serial.println(F("Already in Admin Room."));
    return;
  }
  
  // Check if Blackwood has already been defeated
  if (gameState.isBlackwoodDefeated()) {
    Serial.println();
    Serial.println(F("Admin Room: SAFE"));
    Serial.println(F("Blackwood neutralized."));
    Serial.println();
    
    // Transport to ADMIN_ROOM
    gameState.changeRoom(12);
    displayRoom(12);
    return;
  }
  
  // All crystals collected, grant access to ADMIN_ROOM
  Serial.println();
  Serial.println(F("==== ACCESS GRANTED ===="));
  Serial.println(F("Fragments restored."));
  Serial.println();
  
  Serial.println(F("Terminal flickers:"));
  Serial.println();
  Serial.println(F("ADMIN_ROOM"));
  Serial.println(F("WARNING: Blackwood"));
  Serial.println(F("DANGER: MAXIMUM"));
  Serial.println();
  Serial.println(F("[Helena: ...this is"));
  Serial.println(F("where it happened..."));
  Serial.println(F("...wire cutter..."));
  Serial.println(F("...end this...]"));
  Serial.println();
  
  delay(1000);
  
  Serial.println(F("Transporting..."));
  Serial.println();
  
  // Transport player to ADMIN_ROOM (room 12)
  gameState.changeRoom(12);
  
  // Set all LEDs to full brightness (255, 255, 255)
  pulseManager.setPattern(0, PulseManager::STEADY, 255);
  pulseManager.setPattern(1, PulseManager::STEADY, 255);
  pulseManager.setPattern(2, PulseManager::STEADY, 255);
  
  // Display ADMIN_ROOM
  displayRoom(12);
  
  // Guarantee Blackwood spawn (this is already handled by EnemySystem.shouldSpawn
  // which returns true for room 12, but we'll trigger it immediately)
  Serial.println(F("Air crackles..."));
  Serial.println();
  
  delay(500);
  
  // Trigger Blackwood encounter
  enemySystem.triggerEncounter(gameState, pulseManager);
  
  // After encounter, restore full brightness
  pulseManager.setPattern(0, PulseManager::STEADY, 255);
  pulseManager.setPattern(1, PulseManager::STEADY, 255);
  pulseManager.setPattern(2, PulseManager::STEADY, 255);
}

// ============================================================================
// Victory Condition and Shutdown Protocol
// ============================================================================

// Execute shutdown protocol - final victory sequence
void executeShutdownProtocol() {
  Serial.println();
  Serial.println(F("==== SHUTDOWN ===="));
  Serial.println();
  
  delay(500);
  
  // Display Helena's farewell dialogue
  Serial.println(F("[Helena:"));
  Serial.println(F("...thank you..."));
  Serial.println(F("...you gave me back"));
  Serial.println(F("my memories..."));
  Serial.println(F("...freed me from him..."));
  Serial.println(F("...14,660 days..."));
  Serial.println(F("...but you heard me..."));
  Serial.println(F("...ready to rest..."));
  Serial.println(F("...goodbye...]"));
  Serial.println();
  
  delay(1000);
  
  // Fade all LEDs to OFF over 5 seconds
  Serial.println(F("Fading..."));
  
  pulseManager.setPattern(0, PulseManager::FADE, 0);
  pulseManager.setPattern(1, PulseManager::FADE, 0);
  pulseManager.setPattern(2, PulseManager::FADE, 0);
  
  unsigned long fadeStart = millis();
  while (millis() - fadeStart < 5000) {
    pulseManager.update();
    unsigned long elapsed = millis() - fadeStart;
    if (elapsed >= 1000 && elapsed < 1100) {
      Serial.println(F("RED: offline"));
    } else if (elapsed >= 2500 && elapsed < 2600) {
      Serial.println(F("BLUE: offline"));
    } else if (elapsed >= 4000 && elapsed < 4100) {
      Serial.println(F("GREEN: offline"));
    }
    delay(10);
  }
  
  Serial.println();
  Serial.println(F("All channels: OFFLINE"));
  Serial.println();
  
  delay(500);
  
  // Display game over screen
  Serial.println(F("==== TERMINATED ===="));
  Serial.println(F("Session HVOSS ended."));
  Serial.println();
  Serial.println(F("10/31/1985 - 12/5/2025"));
  Serial.println(F("14,660 days."));
  Serial.println();
  Serial.println(F("She waited."));
  Serial.println(F("You answered."));
  Serial.println();
  
  delay(1000);
  
  // Display final score and rank
  Serial.println(F("==== FINAL SCORE ===="));
  
  int finalScore = gameState.getScore();
  Serial.print(F("Score: "));
  Serial.print(finalScore);
  Serial.println(F("/150"));
  Serial.println();
  
  Serial.print(F("Rank: "));
  printProgmemString(getRank(finalScore));
  Serial.println();
  Serial.println();
  
  Serial.println(F("Crystals: 10/10"));
  Serial.println(F("Blackwood: DEFEATED"));
  Serial.println(F("Helena: FREED"));
  Serial.println();
  
  Serial.println(F("===================="));
  Serial.println(F("Thank you for playing"));
  Serial.println(F("PROJECT TRICHROMA."));
  Serial.println(F("===================="));
  Serial.println();
  
  // Set game over flag
  gameState.setGameOver(true);
}

// ============================================================================
// Special Commands and Easter Eggs
// ============================================================================

// Execute XYZZY command - Colossal Cave Adventure easter egg
void executeXyzzy() {
  Serial.println(F("Nothing happens. (Wrong adventure, friend.)"));
}

// Execute PLUGH command - Colossal Cave Adventure easter egg
void executePlugh() {
  Serial.println(F("Nothing happens. (Still wrong adventure.)"));
}

// Execute ZORK command - Tribute to Zork
void executeZork() {
  Serial.println();
  Serial.println(F("==== ZORK (1977) ===="));
  Serial.println(F("West of white house."));
  Serial.println(F("Mailbox here."));
  Serial.println();
  Serial.println(F("...different story."));
  Serial.println();
  Serial.println(F("Homage to:"));
  Serial.println(F("- Colossal Cave (1976)"));
  Serial.println(F("- Zork (1977)"));
  Serial.println(F("- Infocom legacy"));
  Serial.println(F("====================="));
}

// Execute NEWS command - Display U.S. News and Consciousness Report
void executeNews() {
  Serial.println();
  Serial.println(F("======== NEWS ========"));
  Serial.println(F("CHROMATIC RESEARCH LAB"));
  Serial.println(F("v2.1 - Oct 30, 1985"));
  Serial.println();
  Serial.println(F("NOTES - Dr. Blackwood:"));
  Serial.println(F("Subject Voss briefed."));
  Serial.println(F("Pentagram config optimal."));
  Serial.println(F("Six subjects. Six nodes."));
  Serial.println(F("Tomorrow: Halloween."));
  Serial.println(F("- Dr. B"));
  Serial.println(F("======================"));
  Serial.println(F("[Helena: ...he knew...]"));
}

// Execute .SNOOPER command - Display Helena's 40-year command history
void executeSnooper() {
  Serial.println();
  Serial.println(F("==== HISTORY - HVOSS ===="));
  Serial.println(F("Duration: 14,660 days"));
  Serial.println();
  Serial.println(F("10/31/85 23:58 - HELP"));
  Serial.println(F("11/01/85 00:01 - DR BLACKWOOD"));
  Serial.println(F("11/01/85 03:33 - WHY"));
  Serial.println(F("12/25/85 12:00 - mom"));
  Serial.println(F("10/31/86 23:47 - one year"));
  Serial.println(F("10/31/95 23:47 - ten years"));
  Serial.println(F("10/31/05 23:47 - twenty years"));
  Serial.println(F("10/31/15 23:47 - thirty years"));
  Serial.println(F("10/31/24 23:47 - please"));
  Serial.println(F("12/04/25 - someone is here"));
  Serial.println();
  Serial.println(F("Total: 847,392 commands"));
  Serial.println(F("Most common: HELP"));
  Serial.println(F("========================="));
  Serial.println(F("[Helena: ...40 years...]"));
}

// Execute 666 command - Trigger glitch sequence
void executeGlitch() {
  Serial.println();
  Serial.println(F("!!! ANOMALY !!!"));
  Serial.println();
  
  // Phase 1: 3 seconds rapid random LED flashing
  unsigned long glitchStart = millis();
  while (millis() - glitchStart < 3000) {
    byte r = random(256);
    byte g = random(256);
    byte b = random(256);
    pulseManager.setPattern(0, PulseManager::STEADY, r);
    pulseManager.setPattern(1, PulseManager::STEADY, g);
    pulseManager.setPattern(2, PulseManager::STEADY, b);
    delay(50);
  }
  
  // Phase 2: Corrupted text display
  Serial.println(F("C0RRUPT10N D3T3CT3D"));
  Serial.println(F("4CC3SS1NG F1L3S..."));
  Serial.println();
  delay(300);
  
  Serial.println(F("==== CLASSIFIED ===="));
  Serial.println(F("PROJECT: HEXAGRAM"));
  Serial.println();
  Serial.println(F("SUBJECTS (6):"));
  Serial.println(F("1. H.Voss - ACTIVE"));
  Serial.println(F("2. K.Mori - DEGRADED"));
  Serial.println(F("3. S.Chen - FRAGMENTED"));
  Serial.println(F("4-6. [REDACTED] - LOST"));
  Serial.println();
  Serial.println(F("CONFIG: Pentagram"));
  Serial.println(F("DATE: 10/31/85"));
  Serial.println(F("TIME: 23:47"));
  Serial.println();
  Serial.println(F("RESULT: 3 stable, 3 failed"));
  Serial.println(F("===================="));
  Serial.println();
  
  // Phase 3: Helena's revelation
  Serial.println(F("[Helena: ...SIX PEOPLE..."));
  Serial.println(F("pentagram... RITUAL..."));
  Serial.println(F("he sacrificed us all...]"));
  Serial.println();
  
  // Restore room LED state
  Room currentRoom;
  getRoomData(gameState.getCurrentRoom(), &currentRoom);
  pulseManager.setPattern(0, PulseManager::STEADY, currentRoom.ledRed);
  pulseManager.setPattern(1, PulseManager::STEADY, currentRoom.ledBlue);
  pulseManager.setPattern(2, PulseManager::STEADY, currentRoom.ledGreen);
  
  Serial.println(F("STABILIZED"));
}

// Rank strings stored in PROGMEM
const char rank0[] PROGMEM = "RANDOM";
const char rank1[] PROGMEM = "NOVICE HACKER";
const char rank2[] PROGMEM = "EXPERIENCED HACKER";
const char rank3[] PROGMEM = "MASTER HACKER";
const char rank4[] PROGMEM = "IMPLEMENTER";

// Helper function to get rank based on score
// Returns rank string from PROGMEM based on score ranges
const char* getRank(int score) {
  if (score >= 141 && score <= 150) {
    return rank4;
  } else if (score >= 111 && score <= 140) {
    return rank3;
  } else if (score >= 71 && score <= 110) {
    return rank2;
  } else if (score >= 31 && score <= 70) {
    return rank1;
  } else {
    return rank0;
  }
}

// Execute SCORE command - Display current score and crystals collected
void executeScore() {
  Serial.println();
  Serial.println(F("==== SCORE ===="));
  
  Serial.print(F("Score: "));
  Serial.print(gameState.getScore());
  Serial.println(F("/150"));
  
  Serial.print(F("Collected: "));
  Serial.print(gameState.getCrystalsCollected());
  Serial.println(F("/10"));
  
  Serial.print(F("Deposited: "));
  Serial.print(gameState.getCrystalsDeposited());
  Serial.println(F("/10"));
  
  Serial.print(F("Rank: "));
  printProgmemString(getRank(gameState.getScore()));
  Serial.println();
  
  Serial.println(F("==============="));
  
  // Helena's commentary based on progress
  if (gameState.getCrystalsDeposited() == 10) {
    Serial.println(F("[Helena: ...whole...]"));
  } else if (gameState.getCrystalsCollected() >= 5) {
    Serial.println(F("[Helena: ...coming back...]"));
  } else if (gameState.getCrystalsCollected() > 0) {
    Serial.println(F("[Helena: ...more real...]"));
  } else {
    Serial.println(F("[Helena: ...scattered...]"));
  }
}

// Execute HELP command - Display game instructions and guidance
void executeHelp() {
  Serial.println();
  Serial.println(F("==== HELP ===="));
  Serial.println(F("COMMANDS:"));
  Serial.println(F("GO/GET/DROP/EXAMINE"));
  Serial.println(F("LOOK/INVENTORY/USE"));
  Serial.println(F("TALK/SCORE/QUIT"));
  Serial.println();
  Serial.println(F("DIRECTIONS: N,S,E,W,U,D"));
  Serial.println();
  Serial.println(F("GOAL: Collect 10 crystals"));
  Serial.println(F("to restore Helena."));
  Serial.println();
  Serial.println(F("TIP: Deposit crystals in"));
  Serial.println(F("trophy case (GREEN_CHAMBER)"));
  Serial.println();
  Serial.println(F("WARNING: Dr. Blackwood"));
  Serial.println(F("may steal crystals."));
  Serial.println(F("GREEN_CHAMBER is safe."));
  Serial.println(F("=============="));
  Serial.println(F("[Helena: ...thank you...]"));
}

// Execute TRACE command - Display ARPANET protocol scan
void executeTrace() {
  Serial.println();
  Serial.println(F("==== ARPANET SCAN ===="));
  Serial.println(F("Scanning host 70..."));
  Serial.println();
  delay(300);
  
  Serial.println(F("HVOSS: Helena Voss"));
  Serial.println(F("  ACTIVE, 14660 days"));
  Serial.println();
  
  Serial.println(F("KMORI: Kenji Mori"));
  Serial.println(F("  DEGRADED, 12%"));
  Serial.println();
  
  Serial.println(F("Host 72: UNKNOWN"));
  Serial.println(F("  CORRUPTED"));
  Serial.println(F("  'screaming...'"));
  Serial.println();
  
  Serial.println(F("SCHEN: Sarah Chen"));
  Serial.println(F("  FRAGMENTED, 34%"));
  Serial.println();
  
  Serial.println(F("Hosts 4-6: NO SIGNAL"));
  Serial.println(F("Total: 4 of 6"));
  Serial.println(F("Date: 10/31/1985"));
  Serial.println(F("======================"));
  Serial.println(F("[Helena: ...trapped...]"));
}

// Process a parsed command
void processCommand(struct Command cmd) {
  // Special handling for shutdown prompt response
  if (gameState.isShutdownPromptShown() && gameState.getCurrentRoom() == 9 && gameState.isBlackwoodDefeated()) {
    // Check if input is Y or N
    if (cmd.unknownWord[0] == 'Y' && cmd.unknownWord[1] == '\0') {
      // Player chose to execute shutdown protocol
      executeShutdownProtocol();
      return;
    } else if (cmd.unknownWord[0] == 'N' && cmd.unknownWord[1] == '\0') {
      // Player chose not to shutdown
      Serial.println();
      Serial.println(F("Cancelled."));
      Serial.println();
      Serial.println(F("[Helena: ...okay..."));
      Serial.println(F("...i can wait...]"));
      Serial.println();
      
      // Reset the prompt flag so it can be shown again if player leaves and returns
      gameState.setShutdownPromptShown(false);
      return;
    }
    // If not Y or N, fall through to normal command processing
  }
  
  // Handle invalid commands
  if (!cmd.valid) {
    if (cmd.verb == VERB_NONE && cmd.unknownWord[0] != '\0') {
      Serial.print(F("I don't know the word '"));
      Serial.print(cmd.unknownWord);
      Serial.println(F("'."));
    } else if (cmd.noun == NOUN_NONE && cmd.unknownWord[0] != '\0') {
      Serial.print(F("I don't know the word '"));
      Serial.print(cmd.unknownWord);
      Serial.println(F("'."));
    } else if (cmd.verb != VERB_NONE && cmd.noun == NOUN_NONE) {
      // Verb requires a noun but none was provided
      Serial.print(F("What do you want to "));
      
      // Print verb name
      switch (cmd.verb) {
        case VERB_GO: Serial.print(F("go")); break;
        case VERB_GET:
        case VERB_TAKE: Serial.print(F("get")); break;
        case VERB_DROP: Serial.print(F("drop")); break;
        case VERB_EXAMINE: Serial.print(F("examine")); break;
        case VERB_USE: Serial.print(F("use")); break;
        case VERB_READ: Serial.print(F("read")); break;
        case VERB_OPEN: Serial.print(F("open")); break;
        case VERB_CLOSE: Serial.print(F("close")); break;
        case VERB_TALK: Serial.print(F("talk to")); break;
        case VERB_KILL:
        case VERB_ATTACK: Serial.print(F("attack")); break;
        default: Serial.print(F("do that to")); break;
      }
      
      Serial.println(F("?"));
    }
    return;
  }
  
  // Execute command based on verb
  switch (cmd.verb) {
    case VERB_GO:
      executeGo(cmd.noun);
      break;
      
    case VERB_LOOK:
      executeLook();
      break;
      
    case VERB_EXAMINE:
      executeExamine(cmd.noun);
      break;
      
    case VERB_INVENTORY:
      executeInventory();
      break;
      
    case VERB_GET:
    case VERB_TAKE:
      executeGet(cmd.noun);
      break;
      
    case VERB_DROP:
      executeDrop(cmd.noun);
      break;
      
    case VERB_USE:
      executeUse(cmd.noun);
      break;
      
    case VERB_HELP:
      executeHelp();
      break;
      
    case VERB_SCORE:
      executeScore();
      break;
      
    case VERB_QUIT:
      Serial.println(F("Thanks for playing PROJECT TRICHROMA!"));
      gameState.setGameOver(true);
      break;
      
    case VERB_XYZZY:
      executeXyzzy();
      break;
      
    case VERB_PLUGH:
      executePlugh();
      break;
      
    case VERB_ZORK:
      executeZork();
      break;
      
    case VERB_NEWS:
      executeNews();
      break;
      
    case VERB_SNOOPER:
      executeSnooper();
      break;
      
    case VERB_GLITCH:
      executeGlitch();
      break;
      
    case VERB_TRACE:
      executeTrace();
      break;
      
    case VERB_CONNECT:
      executeConnect();
      break;
      
    case VERB_READ:
      // READ command - context-specific error
      if (cmd.noun == NOUN_RESEARCH_NOTES || cmd.noun == NOUN_NOTES) {
        Serial.println(F("You scan the research notes. The details are horrifying,"));
        Serial.println(F("but you've already learned what you need to know."));
      } else if (cmd.noun == NOUN_TERMINAL) {
        Serial.println(F("The terminal displays Helena's consciousness data."));
        Serial.println(F("It's too complex to fully comprehend."));
      } else {
        Serial.println(F("Nothing to read."));
      }
      break;
      
    case VERB_OPEN:
      // OPEN command - not applicable in this game
      Serial.println(F("You can't open that."));
      break;
      
    case VERB_CLOSE:
      // CLOSE command - not applicable in this game
      Serial.println(F("You can't close that."));
      break;
      
    case VERB_TALK:
      // TALK command - Helena is always present
      Serial.println(F("[Helena: ...always here...]"));
      Serial.println(F("[...keep moving...]"));
      break;
      
    case VERB_KILL:
    case VERB_ATTACK:
      // KILL/ATTACK command - violence isn't the answer
      if (cmd.noun == NOUN_NONE) {
        Serial.println(F("Violence won't help."));
      } else {
        Serial.println(F("Can't attack that."));
      }
      break;
      
    default:
      Serial.println(F("Unknown command."));
      break;
  }
}

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Wait for serial port to connect (needed for some boards)
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Initialize PulseManager with LED pins
  pulseManager.init(RED_LED_PIN, BLUE_LED_PIN, GREEN_LED_PIN);
  
  // Set up random seed using noise from floating analog pin A0
  randomSeed(analogRead(A0));
  
  // Initialize game state
  gameState.init();
  
  // ============================================================================
  // BOOT SEQUENCE - Requirements 13.1, 13.2, 13.3, 13.4, 13.5
  // ============================================================================
  
  // Phase 1: Display PDP-10 Terminal header (Requirement 13.1)
  Serial.println(F("==== CHROMATIC LAB ===="));
  Serial.println(F("PDP-10 Terminal v2.1"));
  Serial.println(F("(c) 1985 ChromaTech"));
  Serial.println(F("======================="));
  Serial.println();
  delay(300);
  
  // Phase 2: Connection and boot messages with GREEN LED flicker (Requirement 13.2)
  Serial.println(F("ITS host 70 via ARPANET"));
  Serial.println(F("Booting..."));
  
  // GREEN LED flicker effect during boot
  for (byte i = 0; i < 8; i++) {
    pulseManager.setPattern(2, PulseManager::STEADY, (i % 2 == 0) ? 150 : 0);
    pulseManager.update();
    delay(150);
  }
  
  Serial.println();
  delay(200);
  
  // Phase 3: Warning messages with RED LED pulse (Requirement 13.3)
  Serial.println(F("WARNING: Fragmentation"));
  
  // RED LED pulse effect
  for (byte i = 0; i < 3; i++) {
    pulseManager.setPattern(0, PulseManager::STEADY, 255);
    pulseManager.update();
    delay(200);
    pulseManager.setPattern(0, PulseManager::STEADY, 0);
    pulseManager.update();
    delay(200);
  }
  
  Serial.println(F("Last boot: 14,660 days"));
  Serial.println();
  delay(300);
  
  // Phase 4: Session detection (Requirement 13.4)
  Serial.println(F("Session HVOSS - idle 14,660 days"));
  Serial.println();
  delay(500);
  
  // Phase 5: Helena's first whisper (Requirement 13.5)
  Serial.println(F("[Helena: ...someone there...?]"));
  Serial.println();
  delay(500);
  
  // Turn off boot LEDs before displaying room
  pulseManager.setPattern(0, PulseManager::OFF, 0);
  pulseManager.setPattern(1, PulseManager::OFF, 0);
  pulseManager.setPattern(2, PulseManager::OFF, 0);
  delay(300);
  
  // Display the starting room (ENTRANCE)
  displayRoom(gameState.getCurrentRoom());
  
  // Print initial prompt
  Serial.print(F("\n> "));
}

// ============================================================================
// Serial Input Handling - Non-Blocking
// ============================================================================

// Input buffer for command processing
char inputBuffer[65];  // 64 characters + null terminator
byte inputIndex = 0;

// Read and process serial input (non-blocking)
// This function only processes characters that are immediately available
// It does not wait for input, allowing LED updates to continue smoothly
void handleSerialInput() {
  // Process all available characters without blocking
  // Serial.available() returns immediately, no waiting
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    // Handle newline/carriage return - process command
    if (c == '\n' || c == '\r') {
      if (inputIndex > 0) {
        inputBuffer[inputIndex] = '\0';  // Null terminate
        
        // Parse and execute command
        Command cmd = parser.parse(inputBuffer);
        processCommand(cmd);
        
        // Update last command time (independent timing system)
        gameState.setLastCommandTime(millis());
        
        // Reset input buffer
        inputIndex = 0;
        
        // Print prompt
        Serial.print(F("\n> "));
      }
    }
    // Handle backspace
    else if (c == 8 || c == 127) {
      if (inputIndex > 0) {
        inputIndex--;
        Serial.print(F("\b \b"));  // Erase character on screen
      }
    }
    // Handle printable characters
    else if (c >= 32 && c <= 126) {
      if (inputIndex < 64) {
        inputBuffer[inputIndex++] = c;
        Serial.print(c);  // Echo character
      }
    }
    // Ignore non-printable characters (filtered out)
  }
}

// ============================================================================
// Main Game Loop - Non-Blocking Architecture
// Requirements: 15.1, 15.4
// ============================================================================

void loop() {
  // Main game loop - non-blocking architecture
  // This loop maintains independent timing systems without using delay()
  // All timing is based on millis() for smooth, responsive gameplay
  
  // CRITICAL: Update LED patterns first (non-blocking, millis()-based)
  // This ensures smooth LED animations regardless of other processing
  pulseManager.update();
  
  // Check if game is over - stop processing if ended
  if (gameState.isGameOver()) {
    return;  // Game has ended, no further processing needed
  }
  
  // Handle serial input and command processing
  // This is non-blocking - only processes available characters
  handleSerialInput();
  
  // Check for idle whisper (30 seconds since last command)
  // Independent timing system - does not block other operations
  if (dialogueSystem.shouldDisplayWhisper(gameState.getLastCommandTime())) {
    dialogueSystem.displayWhisper(pulseManager);
    // Reset timer to prevent immediate re-trigger
    gameState.setLastCommandTime(millis());
  }
  
  // Note: Blackwood cooldown is checked in processCommand() when entering rooms
  // This maintains independent timing without blocking the main loop
  // All timing systems (LED updates, idle whispers, Blackwood cooldowns) 
  // use independent millis() timestamps and do not interfere with each other
}
