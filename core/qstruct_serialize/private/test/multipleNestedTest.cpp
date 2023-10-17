#include "gtest/gtest.h"

#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"
#include "fieldType/fields.hpp"

GEN_QSTRUCT(Foo2)
{
    GEN_QSTRUCT_BODY()
public:
    DynamicArray<float> nums {};
};

GEN_QSTRUCT_STATIC_DEF(Foo2, {
    GEN_INS_DEF_FIELD_ENTRY(Foo2, nums),
})



GEN_QSTRUCT(Bar2)
{
GEN_QSTRUCT_BODY()
public:
    DynamicArray<DynamicArray<Foo2>> arr {};
};

GEN_QSTRUCT_STATIC_DEF(Bar2, {
    GEN_INS_DEF_FIELD_ENTRY(Bar2, arr),
})


TEST(ConverterTest2, Test)
{
    Bar2 bar {};
    bar.arr.push_back( DynamicArray<Foo2>() );
    bar.arr[0].push_back(Foo2());

    for(int i = 0 ; i != 18 ; i++)
    {
        bar.arr[0][0].nums.push_back(i*2);
    }

    auto json =  Converter().qstructToJson(&bar, bar.staticDef.getWeak());
    auto source = json.stringify();
    Bar2 bar2{};
    Converter().jsonToQStruct(std::get<json::Object>(json::Parser().parse(source)), Bar2::staticDef.getWeak(), &bar2);


    for(int i = 0 ; i != 18 ; i++)
    {
        EXPECT_EQ(bar.arr[0][0].nums[i], i*2);
    }
}
