#include "item.h"

Item::Item() {
	this->itemID = -1;
	this->roomID = -1;
	this->nouns = {};
	this->name = "";
	this->shortDesc = "";
	this->longDesc = "";
	this->canGet = false;
	this->isHidden = false;
	this->isPerson = false;
	this->specs = {};
}


Item::Item(int itemID, int roomID, vector<string> nouns, string name, string shortDesc, string longDesc, bool canGet, bool isHidden, bool isPerson, map<string,int> specs) {
	this->itemID = itemID;
	this->roomID = roomID;
	this->nouns = nouns;
	this->name = name;
	this->shortDesc = shortDesc;
	this->longDesc = longDesc;
	this->canGet = canGet;
	this->isHidden = isHidden;
	this->isPerson = isPerson;
	this->specs = specs;
}

int Item::getItemID() {
	return this->itemID;
}

int Item::getRoomID() {
	return this->roomID;
}

vector<string> Item::getNouns() {
	return this->nouns;
}

string Item::getName() {
	return this->name;
}

string Item::getShortDesc() {
	return this->shortDesc;
}

string Item::getLongDesc() {
	return this->longDesc;
}

bool Item::getCanGet() {
	return this->canGet;
}

bool Item::getIsHidden() {
	return this->isHidden;
}

bool Item::getIsPerson() {
	return this->isPerson;
}

map<string, int> Item::getSpecs() {
	return this->specs;
}

void Item::setItemID(int itemID) {
	this->itemID = itemID;
}

void Item::setRoomID(int roomID) {
	this->roomID = roomID;
}

void Item::setNouns(vector<string> nouns) {
	this->nouns = nouns;
}

void Item::addNoun(string noun) {
	if (find(this->nouns.begin(), this->nouns.end(), noun) != this->nouns.end()) {
		// Noun already exists in vector
		// For debug use only
		std::cout << "Item " << this->itemID << " already has noun '" << noun << "'" << endl;
	} else {
		this->nouns.push_back(noun);
	}
}

void Item::removeNoun(string noun) {
	if (find(this->nouns.begin(), this->nouns.end(), noun) != this->nouns.end()) {
		this->nouns.erase(find(this->nouns.begin(), this->nouns.end(), noun));
	}
	else {
		// Noun does not exist in vector
		// For debug use only
		std::cout << "Item " << this->itemID << " does not have noun '" << noun << "'" << endl;
	}
}

void Item::setName(string name) {
	this->name = name;
}

void Item::setShortDesc(string shortDesc) {
	this->shortDesc = shortDesc;
}

void Item::setLongDesc(string longDesc) {
	this->longDesc = longDesc;
}

void Item::setCanGet(bool canGet) {
	this->canGet = canGet;
}

void Item::setIsHidden(bool isHidden) {
	this->isHidden = isHidden;
}

void Item::setIsPerson(bool isPerson) {
	this->isPerson = isPerson;
}

void Item::setSpecs(map<string, int> specs) {
	this->specs = specs;
}

void Item::addSpec(string word, int specNum) {
	if (this->specs.find(word) != this->specs.end()) {
		// Spec already exists on this item
		// For debug use only
		std::cout << "Item " << this->itemID << " already has spec '{ " << word << ", " << specNum << " }'" << endl;
	}
	else {
		this->specs[word] = specNum;
	}
}

void Item::removeSpec(string word) {
	if (this->specs.find(word) != this->specs.end()) {
		this->specs.erase(word);
	} else {
		// Spec does not exists on this item
		// For debug use only
		std::cout << "Item " << this->itemID << " does not have spec '" << word << "'" << endl;
	}
}