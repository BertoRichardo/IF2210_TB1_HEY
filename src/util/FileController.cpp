#include "FileController.hpp"

vector<string> split (const string &s, char delimeter) {
    vector<string> tokens;
    std::stringstream ss(s);
    string token;

    while (getline(ss, token, delimeter)) {
        tokens.push_back(token);
    }

    return tokens;
}

vector<vector<string>> FileController::readFile(string path) {
    vector<vector<string>> elements;

    fstream file;
    file.open(path, ios::in);
    if (file.is_open()) {
        string line;
        int i = 0;
        while (getline(file, line)) {
            vector<string> this_line;
            this_line = split(line, ' ');
            elements.push_back(this_line);
        }
    }
    file.close();
    return elements;
}

void FileController::write(vector<vector<string>> content, string file) {
    ofstream outfile(file);

    if (outfile.is_open()) {
        for (auto i = content.begin(); i != content.end(); i++) {
            for (auto j = i->begin(); j != i->end(); j++) {
                outfile << *j;
                if (++j != i->end()) {
                    outfile << " ";
                }
                j--;
            }
            outfile << endl;
        }
        outfile.close();
    }
}