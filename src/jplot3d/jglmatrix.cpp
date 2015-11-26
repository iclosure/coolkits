#include "precomp.h"
#include "jglmatrix.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

// - class JRect3D

JRect3D JRect3D::operator |(const JRect3D &r) const
{
    if (isNull()) {
        return r;
    }
    if (r.isNull()) {
        return *this;
    }

    // x

    qreal left = xp;
    qreal right = xp;
    if (w < 0.) {
        left += w;
    } else {
        right += w;
    }

    if (r.w < 0.) {
        left = qMin(left, r.xp + r.w);
        right = qMax(right, r.xp);
    } else {
        left = qMin(left, r.xp);
        right = qMax(right, r.xp + r.w);
    }

    // y

    qreal floor = yp;
    qreal ceil = yp;
    if (h < 0.) {
        floor += h;
    } else {
        ceil += h;
    }

    if (r.h < 0.) {
        floor = qMin(floor, r.yp + h);
        ceil = qMax(ceil, r.yp);
    } else {
        floor = qMin(floor, r.yp);
        ceil = qMax(ceil, r.yp + r.h);
    }

    // z

    qreal back = zp;
    qreal front = zp;
    if (l < 0.) {
        back += l;
    } else {
        front += l;
    }

    if (r.l < 0.) {
        back = qMin(back, r.zp + l);
        front = qMax(front, r.zp);
    } else {
        back = qMin(back, r.zp);
        front = qMax(front, r.zp + r.l);
    }

    return JRect3D(left, floor, back, right - left, ceil - floor, front - back);
}

JRect3D JRect3D::operator &(const JRect3D &r) const
{
    // x

    qreal xl1 = xp;
    qreal xr1 = xp;
    if (w < 0.) {
        xl1 += w;
    } else {
        xr1 += w;
    }
    if (xl1 == xr1) { // null rect
        return JRect3D();
    }

    qreal xl2 = r.xp;
    qreal xr2 = r.xp;
    if (r.w < 0.) {
        xl2 += r.w;
    } else {
        xr2 += r.w;
    }
    if (xl2 == xr2) { // null rect
        return JRect3D();
    }

    if (xl1 >= xr2 || xl2 >= xr1) {
        return JRect3D();
    }

    // y

    qreal yf1 = yp;
    qreal yc1 = yp;
    if (h < 0.) {
        yf1 += h;
    } else {
        yc1 += h;
    }
    if (yf1 == yc1) { // null rect
        return JRect3D();
    }

    qreal yf2 = r.yp;
    qreal yc2 = r.yp;
    if (r.h < 0.) {
        yf2 += r.h;
    } else {
        yc2 += r.h;
    }
    if (yf2 == yc2) { // null rect
        return JRect3D();
    }

    if (yf1 >= yc2 || yf2 >= yc1) {
        return JRect3D();
    }

    // z

    qreal zb1 = zp;
    qreal zf1 = zp;
    if (l < 0.) {
        zb1 += l;
    } else {
        zf1 += l;
    }
    if (zb1 == zf1) { // null rect
        return JRect3D();
    }

    qreal zb2 = r.zp;
    qreal zf2 = r.zp;
    if (r.l < 0.) {
        zb2 += r.l;
    } else {
        zf2 += r.l;
    }
    if (zb2 == zf2) { // null rect
        return JRect3D();
    }

    if (zb1 >= zf2 || zb2 >= zf1) {
        return JRect3D();
    }

    JRect3D tmp;
    tmp.xp = qMax(xl1, xl2);
    tmp.yp = qMax(yf1, yf2);
    tmp.zp = qMax(zb1, zb2);
    tmp.w = qMin(xr1, xr2) - tmp.xp;
    tmp.h = qMin(yc1, yc2) - tmp.yp;
    tmp.l = qMin(zf1, zf2) - tmp.zp;
    return tmp;
}

bool JRect3D::contains(const QVector3D &p) const
{
    // x

    qreal left = xp;
    qreal right = xp;
    if (w < 0.) {
        left += w;
    } else {
        right += w;
    }
    if (left == right) {
        return false;
    }
    if (p.x() < left || p.x() > right) {
        return false;
    }

    // y

    qreal floor = yp;
    qreal ceil = yp;
    if (h < 0.) {
        floor += h;
    } else {
        ceil += h;
    }
    if (floor == ceil) {
        return false;
    }
    if (p.y() < floor || p.y() > ceil) {
        return false;
    }

    // z

    qreal back = zp;
    qreal front = zp;
    if (l < 0.) {
        back += l;
    } else {
        front += l;
    }
    if (back == front) {
        return false;
    }
    if (p.z() < back || p.z() > front) {
        return false;
    }

    return true;
}

