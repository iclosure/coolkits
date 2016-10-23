#ifndef JSTEPCHARTOPTION_H
#define JSTEPCHARTOPTION_H

#include "../jecharts_global.h"
#include <QObject>

namespace JEcharts {

class JStepChartOptionPrivate;

class JECHARTS_EXPORT JStepChartOption : public QObject
{
    Q_OBJECT
public:
    explicit JStepChartOption(QObject *parent = 0);
    ~JStepChartOption();

signals:

public slots:

private:
    Q_DISABLE_COPY(JStepChartOption)
    J_DECLARE_PRIVATE(JStepChartOption)
};

} // end of namespace JEcharts

#endif // JSTEPCHARTOPTION_H
