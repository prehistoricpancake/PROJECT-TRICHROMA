/*
 * PROJECT TRICHROMA - Property-Based Tests
 * 
 * This file contains property-based tests for the Arduino implementation.
 * These tests verify correctness properties across multiple random inputs.
 * 
 * To run: Upload this sketch to Arduino Uno and open Serial Monitor at 9600 baud
 */

// Pin definitions (same as main sketch)
const byte RED_LED_PIN = 12;
const byte BLUE_LED_PIN = 4;
const byte GREEN_LED_PIN = 8;

// Test configuration
const int NUM_ITERATIONS = 100;  // Minimum iterations per property test
bool allTestsPassed = true;

// ============================================================================
// PulseManager Class (copied from main sketch for testing)
// ============================================================================

class PulseManager {
public:
  enum Pattern {
    STEADY, PULSE, STROBE, BREATHE, BATTLE, SYNC, FADE, OFF
  };
  
private:
  byte pins[3];
  Pattern patterns[3];
  byte targetBrightness[3];
  byte currentBrightness[3];
  unsigned long patternStartTime[3];
  byte pwmCounter;
  unsigned long lastPwmUpdate;
  
public:
  void init(byte redPin, byte bluePin, byte greenPin) {
    pins[0] = redPin;
    pins[1] = bluePin;
    pins[2] = greenPin;
    
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
  
  void setPattern(byte channel, Pattern pattern, byte brightness) {
    if (channel >= 3) return;
    
    patterns[channel] = pattern;
    targetBrightness[channel] = brightness;
    patternStartTime[channel] = millis();
    
    if (pattern != FADE) {
      currentBrightness[channel] = brightness;
    }
  }
  
  void update() {
    unsigned long now = millis();
    
    if (now - lastPwmUpdate >= 4) {
      lastPwmUpdate = now;
      pwmCounter++;
    }
    
    for (byte i = 0; i < 3; i++) {
      byte brightness = calculateBrightness(i, now);
      
      if (pwmCounter < brightness) {
        digitalWrite(pins[i], HIGH);
      } else {
        digitalWrite(pins[i], LOW);
      }
    }
  }
  
private:
  byte calculateBrightness(byte channel, unsigned long now) {
    unsigned long elapsed = now - patternStartTime[channel];
    byte target = targetBrightness[channel];
    
    switch (patterns[channel]) {
      case STEADY:
        return target;
      
      case PULSE: {
        float phase = (elapsed % 2000) / 2000.0;
        float sine = sin(phase * 2.0 * PI);
        return (byte)((sine + 1.0) / 2.0 * target);
      }
      
      case STROBE: {
        if ((elapsed % 200) < 100) {
          return target;
        } else {
          return 0;
        }
      }
      
      case BREATHE: {
        float phase = (elapsed % 4000) / 4000.0;
        float sine = sin(phase * 2.0 * PI);
        return (byte)((sine + 1.0) / 2.0 * target);
      }
      
      case BATTLE: {
        if ((elapsed % 150) == 0) {
          return (byte)(random(256) % (target + 1));
        }
        byte phase = (elapsed / 50) % 4;
        return (byte)(target * phase / 4);
      }
      
      case SYNC: {
        float phase = (elapsed % 3000) / 3000.0;
        float sine = sin(phase * 2.0 * PI);
        return (byte)((sine + 1.0) / 2.0 * target);
      }
      
      case FADE: {
        if (elapsed >= 1000) {
          currentBrightness[channel] = target;
          return target;
        }
        int diff = (int)target - (int)currentBrightness[channel];
        return currentBrightness[channel] + (byte)((diff * elapsed) / 1000);
      }
      
      case OFF:
      default:
        return 0;
    }
  }
};

// ============================================================================
// Test Helper Functions
// ============================================================================

void reportTestResult(const char* testName, bool passed) {
  Serial.print(F("  "));
  Serial.print(testName);
  Serial.print(F(": "));
  if (passed) {
    Serial.println(F("PASS"));
  } else {
    Serial.println(F("FAIL"));
    allTestsPassed = false;
  }
}

// ============================================================================
// Property Test 1: Non-blocking LED execution
// **Feature: project-trichroma, Property 1: Non-blocking LED execution**
// **Validates: Requirements 1.2, 2.5, 15.2, 15.3**
// ============================================================================

bool testNonBlockingLEDExecution() {
  Serial.println(F("\n=== Property Test 1: Non-blocking LED execution ==="));
  Serial.println(F("Testing that serial input processing continues without blocking"));
  Serial.println(F("regardless of LED pattern state..."));
  
  PulseManager testManager;
  testManager.init(RED_LED_PIN, BLUE_LED_PIN, GREEN_LED_PIN);
  
  bool allIterationsPassed = true;
  int passCount = 0;
  
  // Test across multiple iterations with random patterns
  for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
    // Generate random LED pattern configuration
    byte randomChannel = random(3);  // 0=RED, 1=BLUE, 2=GREEN
    byte randomPattern = random(8);  // 0-7 for all Pattern enum values
    byte randomBrightness = random(256);  // 0-255
    
    // Set random pattern
    testManager.setPattern(randomChannel, (PulseManager::Pattern)randomPattern, randomBrightness);
    
    // Simulate serial input processing while LED updates
    unsigned long startTime = micros();
    
    // Update LEDs multiple times (simulating continuous operation)
    for (int i = 0; i < 10; i++) {
      testManager.update();
    }
    
    // Simulate serial input check (this should be fast)
    bool serialAvailable = Serial.available();
    
    // Continue LED updates
    for (int i = 0; i < 10; i++) {
      testManager.update();
    }
    
    unsigned long endTime = micros();
    unsigned long elapsedMicros = endTime - startTime;
    
    // Property: Serial input processing should complete within 100ms (100,000 microseconds)
    // even while LEDs are updating
    // This verifies non-blocking behavior
    bool iterationPassed = (elapsedMicros < 100000);
    
    if (iterationPassed) {
      passCount++;
    } else {
      allIterationsPassed = false;
      Serial.print(F("  Iteration "));
      Serial.print(iteration);
      Serial.print(F(" FAILED: Took "));
      Serial.print(elapsedMicros);
      Serial.print(F(" microseconds (>100ms threshold)"));
      Serial.print(F(" [Channel="));
      Serial.print(randomChannel);
      Serial.print(F(", Pattern="));
      Serial.print(randomPattern);
      Serial.print(F(", Brightness="));
      Serial.print(randomBrightness);
      Serial.println(F("]"));
    }
    
    // Small delay between iterations to allow LED patterns to change
    delay(10);
  }
  
