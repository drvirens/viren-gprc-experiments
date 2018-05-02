//
//  CSVFileLineTokenizer.cpp
//  test_ReadCSV
//
//  Created by Virendra Shakya on 5/1/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//


#include <iostream>
#include <sstream>
#include "CSVFileLineTokenizer.hpp"


static int kLongtitudeIndex = 0;
static int kLatitudeIndex = 1;
static int kMemberDataIndex = 2;


CSVFileLineTokenizer::CSVFileLineTokenizer() {

}

CSVFileLineTokenizer::~CSVFileLineTokenizer() {

}

void CSVFileLineTokenizer::didReadLine(const std::string& line, int lineNumber) const {
    parseLine(line, lineNumber);
}


void CSVFileLineTokenizer::didReadOneEntry(std::string& longitude, std::string& latitude, std::string& member) const {
//#if __DEBUG_ALL__
    std::cout << "longitude: [" << longitude << "], latitude: [" << latitude << "], member: [" << member  << "]" << std::endl;
//#endif
}

void CSVFileLineTokenizer::parseLine(const std::string& line, int lineNumber) const {
    std::istringstream ss(line);
    std::string token;
    int index = 0;
    
    std::string longitude;
    std::string latitude;
    std::string member;
    
    while(std::getline(ss, token, ',')) {
        if (kLongtitudeIndex == index) {
            longitude = token;
        } else if (kLatitudeIndex == index) {
            latitude = token;
        } else if (kMemberDataIndex == index) {
            std::stringstream memberstr;
            memberstr << lineNumber << ":" << token;
            member = memberstr.str();
            didReadOneEntry(longitude, latitude, member);
        }
        index++;
    }
}
