CC = g++

csv_reader: main.o csvreader.o
	$(CC) -o csv_reader.exe main.o csvreader.o
csvreader.o: csvreader.cpp csvreader.h
	$(CC) -c csvreader.cpp
main.o: main.cpp csvreader.h
	$(CC) -c main.cpp
clean:
	del /S *.o