#include "tree.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

ExpressionNode::ExpressionNode(int val)
  : value(val), left(nullptr), right(nullptr) {
}

int get_op_code(char op) {
  switch (op) {
    case '+': return -1;
    case '-': return -2;
    case '*': return -3;
    case '/': return -4;
    case '%': return -5;
    default: return 0;
  }
}


int evaluate_tree(ExpressionNode* root) {
  if (!root) return 0;
  if (root->value >= 0) return root->value;

  int l = evaluate_tree(root->left.get());
  int r = evaluate_tree(root->right.get());

  switch (root->value) {
    case -1: return l + r;
    case -2: return l - r;
    case -3: return l * r;
    //FIX_ME: (Добавлена обработка исключений вместо потенциального краша)
    //case -4: return l / r;
    case -4:
        if (r == 0) throw std::runtime_error("Деление на ноль");
        return l / r;
    case -5:
        if (r == 0) throw std::runtime_error("Деление на ноль (остаток)");
        return l % r;
    default: return 0;
  }
}

//FIX_ME: (Старый код требовал ручного вызова функции очистки памяти)
//clearTree(root->left); delete root;
std::unique_ptr<ExpressionNode> transform_tree(
std::unique_ptr<ExpressionNode> root) {
  if (!root) return nullptr;


  // Рекурсивно обрабатываем ветви
  root->left = transform_tree(std::move(root->left));
  root->right = transform_tree(std::move(root->right));

  // Если операция — умножение, заменяем всё поддерево результатом
  if (root->value == -3) {
    int result = evaluate_tree(root.get());
    // При создании нового unique_ptr старый root со всеми ветками 
    // удалится из памяти автоматически (принцип RAII)
    return std::make_unique<ExpressionNode>(result);
  }
  return root;



}

void print_tree(ExpressionNode* root, int depth) {
    if (!root) return;

    // Сначала рекурсивно выводим правое поддерево
    print_tree(root->right.get(), depth + 1);

    // Печатаем текущий узел с отступом
    std::cout << std::setw(depth * 5) << " ";

    if (root->value >= 0) {
        std::cout << root->value << std::endl;
    }
    else {
        // Декодируем операцию обратно в символ для вывода
        char op_char;
        switch (root->value) {
        case -1: op_char = '+'; break;
        case -2: op_char = '-'; break;
        case -3: op_char = '*'; break;
        case -4: op_char = '/'; break;
        case -5: op_char = '%'; break;
        default: op_char = '?'; break;
        }
        std::cout << "(" << op_char << ")" << std::endl;
    }

    // Затем левое поддерево
    print_tree(root->left.get(), depth + 1);
}