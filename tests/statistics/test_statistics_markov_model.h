// ==========================================================================
//                 SeqAn - The Library for Sequence Analysis
// ==========================================================================
// Copyright (c) 2006-2021, Knut Reinert, FU Berlin
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
// Author: Manuel Holtgrewe <manuel.holtgrewe@fu-berlin.de>
// ===========================================================================
// Tests for the probability distribution code in seqan/random.
// ===========================================================================

#ifndef TEST_STATISTICS_TEST_MARKOV_MODEL_H_
#define TEST_STATISTICS_TEST_MARKOV_MODEL_H_

#include <seqan/basic.h>
#include <seqan/sequence.h>
#include <seqan/statistics.h>

SEQAN_DEFINE_TEST(test_statistics_markov_model)
{
    using namespace seqan;

    typedef Dna TAlphabet;
    typedef String<TAlphabet> TSequence;

    TSequence str2 = "CCCAAAGC";
    TSequence str3 = "CCCAAAGTAAATT";

    TSequence str1a =
            "AGAAGCCTCAGATGAGGAGGGTTTTGCTGTGTGCTGCAAGTATCAGGGAGAAAGCATTTCTGCCCTCTCT"
            "GGAACATGGTGTGAACTTCATCCCTGTAATGATATTGTTTGAATTTTCCATGAAAAATTGTCAGCATGAG"
            "AGTAAGAAAAGTGTACGATGGGAAAATATTGAACCAAACAGACAAAAATGGTAGAGTCACATGACCAGTT"
            "TACTCATTGGTAAAGTTAATGAGAGGGTGAGATTAAACAGAAATTGGTAAAGTTAATGAGAGGGTGAGAT"
            "TAAACAGAGGGTGAGATTAAACTTGGGAATGAGTTTGTCTGAGGAGTGAGGTGAAGCATCATTCCTCTGA"
            "TGCACAGGGTAAGGGTTTGTCTGTAAAGAGATAGCACAGGTGTCTGGAGAGCAGCGTGCATGGTAACCTG"
            "TCCTCCAGGCCAGTGGAGCTGTCTGTCTAACCTGGCCAAGGTACAGTCTTCATCAAAGGTCAGGATCCAG"
            "TCCATGCACAAGGGAGGAGCCATTTGCAGCAGAGCCCAGAAATGCCTCCTGCGACATCTTGTTTGTGTCA"
            "TTTACTAGAGTTGGCACTGTCTTAAGATGGGGGCATGGCTGACATTTTCAACTATCATCAGTGAGTCACT"
            "TGCCCAAATGAGGACCATGGTATTAATCTTGCATGTTTTTGGAACTGTTTAAAAAATGTCTGATTTTTGT"
            "TGTTTAGTGTCTGTTTTTGAATTTCCCCTTCTCTGCAGTTCTTGGTTTCTATCTCACTGAGTGCAGAGGA"
            "TTTTAATTGTTGCTGTCTATCTGTGCTTCGCAGCATGAGAGAGCAATGCCTACGGGCTCTTGTGGTGCTT"
            "TGGGGTTGACGGGTTTTATGTCTGAGCAAGCAGATGTCATAGTAGCCATGCTGGATTGCAGTAATAAATG"
            "TGTCCTTTTTTTCCTTCTGTAGCATTGAAAGCCGAAAAGAGAAGAAAGCTGACTCAGGGAAAGGTGTTGA"
            "CAGGGAGACTTGTCTATGACTCGATCTTCAATTTATTTTTTACATATATATGAGAAGAGTGTCACAATTA"
            "TTAATAAAACTGCTTTGATCATGTATTGTAAATTCTGTCCCTCAACCCAAATCCACCTTCATACTGTAAG"
            "TAGTGCAATACTTGTTTCATTTCTGTGTTTAAACTTCTGAGCAGTGAGACATCCCTGTGAGCAGATACAA"
            "TAGCCAATGCAAGAATCTGTGTGTTCCTTGCTGTACGTTAGACATTTGTAAACTGGATTCTGATTGTCAG"
            "TTTTATGAGAGCAATAGCTTCCTTAAAGAGATAAGTCATATTTACCTAGTTTGTATTTTCCTACTTTAGT"
            "GACCTGAAGATGCCTGATAATTTCATTCAGAAGAATTTTTGAAAGGTAGTCTTACTTCTTTTTAGTTTTT"
            "ATAGCTTAGCATTAGTGACTTATTTCAAAAGACCCAAATCAAAAAGTTAGTTTGAAAGCATTTTTTAATA"
            "ATTGTATTTATGCATTTCCTTGATTTAATATGATAAATTTAATACTTAACAATTTATATGTAACTAAAAC"
            "TTAAAGTCATTTGAAAAATATATAGAAACCTATTTACAACTTGTTAAGGACAATCAGACATAATGCAGAG"
            "TTAAGTAGTATTTGCTTAAAATTCAAGTTGTGACTAATGATCAAATACTAGGCTTGTACGAAATGCTTTA"
            "GAAAAACTTTGTAACAGTTTTGTGGGATTTTTCAATATAAACCTTTATCAGAAATATACTAAGTTTGTCT"
            "CCCACTGACAACAGATGTTTTCCAAATAAACATATTCTATACATACTTGTGGAATGCCACATGGTGAATC"
            "ATTGTATATGAAATTCCACTCCTGTACAGTTACTCTGCAGCTAATGGTCATGCACTGCTTAATGCTGGTC"
            "CTGAATCATGTTCTCATGTTAGACCAACAGCTCTCCAATTGTCATTTTTTTTCTGCAGAGTTTTTTTTTT"
            "CCACTTTTAAATTAAATGCATGTTGTGGAAAAACAGTCTTTTAAAATGAAATTTCAGATTCCATTTGAGA"
            "AGGTTCTGTAGATATTTCAGTCCATATAAAATAATACATCTTTACTAAACTTATATAAGGGGAGAGAAAG"
            "TTATGAAGTTTTGGACATTACTAAAAGTACAGTATTTGATTTCACTTTCAATGAATGTGAAGTTAATAAA"
            "ACTAAATCTCATAATGCTCTTGGTTCCTAAGAATGAGTAGTAATCATCAACTTTATAATACTCCAATATT"
            "CCGTTTTATAATAATTCAGAGCCCTGTGGCTTTTACACACCGTTAATTATGTACTCTGTTGGAAGTGCAC"
            "ATGAAAAGTGAAGAAAAGTTCCTCTTGTGATTAAACTAATGGGAGGAAATAAATCAACAAAGTCTCCATT"
            "AAGTTCTACATTTTGAGACCTTTTAAAAATTCCCCTCACAATTCTTTAAGGAGCCCCCCTTTTTATGGAA"
            "CATGAGCCTAAAAATTATAGAAAGAAGAATTTTAAGTTAATAAAGTTTGTATTTATAAATGCTGAAAAAA"
            "TACAGAAACTTTCTGTTCCAAATGTGTTGCTTTGTGTATTTTATAATACAGATACTACATTGTAAACATT"
            "TCCATTGTTTTATGATTTAGCCAGTGATTCCCCAAAGCAGCCTCTTAGTGTTTTAATATATTAATAACTG"
            "TTTTGTTAAAAATGATCATAGTGAATTTAAATCTTCACATGATCACCTATTTGAATAAGCAA";

    TSequence str1b =
            "TGAGGACCTCAGATGAGGAGGGTTTTGCTGTAAACAAGTATCAGGGAGAAAGCATTTCTGCCCTCTCTGC"
            "TGTGTGCTGCAAGTACTTCATCCCTGTAATGATATTGTTTGAATTTTCCATGAAAAATTGTCAGCATGAG"
            "AGTAAGAAAAGTGTACGATGGGAAAATATTGAACCAAACAGACAAAAATGGTAGAGTCACATGACCAGTT"
            "TACTCATTGGTAAAGTTAATGAGAGGGTGAGATTAAACAGAAATTGGTAAAGTTAATGAGAGGGTGAGAT"
            "TAAACAGAGGGTGAGATTAAACTTGGGAATGAGTTTGTCTGAGGAGTGAGGTGAAGCATCATTCCTCTGA"
            "TGCACAGGGTAAGGGTTTGTCTGTAAAGAGATAGCACAGGTGTCTGGAGAGCAGCGTGCATGGTAACCTG"
            "TCCTCCAGGCCAGTGGAGCTGTCTGTCTAACCTGGCCAAGGTACAGTCTTCATCAAAGGTCAGGATCCAG"
            "TCCATGCACAAGGGAGGAGCCATTTGCAGCAGAGCCCAGAAATGCCTCCTGCGACATCTTGTTTGTGTCA"
            "TTTACTAGAGTTGGCACTGTCTTAAGATGGGGGCATGGCTGACATTTTCAACTATCATCAGTGAGTCACT"
            "TGCCCAAATGAGGACCATGGTATTAATCTTGCATGTTTTTGGAACTGTTTAAAAAATGTCTGATTTTTGT"
            "TGTTTAGTGTCTGTTTTTGAATTTCCCCTTCTCTGCAGTTCTTGGTTTCTATCTCACTGAGTGCAGAGGA"
            "TTTTAATTGTTGCTGTCTATCTGTGCTTCGCAGCATGAGAGAGCAATGCCTACGGGCTCTTGTGGTGCTT"
            "TGGGGTTGACGGGTTTTATGTCTGAGCAAGCAGATGTCATAGTAGCCATGCTGGATTGCAGTAATAAATG"
            "TGTCCTTTTTTTCCTTCTGTAGCATTGAAAGCCGAAAAGAGAAGAAAGCTGACTCAGGGAAAGGTGTTGA"
            "CAGGGAGACTTGTCTATGACTCGATCTTCAATTTATTTTTTACATATATATGAGAAGAGTGTCACAATTA"
            "TTAATAAAACTGCTTTGATCATGTATTGTAAATTCTGTCCCTCAACCCAAATCCACCTTCATACTGTAAG"
            "TAGTGCAATACTTGTTTCATTTCTGTGTTTAAACTTCTGAGCAGTGAGACATCCCTGTGAGCATTTGCTG"
            "TAAAGCAAGAATCTGTGTGTTCCTTGCTGTACGTTAGACATTTGTAAACTGGATTCTGATTGTCAGTTTT"
            "ATGAGAGCAATAGCTTCCTTAAAGAGATAAGTCATATTTACCTAGTTTGTATTTTCCTACTTTAGTGACC"
            "TGAAGATGCCTGATAATTTCATTCAGAAGAATTTTTGAAAGGTAGTCTTACTTCTTTTTAGTTTTTATAG"
            "CTTAGCATTAGTGACTTATTTCAAAAGACCCAAATCAAAAAGTTAGTTTGAAAGCATTTTTTAATAATTG"
            "TATTTATGCATTTCCTTGATTTAATATGATAAATTTAATACTTAACAATTTATATGTAACTAAAACTTAA"
            "AGTCATTTGAAAAATATATAGAAACCTATTTACAACTTGTTAAGGACAATCAGACATAATGCAGAGTTAA"
            "GTAGTATTTGCTTAAAATTCAAGTTGTGACTAATGATCAAATACTAGGCTTGTACGAAATGCTTTAGAAA"
            "AACTTTGTAACAGTTTTGTGGGATTTTTCAATATAAACCTTTATCAGAAATATACTAAGTTTGTCTCCCA"
            "CTGACAACAGATGTTTTCCAAATAAACATATTCTATACATACTTGTGGAATGCCACATGGTGAATCATTG"
            "TATATGAAATTCCACTCCTGTACAGTTACTCTGCAGCTAATGGTCATGCACTGCTTAATGCTGGTCCTGA"
            "ATCATGTTCTCATGTTAGACCAACAGCTCTCCAATTGTCATTTTTTTTCTGCAGAGTTTTTTTTTTCCAC"
            "TTTTAAATTAAATGCATGTTGTGGAAAAACAGTCTTTTAAAATGAAATTTCAGATTCCATTTGAGAAGGT"
            "TCTGTAGATATTTCAGTCCATATAAAATAATACATCTTTACTAAACTTATATAAGGGGAGAGAAGTTTAC"
            "AAGGTAGTCTGGGATTACTAACAAAATAAACAAGAGCCTTTCTAGATAAATGTGTCCATATGCCAGTGCG"
            "GTTTAGGTCTTATTCAAGACACAAGTCATTACTT";
    TSequence str1c =
            "CATGGTGTGAACTTCATCCCTGTAATGATATTGTTTGAATTTTCCATGAAAAATTGTCAGCATGAGAGTA"
            "AGAAAAGTGTACGATGGGAAAATATTGAACCAAACAGACAAAAATGGTAGAGTCACATGACCAGTTTACT"
            "CATTGGTAAAGTTAATGAGAGGGTGAGATTAAACAGAAATTGGTAAAGTTAATGAGAGGGTGAGATTAAA"
            "CAGAGGGTGAGATTAAACTTGGGAATGAGTTTGTCTGAGGAGTGAGGTGAAGCATCATTCCTCTGATGCA"
            "CAGGGTAAGGGTTTGTCTGTAAAGAGATAGCACAGGTGTCTGGAGAGCAGCGTGCATGGTAACCTGTCCT"
            "CCAGGCCAGTGGAGCTGTCTGTCTAACCTGGCCAAGGTACAGTCTTCATCAAAGGTCAGGATCCAGTCCA"
            "TGCACAAGGGAGGAGCCATTTGCAGCAGAGCCCAGAAATGCCTCCTGCGAGTTTTGCTGTAAACAAGTAT"
            "CAGGGAGAAAGCATTTCTGCCCTCTCTGCTGTGTGCTGCAAGTACTTCATCCCTGTAATGATATTGTTTG"
            "AATTTTCCATGAAAAATTGTCAGCATGAGAGTAAGAAAAGTGTACGATGGGAAAATATTGAACCAAACAG"
            "ACAAAAATGGTAGAGTCACATGACCAGTTTACTCATTGGTAAAGTTAATGAGAGGGTGAGATTAAACAGA"
            "AATTGGTAAAGTTAATGAGAGGGTGAGATTAAACAGAGGGTGAGATTAAACTTGGGAATGAGTTTGTCTG"
            "AGGAGTGAGGTGAAGCATCATTCCTCTGATGCACAGGGTAAGGGTTTGTCTGTAAAGAGATAGCACAGGT"
            "GTCTGGAGAGCAGCGTGCATGGTAACCTGTCCTCCAGGCCAGTGGAGCTGTCTGTCTAACCTGGCCAAGG"
            "TACAGTCTTCATCAAAGGTCAGGATCCAGTCCATGCACAAGGGAGGAGCCATTTGCAGCAGAGCCCAGAA"
            "ATGCCTCCTGCGACATCTTGTTTGTGTCATTTACTAGAGTTGGCACTGTCTTAAGATGGGGGCATGGCTG"
            "ACATTTTCAACTATCATCAGTGAGTCACTTGCCCAAATGAGGACCATGGTATTAATCTTGCATGTTTTTG"
            "GAACTGTTTAAAAAATGTCTGATTTTTGTTGTTTAGTGTCTGTTTTTGAATTTCCCCTTCTCTGCAGTTC"
            "TTGGTTTCTATCTCACTGAGTGCAGAGGATTTTAATTGTTGCTGTCTATCTGTGCTTCGCAGCATGAGAG"
            "AGCAATGCCTACGGGCTCTTGTGGTGCTTTGGGGTTGACGGGTTTTATGTCTGAGCAAGCAGATGTCATA"
            "GTAGCCATGCTGGATTGCAGTAATAAATGTGTCCTTTTTTTCCTTCTGTAGCATTGAAAGCCGAAAAGAG"
            "AAGAAAGCTGACTCAGGGAAAGGTGTTGACAGGGAGACTTGTCTATGACTCGATCTTCAATTTATTTTTT"
            "ACATATATATGAGAAGAGTGTCACAATTATTAATAAAACTGCTTTGATCATGTATTGTAAATTCTGTCCC"
            "TCAACCCAAATCCACCTTCATACTGTAAGTAGTGCAATACTTGTTTCATTTCTGTGTTTAAACTTCTGAG"
            "CAGTGAGACATCCCTGTGAGCATTTGCTGTAAAGCAAGAATCTGTGTGTTCCTTGCTGTACGTTAGACAT"
            "TTGTAAACTGGATTCTGATTGTCAGTTTTATGAGAGCAATAGCTTCCTTAAAGAGATAAGTCATATTTAC"
            "CTAGTTTGTATTTTCCTACTTTAGTGACCTGAAGATGCCTGATAATTTCATTCAGAAGAATTTTTGAAAG"
            "GTAGTCTTACTTCTTTTTAGTTTTTATAGCTTAGCATTAGTGACTTATTTCAAAAGACCCAAATCAAAAA"
            "GTTAGTTTGAAAGCATTTTTTAATAATTGTATTTATGCATTTCCTTGATTTAATATGATAAATTTAATAC"
            "TTAACAATTTATATGTAACTAAAACTTAAAGTCATTTGAAAAATATATAGAAACCTATTTACAACTTGTT"
            "AAGGACAATCAGACATAATGCAGAGTTAAGTAGTATTTGCTTAAAATTC";

    StringSet<TSequence> X;
    appendValue(X, str1a);
    appendValue(X, str1b);
    appendValue(X, str1c);


    StringSet<TSequence> W;
    appendValue(W,str2);
    appendValue(W,str3);

     MarkovModel<TAlphabet> mm(1);
    buildMarkovModel(mm,X);

    double x = emittedProbability(mm,W);
    SEQAN_ASSERT_IN_DELTA(x, 1.25542e-05, 1.25542e-07);
    double x2 = mm.emittedProbability(W);
    SEQAN_ASSERT_IN_DELTA(x2, 1.25542e-05, 1.25542e-07);

    ensureAuxMatrices(mm);
}

#endif  // TEST_STATISTICS_TEST_MARKOV_MODEL_H_
