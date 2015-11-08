#include "precomp.h"
#include "plot3d_scene.h"
#include "plot3d_indicator.h"
#include "plot3d_coord.h"
#include "plot3d_shape.h"
#include "plot3d_view.h"
#include <Qt3D/qglpainter.h>

using namespace Plot3D;

namespace Plot3D {

// - class JScenePrivate

class JScenePrivate
{
public:
    JScenePrivate(JView *view, QGLSceneNode *parent)
        : view(view)
    {
        // indicator
        indicator = new JIndicator(view, parent);
        parent->addNode(indicator);

        // coord
        coord = new JCoord(view, parent);
        parent->addNode(coord);

        // shape
        shape = new JShape(parent);
        parent->addNode(shape);
    }

    JView *view;
    JIndicator *indicator;
    JCoord *coord;
    JShape *shape;
};

} // - end of namespace Plot3D

// - class JScene -

JScene::JScene(JView *parent)
    : QGLSceneNode(parent)
{
    d = new JScenePrivate(parent, this);

    setPalette(new QGLMaterialCollection(this));
    setEffect(QGL::LitMaterial);
}

JScene::~JScene()
{
    delete d;
}

void JScene::draw(QGLPainter *painter)
{
    QGLSceneNode::draw(painter);
}
