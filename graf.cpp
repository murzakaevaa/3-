#include "graf.h"
#include <fstream>
#include <queue>
#include <limits>

std::vector<int> find_cities_with_transfers(const std::string& file_name,
    int K,
    int L) {
  //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
  //std::ifstream file(fileName);
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error("Ошибка открытия файла");
  }

  //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
  // int n;
  // file >> n;
  int num_cities;
  file >> num_cities;

  //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
  //std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
  std::vector<std::vector<int>> adjacency_matrix(num_cities,
    std::vector<int>(num_cities));

  for (int i = 0; i < num_cities; ++i) {
    for (int j = 0; j < num_cities; ++j) {
      file >> adjacency_matrix[i][j];
    }
  }
  file.close();

  // Массивы для хранения информации
  //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
  //std::vector<int> minTransfers(n, std::numeric_limits<int>::max());
  //std::queue<std::pair<int, int>> q;
  std::vector<int> min_transfers_count(num_cities,
    std::numeric_limits<int>::max());
  std::queue<std::pair<int, int>> transfer_queue;

  //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
  /*
  K--;  // Приводим к 0-индексации
  minTransfers[K] = 0;
  q.push({ K, 0 });*/
  int start_index = K - 1;
  min_transfers_count[start_index] = 0;
  transfer_queue.push({ start_index, 0 });

  // BFS для поиска кратчайших путей
  while (!transfer_queue.empty()) {
    //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
    //int current = q.front().first;
    int current_city = transfer_queue.front().first;
    //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
    //int transfers = q.front().second;
    int current_transfers = transfer_queue.front().second;
    transfer_queue.pop();

    for (int i = 0; i < num_cities; ++i) {
      if (adjacency_matrix[current_city][i] == 1) {
        //FIX_ME: Имя переменной должно быть в lower_case_with_underscores
        //if (transfers + 1 < minTransfers[i]) {
        if (current_transfers + 1 < min_transfers_count[i]) {
          min_transfers_count[i] = current_transfers + 1;
          transfer_queue.push({ i, current_transfers + 1 });
        }
      }
    }
  }

  // Формирование итогового результата
  std::vector<int> result;
  for (int i = 0; i < num_cities; ++i) {
    if (min_transfers_count[i] == L + 1) {
      result.push_back(i + 1);  // Возврат к 1-based индексации
    }
  }

  return result;
}