/*
 * GameState Manager Test
 * Tests the GameState class implementation
 */

// Minimal mock structures for testing
const byte FLAG_PORTABLE = 0x01;
const byte FLAG_TREASURE = 0x02;
const byte FLAG_IN_INVENTORY = 0x04;

struct Object {
  byte id;
  const char* name;
  const char* description;
  byte location;
  byte flags;
  byte ledResponse;
  const char* helenaDialogue;
};

struct Room {
  byte id;
  const char* name;
  const char* description;
  byte exits[6];
  byte ledRed, ledBlue, ledGreen;
  byte dangerLevel;
  const char* helenaDialogue;
};

// Mock PulseManager for testing
class PulseManager {
public:
  enum Pattern { STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE, OFF };
  void init(byte r, byte b, byte g) {}
  void setPattern(byte ch, Pattern p, byte br) {}
  void update() {}
};

PulseManager pulseManager;

// Mock data
const char objName0[] PROGMEM = "LAMP";
const char objDesc0[] PROGMEM = "A lamp";
const char helenaObj0[] PROGMEM = "lamp dialogue";

const Object OBJECTS[15] PROGMEM = {
  {0, objName0, objDesc0, 255, FLAG_PORTABLE | FLAG_IN_INVENTORY, 2, helenaObj0},
};

void getObjectData(byte id, Object* obj) {
  if (id >= 15) return;
  memcpy_P(obj, &OBJECTS[id], sizeof(Object));
}

const char roomName0[] PROGMEM = "Entrance";
const char roomDesc0[] PROGMEM = "You are at the entrance";
const char helenaDialogue0[] PROGMEM = "...you came back...";

const Room ROOMS[15] PROGMEM = {
  {0, roomName0, roomDesc0, {1, 255, 13, 255, 255, 255}, 50, 50, 100, 1, helenaDialogue0},
};

void getRoomData(byte id, Room* room) {
  if (id >= 15) return;
  memcpy_P(room, &ROOMS[id], sizeof(Room));
}

// ============================================================================
// GameState Manager Class
// ============================================================================

class GameState {
private:
  byte currentRoom;
  byte inventory[8];
  byte inventoryCount;
  int score;
  byte crystalsCollected;
  byte crystalsDeposited;
  bool blackwoodDefeated;
  bool gameOver;
  unsigned long lastCommandTime;
  unsigned long blackwoodCooldown;
  byte objectLocations[15];
  byte objectFlags[15];

public:
  void init() {
    currentRoom = 0;
    inventoryCount = 0;
    score = 0;
    crystalsCollected = 0;
    crystalsDeposited = 0;
    blackwoodDefeated = false;
    gameOver = false;
    lastCommandTime = millis();
    blackwoodCooldown = 0;
    
    for (byte i = 0; i < 8; i++) {
      inventory[i] = 255;
    }
    
    Object obj;
    for (byte i = 0; i < 15; i++) {
      getObjectData(i, &obj);
      objectLocations[i] = obj.location;
      objectFlags[i] = obj.flags;
    }
    
    addToInventory(0);  // Add LAMP
  }
  
  void changeRoom(byte newRoomId) {
    if (newRoomId >= 15) return;
    currentRoom = newRoomId;
    
    Room room;
    getRoomData(newRoomId, &room);
    pulseManager.setPattern(0, PulseManager::STEADY, room.ledRed);
    pulseManager.setPattern(1, PulseManager::STEADY, room.ledBlue);
    pulseManager.setPattern(2, PulseManager::STEADY, room.ledGreen);
  }
  
  bool addToInventory(byte objectId) {
    if (objectId >= 15) return false;
    if (inventoryCount >= 8) return false;
    
    for (byte i = 0; i < inventoryCount; i++) {
      if (inventory[i] == objectId) return false;
    }
    
    for (byte i = 0; i < 8; i++) {
      if (inventory[i] == 255) {
        inventory[i] = objectId;
        inventoryCount++;
        objectLocations[objectId] = 255;
        objectFlags[objectId] |= FLAG_IN_INVENTORY;
        return true;
      }
    }
    return false;
  }
  
  bool removeFromInventory(byte objectId) {
    if (objectId >= 15) return false;
    
    for (byte i = 0; i < 8; i++) {
      if (inventory[i] == objectId) {
        inventory[i] = 255;
        inventoryCount--;
        objectLocations[objectId] = currentRoom;
        objectFlags[objectId] &= ~FLAG_IN_INVENTORY;
        return true;
      }
    }
    return false;
  }
  
  void updateScore(int delta) {
    score += delta;
    if (score < 0) score = 0;
    if (score > 150) score = 150;
  }
  
  byte getCurrentRoom() const { return currentRoom; }
  byte getInventoryCount() const { return inventoryCount; }
  int getScore() const { return score; }
  byte getInventorySlot(byte slot) const {
    if (slot >= 8) return 255;
    return inventory[slot];
  }
};

GameState gameState;

