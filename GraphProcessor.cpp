#include "GraphProcessor.h"

GraphProcessor::GraphProcessor(
  const std::vector<std::vector<int>>& adj_matrix)
  : graph_(adj_matrix),
  n_(graph_.size()) {
}

std::vector<int> GraphProcessor::bfs_shortest_paths(int start) const {
  std::vector<int> distance(n_, INT_MAX);
  std::queue<int> q;

  //FIX_ME: Добавить проверку корректности start
  if (start < 0 || start >= n_) {
      return distance;
  }

  distance[start] = 0;
  q.push(start);

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    for (int next = 0; next < n_; ++next) {
      if (graph_[current][next] == 1 && distance[next] == INT_MAX) {
        distance[next] = distance[current] + 1;q.push(next);
      }
    }
  }

  return distance;
}

std::vector<int> GraphProcessor::find_сities_with_min_transfers(int K, int L) {
  //FIX_ME: Добавить проверку границ входных данных
  //K--;
  if (K <= 0 || K > n_) {
    return std::vector<int>();
  }
  int start_index = K - 1;

  // Получаем кратчайшие расстояния от города K
  std::vector<int> distance = bfs_shortest_paths(start_index);

  // Поиск городов, удовлетворяющих условию
  std::vector<int> result;
  for (int i = 0; i < n_; ++i) {
    // Пропускаем исходный город
    if (i == start_index) {
      continue;
    }

    // Проверяем, что город достижим
    if (distance[i] != INT_MAX) {
      // Количество пересадок = количество ребер - 1
      // (если путь состоит из 1 ребра, то пересадок 0)
      int transfers = distance[i] - 1;

      // Условие: не менее L пересадок
      // BFS уже гарантирует, что это кратчайший путь
      if (transfers >= L) {
        result.push_back(i + 1); // Возвращаем к 1-индексации
      }
    }
  }

  // Сортируем результат по возрастанию
  sort(result.begin(), result.end());

  return result;
}