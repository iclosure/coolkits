#ifndef JGLFONT_H
#define JGLFONT_H

#include "jplot3d_global.h"
#include <QFont>
#include <QVector3D>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLFont -

class JGLFontPrivate;

class J3D_EXPORT JGLFont
{
public:
    static JGLFont *instance();
    static void releaseInstance();

    QFont font() const;
    void setFont(const QFont &font);

    void drawText2D(const QString &text);
    void drawText2D(const QString &text, const QColor &color);
    void drawText2D(const QString &text, const QVector3D &pos);
    void drawText2D(const QString &text, const QVector3D &pos, const QColor &color,
                    Qt::Alignment alignment = Qt::AlignLeft);

    void drawText3D(const QString &text);
    void drawText3D(const QString &text, const QColor &color);
    void drawText3D(const QString &text, const QVector3D &pos);
    void drawText3D(const QString &text, const QVector3D &pos, const QColor &color,
                    Qt::Alignment alignment = Qt::AlignLeft);

private:
    JGLFont();
    ~JGLFont();

private:
    J_DECLARE_PRIVATE(JGLFont)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLFONT_H
