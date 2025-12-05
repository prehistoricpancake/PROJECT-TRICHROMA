/*
 * Test for EnemySystem - Dr. Blackwood Encounters
 * Tests spawn chance calculation and encounter mechanics
 */

// Mock Arduino functions for testing
unsigned long millis() { return 0; }
void delay(unsigned long ms) {}
int analogRead(int pin) { return 0; }
void pinMode(int pin, int mode) {}
void digitalWrite(int pin, int value) {}
long random(long max) { return 0; }
long random(long min, long max) { return min; }
void randomSeed(unsigned long seed) {}

// Mock Serial for testing
class MockSerial {
public:
  void begin(int baud) {}
  void print(const char* str) {}
  void print(char c) {}
  void print(int n) {}
  void println() {}
  void println(const char* str) {}
  void println(int n) {}
  bool available() { return false; }
  char read() { return 0; }
} Serial;

// Include the main game file (which contains all classes)
#include "project_trichroma.ino"

// Test results
int testsPassed = 0;
int testsFailed = 0;

void assertTrue(bool condition, const char* testName) {
  if (condition) {
    testsPassed++;
  } else {
    testsFailed++;
    Serial.print("FAILED: ");
    Serial.println(testName);
  }
}

void testSpawnChanceGreenChamber() {
  // GREEN_CHAMBER (room 9) should never spawn Blackwood (0%)
  bool spawned = enemySystem.shouldSpawn(9, 0);
  assertTrue(!spawned, "GREEN_CHAMBER should never spawn Blackwood");
}

void testSpawnChanceAdminRoom() {
  // ADMIN_ROOM (room 12) should always spawn Blackwood (100%)
  bool spawned = enemySystem.shouldSpawn(12, 0);
  assertTrue(spawned, "ADMIN_ROOM should always spawn Blackwood");
}

void testSpawnChanceBaseRate() {
  // Test base spawn rate (15%) in low danger room
  // Room 0 (ENTRANCE) has dangerLevel=1, so base 15% applies
  // With random() mocked to return 0, spawn should occur (0 < 15)
  bool spawned = enemySystem.shouldSpawn(0, 0);
  assertTrue(spawned, "Base spawn rate should work in ENTRANCE");
}

void testSpawnChanceHighDanger() {
  // Test high danger room spawn rate (35%)
  // Room 2 (ANGER_PIT) has dangerLevel=5, so 35% applies
  // With random() mocked to return 0, spawn should occur (0 < 35)
  bool spawned = enemySystem.shouldSpawn(2, 0);
  assertTrue(spawned, "High danger room should have 35% spawn rate");
}

void testSpawnChanceManyCrystals() {
  // Test spawn rate with 3+ crystals (50%)
  // With random() mocked to return 0, spawn should occur (0 < 50)
  bool spawned = enemySystem.shouldSpawn(0, 3);
  assertTrue(spawned, "3+ crystals should trigger 50% spawn rate");
}

void runTests() {
  Serial.println("=== EnemySystem Tests ===");
  
  testSpawnChanceGreenChamber();
  testSpawnChanceAdminRoom();
  testSpawnChanceBaseRate();
  testSpawnChanceHighDanger();
  testSpawnChanceManyCrystals();
  
  Serial.println();
  Serial.print("Tests passed: ");
  Serial.println(testsPassed);
  Serial.print("Tests failed: ");
  Serial.println(testsFailed);
  
  if (testsFailed == 0) {
    Serial.println("All tests PASSED!");
  } else {
    Serial.println("Some tests FAILED!");
  }
}

void setup() {
  Serial.begin(9600);
  runTests();
}

void loop() {
  // Nothing to do
}
