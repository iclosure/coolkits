#include "precomp.h"
#include "plot3d_view.h"
#include "plot3d_scene.h"
#include "plot3d_indicator.h"
#include <Qt3D/qglbuilder.h>
#include <Qt3D/qglteapot.h>
#include <Qt3D/qglcube.h>
#include <Qt3D/qglsphere.h>

using namespace Plot3D;

namespace Plot3D {

// - class JViewPrivate -

class JViewPrivate
{
public:
    /**
     * @brief JViewPrivate
     */
    JViewPrivate(JView *view)
    {
        //
        scene = new JScene(view);
    }

    JScene *scene;
};

} // - end of namespace Plot3D

// - class JView -

/**
 * @brief JView::JView
 * @param parent
 */
JView::JView(QWidget *parent)
    : QGLView(parent)
{
    d = new JViewPrivate(this);

    setOption(QGLView::ObjectPicking, true);
    setOption(QGLView::CameraNavigation, true);
    setOption(QGLView::FOVZoom, true);
}

/**
 * @brief JView::~JView
 */
JView::~JView()
{
    delete d;
}

/**
 * @brief JPlot3D::JView::initializeGL
 * @param painter
 */
void JView::initializeGL(QGLPainter *painter)
{
    QGLMaterial *material = new QGLMaterial();
    material->setColor(QColor(76, 76, 76, 150));
    //material->setAmbientColor(QColor(76, 76, 76, 200));
    material->setSpecularColor(QColor(76, 76, 76, 200));
    //material->setDiffuseColor(QColor(48, 32, 32, 255));
    //material->setEmittedLight(QColor(70, 70, 100, 200));
    material->setShininess(50);

    d->scene->setMaterial(material);

    painter->setClearColor(QColor(150, 150, 200, 255));
    camera()->setFieldOfView(45);
    camera()->setNearPlane(0.001);
    camera()->setFarPlane(1000.0);
    camera()->setEye(QVector3D(1.0, 1.0, 3));
    //camera()->setEye(camera()->eye() + QVector3D(0, 3, 10));
    //glEnable(GL_BLEND);
}

/**
 * @brief JPlot3D::JView::paintGL
 * @param painter
 */
void JView::paintGL(QGLPainter *painter)
{
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    d->scene->draw(painter);

    //glColor4d(100, 100, 150, 200);
    //glutSolidCone(0.5, 1.0, 50, 50);
}
