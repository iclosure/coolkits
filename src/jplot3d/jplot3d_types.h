#ifndef JPLOT3D_TYPES_H
#define JPLOT3D_TYPES_H

#include "jplot3d_global.h"
#include <Qt3D/qglview.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(J3D)

namespace J3D {

// - class JView -

QT_FORWARD_DECLARE_CLASS(JViewPrivate)

class J3D_EXPORT JView : public QGLView
{
    Q_OBJECT
public:
    JView(QWidget *parent = 0);
    ~JView();

protected:
    virtual void initializeGL(QGLPainter *painter);
    virtual void paintGL(QGLPainter *painter);

private:
    Q_DISABLE_COPY(JView)
    J_DECLARE_PRIVATE(JView)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_TYPES_H
