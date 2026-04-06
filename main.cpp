#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Scene.h"
using namespace std;

int GetChoice()
{
    while (true)
    {
        cout << "Enter choice (1 or 2): ";
        string input;
        cin >> input;
        try
        {
            int choice = stoi(input);
            if (choice == 1 || choice == 2)
            {
                return choice;
            }
            throw out_of_range("Choice must be 1 or 2");
        }
        catch (const invalid_argument &)
        {
            cout << "Invalid input. Please type 1 or 2.\n";
        }
        catch (const out_of_range &)
        {
            cout << "Please enter either 1 or 2.\n";
        }
    }
}

void SaveGame(Player &player)
{
    ofstream file("savegame.txt");
    if (!file)
    {
        cout << "Error: Could not save the game.\n";
        return;
    }
    file << player.name       << "\n";
    file << player.health     << "\n";
    file << player.max_health << "\n";
    file << player.attack     << "\n";
    file << player.defense    << "\n";
    file << player.score      << "\n";
    file << player.lives      << "\n";
    file << player.currentScene << "\n";
    file << player.inventory.size() << "\n";
    for (int i = 0; i < (int)player.inventory.size(); i++)
    {
        file << player.inventory[i].name          << "\n";
        file << player.inventory[i].attack_bonus  << "\n";
        file << player.inventory[i].defense_bonus << "\n";
        file << player.inventory[i].health_bonus  << "\n";
    }
    file.close();
    cout << "Game saved successfully!\n";
}

bool LoadGame(Player &player)
{
    ifstream file("savegame.txt");
    if (!file)
    {
        cout << "No saved game found.\n";
        return false;
    }
    getline(file, player.name);
    file >> player.health;
    file >> player.max_health;
    file >> player.attack;
    file >> player.defense;
    file >> player.score;
    file >> player.lives;
    file >> player.currentScene;
    int item_count;
    file >> item_count;
    file.ignore();
    player.inventory.clear();
    for (int i = 0; i < item_count; i++)
    {
        string item_name;
        int atk, def, hp;
        getline(file, item_name);
        file >> atk >> def >> hp;
        file.ignore();
        player.inventory.push_back(Item(item_name, atk, def, hp));
    }
    file.close();
    cout << "Game loaded successfully!\n";
    return true;
}

void AskToSave(Player &player)
{
    cout << "\nWould you like to save your progress?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";
    string input;
    cin >> input;
    if (input == "1")
    {
        SaveGame(player);
    }
}

void PrintGameOver(Player &player)
{
    cout << "\n========================================\n";
    cout << "           *** GAME OVER ***\n";
    cout << "========================================\n";
    cout << "You have no lives remaining, " << player.name << ".\n";
    cout << "The realm falls to darkness...\n";
    cout << "Final Score: " << player.score << "\n";
    cout << "========================================\n";
}

void PrintVictory(Player &player)
{
    player.score += 500;

    cout << "\n========================================\n";
    cout << "         *** YOU WIN! ***\n";
    cout << "========================================\n";
    cout << "You have reached the end of your quest, " << player.name << "!\n";
    cout << "The Shattered Realm is saved.\n";
    cout << "\n--- Final Stats ---\n";
    player.ShowStats();
    player.ShowInventory();

    cout << "\n--- Final Score: " << player.score << " ---\n";
    if (player.score >= 900)
        cout << "Rating: *** LEGENDARY DRAGON SLAYER ***\n";
    else if (player.score >= 600)
        cout << "Rating: ** GOLD CHAMPION **\n";
    else if (player.score >= 300)
        cout << "Rating: * SILVER ADVENTURER *\n";
    else
        cout << "Rating: BRONZE WANDERER\n";

    cout << "========================================\n";
}

bool RunScene(Scene &scene, Player &player)
{
    bool alive = scene.Run(player);
    if (!alive)
    {
        PrintGameOver(player);
        return false;
    }
    cout << "Current Score: " << player.score << "\n";
    AskToSave(player);
    return true;
}

