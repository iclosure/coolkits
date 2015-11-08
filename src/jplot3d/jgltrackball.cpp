#include "precomp.h"
#include "jgltrackball.h"
#include "jglanimation.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLTrackBallPrivate

/**
 * @brief The JGLTrackBallPrivate class
 */
class JGLTrackBallPrivate
{
    J_DECLARE_PUBLIC(JGLTrackBall)
public:
    JGLTrackBallPrivate(JGLTrackBall *parent)
        : q_ptr(parent)
        , angle(0.0f)
        , rotation(1.0, 0.0, 0.0, 0.0)
        , defaultCenter(0.0f, 0.0f, 0.0f)
        , offset(defaultOffset())
        , axis(0.0, 1.0, 0.0)
        , angularVelocity(0.0)
        , paused(true)
        , pressed(false)
    {
        center = defaultCenter;
    }

    static QVector3D defaultOffset() { return QVector3D(0.0f, 0.0f, 0.0f); }

private:
    void init();

private:
    qreal angle;
    QQuaternion rotation;
    QVector3D center;
    QVector3D defaultCenter;
    QVector3D offset;
    QVector3D axis;
    qreal angularVelocity;

    QPointF lastPos;
    bool paused;
    bool pressed;
    JGLTrackBall::TrackMode mode;

    JPropertyAnimation *animationCenter;
    JPropertyAnimation *animationRotation;
    JPropertyAnimation *animationOffset;
};

/**
 * @brief JGLTrackBallPrivate::init
 */
void JGLTrackBallPrivate::init()
{
    Q_Q(JGLTrackBall);
    q->setObjectName("JGLTrackBall");
    // center
    animationCenter = new JPropertyAnimation(q, "center", q);
    animationCenter->setRange(defaultCenter, defaultCenter);
    // offset
    animationOffset = new JPropertyAnimation(q, "offset", q);
    animationOffset->setRange(defaultOffset(), defaultOffset());
    // rotation
    animationRotation = new JPropertyAnimation(q, "rotation", q);
    animationRotation->setRange(QQuaternion(), QQuaternion());
}

J3D_END_NAMESPACE

// - class JGLTrackBall -

/**
 * @brief JGLTrackBall::JGLTrackBall
 * @param mode
 * @param parent
 */
JGLTrackBall::JGLTrackBall(TrackMode mode, QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLTrackBallPrivate(this))
{
    Q_D(JGLTrackBall);
    d->init();
    d->mode = mode;
}

/**
 * @brief JGLTrackBall::JGLTrackBall
 * @param angularVelocity
 * @param axis
 * @param mode
 * @param parent
 */
JGLTrackBall::JGLTrackBall(qreal angularVelocity, const QVector3D &axis,
                           TrackMode mode, QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLTrackBallPrivate(this))
{
    Q_D(JGLTrackBall);
    d->init();
    d->angularVelocity = angularVelocity;
    d->axis = axis;
    d->mode = mode;
}

/**
 * @brief JGLTrackBall::~JGLTrackBall
 */
JGLTrackBall::~JGLTrackBall()
{
    delete d_ptr;
}

/**
 * @brief JGLTrackBall::push
 * @param pos
 */
void JGLTrackBall::push(const QPointF &pos, const QQuaternion &)
{
    Q_D(JGLTrackBall);
    d->rotation = rotation();
    d->pressed = true;
    d->lastPos = pos;
    d->angularVelocity = 0.0f;
}

/**
 * @brief JGLTrackBall::move
 * @param pos
 * @param transform
 * @param animation
 */
void JGLTrackBall::move(const QPointF &pos, const QQuaternion &transform, bool animation)
{
    Q_D(JGLTrackBall);
    if (!d->pressed) {
        return;
    }

    switch (d->mode) {
    case Plane:
    {
        QLineF delta(d->lastPos, pos);
        d->angularVelocity = 180 * delta.length() / M_PI;
        d->axis = QVector3D(-delta.dy(), delta.dx(), 0.0f).normalized();
        d->axis = transform.rotatedVector(d->axis);
        setRotation(QQuaternion::fromAxisAndAngle(d->axis,
                                                  180 / M_PI * delta.length()) * d->rotation, animation);
        break;
    }
    case Sphere:
    {
        QVector3D lastPos3D = QVector3D(d->lastPos.x(), d->lastPos.y(), 0.0f);
        float sqrtZ = 1 - QVector3D::dotProduct(lastPos3D, lastPos3D);
        if (sqrtZ > 0) {
            lastPos3D.setZ(sqrt(sqrtZ));
        } else {
            lastPos3D.normalize();
        }

        QVector3D currentPos3D = QVector3D(pos.x(), pos.y(), 0.0f);
        sqrtZ = 1 - QVector3D::dotProduct(currentPos3D, currentPos3D);
        if (sqrtZ > 0) {
            currentPos3D.setZ(sqrt(sqrtZ));
        } else {
            currentPos3D.normalize();
        }

        d->axis = QVector3D::crossProduct(lastPos3D, currentPos3D);
        qreal angle = 180 / M_PI * asin(sqrt(QVector3D::dotProduct(d->axis, d->axis)));

        d->axis.normalize();
        d->axis = transform.rotatedVector(d->axis);
        setRotation(QQuaternion::fromAxisAndAngle(d->axis, angle) * d->rotation, animation);
        break;
    }
    default:
        break;
    }

    d->lastPos = pos;
}

