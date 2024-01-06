#ifndef TEXTURESTATUS_H
#define TEXTURESTATUS_H

#include <string>

struct TextureStatus {
    bool imported = false;
    bool failed = false;
    std::string errorText = "";
};


#endif // TEXTURESTATUS_H
