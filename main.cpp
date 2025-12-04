#include "tokenizer.hpp"

int main() {
    Tokenizer tokenizer(500, "training_data.txt");
    tokenizer.train();

    return 0;
}
