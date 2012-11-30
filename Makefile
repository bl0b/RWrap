
#####################################
# Configure this
PREFIX=/usr
CXXFLAGS=-ggdb
#
#####################################














INCLUDES=FuncTraits.h gen_wrap.h RWrap.h Value.h
INCINST=$(PREFIX)/include/RWrap
BININST=$(PREFIX)/bin

RCFLAGS=$(shell R CMD config --cppflags)
RLDFLAGS=$(shell R CMD config --ldflags)
CXX=$(shell R CMD config CXX)


all: Rwrap

Rwrap: Rwrap.cc $(INCLUDES)
	$(CXX) $(RCFLAGS) $(RLDFLAGS) $(CXXFLAGS) $< -o $@


install: $(INCLUDES) Rwrap
	mkdir -p $(INCINST)
	mkdir -p $(BININST)
	cp -va Rwrap $(BININST)
	cp -va $(INCLUDES) $(INCINST)
