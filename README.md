
# Rogue Runner – OOP Console Game

Rogue Runnder is a object-oriented console game whereby a character has to defeat all enemies in each round in order to progress to the next one. There are a total of three rounds with enemies like slimes, which attack in adjacent squares, and archers which attack 2 positions away. Potions can be collected throughout the game to restore health and are spawned randomly in each round. Once all three rounds are complete the player will recieve a victory message along with a new high score added to the scoreboard.

The project consists of 10+ classes; GameObject, Enemy (Abstract), Actor, Slime, Archer, Player, Map, Potion, Scoreboard and Game. It adheres to encapsulation principles as within classes or inherited classes data members are private/protected and can be accessed using getters. There is a three level inheritance hierarchy, from GameObject, to Actor, to Enemy, to Slime/Archer. There is also Enemy which is an abstract class which uses a pure virtual doMoveAttack(...) and enforces subclass behaviour. Polymorphism is utilised in the abstract class Enemy with a pure virtual doMoveAttack(...) which slime and Archer can override to implement their unique decision logic. Enemies are stored as a unique_ptr<Enemy> and polymorphism runs subclass behaviour so new enemy types plug in without changing the loop.

Furthermore, the project uses ASCII map and HUD display which shows Round, Turn, Score, HP, Potions, and Enemies followed by their respective update logic. The program also writes data to a file successfully (score.txt) in the expected format, it also reads the top three scores by sorting and reconstructing object states, and it alos utilises a menu that is functioning and easy to use.

The program also handles runtime errors well and uses try-catch statements, and uses defensive programming to accurately handle invalid user inputs. tests/tests.cpp asserts scoreboard ordering and basic line-of-sight.

Throughout the project, a clean code-style was used for readability such as conistant formatting, commenting to understand what each line or section of code does, #pragma once to keep clean instead of traditional #indef #endif, and appropriate headers were used. There was accurate use of dynamic memory such as using smart pointers for polymorphic objects so new/delete is unnecessary to avoid memory leaks. 

## Build & Run
bash:
make
make run

## Controls
- 'W A S D' to move
- 'F' to attack adjacent enemy (up/down/left/right)
- 'E' to drink potion (+9 HP)
- 'Q' to quit to menu

## Rules
- Map with walls ('#') and random obstacles; border enforced.
- Slime ('S'): attacks only when adjacent, every 2nd turn.
- Archer ('A'): attacks every second turn from exactly 2 tiles away in the same row/column, with line of sight and cannot shoot through walls.
- Player ('@'): attacks only adjacent.
- Potion ('!'): one spawns each round; pick up to gain an extra heal. You start with 1.
- 3 rounds. More mobs each round. Victory after Round 3.
- Score: +10 per kill, +25 bonus on victory. Top 3 saved in `scores.txt`.

## Testing
bash
make tests
./bin/tests

Tests cover line‑of‑sight including wall blocking and scoreboard ordering.

## Files
- 'src/*.cpp', 'include/*.hpp'
- 'scores.txt' was created on first save
- 'tests/tests.cpp'
- 'Makefile'
- 'README.md'
