#ifndef JGLVIEW_H
#define JGLVIEW_H

#include "jplot3d_global.h"
#include <QGraphicsView>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLView -

class JGLViewPrivate;

class J3D_EXPORT JGLView : public QGraphicsView
{
    Q_OBJECT
public:
    JGLView(QWidget *parent = 0);
    virtual ~JGLView();

Q_SIGNALS:

public Q_SLOTS:

protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

private:
    Q_DISABLE_COPY(JGLView)
    J_DECLARE_PRIVATE(JGLView)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLVIEW_H
