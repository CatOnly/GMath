#include "MainWindow.h"
#include "SFLModelNoLight.h"
#include "views/SFLViewRender.h"
#include "views/SFLViewControl.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _model = new SFLModelNoLight();
    _renderView  = new SFLViewRender(this);
    _controlView = new SFLViewControl(this);

    _model->setDelegate(_renderView->cameraVirtual());
    _controlView->setDelegate(_model);
    _renderView->setDelegate(_model);
    SFLModelAbstract::currentUseWidget = _model;

    setupUI();
}

MainWindow::~MainWindow()
{
    disconnect(_model->view(), &SFLViewAbstract::needRender, _renderView, &SFLViewRender::update);
    disconnect((SFLViewControl *)_controlView, &SFLViewControl::resetCamera, this, &MainWindow::resetCamera);
}

void MainWindow::setupUI()
{
    setCentralWidget(_renderView);
    addDockWidget(Qt::RightDockWidgetArea, _controlView);

    QRect deskRect = QApplication::desktop()->availableGeometry();
    setGeometry((deskRect.width() - width()) * 0.5, (deskRect.height() - height()) * 0.5, width(), height());
    setFixedSize(_renderView->width() + _controlView->width(), _renderView->height());
    setWindowTitle("Keep Reading , Keep Writing , Keep Coding");

    connect(_model->view(), &SFLViewAbstract::needRender, _renderView, &SFLViewRender::update);
    connect((SFLViewControl *)_controlView, &SFLViewControl::resetCamera, this, &MainWindow::resetCamera);
}

void MainWindow::resetCamera()
{
//    _renderView->cameraVirtual()->resetData();
    _renderView->update();
}
