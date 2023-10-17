#include "gtest/gtest.h"

#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"
#include "fieldType/fields.hpp"

GEN_QSTRUCT(Foo)
{
    GEN_QSTRUCT_BODY()
public:
    Foo() = default;
    Foo(float in_x,float in_y, float in_z, const std::string& in_text) : x(in_x), y(in_y), z(in_z), text(in_text){};
    float x {};
    float y {};
    float z {};

    std::string text {};
};

GEN_QSTRUCT_STATIC_DEF(Foo, {
    GEN_INS_DEF_FIELD_ENTRY(Foo, x),
    GEN_INS_DEF_FIELD_ENTRY(Foo, y),
    GEN_INS_DEF_FIELD_ENTRY(Foo, z),
    GEN_INS_DEF_FIELD_ENTRY(Foo, text),
})

GEN_QSTRUCT(Bar)
{
GEN_QSTRUCT_BODY()
public:
    std::string text {};
    Foo foo {};
    DynamicArray<Foo> arr {};

};

GEN_QSTRUCT_STATIC_DEF(Bar, {
    GEN_INS_DEF_FIELD_ENTRY(Bar, text),
    GEN_INS_DEF_FIELD_ENTRY(Bar, foo),
    GEN_INS_DEF_FIELD_ENTRY(Bar, arr),
})



TEST(ConverterTest, Test)
{
    Bar bar {};
    bar.text = "lorem";
    bar.foo.x = 1;
    bar.foo.y = 2;
    bar.foo.z = 3;
    bar.foo.text = "lorem ipsum";

    bar.arr.push_back({1,2,3,"lorem ipsum"});
    bar.arr.push_back({4,5,6,"ipsum lorem"});

    auto json =  Converter().qstructToJson(&bar, Bar::staticDef.getWeak());
    auto source = json.stringify();
    Bar bar2{};
    Converter().jsonToQStruct(std::get<json::Object>(json::Parser().parse(source)), Bar::staticDef.getWeak(), &bar2);
    EXPECT_EQ(bar2.foo.x,1);
    EXPECT_EQ(bar2.foo.y,2);
    EXPECT_EQ(bar2.foo.z,3);
    EXPECT_EQ(bar2.foo.text,"lorem ipsum");

    EXPECT_EQ(bar2.arr[0].text,"lorem ipsum");
    EXPECT_EQ(bar2.arr[1].text,"ipsum lorem");
}
