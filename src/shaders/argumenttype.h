#ifndef ARGUMENTTYPE_H
#define ARGUMENTTYPE_H
#include <stdio.h>

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUniform.xhtml

enum ArgumentType {
    t1f,
    t2f,
    t3f,
    t4f,

    t1i,
    t2i,
    t3i,
    t4i,

    t1ui,
    t2ui,
    t3ui,
    t4ui,

    t1fv,
    t2fv,
    t3fv,
    t4fv,

    t1iv,
    t2iv,
    t3iv,
    t4iv,

    t1uiv,
    t2uiv,
    t3uiv,
    t4uiv,

    matrix2fv,
    matrix3fv,
    matrix4fv,

    matrix2x3fv,
    matrix3x2fv,
    matrix2x4fv,
    matrix4x2fv,
    matrix3x4fv,
    matrix4x3fv,
};


#endif // ARGUMENTTYPE_H
