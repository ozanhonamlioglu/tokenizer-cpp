//
// Created by ozanhonamlioglu on 4.12.2025.
//

#pragma once

#include <iostream>

namespace performance {
    std::chrono::time_point<std::chrono::steady_clock> startPerf(std::optional<std::string> title);

    void endPerf(std::chrono::time_point<std::chrono::steady_clock> start);
}
