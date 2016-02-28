#pragma once
#include <type_traits>

#define EnumFlagOperators(a_EnumType) \
inline a_EnumType operator | (a_EnumType a_Value1, a_EnumType a_Value2) \
{ \
    return EnumUtility::bitwiseEnumOR(a_Value1, a_Value2); \
} \
\
inline a_EnumType operator & (a_EnumType a_Value1, a_EnumType a_Value2) \
{ \
    return EnumUtility::bitwiseEnumAND(a_Value1, a_Value2); \
} \
\
inline a_EnumType operator ^ (a_EnumType a_Value1, a_EnumType a_Value2) \
{ \
   return EnumUtility::bitwiseEnumXOR(a_Value1, a_Value2); \
}

class EnumUtility
{
public:
    template<typename TEnumType>
    static TEnumType bitwiseEnumOR(TEnumType a_Value1, TEnumType a_Value2)
    {
        return static_cast<TEnumType>(static_cast<std::underlying_type<TEnumType>::type>(a_Value1) |
            static_cast<std::underlying_type<TEnumType>::type>(a_Value2));
    }

    template<typename TEnumType>
    static TEnumType bitwiseEnumAND(TEnumType a_Value1, TEnumType a_Value2)
    {
        return static_cast<TEnumType>(static_cast<std::underlying_type<TEnumType>::type>(a_Value1) &
            static_cast<std::underlying_type<TEnumType>::type>(a_Value2));
    }

    template<typename TEnumType>
    static TEnumType bitwiseEnumXOR(TEnumType a_Value1, TEnumType a_Value2)
    {
        return static_cast<TEnumType>(static_cast<std::underlying_type<TEnumType>::type>(a_Value1) ^
            static_cast<std::underlying_type<TEnumType>::type>(a_Value2));
    }
};