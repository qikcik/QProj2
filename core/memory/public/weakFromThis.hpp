#pragma once
#include "weakPtr.hpp"

class WeakFromThis
{
public:
    virtual void setSelfWeak(WeakPtr<void> in_selfPtr) = 0;
};