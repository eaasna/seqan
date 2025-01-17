// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2024, Knut Reinert, FU Berlin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of Knut Reinert or the FU Berlin nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL KNUT REINERT OR THE FU BERLIN BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ==========================================================================
// Author: Kristin Knorr <kristin.knorr@fu-berlin.de>
// ==========================================================================
// Li10 reduction of AminoAcid alphabet
// ==========================================================================

#ifndef SEQAN_REDUCED_AMINOACID_LI10_BASE_H_
#define SEQAN_REDUCED_AMINOACID_LI10_BASE_H_

namespace seqan2 {

// ============================================================================
// Forwards
// ============================================================================

// ============================================================================
// Tags, Classes, Enums
// ============================================================================

// -----------------------------------------------------------------------
// Tag Li10
// -----------------------------------------------------------------------

/*!
 * @tag Li10
 * @brief Specialization for @link ReducedAminoAcid @endlink#
 * @headerfile seqan/reduced_aminoacid.h
 *
 * @signature typedef Li10 Tag<Li10_>;
 *
 * This is the 10-character reduction defined by Li et al,
 * 2003, <a href="https://www.ncbi.nlm.nih.gov/pubmed/12826723">https://www.ncbi.nlm.nih.gov/pubmed/12826723</a>
 *
 * Since it was created from the 20-letter alphabet the clusters in SeqAn are
 * not identical (they contain more symbols). This is the clustering:
 * @code{.txt}
 *   'A', // A S T X
 *   'B', // B D E Q Z
 *   'C', // C U
 *   'F', // F W Y *
 *   'G', // G
 *   'H', // H N
 *   'I', // I V
 *   'J', // J L M
 *   'K', // K O R
 *   'P', // P
 * @endcode
 *
 */

struct Li10_ {};

typedef Tag<Li10_> Li10;

// ============================================================================
// Metafunctions
// ============================================================================

// -----------------------------------------------------------------------
// Metafunction ValueSize
// -----------------------------------------------------------------------

template <>
struct ValueSize<SimpleType<unsigned char, ReducedAminoAcid_<Li10> > >
{
    typedef uint8_t Type;
    static const Type VALUE = 10;
};

// -----------------------------------------------------------------------
// Metafunction BitPerValue
// -----------------------------------------------------------------------

template <>
struct BitsPerValue<SimpleType<unsigned char, ReducedAminoAcid_<Li10> > >
{
    typedef uint8_t Type;
    static const Type VALUE = 4;
};

// -----------------------------------------------------------------------
// Translation Tables (implementations see extra files)
// -----------------------------------------------------------------------

// ============================================================================
// Functions
// ============================================================================

}
#endif // def SEQAN_REDUCED_AMINOACID_LI10_BASE_H_
