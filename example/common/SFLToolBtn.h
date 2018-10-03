#ifndef SFLTOOLBTN_H
#define SFLTOOLBTN_H

#include <QToolButton>

class SFLModelAbstract;
class SFLToolBtn: public QToolButton
{
    Q_OBJECT

public:
    SFLToolBtn(QWidget *parent = nullptr):QToolButton(parent){}

    void setOwner(SFLModelAbstract *owner){
        _owner = owner;
    }

signals:
    void clicked(SFLModelAbstract *owner);

protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
        QToolButton::mouseReleaseEvent(event);
        emit clicked(_owner);
    }

private:
    SFLModelAbstract *_owner;
};

#endif // SFLTOOLBTN_H
