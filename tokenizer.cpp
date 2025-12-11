#include "tokenizer.hpp"

#include "performance.hpp"

void Tokenizer::train() {
    printf("* Training started\n");

    const auto start = performance::startPerf(std::nullopt);

    generateRawTokens();

    std::vector<std::pair<std::pair<int, int>, int> > _merges;
    auto mTokens = tokens;

    for (int i = 0; i < vocab_size; ++i) {
        auto stats = getStats(mTokens);

        // get the max repeated token and assign it the lowest idx, in this case initially idx=257 and continues
        auto max = utils::getMax(stats);
        const size_t idx = default_vocab_size + i;

        mTokens = generateTokenWithId(mTokens, max, idx);
        _merges.push_back(std::pair<std::pair<int, int>, int>(max, idx));
        // printf("merging: (%i, %i) -> %lu\n", max.first, max.second, idx);
    }

    performance::endPerf(start);

    merges = _merges;
    makeVocab(_merges);
}

std::map<std::pair<int, int>, int> Tokenizer::getStats(const std::vector<int> &ids) const {
    std::map<std::pair<int, int>, int> counted_pairs = {};

    for (size_t i = 0; i < ids.size() - 1; ++i) {
        std::pair<int, int> key = {ids[i], ids[i + 1]};
        counted_pairs[key]++;
    }

    return counted_pairs;
}

void Tokenizer::generateRawTokens() {
    std::vector<unsigned char> file_content = utils::readFile(this->file_name);

    for (unsigned char byte_value: file_content) {
        const int integer_val = static_cast<int>(byte_value);
        tokens.push_back(integer_val);
    }
}

std::vector<int> Tokenizer::generateTokenWithId(const std::vector<int> &ids, const std::pair<int, int> &pair,
                                                size_t idx) const {
    std::vector<int> newIds;

    for (size_t i = 0; i < ids.size(); ++i) {
        if (ids.size() > 1 && ids[i] == pair.first && ids[i + 1] == pair.second) {
            newIds.push_back(idx);
            ++i;
        } else {
            newIds.push_back(ids[i]);
        }
    }

    return newIds;
}

void Tokenizer::makeVocab(const std::vector<std::pair<std::pair<int, int>, int> > &_merges) {
    for (int idx = 0; idx < default_vocab_size; ++idx) {
        auto byte_pair = {static_cast<unsigned char>(idx)};
        vocab[idx] = byte_pair;
    }

    for (const auto entry: _merges) {
        const auto &firsChar = vocab[entry.first.first];
        const auto &secondChar = vocab[entry.first.second];

        auto byte_pair = firsChar;
        byte_pair.insert(byte_pair.end(), secondChar.begin(), secondChar.end());
        vocab[entry.second] = byte_pair;
    }
}

std::string Tokenizer::decode(const std::vector<int> &ids) const {
    std::string text;
    for (const int i: ids) {
        const auto &byte_sequence = vocab.at(i);
        text.append(byte_sequence.begin(), byte_sequence.end());
    }
    return text;
}

std::vector<int> Tokenizer::encode(std::string text) const {
    auto _tokens = std::vector<int>(text.begin(), text.end());
    printf("\nToken size before encode: %lu", _tokens.size());

    while (_tokens.size() >= 2) {
        auto stats = getStats(_tokens);

        // now get the pair by comparing its tokens in the merges table with the lowest idx.
        // because lowest idx is the most repeated one in merges table by its design. See the training function above.
        const auto minPair = utils::getMinByMerges(stats, merges);
        if (!minPair) break; // no more merges found. break and return the token list
        auto idx = getIdxOfPair(minPair.value());

        _tokens = generateTokenWithId(_tokens, minPair.value(), idx);
    }

    printf("\nToken size after encode: %lu", _tokens.size());

    return _tokens;
}

int Tokenizer::getIdxOfPair(const std::pair<int, int> &pair) const {
    int idx = -1; // bad value!

    for (const auto &i : merges) {
        if(i.first == pair) {
            idx = i.second;
            break;
        }
    }

    return idx;
}
