#ifndef JGLPICKING_H
#define JGLPICKING_H

#include "jplot3d_global.h"
#include <QObject>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLPicking -

class JGLPickingPrivate;

class J3D_EXPORT JGLPicking : public QObject
{
    Q_OBJECT
public:
    explicit JGLPicking(QObject *parent = 0);
    virtual ~JGLPicking();

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JGLPicking)
    J_DECLARE_PRIVATE(JGLPicking)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLPICKING_H
