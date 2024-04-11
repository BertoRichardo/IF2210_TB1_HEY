#include "../header/Config.hpp"
#include <iostream>
#include <string>
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

int Config::getID() const {
    return this->id;
}

void Config::setID(int id) {
    this->id = id;
}

string Config::getKodeHuruf() const {
    return this->kode_huruf;
}

void Config::setKodeHuruf(string kode_huruf) {
    this->kode_huruf = kode_huruf;
}

string Config::getNama() const {
    return this->nama;
}

void Config::setNama(string nama) {
    this->nama = nama;
}

int Config::getPrice() const {
    return this->price;
}

void Config::setPrice(int price) {
    this->price = price;
}