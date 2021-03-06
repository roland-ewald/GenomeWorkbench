# $Id: Makefile.pending.app 554151 2017-12-28 18:34:57Z ucko $

APP = db100_pending
SRC = pending common

CPPFLAGS = -DHAVE_CONFIG_H=1 -DNEED_FREETDS_SRCDIR $(FTDS100_INCLUDE) \
           $(ORIG_CPPFLAGS)
LIB      = sybdb_ftds100$(STATIC) tds_ftds100$(STATIC)
LIBS     = $(FTDS100_CTLIB_LIBS) $(NETWORK_LIBS) $(RT_LIBS) $(C_LIBS)
LINK     = $(C_LINK)

CHECK_CMD  = test-db100 db100_pending
CHECK_COPY = pending.sql

CHECK_REQUIRES = in-house-resources

WATCHERS = ucko satskyse
