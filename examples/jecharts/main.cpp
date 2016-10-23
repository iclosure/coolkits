
#include <QApplication>
#include <QDateTime>
#include "chartview.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

#if defined(Q_OS_LINUX)
    glutInit(&argc, argv);
#endif

    qsrand(QDateTime::currentDateTime().toTime_t());

    ChartView chartView;
    chartView.resize(1024, 650);
    chartView.show();

    return app.exec();
}
