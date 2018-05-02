//
//  main.cpp
//  test_ReadCSV
//
//  Created by Virendra Shakya on 5/1/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//


#include "CSVFileLineTokenizer.hpp"
#include "CSVFileReader.hpp"
#include "CSVFileLineTokenizer.hpp"


static void parseStarbucks() {
    const CSVFileLineTokenizer tokenizer;
    const std::string csvfile = "starbucks_us_locations_original.csv";
    CSVFileReader csv(tokenizer, csvfile);
    csv.read();
}

int main(int argc, const char * argv[]) {
    //readAllEntriesFromCSV("starbucks_us_locations_original.csv");
    parseStarbucks();
    return 0;
}
