#ifndef SIMPLEMUDMODIFIED_GAMECONTROLLER_H
#define SIMPLEMUDMODIFIED_GAMECONTROLLER_H

#include "TextParser.h"
#include "iostream"
#include<fstream>
#include<string>
#include "cstdlib"

class GameController {
public:
    GameController() = default;

    void RunGame();

private:
    // Display Information or Menu
    void showStartMenu();

    static void showCombatMenu();

    static void showSkillMenu(const Player& player);

    static void showItemMenu(Player player);

    static void showEscape();

    static void showPlayerHurt(Player& player, int damage);

    static void showEnemyHurt(Enemy& enemy, int damage);

    static void showEnemyAttack(const Enemy& enemy);

    static void showChoiceError();

    static void showItemDrop(const Enemy& enemy);

    static void showNormalDiscoverMenu();

    static void showPlayerState(const Player& player);

    static void displayLogo(const std::string filename);// Display Logo

    static void displayMap(const std::string filename);

    static void displayAllData();

    // Turn-based Combat System
    static bool PlayerTurn(Player& player, Enemy& enemy);

    static void EnemyTurn(Player& player, Enemy& enemy);

    void Combat(Player& player);

    //
    void Discover(Player& player);

    static void Interactive(Player& player);

    // Archive-about Operation
    static Player initializeArchive();

    static Player loadArchive(const std::string& filename);

    static void loadAllData();

    // Used for Test
    void Test();
};

#endif //SIMPLEMUDMODIFIED_GAMECONTROLLER_H