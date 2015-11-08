#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

J3D_ROOT = $$PWD/../../

TEMPLATE = lib
TARGET = QtPlot3D
DESTDIR = $${J3D_ROOT}/lib

CONFIG      += warn_on qt_framework
#CONFIG      += silent

# - output - tmp -
MOC_DIR = $${J3D_ROOT}/temp/plot3d
OBJECTS_DIR = $${J3D_ROOT}/temp/plot3d
RCC_DIR = $${J3D_ROOT}/temp/plot3d

##

win32: unix: {
    CONFIG(debug, debug|release) {
        LIBS += -lQt3D$${QT_LIBINFIX}d
    } else {
        LIBS += -lQt3D$${QT_LIBINFIX}
    }
    LIBS += -lglut
} else: macx: {
    QT += network declarative
    LIBS += -framework Qt3D \
            -framework Qt3DQuick \
            -framework glut
}

win32 {
    CONFIG(debug, debug|release) {
        TARGET = $$member(TARGET, 0)d
    }
}

win32 {
    CONFIG           += dll
    CONFIG           += debug_and_release
    CONFIG           += build_all
    DEFINES          += QT_NO_DEBUG_OUTPUT
} else {
#    CONFIG           += release
}

include(plot3d.pri)

macx:CONFIG(qt_framework, qt_framework|qt_no_framework) {
    CONFIG += shared lib_bundle
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,$$DESTDIR/
    CONFIG += lib_bundle
    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.path = Headers
    FRAMEWORK_HEADERS.files = $$PUBLIC_HEADERS
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}
