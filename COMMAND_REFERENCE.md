# PROJECT TRICHROMA - Command Reference

## Command Parser Mechanics

### Two-Word Parser System
PROJECT TRICHROMA uses an authentic 1970s-style two-word parser:
- First word = VERB (action)
- Second word = NOUN (object/direction)
- Additional words are ignored

### Input Processing
1. Input converted to UPPERCASE
2. Articles (THE, A, AN) removed
3. First two words extracted
4. Verb and noun matched against known words
5. Command executed or error displayed

---

## Complete Verb List

### Movement Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| GO | - | GO [direction] | GO NORTH |

**Note:** Single direction words auto-expand to GO commands.

### Object Manipulation Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| GET | TAKE | GET [object] | GET LAMP |
| DROP | - | DROP [object] | DROP CRYSTAL |
| EXAMINE | - | EXAMINE [object] | EXAMINE TROPHY_CASE |
| USE | - | USE [object] | USE WIRE_CUTTER |

### Information Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| LOOK | - | LOOK | LOOK |
| INVENTORY | I | INVENTORY | I |
| SCORE | - | SCORE | SCORE |
| HELP | - | HELP | HELP |

### Communication Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| TALK | - | TALK | TALK |

### System Verbs
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| QUIT | - | QUIT | QUIT |
| TRACE | - | TRACE | TRACE |
| CONNECT | - | CONNECT | CONNECT |

### Combat Verbs (Legacy)
| Verb | Aliases | Usage | Example |
|------|---------|-------|---------|
| KILL | ATTACK | KILL [enemy] | KILL BLACKWOOD |

**Note:** Combat verbs display flavor text but don't affect gameplay.

### Easter Egg Verbs
| Verb | Usage | Description |
|------|-------|-------------|
| XYZZY | XYZZY | Colossal Cave Adventure reference |
| PLUGH | PLUGH | Colossal Cave Adventure reference |
| ZORK | ZORK | Tribute to Zork |
| NEWS | NEWS | Display in-universe patch notes |
| .SNOOPER | .SNOOPER | Helena's command history |
| 666 | 666 | Glitch sequence revelation |

---

## Complete Noun List

### Directions
| Noun | Shortcut | Description |
|------|----------|-------------|
| NORTH | N | Move north |
| SOUTH | S | Move south |
| EAST | E | Move east |
| WEST | W | Move west |
| UP | U | Move up |
| DOWN | D | Move down |

### Objects
| Noun | Location(s) | Properties |
|------|-------------|------------|
| LAMP | Starting inventory | Portable, can be dropped as marker |
| CRYSTAL | Various rooms (10 total) | Portable, treasure, increases LED |
| WIRE_CUTTER | MAZE_CENTER | Portable, required for final boss |
| TROPHY_CASE | GREEN_CHAMBER | Non-portable, stores crystals |
| TERMINAL | Various rooms | Non-portable, flavor object |
| NOTES | RESEARCH_LAB | Non-portable, lore object |

---

## Command Examples

### Valid Commands
```
> GO NORTH
> N
> GET LAMP
> TAKE CRYSTAL
> DROP THE LAMP
> EXAMINE TROPHY CASE
> USE WIRE_CUTTER
> INVENTORY
> I
> LOOK
> SCORE
> HELP
> TALK
> XYZZY
> NEWS
> .SNOOPER
> 666
> TRACE
> QUIT
```

### Invalid Commands (with error messages)
```
> JUMP
I don't know the word 'JUMP'.

> GET
What do you want to GET?

> GO
What do you want to GO?

> TAKE BLACKWOOD
You can't take that.

> GET ROCK
I don't see that here.

> GO NORTHWEST
I don't know the word 'NORTHWEST'.
```

### Article Filtering Examples
```
> GET THE LAMP
(Processed as: GET LAMP)

> EXAMINE A CRYSTAL
(Processed as: EXAMINE CRYSTAL)

> DROP AN OBJECT
(Processed as: DROP OBJECT)
```

### Case Insensitivity Examples
```
> get lamp
(Processed as: GET LAMP)

> Go North
(Processed as: GO NORTH)

> eXaMiNe CrYsTaL
(Processed as: EXAMINE CRYSTAL)
```

