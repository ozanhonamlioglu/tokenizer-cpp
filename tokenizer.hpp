#pragma once

#include <vector>

#include "utils.hpp"

constexpr unsigned int default_vocab_size = 256;

class Tokenizer {
    const unsigned int vocab_size = 0;
    const std::string &file_name;
    std::vector<int> tokens;
    std::map<int, std::vector<unsigned char> > vocab;
    std::vector<std::pair<std::pair<int, int>, int> > merges;

public:
    Tokenizer(const int vocab_size, const std::string &file_name)
        : vocab_size(vocab_size - default_vocab_size),
          file_name(file_name) {
    }

    void train();

    std::string decode(const std::vector<int> &ids) const;

    std::vector<int> encode(std::string text) const;

private:
    void generateRawTokens();

    std::map<std::pair<int, int>, int> getStats(const std::vector<int> &ids) const;

    std::vector<int> generateTokenWithId(const std::vector<int> &ids, const std::pair<int, int> &pair, size_t idx) const;

    void makeVocab(const std::vector<std::pair<std::pair<int, int>, int> > &merges);

    int getIdxOfPair(const std::pair<int, int>& pair) const;
};
