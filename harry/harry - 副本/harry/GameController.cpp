#include "GameController.h"

// ¶¨ÒåÑÕÉ«ºê
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
        std::cout << "ÎÞ·¨´ò¿ªÎÄ¼þ." << filename << std::endl;
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
        std::cout << "ÎÞ·¨´ò¿ªÎÄ¼þ" << filename << std::endl;
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
//        std::cout <<RED<< "ÎÞ·¨´ò¿ªÎÄ¼þ£º" << filename << std::endl;
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
//        std::cout <<RED<< "ÎÞ·¨´ò¿ªÎÄ¼þ£º" << filename << std::endl;
//    }
//    return player;
//}


// æ˜¾ç¤ºæˆ˜æ–—èœå•ï¼ŒåŒ…æ‹¬æ”»å‡»ã€æŠ€èƒ½å’Œé€ƒè·‘é€‰é¡¹
void GameController::showCombatMenu() {
    std::cout << "Ñ¡Ôñ¹¥»÷µÄ·½Ê½»òÕßÌÓÅÜ£º" << std::endl;
    std::cout << "1. ÆÕÍ¨¹¥»÷" << std::endl;
    std::cout << "2. Ê¹ÓÃ¼¼ÄÜ" << std::endl;
    std::cout << "3. Ê¹ÓÃµÀ¾ß" << std::endl;
    std::cout << "4. ÌÓÅÜ" << std::endl;
}

// æ ¹æ®çŽ©å®¶è§’è‰²æ˜¾ç¤ºæŠ€èƒ½èœå•ï¼Œåˆ—å‡ºå¯ç”¨çš„æŠ€èƒ½å’Œå¯¹åº”çš„ä¼¤å®?
void GameController::showSkillMenu(const Player& player) {
    std::cout << "Ñ¡ÔñÒ»¸ö¼¼ÄÜ½øÐÐ¹¥»÷£¬ÄãÏÖÔÚÓÐ" << player.getCurWisdom()
        << "µã·¨Á¦Öµ¡£" << std::endl;
    for (int i = 1; i <= player.getSkillList().size(); ++i) {
        std::cout << i << ". " << player.getSkillList().at(i - 1).skill_name << ", ÉËº¦Öµ£º "
            << player.getSkillList().at(i - 1).skill_power << "£¬·¨Á¦Öµ£º "
            << player.getSkillList().at(i - 1).wisdom_need << std::endl;
    }
}

// æ˜¾ç¤ºçŽ©å®¶æ‹¥æœ‰çš„ç‰©å“èœå•ï¼ŒåŒ…æ‹¬ç‰©å“åç§°å’Œæè¿?
void GameController::showItemMenu(Player player) {
    if (player.getItemList().size() != 0) {
        std::cout << "ÕâÊÇÄãËùÓÐµÄÎïÆ·£º" << std::endl;
        for (int i = 1; i <= player.getItemList().size(); ++i) {
            std::cout << i << ". " << player.getItemList().at(i - 1).getName() << "£¬¼ò½é£º "
                << player.getItemList().at(i - 1).getDescription() << "ÊýÁ¿£º "
                << player.getItemList().at(i - 1).getNumber() << std::endl;
        }
    }
    else {
        std::cout
            << "µ½Ä¿Ç°ÎªÖ¹£¬ÄãÊÖÉÏÊ²Ã´Ò²Ã»ÓÐ¡£Äã¿ÉÒÔ´Ó»÷°ÜµÐÈË»òÉÌÈËÖÐ»ñµÃÒ»Ð©ÓÐÓÃµÄÎïÆ·¡£"
            << std::endl;
    }
}

// æ˜¾ç¤ºé€ƒç¦»æˆ˜æ–—çš„æç¤ºä¿¡æ?
void GameController::showEscape() {
    std::cout << "Äã´ÓÕ½¶·ÖÐÌÓ×ß¡£¡£¡£¡£¡£¡£" << std::endl;
}

