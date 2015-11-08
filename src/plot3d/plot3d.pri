#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

################################################################
# creating a precompiled header file (only supported on some platforms (Windows - all MSVC project types,
# Mac OS X - Xcode, Makefile, Unix - gcc 3.3 and up)
################################################################

CONFIG += precompile_header
PRECOMPILED_HEADER = precomp.h
INCLUDEPATH += $$PWD

################################################################
# Resouces
################################################################

SOURCES += \
    plot3d_view.cpp \
    plot3d_scene.cpp \
    plot3d_shape.cpp \
    plot3d_coord.cpp \
    plot3d_indicator.cpp \
    plot3d_global.cpp

HEADERS += \
    plot3d_view.h \
    plot3d_scene.h \
    plot3d_shape.h \
    plot3d_coord.h \
    plot3d_indicator.h \
    plot3d_global.h \
    plot3d_inc.h

RESOURCES += \
    resources/plot3d.qrc

##
PUBLIC_HEADERS += $$HEADERS
