#pragma once

#include <optional>
#include <string>
#include <vector>

namespace wiremap::parser{
    struct Type{
        enum class BaseType{
            OBJECT,
            LIST,
            COLLECTION
        };

        enum class UnderlyingType{
            BIT,
            CHAR,
            BYTE,
            WORD,
            DWORD,
            QWORD,
            INTEGER,
            BOOL,
            REAL
        };
    private:
        static constexpr std::string_view COLLECTION_KEYWORD = "Collection";
        static constexpr std::string_view LIST_KEYWORD = "List";
        static constexpr std::string_view CONTAINER_TYPE_SPECIFIER = "of";

        BaseType base_type;

        unsigned list_size;

        std::vector<UnderlyingType> underlying_types;

        static Type parseObject(const std::string&);
        static Type parseList(const std::vector<std::string>&);
        static Type parseCollection(const std::vector<std::string>&);
    public:

        BaseType getBaseType()const;

        UnderlyingType getUnderlyingType()const;

        std::vector<UnderlyingType> getUnderlyingTypes()const;

        unsigned getListSize()const;

        static Type parse(const std::vector<std::string>&);
        static Type parse(const std::string&);

        std::string toString()const;
    };

    std::string asString(const Type::BaseType&);
}
