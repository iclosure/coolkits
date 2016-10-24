#include "precomp.h"
#include "jchart.h"
#include "jecharts_option.h"

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
    QWebEngineView *view;
    QWebChannel *channel;
    JEchartsOption *option;
};

void JChartPrivate::init()
{
    Q_Q(JChart);

    QHBoxLayout *horiLayoutMain = new QHBoxLayout(q);
    horiLayoutMain->setContentsMargins(0, 0, 0, 0);

    view = new QWebEngineView(q);
    horiLayoutMain->addWidget(view);

    channel = new QWebChannel(q);
    view->page()->setWebChannel(channel);

    option = new JEchartsOption(q);
    channel->registerObject(QStringLiteral("option"), option);
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

QObject *JChart::view() const
{
    Q_D(const JChart);
    return d->view;
}

QObject *JChart::channel() const
{
    Q_D(const JChart);
    return d->channel;
}

QObject *JChart::option() const
{
    Q_D(const JChart);
    return d->option;
}

} // end of namespace JEcharts
