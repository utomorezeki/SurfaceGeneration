#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T17:52:06
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurveModel
TEMPLATE = app

INCLUDEPATH +=  /usr/include/
LIBS        += -L/usr/include/
LIBS        += -lCGAL
LIBS        += -lgmp
QMAKE_CXXFLAGS += -frounding-math -O3

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        curvegenerator.cpp \
    qcustomplot.cpp \
    mathematics.cpp \
    mesh.cpp \
    generate3d.cpp \
    polyhedron.cpp \
    nncrust.cpp \
    crust.cpp

HEADERS += \
        curvegenerator.h \
    qcustomplot.h \
    mathematics.h \
    mesh.h \
    generate3d.h \
    polyhedron.h \
    nncrust.h \
    crust.h

FORMS += \
        curvegenerator.ui
