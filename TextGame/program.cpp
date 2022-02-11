#include "program.h"

Program::Program() {
    // todo: game won variable
	game_over = false;
	currentRoom = nullptr;
    moved = true;
    setupCommands();
    setupFunctionMap();
	setupWorld();
}

string Program::toLower(const string& upper) {
    string lower = "";
    for (unsigned int i = 0; i < upper.size(); i++) {
        lower += tolower(upper[i]);
    }
    return lower;
}

int Program::is_abbrev(string str, string substr) {
    return !(strncmp(str.c_str(), substr.c_str(), strlen(substr.c_str())));
}

void Program::color(int color = 0x07) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Program::ignoreOutput(vector<string> v, int i) {
    if (i >= v.size()) {
        return;
    }
    cout << "\nWarning: Your input '";
    for (int a = i; a < v.size() - 1; a++) {
        cout << v[a] << " ";
    }
    cout << v[v.size() - 1] << "' was ignored." << endl;
}

void Program::run() {
    string userInput;

    while (!game_over) {
        if (moved) {
            color(0x03);
            std::cout << "\n" << currentRoom->getName() << endl;
            color();
            std::cout << currentRoom->getDescription() << endl;
            color(0x0c);
            for (int i = 0; i < item_list.size(); i++) {
                if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                    if (item_list[i]->getIsPerson() == true) {
                        if (item_list[i]->getHiddenState() == 0) {
                            std::cout << item_list[i]->getShortDesc() << std::endl;
                        }
                    }
                }
            }
            color(0x0e);
            for (int i = 0; i < item_list.size(); i++) {
                if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                    if (item_list[i]->getIsPerson() == false) {
                        if (item_list[i]->getHiddenState() == 0) {
                            std::cout << item_list[i]->getShortDesc() << std::endl;
                        }
                    }
                }
            }
            color();
        }

        // FOR DEBUG USE ONLY: Prints every room in the game.
        /*
        for (int i = 0; i < room_list.size(); i++) {
            std::cout << room_list[i]->getName() << endl;
        }
        */
        checkSpecs();
        if (game_over) {
            cout << "\nGAME OVER\nPress any key to try again!" << endl;
            std::getchar();
            std::cout << "Space-time rewinds, and you feel yourself pulled back to a familiar place..." << endl;
            return;
        }
        printExits();
        moved = false;
        std::getline(cin, userInput);
        parseCommand(toLower(userInput));
	}
}

