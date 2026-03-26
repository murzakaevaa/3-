#include <string>
#include <memory>

// FIX_ME: использование сырых указателей вместо умных
// struct Node {
//   int value;
//   Node* left;
//   Node* right;
//   Node(int val);
// };

// Структура узла дерева
struct Node {
	int value;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;

	explicit Node(int val);
};

// Функция для построения дерева из выражения в обратной польской записи
// FIX_ME: имя функции в lower_case_with_underscores
// Node* buildTreeFromRPN(const std::string& filename);
std::unique_ptr<Node> build_tree_from_rpn(const std::string& filename);

// Функция для вычисления значения поддерева
// FIX_ME: имя функции в lower_case_with_underscores
// int evaluate(Node* root);
int evaluate_tree(const std::unique_ptr<Node>& root);

// FIX_ME: имя функции в lower_case_with_underscores
// void deleteTree(Node* root);
void delete_tree(Node* root);

// Функция для замены поддеревьев с умножением на их значения
// FIX_ME: имя функции в lower_case_with_underscores
// Node* replaceMultiplication(Node* root);
std::unique_ptr<Node> replace_multiplication(std::unique_ptr<Node> root);

// Функция для вывода дерева в виде строки (инфиксная запись)
// FIX_ME: имя функции в lower_case_with_underscores
// void printTreeInfix(Node* root);
void print_tree_infix(const std::unique_ptr<Node>& root);

// Функция для вывода дерева в виде структуры
// FIX_ME: имя функции в lower_case_with_underscores
// void printTreeStructure(Node* root, int level = 0);
void print_tree_structure(const std::unique_ptr<Node>&root, int level = 0);


