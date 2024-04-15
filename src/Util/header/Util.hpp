#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include "../../GameObject/header/Plant.hpp"
#include "../../GameObject/header/Animal.hpp"
#include "../../GameObject/header/Building.hpp"
#include "../../GameObject/header/Product.hpp"
using namespace std;

class Util
{
public:
    /**
     * Meng-convert string koordinat menjadi pair<row,col>
     * Indexing string dimulai dari 1
     * @param koordinat
     * @return Item pada cell tersebut : T
     */
    static pair<int, int> strToRowCol(string koordinat);

    /**
     * @param in : input koordinat, separated by comma
     * @return vector of koordinat
     */
    static vector<string> parserSlots(string in);

    /**
     * @return persen pajak berdasarkan kekayaan kena pajak
     */
    static int persenPajak(int kkp);

    /**
     * @param in int masukan user
     * @return hasil convert dari angka huruf : 1 -> a
     * handle hingga 26 * 26 + 26
     */
    static string angkaToHuruf(int in);

    /**
     * obj is not Null
     * @param obj
     * @return item as one of the child of gameObject
     */
    static GameObject *callCCtor(GameObject *obj);

    /**
     * @return true jika urutan int naik. Jika sama, return true jika urutan pair string turun
     */
    static bool customComparator(const pair<int, pair<string, string>> &a, const pair<int, pair<string, string>> &b);

    static void clearScreen();

    static void waitScreen(int ms);

    static void displayStartingScreen();

    static bool containSpace(string s);

    /**
     * Meng-convert row col menjadi string coordinate
     * Indexing string dimulai dari 1
     * @param row: int
     * @param col: int
     * @return coordinate: string
     */
    static string rowColToStr(int row, int col);
};

#endif