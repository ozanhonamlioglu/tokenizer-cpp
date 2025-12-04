#include "tokenizer.hpp"

#include "performance.hpp"

void Tokenizer::train() {
    printf("* Training started\n");

    const auto start = performance::startPerf(std::nullopt);

    generateRawTokens();

    std::vector<std::pair<std::pair<int, int>, int> > merges;
    auto mTokens = tokens;

    for (int i = 0; i < vocab_size; ++i) {
        auto stats = getStats(mTokens);
        auto max = utils::getMax(stats);
        const size_t idx = default_vocab_size + i;
        mTokens = merge(mTokens, max, idx);
        merges.push_back(std::pair<std::pair<int, int>, int>(max, idx));
        // printf("merging: (%i, %i) -> %lu\n", max.first, max.second, idx);
    }

    performance::endPerf(start);

    makeVocab(merges);
}

std::map<std::pair<int, int>, int> Tokenizer::getStats(const std::vector<int> &ids) {
    std::map<std::pair<int, int>, int> counted_pairs = {};

    for (size_t i = 0; i < ids.size() - 1; ++i) {
        std::pair<int, int> key = {ids[i], ids[i + 1]};
        counted_pairs[key]++;
    }

    return counted_pairs;
}

void Tokenizer::generateRawTokens() {
    auto file_content = utils::readFile(this->file_name);

    for (unsigned char byte_value: file_content) {
        const int integer_val = static_cast<int>(byte_value);
        tokens.push_back(integer_val);
    }
}

std::vector<int> Tokenizer::merge(const std::vector<int> &ids, const std::pair<int, int> &pair, size_t idx) {
    std::vector<int> newIds;

    for (size_t i = 0; i < ids.size() - 1; ++i) {
        if (ids.size() > 1 && ids[i] == pair.first && ids[i + 1] == pair.second) {
            newIds.push_back(idx);
            ++i;
        } else {
            newIds.push_back(ids[i]);
        }
    }

    return newIds;
}

void Tokenizer::makeVocab(const std::vector<std::pair<std::pair<int, int>, int> > &merges) {
    for (int idx = 0; idx < default_vocab_size; ++idx) {
        auto byte_pair = {static_cast<unsigned char>(idx)};
        vocab[idx] = byte_pair;
    }

    for (const auto entry: merges) {
        auto byte_pair = {
            static_cast<unsigned char>(entry.first.first), static_cast<unsigned char>(entry.first.second)
        };
        vocab[entry.second] = byte_pair;
    }
}
