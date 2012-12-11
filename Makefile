
#####################################
# Configure this
PREFIX=/usr
CXXFLAGS=-ggdb
#
#####################################














INCLUDES=src/FuncTraits.h src/gen_wrap.h src/RWrap.h src/Value.h src/gen_method_wrap.h src/static_ctor.h
INCINST=$(PREFIX)/include/RWrap
BININST=$(PREFIX)/bin

RCFLAGS=$(shell R CMD config --cppflags)
RLDFLAGS=$(shell R CMD config --ldflags)
CXX=$(shell R CMD config CXX)


all: Rwrap

Rwrap: src/Rwrap.cc $(INCLUDES)
	$(CXX) $(RCFLAGS) $(CXXFLAGS) $< -ldl $(RLDFLAGS) -o $@


test: src/test_rwrap.cc $(INCLUDES)
	$(CXX) $(RCFLAGS) $(CXXFLAGS) $< -ldl $(RLDFLAGS) -o $@

clean:
	rm -f Rwrap test
	cd testshlib && make clean

install: $(INCLUDES) Rwrap
	mkdir -p $(INCINST)
	mkdir -p $(BININST)
	cp -va Rwrap $(BININST)
	cp -va $(INCLUDES) $(INCINST)
