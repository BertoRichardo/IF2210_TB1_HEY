#ifndef _FILECONTROLLER_HPP_
#define _FILECONTROLLER_HPP_

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class FileController {
    public:
        /**
         * Melakukan pembacaan file 
         * @param path lokasi file yang akan dibaca
        */
        static vector<vector<string>> readFile(string path);

        /**
         * Melakukan penulisan ke file
         * @param content matriks tipe string yang akan ditulis ke dalam file
         * @param file lokasi (path) content akan ditulis
        */
        static void write(vector<vector<string>> content, string file);
};

#endif