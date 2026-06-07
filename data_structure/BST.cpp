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
            if(node == nullptr){
                return;
            }
            inorder(node -> left);
            std::cout << node -> data << " ";
            inorder(node -> right);
        }

        void destroy(Node* node){
            if(node == nullptr){
                return;
            }
            destroy(node -> left);
            destroy(node -> right);
            delete node;
        }

        Node* findMin(Node* node) const{
            while(node -> left != nullptr){
                node = node -> left;
            }
            return node;
        }

        Node* remove(Node* node, const T& value){
            if(node == nullptr){
                return nullptr;
            }
            if(value < node ->data){
                node -> left = remove(node -> left, value);
            }else if (value > node -> data){
                node -> right = remove(node -> right, value);
            }else{
                //this is the node to delete
                if( node -> left == nullptr){
                    Node* sub = node -> right;
                    delete node;
                    --count;
                    return sub;
                }else if(node -> right == nullptr){
                    Node* sub = node -> left;
                    delete node;
                    --count;
                    return sub;
                }else{
                    Node* successor = findMin(node -> right);
                    node -> data = successor -> data;
                    node -> right = remove(node -> right, successor -> data);
                }
            }
            return node;
        }
    public:
        BinarySearchTree() : root(nullptr), count(0) {}
        
        ~BinarySearchTree(){
            destroy(root);
        }

        void insert (const T& value){
            root = insert(root, value);
        }

        bool contains(const T& value) const{
            return contains(root, value);
        }

        void printSorted() const {
        std::cout << "[ ";
        inorder(root);
        std::cout << "]\n";
    }

    size_t size() const {
        return count;
    }

    bool empty() const {
        return count == 0;
    }

    void remove(const T& value){
        root = remove(root, value);
    }
};

int main() {
    BinarySearchTree<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    tree.printSorted();                      // [ 20 30 40 50 60 70 80 ]
    std::cout << tree.contains(40) << "\n";  // 1
    std::cout << tree.contains(45) << "\n";  // 0
    std::cout << "size: " << tree.size() << "\n";   // 7
}