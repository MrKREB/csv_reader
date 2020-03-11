#include "csvreader.h"

CsvReader::CsvReader()
{

}

int CsvReader::get_col(string head){
    vector <string> vec = vals[keys[0]];
    auto iter = find(vec.begin(), vec.end(), head);
    auto index = distance(vec.begin(), iter);

    if(index == vec.size())
        return -1;

    return index;
}

int CsvReader::get_operand(string &val)
{
    int res, i = 1, j = 1;

    while (isalpha(val[i]))
        i++;

    string head = val.substr(1, i-1);
    int col = get_col(head);

    if (col == -1) {
        cerr << "Incorrect column header: " << val << endl;
        return -1;
    }

    while (isdigit(val[i+j]))
        j++;

    string rw = val.substr(i, j);

    try {
        res = stoi(vals[rw][col]);
    } catch (const invalid_argument & e) {
        cerr << e.what() << ": value is not digit: " << val << endl;
        return -1;
    }

    val = val.substr(i+j, val.size()-i-j);
    return res;
}

int CsvReader::calc_expr(string val) {
    int op1, op2, result;

    op1 = get_operand(val);

    if (op1 < 0)
        return -1;

    char op = val[0];
    op2 = get_operand(val);

    if (op2 < 0)
        return -1;
    else if (op2 == 0) {
        cerr << "Division by zero\n";
        return -1;
    }

    switch(op) {
        case '+': result = op1 + op2; break;
        case '-': result = op1 - op2; break;
        case '*': result = op1 * op2; break;
        case '/': result = op1 / op2; break;
    }

    if (result < 0) {
        cerr << "File can contain only positive integer values" << endl;
        return -1;
    }

    return result;
}

void CsvReader::calc_vals(){
    for (auto& pair: vals)
        for (auto& v: pair.second)
            if (v[0] == '=') {
                int temp = calc_expr(v);

                if (temp < 0)
                    continue;

                v = to_string(temp);
            }
}

int CsvReader::read_csv(string filename)
{
    ifstream fin(filename);

    if (!fin) {
          cerr << "No file with name: " << filename << endl;
          return -1;
    }

    vector<string> row;
    string line, word;

    while (fin.good()) {
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ','))
            row.push_back(word);

        string key = row[0];
        row.erase(row.begin());
        vals[key] = row;
        keys.push_back(key);
        row.clear();
    }

    fin.close();

    return 0;
}

map<string, vector<string>> CsvReader::get_vals(){
    return vals;
}

void CsvReader::print_csv() {
    for (auto& key: keys) {
        cout << key << ',';

        for (auto& v: vals[key]){
            cout << v;

            if (vals[key].back() != v)
                cout << ',';
        }

        cout << endl;
    }
}
