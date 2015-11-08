#include "precomp.h"
#include "jglanimation.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JPropertyAnimationPrivate -

/**
 * @brief The JPropertyAnimationPrivate class
 */
class JPropertyAnimationPrivate
{
    J_DECLARE_PUBLIC(JPropertyAnimation)
public:
    JPropertyAnimationPrivate(JPropertyAnimation *parent)
        : q_ptr(parent)
    {

    }

private:
    void init();

private:
};

/**
 * @brief JPropertyAnimationPrivate::init
 */
void JPropertyAnimationPrivate::init()
{
    Q_Q(JPropertyAnimation);
    q->setObjectName("JPropertyAnimation");
    q->setEasingCurve(QEasingCurve::OutCurve);
    q->setDuration(300);
}

J3D_END_NAMESPACE

// - class JPropertyAnimation -

/**
 * @brief JGLAnimation::JGLAnimation
 * @param parent
 */
JPropertyAnimation::JPropertyAnimation(QObject *parent)
    : QPropertyAnimation(parent)
    , d_ptr(new JPropertyAnimationPrivate(this))
{
    Q_D(JPropertyAnimation);
    d->init();
}

/**
 * @brief JGLAnimation::JGLAnimation
 * @param target
 * @param propertyName
 * @param parent
 */
JPropertyAnimation::JPropertyAnimation(QObject *target,const QByteArray &propertyName,
                                       QObject *parent)
    : QPropertyAnimation(target, propertyName, parent)
    , d_ptr(new JPropertyAnimationPrivate(this))
{
    Q_D(JPropertyAnimation);
    d->init();
}

/**
 * @brief JGLAnimation::~JGLAnimation
 */
JPropertyAnimation::~JPropertyAnimation()
{
    delete d_ptr;
}

/**
 * @brief JGLAnimation::restart
 */
void JPropertyAnimation::restart()
{
    stop();
    start();
}

/**
 * @brief JGLAnimation::restart
 * @param endValue
 */
void JPropertyAnimation::restart(const QVariant &endValue)
{
    setEndValue(endValue);
    start();
}

/**
 * @brief JGLAnimation::restart
 * @param startValue
 * @param endValue
 */
void JPropertyAnimation::restart(const QVariant &startValue, const QVariant &endValue)
{
    stop();
    setStartValue(startValue);
    setEndValue(endValue);
    start();
}

/**
 * @brief JGLAnimation::restart
 * @param startValue
 * @param endValue
 * @param msecs
 */
void JPropertyAnimation::restart(const QVariant &startValue, const QVariant &endValue, int msecs)
{
    stop();
    setStartValue(startValue);
    setEndValue(endValue);
    setDuration(msecs);
    start();
}

/**
 * @brief JGLAnimation::setRange
 * @param startValue
 * @param endValue
 */
void JPropertyAnimation::setRange(const QVariant &startValue, const QVariant &endValue)
{
    setStartValue(startValue);
    setEndValue(endValue);
}

QT_END_NAMESPACE
