#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class MyHashSet {
private:
    int num_buckets;
    vector<list<int>> buckets;

    // Helper function to calculate the hash index
    int hash(int key) {
        return key % num_buckets;
    }

public:
    MyHashSet() {
        // A prime number of buckets helps distribute keys evenly
        num_buckets = 769;
        buckets.resize(num_buckets);
    }
    
    void add(int key) {
        int index = hash(key);
        // Check if the key already exists to prevent duplicates
        auto it = find(buckets[index].begin(), buckets[index].end(), key);
        if (it == buckets[index].end()) {
            buckets[index].push_back(key);
        }
    }
    
    void remove(int key) {
        int index = hash(key);
        auto it = find(buckets[index].begin(), buckets[index].end(), key);
        // If the key is found, remove it from the list
        if (it != buckets[index].end()) {
            buckets[index].erase(it);
        }
    }
    
    bool contains(int key) {
        int index = hash(key);
        auto it = find(buckets[index].begin(), buckets[index].end(), key);
        // Return true if the key exists in the bucket list
        return it != buckets[index].end();
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */