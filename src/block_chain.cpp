/**
 * Author   : Chung Duc Nguyen Dang
 * Email    : nguyendangchungduc1999@gmail.com
 * 
 * block_chain.cpp
 */

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>

#include "block_chain.hpp"

std::string 
Block::CalculateHash(void) const 
{
    std::stringstream ss;
    ss << m_index << m_timestamp << m_data << m_prevHash;

    return Sha256(ss.str());
}

std::string 
Block::CurrentTime(void) const 
{
    time_t now = time(nullptr);
    char buf[100];
    strftime(buf, sizeof(buf), "%F %T", localtime(&now));

    return std::string(buf);
}

std::string 
Block::Sha256(
    const std::string& input) const 
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.length(), hash);
    std::stringstream ss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str();
}

void 
BlockChainLog::AddLog(
	const std::string& message) 
{
    const Block& last = m_chain.back();
    m_chain.emplace_back(last.m_index + 1, message, last.m_hash);
}

bool 
BlockChainLog::Verify(void) const 
{
    for (size_t i = 1; i < m_chain.size(); ++i) 
    {
        const Block& current = m_chain[i];
        const Block& previous = m_chain[i - 1];

        if (current.m_hash != current.CalculateHash()) 
        {
            std::cerr << "[!] Hash mismatch at block " << i << "\n";
            return false;
        }

        if (current.m_prevHash != previous.m_hash) 
        {
            std::cerr << "[!] PrevHash mismatch at block " << i << "\n";
            return false;
        }
    }

    return true;
}

void 
BlockChainLog::Print(void) const 
{
    for (const auto& block : m_chain) 
    {
        std::cout << "Block #" << block.m_index << "\n"
                  << "  Time: " << block.m_timestamp << "\n"
                  << "  Data: " << block.m_data << "\n"
                  << "  Hash: " << block.m_hash << "\n"
                  << "  Prev: " << block.m_prevHash << "\n\n";
    }
}