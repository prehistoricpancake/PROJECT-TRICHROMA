# SCORE Command - Serial Monitor Display Examples

## How to View Your Score

At any time during gameplay, type `SCORE` in the Serial Monitor and press Enter to see your current progress.

---

## Example 1: Game Start (No Crystals Collected)

```
> SCORE

==== SCORE ====
Score: 0/150
Collected: 0/10
Deposited: 0/10
Rank: RANDOM
===============
[Helena: ...scattered...]

> 
```

**Explanation:**
- Score: 0 out of 150 maximum points
- Collected: 0 crystals picked up
- Deposited: 0 crystals in trophy case
- Rank: RANDOM (lowest rank, 0-30 points)
- Helena's comment reflects her fragmented state

---

## Example 2: After Collecting 3 Crystals

```
> SCORE

==== SCORE ====
Score: 15/150
Collected: 3/10
Deposited: 0/10
Rank: RANDOM
===============
[Helena: ...more real...]

> 
```

**Explanation:**
- Score: 15 points (3 crystals × 5 points each)
- Collected: 3 crystals in inventory
- Deposited: 0 crystals in trophy case
- Rank: Still RANDOM (need 31+ for NOVICE HACKER)
- Helena feels "more real" with some memories restored

---

## Example 3: After Collecting 5 Crystals and Depositing 2

```
> SCORE

==== SCORE ====
Score: 35/150
Collected: 5/10
Deposited: 2/10
Rank: NOVICE HACKER
===============
[Helena: ...coming back...]

> 
```

**Explanation:**
- Score: 35 points (5 collected × 5 = 25, plus 2 deposited × 5 = 10)
- Collected: 5 crystals total found
- Deposited: 2 crystals in trophy case
- Rank: NOVICE HACKER (31-70 points)
- Helena is "coming back" with more memories

---

## Example 4: After Blackwood Steals a Crystal

```
> SCORE

==== SCORE ====
Score: 30/150
Collected: 4/10
Deposited: 2/10
Rank: RANDOM
===============
[Helena: ...coming back...]

> 
```

**Explanation:**
- Score: 30 points (was 35, lost 5 from theft)
- Collected: 4 crystals (one was stolen)
- Deposited: 2 crystals still safe in trophy case
- Rank: Dropped back to RANDOM (30 points)
- Note: Stolen crystal can be recovered from its original room

---

## Example 5: All 10 Crystals Collected and Deposited

```
> SCORE

==== SCORE ====
Score: 100/150
Collected: 10/10
Deposited: 10/10
Rank: EXPERIENCED HACKER
===============
[Helena: ...whole...]

> 
```

**Explanation:**
- Score: 100 points (10 collected × 5 = 50, plus 10 deposited × 5 = 50)
- Collected: All 10 crystals found
- Deposited: All 10 crystals in trophy case
- Rank: EXPERIENCED HACKER (71-110 points)
- Helena feels "whole" with all memories restored
- Ready to access ADMIN_ROOM with CONNECT command

---

## Example 6: After Defeating Blackwood (Perfect Score)

```
> SCORE

==== SCORE ====
Score: 150/150
Collected: 10/10
Deposited: 10/10
Rank: IMPLEMENTER
===============
[Helena: ...whole...]

> 
```

**Explanation:**
- Score: 150 points (PERFECT SCORE!)
  - 10 crystals collected: +50 points
  - 10 crystals deposited: +50 points
  - Blackwood defeated: +50 points
- Rank: IMPLEMENTER (highest rank, 141-150 points)
- Ready for final shutdown protocol

---

## Example 7: After Multiple Blackwood Encounters (Imperfect Run)

```
> SCORE

==== SCORE ====
Score: 135/150
Collected: 10/10
Deposited: 10/10
Rank: MASTER HACKER
===============
[Helena: ...whole...]

> 
```

