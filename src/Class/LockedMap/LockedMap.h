#pragma once
#include <map>
#include <optional>

template<typename TKey, typename TValue>
class LockedMap {
    
    std::map<TKey, TValue> map;

public:
    explicit LockedMap(const std::map<TKey, TValue> &init_map) : map(init_map) {
    }

    void update(const TKey key, const TValue new_val) {
        map[key] = new_val;
    }

    std::optional<TValue> get(const TKey key) const
    {
        if (auto search = map.find(key); search != map.end()) {
            return map.at(key);
        }
        return {};
    }
};
