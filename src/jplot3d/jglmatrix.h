#ifndef JGLMATRIX_H
#define JGLMATRIX_H

#include "jplot3d_global.h"
#include <QVector3D>
#include <qmath.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JRect3D -

class J3D_EXPORT JRect3D
{
public:
    explicit JRect3D() { xp = yp = zp; w = h = l; }
    inline JRect3D(qreal left, qreal floor, qreal back,
                   qreal width, qreal height, qreal depth);
    inline JRect3D(const QVector3D &minVector, const QVector3D &maxVector);

    inline JRect3D(const JRect3D &other);
    inline JRect3D &operator =(const JRect3D &other);

    inline bool isNull() const;
    inline bool isEmpty() const;
    inline bool isValid() const;

    inline QVector3D delta() const;

    inline QVector3D minVector() const;
    inline QVector3D maxVector() const;

    inline void setMinVector(const QVector3D &value);
    inline void setMaxVector(const QVector3D &value);

    inline qreal x() const { return xp; }
    inline qreal y() const { return yp; }
    inline qreal z() const { return zp; }
    inline qreal minX() const { return xp; }
    inline qreal minY() const { return yp; }
    inline qreal minZ() const { return zp; }
    inline qreal maxX() const { return xp + w; }
    inline qreal maxY() const { return yp + h; }
    inline qreal maxZ() const { return zp + l; }

    inline void setMinX(qreal value) { xp = value; }
    inline void setMinY(qreal value) { yp = value; }
    inline void setMinZ(qreal value) { zp = value; }
    inline void setMaxX(qreal value) { w = value - xp; }
    inline void setMaxY(qreal value) { h = value - yp; }
    inline void setMaxZ(qreal value) { l = value - zp; }

    inline qreal dx() const { return w; }
    inline qreal dy() const { return h; }
    inline qreal dz() const { return l; }
    inline qreal width() const { return w; }
    inline qreal height() const { return h; }
    inline qreal depth() const { return l; }

    inline qreal left() const { return xp; }
    inline qreal floor() const { return yp; }
    inline qreal back() const { return zp; }
    inline qreal right() const { return xp + w; }
    inline qreal ceil() const { return yp + h; }
    inline qreal front() const { return zp + l; }

    inline void setLeft(qreal value) { xp = value; }
    inline void setFloor(qreal value) { yp = value; }
    inline void setBack(qreal value) { zp = value; }
    inline void setRight(qreal value) { w = value - xp; }
    inline void setCeil(qreal value) { h = value - yp; }
    inline void setFront(qreal value) { l = value - zp; }

    inline QVector3D center() const;

    inline JRect3D operator-() const;
    inline JRect3D operator+(const QVector3D &v) const;
    inline JRect3D operator-(const QVector3D &v) const;
    inline JRect3D operator+=(const QVector3D &v);
    inline JRect3D operator-=(const QVector3D &v);

    inline friend JRect3D operator+(const QVector3D &v, const JRect3D &box);
    inline friend JRect3D operator-(const QVector3D &v, const JRect3D &box);

    JRect3D operator |(const JRect3D &r) const;
    JRect3D operator &(const JRect3D &r) const;

    inline JRect3D operator *(const JRect3D &r) const;
    inline JRect3D operator /(const JRect3D &r) const;
    inline JRect3D operator *(const QVector3D &v) const;
    inline JRect3D operator /(const QVector3D &v) const;
    inline JRect3D operator *(qreal factor) const;
    inline JRect3D operator /(qreal factor) const;

    inline JRect3D operator |=(const JRect3D &r);
    inline JRect3D operator &=(const JRect3D &r);

    inline JRect3D operator *=(const JRect3D &r);
    inline JRect3D operator /=(const JRect3D &r);
    inline JRect3D operator *=(const QVector3D &v);
    inline JRect3D operator /=(const QVector3D &v);
    inline JRect3D operator *=(qreal factor);
    inline JRect3D operator /=(qreal factor);

    bool contains(const QVector3D &p) const;
    inline bool contains(qreal x, qreal y, qreal z) const;
    bool contains(const JRect3D &r) const;
    inline JRect3D unite(const JRect3D &r) const;
    inline JRect3D united(const JRect3D &r) const;
    JRect3D intersect(const JRect3D &r) const;
    inline JRect3D intersected(const JRect3D &r) const;
    bool intersects(const JRect3D &r) const;

    bool isNormalized() const;

    inline friend bool operator ==(const JRect3D &r1, const JRect3D &r2);
    inline friend bool operator !=(const JRect3D &r1, const JRect3D &r2);

    enum Type { Invalid = -1, Point, Line, Plane, Box };

