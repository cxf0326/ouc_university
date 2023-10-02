// 定义颜色宏
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#include "GameController.h"

Player current_player{};
std::vector<std::string> scripts_list;
std::vector<Spot> spots_list;
std::vector<Enemy> enemies_list;
std::vector<Item> item_list;
std::vector<Npc> npcs_list;
std::vector<Quest> quests_list;
Enemy questEnemy;

void saveArchive(const std::string& filename, const Player& player) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "#" << player.getID() << std::endl;
        file << player.getName() << std::endl;
        file << player.getHealth() << std::endl;
        file << player.getDefensive() << std::endl;
        file << player.getWisdom() << std::endl;
        file << player.getStrength() << std::endl;
        file << player.getEXP() << std::endl;
        file << player.getLevel() << std::endl;
        file << player.getCurSpotID() << std::endl;
        file << player.getQuestID() << std::endl;
        file << player.getProgress() << std::endl;
        file << player.getCriticalRate() << std::endl;
        file << player.getCriticalPower() << std::endl;
        file << player.getAgility() << std::endl;
        for (int i = 0; i < player.getItemList().size(); ++i) {
            file << player.getItemList().at(i).getID() << ' ' << player.getItemList().at(i).getNumber() << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件." << filename << std::endl;
    }
}

Player GameController::loadArchive(const std::string& filename) {
    Player player;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            std::istringstream idIss(line.substr(1));
            int id;
            if (idIss >> id) {
                player.setID(id);
            }
        }
        if (std::getline(file, line)) {
            player.setName(line);
        }
        if (std::getline(file, line)) {
            int health = std::stoi(line);
            player.setHealth(health);
        }
        if (std::getline(file, line)) {
            int defensive = std::stoi(line);
            player.setDefensive(defensive);
        }
        if (std::getline(file, line)) {
            int wisdom = std::stoi(line);
            player.setWisdom(wisdom);
        }
        if (std::getline(file, line)) {
            int strength = std::stoi(line);
            player.setStrength(strength);
        }
        if (std::getline(file, line)) {
            int exp = std::stoi(line);
            player.setEXP(exp);
        }
        if (std::getline(file, line)) {
            int level = std::stoi(line);
            player.setLevel(level);
        }
        if (std::getline(file, line)) {
            int spotID = std::stoi(line);
            player.setSpotID(spotID);
        }
        if (std::getline(file, line)) {
            int questID = std::stoi(line);
            player.setQuestID(questID);
        }
        if (std::getline(file, line)) {
            int progress = std::stoi(line);
            player.setProgress(progress);
        }
        if (std::getline(file, line)) {
            float criticalRate = std::stof(line);
            player.setCriticalRate(criticalRate);
        }
        if (std::getline(file, line)) {
            float criticalPower = std::stof(line);
            player.setCriticalPower(criticalPower);
        }
        if (std::getline(file, line)) {
            float agility = std::stof(line);
            player.setAgility(agility);
        }
        player.setItemList(std::vector<Item>());
        while (std::getline(file, line) && !line.empty()) {
            std::istringstream itemIss(line);
            int itemID, itemNumber;
            if (itemIss >> itemID >> itemNumber) {
                player.getItemList().push_back(item_list.at(itemID));
                player.getItemList().back().setNumber(itemNumber);
            }
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件" << filename << std::endl;
    }
    return player;
}


// 显示战斗菜单，包括攻击、技能和逃跑选项
void GameController::showCombatMenu() {
    std::cout << "选择选项来应对当前敌人" << std::endl;
    std::cout << "1.普通攻击" << std::endl;
    std::cout << "2.使用技能" << std::endl;
    std::cout << "3.使用物品" << std::endl;
    std::cout << "4.逃离战斗" << std::endl;
}

// 根据玩家角色显示技能菜单，列出可用的技能和对应的伤害
void GameController::showSkillMenu(const Player& player) {
    std::cout << "请选择一个技能，你目前拥有" << player.getCurWisdom()
        << "法力值。" << std::endl;
    for (int i = 1; i <= player.getSkillList().size(); ++i) {
        std::cout << i << ". " << player.getSkillList().at(i - 1).skill_name << ", 伤害: "
            << player.getSkillList().at(i - 1).skill_power << ", 法力消耗: "
            << player.getSkillList().at(i - 1).wisdom_need << std::endl;
    }
}

// 显示玩家拥有的物品菜单，包括物品名称和描述
void GameController::showItemMenu(Player player) {
    if (player.getItemList().size() != 0) {
        std::cout << "这些是你的所有物品:" << std::endl;
        for (int i = 1; i <= player.getItemList().size(); ++i) {
            std::cout << i << ". " << player.getItemList().at(i - 1).getName() << ", 数量: "
                << player.getItemList().at(i - 1).getNumber() << std::endl;
        }
    }
    else {
        std::cout
            << "目前你手上没有任何物品，你可以通过击杀怪物或者完成任务获得物品."
            << std::endl;
    }
}

