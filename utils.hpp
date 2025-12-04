#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <utility>
#include <map>

namespace utils {
    struct pair_hash {
        template<typename T1, typename T2>
        std::size_t operator ()(const std::pair<T1, T2> &p) {
            // 1. Get the hash of the first element (p.first)
            auto h1 = std::hash<T1>{}(p.first);

            // 2. Get the hash of the second element (p.second)
            auto h2 = std::hash<T2>{}(p.second);

            // 3. Combine them using a standard technique: XOR and Shift
            // Shifting h2 left (<< 1) ensures the bits of h1 and h2 don't overlap directly,
            // and XORing them combines the two values into a single result.
            return h1 ^ (h2 << 1);
        }
    };

    typedef std::vector<std::map<std::pair<int, int>, int, pair_hash> > stats;

    std::vector<unsigned char> readFile(const std::string &fileName);

    std::pair<int, int> getMax(const std::map<std::pair<int, int>, int> &list);
}
