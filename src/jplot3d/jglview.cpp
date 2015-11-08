#include "precomp.h"
#include "jglview.h"
#include <QGLWidget>
#include "3rdparty/glextensions.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLViewPrivate -

/**
 * @brief The JGLViewPrivate class
 */
class JGLViewPrivate
{
    J_DECLARE_PUBLIC(JGLView)
public:
    JGLViewPrivate(JGLView *parent)
        : q_ptr(parent)
    {

    }

private:
    void init();

private:
    QGLWidget *glWidget;
};

/**
 * @brief JGLViewPrivate::init
 */
void JGLViewPrivate::init()
{
    Q_Q(JGLView);
    q->setObjectName("JGLView");
    q->setMouseTracking(true);
    q->setRenderHints(QPainter::Antialiasing |
                      QPainter::SmoothPixmapTransform |
                      QPainter::HighQualityAntialiasing |
                      QPainter::TextAntialiasing);
    q->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    glWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers), q);
    glWidget->makeCurrent();
    q->setViewport(glWidget);
    q->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    if (!getGLExtensionFunctions().resolve(glWidget->context())) {
        //
    }
}

J3D_END_NAMESPACE

// - class JGLView -

/**
 * @brief JGLView::JGLView
 * @param parent
 */
JGLView::JGLView(QWidget *parent)
    : QGraphicsView(parent)
    , d_ptr(new JGLViewPrivate(this))
{
    Q_D(JGLView);
    d->init();
}

/**
 * @brief JGLView::~JGLView
 */
JGLView::~JGLView()
{
    delete d_ptr;
}

/**
 * @brief JGLView::resizeEvent
 * @param e
 */
void JGLView::resizeEvent(QResizeEvent *e)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), e->size()));
    }

    QGraphicsView::resizeEvent(e);
}

/**
 * @brief JGLView::wheelEvent
 * @param e
 */
void JGLView::wheelEvent(QWheelEvent *e)
{
#if 0
    if (e->modifiers() & Qt::ControlModifier) {
        qreal scaleFactor = pow(2.0f, -e->delta() / 240.0f);
        qreal factor = transform().scale(scaleFactor, scaleFactor, scaleFactor)
                .mapRect(QRectF(0, 0, 1, 1)).width();
        if (0.07f <= factor && factor <= 100.0f) {
            scale(scaleFactor, scaleFactor);
        }
    }
#endif
    QGraphicsView::wheelEvent(e);
}

QT_END_NAMESPACE
