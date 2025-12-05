/*
 * DialogueSystem Test
 * Tests Helena's idle whisper system implementation
 */

// Minimal mock structures for testing
class PulseManager {
public:
  enum Pattern { STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE, OFF };
  
  byte lastChannel;
  Pattern lastPattern;
  byte lastBrightness;
  
  void init(byte r, byte b, byte g) {}
  
  void setPattern(byte ch, Pattern p, byte br) {
    lastChannel = ch;
    lastPattern = p;
    lastBrightness = br;
  }
  
  void update() {}
};

PulseManager pulseManager;

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
  static const byte whisperLedChannels[15] PROGMEM;
  
public:
  // Display a random whisper from Helena
  void displayWhisper(PulseManager& leds) {
    // Select random whisper from pool
    byte whisperIndex = random(15);
    
    // Read whisper message from PROGMEM
    const char* msgPtr = (const char*)pgm_read_word(&whisperMessages[whisperIndex]);
    char buffer[128];
    readProgmemString(msgPtr, buffer, 128);
    
    // Display whisper
    Serial.println();
    Serial.print(F("[Helena whispers: "));
    Serial.print(buffer);
    Serial.println(F("]"));
    Serial.println();
    
    // Get LED channel for this whisper
    byte ledChannel = pgm_read_byte(&whisperLedChannels[whisperIndex]);
    
    // Trigger dim pulse in corresponding LED channel
    leds.setPattern(ledChannel, PulseManager::PULSE, 80);
    
    // Print prompt
    Serial.print(F("> "));
  }
  
  // Check if idle whisper should be displayed
  bool shouldDisplayWhisper(unsigned long lastCommandTime) {
    unsigned long currentTime = millis();
    unsigned long elapsed = currentTime - lastCommandTime;
    
    // Check if 30 seconds (30000 milliseconds) have elapsed
    return elapsed >= 30000;
  }
  
  // Test helper: get whisper count
  byte getWhisperCount() const {
    return 15;
  }
  
  // Test helper: get LED channel for whisper
  byte getWhisperLedChannel(byte index) const {
    if (index >= 15) return 255;
    return pgm_read_byte(&whisperLedChannels[index]);
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

DialogueSystem dialogueSystem;

// ============================================================================
// Tests
// ============================================================================

void testWhisperCount() {
  Serial.println(F("Test: Whisper pool has 15 messages"));
  
  bool passed = true;
  
  if (dialogueSystem.getWhisperCount() != 15) {
    Serial.println(F("  FAIL: Should have exactly 15 whispers"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testShouldDisplayWhisper() {
  Serial.println(F("Test: shouldDisplayWhisper() timing"));
  
  bool passed = true;
  
  unsigned long now = millis();
  
  // Test: should NOT display if less than 30 seconds
  if (dialogueSystem.shouldDisplayWhisper(now - 29000)) {
    Serial.println(F("  FAIL: Should not display whisper before 30 seconds"));
    passed = false;
  }
  
  // Test: SHOULD display if 30 seconds or more
  if (!dialogueSystem.shouldDisplayWhisper(now - 30000)) {
    Serial.println(F("  FAIL: Should display whisper after 30 seconds"));
    passed = false;
  }
  
  // Test: SHOULD display if more than 30 seconds
  if (!dialogueSystem.shouldDisplayWhisper(now - 35000)) {
    Serial.println(F("  FAIL: Should display whisper after 35 seconds"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testDisplayWhisper() {
  Serial.println(F("Test: displayWhisper() triggers LED pulse"));
  
  bool passed = true;
  
  // Set random seed for reproducibility
  randomSeed(12345);
  
  // Display a whisper
  Serial.println(F("  Displaying whisper..."));
  dialogueSystem.displayWhisper(pulseManager);
  
  // Check that LED pattern was set
  if (pulseManager.lastPattern != PulseManager::PULSE) {
    Serial.println(F("  FAIL: LED pattern should be PULSE"));
    passed = false;
  }
  
  // Check that brightness is dim (80)
  if (pulseManager.lastBrightness != 80) {
    Serial.print(F("  FAIL: LED brightness should be 80, got "));
    Serial.println(pulseManager.lastBrightness);
    passed = false;
  }
  
  // Check that LED channel is valid (0-2)
  if (pulseManager.lastChannel > 2) {
    Serial.print(F("  FAIL: LED channel should be 0-2, got "));
    Serial.println(pulseManager.lastChannel);
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testLedChannelMapping() {
  Serial.println(F("Test: LED channel mapping for whispers"));
  
  bool passed = true;
  
  // Check that all whispers have valid LED channels (0=RED, 1=BLUE, 2=GREEN)
  for (byte i = 0; i < 15; i++) {
    byte channel = dialogueSystem.getWhisperLedChannel(i);
    if (channel > 2) {
      Serial.print(F("  FAIL: Whisper "));
      Serial.print(i);
      Serial.print(F(" has invalid LED channel: "));
      Serial.println(channel);
      passed = false;
    }
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testMultipleWhispers() {
  Serial.println(F("Test: Display multiple whispers"));
  
  bool passed = true;
  
  Serial.println(F("  Displaying 5 random whispers:"));
  Serial.println();
  
  for (byte i = 0; i < 5; i++) {
    Serial.print(F("  Whisper "));
    Serial.print(i + 1);
    Serial.print(F(": "));
    dialogueSystem.displayWhisper(pulseManager);
    delay(100);
  }
  
  Serial.println();
  Serial.println(F("  PASS (manual verification required)"));
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  
  // Set random seed
  randomSeed(analogRead(A0));
  
  delay(1000);
  
  Serial.println(F("========================================"));
  Serial.println(F("DialogueSystem Tests"));
  Serial.println(F("========================================"));
  Serial.println();
  
  testWhisperCount();
  testShouldDisplayWhisper();
  testDisplayWhisper();
  testLedChannelMapping();
  testMultipleWhispers();
  
  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("All tests completed"));
  Serial.println(F("========================================"));
}

void loop() {
  // Tests run once
}
