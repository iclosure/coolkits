#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

J3D_ROOT = $$PWD/../..

TEMPLATE = app
TARGET = jplot3d
DESTDIR = $${J3D_ROOT}/bin

# - output - tmp -
!win32 {
}
# - output - tmp -
macx: {
    J_PLAT_PREFIX = macx
} else: unix {
    J_PLAT_PREFIX = unix
}

J3D_TEMP_PREFIX = $${J3D_ROOT}/temp/examples/jplot3d/$${J_PLAT_PREFIX}
macx:unix: {
    MOC_DIR = $${J3D_TEMP_PREFIX}
    OBJECTS_DIR = $${J3D_TEMP_PREFIX}
    RCC_DIR = $${J3D_TEMP_PREFIX}
}

## - import libraries -

win32: {
    DEFINES += J3D_DLL
    CONFIG(debug, debug|release) {
        LIBS += -L$${J3D_ROOT}/bin -lJPlot3Dd
    } else {
        LIBS += -L$${J3D_ROOT}/bin -lJPlot3D
    }
    INCLUDEPATH += \
        $${J3D_ROOT}/src/jplot3d
} else: mac: {
    QT += network
    LIBS += \
        -framework JPlot3D -F$${J3D_ROOT}/bin \
        -framework glut

    INCLUDEPATH += \
        $${J3D_ROOT}/bin/JPlot3D.framework/Versions/Current/Headers

} else: unix {
    LIBS += \
            -L$${J3D_ROOT}/bin -lJPlot3D \
            -lGLU -lglut

    INCLUDEPATH += \
        $${J3D_ROOT}/src/jplot3d

}

HEADERS += \
    shapetest.h

SOURCES += \
    main.cpp \
    shapetest.cpp
