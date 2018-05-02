//
//  CSVFileReaderListener.hpp
//  test_ReadCSV
//
//  Created by Virendra Shakya on 5/1/18.
//  Copyright © 2018 Virendra Shakya. All rights reserved.
//

#ifndef CSVFileReaderListener_hpp
#define CSVFileReaderListener_hpp

class CSVFileReaderListener {
 public:
    virtual void didReadLine(const std::string& line, int lineNumber) const = 0;
};

#endif /* CSVFileReaderListener_hpp */
