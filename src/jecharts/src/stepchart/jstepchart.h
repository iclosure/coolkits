#ifndef JSTEPCHART_H
#define JSTEPCHART_H

#include "../jchart.h"

namespace JEcharts {

class JStepChartPrivate;

class JECHARTS_EXPORT JStepChart : public JChart
{
public:
    explicit JStepChart(QWidget *parent = 0);
    ~JStepChart();

signals:

public slots:

private:
    Q_DISABLE_COPY(JStepChart)
    J_DECLARE_PRIVATE(JStepChart)
};

} // end of namespace JEcharts

#endif // JSTEPCHART_H
