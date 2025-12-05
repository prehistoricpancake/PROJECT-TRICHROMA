# PROJECT TRICHROMA - Quick Reference Card

## Hardware Setup
```
Pin 12 ──[220Ω]── RED LED ── GND
Pin 4  ──[220Ω]── BLUE LED ── GND
Pin 8  ──[220Ω]── GREEN LED ── GND

Serial Monitor: 9600 baud, Newline
```

## Essential Commands
| Command | Action |
|---------|--------|
| N, S, E, W, U, D | Move in direction |
| GET/TAKE [item] | Pick up item |
| DROP [item] | Drop item |
| EXAMINE [item] | Look at item closely |
| INVENTORY or I | List items carried |
| LOOK | Redisplay room |
| SCORE | Check progress |
| HELP | Show help |

## Quick Map
```
        EQUIPMENT(14)
              |
        RESEARCH(13)
              |
MOTHER(11)-ADMIN(12)
     |
SISTER(10)
     |
GREEN(9)──ENTRANCE(0)──RED(1)──ANGER(2)
              |
         BLUE_MAZE_1(3)
              |
         BLUE_MAZE_2(4)
              |
         BLUE_MAZE_3(5)
              |
         BLUE_MAZE_4(6)
              |
         BLUE_MAZE_5(7)
              |
        MAZE_CENTER(8)
```

## Crystal Locations
1. RED_CAVERN (1)
2. ANGER_PIT (2)
3. BLUE_MAZE_2 (4)
4. BLUE_MAZE_4 (6)
5. MAZE_CENTER (8)
6. GREEN_CHAMBER (9)
7. SISTER_MEMORY (10)
8. MOTHER_MEMORY (11)
9. RESEARCH_LAB (13)
10. EQUIPMENT_ROOM (14)

## Scoring
- Collect crystal: +5
- Deposit crystal: +5
- Stolen crystal: -5
- Defeat Blackwood: +50
- **Max: 150 points**

## Critical Items
- **LAMP** - Start with it, use as maze marker
- **WIRE_CUTTER** - In MAZE_CENTER, needed for final boss
- **TROPHY_CASE** - In GREEN_CHAMBER, deposit crystals here

## Blackwood Spawn Rates
- Base: 15%
- RED rooms: 35%
- 3+ crystals: 50%
- GREEN_CHAMBER: 0% (SAFE!)
- ADMIN_ROOM: 100%

## Easter Eggs
- XYZZY, PLUGH, ZORK
- NEWS, .SNOOPER, 666, TRACE

## Winning Strategy
1. Collect all 10 crystals
2. Deposit in trophy case (GREEN_CHAMBER)
3. Get WIRE_CUTTER from maze
4. Go to ADMIN_ROOM
5. USE WIRE_CUTTER on Blackwood
6. Return to GREEN_CHAMBER
7. Type Y for shutdown protocol

## Tips
- Deposit crystals often to avoid theft
- GREEN_CHAMBER is safe zone
- Don't carry 3+ crystals in RED rooms
- Map the maze on paper
- Keep WIRE_CUTTER safe!

---
*For full guide, see PLAYER_GUIDE.md*
