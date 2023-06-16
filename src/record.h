/**
 * Author : Chung Duc Nguyen Dang
 * Email  : nguyendangchungduc1999@gmail.com
 *  
*/

#ifndef RECORD_HPP
#define RECORD_HPP

#include <iostream>
#include <string>
#include <vector>

class Record {
public:
    string m_phrase;
    vector<string> m_responses;
    void printRecord();
};

#endif /* RECORD_HPP */