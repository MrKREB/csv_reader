#include "csvreader.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "No name of the file\n";
        return -1;
    }

    string filename = argv[1];

    CsvReader csv_reader;
    if (csv_reader.read_csv(filename))
        return -2;

    csv_reader.calc_vals();
    csv_reader.print_csv();

    return 0;
}
