#include "precomp.h"
#include "jplot3d_shapeitem.h"
#include "jglpainter.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JShapeItemPrivate -

/**
 * @brief The JShapeItemPrivate class
 */
class JShapeItemPrivate
{
    J_DECLARE_PUBLIC(JShapeItem)
    public:
        JShapeItemPrivate(JShapeItem *parent)
      : q_ptr(parent)
      , focusable(true)
      , highlight(true)
      , shapeType(JShapeItem::NoShape)
    {
        pointSize = 1.f;
        lineWidth = 1.f;
        ellipse.slices = 36;
        ellipse.stacks = 36;
    }

private:
    void init();
    void update();

private:
    bool focusable;
    bool highlight;
    JShapeItem::ShapeType shapeType;
    struct {
        union {
            qreal pointSize;
            qreal lineWidth;
            struct {
                int slices;
                int stacks;
            } ellipse;
        };
    };
};

/**
 * @brief JShapeItemPrivate::init
 */
void JShapeItemPrivate::init()
{
    Q_Q(JShapeItem);
    q->setObjectName("JShapeItem");
}

/**
 * @brief JShapeItemPrivate::update
 */
void JShapeItemPrivate::update()
{
    Q_Q(JShapeItem);
    if (shapeType == JShapeItem::NoShape) {
        return;     // invalid shape
    }

    if (!q->beginContext()) {
        return;
    }

    JRect3D box = q->scaledBox();
    if (!box.isNormalized()) {
        return;     // not empty
    }

    if (q->isDirty()) {
        q->setGLListId(glGenLists(1));
        if (!glIsList(q->glListId())) {
            qErrnoWarning("error");
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    glNewList(q->glListId(), GL_COMPILE);
    glPushMatrix();

    QVector3D vect = q->rotationVector();
    glRotatef(q->rotationAngle(), vect.x(), vect.y(), vect.z());
    QColor color = q->color();
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());

    // auto-scale
    QVector3D pos = box.center();

    switch (shapeType) {
    case JShapeItem::ShapePoint:
    {
        glTranslatef(pos.x(), pos.y(), pos.z());
        glutSolidSphere(0.0015f * pointSize, 36, 36);
        if (q->pickable() && q->picking()) {
            glPushAttrib(GL_DEPTH_BIAS | GL_POLYGON_BIT | GL_LIGHTING_BIT);
            glDisable(GL_DEPTH_BITS);
            glDisable(GL_LIGHTING);
            glPopName();
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.5f);
            glutSolidSphere(0.003f * pointSize, 36, 36);

            glPopMatrix();
            glPushMatrix();
            QVector<QVector3D> vertexes;
            vertexes << QVector3D(box.left(), 0.0f, 0.0f)
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(0.0f, box.floor(), 0.0f)
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(0.0f, 0.0f, box.back())
                     << QVector3D(box.left(), box.floor(), box.back());
            glLineWidth(1.2f);
            glLineStipple(1, 0x3333);
            glColor4f(0.7f, 0.7f, 0.9f, 1.0f);
            glEnable(GL_LINE_STIPPLE);
            glVertexPointer(3, GL_FLOAT, 0, vertexes.data());
            glDrawArrays(GL_LINES, 0, vertexes.count());
            glDisable(GL_LINE_STIPPLE);
            glPushName(q->objectId());
            glPopAttrib();
        }
        break;
    }
    case JShapeItem::ShapeLine:
    {
        glLineWidth(lineWidth);
        glBegin(GL_LINES);
        glNormal3f(box.left(), box.floor(), box.back());
        glVertex3f(box.left(), box.floor(), box.back());
        glNormal3f(box.right(), box.ceil(), box.front());
        glVertex3f(box.right(), box.ceil(), box.front());
        glEnd();
        if (q->pickable() && q->picking()) {
            glPushAttrib(GL_DEPTH_BIAS | GL_POLYGON_BIT | GL_LIGHTING_BIT);
            glDisable(GL_DEPTH_BITS);
            glDisable(GL_LIGHTING);
            glPopName();
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.5f);
            glLineWidth(lineWidth * 4);
            glBegin(GL_LINES);
            glNormal3f(box.left(), box.floor(), box.back());
            glVertex3f(box.left(), box.floor(), box.back());
            glNormal3f(box.right(), box.ceil(), box.front());
            glVertex3f(box.right(), box.ceil(), box.front());
            glEnd();

            glPopMatrix();

            glPushMatrix();
            QVector<QVector3D> vertexes;
            vertexes << QVector3D(box.left(), box.floor(), 0.0f)
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(box.left(), 0.0f, box.back())
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(0.0f, box.floor(), box.back())
                     << QVector3D(box.left(), box.floor(), box.back())
                        //
                     << QVector3D(box.right(), box.ceil(), 0.0f)
                     << QVector3D(box.right(), box.ceil(), box.front())
                     << QVector3D(box.right(), 0.0f, box.front())
                     << QVector3D(box.right(), box.ceil(), box.front())
                     << QVector3D(0.0f, box.ceil(), box.front())
                     << QVector3D(box.right(), box.ceil(), box.front());
            glLineWidth(1.2f);
            glColor4f(0.7f, 0.7f, 0.9f, 1.0f);
            glEnable(GL_LINE_STIPPLE);
            glVertexPointer(3, GL_FLOAT, 0, vertexes.data());
            glDrawArrays(GL_LINES, 0, vertexes.count());
            glDisable(GL_LINE_STIPPLE);
            glPushName((GLuint)q->objectId());
            glPopAttrib();
        }
        break;
    }
    case JShapeItem::ShapePlane:
    case JShapeItem::ShapeBox:
    {
        glTranslatef(pos.x(), pos.y(), pos.z());
        qreal dx = box.dx(), dy = box.dy(), dz = box.dz();
        if (dx < 1e-6) {        // plane - y:z
            dx = 1e-6;
        } else if (dy < 1e-6) { // plane - x:z
            dy = 1e-6;
        } else if (dz < 1e-6) { // plane - x:y
            dz = 1e-6;
        }
        qreal minVal = qMin(qMin(dx, dy), dz);
        glScalef(dx / minVal, dy / minVal, dz / minVal);
        glutSolidCube(minVal);
        if (q->pickable() && q->picking()) {
            glPushAttrib(GL_DEPTH_BIAS | GL_POLYGON_BIT | GL_LIGHTING_BIT);
            glDisable(GL_DEPTH_BITS);
            glDisable(GL_LIGHTING);
            glPopName();
            //
            glColor4f(0.6f, 0.6f, 0.6f, 0.7f);
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonOffset(1.0f, 1.0f);
            glutWireCube(minVal);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            //
            glPopMatrix();
            //
            glPushMatrix();
            QVector<QVector3D> vertexes;
            vertexes << QVector3D(box.left(), 0.0f, 0.0f)
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(box.right(), 0.0f, 0.0f)
                     << QVector3D(box.right(), box.floor(), box.back())
                        //
                     << QVector3D(0.0f, box.floor(), 0.0f)
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(0.0f, box.ceil(), 0.0f)
                     << QVector3D(box.left(), box.ceil(), box.back())
                        //
                     << QVector3D(0.0f, 0.0f, box.back())
                     << QVector3D(box.left(), box.floor(), box.back())
                     << QVector3D(0.0f, 0.0f, box.front())
                     << QVector3D(box.left(), box.floor(), box.front());
            glLineWidth(1.2f);
            glLineStipple(1, 0x3333);
            glColor4f(0.7f, 0.7f, 0.9f, 1.0f);
            glEnable(GL_LINE_STIPPLE);
            glVertexPointer(3, GL_FLOAT, 0, vertexes.data());
            glDrawArrays(GL_LINES, 0, vertexes.count());
            glDisable(GL_LINE_STIPPLE);
            glPushName((GLuint)q->objectId());
            glPopAttrib();
        } else if (q->outlineEnabled()) {
            QColor outlineColor = color.lighter();
            glColor4f(outlineColor.redF(), outlineColor.greenF(), outlineColor.blueF(), outlineColor.alphaF());
            glLineWidth(2.0f);
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonOffset(0.8f, 0.8f);
            glutWireCube(minVal);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        break;
    }
    case JShapeItem::ShapeEllipse:
    {
        glTranslatef(pos.x(), pos.y(), pos.z());
        qreal dx = box.dx(), dy = box.dy(), dz = box.dz();
        if (dx < 1e-6) {        // plane - y:z
            dx = 1e-6;
        } else if (dy < 1e-6) { // plane - x:z
            dy = 1e-6;
        } else if (dz < 1e-6) { // plane - x:y
            dz = 1e-6;
        }
        qreal minVal = qMin(qMin(dx, dy), dz);
        glScalef(dx / minVal, dy / minVal, dz / minVal);
        glutSolidSphere(minVal / 2, ellipse.slices, ellipse.stacks);
        if (q->pickable() && q->picking()) {

        }
        break;
    }
    default:
        Q_ASSERT(false);
        break;
    }

    glPopMatrix();
    glEndList();

    glDisableClientState(GL_VERTEX_ARRAY);

    if (!q->doneContext()) {
        return;
    }
}

J3D_END_NAMESPACE

// - class JShapeItem -

/**
 * @brief J3D::JShapeItem::JShapeItem
 * @param parent
 */
J3D::JShapeItem::JShapeItem(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JShapeItemPrivate(this))
{
    Q_D(JShapeItem);
    d->init();
}

/**
 * @brief JShapeItem::JShapeItem
 * @param identity
 * @param color
 * @param parent
 */
JShapeItem::JShapeItem(const QString &identity, const QColor &color, QObject *parent)
    : JGLObject(identity, color, parent)
    , d_ptr(new JShapeItemPrivate(this))
{
    Q_D(JShapeItem);
    d->init();
}

/**
 * @brief JShapeItem::~JShapeItem
 */
JShapeItem::~JShapeItem()
{
    delete d_ptr;
}

/**
 * @brief JShapeItem::shapeType
 * @return
 */
JShapeItem::ShapeType JShapeItem::shapeType() const
{
    Q_D(const JShapeItem);
    return d->shapeType;
}

/**
 * @brief JShapeItem::setPoint
 * @param pos
 * @param size
 */
void JShapeItem::setPoint(const QVector3D &pos, qreal size)
{
    Q_D(JShapeItem);
    d->shapeType = JShapeItem::ShapePoint;
    d->pointSize = size;
    JGLObject::setBox(JRect3D(pos, pos));
}

/**
 * @brief JShapeItem::setLine
 * @param box
 * @param width
 */
void JShapeItem::setLine(const JRect3D &box, qreal width)
{
    Q_D(JShapeItem);
    d->shapeType = ShapeLine;
    d->lineWidth = width;
    JGLObject::setBox(box);
}

/**
 * @brief JShapeItem::setPlane
 * @param box
 */
void JShapeItem::setPlane(const JRect3D &box)
{
    Q_D(JShapeItem);
    d->shapeType = ShapePlane;
    JGLObject::setBox(box);
}

/**
 * @brief JShapeItem::setBox
 * @param box
 */
void JShapeItem::setBox(const JRect3D &box)
{
    Q_D(JShapeItem);
    switch (box.type()) {
    case JRect3D::Invalid:
        break;
    case JRect3D::Point:
        setPoint(box.minVector());
        break;
    case JRect3D::Line:
        setLine(box);
        break;
    case JRect3D::Plane:
        setPlane(box);
        break;
    case JRect3D::Box:
        d->shapeType = ShapeBox;
        JGLObject::setBox(box);
        break;
    default:
        break;
    }
}

/**
 * @brief JShapeItem::setCircle
 * @param pos
 * @param radius
 * @param slices
 * @param stacks
 */
void JShapeItem::setCircle(const QVector3D &pos, qreal radius, int slices, int stacks)
{
    Q_D(JShapeItem);
    d->shapeType = JShapeItem::ShapeEllipse;
    d->ellipse.slices = slices;
    d->ellipse.stacks = stacks;
    JGLObject::setBox(JRect3D(pos.x() - radius, pos.y() - radius, pos.z() - radius,
                              pos.x() + radius, pos.y() + radius, pos.z() + radius));
}

/**
 * @brief JShapeItem::setEllipse
 * @param box
 * @param slices
 * @param stacks
 */
void JShapeItem::setEllipse(const JRect3D &box, int slices, int stacks)
{
    Q_D(JShapeItem);
    d->shapeType = JShapeItem::ShapeEllipse;
    d->ellipse.slices = slices;
    d->ellipse.stacks = stacks;
    JGLObject::setBox(box);
}

/**
 * @brief JShapeItem::setPointSize
 * @param size
 */
void JShapeItem::setPointSize(qreal size)
{
    Q_D(JShapeItem);
    if (d->shapeType != JShapeItem::ShapePoint) {
        return;
    }

    if (size != d->pointSize) {
        d->pointSize = size;
        update();
    }
}

/**
 * @brief JShapeItem::setLineWidth
 * @param width
 */
void JShapeItem::setLineWidth(qreal width)
{
    Q_D(JShapeItem);
    if (d->shapeType != JShapeItem::ShapeLine) {
        return;
    }

    if (width != d->lineWidth) {
        d->lineWidth = width;
        update();
    }
}

/**
 * @brief JShapeItem::draw
 * @param painter
 */
void JShapeItem::draw(JGLPainter *painter)
{
    JGLObject::draw(painter);
}

/**
 * @brief JShapeItem::update
 */
void JShapeItem::update()
{
    Q_D(JShapeItem);
    d->update();

    JGLObject::update();
}

QT_END_NAMESPACE
