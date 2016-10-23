#include "precomp.h"
#include "jchartview.h"
#include "jchart.h"

namespace JEcharts {

// class JChartViewPrivate

class JChartViewPrivate
{
public:
    JChartViewPrivate(JChartView *parent)
        : q_ptr(parent)
    {

    }

    void init();
    void updateLayout();

private:
    J_DECLARE_PUBLIC(JChartView)
    QList<JChart *> charts;
    QSpinBox *spinBoxColumnCount;
    QScrollArea *scrollArea;
    QWidget *widgetCharts;
    QGridLayout *gridLayoutChart;
};

void JChartViewPrivate::init()
{
    Q_Q(JChartView);

    QVBoxLayout *vertLayoutMain = new QVBoxLayout(q);
    vertLayoutMain->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *horiLayoutTop = new QHBoxLayout();
    horiLayoutTop->setContentsMargins(0, 0, 0, 0);
    vertLayoutMain->addLayout(horiLayoutTop);

    QFormLayout *formLayoutColumnCount = new QFormLayout();
    horiLayoutTop->addLayout(formLayoutColumnCount);
    horiLayoutTop->addStretch();

    spinBoxColumnCount = new QSpinBox(q);
    spinBoxColumnCount->setMinimumWidth(120);
    spinBoxColumnCount->setRange(1, 20);
    formLayoutColumnCount->addRow(QStringLiteral("列数："), spinBoxColumnCount);

    scrollArea = new QScrollArea(q);
    //scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    vertLayoutMain->addWidget(scrollArea);

    widgetCharts = new QWidget(q);
    scrollArea->setWidget(widgetCharts);

    gridLayoutChart = new QGridLayout(widgetCharts);
    gridLayoutChart->setContentsMargins(2, 2, 2, 2);
    gridLayoutChart->setSpacing(5);

    //
    QObject::connect(spinBoxColumnCount, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     [q, this](int value){
        //
        updateLayout();
        //
        emit q->columnCountChanged(value);
    });
}

void JChartViewPrivate::updateLayout()
{
    //
    QListIterator<JChart *> citer(charts);
    while (citer.hasNext()) {
        gridLayoutChart->removeWidget(citer.next());
    }
    //
    citer.toFront();
    int rowIndex = 0, columnIndex = 0;
    int columnCount = spinBoxColumnCount->value();
    while (citer.hasNext()) {
        gridLayoutChart->addWidget(citer.next(), rowIndex, columnIndex++, 1, 1);
        if (columnIndex == columnCount) {
            ++rowIndex;
            columnIndex = 0;
        }
    }
}

// class JChartView

JChartView::JChartView(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new JChartViewPrivate(this))
{
    Q_D(JChartView);
    d->init();
}

JChartView::~JChartView()
{
    Q_D(JChartView);
    delete d;
}

void JChartView::appendChart(JChart *chart, bool update)
{
    //
    if (!chart) {
        return;     //
    }
    //
    Q_D(JChartView);
    if (d->charts.contains(chart)) {
        return;     //
    }
    //
    d->charts.append(chart);
    //
    if (update) {
        d->updateLayout();
    }
}

void JChartView::insertChart(int index, JChart *chart, bool update)
{
    //
    if (!chart) {
        return;     //
    }
    //
    Q_D(JChartView);
    if (d->charts.contains(chart)) {
        return;     //
    }
    //
    d->charts.insert(index, chart);
    //
    if (update) {
        d->updateLayout();
    }
}

JChart *JChartView::takeChart(int index, bool update)
{
    Q_D(JChartView);
    //
    if (index < 0 || index >= d->charts.count()) {
        return 0;
    }
    //
    JChart *chart = d->charts.takeAt(index);
    //
    if (update) {
        d->updateLayout();
    }

    return chart;
}

void JChartView::removeChart(JChart *chart, bool update)
{
    //
    if (!chart) {
        return;     //
    }
    //
    Q_D(JChartView);
    if (!d->charts.contains(chart)) {
        return;     //
    }
    //
    d->charts.removeAll(chart);
    //
    chart->deleteLater();
    //
    if (update) {
        d->updateLayout();
    }
}

void JChartView::clearChart(bool destroy)
{
    Q_D(JChartView);
    if (destroy) {
        QListIterator<JChart *> citer(d->charts);
        while (citer.hasNext()) {
            citer.next()->deleteLater();
        }
    }
    d->charts.clear();
    //
    d->updateLayout();
}

JChart *JChartView::chartAt(int index) const
{
    Q_D(const JChartView);
    if (index < 0 || index >= d->charts.count()) {
        return 0;
    }
    return d->charts.at(index);
}

int JChartView::indexOfChart(JChart *chart) const
{
    if (!chart) {
        return -1;
    }
    Q_D(const JChartView);
    return d->charts.indexOf(chart);
}

QList<JChart *> JChartView::charts() const
{
    Q_D(const JChartView);
    return d->charts;
}

int JChartView::columnCount() const
{
    Q_D(const JChartView);
    return d->spinBoxColumnCount->value();
}

void JChartView::setColumnCount(int value)
{
    Q_D(JChartView);
    d->spinBoxColumnCount->setValue(value);
}

void JChartView::updateLayout()
{
    Q_D(JChartView);
    d->updateLayout();
}

} // end of namespace JEcharts