void Program::setupWorld() {
    string r1desc =
        "A torrent of cascading molten rock flows swiftly from the falls behind you,\n"
        "superheating the ground and scorching it black as it lands. Ash swirls\n"
        "through the cavern as unseen air currents flow in no discernible pattern,\n"
        "cycling the immeasurable amount of soot back up to higher elevations. Every\n"
        "time you stop to take a breath, you are reminded of the inhospitability of\n"
        "this place, and decide it would be prudent to get a move on, quickly. The\n"
        "cavern ledge continues to the east.";

    string r2desc =
        "The rocky ledge comes to an end here at a nice vantage point, from where\n"
        "you can make out many of the terrain's surrounding features. Far below,\n"
        "bubbling pools of magma froth violently as they draw heat from further\n"
        "beneath the surface. The safety of the ledge lies back to the west, while\n"
        "to the east there is nothing but air, and a long way down.";

    string r3desc =
        "Holding your breath, you step fearlessly off the edge of the cliff...";

    string r4desc =
        "The rocky promontory you stand on continues to travel east-west along the\n"
        "mountain, but also curves sharply to the north here, where in the side of\n"
        "the rocky face you can make out an ancient stone door. The ash in the air\n"
        "is beginning to become more manageable, but it is still swelteringly hot.";

    string r5desc =
        "This north-south passage is old and musty from years of neglect.";

    string r6desc =
        "The tunnel begin to narrow here as it continues further into the mountain.\n"
        "Peculiarly, however, the passage does not seem to be getting that much\n"
        "darker. A cursory inspection of your surroundings reveals that the walls\n"
        "themselves appear to be glowing with unnatural light, though it isn't\n"
        // "immediately clear why. The passage continues to the north.";
        "immediately clear why. The passage seems to end at a larger wall up ahead.";

    string r7desc =
        "Your wings save you from plummeting to your doom! To the west lies victory,\n"
        "while down below, well, you wouldn't want to go there now, would you?";

    string r8desc =
        "You burn yourself alive!";

    string r9desc =
        "You have made it out of the Magma Escape Room alive! Congratulations.";

    string r10desc =
        "The passage ends at a large wall.";

    Room* r1 = new Room(1, "The Lava Falls", r1desc, -1, 4, -1, -1, -1, -1);
    Room* r2 = new Room(2, "A Rocky Ledge", r2desc, -1, 3, -1, 4, -1, -1);
    Room* r3 = new Room(3, "Above the Magma Pools", r3desc, -1, -1, -1, 2, -1, 7);
    Room* r4 = new Room(4, "Before an Ancient Stone Door", r4desc, -1, 2, -1, 1, -1, -1);
    Room* r5 = new Room(5, "A Long Forgotten Passage", r5desc, 6, -1, 4, -1, -1, -1);
    Room* r6 = new Room(6, "The Passage Continues", r6desc, 10, -1, 5, -1, -1, -1);
    Room* r7 = new Room(7, "Mid-Air Over Magma", r7desc, -1, -1, -1, 9, 3, 8);
    Room* r8 = new Room(8, "Death by Magma", r8desc, -1, -1, -1, -1, 7, -1);
    Room* r9 = new Room(9, "Victory!", r9desc, -1, 8, -1, -1, -1, -1);
    Room* r10 = new Room(10, "A Split in the Passage", r10desc, -1, -1, 6, -1, -1, -1);
    room_list.push_back(r1);
    room_list.push_back(r2);
    room_list.push_back(r3);
    room_list.push_back(r4);
    room_list.push_back(r5);
    room_list.push_back(r6);
    room_list.push_back(r7);
    room_list.push_back(r8);
    room_list.push_back(r9);
    room_list.push_back(r10);

    string sItemDesc1 =
        "A crumpled piece of paper flutters on an unseen breeze.";

    string lItemDesc1 =
        "Sample Text";

    string sItemDesc2 = // unused
        "An ancient stone door stands here, blocking passage.";

    string lItemDesc2 =
        "Intricate stone carvings span the height of this ancient door. It has no\n"
        "knobs, nooks or crevices by which it can visibly be opened, and currently\n"
        "bars passage to the north. Still, you feel as if there must be some way\n"
        "to make it open, or at least be able to get past it. Above one of the\n"
        "carvings, you notice a plaque that had earlier escaped your notice.";

    string sItemDesc3 =
        "A hopelessly lost adventurer ambles along weakly.";

    string lItemDesc3 =
        "Clinging desperately to the hope that he may be rescued, this adventurer\n"
        "does not even notice as you enter the room. Though still quite fit in\n"
        "appearance, and lean of build, he appears to be quite lethargic and\n"
        "lonely at the moment. Perhaps you could listen to him and see if he has\n"
        "anything to say.";

    string sItemDesc4 =
        "A tiny platinum coin lies here, half-buried in the ash.";

    string lItemDesc4 =
        "The faces of the coin gleam with a magnificent lustre.";

    string lItemDesc5 =
        "The wall you see before you is covered from top to bottom with countless\n"
        "inscriptions, and a particularly large section in the center of the wall\n"
        "glows with an unnatural light, as if by magic. It appears some of the\n"
        "writing may be intelligible, if you were to look at the writing directly.";

    string sItemDesc6 = // unused
        "Flowing and glowing scripture illuminates the walls of the tunnel.";

    string lItemDesc6 =
        "The scripture on the wall appears to spell out a person's name.";

    string lItemDesc7 =
        "The name appears to be that of this game's creator. It reads, 'Jordan'.";

    string sItemDesc8 = // unused
        "A shiny golden plaque has been affixed to the headstone of the doorway.";

    string lItemDesc8 =
        "\n    I rain down in this dreaded place\n"
        "    The powder left when something has been burned;\n"
        "    Affix a 'b' to my beginning\n"
        "    And the key to getting past me, you'll have earned.\n\n"
        "You look back at the door, contemplating the riddle.";

    string lItemDesc9 =
        "Stone carvings depicting unknown deities adorn the surface of the door.\n"
        "The carvings serve little purpose other than ornamentation.";

    string sItemDesc10 =
        "An enchanted pair of eagle's wings rest here in the treasure room.";

    string lItemDesc10 =
        "You gaze upon an unassuming pair of waxen bird wings. It is said that long\n"
        "ago, a similar pair of wings was fashioned by Daedalus for his son, Icarus,\n"
        "so that they might escape the land of Crete. Icarus, however, became so\n"
        "charmed by the experience that he, forgetting their composition, began\n"
        "to fly higher into the sky. The sun quickly melted the adhesive in the\n"
        "wings and thus Icarus fell, drowning in the sea.\n\n"
        "This pair of wings, however, seems to have a magical enchantment upon it.\n"
        "Even the heat of the fiery mountain in which it has rested has not softened\n"
        "the wax even slightly. You think these would make an excellent mode of\n"
        "transport around here, and possibly aid you in escaping this place.\n\n"
        "(Having these in your inventory grants the power of flight.)";

    // Item* item1 = new Item(1, 3, { "paper", "folded", "parchment", "crumpled" }, "a crumpled piece of paper", sItemDesc1, lItemDesc1, true, 2, false, {});
    map<string, int> map;
    map["push"] = 1;
    map["bash"] = 2;
    map["open"] = 5;
    Item* item2 = new Item(2, 4, { "door", "stone", "ancient" }, "the ancient stone door", sItemDesc2, lItemDesc2, false, 0, false, map);
    map = {};
    map["listen"] = 3;
    Item* item3 = new Item(3, 5, { "lost", "adventurer" }, "the lost adventurer", sItemDesc3, lItemDesc3, false, 0, true, map);
    map = {};
    map["insert"] = 4;
    Item* item4 = new Item(4, -1, { "coin", "small", "platinum", "tiny" }, "a tiny platinum coin", sItemDesc4, lItemDesc4, 1, 0, false, map);
    Item* item5 = new Item(5, 6, { "wall", "walls", "glowing" }, "the glowing wall", "", lItemDesc5, 0, 2, false, {});
    Item* item6 = new Item(6, 6, { "scripture", "writing", "inscription", "inscriptions"}, "the writing on the wall", "", lItemDesc6, 0, 3, false, {});
    Item* item7 = new Item(7, 6, { "name" }, "the name spelled out on the wall", "", lItemDesc7, 0, 3, false, {});
    Item* item8 = new Item(8, 4, { "plaque" }, "the plaque on the door", "", lItemDesc8, 0, 3, false, {});
    Item* item9 = new Item(9, 4, { "carvings", "carving", "deities" }, "the carvings on the door", "", lItemDesc9, 0, 3, false, {});
    Item* item10 = new Item(10, -1, { "wings", "enchanted", "eagle", "eagle's", "pair" }, "an enchanted pair of eagle's wings", sItemDesc10, lItemDesc10, 1, 0, false, {});

    // item_list.push_back(item1);
    item_list.push_back(item2);
    item_list.push_back(item3);
    item_list.push_back(item4);
    item_list.push_back(item5);
    item_list.push_back(item6);
    item_list.push_back(item7);
    item_list.push_back(item8);
    item_list.push_back(item9);
    item_list.push_back(item10);

    // STARTING ROOM
    currentRoom = r1;
}

