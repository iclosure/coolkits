#ifndef PLOT3D_VIEW_H
#define PLOT3D_VIEW_H

#include "plot3d_global.h"
#include <Qt3D/qglview.h>

namespace Plot3D {

// - class JView -

class JViewPrivate;

class JPLOT3D_EXPORT JView : public QGLView
{
    Q_OBJECT
public:
    JView(QWidget *parent = 0);
    ~JView();

protected:
    virtual void initializeGL(QGLPainter *painter);
    virtual void paintGL(QGLPainter *painter);

private:
    JViewPrivate *d;
};

} // - end of namespace Plot3D

#endif // PLOT3D_VIEW_H
