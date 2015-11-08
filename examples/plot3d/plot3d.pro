#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

J3D_ROOT = $$PWD/../..

TEMPLATE = app
TARGET = plot3d
DESTDIR = $${J3D_ROOT}/bin

# - output - tmp -
MOC_DIR = $${J3D_ROOT}/temp/examples/plot3d
OBJECTS_DIR = $${J3D_ROOT}/temp/examples/plot3d
RCC_DIR = $${J3D_ROOT}/temp/examples/plot3d

HEADERS += \

SOURCES += \
    main.cpp

## - import libraries -

win32: unix: {
    CONFIG(debug, debug|release) {
        LIBS += -L$${J3D_ROOT}/lib -lQtPlot3Dd
    } else {
        LIBS += -L$${J3D_ROOT}/lib -lQtPlot3D
    }
    INCLUDEPATH += \
        $${J3D_ROOT}/src/plot3d
} else: macx: {
    QT += network declarative
    LIBS += \
        -framework QtPlot3D -F$${J3D_ROOT}/lib
    INCLUDEPATH += \
        $${J3D_ROOT}/lib/QtPlot3D.framework/Versions/Current/Headers
}
