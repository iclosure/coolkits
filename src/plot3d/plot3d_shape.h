#ifndef PLOT3D_SHAPE_H
#define PLOT3D_SHAPE_H

#include "plot3d_global.h"
#include <Qt3D/qglscenenode.h>

namespace Plot3D {

// - class JShape -

class JShapePrivate;

class JPLOT3D_EXPORT JShape : public QGLSceneNode
{
    Q_OBJECT
public:
    JShape(QObject *parent = 0);
    ~JShape();

private:
    JShapePrivate *d;
};

} // - end of namespace Plot3D

#endif // PLOT3D_SHAPE_H
