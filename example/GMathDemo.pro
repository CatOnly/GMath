#-------------------------------------------------
#
# Project created by QtCreator 2018-10-03T10:01:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GMathDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../src

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    common/SFLModelAbstract.cpp \
    common/SFLSelectorLayout.cpp \
    common/SFLVec1Editor.cpp \
    common/SFLVec3Editor.cpp \
    views/SFLViewControl.cpp \
    views/SFLViewRender.cpp \
    views/SFLViewNoLight.cpp

HEADERS += \
        MainWindow.h \
    common/SFLDefine.h \
    common/SFLModelAbstract.h \
    common/SFLSelectorLayout.h \
    common/SFLToolBtn.h \
    common/SFLVec1Editor.h \
    common/SFLVec3Editor.h \
    common/SFLViewAbstract.h \
    views/SFLViewControl.h \
    views/SFLViewRender.h \
    views/SFLViewNoLight.h \
    SFLCameraVirtual.h \
    SFLModelNoLight.h \
    ../src/header/debug.hpp \
    ../src/header/geometric.hpp \
    ../src/header/mat.hpp \
    ../src/header/mat3x3.hpp \
    ../src/header/mat4x4.hpp \
    ../src/header/transform.hpp \
    ../src/header/vec2.hpp \
    ../src/header/vec3.hpp \
    ../src/header/vec4.hpp \
    ../src/GMath.hpp
