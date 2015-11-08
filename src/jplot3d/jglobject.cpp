#include "precomp.h"
#include "jglobject.h"
#include "jglpainter.h"
#include "jglanimation.h"
#include "jglscene.h"
#include <QGLWidget>

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JObjectPrivate -

/**
 * @brief The JGLObjectPrivate class
 */
class J3D_EXPORT JGLObjectPrivate
{
    J_DECLARE_PUBLIC(JGLObject)
public:
    JGLObjectPrivate(JGLObject *parent)
        : q_ptr(parent)
        , viewport(0)
        , objectId(generatorObjectId())
        , identity("")
        , pos(0.0f, 0.0f, 0.0f)
        , color(255, 255, 255, 255)
        , scale(1.0f)
        , rotationAngle(0.0f)
        , rotationVector(0.0f, 0.0f, 0.0f)
        , focusable(false)
        , pickable(false)
        , picking(false)
        , box(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
        , offsetVector(0.0f, 0.0f, 0.0f)
        , scaleVector(1.0f, 1.0f, 1.0f)
        , glListId(0)
    {

    }

    /**
     * @brief JGLObject::generatorObjectId
     * @return
     */
    unsigned int generatorObjectId()
    {
        return ++indexOfObjectId;
    }

private:
    void init();

private:
    QGLWidget *viewport;
    unsigned int objectId;
    QString identity;
    QVector3D pos;
    QColor color;
    qreal scale;
    qreal rotationAngle;
    QVector3D rotationVector;
    bool focusable;
    bool pickable;
    bool picking;
    JRect3D box;
    QVector3D offsetVector;
    QVector3D scaleVector;

    unsigned int glListId;
    static unsigned int indexOfObjectId;

    JPropertyAnimation *animationPos;
    JPropertyAnimation *animationColor;
    JPropertyAnimation *animationScale;
    JPropertyAnimation *animationRotationAngle;
    JPropertyAnimation *animationRotationVector;
    JPropertyAnimation *animationOffsetVector;
    JPropertyAnimation *animationScaleVector;
};

/**
 * @brief JGLObjectPrivate::indexOfObjectId
 */
unsigned int JGLObjectPrivate::indexOfObjectId = 0;

/**
 * @brief JGLObjectPrivate::init
 */
void JGLObjectPrivate::init()
{
    Q_Q(JGLObject);
    animationPos = new JPropertyAnimation(q, "pos", q);
    animationColor = new JPropertyAnimation(q, "color", q);
    animationScale = new JPropertyAnimation(q, "scale", q);
    animationRotationAngle = new JPropertyAnimation(q, "rotationAngle", q);
    animationRotationVector = new JPropertyAnimation(q, "rotationVector", q);
    animationOffsetVector = new JPropertyAnimation(q, "offsetVector", q);
    animationScaleVector = new JPropertyAnimation(q, "scaleVector", q);
}

J3D_END_NAMESPACE

// - class JGLObject

/**
 * @brief JGLObject::JGLObject
 * @param parent
 */
JGLObject::JGLObject(QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLObjectPrivate(this))
{
    Q_D(JGLObject);
    d->init();
}

/**
 * @brief JGLObject::JGLObject
 * @param identity
 * @param parent
 */
JGLObject::JGLObject(const QString &identity, QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLObjectPrivate(this))
{
    Q_D(JGLObject);
    d->init();
    d->identity = identity;
}

/**
 * @brief JGLObject::JGLObject
 * @param identity
 * @param color
 * @param parent
 */
JGLObject::JGLObject(const QString &identity, const QColor &color, QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLObjectPrivate(this))
{
    Q_D(JGLObject);
    d->init();
    d->identity = identity;
    d->color = color;
}

/**
 * @brief JGLObject::JGLObject
 * @param identity
 * @param color
 * @param pos
 * @param parent
 */
JGLObject::JGLObject(const QString &identity, const QColor &color, const QVector3D &pos, QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLObjectPrivate(this))
{
    Q_D(JGLObject);
    d->init();
    d->identity = identity;
    d->color = color;
    d->pos = pos;
}

/**
 * @brief JGLObject::~JGLObject
 */
JGLObject::~JGLObject()
{
    setDirty();
    delete d_ptr;
}

/**
 * @brief JGLObject::objectId
 * @return
 */
unsigned int JGLObject::objectId() const
{
    Q_D(const JGLObject);
    return d->objectId;
}

/**
 * @brief JGLObject::identity
 * @return
 */
QString JGLObject::identity() const
{
    Q_D(const JGLObject);
    return d->identity;
}

/**
 * @brief JGLObject::setIdentity
 * @param value
 */
void JGLObject::setIdentity(const QString &value)
{
    Q_D(JGLObject);
    if (value != d->identity) {
        d->identity = value;
        Q_EMIT identityChanged(value);
        update();
    }
}

/**
 * @brief JGLObject::pos
 * @return
 */
QVector3D JGLObject::pos() const
{
    Q_D(const JGLObject);
    return d->pos;
}

/**
 * @brief JGLObject::setPos
 * @param value
 * @param animation
 */
void JGLObject::setPos(const QVector3D &value, bool animation)
{
    Q_D(JGLObject);
    if (value != d->pos) {
        if (animation) {
            d->animationPos->restart(d->pos, value);
        } else {
            d->pos = value;
            Q_EMIT posChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLObject::color
 * @return
 */
QColor JGLObject::color() const
{
    Q_D(const JGLObject);
    return d->color;
}

/**
 * @brief JGLObject::setColor
 * @param value
 * @param animation
 */
void JGLObject::setColor(const QColor &value, bool animation)
{
    Q_D(JGLObject);
    if (value != d->color) {
        if (animation) {
            d->animationColor->restart(d->color, value);
        } else {
            d->color = value;
            Q_EMIT colorChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLObject::scale
 * @return
 */
qreal JGLObject::scale() const
{
    Q_D(const JGLObject);
    return d->scale;
}

/**
 * @brief JGLObject::setScale
 * @param value
 * @param animation
 */
void JGLObject::setScale(qreal value, bool animation)
{
    Q_D(JGLObject);
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
 * @brief JGLObject::rotationAngle
 * @return
 */
qreal JGLObject::rotationAngle() const
{
    Q_D(const JGLObject);
    return d->rotationAngle;
}

/**
 * @brief JGLObject::setRotationAngle
 * @param value
 * @param animation
 */
void JGLObject::setRotationAngle(qreal value, bool animation)
{
    Q_D(JGLObject);
    if (value != d->rotationAngle) {
        if (animation) {
            d->animationRotationAngle->restart(d->rotationAngle, value);
        } else {
            d->rotationAngle = value;
            Q_EMIT rotationAngleChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLObject::rotationVector
 * @return
 */
QVector3D JGLObject::rotationVector() const
{
    Q_D(const JGLObject);
    return d->rotationVector;
}

/**
 * @brief JGLObject::setRotationVector
 * @param value
 * @param animation
 */
void JGLObject::setRotationVector(const QVector3D &value, bool animation)
{
    Q_D(JGLObject);
    if (value != d->rotationVector) {
        if (animation) {
            d->animationRotationVector->restart(d->rotationVector, value);
        } else {
            d->rotationVector = value;
            Q_EMIT rotationVectorChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLObject::focusable
 * @return
 */
bool JGLObject::focusable() const
{
    Q_D(const JGLObject);
    return d->focusable;
}

/**
 * @brief JGLObject::setFocusable
 * @param value
 */
void JGLObject::setFocusable(bool value)
{
    Q_D(JGLObject);
    if (value != d->focusable) {
        d->focusable = value;
        Q_EMIT focusableChanged(value);
        update();
    }
}

/**
 * @brief JGLObject::pickable
 * @return
 */
bool JGLObject::pickable() const
{
    Q_D(const JGLObject);
    return d->pickable;
}

/**
 * @brief JGLObject::setPickable
 * @param value
 */
void JGLObject::setPickable(bool value)
{
    Q_D(JGLObject);
    if (value != d->pickable) {
        d->pickable = value;
        Q_EMIT pickableChanged(value);
        update();
    }
}

/**
 * @brief JGLObject::picking
 * @return
 */
bool JGLObject::picking() const
{
    Q_D(const JGLObject);
    return d->picking;
}

/**
 * @brief JGLObject::setPicking
 * @param value
 */
void JGLObject::setPicking(bool value)
{
    Q_D(JGLObject);
    if (value != d->picking) {
        d->picking = value;
        Q_EMIT pickingChanged(value);
        update();
    }
}

/**
 * @brief JGLObject::setBox
 * @param value
 */
void JGLObject::setBox(const JRect3D &value)
{
    Q_D(JGLObject);
    if (value != d->box) {
        d->box = value;
        Q_EMIT boxChanged(value);
        update();
    }
}

/**
 * @brief JGLObject::setOffsetVector
 * @param value
 * @param animation
 */
void JGLObject::setOffsetVector(const QVector3D &value, bool animation)
{
    Q_D(JGLObject);
    if (value != d->offsetVector) {
        if (animation) {
            d->animationOffsetVector->restart(d->offsetVector, value);
        } else {
            d->offsetVector = value;
            Q_EMIT offsetVectorChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLObject::scaleVector
 * @return
 */
QVector3D JGLObject::scaleVector() const
{
    Q_D(const JGLObject);
    return d->scaleVector;
}

/**
 * @brief JGLObject::makeCurrent
 * @return
 */
bool JGLObject::makeCurrent()
{
    Q_D(JGLObject);
    if (d->viewport) {
        d->viewport->makeCurrent();
        return true;
    } else {
        return false;
    }
}

/**
 * @brief JGLObject::doneCurrent
 * @return
 */
bool JGLObject::doneCurrent()
{
    Q_D(JGLObject);
    if (d->viewport) {
        d->viewport->doneCurrent();
        return true;
    } else {
        return false;
    }
}

/**
 * @brief JGLObject::viewport
 * @return
 */
QGLWidget *JGLObject::viewport() const
{
    Q_D(const JGLObject);
    return d->viewport;
}

/**
 * @brief JGLObject::setViewport
 * @param viewport
 */
void JGLObject::setViewport(QGLWidget *viewport)
{
    Q_D(JGLObject);
    if (viewport != d->viewport) {
        d->viewport = viewport;
        update();
    }
}

/**
 * @brief JGLObject::context
 * @return
 */
QGLContext *JGLObject::context() const
{
    Q_D(const JGLObject);
    if (d->viewport) {
        return const_cast<QGLContext *>(d->viewport->context());
    } else {
        return 0;
    }
}

/**
 * @brief JGLObject::beginContext
 */
bool JGLObject::beginContext()
{
    return makeCurrent();
}

/**
 * @brief JGLObject::doneContext
 */
bool JGLObject::doneContext()
{
    return doneCurrent();
}

/**
 * @brief JGLObject::initialize
 * @param scene
 */
void JGLObject::initialize(JGLScene *scene)
{
    Q_UNUSED(scene);
}

/**
 * @brief JGLObject::setScaleVector
 * @param value
 * @param animation
 */
void JGLObject::setScaleVector(const QVector3D &value, bool animation)
{
    Q_D(JGLObject);
    if (value != d->scaleVector) {
        if (animation) {
            d->animationScaleVector->restart(d->scaleVector, value);
        } else {
            d->scaleVector = value;
            Q_EMIT scaleVectorChanged(value);
            update();
        }
    }
}

/**
 * @brief JGLObject::draw
 * @param painter
 */
void JGLObject::draw(JGLPainter *painter)
{
    Q_D(JGLObject);
    if (d->glListId != 0) {
        if (d->pickable && painter->picking()) {
            glInitNames();
            glPushName((GLuint)d->objectId);
            glCallList(d->glListId);
            glPopName();
        } else {
            glCallList(d->glListId);
        }
    }
}

/**
 * @brief JGLObject::isDirty
 * @return
 */
bool JGLObject::isDirty() const
{
    Q_D(const JGLObject);
    return d->glListId == 0;
}

/**
 * @brief JGLObject::setDirty
 */
void JGLObject::setDirty()
{
    Q_D(JGLObject);
    if (d->glListId != 0) {
        glDeleteLists(d->glListId, 1);
        d->glListId = 0;
    }
}

/**
 * @brief JGLObject::box
 * @return
 */
JRect3D JGLObject::box() const
{
    Q_D(const JGLObject);
    return d->box;
}

/**
 * @brief JGLObject::scaledBox
 * @return
 */
JRect3D JGLObject::scaledBox() const
{
    Q_D(const JGLObject);
    return (d->offsetVector + d->box) * d->scaleVector;
}

/**
 * @brief JGLObject::offsetVector
 * @return
 */
QVector3D JGLObject::offsetVector() const
{
    Q_D(const JGLObject);
    return d->offsetVector;
}

/**
 * @brief JGLObject::event
 * @param e
 * @return
 */
bool JGLObject::event(QEvent *e)
{
    Q_D(JGLObject);
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    {
        QMouseEvent *mouseEvent = reinterpret_cast<QMouseEvent *>(e);
        if (mouseEvent->button() == Qt::LeftButton) {
            Q_EMIT pressed();
        }
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        QMouseEvent *mouseEvent = reinterpret_cast<QMouseEvent *>(e);
        if (mouseEvent->button() == Qt::LeftButton) {
            Q_EMIT released();
            if (mouseEvent->x() >= 0) {
                if (d->pickable) {
                    setPicking(true);
                }
                Q_EMIT clicked();
            }
        }
        break;
    }
    case QEvent::MouseButtonDblClick:
    {
        Q_EMIT doubleClicked();
        break;
    }
    case QEvent::Enter:
    {
        Q_EMIT entered();
        break;
    }
    case QEvent::Leave:
    {
        Q_EMIT left();
        break;
    }
    default:
        break;
    }

    return QObject::event(e);
}

void JGLObject::update()
{
    Q_EMIT repaint();
}

/**
 * @brief JGLObject::glListId
 * @return
 */
unsigned int JGLObject::glListId() const
{
    Q_D(const JGLObject);
    return d->glListId;
}

/**
 * @brief JGLObject::setGLListId
 * @param id
 */
void JGLObject::setGLListId(unsigned int id)
{
    Q_D(JGLObject);
    setDirty();
    d->glListId = id;
}

QT_END_NAMESPACE
