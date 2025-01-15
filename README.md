Two utility operators for converting UTF-8 strings to array<uint> and back.

# Motivation:
Currently nodes like `get_from_string`, `set_in_string`, or `slice_string` operate on the byte sequences like C++ strings. Effectively lacking support for multibyte encoded characters.
By converting a string to its code points first, we can get/set the n-th character in a string, regardless of the byte position and byte length.

# Installation
If you are on Windows and use Bifrost 2.12.0.0, you are in luck! Download the prebuild pack from [here](output/Bifrost2.12.0.0) and point your `BIFROST_LIB_CONFIG_FILES` to the `String2PackConfig.json` (tested on Maya 2024 and Maya 2025).
Else, follow the instructions for building from the [Autodesk website](https://help.autodesk.com/view/BIFROST/ENU/?guid=Bifrost_DevHelp_GettingStarted_Tutorials_GettingStartedWalkThrough_Build_html)

# Operators:
## string_to_code_points
`string [in, type:string]`
The string to convert. During conversion, invalid characters (byte sequences) are recorded as 0. As far as I know, strings cannot contain `\0` or `0x00` so this should be ok.
Surrogate halves and overlong characters are also treated as invalid.

`code_points [out, type:array<uint>]`
An array of uints containing the decimal code point value for valid byte sequences (even if they are empty in UTF-8) and `0` for invalid byte sequences.

## code_points_to_string
`code_points [in, type:uint|array<uint>]`
Either a single uint or an array of uints to convert to a string. `0`s are ignored, as are any values above `U+10FFFF`.

`string [out, type:string]`
The resulting string.

# Compounds:
## validate_string
`string [in, type:string]`
This compound uses `string_to_code_points` to convert all characters into their code points and then search for `0`. If there is no `0` in the code_points, this string is valid.

`valid [out, type:bool]`
Whether this string is valid or not
