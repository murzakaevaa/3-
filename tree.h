#include <memory>

//FIX_ME: структура Node имела CamelCase, но для типов данных часто 
//используют CamelCase, однако переменные внутри должны быть snake_case
//struct Node
struct ExpressionNode {
  int value;
  std::unique_ptr<ExpressionNode> left;
  std::unique_ptr<ExpressionNode> right;
  ExpressionNode(int val);
};

//FIX_ME: Имена функций должны быть lower_case_with_underscores
//int getOpCode(char op);
int get_op_code(char op);

//FIX_ME: Использование сырых указателей заменено на умные для безопасности
//int evaluate(Node* root);
int evaluate_tree(ExpressionNode* root);


//FIX_ME: clear_tree больше не нужна, так как unique_ptr удалит всё сам
std::unique_ptr<ExpressionNode> transform_tree(
  std::unique_ptr<ExpressionNode> root);


// Новая функция для визуализации дерева
void print_tree(ExpressionNode* root, int depth = 0);
