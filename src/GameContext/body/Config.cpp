#include "../header/Config.hpp"
#include <iostream>
using namespace std;

Config::Config() {
    this->id = 0;
    this->kode_huruf = "";
    this->nama = "";
    this->price = 0;
}

Config::Config(int id, string kode_huruf, string nama, int price) {
    this->id = id;
    this->kode_huruf = kode_huruf;
    this->nama = nama;
    this->price = price;
}

int Config::getID() {
    return this->id;
}

void Config::setID(int id) {
    this->id = id;
}

string Config::getKodeHuruf() {
    return this->kode_huruf;
}

void Config::setKodeHuruf(string kode_huruf) {
    this->kode_huruf = kode_huruf;
}

string Config::getNama() {
    return this->nama;
}

void Config::setNama(string nama) {
    this->nama = nama;
}

int Config::getPrice() {
    return this->price;
}

void Config::setPrice(int price) {
    this->price = price;
}