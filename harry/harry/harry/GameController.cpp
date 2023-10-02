// ������ɫ��
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
        std::cout << "�޷����ļ�." << filename << std::endl;
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
        std::cout << "�޷����ļ�" << filename << std::endl;
    }
    return player;
}


// ��ʾս���˵����������������ܺ�����ѡ��
void GameController::showCombatMenu() {
    std::cout << "ѡ��ѡ����Ӧ�Ե�ǰ����" << std::endl;
    std::cout << "1.��ͨ����" << std::endl;
    std::cout << "2.ʹ�ü���" << std::endl;
    std::cout << "3.ʹ����Ʒ" << std::endl;
    std::cout << "4.����ս��" << std::endl;
}

// ������ҽ�ɫ��ʾ���ܲ˵����г����õļ��ܺͶ�Ӧ���˺�
void GameController::showSkillMenu(const Player& player) {
    std::cout << "��ѡ��һ�����ܣ���Ŀǰӵ��" << player.getCurWisdom()
        << "����ֵ��" << std::endl;
    for (int i = 1; i <= player.getSkillList().size(); ++i) {
        std::cout << i << ". " << player.getSkillList().at(i - 1).skill_name << ", �˺�: "
            << player.getSkillList().at(i - 1).skill_power << ", ��������: "
            << player.getSkillList().at(i - 1).wisdom_need << std::endl;
    }
}

// ��ʾ���ӵ�е���Ʒ�˵���������Ʒ���ƺ�����
void GameController::showItemMenu(Player player) {
    if (player.getItemList().size() != 0) {
        std::cout << "��Щ�����������Ʒ:" << std::endl;
        for (int i = 1; i <= player.getItemList().size(); ++i) {
            std::cout << i << ". " << player.getItemList().at(i - 1).getName() << ", ����: "
                << player.getItemList().at(i - 1).getNumber() << std::endl;
        }
    }
    else {
        std::cout
            << "Ŀǰ������û���κ���Ʒ�������ͨ����ɱ������������������Ʒ."
            << std::endl;
    }
}

// ��ʾ����ս������ʾ��Ϣ
void GameController::showEscape() {
    std::cout << "���������ⳡս��." << std::endl;
}

// ��ʾ����ܵ��˺�����Ϣ����������������ܵ����˺��͵�ǰʣ������ֵ
void GameController::showPlayerHurt(Player& player, int damage) {
    std::cout << player.getName() << " �ܵ��� " << damage << " �˺�. ";
    if (player.getHealth() > 0) {
        std::cout << player.getName() << " ������ֵ������ " << player.getHealth() << std::endl;
    }
    else {
        std::cout << player.getName() << " ���ⳡս����������." << std::endl;
    }
}

// ��ʾ�����ܵ��˺�����Ϣ�����������������ܵ����˺��͵�ǰʣ������ֵ
void GameController::showEnemyHurt(Enemy& enemy, int damage) {
    std::cout << enemy.getName() << " �ܵ� " << damage << " �˺�. ";
    if (enemy.getHealth() > 0) {
        std::cout << enemy.getName() << " ������ֵ������ " << enemy.getHealth() << std::endl;
    }
    else {
        std::cout << " ��ϲ��Ӯ���˱���ս���� " << std::endl;
    }
}

// ��ʾ���˹�����ҵ���ʾ��Ϣ
void GameController::showEnemyAttack(const Enemy& enemy) {
    std::cout << enemy.getName() << " ��������. " << std::endl;
}

// ��ʾѡ��������ʾ��Ϣ
void GameController::showChoiceError() {
    std::cout << " ��ѡ���˴����ѡ�������һ��. " << std::endl;
}

// ��ʾ���˵�����Ʒ����ʾ��Ϣ
void GameController::showItemDrop(const Enemy& enemy) {
    std::cout << enemy.getName() << " ������ " << item_list.at(enemy.getDropItemID()).getName() << std::endl;
}

// ��ʾ��ͨ̽���˵��������鿴��Χ�������鿴�������鿴���״̬��ս����ǰ����һ������ͱ��沢�˳�ѡ��
void GameController::showNormalDiscoverMenu() {
    std::cout<<YELLOW << " ѡ��һ���ж� " << std::endl;
    std::cout
        << "1.�鿴����\t2.���ӱ���\t3.����״̬\t4.Ѱ��ս��\t5.�򿪵�ͼ\t6.�����˳�"
        << std::endl;
}

// ��ʾ��ҵ�״̬��Ϣ����������ֵ���������ǻۡ������ʡ������˺������ݶȺͼ���
void GameController::showPlayerState(const Player& player) {
    std::cout <<CYAN<< player.getName() << " ��״̬���£�" << std::endl << "������" << player.getHealth() << std::endl
        << "����: " << player.getStrength() << std::endl << "����: " << player.getWisdom() << std::endl
        << "������" << player.getDefensive() << std::endl << "������: " << player.getCriticalRate()
        << std::endl << "��������: " << player.getCriticalPower() << std::endl << "����: "
        << player.getAgility() << std::endl << "�ȼ�: " << player.getLevel() << std::endl;
}

