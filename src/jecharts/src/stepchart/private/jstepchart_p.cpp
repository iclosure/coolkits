#include "precomp.h"
#include "jstepchart_p.h"
#include "../../jecharts_option.h"

namespace JEcharts {

JStepChartPrivate::JStepChartPrivate(JStepChart *q)
    : QObject(q)
    , q_ptr(q)
{

}

void JStepChartPrivate::init()
{
    Q_Q(JStepChart);
    connect(q->view(), SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

void JStepChartPrivate::load()
{
    Q_Q(JStepChart);
    qobject_cast<QWebEngineView *>(q->view())
            ->setUrl(QUrl("qrc:/coolkits/jecharts/html/stepchart.html"));
}

void JStepChartPrivate::onLoadFinished(bool loaded)
{
    Q_UNUSED(loaded);
    //Q_Q(JStepChart);
}

} // end of namespace JEcharts
