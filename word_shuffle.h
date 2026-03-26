#include <string>
#include <random>
#include <chrono>

// Инициализация генератора случайных чисел
//FIX_ME: функция названа в стиле CamelCase, нужно lower_case_with_underscores
//std::mt19937 initGenerator();
std::mt19937 init_generator();

// Функция перемешивания слова
//FIX_ME: функция названа в стиле CamelCase, нужно lower_case_with_underscores
//std::string shuffleWord(const std::string& word, std::mt19937& gen);
std::string shuffle_word(const std::string& word, std::mt19937& gen);


