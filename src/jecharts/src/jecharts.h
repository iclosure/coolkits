#ifndef JCHART_H
#define JCHART_H

#include <QWidget>
#include "jecharts_global.h"

namespace JEcharts {

class JChartPrivate;

/**
 * @brief The JChart class
 */
class JECHARTS_EXPORT JChart : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief JChart
     * @param parent
     */
    explicit JChart(QWidget *parent = 0);
    virtual ~JChart();

signals:

public slots:

private:
    Q_DISABLE_COPY(JChart)
    J_DECLARE_PRIVATE(JChart)
};

} // end of namespace JEcharts

#endif // JCHART_H
