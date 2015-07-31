#ifndef NDEBUG
    #include <stdio.h>
#else
    #define NOP do { } while(0)
    #define printf(szFormat, ...) NOP
#endif
