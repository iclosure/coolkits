#-------------------------------------------------
# Project created by QtCreator 2015-08-01T00:00:11
#-------------------------------------------------

TEMPLATE = subdirs
#CONFIG += ordered

src_plot3d.subdir = $$PWD/plot3d
src_plot3d.target = sub-plot3d

src_jplot3d.subdir = $$PWD/jplot3d
src_jplot3d.target = sub-jplot3d
#src_jplot3d.depends = src_plot3d

SUBDIRS += \
#    src_plot3d \
    src_jplot3d