Room* Program::getRoom(int id) {
    for (int i = 0; i < room_list.size(); i++) {
        if (room_list[i]->getRoomID() == id) {
            return room_list[i];
        }
    }
    return nullptr;
}

void Program::printExits() {
    std::cout << "\nExits:";
    if (currentRoom->getN() != -1) {
        std::cout << "N";
    }
    if (currentRoom->getE() != -1) {
        std::cout << "E";
    }
    if (currentRoom->getS() != -1) {
        std::cout << "S";
    }
    if (currentRoom->getW() != -1) {
        std::cout << "W";
    }
    if (currentRoom->getU() != -1) {
        std::cout << "U";
    }
    if (currentRoom->getD() != -1) {
        std::cout << "D";
    }
    std::cout << "> ";
}

void Program::parseCommand(string userInput) {

    // user pressed only return
    if (userInput.length() == 0) {
        return;
    }

    vector<string> v = {};
    string temp = "";
    for (int i = 0; i < userInput.length(); i++) {
        if (userInput[i] == ' ') {
            v.push_back(temp);
            temp = "";
        }
        else {
            temp.push_back(userInput[i]);
        }
    }
    v.push_back(temp);

    if (v.size() == 0) {
        // DO NOTHING AND PRINT A NEW PROMPT
    } else {
        // Special command
        for (int i = 0; i < item_list.size(); i++) {
            if (!item_list[i]->getSpecs().empty()) {
                map<string, int> specs = item_list[i]->getSpecs();
                if (specs.find(v[0]) != specs.end()) {
                    // Item in room that has the spec
                    if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                        special(v, item_list[i]);
                        return;
                    }
                    // Item in inventory
                    if (item_list[i]->getRoomID() == 0) {
                        special(v, item_list[i]);
                        return;
                    }
                }
            }
        }

        // Command list
        for (int i = 0; i < commands.size(); i++) {
            if (is_abbrev(commands[i], v[0])) {
                // EXECUTE COMMAND
                ((*this).*(functionMap.find(commands[i]))->second)(v);
                return;
            }
        }

        // Command unrecognized
        cout << "\nHuh?!" << endl;

    }
}

