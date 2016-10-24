#include "chartview.h"
#include "jecharts_inc.h"
#include <QtWidgets>

ChartView::ChartView(QWidget *parent)
    : QDialog(parent, Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
    QVBoxLayout *vertLayoutMain = new QVBoxLayout(this);
    vertLayoutMain->setContentsMargins(2, 2, 2, 2);

    d_chartView = new JEcharts::JChartView(this);
    d_chartView->setColumnCount(2);
    vertLayoutMain->addWidget(d_chartView);

    QPushButton *button1 = new QPushButton("test", this);
    vertLayoutMain->addWidget(button1);

    //
    for (int i = 0; i < 1; ++i) {
        d_charts.append(new JEcharts::JStepChart(this));
        d_chartView->appendChart(d_charts.last(), false);
    }
    d_chartView->updateLayout();

    d_charts.first()->option()->setTitle("what??");

    connect(button1, &QPushButton::clicked, [&](){
        d_charts.first()->option()->setTitle("whats the problem?");
    });
}
