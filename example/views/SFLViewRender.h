#ifndef SFLVIEWRENDER_H
#define SFLVIEWRENDER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class SFLModelAbstract;
class SFLCameraVirtual;
class SFLViewRender: public QOpenGLWidget,
                     public QOpenGLFunctions
{
    Q_OBJECT

public:
    SFLViewRender(QWidget *parent);
    void setDelegate(SFLModelAbstract *delegate);
    SFLCameraVirtual *cameraVirtual();

public slots:
    void update();

protected:
    void paintGL() override;
    void initializeGL() override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    QPoint _currentPoint;
    SFLModelAbstract *_delegate = nullptr;
    SFLCameraVirtual *_camera = nullptr;
};

#endif // SFLVIEWRENDER_H
