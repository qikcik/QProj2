#pragma once
#include "qInsDef.hpp"

class QObjDef : public QInsDef
{
public:
    QObjDef(
            std::string in_name,
            size_t in_size,
            const std::function<void(QIns* in_addr)>& in_constructInstance,
            const std::function<void(QIns* in_addr)>& in_destructInstance,
            DynamicArray<Field>&& in_fields
    ) : QInsDef(
            std::move(in_name),
            in_size,
            in_constructInstance,
            in_destructInstance,
            std::move(in_fields))
    {}
};


class QObj : public QIns
{
public:
    explicit QObj(const WeakPtr<QObjDef>& in_derivedObjDef) : objDef(in_derivedObjDef) {};
    virtual ~QObj() = default;

    const WeakPtr<QObjDef> objDef;
};