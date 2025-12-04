//
// Created by ozanhonamlioglu on 2.12.2025.
//

#include "tokenizer.hpp"

namespace utils {
    std::vector<unsigned char> readFile(const std::string &fileName) {
        std::ifstream file(fileName, std::ios::binary);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file '" << fileName << "'" << std::endl;
            return {};
        }

        file.seekg(0, std::ios::end);

        long long file_size = file.tellg();

        if (file_size < 0) {
            std::cerr << "Error: Could not determine file size or file is empty." << std::endl;
            return {};
        }

        std::vector<unsigned char> buffer(file_size);

        file.seekg(0, std::ios_base::beg);

        file.read(reinterpret_cast<char *>(buffer.data()), file_size);

        size_t bytes_read = file.gcount();

        if (bytes_read != file_size) {
            std::cerr << "Warning: Only read " << bytes_read << " out of " << file_size << " bytes." << std::endl;
            // In this case, we might resize the vector to the actual size read.
            buffer.resize(bytes_read);
        } else {
            // std::cout << "Successfully read " << bytes_read << " bytes." << std::endl;
        }

        // The vector 'buffer' now holds the entire file content.
        return buffer;
    }

    std::pair<int, int> getMax(const std::map<std::pair<int, int>, int> &list) {
        if (list.empty()) {
            throw std::out_of_range("The map is empty and has no max element.");
        }

        using map_element_type = std::pair<const std::pair<int, int>, int>;

        auto max = std::max_element(list.begin(), list.end(),
                                    [](const map_element_type &a, const map_element_type &b) {
                                        return a.second < b.second;
                                    }
        );

        return max->first;
    }
}
