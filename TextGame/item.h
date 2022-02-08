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
	bool canGet;
	bool isHidden;
	bool isPerson;
	map<string, int> specs;

public:
	Item();
	Item(int itemID, int roomID, vector<string> nouns, string name, string shortDesc, string longDesc, bool canGet, bool isHidden, bool isPerson, map<string,int> specs);
	int getItemID();
	int getRoomID();
	vector<string> getNouns();
	string getName();
	string getShortDesc();
	string getLongDesc();
	bool getCanGet();
	bool getIsHidden();
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
	void setCanGet(bool canGet);
	void setIsHidden(bool isHidden);
	void setIsPerson(bool isPerson);
	void setSpecs(map<string, int> specs);
	void addSpec(string word, int specNum);
	void removeSpec(string word);
};

