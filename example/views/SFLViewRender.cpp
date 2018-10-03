#include <QDebug>
#include <QKeyEvent>
#include "SFLViewRender.h"
#include "../common/SFLModelAbstract.h"
#include "SFLCameraVirtual.h"

SFLViewRender::SFLViewRender(QWidget *parent):QOpenGLWidget(parent)
{
    _camera = new SFLCameraVirtual(glm::vec3(0.0, 0.0, 3.0));
    setFixedSize(700, 700);
}

void SFLViewRender::paintGL()
{
    if (!_delegate) return;

    _delegate->render();

    qDebug() << __func__ << _delegate;
}

void SFLViewRender::initializeGL()
{
    initializeOpenGLFunctions();

    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    QOpenGLContext *defaultCtx = context();
    GLint attributeNumber;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attributeNumber);
    qDebug() << "Has default context: " <<  (defaultCtx != nullptr ? "Yes" : "No") << endl
             << "Default context is current context: " << (defaultCtx == ctx ? "Yes" : "No")  << endl
             << "Renderer: " << (const char*)glGetString(GL_RENDERER) << endl
             << "Version:  " << (ctx->isOpenGLES() ? "OpenGL ES" : "OpenGL") << (const char*)glGetString(GL_VERSION) << endl
             << "Shader Version:" << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << endl
             << "R:" << ctx->format().redBufferSize() << endl
             << "G:" << ctx->format().greenBufferSize() << endl
             << "B:" << ctx->format().blueBufferSize() << endl
             << "A:" << ctx->format().alphaBufferSize() << endl
             << "Depth:   " << ctx->format().depthBufferSize() << endl
             << "Stencil: " << ctx->format().stencilBufferSize() << endl
             << "Pixel Radio: " << devicePixelRatio() << endl
             << "Support Attribute Number: " << attributeNumber << endl;

    const int pixelRadio = devicePixelRatio();
    glViewport(0, 0, pixelRadio * width(), pixelRadio * height());
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void SFLViewRender::keyPressEvent(QKeyEvent *event)
{
    QString keyName;
    switch(event->key()){
    case Qt::Key_W:
    case Qt::Key_Up:
//        _camera->moveStepFromDirection(SFLCameraVirtual::moveForward);
        keyName = "W";
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
//        _camera->moveStepFromDirection(SFLCameraVirtual::moveBackward);
        keyName = "S";
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
//        _camera->moveStepFromDirection(SFLCameraVirtual::moveLeft);
        keyName = "A";
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
//        _camera->moveStepFromDirection(SFLCameraVirtual::moveRight);
        keyName = "D";
        break;
    }
    qDebug() << "Key Press " << keyName;

    update();
//    QMetaObject::invokeMethod(this, "update", Qt::DirectConnection);
}

void SFLViewRender::mousePressEvent(QMouseEvent *event)
{
    _currentPoint = event->pos();
    update();
}
void SFLViewRender::mouseMoveEvent(QMouseEvent *event)
{
    QPoint offsetPos = event->pos() - _currentPoint;
//    _camera->rotateByMouseOffset(offsetPos.x(), offsetPos.y());
    update();
}
void SFLViewRender::mouseReleaseEvent(QMouseEvent *event)
{
    setFocus();
    update();
}

void SFLViewRender::setDelegate(SFLModelAbstract *delegate)
{
    if (delegate != nullptr && delegate != _delegate){
        _delegate = delegate;
        _delegate->initializeOpenGLFunctions();
        setFocus();
    }
    update();
}

void SFLViewRender::update()
{
    QOpenGLWidget::update();
}

SFLCameraVirtual* SFLViewRender::cameraVirtual()
{
    return _camera;
}