void Program::setupCommands() {
    commands = { "north", "east", "south", "west", "up", "down", "look", "help", "get", "take", "drop", "inventory", "restart"};
}

void Program::setupFunctionMap() {
    functionMap["north"] = &Program::move;
    functionMap["east"] = &Program::move;
    functionMap["south"] = &Program::move;
    functionMap["west"] = &Program::move;
    functionMap["up"] = &Program::move;
    functionMap["down"] = &Program::move;
    functionMap["look"] = &Program::look;
    functionMap["help"] = &Program::help;
    functionMap["get"] = &Program::get;
    functionMap["take"] = &Program::get;
    functionMap["drop"] = &Program::drop;
    functionMap["inventory"] = &Program::inventory;
    functionMap["restart"] = &Program::restart;
}

void Program::restart(vector<string> v) {
    if (v[0] != "restart") {
        cout << "\nYou have to type 'restart' - no less - to restart!" << endl;
        return;
    } else {
        std::cout << "\nSpace-time rewinds, and you feel yourself pulled back to a familiar place..." << endl;
        game_over = true;
    }
}

void Program::move(vector<string> v) {
    char c = v[0].at(0);
    int dest_room = -1;
    switch (c) {
        case 'n': {
            dest_room = currentRoom->getN();
            break;
        }
        case 'e': {
            dest_room = currentRoom->getE();
            break;
        }
        case 's': {
            dest_room = currentRoom->getS();
            break;
        }
        case 'w': {
            dest_room = currentRoom->getW();
            break;
        }
        case 'u': {
            dest_room = currentRoom->getU();
            break;
        }
        case 'd': {
            dest_room = currentRoom->getD();
            break;
        }
        default: {
            cout << "\nError in move!" << endl;
        }
    }
    if (dest_room != -1) {
        currentRoom = getRoom(dest_room);
        moved = true;
    } else {
        cout << "\nAlas, you cannot go that way..." << endl;
    }
}


void Program::look(vector<string> v) {
    int size = v.size();
    if (size == 1) {
        moved = true;
        return;
    }
    if (size == 2) {
        if (is_abbrev("inside", v[1])) {
            // look_in(v[1]);
            return;
        }
        else {
            look_at(v[1]);
            return;
        }
    }
    if (size == 3) {
        if ((v[1] == "at") || (v[1] == "the")) {
            look_at(v[2]);
            return;
        }
        else if (is_abbrev("inside", v[1])) {
            // look_in(v[2]);
            return;
        }
        else {
            ignoreOutput(v, 2);
            look_at(v[1]);
            return;
        }
    }
    if (size >= 4) {
        if (v[1] == "at") {
            if (v[2] == "the") {
                if (size > 4) {
                    ignoreOutput(v, 4);
                }
                look_at(v[3]);
                return;
            }
            else {
                ignoreOutput(v, 3);
                look_at(v[2]);
                return;
            }
        }
        else if (is_abbrev("inside", v[1])) {
            if (v[2] == "the") {
                if (size > 4) {
                    ignoreOutput(v, 4);
                }
                // look_in(v[3]);
                return;
            }
            else {
                ignoreOutput(v, 3);
                // look_in(v[2]);
                return;
            }
        }
        else {
            // not looking "at" or "in" something
            ignoreOutput(v, 2);
            look_at(v[1]);
            return;
        }
    }
}

