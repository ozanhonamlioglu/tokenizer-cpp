#pragma once

#include <vector>

#include "utils.hpp"

constexpr unsigned int default_vocab_size = 256;

class Tokenizer {
    const unsigned int vocab_size = 0;
    const std::string &file_name;
    std::vector<int> tokens;
    std::map<int, std::vector<unsigned char> > vocab;

public:
    Tokenizer(const int vocab_size, const std::string &file_name)
        : vocab_size(vocab_size - default_vocab_size),
          file_name(file_name) {
    }

    void train();

private:
    void generateRawTokens();

    std::map<std::pair<int, int>, int> getStats(const std::vector<int> &ids);

    std::vector<int> merge(const std::vector<int> &ids, const std::pair<int, int> &pair, size_t idx);

    void makeVocab(const std::vector<std::pair<std::pair<int, int>, int> > &merges);
};
