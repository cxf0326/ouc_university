#include "GameController.h"

// 定义颜色宏
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

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

//void saveArchive(const std::string filename, const Player& player) {
//    std::ofstream file(filename);
//    if (file.is_open()) {
//        file << "#" << player.getID() << std::endl;
//        file << player.getHealth() << std::endl;
//        file << player.getDefensive() << std::endl;
//        file << player.getWisdom() << std::endl;
//        file << player.getStrength() << std::endl;
//        file << player.getEXP() << std::endl;
//        file << player.getLevel() << std::endl;
//        file << player.getCurSpotID() << std::endl;
//        file << player.getQuestID() << std::endl;
//        file << player.getProgress() << std::endl;
//        for (int i = 0; i < player.getItemList().size(); ++i) {
//            file << player.getItemList().at(i).getID() << ' ' << player.getItemList().at(i).getNumber() << std::endl;
//        }
//        file << std::endl;
//        file.close();
//    }
//    else {
//        std::cout <<RED<< "无法打开文件：" << filename << std::endl;
//    }
//}
//
//Player GameController::loadArchive(const std::string filename) {
//    Player player;
//    std::ifstream file(filename);
//    if (file.is_open()) {
//        std::string line;
//        if (std::getline(file, line)) {
//            std::istringstream idIss(line.substr(1));
//            int id;
//            if (idIss >> id) {
//                player.setID(id);
//            }
//        }
//        if (std::getline(file, line)) {
//            int health = std::stoi(line);
//            player.setHealth(health);
//        }
//        if (std::getline(file, line)) {
//            int defensive = std::stoi(line);
//            player.setDefensive(defensive);
//        }
//        if (std::getline(file, line)) {
//            int wisdom = std::stoi(line);
//            player.setWisdom(wisdom);
//        }
//        if (std::getline(file, line)) {
//            int strength = std::stoi(line);
//            player.setStrength(strength);
//        }
//        if (std::getline(file, line)) {
//            int exp = std::stoi(line);
//            player.setEXP(exp);
//        }
//        if (std::getline(file, line)) {
//            int level = std::stoi(line);
//            player.setLevel(level);
//        }
//        if (std::getline(file, line)) {
//            int spotID = std::stoi(line);
//            player.setSpotID(spotID);
//        }
//        if (std::getline(file, line)) {
//            int questID = std::stoi(line);
//            player.setQuestID(questID);
//        }
//        if (std::getline(file, line)) {
//            int progress = std::stoi(line);
//            player.setProgress(progress);
//        }
//        while (std::getline(file, line) && !line.empty()) {
//            std::istringstream itemIss(line);
//            int itemID, itemNumber;
//            if (itemIss >> itemID >> itemNumber) {
//                player.getItemList().push_back(item_list.at(itemID));
//                player.getItemList().at(itemID).setNumber(itemNumber);
//
//            }
//        }
//        file.close();
//    }
//    else {
//        std::cout <<RED<< "无法打开文件：" << filename << std::endl;
//    }
//    return player;
//}


// 鏄剧ず鎴樻枟鑿滃崟锛屽寘鎷敾鍑汇�佹妧鑳藉拰閫冭窇閫夐」
void GameController::showCombatMenu() {
    std::cout << "选择攻击的方式或者逃跑：" << std::endl;
    std::cout << "1. 普通攻击" << std::endl;
    std::cout << "2. 使用技能" << std::endl;
    std::cout << "3. 使用道具" << std::endl;
    std::cout << "4. 逃跑" << std::endl;
}

// 鏍规嵁鐜╁瑙掕壊鏄剧ず鎶�鑳借彍鍗曪紝鍒楀嚭鍙敤鐨勬妧鑳藉拰瀵瑰簲鐨勪激瀹?
void GameController::showSkillMenu(const Player& player) {
    std::cout << "选择一个技能进行攻击，你现在有" << player.getCurWisdom()
        << "点法力值。" << std::endl;
    for (int i = 1; i <= player.getSkillList().size(); ++i) {
        std::cout << i << ". " << player.getSkillList().at(i - 1).skill_name << ", 伤害值： "
            << player.getSkillList().at(i - 1).skill_power << "，法力值： "
            << player.getSkillList().at(i - 1).wisdom_need << std::endl;
    }
}

