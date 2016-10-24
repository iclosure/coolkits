#ifndef JECHARTSOPTION_H
#define JECHARTSOPTION_H

#include "jecharts_global.h"
#include <QObject>

namespace JEcharts {

class JEchartsOptionPrivate;
class JEcharts;

/**
 * @brief The JEchartsOption class
 */
class JECHARTS_EXPORT JEchartsOption : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QVector<QColor> color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)
public:
    explicit JEchartsOption(QObject *parent = 0);
    ~JEchartsOption();

    JEcharts *chart() const;

    QString title() const;
    QVector<QColor> color() const;
    bool animation() const;
    int animationDuration() const;

signals:
    void titleChanged(const QString &value);
    void colorChanged(const QVector<QColor> &value);
    void animationChanged(bool value);
    void animationDurationChanged(int value);

public slots:
    void setTitle(const QString &value);
    void setColor(const QVector<QColor> &value);
    void setAnimation(bool value);
    void setAnimationDuration(int value);

private:
    Q_DISABLE_COPY(JEchartsOption)
    J_DECLARE_PRIVATE(JEchartsOption)
};

} // end of namespace JEcharts

#endif // JECHARTSOPTION_H
