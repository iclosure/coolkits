#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QDialog>

namespace JEcharts {
    class JChartView;
    class JStepChart;
}

class ChartView : public QDialog
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);

signals:

public slots:
    void onLoadFinished(bool loaded);

protected:
    void timerEvent(QTimerEvent *e);

private:
    JEcharts::JChartView *d_chartView;
    QList<JEcharts::JStepChart *> d_charts;
    int d_timerId;
};

#endif // CHARTVIEW_H
