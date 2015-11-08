#ifndef PLOT3D_INDICATOR_H
#define PLOT3D_INDICATOR_H

#include "plot3d_global.h"
#include <Qt3D/qglscenenode.h>

namespace Plot3D {

// - class JIndicator

class JView;
class JIndicatorPrivate;

class JPLOT3D_EXPORT JIndicator : public QGLSceneNode
{
    Q_OBJECT
public:
    JIndicator(JView *view, QObject *parent = 0);
    ~JIndicator();

public:
    virtual void draw(QGLPainter *painter);

private:
    JIndicatorPrivate *d;

    // QObject interface
public:
    virtual bool event(QEvent *);
};

} // - end of namespace Plot3D

#endif // PLOT3D_INDICATOR_H
