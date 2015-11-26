#include "precomp.h"
#include "jglscene.h"
#include "jglfunction.h"
#include "jglobject.h"
#include "jglpainter.h"
#include "jglindicator.h"
#include "jgltrackball.h"
#include "jglanimation.h"
#include "jplot3d_marker.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLScenePrivate -

/**
 * @brief The JGLScenePrivate class
 */
class JGLScenePrivate
{
    J_DECLARE_PUBLIC(JGLScene)
public:
    JGLScenePrivate(QGLWidget *viewport, JGLScene *parent)
        : q_ptr(parent)
        , inited(false)
        , options(JGLScene::CameraNavigation)
        , panning(false)
        , moved(false)
        , pressedObject(0)
        , pressedButton(Qt::NoButton)
        , enteredObject(0)
        , panModifiers(Qt::NoModifier)
        , scale(defaultScale())
        , depth(defaultDepth())
        , wheelDelta(defaultWheel())
        , fovy(30.0f)
        , aspect(1.0f)
        , zNear(0.0001f)
        , zFar(100.0f)
        , indicatorDrawable(true)
        , viewportColor(defaultViewportColor())
        , viewport(viewport)
    {

    }

    static QVector3D defaultScale() { return QVector3D(1.0f, 1.0f, 1.0f); }
    static int defaultWheel() { return 1400; }
    static qreal defaultDepth() { return wheelToDepth(defaultWheel()); }
    static QQuaternion defaultRotation()
    { return QQuaternion::fromAxisAndAngle(1.0f, -1.0f, 0.0f, 30.0f); }
    static QColor defaultViewportColor() { return QColor(65, 65, 77, 255); }

    static int depthToWheel(qreal depth) { return (int)(qLn(depth / 1.0f) * 1200.0f); }
    static int wheelBound(int wheel)
    {
        if (wheel < -12000) {
            return -12000;
        } else if (wheel > 4800) {
            return 4800;
        } else {
            return wheel;
        }
    }

    static qreal wheelToDepth(int wheel)
    {
        return 1.0f * qExp((qreal)wheelBound(wheel) / 1200.0f);
    }

private:
    void init();
    void setLight0();
    void setLight1();
    void wheel(int delta);
    void pan(int deltaX, int deltaY);
    void rotation(int deltaX, int deltaY);
    void beginPaint(JGLPainter *painter, const QPointF &pos = QPointF());
    void endPaint(JGLPainter *painter);

    static void sendEnterEvent(QObject *object)
    {
        QEvent e(QEvent::Enter);
        QCoreApplication::sendEvent(object, &e);
    }

    static void sendLeaveEvent(QObject *object)
    {
        QEvent e(QEvent::Leave);
        QCoreApplication::sendEvent(object, &e);
    }

private:
    bool inited;
    JGLScene::Options options;
    bool panning;
    bool moved;
    QMap<unsigned int, JGLObject *> registerObjects;
    JGLObject *pressedObject;
    Qt::MouseButton pressedButton;
    JGLObject *enteredObject;
    QPointF startPan;
    QPointF lastPan;
    Qt::KeyboardModifiers panModifiers;

    QVector3D scale;
    qreal depth;
    int wheelDelta;
    GLdouble fovy, aspect, zNear, zFar;
    JMarker *jmarker;
    QGraphicsProxyWidget *jmarkerProxy;
    JGLTrackBall *trackBall;
    JGLIndicator *jindicator;
    bool indicatorDrawable;
    QColor viewportColor;

    QGLWidget *viewport;

    JPropertyAnimation *animationScale;
    JPropertyAnimation *animationDepth;
    JPropertyAnimation *animationViewportColor;

    QList<JGLObject *> objects;
};

/**
 * @brief JGLScenePrivate::init
 */
