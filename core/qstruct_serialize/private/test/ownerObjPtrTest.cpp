#include "gtest/gtest.h"

#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"
#include "fieldType/fields.hpp"
#include "qObjDef.hpp"

GEN_QOBJ(InnerObj)
{
GEN_QOBJ_BODY(InnerObj)
GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(InnerObj)
public:
    std::string name {};
};

GEN_QOBJ_STATIC_DEF(InnerObj, {
    GEN_INS_DEF_FIELD_ENTRY(InnerObj, name),
})


GEN_QOBJ(Foo3)
{
    GEN_QOBJ_BODY(Foo3)
    GEN_QOBJ_DEF_CONSTRUCTOR_AND_DESTRUCTOR(Foo3)
public:
    OwnerPtr<InnerObj> ptr {};
    WeakPtr<InnerObj> weakPtr;
};

GEN_QOBJ_STATIC_DEF(Foo3, {
    GEN_INS_DEF_FIELD_ENTRY(Foo3, ptr),
    GEN_INS_DEF_FIELD_ENTRY(Foo3, weakPtr),
})

TEST(OwnerObjTest, Test)
{
    Foo3 obj{Foo3::staticDef};
    obj.ptr = OwnerPtr<InnerObj>::CreateWithInstance(InnerObj::staticDef);
    obj.ptr.getPtr()->name = "Test";
    obj.weakPtr = obj.ptr;
    auto test1 = obj.ptr.getPtr();

    EXPECT_EQ(obj.ptr.getPtr()->name,"Test");
    auto json = Converter().qstructToJson(&obj,  Foo3::staticDef.getWeak() );
    std::string source = json.stringify();

    Foo3 res{Foo3::staticDef};
    Converter().jsonToQStruct(std::get<json::Object>(
            json::Parser().parse(source)),
            Foo3::staticDef.getWeak(),
            &res);

    auto test2 = res.ptr.getPtr();
    EXPECT_EQ(res.ptr.getPtr()->name,"Test");
    EXPECT_EQ(res.weakPtr.getPtr()->name,"Test");
}