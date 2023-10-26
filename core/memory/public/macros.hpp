#pragma once
#include "concepts"

#define GEN_COPY_ASSIGMENT_OPERATOR(TType) TType& operator=(const TType& other) \
{ \
    if(this == &other) \
        return *this; \
    this->~TType(); \
    new (this) TType(other); \
    return *this; \
}

#define GEN_MOVE_ASSIGMENT_OPERATOR(TType) \
TType& operator=(TType&& other) noexcept \
{ \
    if(this == &other) \
        return *this; \
    this->~TType(); \
    new (this) TType(std::move(other)); \
    return *this; \
} \


#define DEBUG_ENSURE(value) if(!value) throw std::runtime_error{ (std::string(__FILE__ ) + " " + std::to_string(__LINE__)) };