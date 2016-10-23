#include "chartview.h"
#include "jecharts_inc.h"
#include <QtWidgets>

ChartView::ChartView(QWidget *parent)
    : QDialog(parent, Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
    QVBoxLayout *vertLayoutMain = new QVBoxLayout(this);
    vertLayoutMain->setContentsMargins(2, 2, 2, 2);

    q_chartView = new JEcharts::JChartView(this);
    q_chartView->setColumnCount(2);
    vertLayoutMain->addWidget(q_chartView);

    //
    for (int i = 0; i < 1; ++i) {
        q_chartView->appendChart(new JEcharts::JStepChart(this), false);
    }
    q_chartView->updateLayout();
}
