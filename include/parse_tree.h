#include <memory>
#include <vector>
#include <string>
class ParseTreeNode {
public:
    void PrintTree() const;
    void PrintOutput() const;

private:
    std::vector<std::shared_ptr<ParseTreeNode>> children_;
    std::string name_;
    int ID;
};