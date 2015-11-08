#include "precomp.h"
#include "jglindicator.h"

#include "jglfunction.h"

QT_BEGIN_NAMESPACE
J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLIndicatorPrivate

/**
 * @brief The JGLIndicatorPrivate class
 */
class JGLIndicatorPrivate
{
    J_DECLARE_PUBLIC(JGLIndicator)
public:
    JGLIndicatorPrivate(JGLIndicator *parent)
        : q_ptr(parent)
        , vertexRadius(0.01f)
        , glList(0)
        , xColor(defaultXColor())
        , yColor(defaultYColor())
        , zColor(defaultZColor())
    {

    }

    ~JGLIndicatorPrivate()
    {
        setDirty();
    }

    static QColor defaultXColor() { return QColor(255, 0, 0, 200); }
    static QColor defaultYColor() { return QColor(0, 255, 0, 200); }
    static QColor defaultZColor() { return QColor(0, 0, 255, 200); }

private:
    void init();
    void setDirty();

    void createIndicator();

private:
    qreal vertexRadius;
    GLuint glList;
    QQuaternion rotation;
    QColor xColor, yColor, zColor;
};

/**
 * @brief JGLIndicatorPrivate::init
 */
void JGLIndicatorPrivate::init()
{
    createIndicator();
}

/**
 * @brief JGLIndicatorPrivate::setDirty
 */
void JGLIndicatorPrivate::setDirty()
{
    if (glList != 0) {
        glDeleteLists(glList, 1);
        glList = 0;
    }
}

/**
 * @brief JGLIndicatorPrivate::createIndicator
 */
void JGLIndicatorPrivate::createIndicator()
{
    if (glList == 0) {
        glList = glGenLists(1);
    }

    glNewList(glList, GL_COMPILE);
    GLUquadric *object = gluNewQuadric();

    // line - x
    glColor4f(xColor.redF(), xColor.greenF(), xColor.blueF(), xColor.alphaF());
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(object, 0.01, 0.01, 1.05, 30, 30);
    glPopMatrix();
    // point -x
    glPushMatrix();
    glTranslatef(1.05f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidCone(0.05, 0.15, 50, 50);
    glPopMatrix();
    // name - x
    glPushMatrix();
    glRasterPos3f(1.05f, 0.03f, -0.03f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'x');
    glPopMatrix();
    // line - y
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor4f(yColor.redF(), yColor.greenF(), yColor.blueF(), yColor.alphaF());
    gluCylinder(object, 0.01, 0.01, 1.05, 30, 30);
    glPopMatrix();
    // point - y
    glPushMatrix();
    glTranslatef(0.0f, 1.05f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.05, 0.15, 50, 50);
    glPopMatrix();
    // name - y
    glPushMatrix();
    glRasterPos3f(-0.03f, 1.05f, -0.03f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'y');
    glPopMatrix();
    // line - z
    glColor4f(zColor.redF(), zColor.greenF(), zColor.blueF(), zColor.alphaF());
    gluCylinder(object, 0.01, 0.01, 1.05, 30, 30);
    // point - z
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.05f);
    glutSolidCone(0.05, 0.15, 50, 50);
    glPopMatrix();
    // name - z
    glPushMatrix();
    glRasterPos3f(-0.03f, 0.03f, 1.05f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'z');
    glPopMatrix();

    gluDeleteQuadric(object);
    glEndList();
}

J3D_END_NAMESPACE

// - class JGLIndicator -

/**
 * @brief JGLIndicator::JGLIndicator
 * @param parent
 */
JGLIndicator::JGLIndicator(QObject *parent)
    : QObject(parent)
    , JItemBase(0, 0, 100, 100)
    , d_ptr(new JGLIndicatorPrivate(this))
{
    Q_D(JGLIndicator);
    d->init();
}

/**
 * @brief JGLIndicator::JGLIndicator
 * @param x
 * @param y
 * @param width
 * @param height
 * @param parent
 */
JGLIndicator::JGLIndicator(int x, int y, int width, int height, QObject *parent)
    : QObject(parent)
    , JItemBase(x, y, width, height)
    , d_ptr(new JGLIndicatorPrivate(this))
{
    Q_D(JGLIndicator);
    d->init();
}

/**
 * @brief JGLIndicator::~JGLIndicator
 */
JGLIndicator::~JGLIndicator()
{
    delete d_ptr;
}

/**
 * @brief JGLIndicator::rotation
 * @return
 */
QQuaternion JGLIndicator::rotation() const
{
    Q_D(const JGLIndicator);
    return d->rotation;
}

/**
 * @brief JGLIndicator::setRotation
 * @param value
 */
void JGLIndicator::setRotation(const QQuaternion &value)
{
    Q_D(JGLIndicator);
    if (value != d->rotation) {
        d->rotation = value;
        update();
        Q_EMIT rotationChanged(value);
    }
}

/**
 * @brief JGLIndicator::defaultXColor
 * @return
 */
QColor JGLIndicator::defaultXColor()
{
    return JGLIndicatorPrivate::defaultXColor();
}

/**
 * @brief JGLIndicator::xColor
 * @return
 */
QColor JGLIndicator::xColor() const
{
    Q_D(const JGLIndicator);
    return d->xColor;
}

/**
 * @brief JGLIndicator::setXColor
 * @param value
 */
void JGLIndicator::setXColor(const QColor &value)
{
    Q_D(JGLIndicator);
    if (value != d->xColor) {
        d->xColor = value;
        update();
    }
}

/**
 * @brief JGLIndicator::defaultYColor
 * @return
 */
QColor JGLIndicator::defaultYColor()
{
    return JGLIndicatorPrivate::defaultYColor();
}

/**
 * @brief JGLIndicator::yColor
 * @return
 */
QColor JGLIndicator::yColor() const
{
    Q_D(const JGLIndicator);
    return d->yColor;
}

/**
 * @brief JGLIndicator::setYColor
 * @param value
 */
void JGLIndicator::setYColor(const QColor &value)
{
    Q_D(JGLIndicator);
    if (value != d->yColor) {
        d->yColor = value;
        update();
    }
}

/**
 * @brief JGLIndicator::defaultZColor
 * @return
 */
QColor JGLIndicator::defaultZColor()
{
    return JGLIndicatorPrivate::defaultZColor();
}

/**
 * @brief JGLIndicator::zColor
 * @return
 */
QColor JGLIndicator::zColor() const
{
    Q_D(const JGLIndicator);
    return d->zColor;
}

/**
 * @brief JGLIndicator::setZColor
 * @param value
 */
void JGLIndicator::setZColor(const QColor &value)
{
    Q_D(JGLIndicator);
    if (value != d->zColor) {
        d->zColor = value;
        update();
    }
}

/**
 * @brief JGLIndicator::paint
 * @param painter
 * @param option
 * @param widget
 */
void JGLIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(JGLIndicator);
    painter->beginNativePainting();

    qreal width = boundingRect().width();
    qreal height = boundingRect().height();
#if defined(Q_OS_MAC) && (QT_VERSION >= 0x050000)
    glViewport(0, 0, (GLsizei)width * 2, (GLsizei)height * 2);
#else
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
#endif
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(45.0, width / height, 0.01, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    QMatrix4x4 matrix;
    matrix.rotate(d->rotation);
    matrix(2, 3) -= 1.1 * qExp(1.0);
    JGLFunction::loadMatrix(matrix);

    glCallList(d->glList);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    painter->endNativePainting();

    JItemBase::paint(painter, option, widget);
}

QT_END_NAMESPACE
