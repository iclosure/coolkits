#ifndef JCHART_H
#define JCHART_H

#include <QWidget>
#include "jecharts_global.h"

class QWebEngineView;
class QWebChannel;

namespace JEcharts {

class JChartPrivate;
class JEchartsOption;

/**
 * @brief The JChart class
 */
class JECHARTS_EXPORT JChart : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief JEchart
     * @param parent
     */
    explicit JChart(QWidget *parent = 0);
    virtual ~JChart();

    /**
     * @brief view
     * @return
     */
    QObject *view() const;

    /**
     * @brief channel
     * @return
     */
    QObject *channel() const;

    /**
     * @brief option
     * @return
     */
    QObject *option() const;

signals:

public slots:

private:
    Q_DISABLE_COPY(JChart)
    J_DECLARE_PRIVATE(JChart)
};

} // end of namespace JEcharts

#endif // JCHART_H