// 显示逃离战斗的提示信息
void GameController::showEscape() {
    std::cout << "你逃离了这场战斗." << std::endl;
}

// 显示玩家受到伤害的信息，包括玩家姓名、受到的伤害和当前剩余生命值
void GameController::showPlayerHurt(Player& player, int damage) {
    std::cout << player.getName() << " 受到了 " << damage << " 伤害. ";
    if (player.getHealth() > 0) {
        std::cout << player.getName() << " 的生命值现在是 " << player.getHealth() << std::endl;
    }
    else {
        std::cout << player.getName() << " 在这场战斗中死亡了." << std::endl;
    }
}

// 显示敌人受到伤害的信息，包括敌人姓名、受到的伤害和当前剩余生命值
void GameController::showEnemyHurt(Enemy& enemy, int damage) {
    std::cout << enemy.getName() << " 受到 " << damage << " 伤害. ";
    if (enemy.getHealth() > 0) {
        std::cout << enemy.getName() << " 的生命值现在是 " << enemy.getHealth() << std::endl;
    }
    else {
        std::cout << " 恭喜你赢得了本场战斗！ " << std::endl;
    }
}

// 显示敌人攻击玩家的提示信息
void GameController::showEnemyAttack(const Enemy& enemy) {
    std::cout << enemy.getName() << " 攻击了你. " << std::endl;
}

// 显示选择错误的提示信息
void GameController::showChoiceError() {
    std::cout << " 你选择了错误的选项，请再试一次. " << std::endl;
}

// 显示敌人掉落物品的提示信息
void GameController::showItemDrop(const Enemy& enemy) {
    std::cout << enemy.getName() << " 掉落了 " << item_list.at(enemy.getDropItemID()).getName() << std::endl;
}

// 显示普通探索菜单，包括查看周围环境、查看背包、查看玩家状态、战斗、前往下一个房间和保存并退出选项
void GameController::showNormalDiscoverMenu() {
    std::cout<<YELLOW << " 选择一项行动 " << std::endl;
    std::cout
        << "1.查看四周\t2.检视背包\t3.检视状态\t4.寻求战斗\t5.打开地图\t6.保存退出"
        << std::endl;
}

// 显示玩家的状态信息，包括生命值、力量、智慧、暴击率、暴击伤害、敏捷度和级别
void GameController::showPlayerState(const Player& player) {
    std::cout <<CYAN<< player.getName() << " 的状态如下：" << std::endl << "生命：" << player.getHealth() << std::endl
        << "攻击: " << player.getStrength() << std::endl << "法力: " << player.getWisdom() << std::endl
        << "防御：" << player.getDefensive() << std::endl << "暴击率: " << player.getCriticalRate()
        << std::endl << "暴击倍率: " << player.getCriticalPower() << std::endl << "敏捷: "
        << player.getAgility() << std::endl << "等级: " << player.getLevel() << std::endl;
}

// 玩家回合，处理玩家在战斗中的选择，并更新敌人的生命值
bool GameController::PlayerTurn(Player& player, Enemy& enemy) {
    int choice;
    bool retry = false;
    do {
        showCombatMenu();
        std::cin >> choice;
        switch (choice) {
        case 1: {
            showEnemyHurt(enemy, Enemy::getHit(player, enemy));
            break;
        }
        case 2: {
            int skill_choice;
            showSkillMenu(player);
            std::cin >> skill_choice;
            if (skill_choice > player.getSkillList().size()) {
                showChoiceError();

                retry = true;
                continue;
            }
            else if (player.getSkillList().at(skill_choice - 1).wisdom_need <= player.getCurWisdom()) {
                player.setCurWisdom(player.getCurWisdom() -player.getSkillList().at(skill_choice - 1).wisdom_need);
                showEnemyHurt(enemy, Enemy::getSkillHit(player, enemy, skill_choice));
            }
            else {
                std::cout << "没有足够的法力来施法，请再试一次. " << std::endl;
                retry = true;
                continue;
            }
            break;
        }
        case 3: {
            int item_choice;
            showItemMenu(player);
            std::cin >> item_choice;
            if (item_choice > player.getItemList().size()) {
                showChoiceError();
                retry = true;
                continue;
            }
            else {
                player.getItemList().at(item_choice - 1).useItem(player);
                player.rmItem(player.getItemList().at(item_choice - 1));
            }
            break;
        }
        case 4: {
            showEscape();
            return true;
        }
        default: {
            showChoiceError();
            continue;
        }
        }
        break;
    } while (retry);
    return false;
}

