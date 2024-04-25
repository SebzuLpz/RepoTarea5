#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
using namespace std;

int pow2(int n) {
    int resultado = 1;
    for (int i = 0; i < n; i++) {
        resultado *= 2;
    }
    return resultado;
}

class Node {
public:
    int datos;
    Node* izquierda;
    Node* derecha;

    Node(int datos) {
        this->datos = datos;
        this->izquierda = this->derecha = nullptr;
    }
};

Node* insertar_nodo(Node* node, int datos, list<Node*>& insertion_order) {
    if (node == nullptr) {
        node = new Node(datos);
        insertion_order.push_back(node);
    } else if (datos < node->datos) {
        node->izquierda = insertar_nodo(node->izquierda, datos, insertion_order);
    } else {
        node->derecha = insertar_nodo(node->derecha, datos, insertion_order);
    }
    return node;
}

Node* arbol(list<Node*>& insertion_order, Node*& root) {
    int datos;
    cout << "Ingrese los datos del arbol (ingrese 0 para terminar): ";
    while (true) {
        cin >> datos;
        if (datos == 0) {
            break;
        }
        if (root == nullptr) {
            root = new Node(datos);
        } else {
            insertar_nodo(root, datos, insertion_order);
        }
    }
    return root;
}

int max(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int nizquierda = max(node->izquierda);
    int nderecha = max(node->derecha);
    return max(nizquierda, nderecha) + 1;
}

int obtener_level(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    if (node->izquierda == nullptr && node->derecha == nullptr) {
        return 0;
    }
    int nizquierda = obtener_level(node->izquierda);
    int nderecha = obtener_level(node->derecha);
    return max(nizquierda, nderecha) + 1;
}

void imprimir_arbol_level(Node* node, int level, int max_level) {
    if (node == nullptr) {
        return;
    }
    if (level == 1) {
        cout << node->datos << " ";
    } else if (level <= max_level) {
        imprimir_arbol_level(node->izquierda, level - 1, max_level);
        imprimir_arbol_level(node->derecha, level - 1, max_level);
    }
}

void imprimir_arbol(Node* node) {
    int max_level = max(node);
    for (int level = 1; level <= max_level; level++) {
        imprimir_arbol_level(node, level, max_level);
        cout << endl;
    }
}

void imprimir_arbol_inorden(Node* node) {
    if (node == nullptr) {
        return;
    }
    imprimir_arbol_inorden(node->izquierda);
    cout << node->datos << " ";
    imprimir_arbol_inorden(node->derecha);
}

void imprimir_arbol_preorden(Node* node) {
    if (node == nullptr) {
        return;
    }
    cout << node->datos << " ";
    imprimir_arbol_preorden(node->izquierda);
    imprimir_arbol_preorden(node->derecha);
}

void imprimir_arbol_postorden(Node* node) {
    if (node == nullptr) {
        return;
    }
    imprimir_arbol_postorden(node->izquierda);
    imprimir_arbol_postorden(node->derecha);
    cout << node->datos << " ";
}

void imprimir_orden_insercion(list<Node*>& insertion_order) {
    for (auto node : insertion_order) {
        cout << node->datos << " ";
    }
    cout << endl;
}

int main() {
    Node* root = nullptr;
    list<Node*> insertion_order;
    arbol(insertion_order, root);
    cout << "Arbol en forma de imagen: " << endl;
    imprimir_arbol(root);
    cout << "Orden de insercion: " << endl;
    imprimir_orden_insercion(insertion_order);
    cout << "Orden inorden: " << endl;
    imprimir_arbol_inorden(root);
    cout << endl;
    cout << "Orden preorden: " << endl;
    imprimir_arbol_preorden(root);
    cout << endl;
    cout << "Orden postorden: " << endl;
    imprimir_arbol_postorden(root);
    cout << endl;

    return 0;
}