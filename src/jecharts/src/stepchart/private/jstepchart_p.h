#ifndef JSTEPCHARTPRIVATE_H
#define JSTEPCHARTPRIVATE_H

#include <QObject>
#include "../jstepchart.h"

namespace JEcharts {

class JEcharts;

class JStepChartPrivate : public QObject
{
    Q_OBJECT
public:
    explicit JStepChartPrivate(JStepChart *q);

    void init();
    void load();

signals:

public slots:
    void onLoadFinished(bool loaded);

private:
    J_DECLARE_PUBLIC(JStepChart)
};

} // end of namespace JEcharts

#endif // JSTEPCHARTPRIVATE_H
