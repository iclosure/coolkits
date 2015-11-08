#include "precomp.h"
#include "jglwidget.h"
#include "jglfunction.h"
#include "jglobject.h"
#include "jglpainter.h"
#include "jglindicator.h"
#include "jgltrackball.h"
#include "jglanimation.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLWidgetPrivate -

/**
 * @brief The JGLWidgetPrivate class
 */
class JGLWidgetPrivate
{
    J_DECLARE_PUBLIC(JGLWidget)
public:
    JGLWidgetPrivate(JGLWidget *parent)
        : q_ptr(parent)
        , options(JGLWidget::CameraNavigation)
        , panning(false)
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
    JGLWidget::Options options;
    bool panning;
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
    JGLTrackBall *trackBall;
    JGLIndicator *jindicator;
    bool indicatorDrawable;
    QColor viewportColor;

    JPropertyAnimation *animationScale;
    JPropertyAnimation *animationDepth;
    JPropertyAnimation *animationViewportColor;

    QList<JGLObject *> objects;
};

/**
 * @brief JGLWidgetPrivate::init
 */
void JGLWidgetPrivate::init()
{
    Q_Q(JGLWidget);

    //
    QByteArray env = qgetenv("J3D_LOG_EVENTS");
    if (env == "1") {
        options |= JGLWidget::PaintingLog;
    }

    // trackBall
    trackBall = new JGLTrackBall(0.0f, QVector3D(0.0f, 1.0f, 0.0f), JGLTrackBall::Sphere, q);
    trackBall->setRotation(defaultRotation());
/*
    // indicator
    jindicator = new JGLIndicator(5, q->height() - 5, 80, 80, q);
    jindicator->setRotation(trackBall->rotation());

    //
    q->addItem(jindicator);
    */
    QObject::connect(trackBall, SIGNAL(offsetChanged(QVector3D)),
                     q, SLOT(update()), Qt::QueuedConnection);
    QObject::connect(trackBall, SIGNAL(centerChanged(QVector3D)),
                     q, SLOT(update()), Qt::QueuedConnection);
    QObject::connect(trackBall, SIGNAL(rotationChanged(QQuaternion)),
                     q, SLOT(update()), Qt::QueuedConnection);
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
 * @brief JGLWidgetPrivate::setLight0
 */
void JGLWidgetPrivate::setLight0()
{
    glEnable(GL_LIGHT0);

    static const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 0.7f };
    static const GLfloat mat_shininess[] = { 50.0f };
    static const GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat white_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 0.9f };
    //static const GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 1.0f };

    glPushMatrix();
    glRotatef(30.0f, 0.0f, 5.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    //glColor4f(0.2f, 0.2f, 0.2f, 0.7f);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
}

/**
 * @brief JGLWidgetPrivate::setLight1
 */
void JGLWidgetPrivate::setLight1()
{
    static const GLfloat lightDir[] = { 0.0f, 1.0f, 0.0f, 0.0f };
    //static const GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT1, GL_POSITION, lightDir);
    //glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
    //glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor);
    //glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
}

/**
 * @brief JGLWidgetPrivate::wheel
 * @param delta
 */
void JGLWidgetPrivate::wheel(int delta)
{
    wheelDelta = wheelBound(wheelDelta + delta);
    depth = wheelToDepth(wheelDelta);
}

/**
 * @brief JGLWidgetPrivate::pan
 * @param deltaX
 * @param deltaY
 */
void JGLWidgetPrivate::pan(int deltaX, int deltaY)
{
    Q_UNUSED(deltaX);
    Q_UNUSED(deltaY);
}

/**
 * @brief JGLWidgetPrivate::rotation
 * @param deltaX
 * @param deltaY
 */
void JGLWidgetPrivate::rotation(int deltaX, int deltaY)
{
    Q_UNUSED(deltaX);
    Q_UNUSED(deltaY);
}

/**
 * @brief JGLWidgetPrivate::beginPaint
 * @param painter
 * @param pos
 */
void JGLWidgetPrivate::beginPaint(JGLPainter *painter, const QPointF &pos)
{
    //Q_Q(JGLWidget);

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
/*
    // indicator
    if (pos.isNull() && indicatorDrawable) {
        jindicator->setY(q->height() - 5);
        jindicator->setRotation(trackBall->rotation());
    }*/
}

