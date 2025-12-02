#include <memory>
#include <deque>
#include <string>
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
    std::deque<std::shared_ptr<ParseTreeNode>> children_;
    std::string name_;
    int id_;
};