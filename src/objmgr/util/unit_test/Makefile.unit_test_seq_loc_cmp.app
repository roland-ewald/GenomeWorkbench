# $Id: Makefile.unit_test_seq_loc_cmp.app 553638 2017-12-19 19:36:12Z vasilche $

APP = unit_test_seq_loc_cmp
SRC = unit_test_seq_loc_cmp

CPPFLAGS = $(ORIG_CPPFLAGS) $(BOOST_INCLUDE)

LIB = test_boost xobjutil $(SOBJMGR_LIBS)
LIBS = $(NETWORK_LIBS) $(DL_LIBS) $(ORIG_LIBS)

REQUIRES = Boost.Test.Included

CHECK_CMD =

WATCHERS = vasilche grichenk kornbluh