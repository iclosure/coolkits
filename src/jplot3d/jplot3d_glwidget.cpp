#include "precomp.h"
#include "jplot3d_glwidget.h"
#include "jglobject.h"
#include "jplot3d_control.h"
#include "jplot3d_floor.h"
#include "jplot3d_coord.h"
#include "jglscale.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JWidgetPrivate -

/**
 * @brief The JWidgetPrivate class
 */
class JWidgetPrivate
{
    J_DECLARE_PUBLIC(JWidget)
public:
    JWidgetPrivate(JWidget *parent)
        : q_ptr(parent)
        , floorDrawable(false)
        , coordDrawable(true)
    {

    }

private:
    void init();

private:
    JControl *jcontrol;
    JFloor *jfloor;
    JGLScale *jscale;
    JCoord *jcoord;
    bool floorDrawable;
    bool coordDrawable;
};

/**
 * @brief JWidgetPrivate::init
 */
void JWidgetPrivate::init()
{
    Q_Q(JWidget);
    // control
    jcontrol = new JControl(q);
    jcontrol->setViewport(q);
    // floor
    jfloor = new JFloor(q);
    jfloor->setViewport(q);
    // scale
    jscale = new JGLScale(q);
    jscale->setViewport(q);
    // coordinate
    jcoord = new JCoord(q);
    jcoord->setViewport(q);
    //
    QObject::connect(jcoord, SIGNAL(repaint()), q, SLOT(update()));
    QObject::connect(jscale, SIGNAL(boxChanged(JRect3D)),
                     jcoord, SLOT(setBox(JRect3D)));
}

J3D_END_NAMESPACE

// - class JWidget -

/**
 * @brief JWidget::JWidget
 * @param parent
 */
JWidget::JWidget(QWidget *parent)
    : JGLWidget(parent)
    , d_ptr(new JWidgetPrivate(this))
{
    Q_D(JWidget);
    d->init();
}

/**
 * @brief JWidget::~JWidget
 */
JWidget::~JWidget()
{
    delete d_ptr;
}

/**
 * @brief JWidget::floorDrawable
 * @return
 */
bool JWidget::floorDrawable() const
{
    Q_D(const JWidget);
    return d->floorDrawable;
}

/**
 * @brief JWidget::setFloorDrawable
 * @param value
 */
void JWidget::setFloorDrawable(bool value)
{
    Q_D(JWidget);
    if (value != d->floorDrawable) {
        d->floorDrawable = value;
        update();
    }
}

/**
 * @brief JWidget::coordDrawable
 * @return
 */
bool JWidget::coordDrawable() const
{
    Q_D(const JWidget);
    return d->coordDrawable;
}

/**
 * @brief JWidget::setCoordDrawable
 * @param value
 */
void JWidget::setCoordDrawable(bool value)
{
    Q_D(JWidget);
    if (value != d->coordDrawable) {
        d->coordDrawable = value;
        update();
    }
}

/**
 * @brief JWidget::jcontrol
 * @return
 */
JControl *JWidget::jcontrol() const
{
    Q_D(const JWidget);
    return d->jcontrol;
}

/**
 * @brief JWidget::jfloor
 * @return
 */
JFloor *JWidget::jfloor() const
{
    Q_D(const JWidget);
    return d->jfloor;
}

/**
 * @brief JWidget::jscale
 * @return
 */
JGLScale *JWidget::jscale() const
{
    Q_D(const JWidget);
    return d->jscale;
}

/**
 * @brief JWidget::jcoord
 * @return
 */
JCoord *JWidget::jcoord() const
{
    Q_D(const JWidget);
    return d->jcoord;
}

/**
 * @brief JWidget::initializeGL
 */
void JWidget::initializeGL()
{

}

/**
 * @brief JWidget::paintGL
 * @param painter
 */
void JWidget::paintGL(JGLPainter *painter)
{
    Q_D(JWidget);

    // floor
    if (d->floorDrawable) {
        d->jfloor->draw(painter);
    }
    // coordinate
    if (d->coordDrawable) {
        d->jcoord->draw(painter);
    }
    //
    QListIterator<JGLObject *> iter(objects());
    while (iter.hasNext()) {
        iter.next()->draw(painter);
    }
}

QT_END_NAMESPACE