// æ˜¾ç¤ºçŽ©å®¶å—åˆ°ä¼¤å®³çš„ä¿¡æ¯ï¼ŒåŒ…æ‹¬çŽ©å®¶å§“åã€å—åˆ°çš„ä¼¤å®³å’Œå½“å‰å‰©ä½™ç”Ÿå‘½å€?
void GameController::showPlayerHurt(Player& player, int damage) {
    std::cout << player.getName() << " ÊÜµ½ " << damage << " µãÉËº¦ ";
    if (player.getHealth() > 0) {
        std::cout << player.getName() << "µÄÉúÃüÖµÎª " << player.getHealth() << std::endl;
    }
    else {
        std::cout << player.getName() << "ÓÚÕ½¶·ÖÐËÀÍö¡£" << std::endl;
    }
}

// æ˜¾ç¤ºæ•Œäººå—åˆ°ä¼¤å®³çš„ä¿¡æ¯ï¼ŒåŒ…æ‹¬æ•Œäººå§“åã€å—åˆ°çš„ä¼¤å®³å’Œå½“å‰å‰©ä½™ç”Ÿå‘½å€?
void GameController::showEnemyHurt(Enemy& enemy, int damage) {
    std::cout << enemy.getName() << " ÊÜµ½ " << damage << " µãÉËº¦¡£ ";
    if (enemy.getHealth() > 0) {
        std::cout << enemy.getName() << "µÄÉúÃüÖµÎª£º " << enemy.getHealth()  << std::endl;
    }
    else {
        std::cout << "¹§Ï²Äã»÷°ÜÁËµÐÈË£¡" << std::endl;
    }
}

// æ˜¾ç¤ºæ•Œäººæ”»å‡»çŽ©å®¶çš„æç¤ºä¿¡æ?
void GameController::showEnemyAttack(Enemy enemy) {
    std::cout << enemy.getName() << "¹¥»÷ÁËÄã¡£" << std::endl;
}

// æ˜¾ç¤ºé€‰æ‹©é”™è¯¯çš„æç¤ºä¿¡æ?
void GameController::showChoiceError() {
    std::cout << "ÄãÑ¡ÔñµÄÐòºÅ²»ºÏ·¨£¬ÇëÖØÐÂÑ¡Ôñ¡£" << std::endl;
}

// æ˜¾ç¤ºæ•ŒäººæŽ‰è½ç‰©å“çš„æç¤ºä¿¡æ?
void GameController::showItemDrop(Enemy enemy) {
    std::cout << enemy.getName() << " µôÂäÁËÒ»¸ö " << item_list.at(enemy.getDropItemID()).getName() << std::endl;
}

// æ˜¾ç¤ºæ™®é€šæŽ¢ç´¢èœå•ï¼ŒåŒ…æ‹¬æŸ¥çœ‹å‘¨å›´çŽ¯å¢ƒã€æŸ¥çœ‹èƒŒåŒ…ã€æŸ¥çœ‹çŽ©å®¶çŠ¶æ€ã€æˆ˜æ–—ã€å‰å¾€ä¸‹ä¸€ä¸ªæˆ¿é—´å’Œä¿å­˜å¹¶é€€å‡ºé€‰é¡¹
void GameController::showNormalDiscoverMenu() {
    std::cout <<YELLOW<< "Ñ¡ÔñÄã½ÓÏÂÀ´µÄÐÐ¶¯£º" << std::endl;
    std::cout
        <<YELLOW
        << "1.»·¹ËËÄÖÜ\t2.²é¿´±³°ü\t3.²é¿´×´Ì¬\t4.Õ½¶·\t5.Ç°ÍùÏÂÒ»¸öµØµã\t6.±£´æ²¢ÍË³ö"
        << std::endl;
}

