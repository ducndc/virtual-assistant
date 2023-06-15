/**
 * Author : Chung Duc Nguyen Dang
 * Email  : nguyendangchungduc1999@gmail.com
 * 
*/

#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

vector<string> split(string strToSplit, char delimeter);
size_t levenshteinDistance(const string &s1, const string &s2);

void trimLeading(string &str);
void trimTrailing(string &str);
void trim(string &str);

#endif /* STRING_UTILS_HPP */