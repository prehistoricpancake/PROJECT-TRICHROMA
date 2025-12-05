# Serial Monitor Configuration Guide

## Problem
The game is running but commands aren't being processed when you type in the Serial Monitor.

## Solution: Configure Serial Monitor Settings

### Arduino IDE Settings
1. **Baud Rate**: Set to **9600** (bottom right of Serial Monitor)
2. **Line Ending**: Set to **"Newline"** or **"Both NL & CR"** (dropdown next to baud rate)
3. **Input Box**: Type commands in the input box at the top
4. **Send Button**: Click "Send" or press Enter to submit commands

### Common Issues

#### Issue 1: No Echo When Typing
- **Symptom**: You type but don't see characters appear
- **Cause**: Local echo is off (this is normal for Arduino)
- **Solution**: Type your command and press Enter/Send - you'll see the response

#### Issue 2: Commands Not Processing
- **Symptom**: You press Enter but nothing happens
- **Cause**: Line ending not set correctly
- **Solution**: Set line ending to "Newline" or "Both NL & CR"

#### Issue 3: Duplicate Output
- **Symptom**: Room description appears twice
- **Cause**: Arduino reset when Serial Monitor opened
- **Solution**: This is normal - the boot sequence runs again

## How to Play

### Basic Commands
Type these commands in the Serial Monitor input box and press Enter:

```
LOOK          - Look around current room
NORTH or N    - Go north
SOUTH or S    - Go south  
EAST or E     - Go east
WEST or W     - Go west
INVENTORY or I - Check inventory
EXAMINE LAMP  - Examine an object
GET LAMP      - Pick up an object
DROP LAMP     - Drop an object
HELP          - Show help
SCORE         - Show score
```

### Example Session
```
> LOOK
[Room description appears]

> NORTH
[Move to new room, description appears]

> EXAMINE CRYSTAL_FAMILY
[Crystal description and Helena's dialogue appears]

> GET CRYSTAL_FAMILY
[Pick up the crystal, LED pulses]
```

## Testing the Game

### Test 1: Basic Movement
```
> NORTH
```
Expected: Move to Red Cavern, see new room description

### Test 2: Examine Object
```
> EXAMINE LAMP
```
Expected: See lamp description and Helena's dialogue

### Test 3: Check Inventory
```
> I
```
Expected: See list of items you're carrying (should include LAMP)

### Test 4: Look Around
```
> LOOK
```
Expected: See current room description again

## Troubleshooting

### If Nothing Happens When You Type:
1. Check baud rate is 9600
2. Check line ending is set to "Newline"
3. Make sure you're pressing Enter or clicking Send
4. Try typing a simple command like: `LOOK`

### If You See Garbled Text:
1. Wrong baud rate - set to 9600
2. Close and reopen Serial Monitor

### If Arduino Keeps Resetting:
1. This is normal when opening Serial Monitor
2. Wait for boot sequence to complete
3. You'll see the room description and `> ` prompt

### If LEDs Work But No Text Response:
1. Commands are being received but not processed
2. Check that you're using valid commands (see HELP)
3. Try: `HELP` to see all commands

## Current Game State

Based on your output, you are:
- **Location**: Entrance (Room 0)
- **Inventory**: LAMP
- **Available Exits**: NORTH (to Red Cavern), EAST (to Research Lab)
- **Helena's Dialogue**: "...you came back... or is this the first time...? i can't remember anymore..."

## Next Steps

Try these commands in order:
1. `LOOK` - Confirm you can see the room
2. `I` - Check your inventory
3. `NORTH` - Move to Red Cavern
4. `EXAMINE CRYSTAL_FAMILY` - Look at the crystal
5. `GET CRYSTAL_FAMILY` - Pick it up (watch the RED LED pulse!)

## LED Behavior

You should see:
- **RED LED (Pin 12)**: Emotional state - pulses in red rooms
- **BLUE LED (Pin 4)**: Logic state - pulses in maze
- **GREEN LED (Pin 8)**: Identity state - pulses in green chamber

The LEDs change based on which room you're in and what you interact with.
