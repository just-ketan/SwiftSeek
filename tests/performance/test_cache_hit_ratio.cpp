#include "../../src//cache/lru_cache.hpp"
#include <cassert>
int main(){
    LRUCache<int, int> cache(2);    // capacity of 2
    cache.put(1,10);
    cache.put(2,20);
    cache.get(1);
    cache.put(3,30);

    assert(cache.contains(1));
    assert(cache.contains(2));
}