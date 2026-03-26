#include "solver.h"
#include <iostream>
#include <algorithm>
#include <random>

void run_shuffle_process(std::wstring original) {
  //FIX_ME: Имена переменных должны быть lower_case_with_underscores
  //std::wstring current = original;
  std::wstring current_word = original;

  //FIX_ME: Переменные в lower_case_with_underscores
  //std::random_device rd;
  //std::mt19937 generator(rd());
  std::random_device random_device;
  std::mt19937 generator(random_device());

  // FIX_ME: Переменные в lower_case_with_underscores
  //long long count = 0;
  long long attempts_count = 0;

  if (original.length() <= 1) {
    std::wcout << L'Слово слишком короткое.' << std::endl;
    return;
  }

  do {
    std::shuffle(current_word.begin(), current_word.end(), generator);
    std::wcout << current_word << L"\n";
    attempts_count++;

    // Константа для ограничения итераций
    const long long k_max_attempts = 1000000;

    if (attempts_count > k_max_attempts) {
           
      std::wcout << L"Остановка: слишком много попыток." << std::endl;
      break;
    }

  } while (current_word != original);

 std::wcout << attempts_count << L" попыток." << std::endl;

}