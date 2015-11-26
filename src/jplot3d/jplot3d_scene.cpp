#include "precomp.h"
#include "jplot3d_scene.h"
#include "jglobject.h"
#include "jplot3d_control.h"
#include "jplot3d_floor.h"
#include "jplot3d_coord.h"
#include "jglscale.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JScenePrivate -

/**
 * @brief The JScenePrivate class
 */
class JScenePrivate
{
    J_DECLARE_PUBLIC(JScene)
public:
    JScenePrivate(JScene *parent)
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
 * @brief JScenePrivate::init
 */
void JScenePrivate::init()
{
    Q_Q(JScene);
    // control
    jcontrol = new JControl(q);
    jcontrol->setViewport(q->viewport());
    // floor
    jfloor = new JFloor(q);
    jfloor->setViewport(q->viewport());
    // scale
    jscale = new JGLScale(q);
    jscale->setViewport(q->viewport());
    // coordinate
    jcoord = new JCoord(q);
    jcoord->setViewport(q->viewport());
    //
    QObject::connect(jcoord, SIGNAL(repaint()), q, SLOT(update()));
    QObject::connect(jscale, SIGNAL(boxChanged(JRect3D)),
                     jcoord, SLOT(setBox(JRect3D)));
    QObject::connect(jscale, SIGNAL(intervalChanged(QVector3D)),
                     jcoord, SLOT(setInterval(QVector3D)));
    /*
    //TEST
    QWidget *dialog = new QWidget(0, Qt::FramelessWindowHint);
    //dialog->setAttribute(Qt::WA_TranslucentBackground);
    dialog->setWindowOpacity(0.7);
    dialog->setMinimumWidth(200);
    dialog->move(20, 120);
    QPushButton *buttonTest = new QPushButton("test1", dialog);
    QVBoxLayout *horiLayout1 = new QVBoxLayout(dialog);
    horiLayout1->addWidget(buttonTest);
    QGraphicsProxyWidget *proxy = q->addWidget(dialog, Qt::Widget);
    proxy->setAutoFillBackground(true);
    proxy->setPalette(QColor(100, 100, 100, 220));
    buttonTest->setStyleSheet("QPushButton{color:black;}");*/
}

J3D_END_NAMESPACE

// - class JScene -

/**
 * @brief JScene::JScene
 * @param parent
 */
JScene::JScene(QGLWidget *viewport, QObject *parent)
    : JGLScene(viewport, parent)
    , d_ptr(new JScenePrivate(this))
{
    Q_D(JScene);
    d->init();
}

/**
 * @brief JScene::JScene
 * @param sceneRect
 * @param parent
 */
JScene::JScene(const QRectF &sceneRect, QGLWidget *viewport, QObject *parent)
    : JGLScene(sceneRect, viewport, parent)
    , d_ptr(new JScenePrivate(this))
{
    Q_D(JScene);
    d->init();
}

/**
 * @brief JScene::~JScene
 */
JScene::~JScene()
{
    delete d_ptr;
}

/**
 * @brief JScene::floorDrawable
 * @return
 */
bool JScene::floorDrawable() const
{
    Q_D(const JScene);
    return d->floorDrawable;
}

/**
 * @brief JScene::setFloorDrawable
 * @param value
 */
void JScene::setFloorDrawable(bool value)
{
    Q_D(JScene);
    if (value != d->floorDrawable) {
        d->floorDrawable = value;
        update();
    }
}

/**
 * @brief JScene::coordDrawable
 * @return
 */
bool JScene::coordDrawable() const
{
    Q_D(const JScene);
    return d->coordDrawable;
}

/**
 * @brief JScene::setCoordDrawable
 * @param value
 */
void JScene::setCoordDrawable(bool value)
{
    Q_D(JScene);
    if (value != d->coordDrawable) {
        d->coordDrawable = value;
        update();
    }
}

/**
 * @brief JScene::jcontrol
 * @return
 */
JControl *JScene::jcontrol() const
{
    Q_D(const JScene);
    return d->jcontrol;
}

/**
 * @brief JScene::jfloor
 * @return
 */
JFloor *JScene::jfloor() const
{
    Q_D(const JScene);
    return d->jfloor;
}

/**
 * @brief JScene::jscale
 * @return
 */
JGLScale *JScene::jscale() const
{
    Q_D(const JScene);
    return d->jscale;
}

/**
 * @brief JScene::jcoord
 * @return
 */
JCoord *JScene::jcoord() const
{
    Q_D(const JScene);
    return d->jcoord;
}

/**
 * @brief JScene::initializeGL
 */
void JScene::initializeGL()
{

}

/**
 * @brief JScene::paintGL
 * @param painter
 */
void JScene::paintGL(JGLPainter *painter)
{
    Q_D(JScene);

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