// 敌人回合，敌人攻击玩家，并更新玩家的生命值
void GameController::EnemyTurn(Player& player, Enemy& enemy) {
    showEnemyAttack(enemy);
    showPlayerHurt(player, Player::getHit(player, enemy));
}

// 战斗过程，循环执行玩家和敌人的回合，直到一方生命值为0
void GameController::Combat(Player& player) {
    int cur_Enemies_numbers = spots_list.at(player.getCurSpotID()).getEnemyNumber();
    if (cur_Enemies_numbers == 0) {
        std::cout << "这里没有可以攻击的敌人." << std::endl;
    }
    else {
        std::cout << "这里共有 " << cur_Enemies_numbers << " 种敌人." << std::endl;
        std::cout << "选择一个开始攻击." << std::endl;
        int enemy_choice = -1;
        for (int i = 0; i < cur_Enemies_numbers; ++i) {
            std::cout << i + 1 << ". "
                << enemies_list.at(spots_list.at(player.getCurSpotID()).getEnemies().at(i)).getName() << "\t";
        }
        std::cin >> enemy_choice;
        Enemy enemy = enemies_list.at(spots_list.at(player.getCurSpotID()).getEnemies().at(enemy_choice - 1));
        while (player.getHealth() > 0 && enemy.getHealth() > 0) {
            if (PlayerTurn(player, enemy)) {
                return;
            }
            if (enemy.getHealth() <= 0) {
                if (questEnemy.getID() == enemy.getID()) {
                    player.addProgress(1);
                }
                player.setEXP(enemy.getEXP());
                player.levelUp(player);
                showItemDrop(enemy);
                player.addItem(item_list.at(enemy.getDropItemID()), enemy.getDropItemNum());
                break;
            }
            EnemyTurn(player, enemy);
            if (player.getHealth() <= 0) {
                break;
            }
        }
    }

}

void Spot::viewAround(int id) const {
    std::cout << getDescription() << std::endl;
}

// 探索过程，根据玩家在当前位置的选择执行相应的操作，包括查看周围环境、查看物品、查看状态、战斗、前往下一个房间和保存退出
void GameController::Discover(Player& player) {
    Spot previousSpot = spots_list.at(player.getCurSpotID());
    while (true) {
        int choice;
        system("pause");
        system("cls");
        showNormalDiscoverMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << CYAN;
            spots_list.at(player.getCurSpotID()).viewAround(0);
            Interactive(player);
            break;
        case 2:
            std::cout << BLUE;
            showItemMenu(player);
            break;
        case 3:
            std::cout << GREEN;
            showPlayerState(player);
            break;
        case 4:
            std::cout << RED;
            Combat(player);
            break;
        case 5:
            std::cout << YELLOW;
            displayMap("data/map.dat");
            int destination_choice;
            for (int i = 0; i < spots_list.at(player.getCurSpotID()).getExitNumber(); ++i) {
                std::cout << i + 1 << "."
                    << spots_list.at(spots_list.at(player.getCurSpotID()).getExits().at(i)).getName() << "\t";
            }
            std::cout<<RED<< std::endl << "选择一个目的地:"<<YELLOW;
            std::cin >> destination_choice;
            player.setSpotID(spots_list.at(player.getCurSpotID()).getExits().at(destination_choice - 1));
            break;
        case 6:
            saveArchive("data/archive.dat", player);
            exit(0);
            // used for test
        case 233:
            displayAllData();
            return;
        default:
            showChoiceError();
            continue;
        }
    }
}

void GameController::Interactive(Player& player) {
    int cur_Npc_numbers = spots_list.at(player.getCurSpotID()).getNpcNumber();
    if (cur_Npc_numbers == 0) {
        std::cout << "这里没有可以交互的NPC." << std::endl;
    }
    else {
        std::cout << "这里有 " << cur_Npc_numbers << " 个NPC." << std::endl;
        std::cout << "选择一个NPC来接收任务." << std::endl;
        int npc_choice = -1;
        for (int i = 0; i < cur_Npc_numbers; ++i) {
            std::cout << i + 1 << ". "
                << npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(i)).getName() << "\t";
        }
        std::cin >> npc_choice;
        Npc npc = npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(npc_choice - 1));
        if (player.getQuestID() == -1) {
            if (quests_list.at(npc.getQuestID()).getQuestDone()) {
                std::cout << "你已经完成过这个任务." << std::endl;
                return;
            }
            quests_list.at(npc.getQuestID()).start(player);
        }
        else if (player.getQuestID() == npc.getQuestID()) {
            quests_list.at(npc.getQuestID()).check(player);
        }
        else {
            std::cout << "你已经有一个未完成的任务了，请完成上一个任务在接取当前任务." << std::endl;
            return;
        }
    }
}