int main()
{
    cout << "                                           ========================================\n";
    cout << "                                                       THE SHATTERED REALM\n";
    cout << "                                           ========================================\n\n";

    cout << "                                               1. New Game\n";
    cout << "                                               2. Load Saved Game\n";
    string menu_input;
    cin >> menu_input;
    cin.ignore();

    Player player("Adventurer");

    if (menu_input == "2")
    {
        bool loaded = LoadGame(player);
        if (!loaded)
        {
            cout << "Starting a new game instead.\n";
            string player_name;
            cout << "Enter your name, adventurer: ";
            getline(cin, player_name);
            if (player_name.empty())
            {
                player_name = "Adventurer";
                cout << "No name entered, you shall be known as Adventurer.\n";
            }
            player = Player(player_name);
        }
        else
        {
            cout << "\nWelcome back, " << player.name << "!\n";
            player.ShowStats();
            player.ShowInventory();
            cout << "\nResuming from scene " << player.currentScene << "...\n";
        }
    }
    else
    {
        string player_name;
        cout << "Enter your name, adventurer: ";
        getline(cin, player_name);

        if (player_name.empty())
        {
            player_name = "Adventurer";
            cout << "No name entered, you shall be known as Adventurer.\n";
        }

        player = Player(player_name);
    }

    cout << "\nWelcome, " << player.name << "! You start with " << player.lives << " lives.\n";
    cout << "Lose all lives and your journey ends.\n";
    player.ShowStats();

    cout << "\n----------------------------------------\n";
    cout << "SCENE: The Crossroads of Aldenmoor\n";
    cout << "----------------------------------------\n";
    cout << "A dying soldier thrusts a cracked map into your\n";
    cout << "hands. 'The Crystal... Malachar must be stopped...'\n";
    cout << "Two paths stretch before you.\n\n";
    cout << "1. Take the forest path east\n";
    cout << "2. Take the cursed road west\n";

    int opening_choice = GetChoice();
    AskToSave(player);

    if (opening_choice == 1)
    {
        player.currentScene = 1;
        {
            cout << "\n----------------------------------------\n";
            cout << "SCENE: The Whispering Forest\n";
            cout << "----------------------------------------\n";
            cout << "Bioluminescent mushrooms light a faint trail.\n";
            cout << "A wounded fox is caught in a trap. A ranger's\n";
            cout << "pack hangs from a nearby branch.\n\n";
            cout << "1. Free the wounded fox\n";
            cout << "2. Grab the ranger's pack\n";

            if (GetChoice() == 1)
            {
                cout << "\nThe grateful fox leads you to a hidden cache.\n";
                player.AddItem(Item("Elvish Boots", 0, 2, 0));
                player.score += 25;
            }
            else
            {
                cout << "\nThe pack contains a knife and dried food!\n";
                player.AddItem(Item("Hunting Knife", 3, 0, 0));
                player.AddItem(Item("Dried Meat",    0, 0, 2));
                player.score += 25;
            }
            cout << "Current Score: " << player.score << "\n";
            AskToSave(player);
        }

        player.currentScene = 2;
        CombatScene scene2A(
            "Goblin Ambush",
            "A goblin scout drops from the trees with a shriek!\n"
            "His beady eyes fix on your pack.",
            "Fight the goblin scout",
            "Flee into the undergrowth",
            "Goblin Scout", 6, 2, 8,
            75, true, Item("Brass Key", 0, 0, 0),
            "You escape but fall -> 2 damage from the fall.",
            2, true, Item("Crude Sword", 2, 0, 0)
        );
        if (!RunScene(scene2A, player)) return 0;

        player.currentScene = 3;
        PuzzleScene scene3A(
            "The Stone Door Riddle",
            "A stone door blocks the path. A carved face speaks:\n"
            "'I have cities but no houses, mountains but no\n"
            "trees, and water but no fish. What am I?'",
            "A Map",
            "A Painting",
            1, 50, 3,
            true, Item("Spectral Cloak", 0, 3, 0)
        );
        if (!RunScene(scene3A, player)) return 0;

        player.currentScene = 4;
        ItemScene scene4A(
            "The Mossy Hollow",
            "A glowing crystal shard rests beside a locked chest.",
            "Take the crystal shard",
            "Force the chest open",
            { "The shard pulses with warm light! +100 score!", false, Item("", 0, 0, 0), 100, 0 },
            { "A trap needle strikes you for 4 damage!", true,  Item("Steel Gauntlets", 0, 4, 0), 0, 4 }
        );
        if (!RunScene(scene4A, player)) return 0;

        player.currentScene = 5;
        CombatScene scene5A(
            "The Darkwood Trail",
            "A large grey wolf steps onto the path, growling\n"
            "low. Its eyes glow amber in the dark.",
            "Draw your weapon and fight",
            "Back away slowly and take a detour",
            "Grey Wolf", 7, 1, 10,
            80, true, Item("Wolf Pelt", 0, 2, 0),
            "The detour is longer, you arrive tired. -2 HP.",
            2
        );
        if (!RunScene(scene5A, player)) return 0;

        player.currentScene = 6;
        ItemScene scene6A(
            "The Abandoned Camp",
            "A deserted campsite. A sword lies in the mud\n"
            "A deserted campsite. A sword lies in the mud\n"
            "and a health potion sits on a rock.",
            "Take the damaged sword",
            "Take the health potion",
            { "The blade is cracked, it will reduce your attack!", true, Item("Damaged Sword", -1, 0, 0), 0, 0 },
            { "The potion restores your strength!", true, Item("Health Potion",  0, 0, 5), 0, 0 }
        );
        if (!RunScene(scene6A, player)) return 0;

        player.currentScene = 7;
        int score_before_7A = player.score;
        CombatScene scene7A(
            "Bandit Ambush",
            "Three bandits step from the trees. Their leader\n"
            "grins: 'Hand over your items or face us all!'",
            "Fight the bandit leader",
            "Throw your coins as a distraction and run",
            "Bandit Leader", 8, 3, 12,
            90, true, Item("Bandit's Shortsword", 3, 0, 0),
            "You escape! But you lose 10 score for the coins.",
            0
        );
        if (!RunScene(scene7A, player)) return 0;
        if (player.score == score_before_7A)
        {
            player.score -= 10;
            if (player.score < 0) player.score = 0;
        }

        player.currentScene = 8;
        PuzzleScene scene8A(
            "The Runed Gate",
            "A glowing gate is sealed with a number. The\n"
            "inscription reads: 'What is 12 x 7 - 4?'",
            "80",
            "100",
            1, 50, 3,
            true, Item("Gate Key Fragment", 0, 0, 0)
        );
        if (!RunScene(scene8A, player)) return 0;
    }

    else
    {
        player.currentScene = 11;

        PuzzleScene scene1B(
            "The Spectral Toll-Keeper",
            "A glowing ghost bars your way.\n"
            "'The more you take, the more you leave behind.\n"
            "What am I?'",
            "Footsteps",
            "Memories",
            1, 50, 3,
            true, Item("Spectral Cloak", 0, 3, 0)
        );
        if (!RunScene(scene1B, player)) return 0;

        player.currentScene = 12;
        ItemScene scene2B(
            "Village of Thornwall",
            "Survivors huddle by a dying fire.\n"
            "The blacksmith offers weapons. The healer needs a guard.",
            "Trade with the blacksmith for an Iron Sword",
            "Guard the healer overnight",
            { "The blacksmith hands you a fine blade!", true,  Item("Iron Sword", 5, 0, 0), 25, 0 },
            { "You guard the healer through the night safely.", true, Item("Healing Potion", 0, 0, 5), 50, 0 }
        );
        if (!RunScene(scene2B, player)) return 0;

        player.currentScene = 13;
        PuzzleScene scene3B(
            "The Will-o-Wisp",
            "A wisp forms glowing letters in the air: D R S W A\n"
            "'Unscramble my name or join the drowned!'",
            "WARDS",
            "DRAWS",
            1, 50, 3,
            true, Item("Swamp Pearl", 0, 2, 0)
        );
        if (!RunScene(scene3B, player)) return 0;

        player.currentScene = 14;
        CombatScene scene4B(
            "The Stone Bridge",
            "A skeletal warrior blocks the bridge, spear raised.",
            "Fight the skeleton",
            "Sneak through the thorny briars beside the bridge",
            "Skeletal Warrior", 7, 4, 10,
            100, true, Item("Steel Shield", 0, 3, 0),
            "Thorns scratch you for 2 damage.",
            2, true, Item("Bandages", 0, 0, 3)
        );
        if (!RunScene(scene4B, player)) return 0;

        player.currentScene = 15;
        CombatScene scene5B(
            "The Ruined Watchtower",
            "A cursed knight in black armour charges at you\n"
            "from the watchtower ruins!",
            "Face him in combat",
            "Collapse the tower entrance to block him",
            "Cursed Knight", 9, 5, 14,
            110, true, Item("Knight's Chestplate", 0, 5, 0),
            "The rubble slows him. You escape, but take 3 HP from debris.",
            3
        );
        if (!RunScene(scene5B, player)) return 0;

        player.currentScene = 16;
        ItemScene scene6B(
            "The Witch's Hut",
            "A cloaked witch offers you a choice from her shelf:\n"
            "a strength elixir or a shield charm.",
            "Take the strength elixir (+4 ATK)",
            "Take the shield charm (+3 DEF)",
            { "Power surges through your arms!", true, Item("Strength Elixir", 4, 0, 0), 25, 0 },
            { "A faint shimmer surrounds you.",  true, Item("Shield Charm",0, 3, 0), 25, 0 }
        );
        if (!RunScene(scene6B, player)) return 0;

        player.currentScene = 17;
        CombatScene scene7B(
            "The Rickety Bridge",
            "A cave troll lumbers across the rope bridge,\n"
            "blocking the only way forward.",
            "Fight the cave troll",
            "Try to swim across the river below",
            "Cave Troll", 10, 3, 18,
            120, true, Item("Troll Club", 4, 0, 0),
            "The river current is brutal -> you take 3 damage.\n"
            "But you spot a dagger wedged in the rocks!",
            3, true, Item("River Dagger", 2, 0, 0)
        );
        if (!RunScene(scene7B, player)) return 0;

        player.currentScene = 18;
        CombatScene scene8B(
            "The Dark Mage's Tower",
            "A dark mage seals the road with a wall of flame.\n"
            "'You shall not pass without defeating me!'",
            "Charge into melee combat",
            "Hurl your weapon at him from range",
            "Dark Mage", 11, 2, 12,
            130, true, Item("Mage Staff", 5, 0, 0),
            "Your thrown weapon strikes the mage -> he staggers!\n"
            "He retaliates with a fire bolt -> 4 damage to you!\n>"
            "The mage flees, wounded.",
            4
        );
        if (!RunScene(scene8B, player)) return 0;
    }

    cout << "\n========================================\n";
    cout << "Both paths converge at the base of\n";
    cout << "Malachar's volcanic mountain. The air\n";
    cout << "burns hot. The final battle awaits.\n";
    cout << "========================================\n";

    player.currentScene = 20;
    PuzzleScene sharedScene1(
        "The Lava Oracle",
        "A stone oracle rises from the lava fields.\n"
        "'Answer me this: the more you use me, the\n"
        "smaller I become. What am I?'",
        "A candle",
        "A shadow",
        1, 60, 3,
        true, Item("Oracle's Blessing", 2, 0, 0)
    );
    if (!RunScene(sharedScene1, player)) return 0;

    player.currentScene = 21;
    CombatScene sharedScene2(
        "The Gargoyle's Perch",
        "A stone gargoyle drops from the cliff above,\n"
        "landing with a crash that shakes the ground.",
        "Fight the gargoyle",
        "Dive behind a boulder for cover",
        "Stone Gargoyle", 9, 4, 14,
        100, true, Item("Gargoyle Claw", 3, 0, 0),
        "You hide safely but lava spatters you -> 3 damage.",
        3
    );if (!RunScene(sharedScene2, player)) return 0;

    player.currentScene = 22;
    ItemScene sharedScene3(
        "The Merchant at the Gates",
        "A shady merchant sits beside the volcano path.\n"
        "He offers two things -> you can only take one.",
        "Buy a strength potion (+3 ATK)",
        "Rest by his fire and recover 5 HP",
        { "The potion surges through you -> power!", true, Item("Strength Potion", 3, 0, 0), 25, 0 },
        { "You rest and feel restored.",false, Item("", 0, 0, 0), 0, -5 }
    );
    if (!RunScene(sharedScene3, player)) return 0;

player.currentScene = 23;
    PuzzleScene sharedScene4(
        "The Ancient Inscription",
        "Carved into the volcano wall is an anagram.\n"
        "Unscramble it to reveal the safe path:\n"
        "AGLME",
        "FLAME",
        "GLEAM",
        1, 60, 4,
        true, Item("Path Marker", 0, 0, 3)
    );
    if (!RunScene(sharedScene4, player)) return 0;

    player.currentScene = 24;
    CombatScene sharedScene5(
        "The Fire Elemental",
        "A roaring fire elemental blocks the tunnel\n"
        "entrance, hurling fireballs at everything.",
        "Fight the fire elemental",
        "Sprint through the smoke on the left side",
        "Fire Elemental", 11, 3, 16,
        140, true, Item("Ember Shield", 0, 4, 0),
        "You sprint through but breathe in smoke -> 4 damage.",
        4
    );
    if (!RunScene(sharedScene5, player)) return 0;

 player.currentScene = 25;
    ItemScene sharedScene6(
        "The Fallen Warrior",
        "A slain warrior lies beside the path. Two items\n"
        "rest beside her, a blade and a healing vial.",
        "Take the warrior's blade (+5 ATK)",
        "Drink the healing vial (+8 HP)",
        { "The blade hums with ancient power!", true, Item("Warrior's Blade", 5, 0, 0), 25, 0 },
        { "Warmth spreads through your wounds.", true, Item("Healing Vial",   0, 0, 8), 25, 0 }
    );
    if (!RunScene(sharedScene6, player)) return 0;

    player.currentScene = 26;
    PuzzleScene sharedScene7(
        "The Sealed Chamber",
        "The chamber door has a number lock.\n"
        "Inscribed above it: 'What is the square\n"
        "root of 144?'",
        "12",
        "14",
        1, 60, 4,
        true, Item("Chamber Key", 0, 0, 0)
    );
    if (!RunScene(sharedScene7, player)) return 0;
 player.currentScene = 27;
    CombatScene sharedScene8(
        "The Lava Serpent",
        "A massive serpent erupts from the magma pool,\n"
        "coiling around the only path forward!",
        "Fight the lava serpent",
        "Push a boulder onto it from above",
        "Lava Serpent", 12, 4, 20,
        150, true, Item("Serpent Scale Armour", 0, 6, 0),
        "The boulder slows it, but the tremor shakes\n"
        "the floor and you take 2 damage.",
        2
    );
    if (!RunScene(sharedScene8, player)) return 0;

    player.currentScene = 28;
    CombatScene sharedScene9(
        "The Throne Room Gates",
        "Two of Malachar's elite dragon guards block\n"
        "the final door, armour glowing red with heat.",
        "Fight the dragon guard",
        "Bluff your way in as a servant of Malachar",
        "Dragon Guard", 12, 5, 18,
        160, true, Item("Dragon Guard Helmet", 0, 4, 0),
        "Your bluff partially works, but one guard\n"
        "catches on and strikes you for 5 damage.",
        5
    );
    if (!RunScene(sharedScene9, player)) return 0;

    player.currentScene = 29;
    ItemScene sharedScene10(
        "Malachar's Antechamber",
        "You stand before the final door. Two choices\n"
        "remain ->  prepare your body or your mind.",
        "Study Malachar's weak point (+3 ATK for this fight)",
        "Rest and recover all HP",
        { "You spot a crack in his scales. +3 ATK!", true, Item("Battle Focus", 3, 0, 0), 25, 0 },
        { "You rest fully and feel ready.",false, Item("", 0, 0, 0), 25, 0 }
    );
    if (!RunScene(sharedScene10, player)) return 0;

    if (player.health < player.max_health)
    {
        player.health = player.max_health;
    }

    player.currentScene = 30;
    CombatScene finalBoss(
        "Malachar the Dragon",
        "The chamber glows red hot. Malachar uncoils\n"
        "from his throne, eyes like twin furnaces.\n"
        "'Another mortal comes to die,' he rumbles.\n"
        "The Crystal of Ages pulses on the dais.",
        "Charge at Malachar with everything you have!",
        "Circle and wait for an opening",
        "Malachar the Dragon", 14, 6, 30,
        500, false, Item("", 0, 0, 0),
        "You circle carefully, but his tail sweeps\n"
        "you across the chamber for 6 damage.",
        6
    );
    if (!RunScene(finalBoss, player)) return 0;

    PrintVictory(player);
    return 0;
}