    inline bool isShape() const;
    inline bool isPoint(qreal eps = 1e-6) const;
    inline bool isLine(qreal eps = 1e-6) const;
    inline bool isPlane(qreal eps = 1e-6) const;
    inline bool isBox(qreal eps = 1e-6) const;
    inline Type type(qreal eps = 1e-6) const;
    JRect3D intersect0(const JRect3D &r) const;     //! for shape

    JRect3D normalized() const;
    JRect3D &normalize();

private:
    qreal xp, yp, zp;
    qreal w, h, l;
};

Q_INLINE_TEMPLATE
JRect3D::JRect3D(qreal left, qreal floor, qreal back,
                                   qreal width, qreal height, qreal depth)
    : xp(left), yp(floor), zp(back), w(width), h(height), l(depth)
{
}

Q_INLINE_TEMPLATE
JRect3D::JRect3D(const QVector3D &minVector, const QVector3D &maxVector)
{
    xp = minVector.x();
    yp = minVector.y();
    zp = minVector.z();
    w = maxVector.x() - xp;
    h = maxVector.y() - yp;
    l = maxVector.z() - zp;
}

Q_INLINE_TEMPLATE
JRect3D::JRect3D(const JRect3D &other)
{
    *this = other;
}

Q_INLINE_TEMPLATE
JRect3D &JRect3D::operator =(const JRect3D &other)
{
    xp = other.xp;
    yp = other.yp;
    zp = other.zp;
    w = other.w;
    h = other.h;
    l = other.l;
    return *this;
}

Q_INLINE_TEMPLATE
bool JRect3D::isNull() const
{ return w == 0. && h == 0. && l == 0.; }

Q_INLINE_TEMPLATE
bool JRect3D::isEmpty() const
{ return w <= 0. || h <= 0. || l <= 0.; }

Q_INLINE_TEMPLATE
bool JRect3D::isValid() const
{ return w > 0. && h > 0. && l > 0.; }

Q_INLINE_TEMPLATE
QVector3D JRect3D::delta() const
{ return QVector3D(w, h, l); }

QVector3D JRect3D::minVector() const
{ return QVector3D(xp, yp, zp); }

Q_INLINE_TEMPLATE
QVector3D JRect3D::maxVector() const
{ return QVector3D(xp + w, yp + h, zp + l); }

Q_INLINE_TEMPLATE
void JRect3D::setMinVector(const QVector3D &value)
{
    xp = value.x();
    yp = value.y();
    zp = value.z();
}

Q_INLINE_TEMPLATE
void JRect3D::setMaxVector(const QVector3D &value)
{
    w = value.x() - xp;
    h = value.y() - yp;
    l = value.z() - zp;
}

