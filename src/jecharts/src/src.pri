#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

################################################################
# Resouces
################################################################

include($$PWD/stepchart/stepchart.pri)

jecharts_headers += \
    $$PWD/jchart.h \
    $$PWD/jchartview.h \
    $$PWD/jecharts_global.h \
    $$PWD/jecharts_inc.h \
    $$PWD/jecharts_option.h

HEADERS += \
    $$jecharts_headers

SOURCES += \
    $$PWD/jchart.cpp \
    $$PWD/jchartview.cpp \
    $$PWD/jecharts_global.cpp \
    $$PWD/jecharts_option.cpp

#
framework_headers_echarts.version = Versions
framework_headers_echarts.path = Headers
framework_headers_echarts.files = $$jecharts_headers
