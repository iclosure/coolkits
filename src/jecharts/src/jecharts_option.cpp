#include "precomp.h"
#include "jecharts_option.h"
#include "jchart.h"

namespace JEcharts {

// class JEchartsOptionPrivate

class JEchartsOptionPrivate
{
public:
    JEchartsOptionPrivate(JEchartsOption *q)
        : q_ptr(q)
        , animation(true)
        , animationDuration(300)
    {

    }

    void init();

private:
    J_DECLARE_PUBLIC(JEchartsOption)
    JChart *chart;
    QWebEngineView *view;
    QWebChannel *channel;
    // option
    QString title;
    QVector<QColor> color;
    bool animation;
    int animationDuration;
};

void JEchartsOptionPrivate::init()
{
    Q_Q(JEchartsOption);

    //
    chart = qobject_cast<JChart *>(q->parent());
    view = chart->view();
    channel = chart->channel();

    //
    QObject::connect(chart->view(), SIGNAL(titleChanged(QString)),
                     q, SIGNAL(titleChanged(QString)));
}

// class JEchartsOption

JEchartsOption::JEchartsOption(QObject *parent)
    : QObject(parent)
    , d_ptr(new JEchartsOptionPrivate(this))
{
    Q_D(JEchartsOption);
    d->init();
}

JEchartsOption::~JEchartsOption()
{
    Q_D(JEchartsOption);
    delete d;
}

QString JEchartsOption::title() const
{
    Q_D(const JEchartsOption);
    return d->title;
}

QVector<QColor> JEchartsOption::color() const
{
    Q_D(const JEchartsOption);
    return d->color;
}

bool JEchartsOption::animation() const
{
    Q_D(const JEchartsOption);
    return d->animation;
}

int JEchartsOption::animationDuration() const
{
    Q_D(const JEchartsOption);
    return d->animationDuration;
}

void JEchartsOption::setTitle(const QString &value)
{
    Q_D(JEchartsOption);
    if (value != d->title) {
        d->title = value;
        emit titleChanged(value);
    }
}

void JEchartsOption::setColor(const QVector<QColor> &value)
{
    Q_D(JEchartsOption);
    if (value != d->color) {
        d->color = value;
        emit colorChanged(value);
    }
}

void JEchartsOption::setAnimation(bool value)
{
    Q_D(JEchartsOption);
    if (value != d->animation) {
        d->animation = value;
        emit animationChanged(value);
    }
}

void JEchartsOption::setAnimationDuration(int value)
{
    Q_D(JEchartsOption);
    if (value != d->animationDuration) {
        d->animationDuration = value;
        emit animationDurationChanged(value);
    }
}

} // end of namespace JEcharts
