#include "word_shuffle.h"
#include <algorithm>

//FIX_ME: функция названа в стиле CamelCase, нужно lower_case_with_underscores
//std::mt19937 initGenerator() {
std::mt19937 init_generator() {
  unsigned seed = std::chrono::system_clock::now()
   .time_since_epoch().count();
  return std::mt19937(seed);
}

//FIX_ME: функция названа в стиле CamelCase, нужно lower_case_with_underscores
//std::string shuffleWord(const std::string& word, std::mt19937& gen) {
std::string shuffle_word(const std::string& word, std::mt19937& gen) {
  std::string shuffled = word;
  std::shuffle(shuffled.begin(), shuffled.end(), gen);
  return shuffled;
}