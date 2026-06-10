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

        Node** buckets;    // array of bucket head; each bucket is a linked list
        size_t bucketCount;
        size_t count;    // number of key -> value paires stored

        size_t indexFor(const K& key) const{
            return std::hash<K>{}(key) % bucketCount;    // hash, them compress
        }
        
        void rehash(size_t newBucketCount){    // order of heads become reversed, EX: ABC -> CBA
            Node** newBuckets = new Node*[newBucketCount];
            for(size_t i = 0; i < newBucketCount; ++i){
                newBuckets[i] = nullptr;
            }
            for(size_t i = 0; i < bucketCount; ++i){
                Node* node = buckets[i];
                while(node != nullptr){
                    Node* next = node -> next;    // save next before we overwrite it
                    size_t idx = std::hash<K>{}(node -> key) % newBucketCount;
                    node -> next = newBuckets[idx];    // prepend into new bucket
                    newBuckets[idx] = node;
                    node = next;
                }
            }
            delete[] buckets;    // free the old array of heads not the nodes
            buckets = newBuckets;
            bucketCount = newBucketCount;
        }
    public:
        HashMap() : bucketCount(8), count(0) {
            buckets = new Node*[bucketCount];
            for(size_t i = 0; i < bucketCount; ++i){
                buckets[i] = nullptr;
            }
        }

        ~HashMap(){
            for(size_t i = 0; i < bucketCount; ++i){
                Node* node = buckets[i];
                while(node != nullptr){
                    Node* next = node -> next;
                    delete node;
                    node = next;
                }
            }
            delete[] buckets;
        }

        void insert(const K& key, const V& value){
            size_t idx = indexFor(key);
            for(Node* node = buckets[idx]; node != nullptr; node = node -> next){
                if(node -> key == key){
                    node -> value = value;    // key already present -> update
                    return;
                }
            }
            Node* node = new Node(key, value);    // new key -> prepend to the chain
            node-> next = buckets[idx];
            buckets[idx] = node;
            ++count;

            if(count > bucketCount * 3 / 4){    // load factor over ~0.75 -> grow
                rehash(bucketCount * 2);
            }
        }

        bool find(const K& key, V& out) const{
            size_t idx = indexFor(key);
            for(Node* node = buckets[idx]; node != nullptr; node = node -> next){
                if(node -> key == key){
                    out = node ->value;    // out now hols the value
                    return true;
                }
            }
            return false;
        }

        bool remove(const K& key){
            size_t idx = indexFor(key);
            Node* node = buckets[idx];
            Node* prev = nullptr;
            while(node != nullptr){
                if(node -> key == key){
                    if(prev == nullptr){
                        buckets[idx] = node -> next;    // removing head of the chain
                    }else{
                        prev -> next = node -> next;
                    }
                    delete node;
                    --count;
                    return true;
                }
                prev = node;
                node = node -> next;
            }
            return false;
        }

        size_t size() const {
            return count;
        }

        bool empty() const{
            return count == 0;
        }
};

int main() {
    HashMap<std::string, int> ages;

    ages.insert("alice", 30);
    ages.insert("bob", 25);
    ages.insert("carol", 35);
    ages.insert("alice", 31);     // same key → updates, not a duplicate

    int age = 0;
    if (ages.find("alice", age)) {
        std::cout << "alice: " << age << "\n";    // alice: 31
    }
    if (!ages.find("dave", age)) {
        std::cout << "dave not found\n";          // dave not found
    }

    ages.remove("bob");
    std::cout << "size: " << ages.size() << "\n"; // 2
}