void Program::look_at(string noun) {
    if ((noun == "at") || (noun == "the")) {
        std::cout << "\nLook at what?" << endl;
        return;
    }

    for (int i = 0; i < item_list.size(); i++) {
        // Inventory objects
        if (item_list[i]->getRoomID() == 0) {
            for (int j = 0; j < item_list[i]->getNouns().size(); j++) {
                if (item_list[i]->getNouns()[j] == noun) {
                    std::cout << "\nYou look at " << item_list[i]->getName() << "." << endl;
                    std::cout << item_list[i]->getLongDesc() << endl;
                    return;
                }
            }
        }

        // Room objects
        if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
            for (int j = 0; j < item_list[i]->getNouns().size(); j++) {
                if (item_list[i]->getNouns()[j] == noun) {
                    std::cout << "\nYou look at " << item_list[i]->getName() << "." << endl;
                    std::cout << item_list[i]->getLongDesc() << endl;
                    return;
                }
            }
        }
    }

    // Object could not be found
    std::cout << "\nYou do not see that here." << endl;
}

void Program::help(vector<string> v) {
    if (v.size() > 1) {
        if (v.size() > 2) {
            ignoreOutput(v, 2);
        }
        // TODO: Handle help for each individual command
        // handleHelp(v[1]);
    }
    else {
        std::cout << std::endl <<
            // TODO: SCAN
            "The general commands available to you are:\n\n"
            "    LOOK, SCAN, NORTH, EAST, SOUTH, WEST, UP, DOWN,\n"
            "    INVENTORY, GET, DROP, and RESTART.\n\n"
            "To get more information on a particular command, type 'HELP [COMMAND]'.\n\n"

            "There are other commands, generally of the form [VERB] [NOUN], however\n"
            "these must be discovered on your own. Use your imagination, and don't\n"
            "forget to have fun!"
            << std::endl;
    }
}

void Program::get(vector<string> v) {
    // TODO: Handle
    // get the X from the Y
    // get the X from Y
    // get the X the Y
    // get the X Y
    // get X from the Y
    // get X from Y
    // get X the Y
    // get X Y
    // get X
    if (v.size() > 1) {
        if (v[1] == "the") {
            if (v.size() > 2) {
                if (v.size() > 3) {
                    ignoreOutput(v, 3);
                }
                handleGet(v[2]);
            }
            else {
                std::cout << "\nGet what?" << endl;
            }
        }
        else {
            if (v.size() > 2) {
                ignoreOutput(v, 2);
            }
            handleGet(v[1]);
        }
    }
    else {
        std::cout << "\nGet what?" << endl;
    }
}

