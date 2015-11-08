#ifndef JGLMATRIX_H
#define JGLMATRIX_H

#include "jplot3d_global.h"
#include <QMatrix3x2>
#include <QVector3D>
#include <qmath.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JRect3D -

class J3D_EXPORT JRect3D : public QGenericMatrix<3, 2, qreal>
{
public:
    JRect3D() : QGenericMatrix<3, 2, qreal>() {}
    JRect3D(qreal left, qreal floor, qreal back,
            qreal right, qreal ceil, qreal front);
    JRect3D(const QVector3D &minVector, const QVector3D &maxVector);

    QVector3D minVector() const;
    QVector3D maxVector() const;

    void setMinVector(const QVector3D &value);
    void setMaxVector(const QVector3D &value);

    inline qreal minX() const { return (*this)(0, 0); }
    inline qreal minY() const { return (*this)(0, 1); }
    inline qreal minZ() const { return (*this)(0, 2); }

    inline qreal maxX() const { return (*this)(1, 0); }
    inline qreal maxY() const { return (*this)(1, 1); }
    inline qreal maxZ() const { return (*this)(1, 2); }

    inline void setMinX(qreal value) { (*this)(0, 0) = value; }
    inline void setMinY(qreal value) { (*this)(0, 1) = value; }
    inline void setMinZ(qreal value) { (*this)(0, 2) = value; }

    inline void setMaxX(qreal value) { (*this)(1, 0) = value; }
    inline void setMaxY(qreal value) { (*this)(1, 1) = value; }
    inline void setMaxZ(qreal value) { (*this)(1, 2) = value; }

    inline qreal left() const { return (*this)(0, 0); }
    inline qreal floor() const { return (*this)(0, 1); }
    inline qreal back() const { return (*this)(0, 2); }
    inline qreal right() const { return (*this)(1, 0); }
    inline qreal ceil() const { return (*this)(1, 1); }
    inline qreal front() const { return (*this)(1, 2); }

    inline void setLeft(qreal value) { (*this)(0, 0) = value; }
    inline void setFloor(qreal value) { (*this)(0, 1) = value; }
    inline void setBack(qreal value) { (*this)(0, 2) = value; }
    inline void setRight(qreal value) { (*this)(1, 0) = value; }
    inline void setCeil(qreal value) { (*this)(1, 1) = value; }
    inline void setFront(qreal value) { (*this)(1, 2) = value; }

    inline qreal dx() const { return qFabs((*this)(1, 0) - (*this)(0, 0)); }
    inline qreal dy() const { return qFabs((*this)(1, 1) - (*this)(0, 1)); }
    inline qreal dz() const { return qFabs((*this)(1, 2) - (*this)(0, 2)); }

    QVector3D center() const;

    JRect3D united(const JRect3D &other) const;
    JRect3D intersected(const JRect3D &other) const;

    JRect3D operator-() const;
    JRect3D operator+(const QVector3D &v) const;
    JRect3D operator-(const QVector3D &v) const;

    friend JRect3D operator+(const QVector3D &v, const JRect3D &box);
    friend JRect3D operator-(const QVector3D &v, const JRect3D &box);

    JRect3D operator+=(const QVector3D &v);
    JRect3D operator-=(const QVector3D &v);

    JRect3D operator |(const JRect3D &other) const;
    JRect3D operator &(const JRect3D &other) const;

    JRect3D operator *(const JRect3D &other) const;
    JRect3D operator /(const JRect3D &other) const;

    JRect3D operator *(const QVector3D &v) const;
    JRect3D operator /(const QVector3D &v) const;

    JRect3D operator *(qreal factor) const;
    JRect3D operator /(qreal factor) const;

    JRect3D operator |=(const JRect3D &other);
    JRect3D operator &=(const JRect3D &other);

    JRect3D operator *=(const JRect3D &other);
    JRect3D operator /=(const JRect3D &other);

    JRect3D operator *=(const QVector3D &v);
    JRect3D operator /=(const QVector3D &v);

    JRect3D operator *=(qreal factor);
    JRect3D operator /=(qreal factor);

    JRect3D normalized() const;
    JRect3D &normalize();

    bool isNull() const;
    bool isEmpty() const;
    bool isValid() const;
};

