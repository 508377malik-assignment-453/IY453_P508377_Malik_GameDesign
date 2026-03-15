#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <string>
#include <functional>
#include "Player.h"
using namespace std;

class Scene
{
public:
    string title;
    string description;
    string option1;
    string option2;

    Scene(string title, string description, string opt1, string opt2);

    virtual ~Scene() {}

    virtual bool Run(Player &player) = 0;

protected:
    void PrintScene() const;
};


class ItemScene : public Scene
{
public:

    struct Outcome
    {
        string  message;
        bool    hasItem;
        Item    item;
        int     scoreDelta;
        int     hpPenalty;
    };

    Outcome outcome1;
    Outcome outcome2;

    ItemScene(string title, string description,
              string opt1, string opt2,
              Outcome o1, Outcome o2);

    bool Run(Player &player) override;
};


class PuzzleScene : public Scene
{
public:
    int    correctOption;
    int    scoreReward;
    int    hpPenalty;
    bool   hasItem;
    Item   rewardItem;

    PuzzleScene(string title, string description,
                string opt1, string opt2,
                int correctOption, int scoreReward, int hpPenalty,
                bool hasItem = false,
                Item rewardItem = Item("", 0, 0, 0));

    bool Run(Player &player) override;
};


class CombatScene : public Scene
{
public:
    string enemyName;
    int    enemyAttack;
    int    enemyDefense;
    int    enemyHealth;
    int    scoreReward;
    bool   hasWinItem;
    Item   winItem;


    string avoidMessage;
    int    avoidHpLoss;
    bool   hasAvoidItem;
    Item   avoidItem;

    CombatScene(string title, string description,
                string fightOption, string avoidOption,
                string enemyName, int enemyAtk, int enemyDef, int enemyHp,
                int scoreReward, bool hasWinItem, Item winItem,
                string avoidMessage, int avoidHpLoss,
                bool hasAvoidItem = false,
                Item avoidItem = Item("", 0, 0, 0));


    bool Run(Player &player) override;

private:
    bool RunCombat(Player &player);

    int  RandomNumber(int min, int max);
};

#endif