// æ˜¾ç¤ºçŽ©å®¶çš„çŠ¶æ€ä¿¡æ¯ï¼ŒåŒ…æ‹¬ç”Ÿå‘½å€¼ã€åŠ›é‡ã€æ™ºæ…§ã€æš´å‡»çŽ‡ã€æš´å‡»ä¼¤å®³ã€æ•æ·åº¦å’Œçº§åˆ?
void GameController::showPlayerState(Player player) {
    std::cout << player.getName() << "µÄ×´Ì¬ÈçÏÂ£º" << std::endl << "ÉúÃüÖµ£º " << player.getHealth() << std::endl
        << "¹¥»÷Á¦£º" << player.getStrength() << std::endl << "·¨Á¦Öµ£º " << player.getWisdom() << std::endl
        << "±©»÷ÂÊ£º " << player.getCriticalRate() << std::endl << "±©»÷ÉËº¦£º "
        << player.getCriticalPower() << std::endl << "ÉÁ±ÜÖµ£º " << player.getAgility() << std::endl << "µÈ¼¶£º "
        << player.getLevel() << std::endl;
}

// çŽ©å®¶å›žåˆï¼Œå¤„ç†çŽ©å®¶åœ¨æˆ˜æ–—ä¸­çš„é€‰æ‹©ï¼Œå¹¶æ›´æ–°æ•Œäººçš„ç”Ÿå‘½å€?
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
                std::cout << "·¨Á¦Öµ²»×ã£¡" << std::endl;
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

// æ•Œäººå›žåˆï¼Œæ•Œäººæ”»å‡»çŽ©å®¶ï¼Œå¹¶æ›´æ–°çŽ©å®¶çš„ç”Ÿå‘½å€?
void GameController::EnemyTurn(Player& player, Enemy& enemy) {
    showEnemyAttack(enemy);
    showPlayerHurt(player, Player::getHit(player, enemy));
}

// æˆ˜æ–—è¿‡ç¨‹ï¼Œå¾ªçŽ¯æ‰§è¡ŒçŽ©å®¶å’Œæ•Œäººçš„å›žåˆï¼Œç›´åˆ°ä¸€æ–¹ç”Ÿå‘½å€¼ä¸º0
void GameController::Combat(Player& player) {
    int cur_Enemies_numbers = spots_list.at(player.getCurSpotID()).getEnemyNumber();
    if (cur_Enemies_numbers == 0) {
        std::cout << "¸½½üÃ»ÓÐµÐÈË¡£" << std::endl;
    }
    else {
        std::cout << "ÕâÀïÓÐ " << cur_Enemies_numbers << " ¸öµÐÈË¡£" << std::endl;
        std::cout << "ÇëÑ¡ÔñÆäÖÐÒ»¸ö½øÐÐ¹¥»÷£º" << std::endl;
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
                std::cout << "°´0²é¿´ÏêÏ¸ÐÅÏ¢£¬°´ÆäËûÊý×ÖÌø¹ý¡£" << std::endl;
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

// æŽ¢ç´¢è¿‡ç¨‹ï¼Œæ ¹æ®çŽ©å®¶åœ¨å½“å‰ä½ç½®çš„é€‰æ‹©æ‰§è¡Œç›¸åº”çš„æ“ä½œï¼ŒåŒ…æ‹¬æŸ¥çœ‹å‘¨å›´çŽ¯å¢ƒã€æŸ¥çœ‹ç‰©å“ã€æŸ¥çœ‹çŠ¶æ€ã€æˆ˜æ–—ã€å‰å¾€ä¸‹ä¸€ä¸ªæˆ¿é—´å’Œä¿å­˜é€€å‡?
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
            std::cout <<YELLOW<< std::endl << "Ñ¡ÔñÒ»¸öµØ·½Ç°Íù£º";
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
        std::cout << "¸½½üÃ»ÓÐNPC¡£" << std::endl;
    }
    else {
        std::cout << "¸½½üÓÐ " << cur_Npc_numbers << "¸öNPC¡£" << std::endl;
        std::cout << "Ñ¡ÔñÆäÖÐÒ»¸öNPC½ÓÊÕÈÎÎñ£º" << std::endl;
        int npc_choice = -1;
        for (int i = 0; i < cur_Npc_numbers; ++i) {
            std::cout << i + 1 << ". "
                << npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(i)).getName() << "\t";
        }
        std::cin >> npc_choice;
        Npc npc = npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(npc_choice - 1));
        if (player.getQuestID() == -1) {
            if (quests_list.at(npc.getQuestID()).getQuestDone()) {
                std::cout << "ÄãÒÑ¾­Íê³ÉÁËÕâÏîÈÎÎñ¡£" << std::endl;
                return;
            }
            quests_list.at(npc.getQuestID()).start(player);
        }
        else if (player.getQuestID() == npc.getQuestID()) {
            quests_list.at(npc.getQuestID()).check(player);
        }
        else {
            std::cout << "ÄãÏÖÔÚÒÑ¾­ÓÐÈÎÎñÒª×öÁË£¬Äã¿ÉÒÔÔÚ½ÓÕâ¸öÈÎÎñÖ®Ç°Íê³ÉËü¡£" << std::endl;
            return;
        }
    }
}

