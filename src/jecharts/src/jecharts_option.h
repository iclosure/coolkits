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
    Q_PROPERTY(QString option READ option WRITE setOption NOTIFY optionChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QVector<QColor> color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool animation READ animation WRITE setAnimation NOTIFY animationChanged)
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit JEchartsOption(QObject *parent = 0);
    ~JEchartsOption();

    JEcharts *chart() const;

    QString title() const;
    QVector<QColor> color() const;
    QColor backgroundColor() const;
    bool animation() const;
    int animationDuration() const;
    QString option() const;

    Q_INVOKABLE void appendData(int index, const QVariant &data);
    Q_INVOKABLE void leftShiftData(int index, const QVariant &data);

signals:
    void optionChanged(const QString &value);
    void titleChanged(const QString &value);
    void colorChanged(const QVector<QColor> &value);
    void backgroundColorChanged(const QColor &value);
    void animationChanged(bool value);
    void animationDurationChanged(int value);

public slots:
    void setOption(const QString &content);
    void setTitle(const QString &value);
    void setColor(const QVector<QColor> &value);
    void setBackgroundColor(const QColor &value);
    void setAnimation(bool value);
    void setAnimationDuration(int value);

private:
    Q_DISABLE_COPY(JEchartsOption)
    J_DECLARE_PRIVATE(JEchartsOption)
};

} // end of namespace JEcharts

#endif // JECHARTSOPTION_H
