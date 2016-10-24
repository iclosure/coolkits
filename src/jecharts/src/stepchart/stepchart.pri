#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T00:00:11
#
#-------------------------------------------------

################################################################
# Resouces
################################################################

stepchart_headers += \
    $$PWD/jstepchart.h

HEADERS += \
    $$stepchart_headers \
    $$PWD/private/jstepchart_p.h

SOURCES += \
    $$PWD/jstepchart.cpp \
    $$PWD/private/jstepchart_p.cpp

#
framework_headers_stepchart.version = Versions
framework_headers_stepchart.path = Headers/stepchart
framework_headers_stepchart.files = $$stepchart_headers