/**
 * @brief JGLTrackBall::pan
 * @param pos
 * @param transform
 * @param animation
 */
void JGLTrackBall::pan(const QPointF &pos, const QQuaternion &transform, bool animation)
{
    Q_UNUSED(transform);
    Q_D(JGLTrackBall);
    switch (d->mode) {
    case JGLTrackBall::Plane:
    {
        break;
    }
    case JGLTrackBall::Sphere:
    {
        QPointF delta = d->lastPos - pos;
        setOffset(QVector3D(d->offset.x() + delta.x(),
                            d->offset.y() + delta.y(),
                            0.0f), animation);
        break;
    }
    default:
        break;
    }

    d->lastPos = pos;
}

/**
 * @brief JGLTrackBall::release
 * @param pos
 * @param transform
 */
void JGLTrackBall::release(const QPointF &pos, const QQuaternion &transform)
{
    // Calling move() caused the rotation to stop if the framerate was too low.
    Q_D(JGLTrackBall);
    move(pos, transform);
    d->pressed = false;
}

/**
 * @brief JGLTrackBall::angle
 * @return
 */
qreal JGLTrackBall::angle() const
{
    Q_D(const JGLTrackBall);
    return d->angle;
}

/**
 * @brief JGLTrackBall::rotation
 * @return
 */
QQuaternion JGLTrackBall::rotation() const
{
    Q_D(const JGLTrackBall);
    if (d->paused || d->pressed) {
        return d->rotation;
    }

    return QQuaternion::fromAxisAndAngle(d->axis, d->angularVelocity) * d->rotation;
}

/**
 * @brief JGLTrackBall::lastPos
 * @return
 */
QPointF JGLTrackBall::lastPos() const
{
    Q_D(const JGLTrackBall);
    return d->lastPos;
}

/**
 * @brief JGLTrackBall::defaultOffset
 * @return
 */
QVector3D JGLTrackBall::defaultOffset()
{
    return JGLTrackBallPrivate::defaultOffset();
}

/**
 * @brief JGLTrackBall::offset
 * @return
 */
QVector3D JGLTrackBall::offset() const
{
    Q_D(const JGLTrackBall);
    return d->offset;
}

/**
 * @brief JGLTrackBall::center
 * @return
 */
QVector3D JGLTrackBall::center() const
{
    Q_D(const JGLTrackBall);
    return d->center;
}

/**
 * @brief JGLTrackBall::defaultCenter
 * @return
 */
QVector3D JGLTrackBall::defaultCenter() const
{
    Q_D(const JGLTrackBall);
    return d->defaultCenter;
}

/**
 * @brief JGLTrackBall::setCenter
 * @param value
 * @param animation
 */
void JGLTrackBall::setCenter(const QVector3D &value, bool animation)
{
    Q_D(JGLTrackBall);
    if (value != d->center) {
        if (animation) {
            d->animationCenter->restart(d->center, value);
        } else {
            d->center = value;
            Q_EMIT centerChanged(value);
        }
    }
}

/**
 * @brief JGLTrackBall::setRotation
 * @param value
 * @param animation
 */
void JGLTrackBall::setRotation(const QQuaternion &value, bool animation)
{
    Q_D(JGLTrackBall);
    if (value != d->rotation) {
        if (animation) {
            d->animationRotation->stop();
            d->animationRotation->setStartValue(d->rotation);
            d->animationRotation->setEndValue(value);
            d->animationRotation->start();
        } else {
            d->rotation = value;
            Q_EMIT rotationChanged(value);
        }
    }
}

/**
 * @brief JGLTrackBall::setOffset
 * @param value
 * @param animation
 */
void JGLTrackBall::setOffset(const QVector3D &value, bool animation)
{
    Q_D(JGLTrackBall);
    if (value != d->offset) {
        if (animation) {
            d->animationOffset->restart(d->offset, value);
        } else {
            d->offset = value;
            Q_EMIT offsetChanged(value);
        }
    }
}

/**
 * @brief JGLTrackBall::setDefaultCenter
 * @param value
 */
void JGLTrackBall::setDefaultCenter(const QVector3D &value, bool animation)
{
    Q_UNUSED(animation);
    Q_D(JGLTrackBall);
    if (value != d->defaultCenter) {
        d->defaultCenter = value;
        Q_EMIT defaultCenterChanged(value);
        setCenter(value, true);
    }
}

QT_END_NAMESPACE
