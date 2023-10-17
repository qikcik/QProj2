#include "gtest/gtest.h"

#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"
#include "fieldType/fields.hpp"

GEN_QSTRUCT(FooArr)
{
    GEN_QSTRUCT_BODY()
public:
    DynamicArray<float> arr {};
};

GEN_QSTRUCT_STATIC_DEF(FooArr, {
    GEN_INS_DEF_FIELD_ENTRY(FooArr, arr)
})

TEST(ConverterTest, ArrayCheck)
{
    FooArr obj{};
    obj.arr.push_back(2);
    obj.arr.push_back(3);
    obj.arr.push_back(6);

    auto json = Converter().qstructToJson(&obj, obj.staticDef);
    std::string source = json.stringify();

    FooArr a{};
    Converter().jsonToQStruct(std::get<json::Object>(json::Parser().parse(source)), FooArr::staticDef, &a);


    EXPECT_EQ(a.arr[0],2);
    EXPECT_EQ(a.arr[1],3);
    EXPECT_EQ(a.arr[2],6);
}