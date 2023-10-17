
#include "dynamicArray.tpp"
#include "qInsDef.hpp"
#include "fieldType.hpp"
#include "converter.hpp"
#include "structMacros.hpp"
#include "parser.hpp"

GEN_QSTRUCT(FooArr)
{
GEN_QSTRUCT_BODY()
public:
    DynamicArray<float> arr {};
};

GEN_QSTRUCT_STATIC_DEF(FooArr, {
    GEN_INS_DEF_FIELD_ENTRY(FooArr, arr)
})

int main() {

}