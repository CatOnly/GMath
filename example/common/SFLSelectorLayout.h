#ifndef SFLSELECTORLAYOUT_H
#define SFLSELECTORLAYOUT_H
#include <QHBoxLayout>

class QLabel;
class QComboBox;
class SFLSelectorLayout:public QHBoxLayout
{
    Q_OBJECT

public:
    explicit SFLSelectorLayout(const QString title, QWidget *parent = nullptr);
    ~SFLSelectorLayout();

    void setSelections(QStringList list);
    void hide();
    void show();

signals:
    void selectChanged(int index);

public slots:
    void onSelectChanged(int index);

private:
    QLabel *_titleLabel;
    QComboBox *_comboBox;

    void setupUI();
};

#endif // SFLSELECTORLAYOUT_H
