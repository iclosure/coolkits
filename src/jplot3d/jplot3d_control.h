#ifndef JPLOT3D_CONTROL_H
#define JPLOT3D_CONTROL_H

#include "jplot3d_global.h"
#include "jglobject.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JControl -

class JControlPrivate;
class JGLScene;

class J3D_EXPORT JControl : public JGLObject
{
    Q_OBJECT
    Q_PROPERTY(qreal xAngle READ xAngle WRITE setXAngle NOTIFY xAngleChanged)
    Q_PROPERTY(qreal yAngle READ yAngle WRITE setYAngle NOTIFY yAngleChanged)
    Q_PROPERTY(qreal zAngle READ zAngle WRITE setZAngle NOTIFY zAngleChanged)
public:
    explicit JControl(QObject *parent = 0);
    virtual ~JControl();

    qreal xAngle() const;
    qreal yAngle() const;
    qreal zAngle() const;

Q_SIGNALS:
    void xAngleChanged(qreal);
    void yAngleChanged(qreal);
    void zAngleChanged(qreal);

public Q_SLOTS:
    void setXAngle(qreal value);
    void setYAngle(qreal value);
    void setZAngle(qreal value);

private:
    Q_DISABLE_COPY(JControl)
    J_DECLARE_PRIVATE(JControl)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_CONTROL_H
