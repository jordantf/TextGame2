#pragma once
#include "Room.h"
#include "item.h"

class Program {
private:
	bool game_over;
	bool moved;
	Room* currentRoom;
	vector<Room*> room_list;
	vector<Item*> item_list;
	int invSize;
	vector<string> commands;
	std::map<std::string, void (Program::*)(vector<string>)> functionMap;

	void setupWorld();
	void printExits();
	Room* getRoom(int id);
	void parseCommand(string userInput);
	void setupCommands();
	void setupFunctionMap();

	// Player actions
	void move(vector<string> v);
	void look(vector<string> v);
	void help(vector<string> v);
	void get(vector<string> v);
	void inventory(vector<string> v);
	void drop(vector<string> v);
	void special(vector<string> v, Item* item);
	void restart(vector<string> v);

	// Helper functions for actions
	void look_at(string noun);
	void handleGet(string noun);
	void handleDrop(string noun);
	void checkSpecs();

	// util functions
	int is_abbrev(string str, string substr);
	string toLower(const string& val);
	void color(int color);
	void ignoreOutput(vector<string> v, int i);

public:
	Program();
	void run();
};

// ROOM NUMBER OF 0 = INVENTORY
// ROOM NUMBER OF -1 = PLACEHOLDER FOR NO ROOM


