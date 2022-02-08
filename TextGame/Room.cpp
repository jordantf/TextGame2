#include "Room.h"

Room::Room() {
	this->roomID = -1;
	this->name = "Room Name";
	this->description = "Room description goes here";
	this->n = -1;
	this->e = -1;
	this->s = -1;
	this->w = -1;
	this->u = -1;
	this->d = -1;
}

Room::Room(int roomID, string name, string description, int n, int e, int s, int w, int u, int d) {
	this->roomID = roomID;
	this->name = name;
	this->description = description;
	this->n = n;
	this->e = e;
	this->s = s;
	this->w = w;
	this->u = u;
	this->d = d;
}

void Room::setFields(int roomID, string name, string description, int n, int e, int s, int w, int u, int d) {
	this->roomID = roomID;
	this->name = name;
	this->description = description;
	this->n = n;
	this->e = e;
	this->s = s;
	this->w = w;
	this->u = u;
	this->d = d;
}

string Room::getName() {
	return this->name;
}

string Room::getDescription() {
	return this->description;
}

int Room::getRoomID() {
	return this->roomID;
}

int Room::getN() {
	return this->n;
}

int Room::getE() {
	return this->e;
}

int Room::getS() {
	return this->s;
}

int Room::getW() {
	return this->w;
}
int Room::getU() {
	return this->u;
}

int Room::getD() {
	return this->d;
}

void Room::setName(string name) {
	this->name = name;
}

void Room::setDescription(string description) {
	this->description = description;
}

void Room::setRoomID(int roomID) {
	this->roomID = roomID;
}

void Room::setN(int n) {
	this->n = n;
}

void Room::setE(int e) {
	this->e = e;
}

void Room::setS(int s) {
	this->s = s;
}

void Room::setW(int w) {
	this->w = w;
}

void Room::setU(int u) {
	this->u = u;
}

void Room::setD(int d) {
	this->d = d;
}