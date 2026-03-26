/*  лаб3(3.3 чат).cpp   ::Graf8. Юный путешественник решил изучить схему авиационного сообщения Схема авиацион
ного сообщения задана в текстовом файле с именем FileName.в виде матрицы смежности.Первая
строка файла содержит количество городов(n) n <= 15, связанных авиационным сообщением, а
следующие n строк хранят матрицу(m), m[i][j] = 0, если не имеется возможности перелета из го
рода i в город j, иначе m[i][j] = 1. Определить номера городов, в которые из города K можно доле
теть не менее чем с L пересадками и более коротких путей к таким городам не существует.Пере
числите номера таких городов в порядке возрастания.Нумерация городов начинается с 1. Если
таких городов нет, выведите число(-1).* /

/*https://alice.yandex.ru/ */


#include <iostream>
#include "graf.h"
#include <algorithm>

int main() {
  setlocale(LC_ALL, "ru");
  try {
    std::string file_name;
    int K, L;

    std::cout << "Введите имя файла с матрицей: ";
    std::cin >> file_name;

    std::cout << "Введите номер исходного города (от 1 до N): ";
    std::cin >> K;

    std::cout << "Введите минимальное количество пересадок: ";
    std::cin >> L;

    std::vector<int> result = find_cities_with_transfers(file_name, K, L);

    if (result.empty()) {
      std::cout << "-1" << std::endl;
    }
    else {
      std::sort(result.begin(), result.end());  // Сортируем по возрастанию
      for (int city : result) {
        std::cout << city << " ";
      }
      std::cout << std::endl;
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
  }

  return 0;
}
