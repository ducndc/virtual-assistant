#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>

class Block {
public:
    int m_index;
    std::string m_timestamp;
    std::string m_data;
    std::string m_prevHash;
    std::string m_hash;

    Block(int idx, const std::string& d, const std::string& prev)
        : m_index(idx), m_data(d), m_prevHash(prev)
    {
        m_timestamp = currentTime();
        m_hash = calculateHash();
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << m_index << m_timestamp << m_data << m_prevHash;
        return sha256(ss.str());
    }

private:
    std::string currentTime() const {
        time_t now = time(nullptr);
        char buf[100];
        strftime(buf, sizeof(buf), "%F %T", localtime(&now));
        return std::string(buf);
    }

    std::string sha256(const std::string& input) const {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((const unsigned char*)input.c_str(), input.length(), hash);
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        return ss.str();
    }
};

class BlockchainLog {
public:
    BlockchainLog() {
        chain.emplace_back(0, "Genesis Block", "0");
    }

    void addLog(const std::string& message) {
        const Block& last = chain.back();
        chain.emplace_back(last.m_index + 1, message, last.m_hash);
    }

    bool verify() const {
        for (size_t i = 1; i < chain.size(); ++i) {
            const Block& current = chain[i];
            const Block& previous = chain[i - 1];

            if (current.m_hash != current.calculateHash()) {
                std::cerr << "[!] Hash mismatch at block " << i << "\n";
                return false;
            }

            if (current.m_prevHash != previous.m_hash) {
                std::cerr << "[!] PrevHash mismatch at block " << i << "\n";
                return false;
            }
        }
        return true;
    }

    void print() const {
        for (const auto& block : chain) {
            std::cout << "Block #" << block.m_index << "\n"
                      << "  Time: " << block.m_timestamp << "\n"
                      << "  Data: " << block.m_data << "\n"
                      << "  Hash: " << block.m_hash << "\n"
                      << "  Prev: " << block.m_prevHash << "\n\n";
        }
    }

private:
    std::vector<Block> chain;
};
