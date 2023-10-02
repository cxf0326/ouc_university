#include "TextParser.h"

// read spots.dat
std::vector<Spot> TextParser::loadSpotDat(const std::string filename) {
    std::vector<Spot> spots;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        Spot spot;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] == '#') {
                if (!spot.getName().empty()) {
                    spots.push_back(spot);
                }
                spot = Spot();
                std::istringstream iss(line.substr(1));
                int id;
                iss >> id;
                spot.setID(id);
                std::getline(file, line);
                spot.setName(line);
                std::getline(file, line);
                spot.setDescription(line);
                std::getline(file, line);
                int exitNumber = std::stoi(line);
                spot.setExitNumber(exitNumber);
                std::getline(file, line);
                std::istringstream exitIss(line);
                int exitValue;
                while (exitIss >> exitValue) {
                    spot.getExits().push_back(exitValue);
                }
                std::getline(file, line);
                int enemyNumber = std::stoi(line);
                spot.setEnemyNumber(enemyNumber);
                std::getline(file, line);
                std::istringstream enemyIss(line);
                int enemyValue;
                while (enemyIss >> enemyValue) {
                    spot.getEnemies().push_back(enemyValue);
                }
                std::getline(file, line);
                int npcNumber = std::stoi(line);
                spot.setNpcNumber(npcNumber);
                std::getline(file, line);
                std::istringstream npcIss(line);
                int npcValue;
                while (npcIss >> npcValue) {
                    spot.getNpcs().push_back(npcValue);
                }
                std::getline(file, line);
                std::istringstream scriptIss(line);
                int scriptValue;
                while (scriptIss >> scriptValue) {
                    spot.getScripts().push_back(scriptValue);
                }
            }
        }
        if (!spot.getName().empty()) {
            spots.push_back(spot);
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件：" << filename << std::endl;
    }
    return spots;
}

// read scripts.dat
std::vector<std::string> TextParser::loadScriptDat(const std::string filename) {
    std::vector<std::string> scripts;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::string script;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] == '#') {
                if (!script.empty()) {
                    scripts.push_back(script);
                    script.clear();
                }
            }
            else {
                script += line + "\n";
            }
        }
        if (!script.empty()) {
            scripts.push_back(script);
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件： " << filename << std::endl;
    }
    return scripts;
}

// read enemies.dat
std::vector<Enemy> TextParser::loadEnemiesDat(const std::string filename) {
    std::vector<Enemy> enemies;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        Enemy enemy;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] == '#') {
                if (!enemy.getName().empty()) {
                    enemies.push_back(enemy);
                }
                enemy = Enemy();
                std::istringstream iss(line.substr(1));
                int id;
                iss >> id;
                enemy.setID(id);
                std::getline(file, line);
                enemy.setName(line);
                std::getline(file, line);
                enemy.setDescription(line);
                std::getline(file, line);
                int health = std::stoi(line);
                enemy.setHealth(health);
                std::getline(file, line);
                int defensive = std::stoi(line);
                enemy.setDefensive(defensive);
                std::getline(file, line);
                int strength = std::stoi(line);
                enemy.setStrength(strength);
                std::getline(file, line);
                int exp = std::stoi(line);
                enemy.setEXP(exp);
                std::getline(file, line);
                int itemID = std::stoi(line);
                enemy.setDropItemID(itemID);
                std::getline(file, line);
                int itemNumber = std::stoi(line);
                enemy.setDropItemNum(itemNumber);
                std::getline(file, line);
                int skillID = std::stoi(line);
                enemy.setSkillID(skillID);
            }
        }
        if (!enemy.getName().empty()) {
            enemies.push_back(enemy);
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件：" << filename << std::endl;
    }
    return enemies;
}

// read items.dat
std::vector<Item> TextParser::loadItemDat(const std::string filename) {
    std::vector<Item> items;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        Item item;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] == '#') {
                if (!item.getName().empty()) {
                    items.push_back(item);
                }
                item = Item();
                std::istringstream iss(line.substr(1));
                int id;
                iss >> id;
                item.setID(id);
                std::getline(file, line);
                item.setName(line);
                std::getline(file, line);
                item.setDescription(line);
                std::getline(file, line);
                int health_gain = std::stoi(line);
                item.setHealthGain(health_gain);
                std::getline(file, line);
                int defensive_gain = std::stoi(line);
                item.setDefensiveGain(defensive_gain);
                std::getline(file, line);
                int strength_gain = std::stoi(line);
                item.setWisdomGain(strength_gain);
            }
        }
        if (!item.getName().empty()) {
            items.push_back(item);
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件： "<< filename << std::endl;
    }
    return items;
}

// read npcs.dat
std::vector<Npc> TextParser::loadNpcDat(const std::string filename) {
    std::vector<Npc> Npcs;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        Npc npc;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] == '#') {
                if (!npc.getName().empty()) {
                    Npcs.push_back(npc);
                }
                npc = Npc();
                std::istringstream iss(line.substr(1));
                int id;
                iss >> id;
                npc.setID(id);
                std::getline(file, line);
                npc.setName(line);
                std::getline(file, line);
                npc.setDescription(line);
                std::getline(file, line);
                int questID = std::stoi(line);
                npc.setQuestID(questID);
            }
        }
        if (!npc.getName().empty()) {
            Npcs.push_back(npc);
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件：" << filename << std::endl;
    }
    return Npcs;
}


// read quest.dat
std::vector<Quest> TextParser::loadQuestDat(const std::string filename) {
    std::vector<Quest> quests;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        Quest quest;
        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }
            if (line[0] == '#') {
                if (!quest.getName().empty()) {
                    quests.push_back(quest);
                }
                quest = Quest();
                std::istringstream iss(line.substr(1));
                int id;
                iss >> id;
                quest.setID(id);
                std::getline(file, line);
                quest.setName(line);
                std::getline(file, line);
                quest.setDescription0(line);
                std::getline(file, line);
                quest.setDescription1(line);
                std::getline(file, line);
                int enemyID = std::stoi(line);
                quest.setEnemyID(enemyID);
                std::getline(file, line);
                int enemyNumber = std::stoi(line);
                quest.setEnemyNumber(enemyNumber);
                std::getline(file, line);
                int itemID = std::stoi(line);
                quest.setItemID(itemID);
            }
        }
        if (!quest.getName().empty()) {
            quests.push_back(quest);
        }
        file.close();
    }
    else {
        std::cout << "无法打开文件： "<< filename << std::endl;
    }
    return quests;
}

