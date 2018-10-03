#ifndef SFLVEC1EDITOR_H
#define SFLVEC1EDITOR_H

#include <QHBoxLayout>

class QLabel;
class QDoubleSpinBox;
class SFLVec1Editor: public QHBoxLayout
{
    Q_OBJECT

public:
    enum SFLVec1Type{
        typeColor,
        typePosition
    };

    explicit SFLVec1Editor(const QString title, SFLVec1Type type = typeColor, QWidget *parent = nullptr);
    ~SFLVec1Editor();

    void setValue(double x);
    void setSuffix(QString sufffix);
    void hide();
    void show();

signals:
    void changeValue(double value);

public slots:
    void onValueChanged(double value);

private:
    SFLVec1Type _type;
    QLabel *_titleLabel;
    QDoubleSpinBox* _doubleSpineBox;

    void setupUI();
};

#endif // SFLVEC3EDITOR_H
