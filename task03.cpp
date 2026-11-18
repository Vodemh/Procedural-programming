#include "tasks.h"

#include <cstddef>
#include <iostream>
#include <string_view>

namespace
{
    bool is_continuation(unsigned char byte)
    {
        return (byte & 0xC0U) == 0x80U;
    }

    std::size_t utf8_length(std::string_view s)
    {
        std::size_t count = 0;
        for (unsigned char byte : s)
            if (!is_continuation(byte)) ++count;
        return count;
    }

    std::string_view utf8_prefix(std::string_view s, std::size_t n)
    {
        if (n == 0) return s.substr(0, 0);
        std::size_t count = 0;
        std::size_t i = 0;
        while (i < s.size())
        {
            const unsigned char byte = static_cast<unsigned char>(s[i]);
            std::size_t width = 1;
            if ((byte & 0xE0U) == 0xC0U) width = 2;
            else if ((byte & 0xF0U) == 0xE0U) width = 3;
            else if ((byte & 0xF8U) == 0xF0U) width = 4;
            if (count == n) break;
            i += width;
            ++count;
        }
        return s.substr(0, i);
    }
}

void task03()
{
    const std::string_view kyiv = "\xD0\x9A\xD0\xB8\xD1\x97\xD0\xB2";
    const std::string_view naive = "na\xC3\xAFve";
    const std::string_view emoji = "A\xF0\x9F\x98\x80" "B";
    const std::string_view latin = "Hello";

    const auto show = [](std::string_view label, std::string_view value)
    {
        std::cout << label << ": bytes=" << value.size()
                  << ", characters=" << utf8_length(value)
                  << ", prefix(2)=" << utf8_prefix(value, 2) << '\n';
    };

    show("Kyiv", kyiv);
    show("naive", naive);
    show("Emoji", emoji);
    show("Latin", latin);
    std::cout << "Kyiv substr(0, 3): " << kyiv.substr(0, 3) << '\n';
}
