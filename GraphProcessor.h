#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

//FIX_ME: using namespace std; запрещен по кодстайлу
//using namespace std;
// Используем полные имена

class GraphProcessor {
private:
  const std::vector<std::vector<int>> graph_;
  const int n_;
  //FIX_ME: Имена аргументов должны быть в lower_case_with_underscores
  //std::vector<int> BfsShortestPaths(int start) const;
  std::vector<int> bfs_shortest_paths(int start) const;

public:
  // Конструктор
  //FIX_ME: Конструктор должен быть explicit
  //GraphProcessor(const vector<vector<int>>& adjMatrix);
  explicit GraphProcessor(const std::vector<std::vector<int>>& adj_matrix);

  // Поиск городов, в которые можно долететь не менее чем с L пересадками
  // и более коротких путей не существует
  //FIX_ME: Имена аргументов должны быть в lower_case_with_underscores
  // std::vector<int> FindCitiesWithMinTransfers(int K, int L);
  std::vector<int> find_сities_with_min_transfers(int K, int L);

};
