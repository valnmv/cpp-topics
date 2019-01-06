# cpp-topics

Rule Of 5

Copy-and-swap, <https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom>

Guidelines Support Library (GSL), [gsl-lite](https://github.com/martinmoene/gsl-lite)

Testing [Catch2](https://github.com/catchorg/Catch2)

RAII

Exception safety

[Find memory leaks with the CRT library](https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2017)

Avoid slicing, clone()

Overload + override - method selection starts from given type of the variable, not from the 
actual type in case of pointer/reference. Even if there is better match in a derived class 
it will not be selected!
