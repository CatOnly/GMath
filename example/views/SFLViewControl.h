#ifndef SFLVIEWCONTROL_H
#define SFLVIEWCONTROL_H

#include <QDockWidget>

class QLabel;
class QPushButton;
class QVBoxLayout;
class SFLViewAbstract;
class SFLModelAbstract;
class SFLSelectorLayout;
class SFLViewControl: public QDockWidget
{
    Q_OBJECT

public:
    SFLViewControl(QWidget *parent = Q_NULLPTR);
    ~SFLViewControl();

    void setDelegate(SFLModelAbstract *delegate);

signals:
    void resetCamera();

public slots:
    void changeKinds(int index);
    void resetCameraBtnClicked();

private:
    QLabel *_titleLabel;
    SFLViewAbstract *_currentWidget;
    QVBoxLayout *_containerLayout;
    SFLSelectorLayout *_kindsLayout;

    QPushButton *_cameraResetBtn;
    SFLModelAbstract *_delegate = nullptr;

    void setupUI();
    void setCurrentWidget(SFLViewAbstract *widget);
};

#endif // SFLVIEWCONTROL_H
