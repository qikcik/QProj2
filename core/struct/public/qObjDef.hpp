#pragma once
#include <utility>

#include "qInsDef.hpp"

class QObjDef : public QInsDef
{
public:
    QObjDef(
            std::string in_name,
            size_t in_size,
            const WeakPtr<QObjDef>& in_baseObjDef,
            const std::function<void(QIns* in_addr)>& in_constructInstance,
            const std::function<void(QIns* in_addr)>& in_destructInstance,
            DynamicArray<Field>&& in_fields
    ) : QInsDef(
            std::move(in_name),
            in_size,
            in_constructInstance,
            in_destructInstance,
            std::move(in_fields)),
        baseObjDef(in_baseObjDef)
    {}

    const WeakPtr<QObjDef> baseObjDef {};
    DynamicArray<Field*> getAllFields() const override;
    Field * getField(const std::string &in_name) const override;
};


class QObj : public QIns, public WeakFromThis
{
public:
    explicit QObj(const WeakPtr<QObjDef>& in_derivedObjDef) : objDef(in_derivedObjDef) {};
    virtual ~QObj() = default;

    void setSelfWeak(WeakPtr<void> in_selfPtr) override {
        selfPtr = in_selfPtr.cast<QObj>();
    };

    WeakPtr<QObj> selfPtr;
    const WeakPtr<QObjDef> objDef;
    static const OwnerPtr<QObjDef> staticDef;
};