#ifndef JGLSCALE_H
#define JGLSCALE_H

#include "jplot3d_global.h"
#include "jglobject.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLScale -

class JGLScalePrivate;

class J3D_EXPORT JGLScale : public JGLObject
{
    Q_OBJECT
    Q_PROPERTY(bool autoScale READ autoScale WRITE setAutoScale NOTIFY autoScaleChanged)
public:
    JGLScale(QObject *parent = 0);
    virtual ~JGLScale();

    virtual void draw(JGLPainter *painter);

    bool autoScale() const;

    void resetRange();

    static JRect3D normalized(const JRect3D &box);

protected:
    virtual void update();

Q_SIGNALS:
    void autoScaleChanged(bool);

public Q_SLOTS:
    void setAutoScale(bool value);
    void setRange(const JRect3D &value, bool animation = false);

private:
    Q_DISABLE_COPY(JGLScale)
    J_DECLARE_PRIVATE(JGLScale)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLSCALE_H
