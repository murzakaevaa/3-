#include "tree2.h"
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

// FIX_ME: Запрещено использовать
// using namespace std;

// Конструктор узла
Node::Node(int val) : value(val), left(nullptr), right(nullptr) {}

// Функция для построения дерева из выражения в обратной польской записи
std::unique_ptr<Node> build_tree_from_rpn(const std::string& filename) {
  // FIX_ME: имя переменной в lower_case_with_underscores
  //std::ifstream file(filename);
  //if (!file.is_open()) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return nullptr;
  }

  // FIX_ME: неинформативное имя переменной st
  // stack<Node*> st;
  std::stack<std::unique_ptr<Node>> node_stack;
  // FIX_ME: неинформативное имя переменной token
  // string token;
  std::string current_token;

  while (input_file >> current_token) {
    if (current_token == "+" || current_token == "-" || current_token == "*" ||
    current_token == "/" || current_token == "%") {
      // FIX_ME: неинформативное имя переменной opCode
      // int opCode;
      int operation_code;
      if (current_token == "+") {
          operation_code = -1;
      }
      else if (current_token == "-") {
          operation_code = -2;
      }
      else if (current_token == "*") {
          operation_code = -3;
      }
      else if (current_token == "/") {
          operation_code = -4;
      }
      else {
          operation_code = -5;
      }

      auto operation_node = std::make_unique<Node>(operation_code);
      // FIX_ME: неинформативное имя переменной right, left
      // Node* right = st.top(); st.pop();
      // Node* left = st.top(); st.pop();
      auto right_operand = std::move(node_stack.top());
      node_stack.pop();
      auto left_operand = std::move(node_stack.top());
      node_stack.pop();

      operation_node->left = std::move(left_operand);
      operation_node->right = std::move(right_operand);
      node_stack.push(std::move(operation_node));
    }
    else {
      int number_value = std::stoi(current_token);
      // FIX_ME: неинформативное имя переменной numNode
      // Node* numNode = new Node(num);
      node_stack.push(std::make_unique<Node>(number_value));
    }
  }

  input_file.close();
  return node_stack.empty() ? nullptr : std::move(node_stack.top());
}


// Функция для вычисления значения поддерева
int evaluate_tree(const std::unique_ptr<Node>& node) {
  if (node == nullptr) {
    return 0;
  }
  if (node->value >= 0 && node->value <= 9) {
    return node->value;
  }

  // FIX_ME: неинформативные имена переменных leftVal, rightVal
  // int leftVal = evaluate(root->left);
  // int rightVal = evaluate(root->right);
  int left_subtree_value = evaluate_tree(node->left);
  int right_subtree_value = evaluate_tree(node->right);

  switch (node->value) {
    case -1:
    return left_subtree_value + right_subtree_value;
    case -2:
    return left_subtree_value - right_subtree_value;
    case -3:
    return left_subtree_value * right_subtree_value;
    case -4:
    if (right_subtree_value != 0) {
      return left_subtree_value / right_subtree_value;
    }
    return 0;
    case -5:
    if (right_subtree_value != 0) {
      return left_subtree_value % right_subtree_value;
    }
    return 0;
    default:
    return 0;
  }
}

// Функция для освобождения памяти
void delete_tree(Node* node) {
  if (node == nullptr) {
    return;
  }
  delete_tree(node->left.get());
  delete_tree(node->right.get());
  delete node;
}

// Функция для замены поддеревьев с умножением на их значения
std::unique_ptr<Node> replace_multiplication(std::unique_ptr<Node> node) {
  if (node == nullptr) {
    return nullptr;
  }

  // Если текущий узел - операция умножения
  if (node->value == -3) {
    // FIX_ME: неинформативное имя переменной result
    // int result = evaluate(root);
    int multiplication_result = evaluate_tree(node);
    // FIX_ME: неинформативное имя переменной newNode
    // Node* newNode = new Node(result);
    return std::make_unique<Node>(multiplication_result);
  }
  node->left = replace_multiplication(std::move(node->left));
  node->right = replace_multiplication(std::move(node->right));

  return node;
}


// Функция для вывода дерева в виде строки (инфиксная запись)
void print_tree_infix(const std::unique_ptr<Node>& node) {
  if (node == nullptr) {
    return;
  }

  // Если это число (от 0 до 9 или больше, после замены умножения)
  if (node->value >= 0) {
    std::cout << node->value;
    return;
  }

  // Если это операция
  // FIX_ME: неинформативное имя переменной op
  // string op;
  std::string operation_symbol;
  switch (node->value) {
    case -1:
    operation_symbol = "+";
    break;
    case -2:
    operation_symbol = "-";
    break;
    case -3:
    operation_symbol = "*";
    break;
    case -4:
    operation_symbol = "/";
    break;
    case -5:
    operation_symbol = "%";
    break;
    default:
    operation_symbol = "?";
    break;
  }


  std::cout << "(";
  print_tree_infix(node->left);
  std::cout << " " << operation_symbol << " ";
  print_tree_infix(node->right);
  std::cout << ")";
}

// Функция для вывода дерева в виде структуры (с отступами)
void print_tree_structure(const std::unique_ptr<Node>& node, int level) {
  if (node == nullptr) {
    return;
  }

  // Выводим правого потомка
  print_tree_structure(node->right, level + 1);

  // Выводим текущий узел с отступами
  for (int i = 0; i < level; ++i) {
    std::cout << "    ";
  }


  // Если это число (от 0 до 9 или больше, после замены умножения)
  if (node->value >= 0) {
    std::cout << node->value << std::endl;
  }
  // Если это операция
  else {
    // FIX_ME: неинформативное имя переменной op
    // string op;
    std::string operation_symbol;
    switch (node->value) {
      case -1:
      operation_symbol = "+";
      break;
      case -2:
      operation_symbol = "-";
      break;
      case -3:
      operation_symbol = "*";
      break;
      case -4:
      operation_symbol = "/";
      break;
      case -5:
      operation_symbol = "%";
      break;
      default:
      operation_symbol = "?";
      break;
    }
    std::cout << operation_symbol << std::endl;
  }


  // Выводим левого потомка
  print_tree_structure(node->left, level + 1);
}