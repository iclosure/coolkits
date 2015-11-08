#include "precomp.h"
#include "jplot3d_floor.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JFloorPrivate -

/**
 * @brief The JFloorPrivate class
 */
class JFloorPrivate
{
    J_DECLARE_PUBLIC(JFloor)
public:
    JFloorPrivate(JFloor *parent)
        : q_ptr(parent)
    {

    }

private:
    void init();

private:
};

/**
 * @brief JFloorPrivate::init
 */
void JFloorPrivate::init()
{
    Q_Q(JFloor);

    if (!q->beginContext()) {
        return;
    }

    q->setGLListId(glGenLists(1));
    glNewList(q->glListId(), GL_COMPILE);
    glPushMatrix();
    glScalef(1.2f, 0.0001f, 1.0f);
    glTranslatef(0.0f, -0.0001f, 0.0f);
    glColor4f(0.3f, 0.3f, 0.5f, 0.3f);
    glutSolidCube(2.5);
    glPopMatrix();
    glEndList();

    if (!q->doneContext()) {
        return;
    }
}

// - class JFloor -

/**
 * @brief JFloor::JFloor
 * @param parent
 */
JFloor::JFloor(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JFloorPrivate(this))
{
    Q_D(JFloor);
    d->init();
}

/**
 * @brief JFloor::~JFloor
 */
JFloor::~JFloor()
{
    delete d_ptr;
}

/**
 * @brief JFloor::draw
 * @param painter
 */
void JFloor::draw(JGLPainter *painter)
{
    JGLObject::draw(painter);
}

J3D_END_NAMESPACE

QT_END_NAMESPACE