---

## Special Command Behaviors

### Direction Shortcuts
Single-word direction commands automatically expand:
- `N` → `GO NORTH`
- `S` → `GO SOUTH`
- `E` → `GO EAST`
- `W` → `GO WEST`
- `U` → `GO UP`
- `D` → `GO DOWN`

### Inventory Shortcut
- `I` → `INVENTORY`

### Context-Sensitive Commands

#### USE Command
- **In ADMIN_ROOM with WIRE_CUTTER:** Triggers boss battle
- **Elsewhere:** Generic response

#### DROP Command
- **In GREEN_CHAMBER with CRYSTAL:** Auto-deposits in trophy case
- **Elsewhere:** Drops object in current room

#### EXAMINE Command
- **TROPHY_CASE:** Shows crystal count (X of 10)
- **CRYSTAL:** Shows unique memory description
- **Other objects:** Shows object description

---

## Error Messages Reference

### Parser Errors
| Error | Cause | Solution |
|-------|-------|----------|
| "I don't know the word '[word]'." | Unrecognized verb or noun | Check command reference |
| "What do you want to [verb]?" | Verb requires noun | Add object/direction |

### Movement Errors
| Error | Cause | Solution |
|-------|-------|----------|
| "You can't go that way." | No exit in that direction | Use LOOK to see exits |

### Object Errors
| Error | Cause | Solution |
|-------|-------|----------|
| "I don't see that here." | Object not in room | Use LOOK to see objects |
| "You can't take that." | Object is non-portable | Leave it in place |
| "You're carrying too much." | Inventory full (8 items) | Drop something first |
| "You're not carrying that." | Object not in inventory | Check INVENTORY |

### Action Errors
| Error | Cause | Solution |
|-------|-------|----------|
| "You can't do that." | Invalid action | Try different approach |

---

## Advanced Parser Features

### Multi-Word Object Names
The parser handles multi-word objects by matching the noun:
- "TROPHY CASE" → Matches TROPHY_CASE
- "WIRE CUTTER" → Matches WIRE_CUTTER
- "MEMORY CRYSTAL" → Matches CRYSTAL

### Abbreviation Expansion
Common abbreviations are expanded:
- `I` → `INVENTORY`
- `N, S, E, W, U, D` → Full direction names

### Input Buffer
- Maximum 64 characters accepted
- Longer input is truncated
- Non-printable characters filtered

---

## Command Timing

### Idle System
- **30 seconds** without input triggers Helena's whisper
- Any command resets the timer
- Whispers provide atmospheric storytelling

### Blackwood Cooldown
- After encounter, brief cooldown before next spawn
- Prevents immediate consecutive encounters

### LED Response Timing
- Commands execute immediately
- LED patterns update non-blocking
- Serial input never blocked by animations

---

## Tips for Effective Commands

### Be Specific
```
Good: GET CRYSTAL
Bad:  GET THING
```

### Use Shortcuts
```
Fast: N
Slow: GO NORTH
```

### Check Before Acting
```
> LOOK
(See what's in the room)
> GET LAMP
```

### Verify Inventory
```
> I
(Check what you're carrying)
> DROP CRYSTAL
```

### Explore Systematically
```
> LOOK
(Note all exits)
> GO NORTH
> LOOK
(Map as you go)
```

---

## Command Frequency Guide

### Essential Commands (Use Often)
- `N, S, E, W, U, D` - Navigation
- `GET/TAKE` - Collecting items
- `DROP` - Managing inventory
- `LOOK` - Orientation
- `INVENTORY/I` - Inventory check

### Important Commands (Use Regularly)
- `EXAMINE` - Object details
- `SCORE` - Progress tracking
- `HELP` - Reference

### Situational Commands (Use When Needed)
- `USE` - Final boss only
- `TALK` - Flavor dialogue
- `QUIT` - Exit game

### Discovery Commands (Use Once)
- `XYZZY, PLUGH, ZORK` - Easter eggs
- `NEWS` - Lore
- `.SNOOPER` - History
- `666` - Dark revelation
- `TRACE` - Network scan

---

*For gameplay strategies, see WALKTHROUGH.md*  
*For complete game guide, see PLAYER_GUIDE.md*
