#include "program.h"

Program::Program() {
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
                        std::cout << item_list[i]->getShortDesc() << std::endl;
                    }
                }
            }
            color(0x0e);
            for (int i = 0; i < item_list.size(); i++) {
                if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                    if (item_list[i]->getIsPerson() == false) {
                        std::cout << item_list[i]->getShortDesc() << std::endl;
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
        printExits();
        moved = false;
        std::getline(cin, userInput);
        parseCommand(toLower(userInput));
	}
}

void Program::setupWorld() {
    string r1desc = 
        // "Torrents of cascading molten rock flow swiftly from the falls behind you,\n"
        // "superheating the ground and reminding you that there is no hope of returning that way."
        "Molten lavafalls pound the landscape here. A rocky promontory continues to\n"
        "the east, while back to the west lie the falls themselves.";

    string r2desc =
        "This east-west outcrop of rock continues.";

    string r3desc =
        "The rocky ledge makes a sharp turn towards the north here.";

    string r4desc =
        "The rocky ledge seems to end here.";

    string r5desc =
        "This north-south passage is old and musty from years of neglect.";

    Room* r1 = new Room(1, "The Lava Falls", r1desc, -1, 2, -1, -1, -1, -1);
    Room* r2 = new Room(2, "A Rocky Ledge", r2desc, -1, 3, -1, 1, -1, -1);
    Room* r3 = new Room(3, "A Turn on the Ledge", r3desc, 4, -1, -1, 2, -1, -1);
    Room* r4 = new Room(4, "Before an Ancient Stone Door", r4desc, -1, -1, 3, -1, -1, -1);
    Room* r5 = new Room(5, "A Long Forgotten Passage", r5desc, -1, -1, 4, -1, -1, -1);
    Room* r6 = new Room(6, "Room6", "Description of room goes here", -1, -1, -1, -1, -1, -1);
    Room* r7 = new Room(7, "Room7", "Description of room goes here", -1, -1, -1, -1, -1, -1);
    Room* r8 = new Room(8, "Room8", "Description of room goes here", -1, -1, -1, -1, -1, -1);
    Room* r9 = new Room(9, "Room9", "Description of room goes here", -1, -1, -1, -1, -1, -1);
    room_list.push_back(r1);
    room_list.push_back(r2);
    room_list.push_back(r3);
    room_list.push_back(r4);
    room_list.push_back(r5);
    room_list.push_back(r6);
    room_list.push_back(r7);
    room_list.push_back(r8);
    room_list.push_back(r9);

    string sItemDesc1 =
        "A crumpled piece of paper flutters on an unseen breeze.";

    string lItemDesc1 =
        "Sample Text";

    string sItemDesc2 =
        "An ancient stone door stands here, blocking passage.";

    string lItemDesc2 =
        "Intricate stone carvings span the height of this ancient doorway. It\n"
        "currently bars passage to the north, yet you feel there must be some way\n"
        "to open it.";

    string sItemDesc3 =
        "A hopelessly lost adventurer ambles along weakly.";

    string lItemDesc3 =
        "He looks like he's been here for a while.";

    Item* item1 = new Item(1, 3, { "paper", "folded", "parchment", "crumpled" }, "a crumpled piece of paper", sItemDesc1, lItemDesc1, true, false, false, {});
    map<string, int> map;
    map["push"] = 1;
    map["bash"] = 2;
    Item* item2 = new Item(2, 4, { "door", "stone", "ancient" }, "the ancient stone door", sItemDesc2, lItemDesc2, false, false, false, map);

    map = {};
    map["listen"] = 3;
    Item* item3 = new Item(3, 5, { "lost", "adventurer" }, "the lost adventurer", sItemDesc3, lItemDesc3, false, false, true, map);

    item_list.push_back(item1);
    item_list.push_back(item2);
    item_list.push_back(item3);

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
                }
            }
            // Item in inventory
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
    commands = { "north", "east", "south", "west", "up", "down", "look", "get", "take", "drop", "inventory"};
}

