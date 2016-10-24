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
    QString option;
    QString title;
    QVector<QColor> color;
    QColor backgroundColor;
    bool animation;
    int animationDuration;
};

void JEchartsOptionPrivate::init()
{
    Q_Q(JEchartsOption);

    //
    chart = qobject_cast<JChart *>(q->parent());
    view = qobject_cast<QWebEngineView *>(chart->view());
    channel = qobject_cast<QWebChannel *>(chart->channel());
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

void JEchartsOption::setOption(const QString &content)
{
    Q_D(JEchartsOption);
    d->view->page()->runJavaScript(QString("setOption(%1)").arg(content),
                                   [](const QVariant &value){
        qDebug() << value;
    });
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

QColor JEchartsOption::backgroundColor() const
{
    Q_D(const JEchartsOption);
    return d->backgroundColor;
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

QString JEchartsOption::option() const
{
    Q_D(const JEchartsOption);
    return d->option;
}

void JEchartsOption::addData(int index, const QVariant &value)
{
    Q_D(JEchartsOption);
    d->view->page()->runJavaScript(QString("addData(%1, %2)").arg(index).arg(value.toString()),
                                   [](const QVariant &value){
        qDebug() << value;
    });
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

void JEchartsOption::setBackgroundColor(const QColor &value)
{
    Q_D(JEchartsOption);
    if (value != d->backgroundColor) {
        d->backgroundColor = value;
        emit backgroundColorChanged(value);
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
