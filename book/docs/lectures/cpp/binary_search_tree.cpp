#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int x) {
    key = x;
    left = nullptr;
    right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;
    int size;

    Node* insert(int x, Node* subroot) {
        // if subtree is empty
        if (subroot == nullptr) {
        return new Node(x);
    }

    if (x <= subroot->key) {
        subroot->left = insert(x, subroot->left);
    } else {
        subroot->right = insert(x, subroot->right);
    }
        return subroot;
    }

    void print(Node* subroot) {
        if (subroot == nullptr) {
            return;
        }

        print(subroot->left);
        cout << subroot->key << endl;
        print(subroot->right);
    }


    void add_values(Node* subroot, vector<int>& numbers) {
        if (subroot == nullptr) {
            return;
        }

        add_values(subroot->left, numbers);
        numbers.push_back(subroot->key);
        add_values(subroot->right, numbers);
    }


    bool contains(Node* subroot, int x) {
        if (subroot == nullptr) {
            return false;
        }

        if (x == subroot->key) {
            return true;
        } else if (x < subroot->key) {
            return contains(subroot->left, x);
        } else {
            return contains(subroot->right, x);
        }
    }

    Node* remove(Node* subroot, int x) {
        /* Remove node with key x from subtree, if present */
        if (subroot == nullptr) {
            throw runtime_error("Element not in tree");
        }

        if (x < subroot->key) {
            // Keep searching left subtree
            subroot->left = remove(subroot->left, x);
        } else if (x > subroot-> key) {
            // Keep searching right subtree
            subroot->right = remove(subroot->right, x);
        } else {
            // We have found the node to be removed

            if (subroot->left == nullptr and subroot->right == nullptr) {
                // No children
                delete subroot;
                return nullptr;

            } else if (subroot->left == nullptr) {
                // 1 child
                Node* child = subroot->right;
                delete subroot;
                return child;

            } else if (subroot->right == nullptr) {
                // 1 child
                Node* child = subroot->left;
                delete subroot;
                return child;
            } else {
                // 2 Children
                Node* succsessor = find_minimum(subroot->right);
                subroot->key = succsessor->key;
                subroot->right = remove(subroot->right, succsessor->key);
            }
        }
        return subroot;
    }

    Node* find_minimum(Node* subroot) {
        /* Find the smalles node of a given subtree */
        Node* minimum = subroot;
        while (minimum->left != nullptr) {
            minimum = minimum->left;
        }
        return minimum;
    }



public: 
    BinarySearchTree() {
        root = nullptr;
        size = 0;
    }

    BinarySearchTree(vector<int> keys) {
        root = nullptr;
        size = 0;
        for (int key: keys) {
            insert(key);
        }
    }

    void insert(int x) {
        size++;
        root = insert(x, root);
    }	

    void insert(vector<int> numbers) {
        for (int n: numbers) {
            insert(n);
        }
    }

    int length() {
        return size;
    }

    void print() {
        print(root);
    }

    vector<int> get_vector() {
        vector<int> numbers;
        add_values(root, numbers);
        return numbers;
    }

    bool contains(int x) {
        return contains(root, x);
    }

    void remove(int x) {
        /* Remove node with key x from whole tree if present

        If the key is not present, we throw an error
        */
        root = remove(root, x);
        size--;
    }
};

vector<int> bst_sort(vector<int> numbers) {
    BinarySearchTree tree(numbers);
    return tree.get_vector();
}


int main() {
    BinarySearchTree example({4, 1, 3, 5, 0, 9, 2, 4, 1, 7});

    example.remove(3);
    example.remove(9);
    example.remove(0);

    example.print();
}

 