void Program::handleGet(string noun) {
    if (noun == "all") {
        int count = 0;
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getIsPerson() == false) {
                if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                    if (item_list[i]->getHiddenState() < 2) {
                        if (item_list[i]->getGetState() == 1) {
                            count++;
                            std::cout << "\nYou get " << item_list[i]->getName() << ".";
                            invSize++;
                            item_list[i]->setRoomID(0);
                        } else if (item_list[i]->getGetState() == 0) {
                            std::cout << "\nYou can't seem to get " << item_list[i]->getName() << ".";
                            count++;
                        } else {
                            // state == 2
                            std::cout << "\nThere's no reason to get " << item_list[i]->getName() << ".";
                            count++;
                        }
                    }
                }
            }
        }
        if (count == 0) {
            std::cout << "\nYou can't seem to find anything to pick up." << std::endl;
        } else {
            std::cout << std::endl;
        }
    } else {
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getIsPerson() == false) {
                if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                    for (int j = 0; j < item_list[i]->getNouns().size(); j++) {
                        if (item_list[i]->getNouns()[j] == noun) {
                            if (item_list[i]->getHiddenState() < 3) {
                                if (item_list[i]->getGetState() == 1) {
                                    std::cout << "\nYou get " << item_list[i]->getName() << "." << endl;
                                    invSize++;
                                    item_list[i]->setRoomID(0);
                                    return;
                                } else if (item_list[i]->getGetState() == 0) {
                                    std::cout << "\nYou can't seem to get " << item_list[i]->getName() << "." << endl;
                                    return;
                                }
                                else {
                                    // state == 2
                                    std::cout << "\nThere's no reason to pick that up." << endl;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
        std::cout << "\nYou do not see that here." << endl;
    }
}

void Program::inventory(vector<string> v) {
    if (invSize == 0) {
        std::cout << "\nYou aren't carrying anything." << endl;
    } else {
        std::cout << "\nYou are carrying:" << endl;
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getRoomID() == 0) {
                std::cout << item_list[i]->getName() << endl;
            }
        }
    }
}

void Program::drop(vector<string> v) {
    if (v.size() > 1) {
        if (v[1] == "the") {
            if (v.size() > 2) {
                if (v.size() > 3) {
                    ignoreOutput(v, 3);
                }
                handleDrop(v[2]);
            }
            else {
                std::cout << "\nDrop what?" << endl;
            }
        }
        else {
            if (v.size() > 2) {
                ignoreOutput(v, 2);
            }
            handleDrop(v[1]);
        }
    }
    else {
        std::cout << "\nDrop what?" << endl;
    }
}

void Program::handleDrop(string noun) {
    if (noun == "all") {
        if (invSize == 0) {
            std::cout << "\nYou aren't carrying anything." << std::endl;
            return;
        }
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getRoomID() == 0) {
                std::cout << "\nYou drop " << item_list[i]->getName() << "." << endl;
                invSize--;
                item_list[i]->setRoomID(currentRoom->getRoomID());
                // When an item is dropped, set its hidden state to 0
                item_list[i]->setHiddenState(0);
            }
        }
    } else {
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getRoomID() == 0) {
                for (int j = 0; j < item_list[i]->getNouns().size(); j++) {
                    if (item_list[i]->getNouns()[j] == noun) {
                        std::cout << "\nYou drop " << item_list[i]->getName() << "." << endl;
                        invSize--;
                        item_list[i]->setRoomID(currentRoom->getRoomID());
                        // When an item is dropped, set its hidden state to 0
                        item_list[i]->setHiddenState(0);
                        return;
                    }
                }
            }
        }
    }
}