// ============================================================================
// Tests
// ============================================================================

void testInit() {
  Serial.println(F("Test: init()"));
  gameState.init();
  
  bool passed = true;
  
  // Check starting room is ENTRANCE (0)
  if (gameState.getCurrentRoom() != 0) {
    Serial.println(F("  FAIL: Starting room should be 0"));
    passed = false;
  }
  
  // Check LAMP is in inventory
  if (gameState.getInventoryCount() != 1) {
    Serial.println(F("  FAIL: Should have 1 item (LAMP) in inventory"));
    passed = false;
  }
  
  if (gameState.getInventorySlot(0) != 0) {
    Serial.println(F("  FAIL: LAMP (object 0) should be in first slot"));
    passed = false;
  }
  
  // Check score is 0
  if (gameState.getScore() != 0) {
    Serial.println(F("  FAIL: Starting score should be 0"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testChangeRoom() {
  Serial.println(F("Test: changeRoom()"));
  gameState.init();
  
  gameState.changeRoom(1);
  
  bool passed = true;
  if (gameState.getCurrentRoom() != 1) {
    Serial.println(F("  FAIL: Room should be 1 after changeRoom(1)"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testAddToInventory() {
  Serial.println(F("Test: addToInventory()"));
  gameState.init();
  
  bool passed = true;
  
  // Try adding object 1
  bool result = gameState.addToInventory(1);
  if (!result) {
    Serial.println(F("  FAIL: Should be able to add object 1"));
    passed = false;
  }
  
  if (gameState.getInventoryCount() != 2) {
    Serial.println(F("  FAIL: Should have 2 items after adding"));
    passed = false;
  }
  
  // Try adding same object again (should fail)
  result = gameState.addToInventory(1);
  if (result) {
    Serial.println(F("  FAIL: Should not be able to add same object twice"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testRemoveFromInventory() {
  Serial.println(F("Test: removeFromInventory()"));
  gameState.init();
  
  bool passed = true;
  
  // Remove LAMP (object 0)
  bool result = gameState.removeFromInventory(0);
  if (!result) {
    Serial.println(F("  FAIL: Should be able to remove LAMP"));
    passed = false;
  }
  
  if (gameState.getInventoryCount() != 0) {
    Serial.println(F("  FAIL: Should have 0 items after removing LAMP"));
    passed = false;
  }
  
  // Try removing again (should fail)
  result = gameState.removeFromInventory(0);
  if (result) {
    Serial.println(F("  FAIL: Should not be able to remove object not in inventory"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testInventoryLimit() {
  Serial.println(F("Test: 8-item inventory limit"));
  gameState.init();
  
  bool passed = true;
  
  // Try to add 8 more items (already have LAMP, so total would be 9)
  for (byte i = 1; i <= 8; i++) {
    bool result = gameState.addToInventory(i);
    if (i <= 7) {
      if (!result) {
        Serial.print(F("  FAIL: Should be able to add item "));
        Serial.println(i);
        passed = false;
      }
    } else {
      // 8th item should fail (inventory full)
      if (result) {
        Serial.println(F("  FAIL: Should not be able to add 9th item"));
        passed = false;
      }
    }
  }
  
  if (gameState.getInventoryCount() != 8) {
    Serial.print(F("  FAIL: Should have exactly 8 items, have "));
    Serial.println(gameState.getInventoryCount());
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void testUpdateScore() {
  Serial.println(F("Test: updateScore()"));
  gameState.init();
  
  bool passed = true;
  
  // Add points
  gameState.updateScore(5);
  if (gameState.getScore() != 5) {
    Serial.println(F("  FAIL: Score should be 5"));
    passed = false;
  }
  
  // Add more points
  gameState.updateScore(10);
  if (gameState.getScore() != 15) {
    Serial.println(F("  FAIL: Score should be 15"));
    passed = false;
  }
  
  // Subtract points
  gameState.updateScore(-5);
  if (gameState.getScore() != 10) {
    Serial.println(F("  FAIL: Score should be 10"));
    passed = false;
  }
  
  // Test clamping at 0
  gameState.updateScore(-20);
  if (gameState.getScore() != 0) {
    Serial.println(F("  FAIL: Score should be clamped at 0"));
    passed = false;
  }
  
  // Test clamping at 150
  gameState.updateScore(200);
  if (gameState.getScore() != 150) {
    Serial.println(F("  FAIL: Score should be clamped at 150"));
    passed = false;
  }
  
  if (passed) {
    Serial.println(F("  PASS"));
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  
  delay(1000);
  
  Serial.println(F("========================================"));
  Serial.println(F("GameState Manager Tests"));
  Serial.println(F("========================================"));
  Serial.println();
  
  testInit();
  testChangeRoom();
  testAddToInventory();
  testRemoveFromInventory();
  testInventoryLimit();
  testUpdateScore();
  
  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("All tests completed"));
  Serial.println(F("========================================"));
}

void loop() {
  // Tests run once
}
