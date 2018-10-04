#include "SFLViewControl.h"
#include "../common/SFLModelAbstract.h"
#include "../common/SFLSelectorLayout.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

SFLViewControl::SFLViewControl(QWidget *parent):QDockWidget(parent)
{
    _titleLabel = new QLabel("标题");
    _kindsLayout = new SFLSelectorLayout("类型", this);
    _containerLayout = new QVBoxLayout();
    _currentWidget = nullptr;
    _cameraResetBtn = new QPushButton("还 原",this);

    setupUI();
}
SFLViewControl::~SFLViewControl()
{
    disconnect(_kindsLayout, &SFLSelectorLayout::selectChanged, this, &SFLViewControl::changeKinds);
    disconnect(_cameraResetBtn, &QPushButton::clicked, this, &SFLViewControl::resetCameraBtnClicked);
}

void SFLViewControl::setupUI()
{
    setFixedWidth(300);
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    QLabel *title = new QLabel("E-mail: l.tat@qq.com");
    title->setTextFormat(Qt::PlainText);
    title->setAlignment(Qt::AlignRight);
    title->setTextInteractionFlags(Qt::TextSelectableByMouse);
    title->setContentsMargins(20, 5, 20, 0);
    setTitleBarWidget(title);

    _titleLabel->setTextFormat(Qt::PlainText);
    _titleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
    _titleLabel->setContentsMargins(10, 0, 20, 0);

    _containerLayout->addWidget(_titleLabel);
    _containerLayout->addLayout(_kindsLayout);
    _containerLayout->addWidget(_currentWidget);
    _containerLayout->addStretch();
    _containerLayout->addWidget(_cameraResetBtn);

    QWidget *container = new QWidget(this);
    container->setLayout(_containerLayout);
    QDockWidget::setWidget(container);

    connect(_kindsLayout, &SFLSelectorLayout::selectChanged, this, &SFLViewControl::changeKinds);
    connect(_cameraResetBtn, &QPushButton::clicked, this, &SFLViewControl::resetCameraBtnClicked);
}

void SFLViewControl::setDelegate(SFLModelAbstract *delegate)
{
    if (delegate != nullptr && _delegate != delegate){
        _delegate = delegate;
        _titleLabel->setText(delegate->toolBtn()->text());
        _kindsLayout->setSelections(delegate->view()->types());
        setCurrentWidget(delegate->view());
    }
}

void SFLViewControl::setCurrentWidget(SFLViewAbstract *widget)
{
    SFLViewAbstract *lastWidget = _currentWidget;
    _currentWidget = widget;
    if (lastWidget != nullptr){
        _containerLayout->removeWidget(lastWidget);
        lastWidget->setParent(nullptr);
    }
    _containerLayout->insertWidget(2, _currentWidget);
}

void SFLViewControl::changeKinds(int index)
{
    if (index > -1){
        _delegate->view()->changeViewBy(index);
    }
}

void SFLViewControl::resetCameraBtnClicked()
{
    _delegate->view()->initDataCamera();
    emit resetCamera();
}
