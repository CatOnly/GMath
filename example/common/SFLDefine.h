#ifndef SFLDEFINE_H
#define SFLDEFINE_H

#define DELETE_SAFE(pointer) \
    if (pointer != nullptr) {\
        delete pointer;\
        pointer = nullptr;\
    }

#endif // SFLDEFINE_H
