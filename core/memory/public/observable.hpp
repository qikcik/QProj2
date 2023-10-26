#pragma once
#include <functional>

template<typename TType>
class Observable
{
public:
    using element_type = TType;

    TType value {};

    void notify() {
        for(auto& it : listeners)
            it();
    }

    void add(std::function<void()> in_func) {
        listeners.push_back(std::move(in_func));
    }

    DynamicArray<std::function<void()>> listeners;
};

