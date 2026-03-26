#include "shuffle_utils.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <windows.h>

// FIX_ME: Имя функции в lower_case_with_underscores
// void setConsoleEncoding() {
void set_console_encoding() {
  setlocale(LC_ALL, "Russian");
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);
}

// FIX_ME: Имя функции в lower_case_with_underscores
// int shuffleUntilOriginal(const std::string& original, std::string& shuffled, bool verbose) {
int shuffle_until_original(const std::string& original,
  std::string& shuffled,
  bool verbose) {
  int attempts = 0;

   
  unsigned seed = std::chrono::system_clock::now()
    .time_since_epoch()
    .count();
  std::mt19937 generator(seed);

  if (verbose) {
    std::cout << "\nПроцесс перестановки:\n";
  }

  do {
    std::shuffle(shuffled.begin(), shuffled.end(), generator);

    if (verbose) {
      std::cout << shuffled << std::endl;
    }

    attempts++;

  } while (shuffled != original);

  return attempts;
}