#ifndef JPLOT3D_SHADOW_H
#define JPLOT3D_SHADOW_H

#include "jplot3d_global.h"
#include "jglobject.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JShadow -

class JShadowPrivate;

class J3D_EXPORT JShadow : public JGLObject
{
    Q_OBJECT
public:
    JShadow(QObject *parent = 0);
    virtual ~JShadow();

private:
    Q_DISABLE_COPY(JShadow)
    J_DECLARE_PRIVATE(JShadow)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_SHADOW_H