// ��һغϣ����������ս���е�ѡ�񣬲����µ��˵�����ֵ
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
                std::cout << "û���㹻�ķ�����ʩ����������һ��. " << std::endl;
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

// ���˻غϣ����˹�����ң���������ҵ�����ֵ
void GameController::EnemyTurn(Player& player, Enemy& enemy) {
    showEnemyAttack(enemy);
    showPlayerHurt(player, Player::getHit(player, enemy));
}

// ս�����̣�ѭ��ִ����Һ͵��˵Ļغϣ�ֱ��һ������ֵΪ0
void GameController::Combat(Player& player) {
    int cur_Enemies_numbers = spots_list.at(player.getCurSpotID()).getEnemyNumber();
    if (cur_Enemies_numbers == 0) {
        std::cout << "����û�п��Թ����ĵ���." << std::endl;
    }
    else {
        std::cout << "���ﹲ�� " << cur_Enemies_numbers << " �ֵ���." << std::endl;
        std::cout << "ѡ��һ����ʼ����." << std::endl;
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

// ̽�����̣���������ڵ�ǰλ�õ�ѡ��ִ����Ӧ�Ĳ����������鿴��Χ�������鿴��Ʒ���鿴״̬��ս����ǰ����һ������ͱ����˳�
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
            std::cout<<RED<< std::endl << "ѡ��һ��Ŀ�ĵ�:"<<YELLOW;
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
        std::cout << "����û�п��Խ�����NPC." << std::endl;
    }
    else {
        std::cout << "������ " << cur_Npc_numbers << " ��NPC." << std::endl;
        std::cout << "ѡ��һ��NPC����������." << std::endl;
        int npc_choice = -1;
        for (int i = 0; i < cur_Npc_numbers; ++i) {
            std::cout << i + 1 << ". "
                << npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(i)).getName() << "\t";
        }
        std::cin >> npc_choice;
        Npc npc = npcs_list.at(spots_list.at(player.getCurSpotID()).getNpcs().at(npc_choice - 1));
        if (player.getQuestID() == -1) {
            if (quests_list.at(npc.getQuestID()).getQuestDone()) {
                std::cout << "���Ѿ���ɹ��������." << std::endl;
                return;
            }
            quests_list.at(npc.getQuestID()).start(player);
        }
        else if (player.getQuestID() == npc.getQuestID()) {
            quests_list.at(npc.getQuestID()).check(player);
        }
        else {
            std::cout << "���Ѿ���һ��δ��ɵ������ˣ��������һ�������ڽ�ȡ��ǰ����." << std::endl;
            return;
        }
    }
}

void GameController::displayAllData() {
    for (const auto& spot : spots_list) {
        std::cout << "ID: " << spot.getID() << std::endl;
        std::cout << "����: " << spot.getName() << std::endl;
        std::cout << "����: " << spot.getDescription() << std::endl;
        std::cout << "��������: " << spot.getExitNumber() << std::endl;
        std::cout << "�����б�: ";
        const auto& exits = spot.getExits();
        for (const auto& exit : exits) {
            std::cout << exit << " ";
        }
        std::cout << std::endl;
        std::cout << "NPC����: " << spot.getNpcNumber() << std::endl;
        std::cout << "NPC�б�: ";
        const auto& npcs = spot.getNpcs();
        for (const auto& npc : npcs) {
            std::cout << npc << " ";
        }
        std::cout << std::endl;
        std::cout << "Script�б�: ";
        const auto& scripts = spot.getScripts();
        for (const auto& script : scripts) {
            std::cout << script << " ";
        }
        std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    for (const auto& enemy : enemies_list) {
        std::cout << "ID: " << enemy.getID() << std::endl;
        std::cout << "����: " << enemy.getName() << std::endl;
        std::cout << "����: " << enemy.getDescription() << std::endl;
        std::cout << "����ֵ: " << enemy.getHealth() << std::endl;
        std::cout << "����ֵ: " << enemy.getDefensive() << std::endl;
        std::cout << "������: " << enemy.getStrength() << std::endl;
        std::cout << "exp: " << enemy.getEXP() << std::endl;
        std::cout << "��Ʒ: " << enemy.getDropItemID() << std::endl;
        std::cout << "����: " << enemy.getSkillID() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void GameController::displayLogo(const std::string filename) {
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr << "�޷����ļ���" << std::endl;
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
    std::cout << "\033[0;32;31m" << "1������ѧԺ\t2��������;\t3��������;" << std::endl;
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
    std::cout <<RED<< "���������� " << spots_list.at(current_player.getCurSpotID()).getName() <<YELLOW<< std::endl;
    std::ifstream file;
    file.open(filename);
    if (!file) {
        std::cerr << "�޷����ļ���" << std::endl;
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
        std::cout << "����δ��ɣ�" << std::endl;
    }
}