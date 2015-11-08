#ifndef PLOT3D_COORD_H
#define PLOT3D_COORD_H

#include "plot3d_global.h"
#include <Qt3D/qglscenenode.h>

namespace Plot3D {

// - class JCoord -

class JView;
class JCoordPrivate;

class JPLOT3D_EXPORT JCoord : public QGLSceneNode
{
    Q_OBJECT
public:
    JCoord(JView *view, QObject *parent = 0);
    ~JCoord();

public:
    virtual void draw(QGLPainter *painter);

private:
    JCoordPrivate *d;
};

} // - end of namespace Plot3D

#endif // PLOT3D_COORD_H
