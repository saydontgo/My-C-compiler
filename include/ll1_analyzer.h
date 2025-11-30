#include <string>
#include <unordered_map>
#include <vector>
class LL1Analyzer {
public:
    explicit LL1Analyzer(std::string grammar);
    auto BuildTable() -> std::unordered_map<int, std::unordered_map<int, std::vector<std::string>*>>;

private:
    std::unordered_map<int, std::vector<int>> first_;
    std::unordered_map<int, std::vector<int>> follow_;
};