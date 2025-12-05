/*
 * Test for Scoring System (Task 14)
 * Tests the SCORE command and rank calculation
 */

// Mock Serial for testing
class MockSerial {
public:
  void begin(int baud) {}
  void print(const char* str) {}
  void print(int val) {}
  void println() {}
  void println(const char* str) {}
  void println(int val) {}
  void print(const __FlashStringHelper* str) {}
  void println(const __FlashStringHelper* str) {}
  bool available() { return false; }
  char read() { return 0; }
};

MockSerial Serial;

// Include the main file
#include "project_trichroma.ino"

// Test helper function
void testRankCalculation() {
  Serial.println("Testing rank calculation...");
  
  // Test RANDOM rank (0-30)
  const char* rank0 = getRank(0);
  const char* rank15 = getRank(15);
  const char* rank30 = getRank(30);
  
  if (strcmp(rank0, "RANDOM") != 0) {
    Serial.println("FAIL: Score 0 should be RANDOM");
  }
  if (strcmp(rank15, "RANDOM") != 0) {
    Serial.println("FAIL: Score 15 should be RANDOM");
  }
  if (strcmp(rank30, "RANDOM") != 0) {
    Serial.println("FAIL: Score 30 should be RANDOM");
  }
  
  // Test NOVICE HACKER rank (31-70)
  const char* rank31 = getRank(31);
  const char* rank50 = getRank(50);
  const char* rank70 = getRank(70);
  
  if (strcmp(rank31, "NOVICE HACKER") != 0) {
    Serial.println("FAIL: Score 31 should be NOVICE HACKER");
  }
  if (strcmp(rank50, "NOVICE HACKER") != 0) {
    Serial.println("FAIL: Score 50 should be NOVICE HACKER");
  }
  if (strcmp(rank70, "NOVICE HACKER") != 0) {
    Serial.println("FAIL: Score 70 should be NOVICE HACKER");
  }
  
  // Test EXPERIENCED HACKER rank (71-110)
  const char* rank71 = getRank(71);
  const char* rank90 = getRank(90);
  const char* rank110 = getRank(110);
  
  if (strcmp(rank71, "EXPERIENCED HACKER") != 0) {
    Serial.println("FAIL: Score 71 should be EXPERIENCED HACKER");
  }
  if (strcmp(rank90, "EXPERIENCED HACKER") != 0) {
    Serial.println("FAIL: Score 90 should be EXPERIENCED HACKER");
  }
  if (strcmp(rank110, "EXPERIENCED HACKER") != 0) {
    Serial.println("FAIL: Score 110 should be EXPERIENCED HACKER");
  }
  
  // Test MASTER HACKER rank (111-140)
  const char* rank111 = getRank(111);
  const char* rank125 = getRank(125);
  const char* rank140 = getRank(140);
  
  if (strcmp(rank111, "MASTER HACKER") != 0) {
    Serial.println("FAIL: Score 111 should be MASTER HACKER");
  }
  if (strcmp(rank125, "MASTER HACKER") != 0) {
    Serial.println("FAIL: Score 125 should be MASTER HACKER");
  }
  if (strcmp(rank140, "MASTER HACKER") != 0) {
    Serial.println("FAIL: Score 140 should be MASTER HACKER");
  }
  
  // Test IMPLEMENTER rank (141-150)
  const char* rank141 = getRank(141);
  const char* rank145 = getRank(145);
  const char* rank150 = getRank(150);
  
  if (strcmp(rank141, "IMPLEMENTER") != 0) {
    Serial.println("FAIL: Score 141 should be IMPLEMENTER");
  }
  if (strcmp(rank145, "IMPLEMENTER") != 0) {
    Serial.println("FAIL: Score 145 should be IMPLEMENTER");
  }
  if (strcmp(rank150, "IMPLEMENTER") != 0) {
    Serial.println("FAIL: Score 150 should be IMPLEMENTER");
  }
  
  Serial.println("Rank calculation tests completed!");
}

void testScoreTracking() {
  Serial.println("Testing score tracking...");
  
  // Initialize game state
  gameState.init();
  
  // Test initial score
  if (gameState.getScore() != 0) {
    Serial.println("FAIL: Initial score should be 0");
  }
  
  // Test score update
  gameState.updateScore(5);
  if (gameState.getScore() != 5) {
    Serial.println("FAIL: Score should be 5 after adding 5");
  }
  
  // Test negative score update
  gameState.updateScore(-5);
  if (gameState.getScore() != 0) {
    Serial.println("FAIL: Score should be 0 after subtracting 5");
  }
  
  // Test score clamping at 0
  gameState.updateScore(-10);
  if (gameState.getScore() != 0) {
    Serial.println("FAIL: Score should be clamped at 0");
  }
  
  // Test score clamping at 150
  gameState.updateScore(160);
  if (gameState.getScore() != 150) {
    Serial.println("FAIL: Score should be clamped at 150");
  }
  
  Serial.println("Score tracking tests completed!");
}

void setup() {
  Serial.begin(9600);
  Serial.println("========================================");
  Serial.println("  SCORING SYSTEM TEST (Task 14)");
  Serial.println("========================================");
  Serial.println();
  
  testRankCalculation();
  Serial.println();
  testScoreTracking();
  
  Serial.println();
  Serial.println("========================================");
  Serial.println("  ALL TESTS COMPLETED");
  Serial.println("========================================");
}

void loop() {
  // Nothing to do in loop
}
