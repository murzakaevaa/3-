#include "tree3.h"
#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>

//FIX_ME: Node(int v) — имя параметра v не по стилю
// Node(int v)
Node::Node(int value_param) {
  value = value_param;
}

std::string get_value(int v) {
  switch (v) {
    case -1: return "+";
    case -2: return "-";
    case -3: return "*";
    case -4: return "/";
    case -5: return "%";
    default: return std::to_string(v);
  }
}


void print_tree(const Node* root,int space,int height) {
  if (!root) {
    return;
  }

  space += height;

  print_tree(root->right.get(), space);

  std::cout << std::endl;
  for (int i = height; i < space; ++i) {
    std::cout << " ";
  }

  std::cout << get_value(root->value) << std::endl;

  print_tree(root->left.get(), space);
}


int evaluate_tree(const Node* root) {
  if (!root->left && !root->right) {
    return root->value;
  }
  //FIX_ME: переменные l, r не по стилю
  //старый код
  // int l, r;
  int left_value = evaluate_tree(root->left.get());
  int right_value = evaluate_tree(root->right.get());


  switch (root->value) {
    case -1:
    return left_value + right_value;
    case -2:
    return left_value - right_value;
    case -3:
    return left_value * right_value;
    case -4:
    if (right_value == 0) {
      throw std::runtime_error("Деление на ноль");
    }
    return left_value / right_value;
    case -5:
    if (right_value == 0) {
      throw std::runtime_error("Деление на ноль");
    }
    return left_value % right_value;
    default:
    throw std::runtime_error("Неизвестный оператор");
  }
}

Node* transform_tree(Node* root)
{
    return nullptr;
}

std::unique_ptr<Node> transform_tree(std::unique_ptr<Node> root) {
  if (!root) {
    return nullptr;
  }

  root->left = transform_tree(std::move(root->left));
  root->right = transform_tree(std::move(root->right));

  if (root->value == -3) {
    int subtree_value = evaluate_tree(root.get());

    root->left.reset();
    root->right.reset();
    root->value = subtree_value;
  }

  return root;
}

std::unique_ptr<Node> build_tree(const std::string& expr) {
  std::stack<std::unique_ptr<Node>> node_stack;
  //FIX_ME: имя переменной не в  lower_case_with_underscores
  //for (char c : expr) {
  for (char symbol : expr) {
    if (std::isdigit(symbol)) {
      node_stack.push(std::make_unique<Node>(symbol - '0'));
    }
    else {
      if (node_stack.size() < 2) {
        throw std::runtime_error("invalid expression");
      }

    //FIX_ME: имя переменной не в  lower_case_with_underscores
    //Node* r = st.top(); st.pop();
    //Node* l = st.top(); st.pop();
    auto right_node = std::move(node_stack.top());
    node_stack.pop();

    auto left_node = std::move(node_stack.top());
    node_stack.pop();
    //FIX_ME: имя переменной не в  lower_case_with_underscores
    //int op;
    int operation_code;
    switch (symbol) {
      case '+': operation_code = -1; break;
      case '-': operation_code = -2; break;
      case '*': operation_code = -3; break;
      case '/': operation_code = -4; break;
      case '%': operation_code = -5; break;
      default:
        throw std::runtime_error("Ошибка символа\n");
    }

    auto new_node =std::make_unique<Node>(operation_code);

    new_node->left = std::move(left_node);
    new_node->right = std::move(right_node);

    node_stack.push(std::move(new_node));
    }
  }

  if (node_stack.size() != 1) {
    throw std::runtime_error("Недопустимое выражение");
  }

  return std::move(node_stack.top());
}