void GameController::displayAllData() {
    for (const auto& spot : spots_list) {
        std::cout << "ID: " << spot.getID() << std::endl;
        std::cout << "名称: " << spot.getName() << std::endl;
        std::cout << "描述: " << spot.getDescription() << std::endl;
        std::cout << "出口数量: " << spot.getExitNumber() << std::endl;
        std::cout << "出口列表: ";
        const auto& exits = spot.getExits();
        for (const auto& exit : exits) {
            std::cout << exit << " ";
        }
        std::cout << std::endl;
        std::cout << "NPC数量: " << spot.getNpcNumber() << std::endl;
        std::cout << "NPC列表: ";
        const auto& npcs = spot.getNpcs();
        for (const auto& npc : npcs) {
            std::cout << npc << " ";
        }
        std::cout << std::endl;
        std::cout << "Script列表: ";
        const auto& scripts = spot.getScripts();
        for (const auto& script : scripts) {
            std::cout << script << " ";
        }
        std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    for (const auto& enemy : enemies_list) {
        std::cout << "ID: " << enemy.getID() << std::endl;
        std::cout << "名称: " << enemy.getName() << std::endl;
        std::cout << "描述: " << enemy.getDescription() << std::endl;
        std::cout << "生命值: " << enemy.getHealth() << std::endl;
        std::cout << "防御值: " << enemy.getDefensive() << std::endl;
        std::cout << "攻击力: " << enemy.getStrength() << std::endl;
        std::cout << "exp: " << enemy.getEXP() << std::endl;
        std::cout << "物品: " << enemy.getDropItemID() << std::endl;
        std::cout << "技能: " << enemy.getSkillID() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void GameController::displayLogo(const std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr << "无法打开文件！" << std::endl;
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << "\033[33m" << line << std::endl;
        }
    }
    file.close();
}

void GameController::showStartMenu() {
    displayLogo("data/logo.dat");
    std::cout << "\033[0;32;31m" << "1、初入学院\t2、继续旅途\t3、结束旅途" << std::endl;
    int choice = -1;
    std::cin >> choice;
    while (true) {
        switch (choice) {
        case 1:
            current_player = initializeArchive();
            showPlayerState(current_player);
            //system("pause");
            //system("cls");
            //std::system("clear");
            Discover(current_player);
            break;
        case 2:
            current_player = loadArchive("data/archive.dat");
            showPlayerState(current_player);
            Discover(current_player);
            break;
        case 3:
            exit(0);
        default:
            showChoiceError();
            continue;
        }
    }
}

void GameController::displayMap(const std::string filename) {
    std::cout <<RED<< "你现在正在 " << spots_list.at(current_player.getCurSpotID()).getName() <<YELLOW<< std::endl;
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr << "无法打开文件！" << std::endl;
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }
    file.close();
}

Player GameController::initializeArchive() {
    Player default_player("Harry Potter", 50, 0, 5, 100, 0.05f, 0.1f, 0.1f, 0);
    std::cout << scripts_list.at(0) << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 4);
    int randomNum = dis(gen);
    std::cout << scripts_list.at(randomNum) << std::endl;
    switch (randomNum) {
    case 1:
        default_player.addHealth(10);
        break;
    case 2:
        default_player.addDefensive(10);
        break;
    case 3:
        default_player.addWisdom(10);
        break;
    case 4:
        default_player.addStrength(10);
        break;
    }
    default_player.addItem(item_list.at(0), 5);
    return default_player;
}

void GameController::loadAllData() {
    TextParser textParser;
    spots_list = textParser.loadSpotDat("data/spots.dat");
    scripts_list = textParser.loadScriptDat("data/scripts.dat");
    enemies_list = textParser.loadEnemiesDat("data/enemies.dat");
    item_list = textParser.loadItemDat("data/items.dat");
    npcs_list = textParser.loadNpcDat("data/npcs.dat");
    quests_list = textParser.loadQuestDat("data/quest.dat");
}

void GameController::RunGame() {
    loadAllData();
    showStartMenu();
}

void Quest::start(Player& player) {
    player.setQuestID(getID());
    player.setProgress(0);
    questEnemy = enemies_list.at(getEnemyID());
    std::cout << getDescription0() << std::endl;
}

void Quest::check(Player& player) {
    if (player.getProgress() >= quests_list.at(player.getQuestID()).getEnemyNumber()) {
        std::cout << getDescription1() << std::endl;
        player.addItem(item_list.at(getItemID()), 1);
        setQuestDone(true);
        player.setQuestID(-1);
        player.setProgress(0);
    }
    else {
        std::cout << "任务未完成！" << std::endl;
    }
}