# $Id: Makefile.cancel.app 553128 2017-12-13 16:54:04Z satskyse $

APP = db95_cancel
SRC = cancel common

CPPFLAGS = -DHAVE_CONFIG_H=1 -DNEED_FREETDS_SRCDIR $(FTDS95_INCLUDE) \
           $(ORIG_CPPFLAGS)
LIB      = sybdb_ftds95$(STATIC) tds_ftds95$(STATIC)
LIBS     = $(FTDS95_CTLIB_LIBS) $(NETWORK_LIBS) $(RT_LIBS) $(C_LIBS)
LINK     = $(C_LINK)

CHECK_CMD  = test-db95 db95_cancel
CHECK_COPY = cancel.sql

CHECK_REQUIRES = in-house-resources

WATCHERS = ucko satskyse