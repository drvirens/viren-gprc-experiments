//
//  CSVFileReader.cpp
//  test_ReadCSV
//
//  Created by Virendra Shakya on 5/1/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "CSVFileReader.hpp"

#define LINE_SIZE 2*1024

CSVFileReader::CSVFileReader(const CSVFileReaderListener& listener,
                        const std::string& csvfile)
    : listener_(listener)
    , filestream_(csvfile) {
}

CSVFileReader::~CSVFileReader() {
    filestream_.close();
}

void CSVFileReader::read() {
    if (!filestream_) {
        std::cout << "Can not open file" << std::endl;
        return;
    }

    char line[LINE_SIZE] = {0};
    int lineNumber = 0;
    while (filestream_) {
        filestream_.getline(line, LINE_SIZE);
        if (filestream_) {
#if __DEBUG_ALL__
            cout << line << endl;
#endif
            parseLine(line, lineNumber++);
        }
    } //end while
    filestream_.close();
}

void CSVFileReader::parseLine(const std::string& line, int lineNumber) {
    listener_.didReadLine(line, lineNumber);
}

