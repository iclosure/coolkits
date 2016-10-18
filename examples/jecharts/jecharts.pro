#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

THIS_DIR = $$PWD/../..

TEMPLATE = app
TARGET = jecharts
DESTDIR = $${THIS_DIR}/bin

# - output - tmp -
!win32 {
}
# - output - tmp -
macx: {
    J_PLAT_PREFIX = macx
} else: unix {
    J_PLAT_PREFIX = unix
}

JECHARTS_TEMP_PREFIX = $${THIS_DIR}/temp/examples/jecharts/$${J_PLAT_PREFIX}
macx:unix: {
    MOC_DIR = $${JECHARTS_TEMP_PREFIX}
    OBJECTS_DIR = $${JECHARTS_TEMP_PREFIX}
    RCC_DIR = $${JECHARTS_TEMP_PREFIX}
}

## - import libraries -

win32: {
    DEFINES += JECHARTS_DLL
    CONFIG(debug, debug|release) {
        LIBS += -L$${THIS_DIR}/bin -ljechartsd
    } else {
        LIBS += -L$${THIS_DIR}/bin -ljecharts
    }
    INCLUDEPATH += \
        $${THIS_DIR}/src/jecharts
} else: mac: {
    QT += network
    LIBS += \
        -framework jecharts -F$${THIS_DIR}/bin

    INCLUDEPATH += \
        $${THIS_DIR}/bin/jecharts.framework/Versions/Current/Headers

} else: unix {
    LIBS += \
            -L$${THIS_DIR}/bin -ljecharts

    INCLUDEPATH += \
        $${THIS_DIR}/src/jecharts

}

HEADERS +=

SOURCES += \
    main.cpp
