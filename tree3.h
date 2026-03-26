#include <string>
#include <memory>

struct Node {
  int value;
  //FIX_ME: сырые указатели
  //старый код
  // Node* left;
  // Node* right;
  // новый код
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  explicit Node(int v);
};

//FIX_ME: имя функции не в  lower_case_with_underscores
// string getValue(int v);
std::string get_value(int v);

//FIX_ME: имя функции не в  lower_case_with_underscores
// void printTree(...);
void print_tree(const Node* root,
  int space = 0,
  int height = 5);

//FIX_ME: имя функции не в  lower_case_with_underscores
//int evaluate(Node* root);
int evaluate_tree(const Node* root);

//FIX_ME: имя функции не в  lower_case_with_underscores
//Node* transform(Node* root);
std::unique_ptr<Node> transform_tree(std::unique_ptr<Node> root);

//FIX_ME: имя функции не в  lower_case_with_underscores
// Node* buildTree(...);
std::unique_ptr<Node> build_tree(const std::string& expr);


