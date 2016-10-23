#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts webview webenginewidgets

THIS_DIR = $$PWD/../../

TEMPLATE = lib
win32 {
    TARGET = $$qtLibraryTarget(jecharts)
} else {
    TARGET = jecharts
}

DESTDIR = $${THIS_DIR}/bin
#DESTDIR = $${THIS_DIR}/lib

CONFIG += dll warn_on lib_bundle
#CONFIG += no_keywords silent
#DEFINES += QT_NO_DEBUG_OUTPUT

# - output - tmp -
macx: {
    J_PLAT_PREFIX = macx
} else: unix {
    J_PLAT_PREFIX = unix
}

JECHARTS_TEMP_PREFIX = $${THIS_DIR}/temp/jecharts/$${J_PLAT_PREFIX}
macx:unix: {
    MOC_DIR = $${JECHARTS_TEMP_PREFIX}
    OBJECTS_DIR = $${JECHARTS_TEMP_PREFIX}
    RCC_DIR = $${JECHARTS_TEMP_PREFIX}
}

##

contains(CONFIG, dll) {
    DEFINES += JECHARTS_DLL JECHARTS_MAKEDLL
}

win32 {
    CONFIG += debug_and_release
    CONFIG += build_all

    CONFIG(debug, debug|release) {
        LIBS +=
    } else {
        LIBS +=
    }
    LIBS +=
} else: macx: {
    DEFINES -= Q_CC_CLANG
    CONFIG += qt_framework
    QT += network
#    LIBS +=
} else: unix {
    CONFIG += dll
    #
}

##################################################
# creating a precompiled header file (only supported
# on some platforms (Windows - all MSVC project types,
# Mac OS X - Xcode, Makefile, Unix - gcc 3.3 and up)
##################################################

CONFIG += precompile_header
PRECOMPILED_HEADER = $$PWD/precomp.h
INCLUDEPATH += $$PWD

##
include($$PWD/src/src.pri)

##
RESOURCES += \
    $$PWD/resources/jecharts.qrc

###############################################################
# import files
###############################################################

###############################################################
# global commands
###############################################################

macx:CONFIG(qt_framework, qt_framework|qt_no_framework) {
    QMAKE_LFLAGS_SONAME = -Wl,-install_name,$$DESTDIR/
    CONFIG += lib_bundle
    QMAKE_BUNDLE_DATA += \
        framework_headers_echarts \
        framework_headers_stepchart
} else:win32|unix: {
    commands += echo --- console - $$TARGET --- &

    excludefile = $$PWD/copy.ignore
    !exists("$$excludefile"):excludefile = "$$THIS_DIR/common/copy.ignore"
    !exists("$$excludefile"):error("$$excludefile" is not exists!)
    win32:excludefile = $$replace(excludefile, /, \\)

    ## copy files
    dstdir = $$THIS_DIR/include/jecharts
    win32:dstdir = $$replace(dstdir, /, \\)
    !exists("$$dstdir"):commands += $(MKDIR) "\"$$dstdir\"" &
    win32:srcdir = $$PWD/src/*.h
    unix:srcdir = $$PWD/src/
    win32:srcdir = $$replace(srcdir, /, \\)
    win32:commands += $(COPY_DIR) "\"$$srcdir\"" "\"$$dstdir\"" /exclude:"$$excludefile" &
    unix:commands += "\"$$THIS_DIR/tools/xcopy.py\"" "\"$$srcdir\"" "\"$$dstdir\"" "*.h" &

    QMAKE_POST_LINK += $$commands
}
