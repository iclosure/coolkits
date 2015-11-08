#include "precomp.h"
#include "jplot3d_shape.h"
#include "jglscale.h"
#include "jplot3d_coord.h"
#include "jplot3d_scene.h"
#include "jplot3d_glwidget.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JShapePrivate -

/**
 * @brief The JShapePrivate class
 */
class JShapePrivate
{
    J_DECLARE_PUBLIC(JShape)
public:
    JShapePrivate(JShape *parent)
        : q_ptr(parent)
        , jobject(0)
        , jscene(0)
        , jwidget(0)
        , jscale(0)
        , pickedShape(0)
    {

    }

    void bind(JShapeItem *item);
    void unbind(JShapeItem *item);

    void addShape(JShapeItem *item);
    void removeShape(JShapeItem *item);
    void clearShape();

private:
    void init();

private:
    QObject *jobject;
    JScene *jscene;
    JWidget *jwidget;
    JGLScale *jscale;
    QMap<unsigned int, JShapeItem *> shapes;
    JShapeItem *pickedShape;

    GLuint gllists;
};

/**
 * @brief JShapePrivate::init
 */
void JShapePrivate::init()
{
    Q_Q(JShape);
    q->setObjectName("JShape");

    //TEST
    qsrand(QDateTime::currentDateTime().toTime_t());
}

/**
 * @brief JShapePrivate::bind
 * @param item
 */
void JShapePrivate::bind(JShapeItem *item)
{
    Q_Q(JShape);
    if (jscene) {
        jscene->registerObject(item->objectId(), item);
        item->setViewport(jscene->viewport());
    } else {
        jwidget->registerObject(item->objectId(), item);
        item->setViewport(jwidget);
    }
    QObject::connect(item, SIGNAL(repaint()),
                     jobject, SLOT(update()));
    QObject::connect(jscale, SIGNAL(offsetVectorChanged(QVector3D)),
                     item, SLOT(setOffsetVector(QVector3D)));
    QObject::connect(jscale, SIGNAL(scaleVectorChanged(QVector3D)),
                     item, SLOT(setScaleVector(QVector3D)));
    QObject::connect(q, SIGNAL(scaleVectorChanged(QVector3D)),
                     item, SLOT(setScaleVector(QVector3D)));
    QObject::connect(q, SIGNAL(focusableChanged(bool)),
                     item, SLOT(setFocusable(bool)));
    QObject::connect(item, SIGNAL(pressed()),
                     q, SLOT(objectPressed()));
    QObject::connect(item, SIGNAL(clicked()),
                     q, SLOT(objectClicked()));
    QObject::connect(item, SIGNAL(doubleClicked()),
                     q, SLOT(objectDoubleClicked()));
    QObject::connect(item, SIGNAL(entered()),
                     q, SLOT(objectEntered()));
    QObject::connect(item, SIGNAL(left()),
                     q, SLOT(objectLeft()));
}

/**
 * @brief JShapePrivate::unbind
 * @param item
 */
void JShapePrivate::unbind(JShapeItem *item)
{
    Q_Q(JShape);
    if (jscene) {
        jscene->deregisterObject(item->objectId());
    } else {
        jwidget->deregisterObject(item->objectId());
    }
    QObject::disconnect(item, SIGNAL(repaint()),
                        jobject, SLOT(update()));
    QObject::disconnect(jscale, SIGNAL(offsetVectorChanged(QVector3D)),
                        item, SLOT(setOffsetVector(QVector3D)));
    QObject::disconnect(jscale, SIGNAL(scaleVectorChanged(QVector3D)),
                        item, SLOT(setScaleVector(QVector3D)));
    QObject::disconnect(q, SIGNAL(scaleVectorChanged(QVector3D)),
                        item, SLOT(setScaleVector(QVector3D)));
    QObject::disconnect(q, SIGNAL(focusableChanged(bool)),
                        item, SLOT(setFocusable(bool)));
    QObject::disconnect(item, SIGNAL(pressed()),
                        q, SLOT(objectPressed()));
    QObject::disconnect(item, SIGNAL(clicked()),
                        q, SLOT(objectClicked()));
    QObject::disconnect(item, SIGNAL(doubleClicked()),
                        q, SLOT(objectDoubleClicked()));
    QObject::disconnect(item, SIGNAL(entered()),
                        q, SLOT(objectEntered()));
    QObject::disconnect(item, SIGNAL(left()),
                        q, SLOT(objectLeft()));
}

/**
 * @brief JShapePrivate::addShape
 * @param item
 */
void JShapePrivate::addShape(JShapeItem *item)
{
    bind(item);
    shapes[item->objectId()] = item;
    if (jscale->box().isNull()) {
        jscale->setRange(item->box());
    } else {
        jscale->setRange(jscale->box() | item->box());
    }
    item->setOffsetVector(-jscale->box().minVector());
}

/**
 * @brief JShapePrivate::removeShape
 * @param item
 */
void JShapePrivate::removeShape(JShapeItem *item)
{
    unbind(item);
    shapes.remove(item->objectId());
    item->deleteLater();
    //
    JRect3D range;
    QMapIterator<unsigned int, JShapeItem *> iter(shapes);
    while (iter.hasNext()) {
        iter.next();
        range |= iter.value()->box();
    }
    jscale->setRange(range);
}

/**
 * @brief JShapePrivate::clearShape
 */
void JShapePrivate::clearShape()
{
    QMapIterator<unsigned int, JShapeItem *> iter(shapes);
    while (iter.hasNext()) {
        iter.next();
        JShapeItem *item = iter.value();
        unbind(item);
        item->deleteLater();
    }
    shapes.clear();
    jscale->resetRange();
}

J3D_END_NAMESPACE

// - class JShape -

/**
 * @brief JShape::JShape
 * @param parent
 */
JShape::JShape(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JShapePrivate(this))
{
    Q_D(JShape);
    d->init();
}

/**
 * @brief JShape::~JShape
 */
JShape::~JShape()
{
    delete d_ptr;
}

/**
 * @brief JShape::addPoint
 * @param identity
 * @param pos
 * @param color
 * @param size
 */
void JShape::addPoint(const QString &identity, const QVector3D &pos, const QColor &color, qreal size)
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }

    JShapeItem *item = new JShapeItem(identity, color, this);
    item->setFocusable(focusable());
    item->setPickable(pickable());
    item->setScaleVector(scaleVector());
    item->setPoint(pos, size);
    d->addShape(item);
}

/**
 * @brief JShape::addLine
 * @param identity
 * @param minVector
 * @param maxVector
 * @param color
 * @param width
 */
void JShape::addLine(const QString &identity, const QVector3D &minVector,
                     const QVector3D &maxVector, const QColor &color, qreal width)
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }

    JShapeItem *item = new JShapeItem(identity, color, this);
    item->setFocusable(focusable());
    item->setPickable(pickable());
    item->setScaleVector(scaleVector());
    item->setLine(minVector, maxVector, width);
    d->addShape(item);
}

/**
 * @brief JShape::addBox
 * @param identity
 * @param minVector
 * @param maxVector
 * @param color
 */
void JShape::addBox(const QString &identity, const QVector3D &minVector,
                    const QVector3D &maxVector, const QColor &color)
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }

    JShapeItem *item = new JShapeItem(identity, color, this);
    item->setFocusable(focusable());
    item->setPickable(pickable());
    item->setScaleVector(scaleVector());
    item->setBox(minVector, maxVector);
    d->addShape(item);
}

/**
 * @brief JShape::addCircle
 * @param identity
 * @param pos
 * @param radius
 * @param color
 * @param slices
 * @param stacks
 */
void JShape::addCircle(const QString &identity, const QVector3D &pos, qreal radius,
                       const QColor &color, int slices, int stacks)
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }

    JShapeItem *item = new JShapeItem(identity, color, this);
    item->setFocusable(focusable());
    item->setPickable(pickable());
    item->setScaleVector(scaleVector());
    item->setCircle(pos, radius, slices, stacks);
    d->addShape(item);
}

/**
 * @brief JShape::setEllipse
 * @param identity
 * @param box
 * @param color
 * @param slices
 * @param stacks
 */
void JShape::setEllipse(const QString &identity, const JRect3D &box,
                       const QColor &color, int slices, int stacks)
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }

    JShapeItem *item = new JShapeItem(identity, color, this);
    item->setFocusable(focusable());
    item->setPickable(pickable());
    item->setScaleVector(scaleVector());
    item->setEllipse(box, slices, stacks);
    d->addShape(item);
}

/**
 * @brief JShape::findShape
 * @param objectId
 * @return
 */
JShapeItem *JShape::findShape(unsigned int objectId) const
{
    Q_D(const JShape);
    if (d->shapes.contains(objectId)) {
        return d->shapes[objectId];
    } else {
        return 0;
    }

    return 0;
}

/**
 * @brief JShape::findShape
 * @param identity
 * @return
 */
JShapeItem *JShape::findShape(const QString &identity) const
{
    Q_D(const JShape);
    QMapIterator<unsigned int, JShapeItem *> iter(d->shapes);
    while (iter.hasNext()) {
        iter.next();
        JShapeItem *object = iter.value();
        if (object->identity() == identity) {
            return object;
        }
    }

    return 0;
}

/**
 * @brief JShape::removeShape
 * @param objectId
 */
void JShape::removeShape(unsigned int objectId)
{
    removeShape(findShape(objectId));
}

/**
 * @brief JShape::removeShape
 * @param identity
 */
void JShape::removeShape(const QString &identity)
{
    removeShape(findShape(identity));
}

/**
 * @brief JShape::removeShape
 * @param item
 */
void JShape::removeShape(JShapeItem *item)
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }
    d->removeShape(item);
}

/**
 * @brief JShape::clearShape
 */
void JShape::clearShape()
{
    Q_D(JShape);
    if (!d->jobject) {
        return;
    }
    d->clearShape();
}

/**
 * @brief JShape::currentShape
 * @return
 */
