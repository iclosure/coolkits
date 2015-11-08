#ifndef PLOT3D_SCENE_H
#define PLOT3D_SCENE_H

#include "plot3d_global.h"
#include <Qt3D/qglscenenode.h>

namespace Plot3D {

// - class JScene -

class JView;
class JScenePrivate;

class JPLOT3D_EXPORT JScene : public QGLSceneNode
{
    Q_OBJECT
public:
    JScene(JView *parent = 0);
    ~JScene();

public:
    virtual void draw(QGLPainter *painter);

private:
    JScenePrivate *d;
};

} // - end of namespace Plot3D

#endif // PLOT3D_SCENE_H