Q_INLINE_TEMPLATE JRect3D::JRect3D(qreal left, qreal floor, qreal back,
                                   qreal right, qreal ceil, qreal front)
    : QGenericMatrix<3, 2, qreal>()
{
    (*this)(0, 0) = left;
    (*this)(0, 1) = floor;
    (*this)(0, 2) = back;
    (*this)(1, 0) = right;
    (*this)(1, 1) = ceil;
    (*this)(1, 2) = front;
}

Q_INLINE_TEMPLATE JRect3D::JRect3D(const QVector3D &minVector, const QVector3D &maxVector)
{
    (*this)(0, 0) = minVector.x();
    (*this)(0, 1) = minVector.y();
    (*this)(0, 2) = minVector.z();
    (*this)(1, 0) = maxVector.x();
    (*this)(1, 1) = maxVector.y();
    (*this)(1, 2) = maxVector.z();
}

Q_INLINE_TEMPLATE QVector3D JRect3D::minVector() const
{
    return QVector3D((*this)(0, 0), (*this)(0, 1), (*this)(0, 2));
}

Q_INLINE_TEMPLATE QVector3D JRect3D::maxVector() const
{
    return QVector3D((*this)(1, 0), (*this)(1, 1), (*this)(1, 2));
}

Q_INLINE_TEMPLATE void JRect3D::setMinVector(const QVector3D &value)
{
    (*this)(0, 0) = value.x();
    (*this)(0, 1) = value.y();
    (*this)(0, 2) = value.z();
}

Q_INLINE_TEMPLATE void JRect3D::setMaxVector(const QVector3D &value)
{
    (*this)(1, 0) = value.x();
    (*this)(1, 1) = value.y();
    (*this)(1, 2) = value.z();
}

Q_INLINE_TEMPLATE QVector3D JRect3D::center() const
{
    return QVector3D(((*this)(0, 0) + (*this)(1, 0)) / 2,
                     ((*this)(0, 1) + (*this)(1, 1)) / 2,
                     ((*this)(0, 2) + (*this)(1, 2)) / 2);
}

Q_INLINE_TEMPLATE JRect3D JRect3D::united(const JRect3D &other) const
{
    return *this | other;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::intersected(const JRect3D &other) const
{
    return *this & other;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator+=(const QVector3D &v)
{
    *this = *this + v;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator-=(const QVector3D &v)
{
    *this = *this - v;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D operator+(const QVector3D &v, const JRect3D &box)
{
    return box + v;
}

Q_INLINE_TEMPLATE JRect3D operator-(const QVector3D &v, const JRect3D &box)
{
    return -box + v;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator |=(const JRect3D &other)
{
    *this = *this | other;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator &=(const JRect3D &other)
{
    *this = *this & other;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator *=(const JRect3D &other)
{
    *this = *this * other;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator /=(const JRect3D &other)
{
    *this = *this / other;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator *=(const QVector3D &v)
{
    *this = *this * v;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator /=(const QVector3D &v)
{
    *this = *this / v;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator *=(qreal factor)
{
    *this = *this * factor;
    return *this;
}

Q_INLINE_TEMPLATE JRect3D JRect3D::operator /=(qreal factor)
{
    *this = *this / factor;
    return *this;
}

Q_INLINE_TEMPLATE bool JRect3D::isNull() const
{
    return qFuzzyCompare((*this)(0, 0), (*this)(1, 0)) &&
            qFuzzyCompare((*this)(0, 1), (*this)(1, 1)) &&
            qFuzzyCompare((*this)(0, 2), (*this)(1, 2));
}

Q_INLINE_TEMPLATE bool JRect3D::isEmpty() const
{
    return (*this)(0, 0) > (*this)(1, 0) ||
            (*this)(0, 1) > (*this)(1, 1) ||
            (*this)(0, 2) > (*this)(1, 2);
}

Q_INLINE_TEMPLATE bool JRect3D::isValid() const
{
    return (*this)(0, 0) <= (*this)(1, 0) ||
            (*this)(0, 1) <= (*this)(1, 1) ||
            (*this)(0, 2) <= (*this)(1, 2);
}

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLMATRIX_H
