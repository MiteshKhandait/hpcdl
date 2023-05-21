//tree bfs and dfs

#include<bits/stdc++.h>
#include <omp.h>

using namespace std;

// Binary tree node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// Function to build a binary tree from user input
TreeNode* buildBinaryTree() {
    int value;
    cout << "Enter node value (enter -1 to indicate a null node): ";
    cin >> value;

    if (value == -1) {
        return nullptr;
    }

    TreeNode* newNode = new TreeNode(value);
    cout << "Enter left child of " << value << ": ";
    newNode->left = buildBinaryTree();
    cout << "Enter right child of " << value << ": ";
    newNode->right = buildBinaryTree();

    return newNode;
}

void bfs(TreeNode* root) {
    if (root == nullptr)
        return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        // Parallelize processing child nodes at each level
        #pragma omp parallel for
        for (int i = 0; i < levelSize; i++) {
            TreeNode* current;

            // Critical section to dequeue a node
            #pragma omp critical
            {
                current = q.front();
                q.pop();
            }

            // Process the current node
            cout << current->val << " ";

            // Enqueue the left child, if it exists
            if (current->left != nullptr) {
                // Critical section to enqueue a node
                #pragma omp critical
                {
                    q.push(current->left);
                }
            }

            // Enqueue the right child, if it exists
            if (current->right != nullptr) {
                // Critical section to enqueue a node
                #pragma omp critical
                {
                    q.push(current->right);
                }
            }
        }
    }
}


int main() {
    // Build the binary tree from user input
    cout << "Enter the nodes of the binary tree (enter -1 to indicate a null node):\n";
    TreeNode* root = buildBinaryTree();

    // Perform parallel BFS on the binary tree
    cout << "Parallel BFS traversal: ";
    bfs(root);
//     cout<<"\nparallel fds traversal: ";
//     dfs(root);

    return 0;
}