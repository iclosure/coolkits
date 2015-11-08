#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

J3D_ROOT = $$PWD/../../

TEMPLATE = lib
win32 {
    TARGET = $$qtLibraryTarget(JPlot3D)
} else {
    TARGET = JPlot3D
}

DESTDIR = $${J3D_ROOT}/bin

CONFIG += dll warn_on lib_bundle
#CONFIG += no_keywords silent
#DEFINES += QT_NO_DEBUG_OUTPUT

# - output - tmp -
macx: {
    J_PLAT_PREFIX = macx
} else: unix {
    J_PLAT_PREFIX = unix
}

J3D_TEMP_PREFIX = $${J3D_ROOT}/temp/jplot3d/$${J_PLAT_PREFIX}
macx:unix: {
    MOC_DIR = $${J3D_TEMP_PREFIX}
    OBJECTS_DIR = $${J3D_TEMP_PREFIX}
    RCC_DIR = $${J3D_TEMP_PREFIX}
}

##

contains(CONFIG, dll) {
    DEFINES += J3D_DLL J3D_MAKEDLL
}

win32 {
    CONFIG += debug_and_release
    CONFIG += build_all

    CONFIG(debug, debug|release) {
        LIBS += \
#                -lQt3D$${QT_LIBINFIX}d \
#                -lQt3DQuick$${QT_LIBINFIX}d

    } else {
        LIBS += \
#                -lQt3D$${QT_LIBINFIX} \
#                -lQt3DQuick$${QT_LIBINFIX}

    }
    LIBS += -lglu32 -lglut32 -lGDI32
} else: macx: {
    DEFINES -= Q_CC_CLANG
    CONFIG += qt_framework
    QT += network declarative
#    LIBS += -framework Qt3D \
#            -framework Qt3DQuick \
#            -framework glut
    LIBS += -framework glut
} else: unix {
    CONFIG += dll
    LIBS += \
#            -lQt4D$${QT_LIBINFIX} \
#            -lQt3DQuick$${QT_LIBINFIX} \
            -lGLU -lglut
}

include(jplot3d.pri)

macx:CONFIG(qt_framework, qt_framework|qt_no_framework) {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,$$DESTDIR/
    CONFIG += lib_bundle
    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.path = Headers
    FRAMEWORK_HEADERS.files = $$PUBLIC_HEADERS
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}
