#include "precomp.h"
#include "jglmatrix.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

// - class JRect3D

/**
 * @brief JRect3D::operator +
 * @param v
 * @return
 */
JRect3D JRect3D::operator-() const
{
    return JRect3D(-(*this)(0, 0),
                   -(*this)(0, 1),
                   -(*this)(0, 2),
                   -(*this)(1, 0),
                   -(*this)(1, 1),
                   -(*this)(1, 2));
}

/**
 * @brief JRect3D::operator +
 * @param v
 * @return
 */
JRect3D JRect3D::operator+(const QVector3D &v) const
{
    return JRect3D((*this)(0, 0) + v.x(),
                   (*this)(0, 1) + v.y(),
                   (*this)(0, 2) + v.z(),
                   (*this)(1, 0) + v.x(),
                   (*this)(1, 1) + v.y(),
                   (*this)(1, 2) + v.z());
}

/**
 * @brief JRect3D::operator -
 * @param v
 * @return
 */
JRect3D JRect3D::operator-(const QVector3D &v) const
{
    return JRect3D((*this)(0, 0) - v.x(),
                   (*this)(0, 1) - v.y(),
                   (*this)(0, 2) - v.z(),
                   (*this)(1, 0) - v.x(),
                   (*this)(1, 1) - v.y(),
                   (*this)(1, 2) - v.z());
}

/**
 * @brief JRect3D::operator |
 * @param other
 * @return
 */
JRect3D JRect3D::operator |(const JRect3D &other) const
{
    return JRect3D(qMin<qreal>((*this)(0, 0), other(0, 0)),
                   qMin<qreal>((*this)(0, 1), other(0, 1)),
                   qMin<qreal>((*this)(0, 2), other(0, 2)),
                   qMax<qreal>((*this)(1, 0), other(1, 0)),
                   qMax<qreal>((*this)(1, 1), other(1, 1)),
                   qMax<qreal>((*this)(1, 2), other(1, 2)));
}

/**
 * @brief JRect3D::operator &
 * @param other
 * @return
 */
JRect3D JRect3D::operator &(const JRect3D &other) const
{
    return JRect3D(qMax<qreal>((*this)(0, 0), other(0, 0)),
                   qMax<qreal>((*this)(0, 1), other(0, 1)),
                   qMax<qreal>((*this)(0, 2), other(0, 2)),
                   qMin<qreal>((*this)(1, 0), other(1, 0)),
                   qMin<qreal>((*this)(1, 1), other(1, 1)),
                   qMin<qreal>((*this)(1, 2), other(1, 2)));
}

/**
 * @brief JRect3D::operator *
 * @param other
 * @return
 */
JRect3D JRect3D::operator *(const JRect3D &other) const
{
    return JRect3D((*this)(0, 0) * other(0, 0),
                   (*this)(0, 1) * other(0, 1),
                   (*this)(0, 2) * other(0, 2),
                   (*this)(1, 0) * other(1, 0),
                   (*this)(1, 1) * other(1, 1),
                   (*this)(1, 2) * other(1, 2));
}

/**
 * @brief JRect3D::operator /
 * @param other
 * @return
 */
JRect3D JRect3D::operator /(const JRect3D &other) const
{
    if (qIsNull(other(0, 0)) ||
            qIsNull(other(0, 1)) ||
            qIsNull(other(0, 2)) ||
            qIsNull(other(1, 0)) ||
            qIsNull(other(1, 1)) ||
            qIsNull(other(1, 2))) {
        return *this;
    }
    return JRect3D((*this)(0, 0) / other(0, 0),
                   (*this)(0, 1) / other(0, 1),
                   (*this)(0, 2) / other(0, 2),
                   (*this)(1, 0) / other(1, 0),
                   (*this)(1, 1) / other(1, 1),
                   (*this)(1, 2) / other(1, 2));
}

/**
 * @brief JRect3D::operator *
 * @param v
 * @return
 */
JRect3D JRect3D::operator *(const QVector3D &v) const
{
    return JRect3D((*this)(0, 0) * v.x(),
                   (*this)(0, 1) * v.y(),
                   (*this)(0, 2) * v.z(),
                   (*this)(1, 0) * v.x(),
                   (*this)(1, 1) * v.y(),
                   (*this)(1, 2) * v.z());
}

/**
 * @brief JRect3D::operator /
 * @param v
 * @return
 */
JRect3D JRect3D::operator /(const QVector3D &v) const
{
    if (v.isNull()) {
        return *this;
    }
    return JRect3D((*this)(0, 0) / v.x(),
                   (*this)(0, 1) / v.y(),
                   (*this)(0, 2) / v.z(),
                   (*this)(1, 0) / v.x(),
                   (*this)(1, 1) / v.y(),
                   (*this)(1, 2) / v.z());
}

/**
 * @brief JRect3D::operator *
 * @param factor
 * @return
 */
JRect3D JRect3D::operator *(qreal factor) const
{
    return JRect3D((*this)(0, 0) * factor,
                   (*this)(0, 1) * factor,
                   (*this)(0, 2) * factor,
                   (*this)(1, 0) * factor,
                   (*this)(1, 1) * factor,
                   (*this)(1, 2) * factor);
}

/**
 * @brief JRect3D::operator /
 * @param factor
 * @return
 */
JRect3D JRect3D::operator /(qreal factor) const
{
    if (qIsNull(factor)) {
        return *this;
    }
    return JRect3D((*this)(0, 0) / factor,
                   (*this)(0, 1) / factor,
                   (*this)(0, 2) / factor,
                   (*this)(1, 0) / factor,
                   (*this)(1, 1) / factor,
                   (*this)(1, 2) / factor);
}

/**
 * @brief J3D::JRect3D::normalized
 * @return
 */
J3D::JRect3D J3D::JRect3D::normalized() const
{
    qreal dx = qFabs((*this)(1, 0) - (*this)(0, 0));
    qreal dy = qFabs((*this)(1, 1) - (*this)(0, 1));
    qreal dz = qFabs((*this)(1, 2) - (*this)(0, 2));
    QVector3D factor(qIsNull(dx) ? 1.0f : 1.0f / dx,
                      qIsNull(dy) ? 1.0f : 1.0f / dy,
                      qIsNull(dz) ? 1.0f : 1.0f / dz);
    return *this * factor;
}

/**
 * @brief J3D::JRect3D::normalize
 * @return
 */
J3D::JRect3D &J3D::JRect3D::normalize()
{
    *this = normalized();
    return *this;
}

QT_END_NAMESPACE
