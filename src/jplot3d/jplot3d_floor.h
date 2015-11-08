#ifndef JPLOT3D_FLOOR_H
#define JPLOT3D_FLOOR_H

#include "jplot3d_global.h"
#include "jglobject.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JFloor -

class JFloorPrivate;

class J3D_EXPORT JFloor : public JGLObject
{
    Q_OBJECT
public:
    explicit JFloor(QObject *parent = 0);
    virtual ~JFloor();

    virtual void draw(JGLPainter *painter);

private:
    Q_DISABLE_COPY(JFloor)
    J_DECLARE_PRIVATE(JFloor)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_FLOOR_H
