
#include <QApplication>
#include <QDateTime>
#include "shapetest.h"

#if defined(Q_WS_MAC) || defined(Q_OS_MACX)
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#if defined(Q_OS_LINUX)
    glutInit(&argc, argv);
#endif

    qsrand(QDateTime::currentDateTime().toTime_t());

#if 1
    ShapeTest shapeTest;
#else
    ShapeTest2 shapeTest;
#endif
    shapeTest.showMaximized();

    return app.exec();
}
