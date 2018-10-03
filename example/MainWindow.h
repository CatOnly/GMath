#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SFLModelNoLight;
class SFLViewControl;
class SFLViewRender;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    SFLModelNoLight *_model;
    SFLViewRender  *_renderView;
    SFLViewControl *_controlView;

    void setupUI();
    void resetCamera();
};

#endif // MAINWINDOW_H
