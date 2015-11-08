#include "precomp.h"
#include "jplot3d_view.h"
#include "jplot3d_scene.h"
#include "3rdparty/glextensions.h"
#include <QGLFormat>

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JViewPrivate -

/**
 * @brief The JViewPrivate class
 */
class JViewPrivate
{
    J_DECLARE_PUBLIC(JView)
public:
    JViewPrivate(JView *parent)
        : q_ptr(parent)
    {

    }

private:
    void init();

private:
};

/**
 * @brief JViewPrivate::init
 */
void JViewPrivate::init()
{
    Q_Q(JView);
    q->setObjectName("JView");
    q->setScene(new JScene(QRectF(0.0f, 0.0f, 1024.0f, 768.0f),
                           qobject_cast<QGLWidget *>(q->viewport()), q));
}

J3D_END_NAMESPACE

// - class JView -

/**
 * @brief JView::JView
 * @param parent
 */
JView::JView(QWidget *parent)
    : JGLView(parent)
    , d_ptr(new JViewPrivate(this))
{
    Q_D(JView);
    d->init();
}

/**
 * @brief JView::~JView
 *
 */
JView::~JView()
{
    delete d_ptr;
}

QT_END_NAMESPACE
