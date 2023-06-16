/**
 * Author : Chung Duc Nguyen Dang
 * Email  : nguyendangchungduc1999@gmail.com
 *  
*/

#include "record.hpp"

void Record::printRecord()
{
    std::cout << "Phrase: " << m_phrase << std::endl;
    std::cout << "Responses: " << std::endl;

    for (int i = 0; i < m_response.size(); i++)
    {
        std::cout << '\t' << m_response.at(i) << std::endl;
    }
}