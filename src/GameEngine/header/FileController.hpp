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
         * @brief Melakukan pembacaan file.
         * 
         * TODO: use implement GameException jika folder atau file tidak ditemukan 
         *
         * @param path lokasi file yang akan dibaca
         * @return content : vector<vector<string>> 
        */
        static vector<vector<string>> readFile(string path);

        /**
         * @brief Melakukan penulisan ke file
         * 
         * TODO: use implement GameException jika folder tidak ditemukan
         * 
         * @param content matriks tipe string yang akan ditulis ke dalam file
         * @param file lokasi (path) content akan ditulis
        */
        static void write(vector<vector<string>> content, string file);
};

#endif