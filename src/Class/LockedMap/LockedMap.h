#pragma once
#include <map>


template<typename TKey, typename TValue>
class LockedMap {
    
    std::map<TKey, TValue> map;

public:
    explicit LockedMap(const std::map<TKey, TValue> &init_map) : map(init_map) {
    }

    void update(const TKey key, const TValue new_val) {
        map[key] = new_val;
    }

    TValue get(const TKey key) const { return map.at(key); }
};
