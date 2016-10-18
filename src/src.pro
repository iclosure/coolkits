#-------------------------------------------------
# Project created by QtCreator 2015-08-01T00:00:11
#-------------------------------------------------

TEMPLATE = subdirs
#CONFIG += ordered

src_jplot3d.subdir = $$PWD/jplot3d
src_jplot3d.target = sub-jplot3d

src_jecharts.subdir = $$PWD/jecharts
src_jecharts.target = sub-jecharts

SUBDIRS += \
#    src_jplot3d \
    src_jecharts
