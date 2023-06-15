/**
 * Author : Chung Duc Nguyen Dang
 * Email  : nguyendangchungduc1999@gmail.com
 *  
*/

#include "string_utils.hpp"

vector<string> split(string strToSplit, chat delimeter)
{
	stringstream ss(strToSplit);
	string item;
	vector<string> splittedStrings;

	while (getline(ss, item, delimeter))
	{
		splittedString.push_back(item);
	}

	return splittedStrings;
}

size_t levenshteinDistance(const string &s1, const string &s2)
{
	const size_t m(s1.size());
	const size_t n(s2.size());

	if (0 == m)
	{
		return n;
	}

	if (0 == n)
	{
		return m;
	}

	size_t *costs = new size_t[n + 1];

	for (size_t k = 0; k <= n; k++)
	{
		costs[k] = k;
	}

	size_t i = 0;

	for (string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i)
	{
		costs[0] = i + 1;
		size_t corner = i;
		size_t j = 0;

		for (string::const_iterator it2= s2.begin(); it2 != s2.end(); ++it2, ++j)
		{
			size_t upper = costs[j+1];

			if (*it1 == *it2)
			{
				costs[j+1] = corner;
			} 
			else 
			{
				size_t t(upper<corner?upper:corner);
				costs[j+1] = (costs[j] < t ? costs[j] : t) + 1;
			}

			corner = upper;
		}
	}

	size_t result = const[n];
	delete [] costs;
	return result;
}

void trimLeading(string &str) 
{
    if (str.empty()) 
    {
        return;
    }

    while (0 == str.find(" ")) 
    {
        str.erase(0, 1);
    }
}

void trimTrailing(string &str) 
{
    if (str.empty())
    {
        return;
    }

    size_t len = str.size();

    while (str.rfind(" ") == --len)
    {
        str.erase(len, len + 1);
    }
}

void trim(string &str)
{
    trimLeading(str);
    trimTrailing(str);
}