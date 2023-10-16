
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

int main() {

}