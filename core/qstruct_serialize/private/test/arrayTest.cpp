#include "gtest/gtest.h"

#include "dynamicArray.tpp"
#include "qClass.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"

GEN_QOBJ(FooArr)
{
    GEN_QOBJ_BODY()
public:
    DynamicArray<float> arr {};
};

GEN_QSTRUCT_TYPE(FooArr,{
    GEN_QSTRUCT_FIELD_ENTRY(FooArr,arr)
})

TEST(ConverterTest, ArrayCheck)
{
    FooArr obj{};
    obj.arr.push_back(2);
    obj.arr.push_back(3);
    obj.arr.push_back(6);

    auto json = Converter().qstructToJson(&obj, obj.staticStruct);
    std::string source = json.stringify();

    FooArr a{};
    Converter().jsonToQStruct(std::get<json::Object>(json::Parser().parse(source)), FooArr::staticStruct, &a);


    EXPECT_EQ(a.arr[0],2);
    EXPECT_EQ(a.arr[1],3);
    EXPECT_EQ(a.arr[2],6);
}