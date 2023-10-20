#pragma once
#include <functional>

template<typename TType>
class Observable
{
public:
    using element_type = TType;

    TType value;

    void notify() {
        for(auto& it : listeners)
            it(value);
    }

    void add(std::function<void(const TType&)> in_func) {
        listeners.push_back(std::move(in_func));
    }

    std::vector<std::function<void(const TType&)>> listeners;
};

