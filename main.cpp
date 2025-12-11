#include "tokenizer.hpp"

int main() {
    Tokenizer tokenizer(1000, "training_data.txt");
    tokenizer.train();

    auto sample = "Catherine and Tom live in Sweden, a country where everyone is expected to lead an orderly life according to rules laid down";
    auto encoded = tokenizer.encode(sample);
    auto decoded = tokenizer.decode(encoded);


    printf("\n\n-----TEST-----\n");
    printf("\nSample text: %s", sample);
    std::cout << "\nDecode text: " << decoded << std::endl;

    return 0;
}
