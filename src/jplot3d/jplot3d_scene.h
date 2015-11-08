#ifndef JPLOT3D_SCENE_H
#define JPLOT3D_SCENE_H

#include "jplot3d_global.h"
#include "jglscene.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QGLWidget;

namespace J3D {

// - class JScene -

class JScenePrivate;
class JControl;
class JFloor;
class JGLScale;
class JCoord;

class J3D_EXPORT JScene : public JGLScene
{
    Q_OBJECT
public:
    JScene(QGLWidget *viewport, QObject *parent = 0);
    JScene(const QRectF &sceneRect, QGLWidget *viewport, QObject *parent = 0);
    virtual ~JScene();

    bool floorDrawable() const;
    void setFloorDrawable(bool value);

    bool coordDrawable() const;
    void setCoordDrawable(bool value);

    virtual JControl *jcontrol() const;
    virtual JFloor *jfloor() const;
    virtual JGLScale *jscale() const;
    virtual JCoord *jcoord() const;

protected:
    virtual void initializeGL();
    virtual void paintGL(JGLPainter *painter);

private:
    Q_DISABLE_COPY(JScene)
    J_DECLARE_PRIVATE(JScene)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_SCENE_H
