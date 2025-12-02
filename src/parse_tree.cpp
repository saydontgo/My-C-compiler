#include "parse_tree.h"

ParseTreeNode::ParseTreeNode(std::string name, int id) : name_(name), id_(id) {}

void ParseTreeNode::PushBack(std::shared_ptr<ParseTreeNode> child) {
    children_.push_back(child);
}

void ParseTreeNode::PushFront(std::shared_ptr<ParseTreeNode> child) {
    children_.push_front(child);
}

void ParseTreeNode::PrintOutput() const {

}

auto ParseTreeNode::GetName() const -> const std::string& {
    return name_;
}

auto ParseTreeNode::GetId() const -> int{
    return id_;
}