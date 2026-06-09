#include <iostream>
#include <string>
#include <functional>    //  std::hash

template <typename K, typename V>
class HashMap{
    private:
        struct Node{
            K key;
            V value;
            Node* next;
            Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
        };
        
}