#ifndef JPLOT3D_GLWIDGET_H
#define JPLOT3D_GLWIDGET_H

#include "jplot3d_global.h"
#include "jglwidget.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JWidget -

class JWidgetPrivate;
class JControl;
class JFloor;
class JGLScale;
class JCoord;

class J3D_EXPORT JWidget : public JGLWidget
{
    Q_OBJECT
public:
    JWidget(QWidget *parent = 0);
    virtual ~JWidget();

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
    Q_DISABLE_COPY(JWidget)
    J_DECLARE_PRIVATE(JWidget)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_GLWIDGET_H
