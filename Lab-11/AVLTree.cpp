#include <iostream>
#include <algorithm> // for std::max

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// get height of a node
int height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// get balance factor of a node
int getBalance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// right rotation (for LL case and part of LR case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // perform rotation
    x->right = y;
    y->left = T2;

    // update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    // return new root
    return x;
}

// left rotation (for RR case and part of RL case)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // perform rotation
    y->left = x;
    x->right = T2;

    // update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // return new root
    return y;
}

// insert a key into avl tree and return new root
Node* insert(Node* node, int key) {
    // normal bst insertion
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        // equal keys not allowed in avl
        return node;
    }

    // update height
    node->height = 1 + max(height(node->left), height(node->right));

    // get balance factor
    int balance = getBalance(node);

    // case 1: ll
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // case 2: rr
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // case 3: lr
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // case 4: rl
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // no imbalance
    return node;
}

// in-order traversal
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// clean up memory
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int N;

    cout << "Enter number of elements to insert (N): ";
    cin >> N;

    cout << "Enter " << N << " integers:\n";
    for (int i = 0; i < N; ++i) {
        int key;
        cin >> key;
        root = insert(root, key);
        cout << "After inserting " << key << ", in-order traversal: ";
        inorder(root);
        cout << "\n";
    }

    cout << "\nFinal AVL Tree (in-order): ";
    inorder(root);
    cout << "\n";

    deleteTree(root);
    return 0;
}
