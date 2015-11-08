#include "precomp.h"
#include "jglfont.h"
#include "jglfunction.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JGLFontPrivate

/**
 * @brief The JGLFontPrivate class
 */
class JGLFontPrivate
{
    J_DECLARE_PUBLIC(JGLFont)
    public:
        JGLFontPrivate(JGLFont *parent)
      : q_ptr(parent)
      , glListAscii(0)
      , font("Consolas", 18, QFont::Normal)
    {

    }

    ~JGLFontPrivate()
    {
        if (glListAscii != 0) {
            glDeleteLists(glListAscii, 128);
            glListAscii = 0;
        }
    }

private:
    void init();
    void update();

private:
    GLuint glListAscii;
    QFont font;
    static JGLFont *fontInstance;
};

/**
 * @brief JGLFontPrivate::fontInstance
 */
JGLFont *JGLFontPrivate::fontInstance = 0;

/**
 * @brief JGLFontPrivate::init
 */
void JGLFontPrivate::init()
{
    glListAscii = glGenLists(128);
    update();
}

/**
 * @brief JGLFontPrivate::update
 */
void JGLFontPrivate::update()
{
    if (glListAscii == 0) {
        return;
    }

#if defined(Q_WS_WIN) || defined(Q_OS_WIN)
    // weight
    int cWeight = 0;
    switch (font.weight()) {
    case QFont::Light:
        cWeight = FW_LIGHT;
        break;
    case QFont::Normal:
        cWeight = FW_NORMAL;
        break;
    case QFont::DemiBold:
        cWeight = FW_SEMIBOLD;
        break;
    case QFont::Bold:
        cWeight = FW_BOLD;
        break;
    case QFont::Black:
        cWeight = FW_BLACK;
        break;
    default:
        break;
    }

    HFONT hFont = ::CreateFontA(font.pointSize(), 0, 0, 0, cWeight, FALSE, FALSE, FALSE,
                               GB2312_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                               ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
                               font.family().toLatin1());
    if (!hFont) {
        return;
    }

    HFONT hOldFont = (HFONT)::SelectObject(wglGetCurrentDC(), hFont);
    ::DeleteObject(hOldFont);
    wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, glListAscii);
#endif
}

J3D_END_NAMESPACE

// - class JGLFont -

/**
 * @brief JGLFont::instance
 * @return
 */
JGLFont *JGLFont::instance()
{
    if (JGLFontPrivate::fontInstance == 0) {
        JGLFontPrivate::fontInstance = new JGLFont();
    }
    return JGLFontPrivate::fontInstance;
}

/**
 * @brief JGLFont::releaseInstance
 */
void JGLFont::releaseInstance()
{
    if (JGLFontPrivate::fontInstance != 0) {
        delete JGLFontPrivate::fontInstance;
        JGLFontPrivate::fontInstance = 0;
    }
}

/**
 * @brief JGLFont::JGLFont
 */
JGLFont::JGLFont()
    : d_ptr(new JGLFontPrivate(this))
{
    Q_D(JGLFont);
    d->init();
}

/**
 * @brief JGLFont::~JGLFont
 */
JGLFont::~JGLFont()
{
    delete d_ptr;
}

/**
 * @brief JGLFont::font
 * @return
 */
QFont JGLFont::font() const
{
    Q_D(const JGLFont);
    return d->font;
}

/**
 * @brief JGLFont::setFont
 * @param font
 */
void JGLFont::setFont(const QFont &font)
{
    Q_D(JGLFont);
    d->font = font;
    d->update();
}

/**
 * @brief JGLFont::drawText2D
 * @param text
 */
void JGLFont::drawText2D(const QString &text)
{
    Q_D(JGLFont);
    if (text.isEmpty() || d->glListAscii == 0) {
        return;
    }
#if defined(Q_OS_WIN) || defined(Q_WS_WIN)
    glPushAttrib(GL_LIST_BIT);
    glListBase(d->glListAscii);
    glCallLists(text.size(), GL_UNSIGNED_BYTE, text.toLocal8Bit());
    glPopAttrib();
#else
    int len = text.count();
    for (int i = 0; i < len; ++i) {
#if defined(Q_OS_MAC) && (QT_VERSION >= 0x050000)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i).toLatin1());
#else
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text.at(i).toLatin1());
#endif
    }
#endif
}

/**
 * @brief JGLFont::drawText2D
 * @param text
 * @param color
 */
void JGLFont::drawText2D(const QString &text, const QColor &color)
{
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    drawText2D(text);
}

/**
 * @brief JGLFont::drawText2D
 * @param text
 * @param pos
 */
void JGLFont::drawText2D(const QString &text, const QVector3D &pos)
{
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glRasterPos3f(pos.x(), pos.y(), pos.z());
    drawText2D(text);
    glPopAttrib();
    glPopMatrix();
}

/**
 * @brief JGLFont::drawText2D
 * @param text
 * @param pos
 * @param color
 * @param alignment
 */
void JGLFont::drawText2D(const QString &text, const QVector3D &pos, const QColor &color,
                         Qt::Alignment alignment)
{
    switch (alignment) {
    case Qt::AlignLeft:

        break;
    default:
        break;
    }

    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    drawText2D(text, pos);
}

/**
 * @brief JGLFont::drawText3D
 * @param text
 */
void JGLFont::drawText3D(const QString &text)
{
    Q_UNUSED(text);
    // draw
}

/**
 * @brief JGLFont::drawText3D
 * @param text
 * @param color
 */
void JGLFont::drawText3D(const QString &text, const QColor &color)
{
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    drawText3D(text);
}

/**
 * @brief JGLFont::drawText3D
 * @param text
 * @param pos
 */
void JGLFont::drawText3D(const QString &text, const QVector3D &pos)
{
    glPushMatrix();
    glRasterPos3f(pos.x(), pos.y(), pos.z());
    drawText3D(text);
    glPopMatrix();
}

/**
 * @brief JGLFont::drawText3D
 * @param text
 * @param pos
 * @param color
 * @param alignment
 */
void JGLFont::drawText3D(const QString &text, const QVector3D &pos, const QColor &color,
                         Qt::Alignment alignment)
{
    switch (alignment) {
    case Qt::AlignLeft:

        break;
    default:
        break;
    }

    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    drawText3D(text, pos);
}

QT_END_NAMESPACE
