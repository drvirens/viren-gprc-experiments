//
//  CSVFileLineTokenizer.hpp
//  test_ReadCSV
//
//  Created by Virendra Shakya on 5/1/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef CSVFileLineTokenizer_hpp
#define CSVFileLineTokenizer_hpp

#include <string>
#include "CSVFileReaderListener.hpp"

class CSVFileLineTokenizer : public CSVFileReaderListener {
 public:
    CSVFileLineTokenizer();
    ~CSVFileLineTokenizer();
    virtual void didReadLine(const std::string& line, int lineNumber) const;
    virtual void didReadOneEntry(std::string& longitude, std::string& latitude, std::string& member) const;
    
 private:
    void tokenize(std::string& longitude, std::string& latitude, std::string& member) const;
    void parseLine(const std::string& line, int lineNumber) const;
};

#endif /* CSVFileLineTokenizer_hpp */