// 鏄剧ず鐜╁鎷ユ湁鐨勭墿鍝佽彍鍗曪紝鍖呮嫭鐗╁搧鍚嶇О鍜屾弿杩?
void GameController::showItemMenu(Player player) {
    if (player.getItemList().size() != 0) {
        std::cout << "这是你所有的物品：" << std::endl;
        for (int i = 1; i <= player.getItemList().size(); ++i) {
            std::cout << i << ". " << player.getItemList().at(i - 1).getName() << "，简介： "
                << player.getItemList().at(i - 1).getDescription() << "数量： "
                << player.getItemList().at(i - 1).getNumber() << std::endl;
        }
    }
    else {
        std::cout
            << "到目前为止，你手上什么也没有。你可以从击败敌人或商人中获得一些有用的物品。"
            << std::endl;
    }
}

// 鏄剧ず閫冪鎴樻枟鐨勬彁绀轰俊鎭?
void GameController::showEscape() {
    std::cout << "你从战斗中逃走。。。。。。" << std::endl;
}

// 鏄剧ず鐜╁鍙楀埌浼ゅ鐨勪俊鎭紝鍖呮嫭鐜╁濮撳悕銆佸彈鍒扮殑浼ゅ鍜屽綋鍓嶅墿浣欑敓鍛藉�?
void GameController::showPlayerHurt(Player& player, int damage) {
    std::cout << player.getName() << " 受到 " << damage << " 点伤害 ";
    if (player.getHealth() > 0) {
        std::cout << player.getName() << "的生命值为 " << player.getHealth() << std::endl;
    }
    else {
        std::cout << player.getName() << "于战斗中死亡。" << std::endl;
    }
}

// 鏄剧ず鏁屼汉鍙楀埌浼ゅ鐨勪俊鎭紝鍖呮嫭鏁屼汉濮撳悕銆佸彈鍒扮殑浼ゅ鍜屽綋鍓嶅墿浣欑敓鍛藉�?
void GameController::showEnemyHurt(Enemy& enemy, int damage) {
    std::cout << enemy.getName() << " 受到 " << damage << " 点伤害。 ";
    if (enemy.getHealth() > 0) {
        std::cout << enemy.getName() << "的生命值为： " << enemy.getHealth()  << std::endl;
    }
    else {
        std::cout << "恭喜你击败了敌人！" << std::endl;
    }
}

// 鏄剧ず鏁屼汉鏀诲嚮鐜╁鐨勬彁绀轰俊鎭?
void GameController::showEnemyAttack(Enemy enemy) {
    std::cout << enemy.getName() << "攻击了你。" << std::endl;
}

// 鏄剧ず閫夋嫨閿欒鐨勬彁绀轰俊鎭?
void GameController::showChoiceError() {
    std::cout << "你选择的序号不合法，请重新选择。" << std::endl;
}

// 鏄剧ず鏁屼汉鎺夎惤鐗╁搧鐨勬彁绀轰俊鎭?
void GameController::showItemDrop(Enemy enemy) {
    std::cout << enemy.getName() << " 掉落了一个 " << item_list.at(enemy.getDropItemID()).getName() << std::endl;
}

// 鏄剧ず鏅�氭帰绱㈣彍鍗曪紝鍖呮嫭鏌ョ湅鍛ㄥ洿鐜銆佹煡鐪嬭儗鍖呫�佹煡鐪嬬帺瀹剁姸鎬併�佹垬鏂椼�佸墠寰�涓嬩竴涓埧闂村拰淇濆瓨骞堕��鍑洪�夐」
void GameController::showNormalDiscoverMenu() {
    std::cout <<YELLOW<< "选择你接下来的行动：" << std::endl;
    std::cout
        <<YELLOW
        << "1.环顾四周\t2.查看背包\t3.查看状态\t4.战斗\t5.前往下一个地点\t6.保存并退出"
        << std::endl;
}

// 鏄剧ず鐜╁鐨勭姸鎬佷俊鎭紝鍖呮嫭鐢熷懡鍊笺�佸姏閲忋�佹櫤鎱с�佹毚鍑荤巼銆佹毚鍑讳激瀹炽�佹晱鎹峰害鍜岀骇鍒?
void GameController::showPlayerState(Player player) {
    std::cout << player.getName() << "的状态如下：" << std::endl << "生命值： " << player.getHealth() << std::endl
        << "攻击力：" << player.getStrength() << std::endl << "法力值： " << player.getWisdom() << std::endl
        << "暴击率： " << player.getCriticalRate() << std::endl << "暴击伤害： "
        << player.getCriticalPower() << std::endl << "闪避值： " << player.getAgility() << std::endl << "等级： "
        << player.getLevel() << std::endl;
}

