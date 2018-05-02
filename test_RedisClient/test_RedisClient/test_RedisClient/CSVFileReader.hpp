//
//  CSVFileReader.hpp
//  test_ReadCSV
//
//  Created by Virendra Shakya on 5/1/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef CSVFileReader_hpp
#define CSVFileReader_hpp

#include <string>
#include <fstream>
#include "CSVFileReaderListener.hpp"

class CSVFileReader final {
 public:
    CSVFileReader(const CSVFileReaderListener& listener, const std::string& csvfile);
    ~CSVFileReader();
    void read();
    
 private:
    void parseLine(const std::string& line, int lineNumber);
    
 private:
    const CSVFileReaderListener& listener_;
    std::ifstream filestream_;
};

#endif /* CSVFileReader_hpp */