Q_INLINE_TEMPLATE
QVector3D JRect3D::center() const
{ return QVector3D(xp + w/2, yp + h/2, zp + l/2); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator -() const
{ return JRect3D(-xp, -yp, -zp, -w, -h, -l); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator +(const QVector3D &v) const
{ return JRect3D(xp + v.x(), yp + v.y(), zp + v.z(), w, h, l); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator -(const QVector3D &v) const
{ return JRect3D(xp - v.x(), yp - v.y(), zp - v.z(), w, h, l); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator+=(const QVector3D &v)
{
    *this = *this + v;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator-=(const QVector3D &v)
{
    *this = *this - v;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D operator+(const QVector3D &v, const JRect3D &r)
{
    return r + v;
}

Q_INLINE_TEMPLATE
JRect3D operator-(const QVector3D &v, const JRect3D &r)
{
    return -r + v;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator *(const JRect3D &r) const
{ return JRect3D(xp * r.xp, yp * r.yp, zp * r.zp, w * r.w, h * r.h, l * r.l); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator /(const JRect3D &r) const
{ return JRect3D(xp / r.xp, yp / r.yp, zp / r.zp, w / r.w, h / r.h, l / r.l); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator *(const QVector3D &v) const
{ return JRect3D(xp * v.x(), yp * v.y(), zp * v.z(), w * v.x(), h * v.y(), l * v.z()); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator /(const QVector3D &v) const
{ return JRect3D(xp / v.x(), yp / v.y(), zp / v.z(), w / v.x(), h / v.y(), l / v.z()); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator *(qreal factor) const
{ return JRect3D(xp * factor, yp * factor, zp * factor, w * factor, h * factor, l * factor); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator /(qreal factor) const
{ return JRect3D(xp / factor, yp / factor, zp / factor, w / factor, h / factor, l / factor); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator |=(const JRect3D &r)
{
    *this = *this | r;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator &=(const JRect3D &r)
{
    *this = *this & r;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator *=(const JRect3D &r)
{
    *this = *this * r;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator /=(const JRect3D &r)
{
    *this = *this / r;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator *=(const QVector3D &v)
{
    *this = *this * v;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator /=(const QVector3D &v)
{
    *this = *this / v;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator *=(qreal factor)
{
    *this = *this * factor;
    return *this;
}

Q_INLINE_TEMPLATE
JRect3D JRect3D::operator /=(qreal factor)
{
    *this = *this / factor;
    return *this;
}

Q_INLINE_TEMPLATE
bool JRect3D::contains(qreal x, qreal y, qreal z) const
{ return contains(QVector3D(x, y, z)); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::unite(const JRect3D &r) const
{ return *this | r; }

Q_INLINE_TEMPLATE
JRect3D JRect3D::united(const JRect3D &r) const
{ return unite(r); }

Q_INLINE_TEMPLATE
JRect3D JRect3D::intersect(const JRect3D &r) const
{ return *this & r; }

Q_INLINE_TEMPLATE
JRect3D JRect3D::intersected(const JRect3D &r) const
{ return intersect(r); }

Q_INLINE_TEMPLATE
bool JRect3D::isNormalized() const
{
    return (xp >= 0. || qFuzzyIsNull((float)xp))
            && (yp >= 0. || qFuzzyIsNull((float)yp))
            && (zp >= 0. || qFuzzyIsNull((float)zp))
            && ((xp + w) <= 1. || qFuzzyCompare((float)(xp + w), 1.f))
            && ((yp + h) <= 1. || qFuzzyCompare((float)(yp + h), 1.f))
            && ((zp + l) <= 1. || qFuzzyCompare((float)(zp + l), 1.f));
}

Q_INLINE_TEMPLATE
bool operator ==(const JRect3D &r1, const JRect3D &r2)
{
    return qFuzzyCompare(r1.xp, r2.xp)
            && qFuzzyCompare(r1.yp, r2.yp)
            && qFuzzyCompare(r1.zp, r2.zp)
            && qFuzzyCompare(r1.w, r2.w)
            && qFuzzyCompare(r1.h, r2.h)
            && qFuzzyCompare(r1.l, r2.l);
}

Q_INLINE_TEMPLATE
bool operator !=(const JRect3D &r1, const JRect3D &r2)
{
    return !qFuzzyCompare(r1.xp, r2.xp)
            || !qFuzzyCompare(r1.yp, r2.yp)
            || !qFuzzyCompare(r1.zp, r2.zp)
            || !qFuzzyCompare(r1.w, r2.w)
            || !qFuzzyCompare(r1.h, r2.h)
            || !qFuzzyCompare(r1.l, r2.l);
}

Q_INLINE_TEMPLATE
bool JRect3D::isShape() const
{ return w >= 0. && h >= 0. && l >= 0.; }

Q_INLINE_TEMPLATE
bool JRect3D::isPoint(qreal eps) const
{ return isShape() && w < eps && h < eps && l < eps; }

Q_INLINE_TEMPLATE
bool JRect3D::isLine(qreal eps) const
{
    return isShape() && ((w < eps && h < eps && l >= eps) ||
                         (h < eps && l < eps && w >= eps) ||
                         (l < eps && w < eps && h >= eps));
}

Q_INLINE_TEMPLATE
bool JRect3D::isPlane(qreal eps) const
{
    return isShape() && ((w < eps && h >= eps && l >= eps) ||
                         (h < eps && l >= eps && w >= eps) ||
                         (l < eps && w >= eps && h >= eps));
}

Q_INLINE_TEMPLATE
bool JRect3D::isBox(qreal eps) const
{ return w >= eps && h >= eps && l >= eps; }

Q_INLINE_TEMPLATE
JRect3D::Type JRect3D::type(qreal eps) const
{
    if (w < 0. || h < 0. || l < 0.) {
        return Invalid;
    } else if (w < eps && h < eps && l < eps) {
        return Point;
    } else if ((w < eps && h < eps) ||
               (h < eps && l < eps) ||
               (l < eps && w < eps)) {
        return Line;
    } else if (w < eps || h < eps || l < eps) {
        return Plane;
    } else {
        return Box;
    }
}

} // - end of namespace J3D

Q_DECLARE_METATYPE(J3D::JRect3D)

#ifndef QT_NO_DEBUG_STREAM
#include <QDebug>

Q_INLINE_TEMPLATE
QDebug operator <<(QDebug dbg, const J3D::JRect3D &r)
{
    dbg.nospace() << "J3D::JRect3D ->" << endl;
    dbg << qSetFieldWidth(10);
    dbg << r.left() << r.floor() << r.back() << endl;
    dbg << r.width() << r.height() << r.depth();
    dbg << qSetFieldWidth(0);
    return dbg.space();
}

#endif

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLMATRIX_H
