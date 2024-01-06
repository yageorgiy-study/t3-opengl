#ifndef COMPILESTATUS_H
#define COMPILESTATUS_H
#include <stdio.h>

struct CompileStatus {
    bool compiled = false;
    bool failed = false;
    std::string errorText = "";
};


#endif // COMPILESTATUS_H
