#include <cmath>
#include <array>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <limits.h>

using namespace std;
    
const size_t HASH_SIZE = 10000;

class hashmap {
    array<vector<pair<int,int>>,HASH_SIZE> arr;

    const size_t hash_func(const int val) const {
        const double A = 0.290415018593;
        double fractional = A*val - floor(A*val);
        return static_cast<int>(floor(HASH_SIZE * fractional));
    }

public:
    int& operator[](int key) {
        const size_t key2 = hash_func(key);
        if(arr[key2].size() > 0) {
            for(pair<int,int>& p: arr[key2]) {
                if(p.first == key)
                    return p.second;
            }
        }
        arr[key2] = {{key, 0}};
        return arr[key2][0].second;
    }

    bool find(int key) const {
        const size_t key2 = hash_func(key);
        if(arr[key2].size() > 0) {
            for(const pair<int,int>& p: arr[key2]) {
                if(p.first == key)
                    return true;
            }
        }
        return false;
    }

    void insert(int key, int val) {
        const size_t key2 = hash_func(key);
        if(arr[key2].size() > 0) {
            for(pair<int,int>& p: arr[key2]) {
                if(p.first == key) {
                    p.second = val;
                    return;
                }
            }
        }
        arr[key2].push_back({key,val});
    }

    int& get(int key) {
        const size_t key2 = hash_func(key);
        if(arr[key2].size() > 0) {
            for(pair<int,int>& p: arr[key2]) {
                if(p.first == key)
                    return p.second;
            }
        }
        throw runtime_error("hashmap key not found");
    }
};

int main(void) {
    hashmap hash;
    hash.insert(128, 10);
    if(hash.find(128)) {
        cout << "128 found, value: " << hash.get(128) << endl;
    } else 
        cout << "128 not found" << endl;
}