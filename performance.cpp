//
// Created by ozanhonamlioglu on 4.12.2025.
//

#include "performance.hpp"

namespace performance {
    std::chrono::time_point<std::chrono::steady_clock> startPerf(std::optional<std::string> title) {
        if (title.has_value()) {
            const std::string &_title = title.value();
            std::cout << _title << "\n" << std::endl;
        }

        return std::chrono::high_resolution_clock::now();
    }

    void endPerf(std::chrono::time_point<std::chrono::steady_clock> start) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;
        auto ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        std::cout << "\nTotal execution time for loop: "
                << ms_duration.count()
                << " milliseconds\n";
    }
}
