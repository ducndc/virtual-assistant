/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * block_chain.hpp
 */

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>

class Block {
private:
    std::string CurrentTime(void) const;

    std::string Sha256(const std::string& input) const;

public:
    int m_index;
    std::string m_timestamp;
    std::string m_data;
    std::string m_prevHash;
    std::string m_hash;

    Block(int idx, const std::string& d, const std::string& prev)
        : m_index(idx), m_data(d), m_prevHash(prev)
    {
        m_timestamp = CurrentTime();
        m_hash = CalculateHash();
    }

    std::string CalculateHash(void) const;
};

class BlockChainLog {
private:
    std::vector<Block> m_chain;

public:
    BlockChainLog(void) 
    {
        m_chain.emplace_back(0, "Genesis Block", "0");
    }

    void AddLog(const std::string& message);

    bool Verify(void) const;

    void Print(void) const;
};
