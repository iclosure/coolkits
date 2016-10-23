#ifndef JSTEPCHARTPRIVATE_H
#define JSTEPCHARTPRIVATE_H

#include <QObject>
#include "../jstepchart_option.h"

class QWebEngineView;
class QWebChannel;

namespace JEcharts {

class JStepChart;

class JStepChartPrivate : public QObject
{
    Q_OBJECT
public:
    explicit JStepChartPrivate(JStepChart *q);

    void init();
    void load();

signals:

public slots:

private:
    J_DECLARE_PUBLIC(JStepChart)
    QWebEngineView *view;
    QWebChannel *channel;
    JStepChartOption *option;
};

} // end of namespace JEcharts

#endif // JSTEPCHARTPRIVATE_H
