#include "precomp.h"
#include "jplot3d_shadow.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JShadowPrivate -

/**
 * @brief The JShadowPrivate class
 */
class JShadowPrivate
{
    J_DECLARE_PUBLIC(JShadow)
public:
    JShadowPrivate(JShadow *parent)
        : q_ptr(parent)
    {

    }

private:
    void init();

private:
};

/**
 * @brief JShadowPrivate::init
 */
void JShadowPrivate::init()
{
    Q_Q(JShadow);
    q->setObjectName("JShadow");
}

J3D_END_NAMESPACE

// - class JShadow -

/**
 * @brief JShadow::JShadow
 * @param parent
 */
JShadow::JShadow(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JShadowPrivate(this))
{
    Q_D(JShadow);
    d->init();
}

/**
 * @brief JShadow::~JShadow
 */
JShadow::~JShadow()
{
    delete d_ptr;
}

QT_END_NAMESPACE
