# RWrap - a simple yet powerful tool to seamlessly wrap C++ into R. #

Pretty much like Rcpp, but the other way around. Wrap your existing C++ code for use in R, from /outside/ R.

RWrap allows you to quickly publish C++ routines for use in R without any refactoring (provided you wrote them well, of course), and also takes care of generating the corresponding NAMESPACE and glue R script files for you.

1. [Steps to create an R package](#steps-to-create-an-r-package-using-rwrap-in-steps-6-and-8)
2. [Applying the RWrap magic](#rwrap-magic)
  1. [RWrap basics](#basics)
  2. [RWrap goodies](#goodies)
      1. [Named arguments](#named-arguments)
      2. [Pre- and Post- processing in glue code](#pre--and-post--processing-of-results-in-glue-code)
      3. [Implicit arguments](#implicit-arguments)
  3. [Wrapped types](#wrapped-types)
      1. [Base types](#base-types)
      2. [Lists](#lists)
      3. [Data frames](#data-frames)
      4. [Classes](#classes)
  4. [Extending RWrap](#extending-rwrap)


## Steps to create an R package (using RWrap, in steps 6 and 8): ##

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

C++ code:

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

#### Implicit arguments ####

In some specific cases, you might want to hide arguments from the R frontend.

Let's say you have this C++ code:

    some_type do_something(my_handle_t global_handle, other_type x) {
        ...
    }

But you wish to publish an R function that looks like:

    do_something(x)

You can then user implicit_arg() instead of arg() as follows:

    MODULE(myStuff)
        .reg(do_something).implicit_arg("an.R.expression").arg("x").auto_glue()
        ;

The generated glue code will be :

    do_something <- function(x) .Call(an.R.expression, x, package="myStuff")

### Wrapped types ###

#### Base types ####

Rwrap provides automatic wrapping of the following base types (followed by their R equivalents) :

- int (integer)
- bool (logical)
- char* and const char* (character)
- std::vector<SOMETHING> (vector)
- List (list)
- DataFrame (data.frame)

#### Lists ####

List makes it easy to bind complex data with R with a minimalistic interface.

    Rwrap::List myListReturn(...) {
        Rwrap::List ret;
        ret.add("name", some_value);
        ret.add("foobar", ...);
        return ret;
    }
    
    void myListArg(Rwrap::List l) {
        some_type foo = l["some_name"];  /* access by name (slow but quite safe) */
        some_other_type bar = l[1];      /* access by index (fast but less safe) */
        std::vector<some_wrapped_type> wow = l["how.hard.can.it.be"];
        ...
    }

#### Data frames ####

DataFrame is a simple extension to List. A data.frame in R is basically a list of columns (data vectors)
all the same length and each their own type. The main quirk is that string columns are converted into
factors. The automagic coercion is extended to handle those columns as either a vector of integers or
a vector of strings.

    Rwrap::DataFrame make_df(...) {
        std::vector<std::string> col1;
        std::vector<double> col2;
        std::vector<int> col3;
        col1.push_back("pouet");
        col2.push_back(23.);
        col3.push_back(42);
        ...
        Rwrap::DataFrame ret;
        ret.add("col.1", col1);
        ret.add("col.2", col2);
        ret.add("col.3", col3);
        return ret;
    }

    void use_df(Rwrap::DataFrame df, int string_col_index) {
        std::vector<int> factors = df[string_col_index];
        std::vector<const char*> strings = df[string_col_index];
        ...
    }

#### Classes ####

R features [Reference classes](http://www.inside-r.org/r-doc/methods/ReferenceClasses) since version 2.12
(see help(ReferenceClasses) from the R prompt). It's a quite neat and convenient way of doing OOP as far as
R goes. RWrap uses Reference classes to declare the wrappers to C++ classes.

This is a beta feature! It doesn't handle automagically inheritance yet.
Features supported:

- default and non-default (overloaded) constructors,
- NON-overloaded methods.
- automatic destructor implemented in the $delete() method.

The API here again tries to be as minimalistic as possible:

    class Foo {
    private:
        int wibble;
    public:
        Foo() : wibble(0) {}
        Foo(int x) : wibble(x) {}
        Foo(int x, bool neg) : wibble((1 - 2*neg) * x) {}

        void bar() { std::cout << x << std::endl; }
    };

    Foo* some_routine(int x) {
        return new Foo(0xdeadbeef * x);
    }

    CLASS(Foo)
        .ctor()
        .ctor<int>("x")
        .ctor<int, bool>("x", "x.is.neg")
        .method(Foo, bar).auto_glue()
        ;

    MODULE(my_example_module)
        .add_class(Foo)
        .reg(some_routine).arg("x").auto_glue()
        ;

The CLASS macro automatically defines a class wrapper object and the code to automatically wrap and unwrap
a pointer to instance.
From R this class can be used in the following way:

    > library(my_example_module)
    > foo <- Foo$new()  # calls the default constructor
    > foo$delete()  # destroys the instance
    > foo <- Foo$new(x=42, neg=F)
    > foo$bar()
    > foo$delete()


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

