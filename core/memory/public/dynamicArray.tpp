#pragma once
#include "dynamicArray.hpp"

template<typename TType>
DynamicArray<TType>::DynamicArray()
{
}

template<typename TType>
DynamicArray<TType>::~DynamicArray()
{
    clear();
}

template<typename TType>
DynamicArray<TType>::DynamicArray(const DynamicArray& other)
{
    reserve(other.capacity);
    for(auto& it : other)
        push_back(it);
}

template<typename TType>
DynamicArray<TType>::DynamicArray(DynamicArray&& other) noexcept
{
    array = other.array;
    capacity = other.capacity;
    length = other.length;

    other.array = nullptr;
    other.capacity = 0;
    other.length = 0;
}


template<typename TType>
size_t DynamicArray<TType>::get_length() const
{
    return length;
}

template<typename TType>
size_t DynamicArray<TType>::get_capacity() const
{
    return capacity;
}

template<typename TType>
const DynamicArray<TType>::element_type&
DynamicArray<TType>::operator[](size_t in_position) const
{
    return array[in_position];
}

template<typename TType>
DynamicArray<TType>::element_type&
DynamicArray<TType>::operator[](size_t in_position)
{
    return array[in_position];
}

template<typename TType>
void DynamicArray<TType>::push_back(element_type in_element) noexcept
{
    if (length == capacity)
        reserve(capacity + 8);

    if constexpr ( std::is_same_v<float, TType>)
        array[length] = in_element;
    else
        new (array + length) TType( std::move(in_element) );
    length++;
}

template<typename TType>
void DynamicArray<TType>::reserve(size_t in_capacity) noexcept
{
    if(in_capacity <= capacity)
        return;

    capacity = in_capacity;
    auto newArr = allocate_memory(capacity,sizeof(TType));
    for(int idx = 0; idx != length; idx++)
        new (newArr + idx) TType(std::move(array[idx]));

    if(array)
        delete[] (uint8_t*)array;
    array = newArr;
}


template<typename TType>
void DynamicArray<TType>::clear() noexcept
{
    if(!array) return;
    for(auto& it : *this)
        it.~TType();

    delete[] (uint8_t*)array;
    array = nullptr;
    capacity = 0;
    length = 0;
}


template<typename TType>
TType* DynamicArray<TType>::allocate_memory(size_t in_capacity,size_t in_elementSize) noexcept
{
    auto* bytePtr = new uint8_t[in_capacity * in_elementSize];
    auto memberPtr = reinterpret_cast<TType*>(bytePtr);
    return memberPtr;
}