**Explanation:**
- Score: 135 points (lost 15 points to Blackwood thefts)
  - 10 crystals collected: +50 points
  - 10 crystals deposited: +50 points
  - Blackwood defeated: +50 points
  - 3 crystals stolen: -15 points (recovered and re-collected)
- Rank: MASTER HACKER (111-140 points)
- Still a great score!

---

## Rank System

The rank is automatically calculated based on your current score:

| Score Range | Rank |
|-------------|------|
| 0-30 | RANDOM |
| 31-70 | NOVICE HACKER |
| 71-110 | EXPERIENCED HACKER |
| 111-140 | MASTER HACKER |
| 141-150 | IMPLEMENTER |

---

## Score Breakdown

### How to Earn Points
- **+5 points** - Pick up a memory crystal (GET CRYSTAL)
- **+5 points** - Deposit a crystal in trophy case (DROP CRYSTAL in GREEN_CHAMBER)
- **+50 points** - Defeat Dr. Blackwood (USE WIRE_CUTTER in ADMIN_ROOM)

### How to Lose Points
- **-5 points** - Blackwood steals a crystal during encounter

### Maximum Score
- **150 points** - Perfect run with no crystal thefts
  - 10 crystals collected: 50 points
  - 10 crystals deposited: 50 points
  - Blackwood defeated: 50 points

---

## Tips for Maximum Score

1. **Avoid Blackwood Encounters**
   - Stay in GREEN_CHAMBER when carrying 3+ crystals (safe zone)
   - Deposit crystals frequently to reduce theft risk
   - Avoid RED rooms (ANGER_PIT, RED_CAVERN) when carrying crystals

2. **Efficient Collection Strategy**
   - Collect crystals in batches
   - Return to GREEN_CHAMBER to deposit
   - Repeat until all 10 are deposited

3. **Recovery from Theft**
   - Stolen crystals return to their original rooms
   - You can collect them again
   - Score penalty is only -5 points per theft

---

## Helena's Commentary

Helena's dialogue changes based on your progress:

- **0 crystals:** "...scattered..." (fragmented, incomplete)
- **1-4 crystals:** "...more real..." (beginning to remember)
- **5-9 crystals:** "...coming back..." (memories returning)
- **10 crystals deposited:** "...whole..." (consciousness restored)

---

## When to Check Your Score

Good times to check your score:
- After collecting your first crystal
- After depositing crystals in trophy case
- After a Blackwood encounter (to see if you lost points)
- Before attempting CONNECT command (need all 10 deposited)
- After defeating Blackwood (to see final score)

---

## Final Score Display

At the end of the game (shutdown protocol), you'll see a more detailed final score:

```
==== FINAL SCORE ====
Score: 150/150

Rank: IMPLEMENTER

Crystals: 10/10
Blackwood: DEFEATED
Helena: FREED

====================
Thank you for playing
PROJECT TRICHROMA.
====================
```

---

## Testing the SCORE Command

To test the SCORE command right now:

1. Open Serial Monitor (9600 baud)
2. Type `SCORE` and press Enter
3. You should see the score display immediately
4. Try it at different points in the game to track progress

---

## Troubleshooting

**Q: SCORE command doesn't work**
- Check spelling: `SCORE` (all caps or lowercase both work)
- Make sure you press Enter after typing
- Verify Serial Monitor is connected

**Q: Score seems wrong**
- Each crystal pickup: +5 points
- Each crystal deposit: +5 points (total +10 per crystal)
- Each crystal theft: -5 points
- Blackwood defeat: +50 points

**Q: Rank doesn't match score**
- Rank is calculated automatically based on score ranges
- Check the rank table above for correct ranges

---

## Summary

The SCORE command is your progress tracker throughout the game. Use it frequently to:
- Monitor your point total
- Track crystal collection progress
- See your current rank
- Get Helena's emotional feedback
- Plan your strategy for maximum score

**Type `SCORE` anytime to see your progress!**

