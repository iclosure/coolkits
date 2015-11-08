#ifndef JGLTRACKBALL_H
#define JGLTRACKBALL_H

#include "jplot3d_global.h"
#include <QObject>
#include <QVector3D>
#include <QQuaternion>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLTrackBall -

class JGLTrackBallPrivate;

class J3D_EXPORT JGLTrackBall : public QObject
{
    Q_OBJECT
    Q_ENUMS(TrackMode)
    Q_PROPERTY(QVector3D center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QVector3D offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(QVector3D defaultCenter READ defaultCenter WRITE setDefaultCenter NOTIFY defaultCenterChanged)
public:
    enum TrackMode {
        Plane,
        Sphere
    };

    explicit JGLTrackBall(TrackMode mode = Sphere, QObject *parent = 0);
    JGLTrackBall(qreal angularVelocity, const QVector3D &axis,
                 TrackMode mode, QObject *parent = 0);
    virtual ~JGLTrackBall();

    void push(const QPointF &pos, const QQuaternion &transform = QQuaternion());
    void move(const QPointF &pos, const QQuaternion &transform = QQuaternion(), bool animation = false);
    void pan(const QPointF &pos, const QQuaternion &transform = QQuaternion(), bool animation = false);
    void release(const QPointF &pos, const QQuaternion &transform = QQuaternion());

    qreal angle() const;
    QQuaternion rotation() const;
    QPointF lastPos() const;
    static QVector3D defaultOffset();
    QVector3D offset() const;
    QVector3D center() const;
    QVector3D defaultCenter() const;

Q_SIGNALS:
    void centerChanged(const QVector3D &);
    void rotationChanged(const QQuaternion &);
    void offsetChanged(const QVector3D &);
    void defaultCenterChanged(const QVector3D &);

public Q_SLOTS:
    void setCenter(const QVector3D &value, bool animation = false);
    void setRotation(const QQuaternion &value, bool animation = false);
    void setOffset(const QVector3D &value, bool animation = false);
    void setDefaultCenter(const QVector3D &value, bool animation = false);

private:
    Q_DISABLE_COPY(JGLTrackBall)
    J_DECLARE_PRIVATE(JGLTrackBall)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLTRACLBALL_H
