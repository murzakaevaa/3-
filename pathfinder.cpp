#include "pathfinder.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <stdexcept>

void find_target_cities(const std::string& file_name,int start_city,
  int transfers) {
  //FIX_ME: имя переменной не в lower_case_with_underscores
  //if (!file.is_open()) return;
  std::ifstream input_file(file_name);
  //FIX_ME: Вместо простого return используем исключение std::runtime_error
  if (!input_file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл");
  }

  //FIX_ME: имя переменной не в lower_case_with_underscores
  //int n;
  int n_cities;
  if (!(input_file >> n_cities)) {
    throw std::runtime_error("Ошибка чтения данных");
  }

  // Использование вложенных векторов для матрицы смежности
  //FIX_ME: имя функция не в lower_case_with_underscores
  //std::vector<std::vector<int>> matrix(n_cities, std::vector<int>(n_cities));


  std::vector<std::vector<int>> adjacency_matrix(n_cities, 
  std::vector<int>(n_cities));

  for (int i = 0; i < n_cities; ++i) {
    for (int j = 0; j < n_cities; ++j) {
      input_file >> adjacency_matrix[i][j];
    }
  }
  input_file.close();

  //FIX_ME: имя переменной не в lower_case_with_underscores
  //int targetDistance = transfers + 1;
  const int target_distance = transfers + 1;
  int start_index = start_city - 1;

  if (start_index < 0 || start_index >= n_cities) {
    std::cout << -1 << std::endl;
    return;
  }

  // Поиск в ширину для определения кратчайших путей
  std::vector<int> distances(n_cities, -1);
  //FIX_ME: имя функция не в lower_case_with_underscores
  //std::queue<int> q;
  std::queue<int> visit_queue;

  distances[start_index] = 0;
  visit_queue.push(start_index);

  while (!visit_queue.empty()) {
    //FIX_ME: имя функция не в lower_case_with_underscores
    //int u = q.front();
    int current_u = visit_queue.front();
    visit_queue.pop();

    //FIX_ME: имя функция не в lower_case_with_underscores
    //for (int v = 0; v < n; ++v) {
    for (int current_v = 0; current_v < n_cities; ++current_v) {
      if (adjacency_matrix[current_u][current_v] == 1 && 
      distances[current_v] == -1) {
        distances[current_v] = distances[current_u] + 1;
        visit_queue.push(current_v);
      }
    }
  }
  //FIX_ME: имя функция не в lower_case_with_underscores
  //std::vector<int> result;
  std::vector<int> result_cities;
  for (int i = 0; i < n_cities; ++i) {
    if (distances[i] == target_distance) {
      result_cities.push_back(i + 1);
    }
  }

   if (result_cities.empty()) {
     std::cout << -1 << std::endl;
   }
   else {
     std::sort(result_cities.begin(), result_cities.end());
     for (size_t i = 0; i < result_cities.size(); ++i) {
       std::cout << result_cities[i]
       << (i == result_cities.size() - 1 ? "" : " ");
     }
     std::cout << std::endl;
   }
}