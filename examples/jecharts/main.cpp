
#include <QApplication>
#include <QDateTime>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#if defined(Q_OS_LINUX)
    glutInit(&argc, argv);
#endif

    qsrand(QDateTime::currentDateTime().toTime_t());

#if 1
    //ShapeTest shapeTest;
#else
    ShapeTest2 shapeTest;
#endif
    //shapeTest.showMaximized();

    return app.exec();
}
