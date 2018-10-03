#ifndef SFLMODELABSTRACT_H
#define SFLMODELABSTRACT_H

#include "SFLDefine.h"
#include "SFLToolBtn.h"
#include "SFLViewAbstract.h"
#include <QOpenGLFunctions>

#include "SFLCameraVirtual.h"

class SFLModelAbstract:public QOpenGLFunctions
{
public:
    static SFLModelAbstract *currentUseWidget;

    SFLModelAbstract();

    virtual ~SFLModelAbstract();
    virtual void render() = 0;
    virtual void initializeOpenGL() = 0;

    void initializeOpenGLFunctions();
//    void setDelegate(SFLCameraVirtual * delegate);

    SFLViewAbstract *view();
    SFLToolBtn *toolBtn();

protected:
    int _times;
    bool _hasInitialized = false;
    SFLViewAbstract *_view = nullptr;
    SFLToolBtn *_btn = nullptr;
//    SFLCameraVirtual *_delegateCamaera = nullptr;
};
#endif // SFLMODELABSTRACT_H
