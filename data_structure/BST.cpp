#include <iostream>

template <typename T>
class BinarySearchTree{
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;
            Node(const T& value) : data(value), left(nullptr), right(nullptr){}
        };

        Node* root;
        size_t count;

        Node* insert(Node* node, const T& value){
            if(node == nullptr){
                ++count;
                return new Node(value);    // base case: found the empty spot
            }
            if(value < node -> data){
                node -> left = insert(node->left, value);
            }else if(value > node -> data){
                node -> right = insert (node -> right, value);
            }

            return node;
        }

        bool contains(Node* node, const T& value) const {
            if(node == nullptr){
                return false;
            }
            if(value < node -> data){
                return contains(node -> left, value);
            }else if(value > node -> data){
                return contains(node -> right, value);
            }else{
                return true;
            }
        }

        void inorder(Node* node) const{
            if(node == nullptr){}
        }
};