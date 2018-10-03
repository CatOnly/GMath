#include "SFLVec3Editor.h"
#include <QLabel>
#include <QDoubleSpinBox>

SFLVec3Editor::SFLVec3Editor(const QString title, SFLVec3Type type, QWidget *parent):QHBoxLayout(parent){
    _type = type;
    switch (type) {
    case typeColor:
        _widgetX = widgetColor();
        _widgetY = widgetColor();
        _widgetZ = widgetColor();
        break;
    case typePosition:
        _widgetX = widgetPosition();
        _widgetY = widgetPosition();
        _widgetZ = widgetPosition();
        break;
    }
    _titleLabel = new QLabel(title);

    setupUI();
}

SFLVec3Editor::~SFLVec3Editor()
{
    void (QDoubleSpinBox::*funPtr)(double);
    funPtr = &QDoubleSpinBox::valueChanged;
    disconnect(_widgetX, funPtr, this, &SFLVec3Editor::onValueChangedX);
    disconnect(_widgetY, funPtr, this, &SFLVec3Editor::onValueChangedY);
    disconnect(_widgetZ, funPtr, this, &SFLVec3Editor::onValueChangedZ);
}

void SFLVec3Editor::setupUI(){
    _titleLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    _titleLabel->setTextFormat(Qt::PlainText);
    _titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);

    addWidget(_titleLabel, 2);
    addWidget(_widgetX, 2);
    addWidget(_widgetY, 2);
    addWidget(_widgetZ, 2);

    void (QDoubleSpinBox::*funPtr)(double);
    funPtr = &QDoubleSpinBox::valueChanged;
    connect(_widgetX, funPtr, this, &SFLVec3Editor::onValueChangedX);
    connect(_widgetY, funPtr, this, &SFLVec3Editor::onValueChangedY);
    connect(_widgetZ, funPtr, this, &SFLVec3Editor::onValueChangedZ);
}

void SFLVec3Editor::hide()
{
    _titleLabel->hide();
    _widgetX->hide();
    _widgetY->hide();
    _widgetZ->hide();
}

void SFLVec3Editor::show()
{
    _titleLabel->show();
    _widgetX->show();
    _widgetY->show();
    _widgetZ->show();
}

void SFLVec3Editor::setVec3Vals(double x, double y, double z){
    _widgetX->setValue(x);
    _widgetY->setValue(y);
    _widgetZ->setValue(z);
}
void SFLVec3Editor::setVec3Vals(double x){
    setVec3Vals(x, x, x);
}

void SFLVec3Editor::setSuffix(QString sufffix){
    _widgetX->setSuffix(sufffix);
    _widgetY->setSuffix(sufffix);
    _widgetZ->setSuffix(sufffix);
}

void SFLVec3Editor::onValueChangedX(double x){
    emit changeValue(x, _widgetY->value(), _widgetZ->value());
}
void SFLVec3Editor::onValueChangedY(double y){
    emit changeValue(_widgetX->value(), y, _widgetZ->value());
}
void SFLVec3Editor::onValueChangedZ(double z){
    emit changeValue(_widgetX->value(), _widgetY->value(), z);
}

QDoubleSpinBox* SFLVec3Editor::widgetPosition(){
    QDoubleSpinBox *w = new QDoubleSpinBox();
    w->setDecimals(1);
    w->setSingleStep(1.0);

    return w;
}
QDoubleSpinBox* SFLVec3Editor::widgetColor(){
    QDoubleSpinBox *w = widgetPosition();
    w->setSingleStep(0.1);
    w->setRange(0, 1);

    return w;
}
