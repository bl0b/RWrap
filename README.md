# RWrap - a simple yet powerful tool to seamlessly wrap C++ into R. #

Pretty much like Rcpp, but the other way around. Wrap your existing C++ code for use in R, from /outside/ R.

RWrap allows you to quickly publish C++ routines for use in R without any refactoring (provided you wrote them well, of course), and also takes care of generating the corresponding NAMESPACE and glue R script files for you.

1. [Steps to create an R package](#steps-to-create-an-r-package-using-rwrap-in-step-6)
2. [Applying the RWrap magic](#rwrap-magic)
  1. [RWrap basics](#basics)
  2. [RWrap goodies](#goodies)
    1. [Named arguments](#named-arguments)
    2. [Pre- and Post- processing in glue code](#pre--and-post--processing-of-results-in-glue-code)
  3. [Wrapped types](#wrapped-types)
  4. [Extending RWrap](#extending-rwrap)


## Steps to create an R package (using RWrap, in step 6.): ##

1. Download RWrap. run **make && (sudo)? make install**
2. Create a directory for you future R package and an /src/ directory in there (this is necessary for R, read their [guide for writing extensions](http://cran.r-project.org/doc/manuals/R-exts.html#System-and-foreign-language-interfaces)).
3. Create a [DESCRIPTION file](http://cran.r-project.org/doc/manuals/R-exts.html#The-DESCRIPTION-file) in your package root.
4. Put all your sources in that /src/ directory.
5. If necessary, fill in that [/src/Makevars](http://cran.r-project.org/doc/manuals/R-exts.html#Using-Makevars) file.
6. Add the Rwrap include, module declaration, and register the routines you want published (see below, section RWrap magic).
7. Create the shared library with **R CMD SHLIB src/my_main_file src/other_files...** (R will use the name of the first file for the shared library)
8. Generate the NAMESPACE file and R/glue.R script by invoking **Rwrap src/my_main_file.so**
9. You're now ready to create the package with the R command **R CMD build .**
10. Install the package with **R CMD INSTALL my_package.tar.gz**, run **R**, issue **library(my_package)**.
11. ...
12. PROFIT!!!1!1!!oneoneone

Note most of those steps are R-specific.

## RWrap magic ##

### Basics ###

Let's say you have this C++ file :

    #include <vector>
    
    int sumsq(std::vector<int> x)
    {
        int accum = 0;
        std::vector<int>::iterator i, j = x.end();
        for (i = x.begin(); i != j; ++i) {
            int v = *i;
            accum += v * v;
        }
        return accum;
    }

To bind it to R, just add a #include at the top and a MODULE declaration at the bottom :


    #include <RWrap/RWrap.h>
    
    #include <vector>
    
    int sumsq(std::vector<int> x)
    {
        int accum = 0;
        std::vector<int>::iterator i, j = x.end();
        for (i = x.begin(); i != j; ++i) {
            int v = *i;
            accum += v * v;
        }
        return accum;
    }
    
    MODULE(myFileName)
        .reg(sumsq).auto_glue()
        ;

This will take care of everything, from two-way R<->C++ data wrapping (kinda like in Rcpp) to generating the NAMESPACE directives and the /.Call("sumsq", x)/ wrapper in R in the file R/glue.R.

### Goodies ###

#### Named arguments ####

The wrapper function in R will have by default arguments named a, b, c... If argument names are important and/or you want to specify default values, use the convenience arg() function between the calls to reg() and auto_glue().

    MODULE(spiderman)
        .reg(cast_web).arg("target").arg("size", "length(target)").auto_glue()

This will generate the following glue code :

    cast_web <- function(target, size=length(target)) .Call("cast_web", target, size, package="spiderman")

#### Pre- and Post- processing of results in glue code ####

It is also possible to wrap the result of the .Call in the glue code. Let's say for example you want to actually return a data.frame. The easiest way to achieve this is to return a List of columns and wrap this in a call to as.data.frame().

C++ code :

    Rwrap::List ledger() {
        Rwrap::List ret;
        std::vector<double> credit, debit;
        ...
        ret.add("credit", credit);
        ret.add("debit", debit);
        return ret;
    }
    
    MODULE(bruceWayne)
        .reg(ledger).wrap_result("as.data.frame(", ")").auto_glue()
        ;

The generated R glue will be :

    ledger <- function() as.data.frame(.Call("ledger", package="bruceWayne"))

### Wrapped types ###

Rwrap provides automatic wrapping of the following base types (followed by their R equivalents) :

- int (integer)
- bool (logical)
- char* and const char* (character)
- std::vector<SOMETHING> (vector)
- List (list)

List makes it easy to bind complex data with R with a minimalistic interface.

    Rwrap::List myListReturn(...) {
        Rwrap::List ret;
        ret.add("name", some_value);
        ret.add("foobar", ...);
        return ret;
    }
    
    void myListArg(List l) {
        some_type foo = l["some_name"];  /* access by name (slow but quite safe) */
        some_other_type bar = l[1];      /* access by index (fast but less safe) */
        std::vector<some_wrapped_type> wow = l["how.hard.can.it.be"];
        ...
    }

### Extending RWrap ###

Of course, it's easy to add new types to automatically wrap :

    namespace Rwrap {
        template <>
        struct Value<my_precious_type> {
            typedef my_precious_type CType;
            
            static CType coerceToC(SEXP rval) { ... }
            static SEXP coerceToR(CType cval) { ... }
        };
    }

