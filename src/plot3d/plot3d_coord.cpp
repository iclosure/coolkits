#include "precomp.h"
#include "plot3d_coord.h"
#include "plot3d_view.h"
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qglcylinder.h>
#include <Qt3D/qglsphere.h>
#include <Qt3D/qgldome.h>
#include <Qt3D/qglpainter.h>

using namespace Plot3D;

namespace Plot3D {

// - class JCoordPrivate

class JCoordPrivate
{
public:
    JCoordPrivate(JView *view, QGLSceneNode *parent)
        : view(view)
    {

    }

    JView *view;
};

} // - end of namespace Plot3D

JCoord::JCoord(JView *view, QObject *parent)
    : QGLSceneNode(parent)
{
    d = new JCoordPrivate(view, this);

    QGeometryData zip;
    QGLBuilder builder;
    builder << QGL::Smooth;

    builder << QGLSphere(0.01f, 36);
    QGLSceneNode *vertextO = builder.currentNode();

    builder << QGLCylinder(0.1f, 0.001f, 0.15, 36, 36, true, true);
    QGLSceneNode *vertextX = builder.currentNode();
    vertextX->setPosition(QVector3D(2.0, 2.0, 2.0));

    QGLSceneNode *cylinder = builder.finalizedSceneNode();

    QGLMaterial *mat = new QGLMaterial;
    mat->setAmbientColor(QColor(100, 100, 150, 200));
    mat->setDiffuseColor(QColor(200, 200, 100, 200));
    mat->setShininess(100);

    QUrl url;
    url.setPath(":/coolkits/plot3d/image/latte.png");
    url.setScheme("file");
    mat->setTextureUrl(url);

    vertextO->setMaterial(mat);
    vertextO->setEffect(QGL::LitDecalTexture2D);

    cylinder->setMaterial(mat);
    cylinder->setEffect(QGL::LitMaterial);

    addNode(cylinder);
}

JCoord::~JCoord()
{
    delete d;
}

void JCoord::draw(QGLPainter *painter)
{
    painter->modelViewMatrix().push();
    painter->projectionMatrix().push();

    QGLSceneNode::draw(painter);

    painter->modelViewMatrix().pop();
    painter->projectionMatrix().pop();
}