bool JRect3D::contains(const JRect3D &r) const
{
    // x

    qreal left1 = xp;
    qreal right1 = xp;
    if (w < 0.) {
        left1 += w;
    } else {
        right1 += w;
    }
    if (left1 == right1) {
        return false;
    }

    qreal left2 = r.xp;
    qreal right2 = r.xp;
    if (r.w < 0.) {
        left1 += r.w;
    } else {
        right2 += r.w;
    }
    if (left2 == right2) {
        return false;
    }
    if (left2 < left1 || right2 > right1) {
        return false;
    }

    // y

    qreal floor1 = yp;
    qreal ceil1 = yp;
    if (h < 0.) {
        floor1 += h;
    } else {
        ceil1 += h;
    }
    if (floor1 == ceil1) {
        return false;
    }

    qreal floor2 = r.yp;
    qreal ceil2 = r.yp;
    if (r.h < 0.) {
        floor1 += r.h;
    } else {
        ceil2 += r.h;
    }
    if (floor2 == ceil2) {
        return false;
    }
    if (floor2 < floor1 || ceil2 > ceil1) {
        return false;
    }

    // z

    qreal back1 = zp;
    qreal front1 = zp;
    if (l < 0.) {
        back1 += l;
    } else {
        front1 += l;
    }
    if (back1 == front1) {
        return false;
    }

    qreal back2 = r.zp;
    qreal front2 = r.zp;
    if (r.l < 0.) {
        back1 += r.l;
    } else {
        front2 += r.l;
    }
    if (back2 == front2) {
        return false;
    }
    if (back2 < back1 || front2 > front1) {
        return false;
    }

    return true;
}

bool JRect3D::intersects(const JRect3D &r) const
{
    // x

    qreal left1 = xp;
    qreal right1 = xp;
    if (w < 0.) {
        left1 += w;
    } else {
        right1 += w;
    }
    if (left1 == right1) {
        return false;
    }

    qreal left2 = r.xp;
    qreal right2 = r.xp;
    if (r.w < 0.) {
        left1 += r.w;
    } else {
        right2 += r.w;
    }
    if (left2 == right2) {
        return false;
    }
    if (left1 >= right2 || left2 >= right1) {
        return false;
    }

    // y

    qreal floor1 = yp;
    qreal ceil1 = yp;
    if (h < 0.) {
        floor1 += h;
    } else {
        ceil1 += h;
    }
    if (floor1 == ceil1) {
        return false;
    }

    qreal floor2 = r.yp;
    qreal ceil2 = r.yp;
    if (r.h < 0.) {
        floor1 += r.h;
    } else {
        ceil2 += r.h;
    }
    if (floor2 == ceil2) {
        return false;
    }
    if (floor1 >= ceil2 || floor2 >= ceil1) {
        return false;
    }

    // z

    qreal back1 = zp;
    qreal front1 = zp;
    if (l < 0.) {
        back1 += l;
    } else {
        front1 += l;
    }
    if (back1 == front1) {
        return false;
    }

    qreal back2 = r.zp;
    qreal front2 = r.zp;
    if (r.l < 0.) {
        back1 += r.l;
    } else {
        front2 += r.l;
    }
    if (back2 == front2) {
        return false;
    }
    if (back1 >= front2 || back2 >= front1) {
        return false;
    }

    return true;
}

JRect3D JRect3D::intersect0(const JRect3D &r) const
{
    // x

    qreal xl1 = xp;
    qreal xr1 = xp;
    if (w < 0.) {
        xl1 += w;
    } else {
        xr1 += w;
    }
    if (xl1 > xr1) { // null rect
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    qreal xl2 = r.xp;
    qreal xr2 = r.xp;
    if (r.w < 0.) {
        xl2 += r.w;
    } else {
        xr2 += r.w;
    }
    if (xl2 > xr2) { // null rect
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    if (xl1 > xr2 || xl2 > xr1) {
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    // y

    qreal yf1 = yp;
    qreal yc1 = yp;
    if (h < 0.) {
        yf1 += h;
    } else {
        yc1 += h;
    }
    if (yf1 > yc1) { // null rect
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    qreal yf2 = r.yp;
    qreal yc2 = r.yp;
    if (r.h < 0.) {
        yf2 += r.h;
    } else {
        yc2 += r.h;
    }
    if (yf2 > yc2) { // null rect
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    if (yf1 > yc2 || yf2 > yc1) {
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    // z

    qreal zb1 = zp;
    qreal zf1 = zp;
    if (l < 0.) {
        zb1 += l;
    } else {
        zf1 += l;
    }
    if (zb1 > zf1) { // null rect
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    qreal zb2 = r.zp;
    qreal zf2 = r.zp;
    if (r.l < 0.) {
        zb2 += r.l;
    } else {
        zf2 += r.l;
    }
    if (zb2 > zf2) { // null rect
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    if (zb1 > zf2 || zb2 > zf1) {
        return JRect3D(0, 0, 0, -1, -1, -1);
    }

    JRect3D tmp;
    tmp.xp = qMax(xl1, xl2);
    tmp.yp = qMax(yf1, yf2);
    tmp.zp = qMax(zb1, zb2);
    tmp.w = qMin(xr1, xr2) - tmp.xp;
    tmp.h = qMin(yc1, yc2) - tmp.yp;
    tmp.l = qMin(zf1, zf2) - tmp.zp;
    return tmp;
}

/**
 * @brief J3D::JRect3D::normalized
 * @return
 */
J3D::JRect3D J3D::JRect3D::normalized() const
{
    QVector3D factor(qIsNull(w) ? 1.0f : 1.0f / w,
                     qIsNull(h) ? 1.0f : 1.0f / h,
                     qIsNull(l) ? 1.0f : 1.0f / l);
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
