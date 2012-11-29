all: test_shlib_1.0.tar.gz


test_shlib_1.0.tar.gz: DESCRIPTION NAMESPACE R/glue.R src/test_shlib.cc
	R CMD BUILD .

NAMESPACE R/glue.R: src/test_shlib.so
	Rwrap src/test_shlib.so

src/test_shlib.so: src/test_shlib.cc
	R CMD SHLIB src/test_shlib.cc