// 鐜╁鍥炲悎锛屽鐞嗙帺瀹跺湪鎴樻枟涓殑閫夋嫨锛屽苟鏇存柊鏁屼汉鐨勭敓鍛藉�?
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
                player.setCurWisdom(-player.getSkillList().at(skill_choice - 1).wisdom_need);
                showEnemyHurt(enemy, Enemy::getSkillHit(player, enemy, skill_choice));
            }
            else {
                std::cout << "法力值不足！" << std::endl;
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

// 鏁屼汉鍥炲悎锛屾晫浜烘敾鍑荤帺瀹讹紝骞舵洿鏂扮帺瀹剁殑鐢熷懡鍊?
void GameController::EnemyTurn(Player& player, Enemy& enemy) {
    showEnemyAttack(enemy);
    showPlayerHurt(player, Player::getHit(player, enemy));
}

// 鎴樻枟杩囩▼锛屽惊鐜墽琛岀帺瀹跺拰鏁屼汉鐨勫洖鍚堬紝鐩村埌涓�鏂圭敓鍛藉�间负0
void GameController::Combat(Player& player) {
    int cur_Enemies_numbers = spots_list.at(player.getCurSpotID()).getEnemyNumber();
    if (cur_Enemies_numbers == 0) {
        std::cout << "附近没有敌人。" << std::endl;
    }
    else {
        std::cout << "这里有 " << cur_Enemies_numbers << " 个敌人。" << std::endl;
        std::cout << "请选择其中一个进行攻击：" << std::endl;
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
                if (questEnemy.getName() == enemy.getName()) {
                    player.addProgress(1);
                }
                player.setEXP(enemy.getEXP());
                player.levelUp(player);
                showItemDrop(enemy);
                player.addItem(item_list.at(enemy.getDropItemID()), enemy.getDropItemNum());
                int choice = -1;
                std::cout << "按0查看详细信息，按其他数字跳过。" << std::endl;
                std::cin >> choice;
                if (choice == 0) {
                    std::cout << item_list.at(enemy.getDropItemID()).getName() << ": "
                        << item_list.at(enemy.getDropItemID()).getDescription() << std::endl;
                }
                break;
            }
            EnemyTurn(player, enemy);
            if (player.getHealth() <= 0) {
                break;
            }
        }
    }

}

void Spot::viewAround(int id) {
    std::cout << getDescription() << std::endl;
}

// 鎺㈢储杩囩▼锛屾牴鎹帺瀹跺湪褰撳墠浣嶇疆鐨勯�夋嫨鎵ц鐩稿簲鐨勬搷浣滐紝鍖呮嫭鏌ョ湅鍛ㄥ洿鐜銆佹煡鐪嬬墿鍝併�佹煡鐪嬬姸鎬併�佹垬鏂椼�佸墠寰�涓嬩竴涓埧闂村拰淇濆瓨閫�鍑?
void GameController::Discover(Player& player) {
    Spot previousSpot = spots_list.at(player.getCurSpotID());
    while (true) {
        system("pause");
        system("cls");
        int choice;
        showNormalDiscoverMenu();
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout<<CYAN;
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
            std::cout << RED;
            for (int i = 0; i < spots_list.at(player.getCurSpotID()).getExitNumber(); ++i) {
                std::cout << i + 1 << "."
                    << spots_list.at(spots_list.at(player.getCurSpotID()).getExits().at(i)).getName() << "\t";
            }
            std::cout <<YELLOW<< std::endl << "选择一个地方前往：";
            std::cin >> destination_choice;
            player.setSpotID(spots_list.at(player.getCurSpotID()).getExits().at(destination_choice - 1));
            break;
        case 6:
            saveArchive("data/archive.dat", player);
            exit(0);
        default:
            showChoiceError();
            continue;
        }
      
        
    }
}

