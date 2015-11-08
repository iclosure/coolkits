#ifndef PRECOMP_H
#define PRECOMP_H

#include <QtCore>
#include <QtGui>

#if (QT_VERSION < 0x050000)
#include <QWidget>
#else
#include <QtWidgets>
#include <QtOpenGL>
#endif

#if defined(Q_WS_MAC) || defined(Q_OS_MACX)
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#if (QT_VERSION < 0x050000) && (defined(Q_OS_WIN) || defined(Q_WS_WIN))
#include <Windows.h>
#endif

// -
//#pragma execution_character_set("utf-8")

#endif // PRECOMP_H
