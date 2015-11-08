#include "precomp.h"
#include "jglpicking.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLPickingPrivate

/**
 * @brief The JGLPickingPrivate class
 */
class JGLPickingPrivate
{
    J_DECLARE_PUBLIC(JGLPicking)
public:
    JGLPickingPrivate(JGLPicking *parent)
        : q_ptr(parent)
    {

    }

private:
    void init();

private:
};

/**
 * @brief JGLPickingPrivate::init
 */
void JGLPickingPrivate::init()
{
    Q_Q(JGLPicking);
    q->setObjectName("JGLPicking");
}

J3D_END_NAMESPACE

// - class JGLPicking -

/**
 * @brief JGLPicking::JGLPicking
 * @param parent
 */
JGLPicking::JGLPicking(QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLPickingPrivate(this))
{
    Q_D(JGLPicking);
    d->init();
}

/**
 * @brief JGLPicking::~JGLPicking
 */
JGLPicking::~JGLPicking()
{
    delete d_ptr;
}

QT_END_NAMESPACE
