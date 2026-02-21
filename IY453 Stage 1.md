# 🗡️ The Shattered Realm — Game Design Document

> A text-based choose-your-own-adventure game built in C++17

---

## Overview

You are **[PLAYER NAME]**, a wandering adventurer tasked with recovering the shattered **Crystal of Ages** and defeating the dragon **Malachar** before he plunges the realm into eternal darkness. Every choice shapes your path — collect items, solve puzzles, survive combat, and reach the volcanic lair.

| Property | Detail |
| --- | --- |
| Genre | Dark Fantasy / Text Adventure |
| Language | C++17 / CLion |
| Total Scenes | 31 (1 start + 30 branching nodes) |
| Scene Types | Story, Combat, Puzzle, Item Collection |

---

## Branching Scene Tree

The game is a **5-level binary tree**. Each node offers two choices — some reward progress, others end in defeat.

```
                                    START
                         ┌────────────────────────┐
                      Choice 1                 Choice 2
               ┌──────────┐               ┌──────────┐
           Choice 3    Choice 4       Choice 5    Choice 6
           ┌──┐         ┌──┐          ┌──┐         ┌──┐
          C7  C8       C9  C10      C11  C12     C13  C14
         ┌─┐ ┌─┐     ┌─┐  ┌─┐    ┌─┐  ┌─┐    ┌─┐   ┌─┐
        15 16 17 18  19 20 21 22 23 24 25 26  27 28 29 30

                    All paths lead to Scene 31: Malachar
```

---

## Scene Summary

| Scene | Title | Type | Choice A | Choice B |
| --- | --- | --- | --- | --- |
| 0   | Crossroads of Aldenmoor | Story | Forest path east → Scene 1 | Cursed road west → Scene 2 |
| 1   | The Whispering Forest | Item | Free the fox → Elvish Boots | Grab ranger's pack → Knife + Meat |
| 2   | The Cursed Road | Puzzle (Riddle) | Answer riddle → Spectral Cloak | Grab & run → Rusty Key, -3 HP |
| 3   | The Fox's Secret | Item | Take crystal shard → +100 score | Force chest open → Gauntlets, -4 HP |
| 4   | The Goblin Scout | Combat | Fight goblin → win or Game Over | Flee to treehouse → Sword + Bread |
| 5   | Village of Thornwall | Item | Trade with blacksmith → Iron Sword | Guard the healer → Healing Potion |
| 6   | The Cursed Swamp | Puzzle (Anagram) | Solve anagram → Swamp Pearl | Navigate by stars → herb or -3 HP |
| 7   | The Crystal Shrine | Item | Drink chalice → +ATK +HP | Read scroll → combat bonus forever |
| 8   | The Skeletal Guardian | Combat | Fight skeleton → win or Game Over | Sneak through briars → Bandages, -2 HP |
| 9   | After the Goblin | Item | Open hollow oak → Malachar's Seal | Take mountain trail → Mountain Herb |
| 10  | The Treehouse Strongbox | Puzzle (Maths) | Solve riddle → Dragon Scale Armour | Pull lever → Silver Dagger, -3 HP |
| 11  | The Blacksmith's Quarter | Combat | Fight mercenary → win or Game Over | Negotiate → Crossbow |
| 12  | The Night Watch | Combat | Throw vial → full HP restore | Fight wolves → win or Game Over |
| 13  | The Sunken Temple | Item | Take Cursed Spear → +6 ATK, -1 HP/scene | Drink from font → full HP + shield |
| 14  | The Crossroads Shrine | Item | Take compass → unlock secret path | Take Shadowblend → enemy -3 ATK |
| 15–30 | Final Approach | Outcome | Player enters Final Battle with accumulated stats | —   |
| 31  | Malachar's Lair | Boss Combat | Defeat Malachar → Victory | Lose → Game Over |

---

## Combat System

```
playerScore = player.attack + rand(1–10) + bonuses
enemyScore  = enemy.attack  + rand(1–10)

if playerScore > enemyScore → enemy takes damage
else                        → player takes damage

damage = max(1, attacker.attack − defender.defense)
Repeat until HP = 0. Player HP = 0 → Game Over.
```

### Enemy Roster

