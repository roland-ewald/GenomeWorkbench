# $Id: Makefile.iconv_fread.app 554130 2017-12-28 17:20:38Z ucko $

APP = tds100_iconv_fread
SRC = iconv_fread

CPPFLAGS = -DHAVE_CONFIG_H=1 $(FTDS100_INCLUDE) $(ORIG_CPPFLAGS)
LIB      = tds_ftds100$(STATIC)
LIBS     = $(FTDS100_CTLIB_LIBS) $(NETWORK_LIBS) $(RT_LIBS) $(C_LIBS)
LINK     = $(C_LINK)

CHECK_CMD  =

WATCHERS = ucko satskyse