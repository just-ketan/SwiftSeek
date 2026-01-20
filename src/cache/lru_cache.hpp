#pragma once
#include <unordered_map>
#include <list>
#include <stdexcept>

// O(1) get and put

template<typename KEY, typename VALUE>

class LRUCache{
    public:
        explicit LRUCache(size_t capacity) : capacity_(capacity){
            if(capacity_ == 0)   throw std::invalid_argument("LRUCache capacity must be greater than ZERO");
        }

        bool contains(const KEY& key) const {
            return map_.find(key)!=map_.end();
        }

        VALUE& get(const KEY& key){
            auto it = map_.find(key);
            if(it == map_.end())    throw std::out_of_range("Key not found in LRUCache !!!!");
            touch(it);  // moves iterator to the front of queue
            return it->second.first;
        }

        void put(const KEY& key, VALUE val){
            auto it = map_.find(key);
            if(it != map_.end()){
                // update existing key
                it->second.first = move(val);
                touch(it);
                return;
            }
            if(map_.size() >= capacity_){
                // time to evict
                evict();    // helper to evict
            }

            lru_.push_front(key);
            map_.emplace(key, std::make_pair(std::move(val), lru_.begin()));
        }

        size_t size() const noexcept{
            return map_.size();
        }

        void clear(){
            map_.clear();
            lru_.clear();
        }
    private:
        using ListIt = typename std::list<KEY>::iterator;
        size_t capacity_;
        std::list<KEY> lru_;
        std::unordered_map<KEY, std::pair<VALUE, ListIt>> map_; // maps key to value and the iterator

        void touch(typename std::unordered_map<KEY, std::pair<VALUE, ListIt>>::iterator it){
            lru_.erase(it->second.second);  // once accessed, update iterator
            lru_.push_front(it->first);
            it->second.second = lru_.begin();   // promote pointer to head
        }

        void evict(){
            const KEY& key = lru_.back();   // remove least frequent entry
            map_.erase(key);
            lru_.pop_back();
        }
};