#include "precomp.h"
#include "jstepchart.h"
#include "private/jstepchart_p.h"

namespace JEcharts {

// class JStepChart

JStepChart::JStepChart(QWidget *parent)
    : JChart(parent)
    , d_ptr(new JStepChartPrivate(this))
{
    Q_D(JStepChart);
    d->init();

    //
    d->load();
}

JStepChart::~JStepChart()
{
    Q_D(JStepChart);
    delete d;
}

} // end of namespace JEcharts
