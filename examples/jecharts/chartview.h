#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QDialog>

namespace JEcharts {
    class JChartView;
}

class ChartView : public QDialog
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);

signals:

public slots:

private:
    JEcharts::JChartView *q_chartView;
};

#endif // CHARTVIEW_H
