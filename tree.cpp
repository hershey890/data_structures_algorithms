#include <memory>
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <queue>
#include <iostream>
#include <utility>

struct TreeNode {
    int val;
    TreeNode* ptr;
    std::vector<TreeNode*> children;
    
    TreeNode() : val(0) {}

    TreeNode(const int& x) : val(x) {}

    TreeNode(const std::initializer_list<int>& lst) {
        children.resize(lst.size());
        int i=0;
        for(auto it=lst.begin(); it != lst.end(); it++)
            children[i++] = new TreeNode(*it);
    }

    TreeNode(int x, const std::initializer_list<int>& lst) : val(x) {
        children.resize(lst.size());
        int i=0;
        for(auto it=lst.begin(); it != lst.end(); it++)
            children[i++] = new TreeNode(*it);
    }

    ~TreeNode() {
        for(TreeNode* child : children)
            delete child;
    }

    void addChild(int x) {
        children.push_back(new TreeNode(x));
    }

    void addChild(TreeNode* x) {
        if(x == nullptr)
            throw std::runtime_error("Can't add TreeNode nullptr to tree");
        children.push_back(x);
    }

    void addChildren(const std::initializer_list<int>& lst) {
        int i=children.size();
        children.resize(children.size() + lst.size());
        for(auto it=lst.begin(); it != lst.end(); it++)
            children[i++] = new TreeNode(*it);
    }

    unsigned int getNumChildren() const {
        return children.size();
    }
};

// TODO: rewrite the child iteration to work for btrees as well
// maybe use a base function and then inside tree.cpp and btree.cpp use a wrapper that passes a function, functor, or lambda expr
int _findDepth(TreeNode* node, int depth=0) {
    if(node == nullptr)
        return 0;

    int maxDepth = 0;
    for(TreeNode* child : node->children)
        maxDepth = std::max(maxDepth, _findDepth(child, depth));

    return maxDepth + 1;    
}

/*
        o
       _|_
      | | |
      o o o
     _|_
    |   |
    o   o
*/

int _subtreeWidth(TreeNode* node) {
    if(node == nullptr)
        return 0;

    int width = 1;
    for(TreeNode* child : node->children)
        width += std::max(width, _subtreeWidth(child));
    
    

    return width;

}

void printTree(TreeNode* node) {
    using namespace std;

    int tree_depth = _findDepth(node);
    int print_width = 2*(1<<tree_depth)-1;
    vector<vector<char>> print_output(tree_depth + 3*(tree_depth-1), vector<char>(' ', print_width));
    
    queue<pair<TreeNode*,int>> q; // node, print_index
    q.push({node, print_width/2});
    q.push({nullptr, -1});
    int depth = 0;

    while(!q.empty()) {
        node = q.front().first;
        int i = q.front().second;
        print_output[depth][i] = node->val;
        q.pop();

        if(node == nullptr && q.size()) {
            q.push({nullptr, -1});
            depth += 3;
        } else {
            cout << node->val << " ";
            for(TreeNode* child: node->children)
                q.push({child, i});
        }
    }

    // iterate through print output and add /
}

int main() {
    using namespace std;

    TreeNode tree(0, {1,2,3});

    int i = 4;
    for(TreeNode* child : tree.children)
        child->addChildren({i++, i++});

    cout << _findDepth(&tree) << endl << endl;
    printTree(&tree);

    return 0;
}