  Serial.print(F("Completed "));
  Serial.print(NUM_ITERATIONS);
  Serial.print(F(" iterations: "));
  Serial.print(passCount);
  Serial.print(F(" passed, "));
  Serial.print(NUM_ITERATIONS - passCount);
  Serial.println(F(" failed"));
  
  return allIterationsPassed;
}

// Additional test: Verify serial responsiveness during long LED operation
bool testSerialResponsivenessDuringLEDOperation() {
  Serial.println(F("\n=== Additional Test: Serial Responsiveness ==="));
  Serial.println(F("Testing that serial remains responsive during continuous LED updates..."));
  
  PulseManager testManager;
  testManager.init(RED_LED_PIN, BLUE_LED_PIN, GREEN_LED_PIN);
  
  // Set all channels to different patterns
  testManager.setPattern(0, PulseManager::PULSE, 200);
  testManager.setPattern(1, PulseManager::BREATHE, 150);
  testManager.setPattern(2, PulseManager::STROBE, 255);
  
  bool testPassed = true;
  unsigned long testDuration = 5000;  // 5 seconds
  unsigned long startTime = millis();
  unsigned long lastCheckTime = startTime;
  int checkCount = 0;
  
  // Run LED updates continuously for 5 seconds
  while (millis() - startTime < testDuration) {
    testManager.update();
    
    // Check serial availability every 100ms
    if (millis() - lastCheckTime >= 100) {
      unsigned long checkStart = micros();
      
      // Simulate serial check
      volatile bool available = Serial.available();
      
      unsigned long checkEnd = micros();
      unsigned long checkDuration = checkEnd - checkStart;
      
      // Serial check should be nearly instantaneous (< 1ms)
      if (checkDuration > 1000) {
        Serial.print(F("  Serial check took too long: "));
        Serial.print(checkDuration);
        Serial.println(F(" microseconds"));
        testPassed = false;
      }
      
      lastCheckTime = millis();
      checkCount++;
    }
  }
  
  Serial.print(F("Performed "));
  Serial.print(checkCount);
  Serial.print(F(" serial checks during "));
  Serial.print(testDuration);
  Serial.println(F("ms of LED operation"));
  
  return testPassed;
}

// ============================================================================
// Main Test Runner
// ============================================================================

void setup() {
  Serial.begin(9600);
  
  // Wait for serial connection
  while (!Serial) {
    ;
  }
  
  delay(1000);  // Give user time to open Serial Monitor
  
  Serial.println(F("========================================"));
  Serial.println(F("PROJECT TRICHROMA - Property-Based Tests"));
  Serial.println(F("========================================"));
  Serial.println();
  
  // Seed random number generator
  randomSeed(analogRead(A0));
  
  // Run Property Test 1
  bool test1Passed = testNonBlockingLEDExecution();
  reportTestResult("Property 1: Non-blocking LED execution", test1Passed);
  
  // Run additional responsiveness test
  bool test2Passed = testSerialResponsivenessDuringLEDOperation();
  reportTestResult("Serial Responsiveness Test", test2Passed);
  
  // Final summary
  Serial.println();
  Serial.println(F("========================================"));
  if (allTestsPassed && test1Passed && test2Passed) {
    Serial.println(F("ALL TESTS PASSED"));
  } else {
    Serial.println(F("SOME TESTS FAILED"));
  }
  Serial.println(F("========================================"));
}

void loop() {
  // Tests run once in setup()
  // Loop does nothing
}
