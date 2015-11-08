#include "precomp.h"
#include "jplot3d_control.h"
#include "jglscene.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JControlPrivate -

/**
 * @brief The JControlPrivate class
 */
class JControlPrivate
{
    J_DECLARE_PUBLIC(JControl)
public:
    JControlPrivate(JControl *parent)
        : q_ptr(parent)
        , xAngle(0.0f)
        , yAngle(0.0f)
        , zAngle(0.0f)
    {

    }

    static qreal normalizeAngle(qreal angle);

private:
    void init();

private:
    qreal xAngle;
    qreal yAngle;
    qreal zAngle;
};

/**
 * @brief JControlPrivate::normalizeAngle
 * @param angle
 * @return
 */
qreal JControlPrivate::normalizeAngle(qreal angle)
{
    qreal t = angle;
    while (angle < 0.0f) {
        t += 360.0f * 16;
    }
    while (t > 360.0f * 16) {
        t -= 360.0f * 16;
    }
    return t;
}

/**
 * @brief JControlPrivate::init
 */
void JControlPrivate::init()
{

}

J3D_END_NAMESPACE

// - class JControl -

/**
 * @brief JControl::JControl
 * @param parent
 */
JControl::JControl(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JControlPrivate(this))
{
    Q_D(JControl);
    d->init();
}

/**
 * @brief JControl::~JControl
 */
JControl::~JControl()
{
    delete d_ptr;
}

/**
 * @brief JControl::xAngle
 * @return
 */
qreal JControl::xAngle() const
{
    Q_D(const JControl);
    return d->xAngle;
}

/**
 * @brief JControl::yAngle
 * @return
 */
qreal JControl::yAngle() const
{
    Q_D(const JControl);
    return d->yAngle;
}

/**
 * @brief JControl::zAngle
 * @return
 */
qreal JControl::zAngle() const
{
    Q_D(const JControl);
    return d->zAngle;
}

/**
 * @brief JControl::setXAngle
 * @param value
 */
void JControl::setXAngle(qreal value)
{
    Q_D(JControl);
    if (value != d->xAngle) {
        d->xAngle = value;
        Q_EMIT xAngleChanged(value);
    }
}

/**
 * @brief JControl::setYAngle
 * @param value
 */
void JControl::setYAngle(qreal value)
{
    Q_D(JControl);
    if (value != d->yAngle) {
        d->yAngle = value;
        Q_EMIT yAngleChanged(value);
    }
}

/**
 * @brief JControl::setZAngle
 * @param value
 */
void JControl::setZAngle(qreal value)
{
    Q_D(JControl);
    if (value != d->zAngle) {
        d->zAngle = value;
        Q_EMIT zAngleChanged(value);
    }
}

QT_END_NAMESPACE
