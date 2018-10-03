#ifndef SFLVIEWNOLIGHT_H
#define SFLVIEWNOLIGHT_H

#include "../common/SFLViewAbstract.h"

class SFLVec1Editor;
class SFLVec3Editor;
class SFLSelectorLayout;
class SFLViewNoLight : public SFLViewAbstract
{
    Q_OBJECT

public:
    explicit SFLViewNoLight(SFLModelAbstract *owner, QWidget *parent = nullptr);
    ~SFLViewNoLight();

public slots:
    void initDataCamera() override;
    void changeViewBy(int index) override;
    void setIsOnlyDrawLine(int index);
    void setIsRightDir(int index);
    void setColorWeight(double weight);
    void setScale(double x, double y, double z);
    void setRotate(double x, double y, double z);
    void setOffset(double x, double y, double z);
    void setViewAngle(double angle);
    void setViewFront(double front);
    void setViewFarther(double farther);

protected:
    SFLSelectorLayout *_drawType;
    SFLSelectorLayout *_direction;
    SFLVec1Editor *_colorWeight;
    SFLVec3Editor *_scale;
    SFLVec3Editor *_rotate;
    SFLVec3Editor *_move;
    SFLVec1Editor *_viewAngle;
    SFLVec1Editor *_viewFront;
    SFLVec1Editor *_viewFarther;

    void setupUI() override;
    void initData() override;
};

#endif // SFLVIEWNOLIGHT_H
