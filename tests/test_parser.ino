/*
 * Simple Parser Test
 * Tests the Command Parser implementation
 */

// ============================================================================
// Command Parser - Two-Word Parser System (copied from main sketch)
// ============================================================================

// Verb enumeration
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

// Noun enumeration
enum Noun {
  NOUN_NONE = 0,
  NOUN_NORTH,
  NOUN_SOUTH,
  NOUN_EAST,
  NOUN_WEST,
  NOUN_UP,
  NOUN_DOWN,
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
  NOUN_CRYSTAL,
  NOUN_CUTTER,
  NOUN_CASE,
  NOUN_NOTES
};

// Command structure
struct Command {
  Verb verb;
  Noun noun;
  bool valid;
  char unknownWord[32];
};

// Parser class
class Parser {
private:
  char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
      return c - 32;
    }
    return c;
  }
  
  void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
      str[i] = toUpper(str[i]);
    }
  }
  
  bool strEquals(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
      if (str1[i] != str2[i]) return false;
      i++;
    }
    return str1[i] == str2[i];
  }
  
  bool isArticle(const char* word) {
    return strEquals(word, "THE") || 
           strEquals(word, "A") || 
           strEquals(word, "AN");
  }
  
  Verb matchVerb(const char* word) {
    if (strEquals(word, "GO")) return VERB_GO;
    if (strEquals(word, "GET")) return VERB_GET;
    if (strEquals(word, "TAKE")) return VERB_TAKE;
    if (strEquals(word, "DROP")) return VERB_DROP;
    if (strEquals(word, "EXAMINE")) return VERB_EXAMINE;
    if (strEquals(word, "LOOK")) return VERB_LOOK;
    if (strEquals(word, "INVENTORY")) return VERB_INVENTORY;
    if (strEquals(word, "HELP")) return VERB_HELP;
    if (strEquals(word, "SCORE")) return VERB_SCORE;
    if (strEquals(word, "XYZZY")) return VERB_XYZZY;
    if (strEquals(word, "I")) return VERB_INVENTORY;
    if (strEquals(word, "L")) return VERB_LOOK;
    if (strEquals(word, "X")) return VERB_EXAMINE;
    return VERB_NONE;
  }
  
  Noun matchNoun(const char* word) {
    if (strEquals(word, "NORTH") || strEquals(word, "N")) return NOUN_NORTH;
    if (strEquals(word, "SOUTH") || strEquals(word, "S")) return NOUN_SOUTH;
    if (strEquals(word, "EAST") || strEquals(word, "E")) return NOUN_EAST;
    if (strEquals(word, "WEST") || strEquals(word, "W")) return NOUN_WEST;
    if (strEquals(word, "LAMP")) return NOUN_LAMP;
    if (strEquals(word, "CRYSTAL")) return NOUN_CRYSTAL;
    return NOUN_NONE;
  }
  
  char* extractWord(char* input, char* wordBuffer, byte bufferSize) {
    while (*input == ' ' || *input == '\t') {
      input++;
    }
    
    if (*input == '\0') {
      wordBuffer[0] = '\0';
      return NULL;
    }
    
    byte i = 0;
    while (*input != '\0' && *input != ' ' && *input != '\t' && i < bufferSize - 1) {
      wordBuffer[i++] = *input++;
    }
    wordBuffer[i] = '\0';
    
    return input;
  }