void GameController::Interactive(Player& player) {
    int cur_Npc_numbers = spots_list.at(player.getCurSpotID()).getNpcNumber();
    if (cur_Npc_numbers == 0) {
        std::cout << "附近没有NPC。" << std::endl;
    }
    else {
        std::cout << "附近有 " << cur_Npc_numbers << "个NPC。" << std::endl;
        std::cout << "选择其中一个NPC接收任务：" << std::endl;
        int npc_choice = -1;
        for (int i = 0; i < cur_Npc_numbers; ++i) {
            std::cout << i + 1 << ". "
                << npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(i)).getName() << "\t";
        }
        std::cin >> npc_choice;
        Npc npc = npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(npc_choice - 1));
        if (player.getQuestID() == -1) {
            if (quests_list.at(npc.getQuestID()).getQuestDone()) {
                std::cout << "你已经完成了这项任务。" << std::endl;
                return;
            }
            quests_list.at(npc.getQuestID()).start(player);
        }
        else if (player.getQuestID() == npc.getQuestID()) {
            quests_list.at(npc.getQuestID()).check(player);
        }
        else {
            std::cout << "你现在已经有任务要做了，你可以在接这个任务之前完成它。" << std::endl;
            return;
        }
    }
}

void GameController::displayAllData() {
    for (const auto& spot : spots_list) {
        std::cout << "ID： " << spot.getID() << std::endl;
        std::cout << "名称： " << spot.getName() << std::endl;
        std::cout << "简介： " << spot.getDescription() << std::endl;
        std::cout << "附近有： " << spot.getExitNumber() << std::endl;
        std::cout << "可以去的地点有： ";
        const auto& exits = spot.getExits();
        for (const auto& exit : exits) {
            std::cout << exit << " ";
        }
        std::cout << std::endl;
        std::cout << "NPC名字： " << spot.getNpcNumber() << std::endl;
        std::cout << "NPC分别为： ";
        const auto& npcs = spot.getNpcs();
        for (const auto& npc : npcs) {
            std::cout << npc << " ";
        }
        std::cout << std::endl;
        std::cout << "Script: ";
        const auto& scripts = spot.getScripts();
        for (const auto& script : scripts) {
            std::cout << script << " ";
        }
        std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    for (const auto& enemy : enemies_list) {
        std::cout << "ID： " << enemy.getID() << std::endl;
        std::cout << "名称： " << enemy.getName() << std::endl;
        std::cout << "简介： " << enemy.getDescription() << std::endl;
        std::cout << "生命值： " << enemy.getHealth() << std::endl;
        std::cout << "防御值： " << enemy.getDefensive() << std::endl;
        std::cout << "攻击力： " << enemy.getStrength() << std::endl;
        std::cout << "exp: " << enemy.getEXP() << std::endl;
        std::cout << "物品： " << enemy.getDropItemID() << std::endl;
        std::cout << "技能： " << enemy.getSkillID() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void GameController::displayLogo(const std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr<<RED << "无法打开Logo.dat文件！" << std::endl;
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << YELLOW << line << std::endl;
        }
    }
    file.close();
}

void GameController::showStartMenu() {
    displayLogo("data/logo.dat");
    std::cout << RED << "1、新的旅途\t2、继续探索\t3、退出 "<< std::endl;
        int choice = -1;
    std::cin >> choice;
    while (true) {
        switch (choice) {
        case 1:
            current_player = initializeArchive();
            showPlayerState(current_player);
            //system("pause");
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
//显示地图
void GameController::displayMap(const std::string filename) {
    std::cout<<RED << "你现在在 " << spots_list.at(current_player.getCurSpotID()).getName() <<YELLOW<< std::endl;
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr <<RED<< "无法打开Map.dat文件！" << std::endl;
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << YELLOW << line << std::endl;
        }
    }
    file.close();
}
//初始化玩家数据
Player GameController::initializeArchive() {
    Player default_player("Harry Potter", 50, 0, 5, 100, 0.05f, 0.1f, 0.1f, 0);
    std::cout << scripts_list.at(0) << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 4);
    int randomNum = dis(gen);
    std::cout <<WHITE<< scripts_list.at(randomNum) << std::endl;
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
//读取各类文档
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
//开始任务
void Quest::start(Player& player) {
    player.setQuestID(getID());
    player.setProgress(0);
    questEnemy = enemies_list.at(getEnemyID());
    std::cout << getDescription0() << std::endl;
}
//检查任务是否完成
void Quest::check(Player& player) {
    if (player.getProgress() >= quests_list.at(player.getQuestID()).getEnemyNumber()) {
        std::cout << getDescription1() << std::endl;
        player.addItem(item_list.at(getItemID()), 1);
        setQuestDone(true);
        player.setQuestID(-1);
        player.setProgress(0);
    }
    else 
    {
        /*std::cout << scripts_list.at(-1) << std::endl;*/ // say unfinished
    }
}

