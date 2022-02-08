#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <sstream>
#include <windows.h>
using namespace std;

class Room {
	// todo: room is DT
	int roomID;
	string name;
	string description;
	int n;
	int e;
	int s;
	int w;
	int u;
	int d;

public:
	Room();
	Room(int roomID, string name, string description, int n, int e, int s, int w, int u, int d);
	void setFields(int roomID, string name, string description, int n, int e, int s, int w, int u, int d);
	string getName();
	string getDescription();
	int getRoomID();
	int getN();
	int getE();
	int getS();
	int getW();
	int getU();
	int getD();
	void setName(string name);
	void setDescription(string description);
	void setRoomID(int roomID);
	void setN(int n);
	void setE(int e);
	void setS(int s);
	void setW(int w);
	void setU(int u);
	void setD(int d);
};