void JGLScenePrivate::init()
{
    Q_Q(JGLScene);

    q->setItemIndexMethod(QGraphicsScene::BspTreeIndex);

    //
    QByteArray env = qgetenv("J3D_LOG_EVENTS");
    if (env == "1") {
        options |= JGLScene::PaintingLog;
    }

    // trackBall
    trackBall = new JGLTrackBall(0.0f, QVector3D(0.0f, 1.0f, 0.0f), JGLTrackBall::Sphere, q);
    trackBall->setRotation(defaultRotation());

    // marker
    jmarker = new JMarker(q);
    jmarker->setVisible(false);
    jmarkerProxy = q->addWidget(jmarker);
    jmarkerProxy->setPalette(QColor(0, 0, 0, 0));

    // indicator
    jindicator = new JGLIndicator(5, q->height() - 5, 80, 80, q);
    jindicator->setRotation(trackBall->rotation());
    q->addItem(jindicator);

    //
    QObject::connect(trackBall, SIGNAL(offsetChanged(QVector3D)),
                     q, SLOT(update()), Qt::QueuedConnection);
    QObject::connect(trackBall, SIGNAL(centerChanged(QVector3D)),
                     q, SLOT(update()), Qt::QueuedConnection);
    QObject::connect(trackBall, SIGNAL(rotationChanged(QQuaternion)),
                     q, SLOT(update()), Qt::QueuedConnection);
    QObject::connect(jmarker, SIGNAL(textChanged(QString)),
                     q, SLOT(_emit_sceneRectChanged()));
    // animation - scales
    animationScale = new JPropertyAnimation(q, "scale", q);
    animationScale->setRange(defaultScale(), defaultScale());
    // animation - depth
    animationDepth = new JPropertyAnimation(q, "depth", q);
    animationDepth->setRange(defaultDepth(), defaultDepth());
    // animation - viewportColor
    animationViewportColor = new JPropertyAnimation(q, "viewportColor", q);
    animationViewportColor->setRange(defaultViewportColor(), defaultViewportColor());
}

/**
 * @brief JGLScenePrivate::setLight0
 */