void Program::special(vector<string> v, Item* item) {
    // For debug use only
    // Print the trigger word and the specNum
    // cout << v[0] << ", " << specNum << endl;
    switch (item->getSpecs().find(v[0])->second) {
        case 1: {
            // ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        cout << "\nYou push on the door, but it doesn't budge." << endl;
                        return;
                    }
                }
            }
            cout << "\nHuh?!" << endl;
            return;
        }
        case 2: {
            // ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        cout << "\nYou bash on the door, and it falls over, revealing a passage to the north.\n"
                            "Its riddle solved, the plaque falls from the door and shatters!" << endl;
                        for (int i = 0; i < room_list.size(); i++) {
                            if (room_list[i]->getRoomID() == 4) {
                                room_list[i]->setN(5);
                                string newDesc =
                                    "The rocky promontory you stand on continues to travel east-west along the\n"
                                    "mountain, but also curves sharply to the north here, where in the side of\n"
                                    "the rocky face you can make out the entrance to a dark passage. The stony\n"
                                    "crevice looks as though it once entertained a door of some sort, but in\n"
                                    "the spot where it looks like the door should be, there is now nothing. The\n"
                                    "ash in the air is beginning to become more manageable here, but it is\n"
                                    "still swelteringly hot. You feel you should not tarry too much longer.";
                                room_list[i]->setDescription(newDesc);
                            }
                        }
                        for (int j = 0; j < item_list.size(); j++) {
                            if (item_list[j]->getItemID() == 2) {
                                item_list[j]->removeSpec("push");
                                item_list[j]->removeSpec("bash");
                                item_list[j]->setName("the destroyed stone door");
                                item_list[j]->setNouns({ "remains", "destroyed", "stone", "door", "ancient", "shattered" });
                                item_list[j]->setShortDesc("The shattered remains of what was once a door lie scattered here.");
                                item_list[j]->setLongDesc("After the hefty bash inflicted upon it, this door now lies in pieces.");
                                item_list[j]->setGetState(2);
                            }
                            if (item_list[j]->getItemID() == 8) {
                                item_list[j]->setRoomID(-1);
                            }
                            if (item_list[j]->getItemID() == 9) {
                                item_list[j]->setLongDesc("The once intricate carvings are now nothing more than fragments of stone.");
                            }
                        }
                        return;
                    }
                }
            }
            cout << "\nHuh?!" << endl;
            return;
        }
        case 3: {
            // ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        string specMsg =
                            "\nFinally noticing you as you approach, the adventurer begins to speak.\n\n"
                            "        Hello there. I suppose you're wondering how I ended up here. Well,\n"
                            "    I was exploring this ancient temple, you see, when the ground opened up\n"
                            "    and swallowed me whole! I must've landed softly, since I haven't broken\n"
                            "    any bones, but the whole ordeal must've made me lose consciousness.\n\n"
                            "        When I awoke, I found myself down here, with my back to a fiery\n"
                            "    mountain and a dark tunnel ahead. I should've tried to climb back up\n"
                            "    when I had the chance, because the next thing I knew, the door over\n"
                            "    there swung itself closed, trapping me behind it. I've been pounding at\n"
                            "    it for days, but I didn't know a bash would knock it down! Thanks for\n"
                            "    opening the way back out, now if you'll excuse me, I really need to get\n"
                            "    out of here...\n\n"
                            "The adventurer pushes past you to the south, heading for the lava falls.";
                        cout << specMsg << endl;
                        item->setRoomID(1);
                        return;
                    }
                }
            }
            cout << "\nHuh?!" << endl;
            return;
        }
        case 4: {
            // ignoreOutput(v, 3);
            if (v.size() >= 3) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        if (v[2] == "slot") {
                            if (currentRoom->getRoomID() == 6) {
                                cout << "\nYou insert the coin into the slot, and an item pops out!" << endl;
                                for (int j = 0; j < item_list.size(); j++) {
                                    if (item_list[j]->getItemID() == 10) {
                                        item_list[j]->setRoomID(6);
                                    }
                                    if (item_list[j]->getItemID() == 4) {
                                        item_list[j]->setRoomID(-1);
                                    }
                                }
                                return;
                            }
                        }
                    }
                }
            }
            cout << "\nHuh?!" << endl;
            return;
        }
        case 5: {
            // ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        cout << "\nYou're not sure how you'd do that given the door has no handles." << endl;
                        return;
                    }
                }
            }
            cout << "\nHuh?!" << endl;
            return;
        }
        default: {
            cout << "\nError!" << endl;
            break;
        }
    }
}

void Program::checkSpecs() {
    if (currentRoom->getRoomID() == 1) {
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getItemID() == 3) {
                if (item_list[i]->getRoomID() == 1) {
                    string specMsg =
                        "\n    As you enter the room, you notice the adventurer taking off his pack. He\n"
                        "turns it upside-down and shakes it good, and a collection of items spill out\n"
                        "onto the floor. He discards the pack, sizes up the cliff, and ponders his\n"
                        "next course of action.\n\n"
                        "    He ties together a thick coil of rope and a metal catch, and throws\n"
                        "his newly-fashioned grappling hook high up the face of the cliff. Mustering\n"
                        "the last of his strength, you watch as he attempts to climb up the rope to\n"
                        "freedom. Just as you think he is about to make it to the top, the hook\n"
                        "comes loose, sending it and the adventurer tumbling to certain doom.\n\n"
                        "    A pathetic scream is all you hear before the noise is cut short by the\n"
                        "adventurer being immolated in the lava. Guess he won't be needing the rest\n"
                        "of his things anymore...";
                    item_list[i]->setRoomID(-1);
                    cout << specMsg << endl;
                    for (int j = 0; j < item_list.size(); j++) {
                        if (item_list[j]->getItemID() == 4) {
                            item_list[j]->setRoomID(1);
                        }
                    }
                }
            }
        }
    }
    if (currentRoom->getRoomID() == 3) {
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getItemID() == 10) { // TODO: CHANGE ITEM ID TO SAFETY ITEM e.g. WINGS OF FLIGHT
                if (item_list[i]->getRoomID() == 0) { // IF ITEM IS IN INVENTORY
                    return; // SAFE!
                }
            }
        }
        string specMsg = "You plummet to your death!";
        cout << specMsg << endl;
        game_over = true;
    }
    if (currentRoom->getRoomID() == 8) {
        game_over = true;
    }
    if (currentRoom->getRoomID() == 9) {
        game_over = true;
    }
}