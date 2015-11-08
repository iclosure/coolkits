#ifndef PRECOMP_H
#define PRECOMP_H

#include <QtCore>
#include <QtGui>

#if (QT_VERSION < 0x050000)
#include <QWidget>
#else
#include <QtWidgets>
#endif

#ifdef Q_WS_MAC
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


#endif // PRECOMP_H

