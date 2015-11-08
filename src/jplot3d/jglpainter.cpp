#include "precomp.h"
#include "jglpainter.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLPainterPrivate

/**
 * @brief The JGLPainterPrivate class
 */
class JGLPainterPrivate
{
    J_DECLARE_PUBLIC(JGLPainter)
public:
    JGLPainterPrivate(JGLPainter *parent)
        : q_ptr(parent)
        , scene(0)
        , picking(false)
        , objectPickId(-1)
    {

    }

    static void gl_enable(GLenum cap, GLboolean enable)
    {
        if (enable) {
            glEnable(cap);
        } else {
            glDisable(cap);
        }
    }

private:
    void init();

    inline void save();
    inline void restore();

private:
    JGLScene *scene;
    bool picking;
    unsigned int objectPickId;

    GLboolean defaultDepthTest;
    GLboolean defaultAlphaTest;
    GLboolean defaultPointSmooth;
    GLboolean defaultLineSmooth;
    GLboolean defaultCullFace;
    GLboolean defaultLighting;
    GLboolean defaultTexture2d;
    GLboolean defaultNormalize;
    GLboolean defaultBlend;
    GLboolean defaultColorMaterial;
    GLboolean defaultPointSize;
    GLboolean defaultLineWidth;
    GLboolean defaultMultiSample;
};

/**
 * @brief JGLPainterPrivate::init
 */
void JGLPainterPrivate::init()
{
    Q_Q(JGLPainter);
    q->setObjectName("JGLPainter");
    save();     // save current properties of opengl
}

/**
 * @brief JGLPainterPrivate::save
 */
void JGLPainterPrivate::save()
{
    glGetBooleanv(GL_DEPTH_TEST, &defaultDepthTest);
    glGetBooleanv(GL_ALPHA_TEST, &defaultAlphaTest);
    glGetBooleanv(GL_POINT_SMOOTH, &defaultPointSmooth);
    glGetBooleanv(GL_LINE_SMOOTH, &defaultLineSmooth);
    glGetBooleanv(GL_CULL_FACE, &defaultCullFace);
    glGetBooleanv(GL_LIGHTING, &defaultLighting);
    glGetBooleanv(GL_TEXTURE_2D, &defaultTexture2d);
    glGetBooleanv(GL_NORMALIZE, &defaultNormalize);
    glGetBooleanv(GL_BLEND, &defaultBlend);
    glGetBooleanv(GL_COLOR_MATERIAL, &defaultColorMaterial);
    glGetBooleanv(GL_POINT_SIZE, &defaultPointSize);
    glGetBooleanv(GL_LINE_WIDTH, &defaultLineWidth);
    glGetBooleanv(GL_MULTISAMPLE_BIT, &defaultMultiSample);
}

/**
 * @brief JGLPainterPrivate::restore
 */
void JGLPainterPrivate::restore()
{
    gl_enable(GL_DEPTH_TEST, defaultDepthTest);
    gl_enable(GL_ALPHA_TEST, defaultAlphaTest);
    gl_enable(GL_POINT_SMOOTH, defaultPointSmooth);
    gl_enable(GL_LINE_SMOOTH, defaultLineSmooth);
    gl_enable(GL_CULL_FACE, defaultCullFace);
    gl_enable(GL_LIGHTING, defaultLighting);
    gl_enable(GL_TEXTURE_2D, defaultTexture2d);
    gl_enable(GL_NORMALIZE, defaultNormalize);
    gl_enable(GL_BLEND, defaultBlend);
    gl_enable(GL_COLOR_MATERIAL, defaultColorMaterial);
    gl_enable(GL_POINT_SIZE, defaultPointSize);
    gl_enable(GL_LINE_WIDTH, defaultLineWidth);
    gl_enable(GL_MULTISAMPLE_BIT, defaultMultiSample);
}

J3D_END_NAMESPACE

// - class JGLPainter -

/**
 * @brief JGLPainter::JGLPainter
 * @param parent
 */
JGLPainter::JGLPainter(QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLPainterPrivate(this))
{
    Q_D(JGLPainter);
    d->init();
}

/**
 * @brief JGLPainter::JGLPainter
 * @param scene
 * @param parent
 */
JGLPainter::JGLPainter(JGLScene *scene, QObject *parent)
    : QObject(parent)
    , d_ptr(new JGLPainterPrivate(this))
{
    Q_D(JGLPainter);
    d->init();
    d->scene = scene;
}

/**
 * @brief JGLPainter::~JGLPainter
 */
JGLPainter::~JGLPainter()
{
    delete d_ptr;
}

/**
 * @brief JGLPainter::scene
 * @return
 */
JGLScene *JGLPainter::scene() const
{
    Q_D(const JGLPainter);
    return d->scene;
}

/**
 * @brief JGLPainter::picking
 * @return
 */
bool JGLPainter::picking() const
{
    Q_D(const JGLPainter);
    return d->picking;
}

/**
 * @brief JGLPainter::setPicking
 * @param value
 */
void JGLPainter::setPicking(bool value)
{
    Q_D(JGLPainter);
    if (value != d->picking) {
        d->picking = value;
        Q_EMIT pickingChanged(value);
    }
}

/**
 * @brief JGLPainter::objectPickId
 * @return
 */
unsigned int JGLPainter::objectPickId() const
{
    Q_D(const JGLPainter);
    return d->objectPickId;
}

/**
 * @brief JGLPainter::setObjectPickId
 * @param id
 */
void JGLPainter::setObjectPickId(unsigned int id)
{
    Q_D(JGLPainter);
    d->objectPickId = id;
}

/**
 * @brief JGLPainter::clearPickObjects
 */
void JGLPainter::clearPickObjects()
{
    Q_D(JGLPainter);
    d->objectPickId = -1;
}

/**
 * @brief JGLPainter::begin
 */
void JGLPainter::begin()
{
    save();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //glEnable(GL_MULTISAMPLE);
    //glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
}

/**
 * @brief JGLPainter::end
 */
void JGLPainter::end()
{
    restore();
}

/**
 * @brief JGLPainter::save
 */
void JGLPainter::save()
{
    Q_D(JGLPainter);
    d->save();
}

/**
 * @brief JGLPainter::restore
 */
void JGLPainter::restore()
{
    Q_D(JGLPainter);
    d->restore();
}

QT_END_NAMESPACE
