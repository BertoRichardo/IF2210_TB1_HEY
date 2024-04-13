#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <string>
#include <vector>
#include <iostream>
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
};

#endif