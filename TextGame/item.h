#pragma once
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <sstream>
#include <windows.h>

class Item {
private:
	int itemID;
	int roomID;
	vector<string> nouns;
	string name;
	string shortDesc;
	string longDesc;
	int getState;
	int hiddenState;
	bool isPerson;
	map<string, int> specs;

	// GET STATE
	// 0 = cannot pick up
	// 1 = can pick up
	// 2 = no reason to pick that up

	// HIDDEN STATE
	// 0 = not hidden
	// 1 = hidden, will try to pick up with 'get all'
	// 2 = hidden, will not try to pick up with 'get all' but can try to pick up specifically
	// 3 = hidden, will display 'You do not see that here' when trying to pick up specifically

public:
	Item();
	Item(int itemID, int roomID, vector<string> nouns, string name, string shortDesc, string longDesc, int getState, int hiddenState, bool isPerson, map<string,int> specs);
	int getItemID();
	int getRoomID();
	vector<string> getNouns();
	string getName();
	string getShortDesc();
	string getLongDesc();
	int getGetState();
	int getHiddenState();
	bool getIsPerson();
	map<string, int> getSpecs();
	void setItemID(int itemID);
	void setRoomID(int roomID);
	void setNouns(vector<string> nouns);
	void addNoun(string noun);
	void removeNoun(string noun);
	void setName(string name);
	void setShortDesc(string shortDesc);
	void setLongDesc(string longDesc);
	void setGetState(int getState);
	void setHiddenState(int hiddenState);
	void setIsPerson(bool isPerson);
	void setSpecs(map<string, int> specs);
	void addSpec(string word, int specNum);
	void removeSpec(string word);
};
