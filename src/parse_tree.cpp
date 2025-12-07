#include "parse_tree.h"
#include "token.h"
#include <memory>

auto ParseTreeNode::invalid_table_ = std::make_shared<std::unordered_set<lex_id_t>>();
ParseTreeNode::ParseTreeNode(std::string name, lex_id_t id) : name_(name), id_(id) {}

void ParseTreeNode::PushBack(std::shared_ptr<ParseTreeNode> child) {
    children_.push_back(child);
}

void ParseTreeNode::PushFront(std::shared_ptr<ParseTreeNode> child) {
    children_.push_front(child);
}

auto ParseTreeNode::IsInvalid(lex_id_t id) -> bool {
    return invalid_table_->count(id);
}
auto ParseTreeNode::ConvertToAst(std::shared_ptr<ParseTreeNode> node) -> std::deque<std::shared_ptr<ParseTreeNode>> {
    std::deque<std::shared_ptr<ParseTreeNode>> tmp;
    // convert all children first
    for (auto& child : node->children_) {
        auto res = ConvertToAst(child);
        tmp.insert(tmp.end(), res.begin(), res.end());
    }

    node->children_ = std::move(tmp);

    // remove invalid children
    node->children_.erase(
        std::remove(node->children_.begin(), node->children_.end(), nullptr),
        node->children_.end()
    );

    if (IsInvalid(node->GetId())) {
        for (const auto& child : node->children_) {
            tmp.push_back(child);
        }
        return tmp;
    }
    tmp.push_back(node);
    return tmp;
}

void ParseTreeNode::Abstract() {
    std::deque<std::shared_ptr<ParseTreeNode>> tmp;
    // convert all children first
    for (auto& child : children_) {
        auto res = ConvertToAst(child);
        tmp.insert(tmp.end(), res.begin(), res.end());
    }
    children_ = std::move(tmp);

    // remove invalid children
    children_.erase(
        std::remove(children_.begin(),children_.end(), nullptr),
        children_.end()
    );
}

void ParseTreeNode::PrintDfs(std::shared_ptr<ParseTreeNode> root, int layer) const {
    for (int i = 0; i < layer; i++) {
        std::cout << "\t";
    }
    std::cout << root->name_ << std::endl;
    if (!root->children_.empty()) {
        for (const auto& child : root->children_) {
            PrintDfs(child, layer + 1);
        }
    }
}

void ParseTreeNode::PrintOutput() const {
    PrintDfs(std::make_shared<ParseTreeNode>(*this), 0);
}

auto ParseTreeNode::GetName() const -> const std::string& {
    return name_;
}

auto ParseTreeNode::GetId() const -> lex_id_t {
    return id_;
}