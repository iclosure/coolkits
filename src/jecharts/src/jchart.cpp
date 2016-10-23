#include "precomp.h"
#include "jchart.h"

namespace JEcharts {

// class JChartPrivate

class JChartPrivate
{
public:
    JChartPrivate(JChart *parent)
        : q_ptr(parent)
    {

    }

    void init();

private:
    J_DECLARE_PUBLIC(JChart)
};

void JChartPrivate::init()
{

}

// class JChart

JChart::JChart(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new JChartPrivate(this))
{
    Q_D(JChart);
    d->init();
}

JChart::~JChart()
{
    Q_D(JChart);
    delete d;
}

} // end of namespace JEcharts
