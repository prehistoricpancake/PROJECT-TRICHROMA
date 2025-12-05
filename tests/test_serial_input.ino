/*
 * Simple Serial Input Test
 * Upload this to test if Serial Monitor is configured correctly
 */

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  
  Serial.println("=== SERIAL TEST ===");
  Serial.println("Type something and press Enter");
  Serial.print("> ");
}

void loop() {
  static char buffer[65];
  static byte index = 0;
  
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    if (c == '\n' || c == '\r') {
      if (index > 0) {
        buffer[index] = '\0';
        
        Serial.println();
        Serial.print("You typed: ");
        Serial.println(buffer);
        Serial.println();
        
        index = 0;
        Serial.print("> ");
      }
    } else if (c >= 32 && c <= 126) {
      if (index < 64) {
        buffer[index++] = c;
        Serial.print(c);  // Echo
      }
    }
  }
}
