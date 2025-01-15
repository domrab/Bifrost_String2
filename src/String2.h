//-
// =============================================================================
// Copyright 2022 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// =============================================================================
//+

#ifndef STRING2_H
#define STRING2_H

#include "String2Export.h"

#include <Amino/Core/String.h>
#include <Amino/Core/Array.h>
#include <Amino/Core/Ptr.h>
#include <Amino/Cpp/Annotate.h>

namespace String2 {

//------------------------------------------------------------------------------
//
/// \brief Convert a UTF-8 string to code points.
STRING2_DECL void string_to_code_points(
    const Amino::String& string,
    Amino::MutablePtr<Amino::Array<unsigned int>>& code_points
) AMINO_ANNOTATE("Amino::Node");

//------------------------------------------------------------------------------
//
/// \brief Convert code points to a string.
STRING2_DECL void code_points_to_string(
    Amino::Array<unsigned int> const& code_points,
    Amino::String& string
) AMINO_ANNOTATE("Amino::Node");

//------------------------------------------------------------------------------
//
/// \brief Convert a single code point to a string. This is the default
/// overload because it allows manual inputting a code point for string
/// generation. If one has an array already, that can be plugged in
/// directly.
STRING2_DECL void code_points_to_string(
    unsigned int code_points,
    Amino::String& string
) AMINO_ANNOTATE("Amino::Node Amino::DefaultOverload");

} // namespace String2


#endif // STRING2_H
