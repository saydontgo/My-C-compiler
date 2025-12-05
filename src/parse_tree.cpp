#include "parse_tree.h"

ParseTreeNode::ParseTreeNode(std::string name, int id) : name_(name), id_(id) {}

void ParseTreeNode::PushBack(std::shared_ptr<ParseTreeNode> child) {
    children_.push_back(child);
}

void ParseTreeNode::PushFront(std::shared_ptr<ParseTreeNode> child) {
    children_.push_front(child);
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
    std::cout << name_ << std::endl;
    if (!children_.empty()) {
        for (const auto& child : children_) {
            PrintDfs(child, 1);
        }
    }
}

auto ParseTreeNode::GetName() const -> const std::string& {
    return name_;
}

auto ParseTreeNode::GetId() const -> int{
    return id_;
}