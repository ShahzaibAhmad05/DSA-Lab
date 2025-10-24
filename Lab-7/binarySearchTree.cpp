#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Tree {
    Node* root;

public:
    Tree() : root(nullptr) {}

    // insert new value in bst
    void insert(int val) {
        root = insertRec(root, val);
    }

    Node* insertRec(Node* node, int val) {
        if (node == nullptr) return new Node(val);  // base case
        if (val < node->data)
            node->left = insertRec(node->left, val);
        else if (val > node->data)
            node->right = insertRec(node->right, val);
        else
            cout << "duplicate value ignored.\n";
        return node;
    }

    // delete a node from bst
    Node* deleteRec(Node* node, int val) {
        if (node == nullptr) return node;

        if (val < node->data)
            node->left = deleteRec(node->left, val);
        else if (val > node->data)
            node->right = deleteRec(node->right, val);
        else {  // found the node, now delete it
            if (node->left == nullptr) {        // node with only right child or no child
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {    // node with only left child or no child
                Node* temp = node->left;
                delete node;
                return temp;
            } else {        // node with two children: get inorder successor
                Node* temp = minValueNode(node->right);
                node->data = temp->data;    // replace the node with its successor
                node->right = deleteRec(node->right, temp->data);
            }
        }
        return node;
    }

    void deleteValue(int val) {
        root = deleteRec(root, val);
    }

    // find the node with the minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    // traversal functions
    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // wrappers for printing traversals
    void printPreorder() { cout << "\npreorder: "; preorder(root); cout << endl; }
    void printInorder()  { cout << "inorder: "; inorder(root); cout << endl; }
    void printPostorder(){ cout << "postorder: "; postorder(root); cout << endl; }

    // print tree in simple pyramid style
    void printSimple(Node* node, int space = 0, int height = 5) {
        if (node == nullptr) return;
        space += height;
        printSimple(node->right, space);
        cout << endl;
        for (int i = height; i < space; i++) cout << " ";
        cout << node->data << "\n";
        printSimple(node->left, space);
    }

    void print() {
        cout << "\nbinary search tree:\n";
        printSimple(root);
        cout << endl;
    }
};

int main() {
    Tree tree;
    int choice, value;

    cout << "---- Testing with different inputs from a smaller array ----\n";
    int arr[] = {23, 43, 1, 17, 70, 52, 29, 8, 90, 33};
    for (int val : arr) {
        cout << "Inserting " << val << " into the BST.\n";
        tree.insert(val);
    }
    tree.print();
    return 0;

    while (true) {
        cout << "\n----- binary search tree menu -----\n";
        cout << "1. insert new data\n";
        cout << "2. in-order traversal\n";
        cout << "3. pre-order traversal\n";
        cout << "4. post-order traversal\n";
        cout << "5. delete an item\n";
        cout << "6. print tree\n";
        cout << "0. exit\n";
        cout << "enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                tree.printInorder();
                break;
            case 3:
                tree.printPreorder();
                break;
            case 4:
                tree.printPostorder();
                break;
            case 5:
                cout << "enter value to delete: ";
                cin >> value;
                tree.deleteValue(value);
                break;
            case 6:
                tree.print();
                break;
            case 0:
                cout << "exiting...\n";
                return 0;
            default:
                cout << "invalid choice.\n";
        }
    }
}