JShapeItem *JShape::currentShape() const
{
    Q_D(const JShape);
    return d->pickedShape;
}

/**
 * @brief JShape::setCurrentShape
 * @param id
 */
void JShape::setCurrentShape(unsigned int id)
{
    if (pickable()) {
        setCurrentShape(findShape(id));
    }
}

/**
 * @brief JShape::setCurrentShape
 * @param identity
 */
void JShape::setCurrentShape(const QString &identity)
{
    if (pickable()) {
        setCurrentShape(findShape(identity));
    }
}

/**
 * @brief JShape::setCurrentShape
 * @param item
 */
void JShape::setCurrentShape(JShapeItem *item)
{
    if (item == 0) {
        return;
    }

    Q_D(JShape);
    if (pickable() && item != d->pickedShape) {
        QMutableMapIterator<unsigned int, JShapeItem *> iter(d->shapes);
        while (iter.hasNext()) {
            iter.next();
            if (iter.value() != item) {
                iter.value()->setPicking(false);
            }
        }

        if (item->focusable()) {
            if (d->jscene) {
                d->jscene->setCenter(item->scaledBox().center(), true);
            } else {
                d->jwidget->setCenter(item->scaledBox().center(), true);
            }
        }

        item->setPicking(true);
        d->pickedShape = item;
        Q_EMIT currentShapeChanged(item->identity());
    }
}

/**
 * @brief JShape::initialize
 * @param scene
 */
void JShape::initialize(JGLScene *scene)
{
    Q_UNUSED(scene);
}

/**
 * @brief JShape::draw
 * @param painter
 */
void JShape::draw(JGLPainter *painter)
{
    Q_D(JShape);
    QMapIterator<unsigned int, JShapeItem *> iter(d->shapes);
    while (iter.hasNext()) {
        iter.next();
        iter.value()->draw(painter);
    }
}

/**
 * @brief JShape::attach
 * @param object
 */
void JShape::attach(QObject *object)
{
    Q_D(JShape);
    if (d->jobject != 0) {
        return;
    }
    if (object->inherits("J3D::JScene")) {
        d->jscene = qobject_cast<JScene *>(object);
        d->jscale = d->jscene->jscale();
    } else if (object->inherits("J3D::JWidget")) {
        d->jwidget = qobject_cast<JWidget *>(object);
        d->jscale = d->jwidget->jscale();
    } else {
        return;
    }
    d->jobject = object;
    QMapIterator<unsigned int, JShapeItem *> iter(d->shapes);
    while (iter.hasNext()) {
        iter.next();
        d->bind(iter.value());
    }
    //
    QObject::connect(d->jobject, SIGNAL(doubleClicked()),
                     this, SLOT(sceneDoubleClicked()));
    QObject::connect(d->jscale, SIGNAL(scaleVectorChanged(QVector3D)),
                     this, SLOT(setScaleVector(QVector3D)));
    if (d->jscene) {
        d->jscene->addObject(this);
    } else {
        d->jwidget->addObject(this);
    }
}

/**
 * @brief JShape::detach
 */
void JShape::detach()
{
    Q_D(JShape);
    if (d->jobject == 0) {
        return;
    }

    QMapIterator<unsigned int, JShapeItem *> iter(d->shapes);
    while (iter.hasNext()) {
        iter.next();
        d->unbind(iter.value());
    }
    //
    QObject::disconnect(d->jobject, SIGNAL(doubleClicked()),
                        this, SLOT(sceneDoubleClicked()));
    QObject::disconnect(d->jscale, SIGNAL(scaleVectorChanged(QVector3D)),
                        this, SLOT(setScaleVector(QVector3D)));
    if (d->jscene) {
        d->jscene->removeObject(this);
    } else {
        d->jwidget->removeObject(this);
    }
    d->jobject = 0;
    d->jscene = 0;
    d->jwidget = 0;
    d->jscale = 0;
}

/**
 * @brief JShape::sceneDoubleClicked
 */
void JShape::sceneDoubleClicked()
{
    Q_D(JShape);
    if (pickable()) {
        glDisable(GL_BLEND);
        QMutableMapIterator<unsigned int, JShapeItem *> iter(d->shapes);
        while (iter.hasNext()) {
            iter.next();
            iter.value()->setPicking(false);
        }
        glEnable(GL_BLEND);
        d->pickedShape = 0;
    }
}

/**
 * @brief JShape::objectPressed
 */
void JShape::objectPressed()
{

}

/**
 * @brief JShape::objectClicked
 */
void JShape::objectClicked()
{
    if (pickable()) {
        JShapeItem *item = qobject_cast<JShapeItem *>(sender());
        setCurrentShape(item);
    }
}

/**
 * @brief JShape::objectReleased
 */
void JShape::objectReleased()
{

}

/**
 * @brief JShape::objectDoubleClicked
 */
void JShape::objectDoubleClicked()
{

}

/**
 * @brief JShape::objectEntered
 */
void JShape::objectEntered()
{

}

/**
 * @brief JShape::objectLeft
 */
void JShape::objectLeft()
{

}

QT_END_NAMESPACE
