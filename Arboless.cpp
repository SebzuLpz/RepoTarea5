#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
using namespace std;

int pow2(int n) {
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= 2;
    }
    return result;
}

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

Node* insert_node(Node* node, int data, list<Node*>& insertion_order) {
    if (node == nullptr) {
        node = new Node(data);
        insertion_order.push_back(node);
    } else if (data < node->data) {
        node->left = insert_node(node->left, data, insertion_order);
    } else {
        node->right = insert_node(node->right, data, insertion_order);
    }
    return node;
}

Node* build_tree(list<Node*>& insertion_order, Node*& root) {
    int data;
    cout << "Ingrese los datos del árbol (ingrese 0 para terminar): ";
    while (true) {
        cin >> data;
        if (data == 0) {
            break;
        }
        if (root == nullptr) {
            root = new Node(data);
        } else {
            insert_node(root, data, insertion_order);
        }
    }
    return root;
}

int get_max_level(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int left_level = get_max_level(node->left);
    int right_level = get_max_level(node->right);
    return max(left_level, right_level) + 1;
}

int get_level(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    if (node->left == nullptr && node->right == nullptr) {
        return 0;
    }
    int left_level = get_level(node->left);
    int right_level = get_level(node->right);
    return max(left_level, right_level) + 1;
}

void print_tree_level(Node* node, int level, int max_level) {
    if (node == nullptr) {
        return;
    }
    if (level == 1) {
        cout << node->data << " ";
    } else if (level <= max_level) {
        print_tree_level(node->left, level - 1, max_level);
        print_tree_level(node->right, level - 1, max_level);
    }
}

void print_tree(Node* node) {
    int max_level = get_max_level(node);
    for (int level = 1; level <= max_level; level++) {
        print_tree_level(node, level, max_level);
        cout << endl;
    }
}

void print_insertion_order(list<Node*>& insertion_order) {
    for (auto node : insertion_order) {
        cout << node->data << " ";
    }
    cout << endl;
}

int main() {
    Node* root = nullptr;
    list<Node*> insertion_order;
    build_tree(insertion_order, root);
    cout << "Arbol en forma de imagen: " << endl;
    print_tree(root);
    cout << "Orden de insercion: " << endl;
    print_insertion_order(insertion_order);

    return 0;
}