public:
  Command parse(char* input) {
    Command cmd;
    cmd.verb = VERB_NONE;
    cmd.noun = NOUN_NONE;
    cmd.valid = false;
    cmd.unknownWord[0] = '\0';
    
    toUpperCase(input);
    
    char word1[32] = "";
    char word2[32] = "";
    char word3[32] = "";
    
    char* pos = input;
    pos = extractWord(pos, word1, 32);
    if (pos) pos = extractWord(pos, word2, 32);
    if (pos) pos = extractWord(pos, word3, 32);
    
    if (word1[0] == '\0') {
      return cmd;
    }
    
    char* firstWord = word1;
    char* secondWord = word2;
    char* thirdWord = word3;
    
    if (isArticle(word1)) {
      firstWord = word2;
      secondWord = word3;
      thirdWord = NULL;
    }
    
    Noun directionNoun = matchNoun(firstWord);
    if (directionNoun >= NOUN_NORTH && directionNoun <= NOUN_DOWN && secondWord[0] == '\0') {
      cmd.verb = VERB_GO;
      cmd.noun = directionNoun;
      cmd.valid = true;
      return cmd;
    }
    
    if (strEquals(firstWord, "I") && secondWord[0] == '\0') {
      cmd.verb = VERB_INVENTORY;
      cmd.noun = NOUN_NONE;
      cmd.valid = true;
      return cmd;
    }
    
    Verb specialVerb = matchVerb(firstWord);
    if (specialVerb >= VERB_XYZZY) {
      cmd.verb = specialVerb;
      cmd.noun = NOUN_NONE;
      cmd.valid = true;
      return cmd;
    }
    
    if (strEquals(firstWord, "LOOK") || strEquals(firstWord, "L") ||
        strEquals(firstWord, "HELP") || strEquals(firstWord, "SCORE") ||
        strEquals(firstWord, "INVENTORY")) {
      cmd.verb = matchVerb(firstWord);
      cmd.noun = NOUN_NONE;
      cmd.valid = true;
      return cmd;
    }
    
    cmd.verb = matchVerb(firstWord);
    
    if (cmd.verb == VERB_NONE) {
      strncpy(cmd.unknownWord, firstWord, 31);
      cmd.unknownWord[31] = '\0';
      return cmd;
    }
    
    if (secondWord[0] == '\0') {
      cmd.valid = false;
      return cmd;
    }
    
    if (isArticle(secondWord) && thirdWord != NULL && thirdWord[0] != '\0') {
      secondWord = thirdWord;
    }
    
    cmd.noun = matchNoun(secondWord);
    
    if (cmd.noun == NOUN_NONE) {
      strncpy(cmd.unknownWord, secondWord, 31);
      cmd.unknownWord[31] = '\0';
      return cmd;
    }
    
    cmd.valid = true;
    return cmd;
  }
};

Parser parser;

void testCommand(const char* testInput) {
  char buffer[64];
  strncpy(buffer, testInput, 63);
  buffer[63] = '\0';
  
  Serial.print("Input: \"");
  Serial.print(testInput);
  Serial.print("\" -> ");
  
  Command cmd = parser.parse(buffer);
  
  if (cmd.valid) {
    Serial.print("VALID - Verb: ");
    Serial.print(cmd.verb);
    Serial.print(", Noun: ");
    Serial.println(cmd.noun);
  } else if (cmd.unknownWord[0] != '\0') {
    Serial.print("UNKNOWN WORD: ");
    Serial.println(cmd.unknownWord);
  } else {
    Serial.println("INVALID (missing noun?)");
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }
  
  Serial.println("========================================");
  Serial.println("Parser Implementation Test");
  Serial.println("Testing Requirements 3.1-3.7");
  Serial.println("========================================");
  Serial.println();
  
  // Requirement 3.1: Extract first word as VERB and second word as NOUN
  Serial.println("--- Requirement 3.1: Two-word extraction ---");
  testCommand("go north");
  testCommand("get lamp");
  testCommand("drop crystal");
  Serial.println();
  
  // Requirement 3.2: Single direction words interpreted as "GO [direction]"
  Serial.println("--- Requirement 3.2: Direction abbreviations ---");
  testCommand("north");
  testCommand("n");
  testCommand("south");
  testCommand("s");
  testCommand("east");
  testCommand("e");
  testCommand("west");
  testCommand("w");
  Serial.println();
  
  // Requirement 3.3: "I" interpreted as "INVENTORY"
  Serial.println("--- Requirement 3.3: I = INVENTORY ---");
  testCommand("i");
  testCommand("inventory");
  Serial.println();
  
  // Requirement 3.4: Articles ignored during parsing
  Serial.println("--- Requirement 3.4: Article filtering ---");
  testCommand("get the lamp");
  testCommand("get lamp");
  testCommand("take a crystal");
  testCommand("take crystal");
  testCommand("examine the lamp");
  Serial.println();
  
  // Requirement 3.5 & 3.6: Error cases (unknown words, missing nouns)
  Serial.println("--- Requirements 3.5 & 3.6: Error handling ---");
  testCommand("foo bar");
  testCommand("get baz");
  testCommand("get");
  Serial.println();
  
  // Requirement 3.7: All supported verbs recognized
  Serial.println("--- Requirement 3.7: Supported verbs ---");
  testCommand("go north");
  testCommand("get lamp");
  testCommand("take lamp");
  testCommand("drop lamp");
  testCommand("examine lamp");
  testCommand("look");
  testCommand("help");
  testCommand("score");
  testCommand("xyzzy");
  Serial.println();
  
  // Additional: Case-insensitive parsing (Requirement 2.3)
  Serial.println("--- Requirement 2.3: Case-insensitive ---");
  testCommand("go north");
  testCommand("GO NORTH");
  testCommand("Go North");
  testCommand("gO nOrTh");
  Serial.println();
  
  Serial.println("========================================");
  Serial.println("Test Complete");
  Serial.println("========================================");
}

void loop() {
  // Nothing
}
