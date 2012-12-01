all: testshlib_1.0.tar.gz


testshlib_1.0.tar.gz: DESCRIPTION NAMESPACE R/glue.R src/testshlib.cc
	rm -f $@
	R CMD build .

NAMESPACE R/glue.R: src/testshlib.so
	Rwrap src/testshlib.so

src/testshlib.so: src/testshlib.cc
	R CMD SHLIB src/testshlib.cc

clean:
	rm -f testshlib_1.0.tar.gz src/testshlib.o src/testshlib.so
