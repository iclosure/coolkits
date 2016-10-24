#ifndef JCHARTVIEW_H
#define JCHARTVIEW_H

#include "jecharts_global.h"
#include <QWidget>

namespace JEcharts {

class JChart;
class JChartViewPrivate;

/**
 * @brief The JChartView class
 */
class JECHARTS_EXPORT JChartView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged)
public:
    /**
     * @brief JChartView
     * @param parent
     */
    explicit JChartView(QWidget *parent = 0);

    ~JChartView();

    /**
     * @brief appendChart
     * @param chart
     * @param update
     */
    void appendChart(JChart *chart, bool update = true);

    /**
     * @brief insertChart
     * @param index
     * @param chart
     * @param update
     */
    void insertChart(int index, JChart *chart, bool update = true);

    /**
     * @brief takeChart
     * @param index
     * @param update
     * @return
     */
    JChart *takeChart(int index, bool update = true);

    /**
     * @brief removeChart
     * @param chart
     * @param update
     */
    void removeChart(JEcharts::JChart *chart, bool update = true);

    /**
     * @brief clearChart
     * @param destroy
     */
    void clearChart(bool destroy = true);

    /**
     * @brief chartAt
     * @param index
     * @return
     */
    JChart *chartAt(int index) const;

    /**
     * @brief indexOfChart
     * @param chart
     * @return
     */
    int indexOfChart(JChart *chart) const;

    /**
     * @brief charts
     * @return
     */
    QList<JChart *> charts() const;

    /**
     * @brief columnCount
     * @return
     */
    int columnCount() const;

signals:
    /**
     * @brief columnCountChanged
     * @param value
     */
    void columnCountChanged(int value);

public slots:
    /**
     * @brief setColumnCount
     * @param value
     */
    void setColumnCount(int value);

    /**
     * @brief updateLayout
     */
    void updateLayout();

private:
    Q_DISABLE_COPY(JChartView)
    J_DECLARE_PRIVATE(JChartView)
};

} // end of namespace JEcharts

#endif // JCHARTVIEW_H
