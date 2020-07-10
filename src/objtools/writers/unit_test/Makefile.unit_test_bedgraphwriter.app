# $Id: Makefile.unit_test_bedgraphwriter.app 590760 2019-08-04 21:12:21Z vakatov $

APP = unit_test_bedgraphwriter
SRC = unit_test_bedgraphwriter
LIB = xunittestutil xobjwrite variation_utils $(OBJREAD_LIBS) xalnmgr xobjutil gbseq entrez2cli entrez2 \
        tables test_boost $(OBJMGR_LIBS)

LIBS = $(GENBANK_THIRD_PARTY_LIBS) $(CMPRS_LIBS) $(NETWORK_LIBS) $(DL_LIBS) $(ORIG_LIBS)

CPPFLAGS = $(ORIG_CPPFLAGS) $(BOOST_INCLUDE)

REQUIRES = Boost.Test.Included

CHECK_CMD  =
CHECK_COPY = bedgraphwriter_test_cases

WATCHERS = ludwigf