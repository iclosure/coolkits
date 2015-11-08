#ifndef JGLFUNCTION_H
#define JGLFUNCTION_H

#include "jplot3d_global.h"
#include <QMatrix4x4>
QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLFunction -

class J3D_EXPORT JGLFunction
{
public:
    static void loadMatrix(const QMatrix4x4 &m);
    static void multMatrix(const QMatrix4x4 &m);
    static QPointF pixelPosToViewPos(const QRect &viewport, const QPoint &pos);
    static QPointF pixelPosToViewPos(const QRectF &viewport, const QPointF &pos);

    static QString gbk2utf8(const QString &text);
    static QString utf82gbk(const QString &text);

    static QColor rangColor(qreal opacity = 1.0f);

    static void clearAnnotate(const QString &folder);
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLFUNCTION_H
