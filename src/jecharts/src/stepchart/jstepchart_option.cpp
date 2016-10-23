#include "precomp.h"
#include "jstepchart_option.h"

namespace JEcharts {

// class JStepChartOptionPrivate

class JStepChartOptionPrivate
{
public:
    JStepChartOptionPrivate(JStepChartOption *q)
        : q_ptr(q)
    {

    }

    void init();

private:
    J_DECLARE_PUBLIC(JStepChartOption)
};

void JStepChartOptionPrivate::init()
{
    //
}

// class JStepChartOption

JStepChartOption::JStepChartOption(QObject *parent)
    : QObject(parent)
    , d_ptr(new JStepChartOptionPrivate(this))
{
    Q_D(JStepChartOption);
    d->init();
}

JStepChartOption::~JStepChartOption()
{
    Q_D(JStepChartOption);
    delete d;
}

} // end of namespace JEcharts
