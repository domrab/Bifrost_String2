#include "String2.h"

#include <iostream>
#include <vector>

// helper function
//
void _string_to_code_points(
    Amino::String string,
    std::vector<unsigned int>& code_points
){
    code_points.clear();

    size_t len = string.size();

    size_t i = 0;

    while (i < len) {
        unsigned int cp = 0;

        const unsigned char c = (unsigned char)(string[i]);

        // ASCII, 1 byte: 0xxxxxxx
        if (c <= 0x7F) {
            cp = c;
            i++;
        }
        // 2 bytes: 110xxxxx 10xxxxxx
        else if ((c & 0xE0) == 0xC0) {
            if (i+1 >= len) {
                code_points.push_back(0);
                i++;
                continue;
            }

            const unsigned char c1 = (unsigned char)(string[i+1]);
            if ((c1 & 0xC0) != 0x80) {
                code_points.push_back(0);
                i++;
                continue;
            }

            // decode
            cp = ((c & 0x1F) << 6) | (c1 & 0x3F);

            // check overlong
            if (cp < 0x80) {
                code_points.push_back(0);
                i++;
                continue;
            }

            i += 2;
        }

        // 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
        else if ((c & 0xF0) == 0xE0) {
            if (i+2 >= len) {
                code_points.push_back(0);
                i++;
                continue;
            }

            const unsigned char c1 = (unsigned char)(string[i+1]);
            const unsigned char c2 = (unsigned char)(string[i+2]);
            if (((c1 & 0xC0) != 0x80) || ((c2 & 0xC0) != 0x80)) {
                code_points.push_back(0);
                i++;
                continue;
            }

            // decode
            cp = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);

            // check overlong and surrogates
            if (cp < 0x800 || (cp >= 0xD800 && cp <= 0xDFFF)) {
                code_points.push_back(0);
                i++;
                continue;
            }

            i += 3;
        }

        // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if ((c & 0xF8) == 0xF0) {
            if (i+3 >= len) {
                code_points.push_back(0);
                i++;
                continue;
            }

            const unsigned char c1 = (unsigned char)(string[i+1]);
            const unsigned char c2 = (unsigned char)(string[i+2]);
            const unsigned char c3 = (unsigned char)(string[i+3]);

            // Validate continuation bytes
            if (
                ((c1 & 0xC0) != 0x80) ||
                ((c2 & 0xC0) != 0x80) ||
                ((c3 & 0xC0) != 0x80)
            ){
                code_points.push_back(0);
                i++;
                continue;
            }

            // decode
            cp = (
                ((c & 0x07) << 18) |
                ((c1 & 0x3F) << 12) |
                ((c2 & 0x3F) << 6) |
                (c3 & 0x3F)
            );

            // check overlong and UTF-8 bounds
            if (cp < 0x10000 || cp > 0x10FFFF) {
                code_points.push_back(0);
                i++;
                continue;
            }

            i += 4;
        }
        // everything else is invalid
        else {
            code_points.push_back(0);
            i++;
            continue;
        }

        code_points.push_back(cp);
    }
}


// helper function
void add_code_point_to_string(
    const unsigned int& code_point,
    Amino::String& string
) {
    // return 0x00 and 0xFFFFFFFF as empty string
    if(code_point == 0) return;


    // 1 byte
    if (code_point <= 0x7F) {
        string += (char)(code_point);
    }

    // 2 bytes
    else if (code_point <= 0x7FF) {
        string += (char)(0xC0 | ((code_point >> 6) & 0x1F));  // 5 bits
        string += (char)(0x80 | (code_point & 0x3F));         // 6 bits
    }

    // 3 bytes
    else if (code_point <= 0xFFFF) {
        // Surrogate halves
        if (code_point >= 0xD800 && code_point <= 0xDFFF) return;

        string += (char)(0xE0 | ((code_point >> 12) & 0x0F));  // 4 bits
        string += (char)(0x80 | ((code_point >> 6) & 0x3F));   // 6 bits
        string += (char)(0x80 | (code_point & 0x3F));          // 6 bits
    }

    // 4 bytes
    else if (code_point <= 0x10FFFF) {
        string += (char)(0xF0 | ((code_point >> 18) & 0x07));      // 3 bits
        string += (char)(0x80 | ((code_point >> 12) & 0x3F));      // 6 bits
        string += (char)(0x80 | ((code_point >> 6) & 0x3F));       // 6 bits
        string += (char)(0x80 | (code_point & 0x3F));              // 6 bits
    }

    // code_points outside the valid range will do nothing
}

//------------------------------------------------------------------------------
//
void String2::string_to_code_points(
    const Amino::String& string,
    Amino::MutablePtr<Amino::Array<unsigned int>>& code_points
) {
    code_points = Amino::newMutablePtr<Amino::Array<unsigned int>>();
    assert(code_points != nullptr);

    std::vector<unsigned int> _codepoints;
    _string_to_code_points(string, _codepoints);

    for(auto& it=_codepoints.begin(); it!=_codepoints.end(); it++){
        code_points->push_back(*it);
    }
}

//------------------------------------------------------------------------------
//
void String2::code_points_to_string(
    Amino::Array<unsigned int> const& code_points,
    Amino::String& string
){
    string.clear();

    for(const unsigned int& cp : code_points){
        add_code_point_to_string(cp, string);
    }
}

//------------------------------------------------------------------------------
//
void String2::code_points_to_string(
    unsigned int code_points,
    Amino::String& string
){
    string.clear();
    add_code_point_to_string(code_points, string);
}