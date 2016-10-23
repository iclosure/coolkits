#include "precomp.h"
#include "jstepchart_p.h"
#include "../jstepchart.h"
#include <QWebEngineView>
#include <QWebChannel>

namespace JEcharts {

JStepChartPrivate::JStepChartPrivate(JStepChart *q)
    : QObject(q)
    , q_ptr(q)
    , view(0)
    , channel(0)
{

}

void JStepChartPrivate::init()
{
    Q_Q(JStepChart);

    QHBoxLayout *horiLayoutMain = new QHBoxLayout(q);
    horiLayoutMain->setContentsMargins(0, 0, 0, 0);

    view = new QWebEngineView(q);
    horiLayoutMain->addWidget(view);

    channel = new QWebChannel(q);
    view->page()->setWebChannel(channel);
}

void JStepChartPrivate::load()
{
    view->load(QUrl("qrc:/coolkits/jecharts/html/stepchart.html"));
}

} // end of namespace JEcharts
