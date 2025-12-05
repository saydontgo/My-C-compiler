#include <memory>
#include <deque>
#include <string>
#include <iostream>
class ParseTreeNode {
public:
    ParseTreeNode() = delete;
    ParseTreeNode(std::string name, int id);

    void PushBack(std::shared_ptr<ParseTreeNode> child);
    void PushFront(std::shared_ptr<ParseTreeNode> child);
    void PrintTree() const;
    void PrintOutput() const;
    auto GetName() const -> const std::string&;
    auto GetId() const -> int;
private:
    void PrintDfs(std::shared_ptr<ParseTreeNode> root, int layer) const;
    std::deque<std::shared_ptr<ParseTreeNode>> children_;
    std::string name_;
    int id_;
};