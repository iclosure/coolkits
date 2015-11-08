#include "precomp.h"
#include "plot3d_shape.h"
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qglcylinder.h>

using namespace Plot3D;

namespace Plot3D {

// - class JShapePrivate -

class JShapePrivate
{
public:
    JShapePrivate(QGLSceneNode *parent)
    {
        Q_UNUSED(parent);
    }

};

} // - end of namespace Plot3D

// - class JShape -

JShape::JShape(QObject *parent)
    : QGLSceneNode(parent)
{
    d = new JShapePrivate(this);
}

JShape::~JShape()
{
    delete d;
}

