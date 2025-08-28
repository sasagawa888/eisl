# At first
Please read this first.
The document folder contains various documents. Mainly explains how to use the library.

# Common
Please do as follows:

```
sudo make install
```

Some libraries need to be compiled. They use a C wrapper and will not work unless compiled. 
Please do as follows:

```
sudo make lisp
```

By default, the installation is kept light by compiling without the -flto option. To enable faster performance with -flto, please recompile as follows:

```
sudo make clean
sudo make install USE_FLTO=1

```


# Documents

## Library
![bit](BIT.md)

![combination](COMBINATION.md)

![compiler](COMPILER.md)

![complex](COMPLEX.md)

![csv](CSV.md)

![datetime](DATETIME.md)

![elixir](ELIXIR.md)

![escape](ESCAPE.md)

![formatter](FORMATTER.md)

![formula](FORMULA.md)

![functions](FUNCTIONS.md)

![functionsJ](FUNCTIONSJ.md)

![hash](HASH.md)

![lazy](LAZY.md)

![list](LIST.md)

![math](MATH.md)

![macro](MACRO.md)

![matrix](MATRIX.md)

![mexp](MEXP.md)

![opengl](OPENGL.md)

![prolog](PROLOG.md)

![seq](SEQ.md)

![sort](SORT.md)

![tcltk](TCLTK.md)

![tcpip](TCPIP.md)

![unixlibs](UNIXLIBS.md)

# Development
![debug](DEBUG.md)

![cross](CROSS.md)

![profiler](PROFILER.md)

![test](TEST.md)

![Edlis](EDLIS.md)

# Extension

![module](MODULE.md)

![unicode](UNICODE.md)

![ctrlchar](CTRLCHAR.md)

![chaitin](CHAITIN.md)

![parallel](PARA.md)

# Specification

![summary](SUMMARY.md)

![ISLisp](ISLISP.md)

![ISLisp(Japanese)](ISLISP-ja.md)

![verification](VERIFICATION.md)


# Other

![policy](POLICY.md)

![bench](BENCH.md)

