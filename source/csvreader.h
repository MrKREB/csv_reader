#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

class CsvReader
{
private:
    map<string, vector<string>> vals;
    vector<string> keys;

    int calc_expr(string val);
    int get_operand(string& val);
    int get_col(string head);

public:
    CsvReader();
    int read_csv(string filename);
    map<string, vector<string>> get_vals();
    void calc_vals();
    void print_csv();
};

#endif // CSVREADER_H
