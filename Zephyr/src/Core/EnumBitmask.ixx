export module Zephyr.Core.EnumBitmask;

import std;

export namespace EnumBitmask
{
    template <typename TEnum>
        requires std::is_enum_v<TEnum>
    struct EnumWrapper
    {
        TEnum Value{};

        [[nodiscard]] constexpr explicit operator bool() const noexcept
        {
            return Value != TEnum{ 0 };
        }

        [[nodiscard]] constexpr operator TEnum() const noexcept
        {
            return Value;
        }
    };

    template <typename TEnum>
    EnumWrapper(TEnum) -> EnumWrapper<TEnum>;
}


export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
[[nodiscard]] constexpr EnumBitmask::EnumWrapper<TEnum>
operator&(TEnum lhs, TEnum rhs) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    return EnumBitmask::EnumWrapper<TEnum>
    {
        static_cast<TEnum>(
            static_cast<UnderlyingType>(lhs)&
            static_cast<UnderlyingType>(rhs))
    };
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
[[nodiscard]] constexpr EnumBitmask::EnumWrapper<TEnum>
operator|(TEnum lhs, TEnum rhs) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    return EnumBitmask::EnumWrapper<TEnum>
    {
        static_cast<TEnum>(
            static_cast<UnderlyingType>(lhs) |
            static_cast<UnderlyingType>(rhs))
    };
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
[[nodiscard]] constexpr EnumBitmask::EnumWrapper<TEnum>
operator^(TEnum lhs, TEnum rhs) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    return EnumBitmask::EnumWrapper<TEnum>
    {
        static_cast<TEnum>(
            static_cast<UnderlyingType>(lhs) ^
            static_cast<UnderlyingType>(rhs))
    };
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
[[nodiscard]] constexpr TEnum operator~(TEnum value) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    return static_cast<TEnum>(~static_cast<UnderlyingType>(value));
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
constexpr TEnum& operator&=(TEnum& lhs, TEnum rhs) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    lhs = static_cast<TEnum>(
        static_cast<UnderlyingType>(lhs) &
        static_cast<UnderlyingType>(rhs));

    return lhs;
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
constexpr TEnum& operator|=(TEnum& lhs, TEnum rhs) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    lhs = static_cast<TEnum>(
        static_cast<UnderlyingType>(lhs) |
        static_cast<UnderlyingType>(rhs));

    return lhs;
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
constexpr TEnum& operator^=(TEnum& lhs, TEnum rhs) noexcept
{
    using UnderlyingType = std::underlying_type_t<TEnum>;

    lhs = static_cast<TEnum>(
        static_cast<UnderlyingType>(lhs) ^
        static_cast<UnderlyingType>(rhs));

    return lhs;
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
[[nodiscard]] constexpr bool HasFlag(TEnum value, TEnum flag) noexcept
{
    using U = std::underlying_type_t<TEnum>;

    return (static_cast<U>(value) & static_cast<U>(flag)) == static_cast<U>(flag);
}

export template <typename TEnum>
    requires (std::is_enum_v<TEnum>)
[[nodiscard]] constexpr bool HasFlag(EnumBitmask::EnumWrapper<TEnum> value, TEnum flag) noexcept
{
    return HasFlag(static_cast<TEnum>(value), flag);
}
