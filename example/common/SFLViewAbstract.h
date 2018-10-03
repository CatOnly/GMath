#ifndef SFLVIEWABSTRACT_H
#define SFLVIEWABSTRACT_H

#include <QWidget>
#include <QVBoxLayout>

class SFLModelAbstract;
class SFLViewAbstract:public QWidget
{
    Q_OBJECT

public:
    explicit SFLViewAbstract(SFLModelAbstract *owner, QWidget *parent = nullptr):QWidget(parent) {
        _owner = owner;
        QVBoxLayout *layoutMain = new QVBoxLayout(this);
        setLayout(layoutMain);
    }

    virtual void initDataCamera(){}
    virtual void changeViewBy(int index) = 0;

    QStringList types(){
        return _types;
    }

signals:
    void needRender();

protected:
    QStringList _types;
    SFLModelAbstract *_owner;

    virtual void initData() = 0;
    virtual void setupUI() = 0;
};
#endif // SFLVIEWABSTRACT_H
