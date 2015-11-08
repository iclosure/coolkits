#ifndef JGLANIMATION_H
#define JGLANIMATION_H

#include "jplot3d_global.h"
#include <QPropertyAnimation>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JPropertyAnimation -

class JPropertyAnimationPrivate;

class J3D_EXPORT JPropertyAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    JPropertyAnimation(QObject *parent = 0);
    JPropertyAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = 0);
    virtual ~JPropertyAnimation();

    void restart();
    void restart(const QVariant &endValue);
    void restart(const QVariant &startValue, const QVariant &endValue);
    void restart(const QVariant &startValue, const QVariant &endValue, int msecs);

    void setRange(const QVariant &startValue, const QVariant &endValue);

private:
    Q_DISABLE_COPY(JPropertyAnimation)
    J_DECLARE_PRIVATE(JPropertyAnimation)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLANIMATION_H
