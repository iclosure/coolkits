#ifndef PRECOMP_H
#define PRECOMP_H

#ifdef QT_CORE_LIB
#include <QtCore>
#endif

#ifdef QT_GUI_LIB
#include <QtGui>
#endif

#if (QT_VERSION < 0x050000)

#ifdef QT_GUI_LIB
#include <QWidget>
#endif

#else

#ifdef QT_WIDGETS_LIB
#include <QtWidgets>
#endif

#ifdef QT_CHARTS_LIB
#include <QtCharts>
#endif

#ifdef QT_WEBVIEW_LIB
#include <QtWebView>
#endif

#ifdef QT_WEBENGINE_LIB
#include <QtWebEngine>
#endif

#ifdef QT_WEBENGINEWIDGETS_LIB
#include <QtWebEngineWidgets>
#endif

#ifdef QT_OPENGL_LIB
#include <QtOpenGL>

#if defined(Q_WS_MAC) || defined(Q_OS_MACX)
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#endif

#endif

#if (QT_VERSION < 0x050000) && (defined(Q_OS_WIN) || defined(Q_WS_WIN))
#include <Windows.h>
#endif

// -
//#pragma execution_character_set("utf-8")

#endif // PRECOMP_H