void Program::setupFunctionMap() {
    functionMap["north"] = &Program::move;
    functionMap["east"] = &Program::move;
    functionMap["south"] = &Program::move;
    functionMap["west"] = &Program::move;
    functionMap["up"] = &Program::move;
    functionMap["down"] = &Program::move;
    functionMap["look"] = &Program::look;
    functionMap["get"] = &Program::get;
    functionMap["take"] = &Program::get;
    functionMap["drop"] = &Program::drop;
    functionMap["inventory"] = &Program::inventory;
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
                    if (item_list[i]->getCanGet() == true) {
                        count++;
                        std::cout << "\nYou get " << item_list[i]->getName() << "." << endl;
                        invSize++;
                        item_list[i]->setRoomID(0);
                    } else {
                        std::cout << "\nYou can't seem to get " << item_list[i]->getName() << "." << endl;
                        count++;
                    }
                }
            }
        }
        if (count == 0) {
            std::cout << "\nYou can't seem to find anything to pick up." << std::endl;
        }
    } else {
        for (int i = 0; i < item_list.size(); i++) {
            if (item_list[i]->getIsPerson() == false) {
                if (item_list[i]->getRoomID() == currentRoom->getRoomID()) {
                    for (int j = 0; j < item_list[i]->getNouns().size(); j++) {
                        if (item_list[i]->getNouns()[j] == noun) {
                            if (item_list[i]->getCanGet() == true) {
                                std::cout << "\nYou get " << item_list[i]->getName() << "." << endl;
                                invSize++;
                                item_list[i]->setRoomID(0);
                                return;
                            } else {
                                std::cout << "\nYou can't seem to get " << item_list[i]->getName() << "." << endl;
                                return;
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
            ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        cout << "\nYou push on the door, but it doesn't budge." << endl;
                        return;
                    }
                }
            }
            cout << "Huh?!" << endl;
            return;
        }
        case 2: {
            ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        cout << "\nYou bash on the door, and it falls over, revealing a passage to the north." << endl;
                        for (int i = 0; i < room_list.size(); i++) {
                            if (room_list[i]->getRoomID() == 4) {
                                room_list[i]->setN(5);
                                room_list[i]->setDescription("The rocky ledge now continues to the north.");
                            }
                        }
                        for (int j = 0; j < item_list.size(); j++) {
                            if (item_list[j]->getItemID() == 2) {
                                item_list[j]->removeSpec("push");
                                item_list[j]->removeSpec("bash");
                                item_list[j]->setName("the destroyed stone door");
                                item_list[j]->setNouns({ "remains", "destroyed", "stone", "door", "ancient", "shatered" });
                                item_list[j]->setShortDesc("The shattered remains of what was once a door lie scattered here.");
                                item_list[j]->setLongDesc("After the hefty bash inflicted upon it, this door now lies in pieces.");
                            }
                        }
                        return;
                    }
                }
            }
            cout << "Huh?!" << endl;
            return;
        }
        case 3: {
            ignoreOutput(v, 2);
            if (v.size() >= 2) {
                for (int i = 0; i < item->getNouns().size(); i++) {
                    if (v[1] == item->getNouns()[i]) {
                        string specMsg =
                            "\n        Hello there. I suppose you're wondering how I ended up here. Well,\n"
                            "    I was exploring this ancient temple, you see, when the ground opened up\n"
                            "    and swallowed me whole! I must've landed softly, since I haven't broken\n"
                            "    any bones, but the whole ordeal must've made me lose consciousness.\n\n"
                            "        When I awoke, I found myself down here, with my back to a fiery\n"
                            "    mountain and a dark tunnel ahead. I should've tried to climb back up\n"
                            "    when I had the chance, because the next thing I knew, the door over\n"
                            "    there swung itself closed, trapping me behind it. I've been pounding\n"
                            "    at it for days, but I was too weak to knock it down. Good thing you\n"
                            "    showed up when you did, because I really need to get out of here...\n\n"
                            "The adventurer pushes past you to the south, heading for the lava falls.";
                        cout << specMsg << endl;
                        item->setRoomID(1);
                        return;
                    }
                }
            }
            cout << "Huh?!" << endl;
            return;
        }
        default: {
            cout << "Error!" << endl;
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
                }
            }
        }
    }
}