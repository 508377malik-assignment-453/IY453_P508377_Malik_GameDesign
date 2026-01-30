# IY453 Stage 1

| Assessment Details | Please Complete All Details      |
| ------------------ | -------------------------------- |
| Group              | B                                |
| Module Title       | Software design & implementation |
| Assessment Type    | Coursework stage1                |
| Module Tutor Name  | Jonathon shore                   |
| Student ID Number  | P508377                          |
| Date of Submission | 30/01/2026                       |
| Word Count         |                                  |

- [x] *I confirm that this assignment is my own work. Where I have referred to academic sources, I have provided in-text citations and included the sources in
  the final reference list.*
- [x] *Where I have used AI, I have cited and referenced appropriately.

-----------------------------------------------------------------------------------------------------------------------------

**Introduction**

#Chatgpt (2025)

**Game Story Overview:**  
The game, titled **"Echoes of the Forgotten Realm"**, is designed to demonstrate good programming practice, object-oriented design, and creative problem solving.The player awakens in the **Forgotten Realm**, a land trapped between time and memory. To escape, they must recover three ancient relics hidden across forests, ruins, and underground caverns. Along the way, the player faces enemies, solves puzzles left by ancient guardians, and uncovers fragments of the realm’s lost history.





### Purpose of the Program and Specification

The software is a console-based adventure game:-

-The player enters their name at the start, which is used throughout the story.

-The game presents at least 30 binary choices, each leading to different consequences.

-Choices will result in:

-Progression to a new scene

-Gaining or losing items

-Combat encounters

-Puzzle challenges

-Game Over states

-The player manages an inventory containing weapons, clothing, food, potions, and keys.

-Player stats such as health, attack, defence, and score are affected by choices and items.

-The game can be saved and loaded using a file system.

-The game ends either in victory (escaping the realm) or defeat, followed by a final score screen.

------------------------------------------------------------------------------------------------------------------------------

### Input Process Output Scenario

**Outputs**

-Story description and dialogues.

-Consequences of player choices. 

-updated player stats and inventory display

-combat results (win or loss)

-puzzle feedback (success or failure message)

-error message for invalid output 

-Game over or victory message

-Final score summary at the end of the game 

**Inputs**

-Player name entered

-Player choices (1 or 2)

-Puzzles answers (numeric or text input)

-commands to save or load the game

-file name (to save the progress of game)

**Process**

-Initialise player statistics (health, attack, defence, score)

-Display story scenes and binary choices 

-Validate user input and handle invalid inputs 

-Update player health, score, and stats based on choices

-Add, remove, and manage inventory items

-Resolve combat using combat ratings and random values

-Check puzzle answers and apply rewards or damages

-save current game progress to a file.

-Load a previously saved game progress.

-check win, loss, or game continuation conditions.

------------------------------------------------------------------------------------------------------------------------------

### Algorithms

------------------------------------------------------------------------------------------------------------------------------


