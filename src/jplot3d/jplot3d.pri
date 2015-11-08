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

HEADERS += \
    3rdparty/glextensions.h \
    jglanimation.h \
    jgltrackball.h \
    jglitem.h \
    jglmatrix.h \
    jglfont.h \
    jglfunction.h \
    jglobject.h \
    jglpainter.h \
    jglpicking.h \
    jglindicator.h \
    jglscale.h \
    jglscene.h \
    jglwidget.h \
    jglview.h \
    jplot3d_view.h \
    jplot3d_scene.h \
    jplot3d_glwidget.h \
    jplot3d_shape.h \
    jplot3d_shapeitem.h \
    jplot3d_control.h \
    jplot3d_coord.h \
    jplot3d_floor.h \
    jplot3d_shadow.h \
    jplot3d_global.h \
    jplot3d_inc.h

SOURCES += \
    3rdparty/glextensions.cpp \
    jglanimation.cpp \
    jgltrackball.cpp \
    jglitem.cpp \
    jglmatrix.cpp \
    jglfont.cpp \
    jglfunction.cpp \
    jglobject.cpp \
    jglpainter.cpp \
    jglpicking.cpp \
    jglindicator.cpp \
    jglscale.cpp \
    jglscene.cpp \
    jglwidget.cpp \
    jglview.cpp \
    jplot3d_view.cpp \
    jplot3d_scene.cpp \
    jplot3d_glwidget.cpp \
    jplot3d_shape.cpp \
    jplot3d_shapeitem.cpp \
    jplot3d_control.cpp \
    jplot3d_coord.cpp \
    jplot3d_floor.cpp \
    jplot3d_shadow.cpp \
    jplot3d_global.cpp

RESOURCES += \
    resources/plot3d.qrc

##

PUBLIC_HEADERS += $$HEADERS