void GameController::displayAllData() {
    for (const auto& spot : spots_list) {
        std::cout << "ID£º " << spot.getID() << std::endl;
        std::cout << "Ãû³Æ£º " << spot.getName() << std::endl;
        std::cout << "¼ò½é£º " << spot.getDescription() << std::endl;
        std::cout << "¸½½üÓÐ£º " << spot.getExitNumber() << std::endl;
        std::cout << "¿ÉÒÔÈ¥µÄµØµãÓÐ£º ";
        const auto& exits = spot.getExits();
        for (const auto& exit : exits) {
            std::cout << exit << " ";
        }
        std::cout << std::endl;
        std::cout << "NPCÃû×Ö£º " << spot.getNpcNumber() << std::endl;
        std::cout << "NPC·Ö±ðÎª£º ";
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
        std::cout << "ID£º " << enemy.getID() << std::endl;
        std::cout << "Ãû³Æ£º " << enemy.getName() << std::endl;
        std::cout << "¼ò½é£º " << enemy.getDescription() << std::endl;
        std::cout << "ÉúÃüÖµ£º " << enemy.getHealth() << std::endl;
        std::cout << "·ÀÓùÖµ£º " << enemy.getDefensive() << std::endl;
        std::cout << "¹¥»÷Á¦£º " << enemy.getStrength() << std::endl;
        std::cout << "exp: " << enemy.getEXP() << std::endl;
        std::cout << "ÎïÆ·£º " << enemy.getDropItemID() << std::endl;
        std::cout << "¼¼ÄÜ£º " << enemy.getSkillID() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void GameController::displayLogo(const std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr<<RED << "ÎÞ·¨´ò¿ªLogo.datÎÄ¼þ£¡" << std::endl;
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
    std::cout << RED << "1¡¢ÐÂµÄÂÃÍ¾\t2¡¢¼ÌÐøÌ½Ë÷\t3¡¢ÍË³ö "<< std::endl;
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
//ÏÔÊ¾µØÍ¼
void GameController::displayMap(const std::string filename) {
    std::cout<<RED << "ÄãÏÖÔÚÔÚ " << spots_list.at(current_player.getCurSpotID()).getName() <<YELLOW<< std::endl;
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr <<RED<< "ÎÞ·¨´ò¿ªMap.datÎÄ¼þ£¡" << std::endl;
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << YELLOW << line << std::endl;
        }
    }
    file.close();
}
//³õÊ¼»¯Íæ¼ÒÊý¾Ý
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
//¶ÁÈ¡¸÷ÀàÎÄµµ
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
//¿ªÊ¼ÈÎÎñ
void Quest::start(Player& player) {
    player.setQuestID(getID());
    player.setProgress(0);
    questEnemy = enemies_list.at(getEnemyID());
    std::cout << getDescription0() << std::endl;
}
//¼ì²éÈÎÎñÊÇ·ñÍê³É
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

