# Blue Maze Navigation Test

## Test Scenario: Navigate through the Blue Maze

### Starting Position
- Room: ENTRANCE (Room 0)
- Inventory: LAMP

### Test Steps

1. **Enter the maze from RED_CAVERN**
   ```
   > GO NORTH          (to RED_CAVERN, Room 1)
   > GO WEST           (to BLUE_MAZE_1, Room 3)
   ```
   - Expected: BLUE LED starts strobing at 400ms period (brightness 200)
   - Expected: Description shows "maze of twisting passages" with binary "HELP"

2. **Progress through maze sections**
   ```
   > GO NORTH          (to BLUE_MAZE_2, Room 4)
   ```
   - Expected: BLUE LED strobes faster at 325ms period (brightness 210)
   - Expected: Binary code shows "WHY"
   
   ```
   > GO EAST           (to BLUE_MAZE_3, Room 5)
   ```
   - Expected: BLUE LED strobes faster at 250ms period (brightness 220)
   - Expected: Binary code shows "LOST"
   
   ```
   > GO NORTH          (to BLUE_MAZE_4, Room 6)
   ```
   - Expected: BLUE LED strobes faster at 175ms period (brightness 230)
   - Expected: Binary code shows "THINK"
   
   ```
   > GO NORTH          (to BLUE_MAZE_5, Room 7)
   ```
   - Expected: BLUE LED strobes fastest at 100ms period (brightness 240)
   - Expected: Binary code shows "CLOSE"

3. **Reach the maze center**
   ```
   > GO NORTH          (to MAZE_CENTER, Room 8)
   ```
   - Expected: BLUE LED becomes steady (no strobing, brightness 180)
   - Expected: Description shows "You have reached the center of the maze"
   - Expected: WIRE_CUTTER is visible in the room

4. **Test LAMP as location marker**
   ```
   > DROP LAMP         (in MAZE_CENTER)
   > GO SOUTH          (back to BLUE_MAZE_5)
   > GO NORTH          (return to MAZE_CENTER)
   > LOOK
   ```
   - Expected: LAMP is still in MAZE_CENTER

5. **Collect the WIRE_CUTTER**
   ```
   > GET WIRE_CUTTER
   > INVENTORY
   ```
   - Expected: WIRE_CUTTER is now in inventory

## LED Behavior Summary

| Room | LED Brightness | Strobe Period | Blink Rate |
|------|---------------|---------------|------------|
| BLUE_MAZE_1 | 200 | 400ms | 2.5 Hz |
| BLUE_MAZE_2 | 210 | 325ms | 3.1 Hz |
| BLUE_MAZE_3 | 220 | 250ms | 4.0 Hz |
| BLUE_MAZE_4 | 230 | 175ms | 5.7 Hz |
| BLUE_MAZE_5 | 240 | 100ms | 10.0 Hz |
| MAZE_CENTER | 180 | N/A (steady) | 0 Hz |

## Maze Map

```
                    MAZE_CENTER (8)
                         |
                    BLUE_MAZE_5 (7)
                         |
                    BLUE_MAZE_4 (6)
                         |
                    BLUE_MAZE_3 (5)
                         |
                    BLUE_MAZE_2 (4)
                         |
                    BLUE_MAZE_1 (3)
                         |
                    RED_CAVERN (1)
                         |
                     ENTRANCE (0)
```

## Success Criteria
- ✅ All maze rooms are accessible via correct directional commands
- ✅ BLUE LED blink frequency increases progressively through maze
- ✅ BLUE LED becomes steady in MAZE_CENTER
- ✅ Binary code messages display correctly in each room
- ✅ WIRE_CUTTER is present and collectible in MAZE_CENTER
- ✅ LAMP can be dropped and persists as location marker
- ✅ All room descriptions match Colossal Cave Adventure style