void JGLScenePrivate::setLight0()
{
    glEnable(GL_LIGHT0);

    static const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 0.7f };
    static const GLfloat mat_shininess[] = { 50.0f };
    static const GLfloat light_position[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    //static const GLfloat white_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //static const GLfloat lmodel_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //static const GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 1.0f };

    glEnable(GL_LIGHT0);

    glPushMatrix();
    glRotatef(30.0f, 0.0f, 5.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    //glColor4f(0.2f, 0.2f, 0.2f, 0.7f);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
}

/**
 * @brief JGLScenePrivate::setLight1
 */
void JGLScenePrivate::setLight1()
{
    static const GLfloat lightDir[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    static const GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHT1);

    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glLightfv(GL_LIGHT1, GL_POSITION, lightDir);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
}

/**
 * @brief JGLScenePrivate::wheel
 * @param delta
 */
void JGLScenePrivate::wheel(int delta)
{
    wheelDelta = wheelBound(wheelDelta + delta);
    depth = wheelToDepth(wheelDelta);
}

/**
 * @brief JGLScenePrivate::pan
 * @param deltaX
 * @param deltaY
 */
void JGLScenePrivate::pan(int deltaX, int deltaY)
{
    Q_UNUSED(deltaX);
    Q_UNUSED(deltaY);
}

/**
 * @brief JGLScenePrivate::rotation
 * @param deltaX
 * @param deltaY
 */
void JGLScenePrivate::rotation(int deltaX, int deltaY)
{
    Q_UNUSED(deltaX);
    Q_UNUSED(deltaY);
}

/**
 * @brief JGLScenePrivate::beginPaint
 * @param painter
 * @param pos
 */
void JGLScenePrivate::beginPaint(JGLPainter *painter, const QPointF &pos)
{
    Q_Q(JGLScene);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    painter->begin();

    if (!pos.isNull()) {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
#if defined(Q_OS_MAC) && (QT_VERSION >= 0x050000)
        viewport[2] /= 2;
        viewport[3] /= 2;
#endif
        gluPickMatrix(pos.x(), viewport[3] - pos.y(), 10, 10, viewport);
    }

    gluPerspective(fovy, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //
    setLight0();
    //setLight1();

    QMatrix4x4 matrix;
    matrix.translate(-trackBall->offset());
    matrix.scale(scale);
    matrix.rotate(trackBall->rotation());
    matrix.translate(-trackBall->center());
    matrix(2, 3) -= depth;
    JGLFunction::loadMatrix(matrix);

    // indicator
    if (pos.isNull() && indicatorDrawable) {
        jindicator->setY(q->height() - 5);
        jindicator->setRotation(trackBall->rotation());
    }
}

/**
 * @brief JGLScenePrivate::endPaint
 */
void JGLScenePrivate::endPaint(JGLPainter *painter)
{
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    painter->end();
}

J3D_END_NAMESPACE

// - class JGLScene -

/**
 * @brief JGLScene::JGLScene
 * @param parent
 */
JGLScene::JGLScene(QGLWidget *viewport, QObject *parent)
    : QGraphicsScene(parent)
    , d_ptr(new JGLScenePrivate(viewport, this))
{
    Q_D(JGLScene);
    d->init();
}

/**
 * @brief JGLScene::JGLScene
 * @param sceneRect
 * @param parent
 */
JGLScene::JGLScene(const QRectF &sceneRect, QGLWidget *viewport, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
    , d_ptr(new JGLScenePrivate(viewport, this))
{
    Q_D(JGLScene);
    d->init();
}

/**
 * @brief JGLScene::JGLScene
 * @param x
 * @param y
 * @param width
 * @param height
 * @param parent
 */
JGLScene::JGLScene(qreal x, qreal y, qreal width, qreal height,
                   QGLWidget *viewport, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
    , d_ptr(new JGLScenePrivate(viewport, this))
{
    Q_D(JGLScene);
    d->init();
}

/**
 * @brief JGLScene::~JGLScene
 */
JGLScene::~JGLScene()
{
    delete d_ptr;
}

/**
 * @brief JGLScene::options
 * @return
 */
JGLScene::Options JGLScene::options() const
{
    Q_D(const JGLScene);
    return d->options;
}

/**
 * @brief JGLScene::setOptions
 * @param value
 */
void JGLScene::setOptions(Options value)
{
    Q_D(JGLScene);
    if (value != d->options) {
        d->options = value;
        update();
    }
}

/**
 * @brief JGLScene::setOption
 * @param option
 * @param enable
 */
void JGLScene::setOption(Option option, bool enable)
{
    Q_D(JGLScene);
    Options options = d->options;
    if (enable) {
        options |= option;
    } else {
        options &= ~option;
    }

    if (options != d->options) {
        d->options = options;
        update();
    }
}

/**
 * @brief JGLScene::registerObject
 * @param objectId
 * @param object
 * @param update
 */
void JGLScene::registerObject(unsigned int objectId, JGLObject *object, bool update)
{
    Q_D(JGLScene);
    d->registerObjects[objectId] = object;
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLScene::deregisterObject
 * @param objectId
 * @param update
 */
void JGLScene::deregisterObject(unsigned int objectId, bool update)
{
    Q_D(JGLScene);
    if (d->pressedObject && d->pressedObject->objectId() == objectId) {
        d->pressedObject = 0;
    } else if (d->enteredObject && d->enteredObject->objectId() == objectId) {
        d->enteredObject = 0;
    }
    d->registerObjects.remove(objectId);
    if (update) {
        this->update();
    }
}

#define BUFFER_SIZE 128
/**
 * @brief JGLScene::objectForPoint
 * @param pos
 * @return
 */
JGLObject *JGLScene::objectForPoint(const QPointF &pos)
{
    Q_D(JGLScene);
    static GLuint selectBuffer[BUFFER_SIZE] = { 0 };

    d->viewport->makeCurrent();

    glSelectBuffer(BUFFER_SIZE, selectBuffer);
    glRenderMode(GL_SELECT);

    JGLPainter painter(this);

    d->beginPaint(&painter, pos);

    painter.setPicking(true);

    paintGL(&painter);

    painter.setPicking(false);

    d->endPaint(&painter);

    JGLObject *object = 0;
    GLint hints = glRenderMode(GL_RENDER);
    if (hints != 0) {
        for (int i = 0; i < hints; ++i) {
            GLuint *item = selectBuffer + i * 4;
            if (item[0] >= 1) {
                unsigned int id = item[3];
                if (d->registerObjects.contains(id)) {
                    object = d->registerObjects[id];
                    break;
                }
            }
        }
    }

    d->viewport->doneCurrent();

    return object;
}

/**
 * @brief JGLScene::addObject
 * @param object
 * @param update
 */
void JGLScene::addObject(JGLObject *object, bool update)
{
    Q_D(JGLScene);
    if (!object || d->objects.contains(object)) {
        return;
    }

    object->setViewport(d->viewport);
    d->objects.append(object);
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLScene::removeObject
 * @param object
 * @param update
 */
void JGLScene::removeObject(JGLObject *object, bool update)
{
    Q_D(JGLScene);
    if (!object || !d->objects.contains(object)) {
        return;
    }

    d->objects.removeAll(object);
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLScene::clearObjects
 * @param update
 */
void JGLScene::clearObjects(bool update)
{
    Q_D(JGLScene);
    if (d->objects.isEmpty()) {
        return;
    }

    d->objects.clear();
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLScene::scale
 * @return
 */
QVector3D JGLScene::scale() const
{
    Q_D(const JGLScene);
    return d->scale;
}

/**
 * @brief JGLScene::setScale
 * @param value
 * @param animation
 */
void JGLScene::setScale(const QVector3D &value, bool animation)
{
    Q_D(JGLScene);
    if (value != d->scale) {
        if (animation) {
            d->animationScale->restart(d->scale, value);
        } else {
            d->scale = value;
            Q_EMIT scaleChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLScene::center
 * @return
 */
QVector3D JGLScene::center() const
{
    Q_D(const JGLScene);
    return d->trackBall->center();
}

/**
 * @brief JGLScene::offset
 * @return
 */
QVector3D JGLScene::offset() const
{
    Q_D(const JGLScene);
    return d->trackBall->offset();
}

/**
 * @brief JGLScene::setCenter
 * @param value
 * @param animation
 */
void JGLScene::setCenter(const QVector3D &value, bool animation)
{
    Q_D(JGLScene);
    d->trackBall->setCenter(value, animation);
}

/**
 * @brief JGLScene::setOffset
 * @param value
 * @param animation
 */
void JGLScene::setOffset(const QVector3D &value, bool animation)
{
    Q_D(JGLScene);
    d->trackBall->setOffset(value, animation);
}

/**
 * @brief JGLScene::depth
 * @return
 */
qreal JGLScene::depth() const
{
    Q_D(const JGLScene);
    return d->depth;
}

/**
 * @brief JGLScene::setDepth
 * @param value
 * @param animation
 */
void JGLScene::setDepth(qreal value, bool animation)
{
    Q_D(JGLScene);
    if (value != d->depth) {
        if (animation) {
            d->animationDepth->restart(d->depth, value);
        } else {
            d->depth = value;
            d->wheelDelta = JGLScenePrivate::depthToWheel(d->depth);
            Q_EMIT depthChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLScene::viewportColor
 * @return
 */
QColor JGLScene::viewportColor() const
{
    Q_D(const JGLScene);
    return d->viewportColor;
}

/**
 * @brief JGLScene::defaultCenter
 * @return
 */
QVector3D JGLScene::defaultCenter() const
{
    Q_D(const JGLScene);
    return d->trackBall->defaultCenter();
}

/**
 * @brief JGLScene::setViewportColor
 * @param value
 * @param animation
 */
void JGLScene::setViewportColor(const QColor &value, bool animation)
{
    Q_D(JGLScene);
    if (value != d->viewportColor) {
        if (animation) {
            d->animationViewportColor->restart(d->viewportColor, value);
        } else {
            d->viewportColor = value;
            Q_EMIT viewportColorChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLScene::setDefaultCenter
 * @param value
 * @param animation
 */
void JGLScene::setDefaultCenter(const QVector3D &value, bool animation)
{
    Q_D(JGLScene);
    d->trackBall->setDefaultCenter(value, animation);
}

/**
 * @brief JGLScene::reset
 * @param animation
 */
void JGLScene::reset(bool animation)
{
    resetScale(animation);
    resetOffset(animation);
    resetCenter(animation);
    resetDepth(animation);
    resetRotation(animation);
}

/**
 * @brief JGLScene::resetScale
 * @param animation
 */
void JGLScene::resetScale(bool animation)
{
    setScale(JGLScenePrivate::defaultScale(), animation);
}

/**
 * @brief JGLScene::resetCenter
 * @param animation
 */
void JGLScene::resetCenter(bool animation)
{
    Q_D(JGLScene);
    setCenter(d->trackBall->defaultCenter(), animation);
}

/**
 * @brief JGLScene::resetOffset
 * @param animation
 */
void JGLScene::resetOffset(bool animation)
{
    setOffset(JGLTrackBall::defaultOffset(), animation);
}

/**
 * @brief JGLScene::resetDepth
 * @param animation
 */
void JGLScene::resetDepth(bool animation)
{
    setDepth(JGLScenePrivate::defaultDepth(), animation);
}

/**
 * @brief JGLScene::resetRotation
 * @param animation
 */
void JGLScene::resetRotation(bool animation)
{
    Q_D(JGLScene);
    d->trackBall->setRotation(JGLScenePrivate::defaultRotation(), animation);
}

/**
 * @brief JGLScene::indicatorDrawable
 * @return
 */
bool JGLScene::indicatorDrawable() const
{
    Q_D(const JGLScene);
    return d->indicatorDrawable;
}

/**
 * @brief JGLScene::setIndicatorDrawable
 * @param value
 */
void JGLScene::setIndicatorDrawable(bool value)
{
    Q_D(JGLScene);
    if (value != d->indicatorDrawable) {
        d->indicatorDrawable = value;
        update();
    }
}

/**
 * @brief JGLScene::jmarker
 * @return
 */
JMarker *JGLScene::jmarker() const
{
    Q_D(const JGLScene);
    return d->jmarker;
}

/**
 * @brief JGLScene::jindicator
 * @return
 */
QGraphicsItem *JGLScene::jindicator() const
{
    Q_D(const JGLScene);
    return d->jindicator;
}

/**
 * @brief JGLScene::viewport
 * @return
 */
QGLWidget *JGLScene::viewport() const
{
    Q_D(const JGLScene);
    return d->viewport;
}

/**
 * @brief JGLScene::objects
 * @return
 */
const QList<JGLObject *> &JGLScene::objects() const
{
    Q_D(const JGLScene);
    return d->objects;
}

/**
 * @brief JGLScene::registerObjects
 * @return
 */
const QMap<unsigned int, JGLObject *> &JGLScene::registerObjects() const
{
    Q_D(const JGLScene);
    return d->registerObjects;
}

/**
 * @brief JGLScene::_emit_sceneRectChanged
 */
void JGLScene::_emit_sceneRectChanged()
{
    Q_D(JGLScene);
    if (d->jmarker->isVisible()) {
        d->jmarker->move(width() - d->jmarker->sizeHint().width() - 3,
                         height() - d->jmarker->sizeHint().height() - 3);
    }
}

/**
 * @brief JGLScene::drawBackground
 * @param painter
 * @param rect
 */
void JGLScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_D(JGLScene);
    if (!d->inited) {
        initializeGL();
        d->inited = true;
    }

    painter->beginNativePainting();
/*
    HDC hDC = wglGetCurrentDC();
    HGLRC hGLRC = wglCreateContext(hDC);
    wglShareLists(wglGetCurrentContext(), hGLRC);
    wglMakeCurrent(hDC, hGLRC);
*/
    glPushAttrib(GL_ALL_ATTRIB_BITS);

#if defined(Q_OS_MAC) && (QT_VERSION >= 0x050000)
    glViewport(0, 0, (GLsizei)rect.width() * 2, (GLsizei)rect.height() * 2);
#else
    glViewport(0, 0, (GLsizei)rect.width(), (GLsizei)rect.height());
#endif

    d->aspect = rect.width() / rect.height();

    JGLPainter painter3D(this, this);
    d->beginPaint(&painter3D);
    earlyPaintGL(&painter3D);
    paintGL(&painter3D);
    d->endPaint(&painter3D);

    glPopAttrib();

    //wglMakeCurrent(0, 0);
    //wglDeleteContext(hGLRC);

    painter->endNativePainting();
}

/**
 * @brief JGLScene::drawForeground
 * @param painter
 * @param rect
 */
void JGLScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawForeground(painter, rect);
}

/**
 * @brief JGLScene::initializeGL
 */
void JGLScene::initializeGL()
{

}

/**
 * @brief JGLScene::earlyPaintGL
 * @param painter
 */
void JGLScene::earlyPaintGL(JGLPainter *painter)
{
    Q_UNUSED(painter);
    Q_D(JGLScene);
    glClearColor(d->viewportColor.redF(), d->viewportColor.greenF(),
                 d->viewportColor.blueF(), d->viewportColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief JGLScene::mousePressEvent
 * @param e
 */
void JGLScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsScene::mousePressEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLScene);
    if (e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
        d->trackBall->push(JGLFunction::pixelPosToViewPos(sceneRect(), e->scenePos()));
#ifndef Qt_NO_CURSOR
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
#endif
    }

    d->moved = false;

    JGLObject *object = 0;
    if (!d->panning && (d->options & JGLScene::ObjectPicking)) {
        object = objectForPoint(e->scenePos());
    }

    if (d->pressedObject) {
        // Send the press event to the pressed object. Use a position
        // of (0, 0) if the mouse is still within the pressed object,
        // or (-1, -1) if the mouse is no longer within the pressed object.
        QMouseEvent event(QEvent::MouseButtonPress,
                          (d->pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                          e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(d->pressedObject, &event);
    } else if (object) {
        // Record the object that was pressed and forward the event.
        d->pressedObject = object;
        d->enteredObject = 0;
        d->pressedButton = e->button();

        // Send a mouse press event for (0, 0).
        QMouseEvent event(QEvent::MouseButtonPress, QPoint(0, 0),
                          e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(object, &event);
    } else if ((d->options & JGLScene::CameraNavigation) &&
               e->button() == Qt::LeftButton) {
        d->panning = true;
        d->lastPan = d->startPan = e->scenePos();
        d->panModifiers = e->modifiers();
    }
}

/**
 * @brief JGLScene::mouseReleaseEvent
 * @param e
 */
void JGLScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsScene::mouseReleaseEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLScene);
    if (e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
        d->trackBall->release(JGLFunction::pixelPosToViewPos(sceneRect(), e->scenePos()));
    }

    if (d->panning && e->button() == Qt::LeftButton) {
        d->panning = false;
    }
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    if (d->pressedObject) {
        // Notify the previously pressed object about the release.
        JGLObject *object = objectForPoint(e->scenePos());
        JGLObject *pressedObject = d->pressedObject;
        if (e->button() == d->pressedButton) {
            d->pressedObject = 0;
            d->pressedButton = Qt::NoButton;
            d->enteredObject = object;

            // Send the release event to the pressed object. Use a position
            // of (0, 0) if the mouse is still within the pressed object,
            // or (-1, -1) if the mouse is no longer wintin the pressed object.
            QMouseEvent event(QEvent::MouseButtonRelease,
                              (pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                              e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
            QCoreApplication::sendEvent(pressedObject, &event);

            // Send enter and leave events if necessary.
            if (object != pressedObject) {
                JGLScenePrivate::sendLeaveEvent(pressedObject);
                if (object) {
                    JGLScenePrivate::sendEnterEvent(object);
                }
            }
        } else {
            // Some other button than the original released.
            // Forward the event to the pressed object.
            QMouseEvent event(QEvent::MouseButtonRelease,
                              (pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                              e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
            QCoreApplication::sendEvent(pressedObject, &event);
        }
    }
}

/**
 * @brief JGLScene::mouseMoveEvent
 * @param e
 */
void JGLScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsScene::mouseMoveEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLScene);

    d->moved = true;

    if (e->buttons() & Qt::LeftButton) {
        d->lastPan = e->scenePos();
        d->trackBall->move(JGLFunction::pixelPosToViewPos(sceneRect(), e->scenePos()));
    }
    if (e->buttons() & Qt::RightButton) {
        d->trackBall->pan(JGLFunction::pixelPosToViewPos(sceneRect(), e->scenePos()));
    }

    if (d->panning) {
        QPointF delta = e->scenePos() - d->startPan;
        if (e->modifiers() == d->panModifiers) {
            //
        } else {
            d->startPan = d->lastPan;
            delta = e->scenePos() - d->startPan;
            d->panModifiers = e->modifiers();
        }

        d->lastPan = e->scenePos();
    } else if (d->options & JGLScene::ObjectPicking) {
        if (e->buttons() & Qt::LeftButton) {    // moving
            d->pressedObject = 0;   // cannot select when drag the track-ball
        } else {
            JGLObject *object = objectForPoint(e->scenePos());
            if (d->pressedObject) {
                // Send the move event to the pressed object. Use a position
                // (0, 0) if the mouse is still within the pressed object.
                // (-1, -1) if the mouse is no longer within the pressed object.
                QMouseEvent event(QEvent::MouseMove,
                                  (d->pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                                  e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
                QCoreApplication::sendEvent(d->pressedObject, &event);
            } else if (object) {
                if (object != d->enteredObject) {
                    if (d->enteredObject) {
                        JGLScenePrivate::sendLeaveEvent(d->enteredObject);
                    }
                    d->enteredObject = object;
                    JGLScenePrivate::sendEnterEvent(d->enteredObject);
                }
                QMouseEvent event(QEvent::MouseMove, QPoint(0, 0),
                                  e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
                QCoreApplication::sendEvent(object, &event);
            } else if (d->enteredObject) {
                JGLScenePrivate::sendLeaveEvent(d->enteredObject);
                d->enteredObject = 0;
            }
        }
    }
}

/**
 * @brief JGLScene::mouseDoubleClickEvent
 * @param e
 */
void JGLScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
{
    QGraphicsScene::mouseDoubleClickEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLScene);
    if (d->options & JGLScene::ObjectPicking) {
        JGLObject *object = objectForPoint(e->scenePos());
        if (object) {
            // Simulate a double click event for (0, 0)
            QMouseEvent event(QEvent::MouseButtonDblClick, QPoint(0, 0),
                              e->pos().toPoint(), e->button(), e->buttons(), e->modifiers());
            QCoreApplication::sendEvent(object, &event);
        } else {
            reset(true);
            Q_EMIT doubleClicked();
        }
    }
}

/**
 * @brief JGLScene::wheelEvent
 * @param e
 */
void JGLScene::wheelEvent(QGraphicsSceneWheelEvent *e)
{
    QGraphicsScene::wheelEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLScene);
    if (d->options & JGLScene::CameraNavigation) {
        if (e->modifiers() & Qt::ShiftModifier) {
            d->scale.setY(qMax<qreal>(0, d->scale.y() + e->delta() / 9600.0));
        } else {
            d->wheel(e->delta());
        }
        update();
    }
}

/**
 * @brief JGLScene::keyPressEvent
 * @param e
 */
void JGLScene::keyPressEvent(QKeyEvent *e)
{
    QGraphicsScene::keyPressEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLScene);
    if (d->options & JGLScene::CameraNavigation) {
        return;
    }

    switch (e->key()) {
    case Qt::Key_Escape:
    case Qt::Key_Q:

        break;
    case Qt::Key_Left:
    {
        d->trackBall->setRotation(QQuaternion::fromAxisAndAngle(1.0f, 1.0f, 0.0f, 30.0f), true);
        break;
    }
    case Qt::Key_Right:
    {
        d->trackBall->setRotation(QQuaternion::fromAxisAndAngle(-1.0f, 1.0f, 0.0f, 30.0f), true);
        break;
    }
    case Qt::Key_Up:
    {
        d->trackBall->setRotation(QQuaternion::fromAxisAndAngle(1.0f, -1.0f, 0.0f, 30.0f), true);
        break;
    }
    case Qt::Key_Down:
    {
        d->trackBall->setRotation(QQuaternion::fromAxisAndAngle(-1.0f, -1.0f, 0.0f, 30.0f), true);
        break;
    }
    case Qt::Key_Home:
    {
        reset(true);
        break;
    }
    case Qt::Key_Minus:
    {
        if (e->modifiers() & Qt::ControlModifier) {
            if (e->modifiers() & Qt::ShiftModifier) {
                d->wheel(30);
            } else if (e->modifiers() & Qt::AltModifier) {
                d->wheel(5);
            } else {
                d->wheel(100);
            }
            update();
        }
        break;
    }
    case Qt::Key_Plus:
    {
        if (e->modifiers() & Qt::ControlModifier) {
            if (e->modifiers() & Qt::ShiftModifier) {
                d->wheel(-30);
            } else if (e->modifiers() & Qt::AltModifier) {
                d->wheel(-5);
            } else {
                d->wheel(-100);
            }
            update();
        }
        break;
    }
    default:
        break;
    }
}

QT_END_NAMESPACE