| Enemy | ATK | DEF | HP  | Reward |
| --- | --- | --- | --- | --- |
| Goblin Scout | 6   | 2   | 8   | +75 score |
| Skeletal Warrior | 7   | 4   | 10  | Steel Shield, +100 score |
| Mercenary | 9   | 3   | 12  | Iron Sword, +125 score |
| Wolf Pack | 8   | 2   | 15  | Wolf Pelt, +100 score |
| **Malachar** | **14** | **6** | **30** | Victory, +500 score |

---

## Item System

| Item | Type | Effect | Found |
| --- | --- | --- | --- |
| Hunting Knife | Weapon | +3 ATK | Scene 1B |
| Crude Sword | Weapon | +2 ATK | Scene 4B |
| Iron Sword | Weapon | +5 ATK | Scene 5A / 11A |
| Silver Dagger | Weapon | +4 ATK | Scene 10B |
| Cursed Spear | Weapon | +6 ATK, -1 HP/scene | Scene 13A |
| Crossbow | Weapon | +3 ATK | Scene 11B |
| Elvish Boots | Armour | +2 DEF | Scene 1A |
| Spectral Cloak | Armour | +3 DEF | Scene 2A |
| Steel Gauntlets | Armour | +4 DEF | Scene 3B |
| Steel Shield | Armour | +3 DEF | Scene 8A |
| Dragon Scale Armour | Armour | +5 DEF | Scene 10A |
| Wolf Pelt | Armour | +3 DEF | Scene 12B |
| Healing Potion | Consumable | +5 HP | Scene 5B |
| Dried Meat | Food | +2 HP | Scene 1B |
| Mountain Herb | Food | +4 HP | Scene 9B |
| Clarity Potion | Potion | +3 ATK, +2 HP | Scene 7A |
| Shadowblend | Potion | Enemy ATK -3 (1 use) | Scene 14B |
| Brass Key | Key | Opens hollow oak chest | Scene 4A |
| Malachar's Seal | Key | Unlocks final gate | Scene 9A |
| Compass | Special | Bypasses Phase 1 of Malachar | Scene 14A |

---

## Puzzles

| Scene | Type | Question | Answer |
| --- | --- | --- | --- |
| Scene 2 | Riddle | "I have cities but no houses, mountains but no trees, water but no fish…" | `A MAP` |
| Scene 6 | Anagram | Unscramble: **D R S W A** | `WARDS` |
| Scene 10 | Maths | "Sum of the first five prime numbers" | `28` |

---

## Score System

| Action | Points |
| --- | --- |
| Correct puzzle answer | +50–75 |
| Defeating an enemy | +75–125 |
| Crystal shard collected | +100 |
| Finding Malachar's Seal | +150 |
| Defeating Malachar | +500 |
| Game completion bonus | +200 |

| Score | Rating |
| --- | --- |
| 0–299 | 🥉 Bronze Wanderer |
| 300–599 | 🥈 Silver Adventurer |
| 600–899 | 🥇 Gold Champion |
| 900+ | 🐉 Legendary Dragon Slayer |

---

## Save & Load

- Save triggered **after every scene** and **before combat**
- Binary file: `saves/savegame.dat`
- Stores: player name, current scene, HP, ATK, DEF, score, inventory, story flags

---

## C++ Class Architecture

```
Item                        — name, type, ATK/DEF/HP bonuses
Player                      — stats, inventory, score, save/load
Scene (abstract base)
  ├── StoryScene            — binary choice navigation
  ├── CombatScene           — RNG battle loop
  ├── PuzzleScene           — riddle / anagram / maths
  └── ItemScene             — item collection and pickup
Game                        — scene map, game loop, menus
Utils                       — input validation helpers
```

---

## Project File Structure

```
ShatteredRealm/
├── CMakeLists.txt
├── README.md
├── GAME_DESIGN.md
├── include/
│   ├── Item.h
│   ├── Player.h
│   ├── Scene.h
│   ├── StoryScene.h
│   ├── CombatScene.h
│   ├── PuzzleScene.h
│   ├── ItemScene.h
│   ├── Game.h
│   └── Utils.h
├── src/
│   ├── *.cpp (matching above)
│   └── main.cpp
└── saves/
    └── savegame.dat
```

---

*Version 1.0 — Stage 1 Design | The Shattered Realm*
