#include "precomp.h"
#include "plot3d_indicator.h"
#include "plot3d_view.h"
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qglcylinder.h>
#include <Qt3D/qglpainter.h>
#include <QGraphicsScene>

using namespace Plot3D;

namespace Plot3D {

// - class JIndicatorPrivate

class JIndicatorPrivate
{
public:
    JIndicatorPrivate(JView *view, QGLSceneNode *parent)
        : view(view)
        , hovering(false)
        , clicked(false)
    {

    }

    JView *view;
    QMatrix4x4 originalModelMatrix;
    QGLCamera *camera;

    bool hovering;
    bool clicked;
};

} // - end of namespace Plot3D

// - class JIndicator

JIndicator::JIndicator(JView *view, QObject *parent)
    : QGLSceneNode(parent)
{
    d = new JIndicatorPrivate(view, this);

    d->camera = new QGLCamera(this);
    d->camera->setAdjustForAspectRatio(false);
    d->camera->setEye(QVector3D(0, 0, 10));

    QGLBuilder builder;
    builder << QGL::Smooth << QGLCylinder(0.5, 0.5, 1.0, 36, 3, true, true);

    QGLSceneNode *cylinder = builder.finalizedSceneNode();

    QGLMaterial *mat = new QGLMaterial;
    mat->setAmbientColor(QColor(100, 100, 150, 200));
    mat->setDiffuseColor(QColor(200, 200, 100, 200));
    mat->setShininess(100);
    cylinder->setMaterial(mat);
    cylinder->setEffect(QGL::LitMaterial);

    addNode(cylinder);

    setPosition(QVector3D(-1.0, -1.0, 0.0));

    d->view->registerObject(100, this);
}

JIndicator::~JIndicator()
{
    delete d;
}

void JIndicator::draw(QGLPainter *painter)
{
    painter->projectionMatrix().push();
    painter->modelViewMatrix().push();

    painter->setCamera(d->camera);

    int preObjectId = painter->objectPickId();
    painter->setObjectPickId(100);

    if (d->hovering) {
        painter->modelViewMatrix().translate(0.0, 0.0, 0.5);
    }

    painter->setObjectPickId(preObjectId);

    QGLSceneNode::draw(painter);

    painter->modelViewMatrix().pop();
    painter->projectionMatrix().pop();
}

bool JIndicator::event(QEvent *e)
{
    if (e->type() == QEvent::Enter) {
        d->hovering = true;
        d->view->updateGL();
    } else if (e->type() == QEvent::Leave) {
        d->hovering = false;
        d->view->updateGL();
    }

    return QGLSceneNode::event(e);
}
