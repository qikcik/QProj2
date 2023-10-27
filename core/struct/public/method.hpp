#pragma once
#include <string>
#include <utility>
#include "weakPtr.hpp"
#include "fieldType.hpp"

class QIns;
class Method
{
public:
    const std::string name {};
    const std::function<void(QIns* in_addr)> invoke;
};