/**
 * @brief JGLWidgetPrivate::endPaint
 */
void JGLWidgetPrivate::endPaint(JGLPainter *painter)
{
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    painter->end();
}

J3D_END_NAMESPACE

// - class JGLWidget -

/**
 * @brief JGLWidget::JGLWidget
 * @param parent
 */
JGLWidget::JGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
    , d_ptr(new JGLWidgetPrivate(this))
{
    Q_D(JGLWidget);
    d->init();
}

/**
 * @brief JGLWidget::~JGLWidget
 */
JGLWidget::~JGLWidget()
{
    delete d_ptr;
}

/**
 * @brief JGLWidget::options
 * @return
 */
JGLWidget::Options JGLWidget::options() const
{
    Q_D(const JGLWidget);
    return d->options;
}

/**
 * @brief JGLWidget::setOptions
 * @param value
 */
void JGLWidget::setOptions(Options value)
{
    Q_D(JGLWidget);
    if (value != d->options) {
        d->options = value;
        update();
    }
}

/**
 * @brief JGLWidget::setOption
 * @param option
 * @param enable
 */
void JGLWidget::setOption(Option option, bool enable)
{
    Q_D(JGLWidget);
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
 * @brief JGLWidget::registerObject
 * @param objectId
 * @param object
 * @param update
 */
void JGLWidget::registerObject(unsigned int objectId, JGLObject *object, bool update)
{
    Q_D(JGLWidget);
    d->registerObjects[objectId] = object;
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLWidget::deregisterObject
 * @param objectId
 * @param update
 */
void JGLWidget::deregisterObject(unsigned int objectId, bool update)
{
    Q_D(JGLWidget);
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
 * @brief JGLWidget::objectForPoint
 * @param pos
 * @return
 */
JGLObject *JGLWidget::objectForPoint(const QPointF &pos)
{
    Q_D(JGLWidget);
    static GLuint selectBuffer[BUFFER_SIZE] = { 0 };

    makeCurrent();

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

    doneCurrent();

    return object;
}

/**
 * @brief JGLWidget::addObject
 * @param object
 * @param update
 */
void JGLWidget::addObject(JGLObject *object, bool update)
{
    Q_D(JGLWidget);
    if (!object || d->objects.contains(object)) {
        return;
    }

    d->objects.append(object);
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLWidget::removeObject
 * @param object
 * @param update
 */
void JGLWidget::removeObject(JGLObject *object, bool update)
{
    Q_D(JGLWidget);
    if (!object || !d->objects.contains(object)) {
        return;
    }

    d->objects.removeAll(object);
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLWidget::clearObjects
 * @param update
 */
void JGLWidget::clearObjects(bool update)
{
    Q_D(JGLWidget);
    if (d->objects.isEmpty()) {
        return;
    }

    d->objects.clear();
    if (update) {
        this->update();
    }
}

/**
 * @brief JGLWidget::scale
 * @return
 */
QVector3D JGLWidget::scale() const
{
    Q_D(const JGLWidget);
    return d->scale;
}

/**
 * @brief JGLWidget::setScale
 * @param value
 * @param animation
 */
void JGLWidget::setScale(const QVector3D &value, bool animation)
{
    Q_D(JGLWidget);
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
 * @brief JGLWidget::center
 * @return
 */
QVector3D JGLWidget::center() const
{
    Q_D(const JGLWidget);
    return d->trackBall->center();
}

/**
 * @brief JGLWidget::offset
 * @return
 */
QVector3D JGLWidget::offset() const
{
    Q_D(const JGLWidget);
    return d->trackBall->offset();
}

/**
 * @brief JGLWidget::setCenter
 * @param value
 * @param animation
 */
void JGLWidget::setCenter(const QVector3D &value, bool animation)
{
    Q_D(JGLWidget);
    d->trackBall->setCenter(value, animation);
}

/**
 * @brief JGLWidget::setOffset
 * @param value
 * @param animation
 */
void JGLWidget::setOffset(const QVector3D &value, bool animation)
{
    Q_D(JGLWidget);
    d->trackBall->setOffset(value, animation);
}

/**
 * @brief JGLWidget::depth
 * @return
 */
qreal JGLWidget::depth() const
{
    Q_D(const JGLWidget);
    return d->depth;
}

/**
 * @brief JGLWidget::setDepth
 * @param value
 * @param animation
 */
void JGLWidget::setDepth(qreal value, bool animation)
{
    Q_D(JGLWidget);
    if (value != d->depth) {
        if (animation) {
            d->animationDepth->restart(d->depth, value);
        } else {
            d->depth = value;
            d->wheelDelta = JGLWidgetPrivate::depthToWheel(d->depth);
            Q_EMIT depthChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLWidget::viewportColor
 * @return
 */
QColor JGLWidget::viewportColor() const
{
    Q_D(const JGLWidget);
    return d->viewportColor;
}

/**
 * @brief JGLWidget::defaultCenter
 * @return
 */
QVector3D JGLWidget::defaultCenter() const
{
    Q_D(const JGLWidget);
    return d->trackBall->defaultCenter();
}

/**
 * @brief JGLWidget::setViewportColor
 * @param value
 * @param animation
 */
void JGLWidget::setViewportColor(const QColor &value, bool animation)
{
    Q_D(JGLWidget);
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
 * @brief JGLWidget::setDefaultCenter
 * @param value
 * @param animation
 */
void JGLWidget::setDefaultCenter(const QVector3D &value, bool animation)
{
    Q_D(JGLWidget);
    d->trackBall->setDefaultCenter(value, animation);
}

/**
 * @brief JGLWidget::reset
 * @param animation
 */
void JGLWidget::reset(bool animation)
{
    resetScale(animation);
    resetOffset(animation);
    resetCenter(animation);
    resetDepth(animation);
    resetRotation(animation);
}

/**
 * @brief JGLWidget::resetScale
 * @param animation
 */
void JGLWidget::resetScale(bool animation)
{
    setScale(JGLWidgetPrivate::defaultScale(), animation);
}

/**
 * @brief JGLWidget::resetCenter
 * @param animation
 */
void JGLWidget::resetCenter(bool animation)
{
    Q_D(JGLWidget);
    setCenter(d->trackBall->defaultCenter(), animation);
}

/**
 * @brief JGLWidget::resetOffset
 * @param animation
 */
void JGLWidget::resetOffset(bool animation)
{
    setOffset(JGLTrackBall::defaultOffset(), animation);
}

/**
 * @brief JGLWidget::resetDepth
 * @param animation
 */
void JGLWidget::resetDepth(bool animation)
{
    setDepth(JGLWidgetPrivate::defaultDepth(), animation);
}

/**
 * @brief JGLWidget::resetRotation
 * @param animation
 */
void JGLWidget::resetRotation(bool animation)
{
    Q_D(JGLWidget);
    d->trackBall->setRotation(JGLWidgetPrivate::defaultRotation(), animation);
}

/**
 * @brief JGLWidget::indicatorDrawable
 * @return
 */
bool JGLWidget::indicatorDrawable() const
{
    Q_D(const JGLWidget);
    return d->indicatorDrawable;
}

/**
 * @brief JGLWidget::setIndicatorDrawable
 * @param value
 */
void JGLWidget::setIndicatorDrawable(bool value)
{
    Q_D(JGLWidget);
    if (value != d->indicatorDrawable) {
        d->indicatorDrawable = value;
        update();
    }
}

/**
 * @brief JGLWidget::jindicator
 * @return
 */
/*
QGraphicsItem *JGLWidget::jindicator() const
{
    Q_D(const JGLWidget);
    return d->jindicator;
}
*/
/**
 * @brief JGLWidget::objects
 * @return
 */
const QList<JGLObject *> &JGLWidget::objects() const
{
    Q_D(const JGLWidget);
    return d->objects;
}

/**
 * @brief JGLWidget::registerObjects
 * @return
 */
const QMap<unsigned int, JGLObject *> &JGLWidget::registerObjects() const
{
    Q_D(const JGLWidget);
    return d->registerObjects;
}

/**
 * @brief JGLWidget::initializeGL
 */
void JGLWidget::initializeGL()
{
    makeCurrent();
}

/**
 * @brief JGLWidget::paintGL
 */
void JGLWidget::paintGL()
{
    Q_D(JGLWidget);

    JGLPainter painter3D(0, this);
    d->beginPaint(&painter3D);
    earlyPaintGL(&painter3D);
    paintGL(&painter3D);
    d->endPaint(&painter3D);
    makeCurrent();
}

/**
 * @brief JGLWidget::resizeGL
 * @param w
 * @param h
 */
void JGLWidget::resizeGL(int w, int h)
{
    Q_D(JGLWidget);
#if defined(Q_OS_MAC) && (QT_VERSION >= 0x050000)
    glViewport(0, 0, (GLsizei)w * 2, (GLsizei)h * 2);
#else
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
#endif
    d->aspect = (GLdouble)w / (GLdouble)h;
}

/**
 * @brief JGLWidget::earlyPaintGL
 * @param painter
 */
void JGLWidget::earlyPaintGL(JGLPainter *painter)
{
    Q_UNUSED(painter);
    Q_D(JGLWidget);
    glClearColor(d->viewportColor.redF(), d->viewportColor.greenF(),
                 d->viewportColor.blueF(), d->viewportColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief JGLWidget::mousePressEvent
 * @param e
 */
void JGLWidget::mousePressEvent(QMouseEvent *e)
{
    QGLWidget::mousePressEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLWidget);
    if (e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
        d->trackBall->push(JGLFunction::pixelPosToViewPos(rect(), e->pos()));
#ifndef Qt_NO_CURSOR
        QApplication::setOverrideCursor(Qt::ClosedHandCursor);
#endif
    }

    JGLObject *object = 0;
    if (!d->panning && (d->options & JGLWidget::ObjectPicking)) {
        object = objectForPoint(e->pos());
    }

    if (d->pressedObject) {
        // Send the press event to the pressed object. Use a position
        // of (0, 0) if the mouse is still within the pressed object,
        // or (-1, -1) if the mouse is no longer within the pressed object.
        QMouseEvent event(QEvent::MouseButtonPress,
                          (d->pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                          e->globalPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(d->pressedObject, &event);
    } else if (object) {
        // Record the object that was pressed and forward the event.
        d->pressedObject = object;
        d->enteredObject = 0;
        d->pressedButton = e->button();

        // Send a mouse press event for (0, 0).
        QMouseEvent event(QEvent::MouseButtonPress, QPoint(0, 0),
                          e->globalPos(), e->button(), e->buttons(), e->modifiers());
        QCoreApplication::sendEvent(object, &event);
    } else if ((d->options & JGLWidget::CameraNavigation) &&
               e->button() == Qt::LeftButton) {
        d->panning = true;
        d->lastPan = d->startPan = e->pos();
        d->panModifiers = e->modifiers();
    }
}

/**
 * @brief JGLWidget::mouseReleaseEvent
 * @param e
 */
void JGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QGLWidget::mouseReleaseEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLWidget);
    if (e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
        d->trackBall->release(JGLFunction::pixelPosToViewPos(rect(), e->pos()));
    }

    if (d->panning && e->button() == Qt::LeftButton) {
        d->panning = false;
    }
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    if (d->pressedObject) {
        // Notify the previously pressed object about the release.
        JGLObject *object = objectForPoint(e->pos());
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
                              e->globalPos(), e->button(), e->buttons(), e->modifiers());
            QCoreApplication::sendEvent(pressedObject, &event);

            // Send enter and leave events if necessary.
            if (object != pressedObject) {
                JGLWidgetPrivate::sendLeaveEvent(pressedObject);
                if (object) {
                    JGLWidgetPrivate::sendEnterEvent(object);
                }
            }
        } else {
            // Some other button than the original released.
            // Forward the event to the pressed object.
            QMouseEvent event(QEvent::MouseButtonRelease,
                              (pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                              e->globalPos(), e->button(), e->buttons(), e->modifiers());
            QCoreApplication::sendEvent(pressedObject, &event);
        }
    }
}

/**
 * @brief JGLWidget::mouseMoveEvent
 * @param e
 */
void JGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    QGLWidget::mouseMoveEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLWidget);
    if (e->buttons() & Qt::LeftButton) {
        d->lastPan = e->pos();
        d->trackBall->move(JGLFunction::pixelPosToViewPos(rect(), e->pos()));
    }
    if (e->buttons() & Qt::RightButton) {
        d->trackBall->pan(JGLFunction::pixelPosToViewPos(rect(), e->pos()));
    }

    if (d->panning) {
        QPointF delta = e->pos() - d->startPan;
        if (e->modifiers() == d->panModifiers) {
            //
        } else {
            d->startPan = d->lastPan;
            delta = e->pos() - d->startPan;
            d->panModifiers = e->modifiers();
        }

        d->lastPan = e->pos();
    } else if (d->options & JGLWidget::ObjectPicking) {
        if (e->buttons() & Qt::LeftButton) {    // moving
            d->pressedObject = 0;   // cannot select when drag the track-ball
        } else {
            JGLObject *object = objectForPoint(e->pos());
            if (d->pressedObject) {
                // Send the move event to the pressed object. Use a position
                // (0, 0) if the mouse is still within the pressed object.
                // (-1, -1) if the mouse is no longer within the pressed object.
                QMouseEvent event(QEvent::MouseMove,
                                  (d->pressedObject == object) ? QPoint(0, 0) : QPoint(-1, -1),
                                  e->globalPos(), e->button(), e->buttons(), e->modifiers());
                QCoreApplication::sendEvent(d->pressedObject, &event);
            } else if (object) {
                if (object != d->enteredObject) {
                    if (d->enteredObject) {
                        JGLWidgetPrivate::sendLeaveEvent(d->enteredObject);
                    }
                    d->enteredObject = object;
                    JGLWidgetPrivate::sendEnterEvent(d->enteredObject);
                }
                QMouseEvent event(QEvent::MouseMove, QPoint(0, 0),
                                  e->globalPos(), e->button(), e->buttons(), e->modifiers());
                QCoreApplication::sendEvent(object, &event);
            } else if (d->enteredObject) {
                JGLWidgetPrivate::sendLeaveEvent(d->enteredObject);
                d->enteredObject = 0;
            }
        }
    }
}

/**
 * @brief JGLWidget::mouseDoubleClickEvent
 * @param e
 */
void JGLWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    QGLWidget::mouseDoubleClickEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLWidget);
    if (d->options & JGLWidget::ObjectPicking) {
        JGLObject *object = objectForPoint(e->pos());
        if (object) {
            // Simulate a double click event for (0, 0)
            QMouseEvent event(QEvent::MouseButtonDblClick, QPoint(0, 0),
                              e->globalPos(), e->button(), e->buttons(), e->modifiers());
            QCoreApplication::sendEvent(object, &event);
        } else {
            reset(true);
            Q_EMIT doubleClicked();
        }
    }
}

/**
 * @brief JGLWidget::wheelEvent
 * @param e
 */
void JGLWidget::wheelEvent(QWheelEvent *e)
{
    QGLWidget::wheelEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLWidget);
    if (d->options & JGLWidget::CameraNavigation) {
        if (e->modifiers() & Qt::ShiftModifier) {
            d->scale.setY(qMax<qreal>(0, d->scale.y() + e->delta() / 9600.0));
        } else {
            d->wheel(e->delta());
        }
        update();
    }
}

/**
 * @brief JGLWidget::enterEvent
 * @param e
 */
void JGLWidget::enterEvent(QEvent *e)
{
    QGLWidget::enterEvent(e);
}

/**
 * @brief JGLWidget::leaveEvent
 * @param e
 */
void JGLWidget::leaveEvent(QEvent *e)
{
    QGLWidget::leaveEvent(e);
}

/**
 * @brief JGLWidget::keyPressEvent
 * @param e
 */
void JGLWidget::keyPressEvent(QKeyEvent *e)
{
    QGLWidget::keyPressEvent(e);
    if (e->isAccepted()) {
        return;
    }

    Q_D(JGLWidget);
    if (d->options & JGLWidget::CameraNavigation) {
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
