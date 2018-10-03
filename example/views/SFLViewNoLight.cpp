#include "SFLViewNoLight.h"
#include "SFLModelNoLight.h"
#include "../common/SFLSelectorLayout.h"
#include "../common/SFLVec1Editor.h"
#include "../common/SFLVec3Editor.h"
#include <QLabel>

SFLViewNoLight::SFLViewNoLight(SFLModelAbstract *owner, QWidget *parent) : SFLViewAbstract(owner, parent)
{
    _types = QStringList({"顶点着色","纹理贴图"});
    _drawType = new SFLSelectorLayout("绘制方式");
    _drawType->setSelections(QStringList({"填充","线条"}));
    _direction = new SFLSelectorLayout("纹理方向");
    _direction->setSelections(QStringList({"默认","修正"}));
    _colorWeight = new SFLVec1Editor("颜色比重");
    _scale = new SFLVec3Editor("缩放", SFLVec3Editor::typePosition);
    _rotate = new SFLVec3Editor("旋转", SFLVec3Editor::typePosition);
    _move = new SFLVec3Editor("位移", SFLVec3Editor::typePosition);
    _viewAngle = new SFLVec1Editor("视角", SFLVec1Editor::typePosition);
    _viewFront = new SFLVec1Editor("近平面", SFLVec1Editor::typePosition);
    _viewFarther = new SFLVec1Editor("远平面", SFLVec1Editor::typePosition);

    setupUI();
    initData();
}
SFLViewNoLight::~SFLViewNoLight()
{
    disconnect(_drawType, &SFLSelectorLayout::selectChanged, this, &SFLViewNoLight::setIsOnlyDrawLine);
    disconnect(_direction, &SFLSelectorLayout::selectChanged, this, &SFLViewNoLight::setIsRightDir);
    disconnect(_colorWeight, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setColorWeight);
    disconnect(_scale, &SFLVec3Editor::changeValue, this, &SFLViewNoLight::setScale);
    disconnect(_rotate, &SFLVec3Editor::changeValue, this, &SFLViewNoLight::setRotate);
    disconnect(_move, &SFLVec3Editor::changeValue, this, &SFLViewNoLight::setOffset);
    disconnect(_viewAngle, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setViewAngle);
    disconnect(_viewFront, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setViewFront);
    disconnect(_viewFarther, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setViewFarther);
}

void SFLViewNoLight::initDataCamera()
{
    _viewAngle->setValue(45.0);
    _viewFront->setValue(0.1);
    _viewFarther->setValue(100.0);
}

void SFLViewNoLight::initData(){
    _colorWeight->setValue(0.4);
    _scale->setVec3Vals(1.0, 1.0, 1.0);
    _rotate->setVec3Vals(0.0, 0.0, 0.0);
    _move->setVec3Vals(0.0, 0.0, 0.0);
    initDataCamera();
}

void SFLViewNoLight::setupUI()
{
    QLabel *subTitle = new QLabel("沿坐标轴变换");
    subTitle->setContentsMargins(10, 5, 10, 0);
    QLabel *subTitle2 = new QLabel("视口设置");
    subTitle2->setContentsMargins(10, 5, 10, 0);

    _viewAngle->setSuffix("º");


    QVBoxLayout *layoutMain = static_cast<QVBoxLayout *>(layout());

    layoutMain->setContentsMargins(0,0,0,0);
    layoutMain->addLayout(_drawType);
    layoutMain->addLayout(_direction);
    layoutMain->addLayout(_colorWeight);
    layoutMain->addWidget(subTitle);
    layoutMain->addLayout(_scale);
    layoutMain->addLayout(_rotate);
    layoutMain->addLayout(_move);
    layoutMain->addWidget(subTitle2);
    layoutMain->addLayout(_viewAngle);
    layoutMain->addLayout(_viewFront);
    layoutMain->addLayout(_viewFarther);

    connect(_drawType, &SFLSelectorLayout::selectChanged, this, &SFLViewNoLight::setIsOnlyDrawLine);
    connect(_direction, &SFLSelectorLayout::selectChanged, this, &SFLViewNoLight::setIsRightDir);
    connect(_colorWeight, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setColorWeight);
    connect(_scale, &SFLVec3Editor::changeValue, this, &SFLViewNoLight::setScale);
    connect(_rotate, &SFLVec3Editor::changeValue, this, &SFLViewNoLight::setRotate);
    connect(_move, &SFLVec3Editor::changeValue, this, &SFLViewNoLight::setOffset);
    connect(_viewAngle, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setViewAngle);
    connect(_viewFront, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setViewFront);
    connect(_viewFarther, &SFLVec1Editor::changeValue, this, &SFLViewNoLight::setViewFarther);
}

void SFLViewNoLight::setIsOnlyDrawLine(int index)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setIsOnlyDrawLine(index != 0);
    emit needRender();
}

void SFLViewNoLight::setIsRightDir(int index)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setHasRightDirection(index != 0);
    emit needRender();
}

void SFLViewNoLight::setColorWeight(double weight)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setMixColorWeight(weight);
    emit needRender();
}
void SFLViewNoLight::setScale(double x, double y, double z){
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setScale(x, y, z);
    emit needRender();
}

void SFLViewNoLight::setRotate(double x, double y, double z){
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setRotate(x, y, z);
    emit needRender();
}

void SFLViewNoLight::setOffset(double x, double y, double z){
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setMove(x, y, z);
    emit needRender();
}

void SFLViewNoLight::setViewFront(double front)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setViewFront((float)front);
    emit needRender();
}
void SFLViewNoLight::setViewFarther(double farther)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setViewFarther((float)farther);
    emit needRender();
}
void SFLViewNoLight::setViewAngle(double angle)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setViewAngle((float)angle);
    emit needRender();
}

void SFLViewNoLight::changeViewBy(int index)
{
    SFLModelNoLight *owner = static_cast<SFLModelNoLight *>(_owner);
    owner->setHasTexture(index != 0);
    emit needRender();
}
