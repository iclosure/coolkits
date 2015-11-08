#include "precomp.h"
#include "jglscale.h"
#include "jglanimation.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

#ifndef DBL_EPSILON
#define DBL_EPSILON 2.2204460492503131e-016
#endif

#ifndef DBL_MIN
#define DBL_MIN     2.2250738585072014e-308
#endif

// - class JGLScalePrivate -

/**
 * @brief The JGLScalePrivate class
 */
class JGLScalePrivate
{
    J_DECLARE_PUBLIC(JGLScale)
public:
    JGLScalePrivate(JGLScale *parent)
      : q_ptr(parent)
      , scale(1.0f, 1.0f, 1.0f)
      , autoScale(true)
    {
        mantissi.push_back(1);
        mantissi.push_back(2);
        mantissi.push_back(5);
    }

    static bool isNull(qreal a, qreal b = 0)
    {
        if (!b) {
            return (fabs(a) <= DBL_MIN);
        } else {
            return (fabs(a - b) <= qMin<qreal>(fabs(a), fabs(b)) * DBL_EPSILON);
        }
    }

    static qreal floorExt(int &exponent, qreal x, const std::vector<qreal> &sortedMantissi);
    static qreal floor125(int &exponent, qreal x);
    static qreal anchorValue(qreal start, qreal m, int n);
    static int segments(int &l_intervals, int &r_intervals,
                        qreal start, qreal stop, qreal anchor, qreal m, int n);
    int execute(qreal &a, qreal &b, qreal start, qreal stop, int intervals);
    static int execute(qreal &a, qreal &b, qreal start, qreal stop, int intervals,
                       const std::vector<qreal> &mantissi);
    int autoScaled(qreal &new_start, qreal &new_stop, qreal start, qreal stop, int intervals);
    static int autoScaled(qreal &new_start, qreal &new_stop, qreal start, qreal stop, int intervals,
                          const std::vector<qreal> &mantissi);

    static JRect3D defaultRange()
    { return JRect3D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }

private:
    void init();

private:
    QVector3D scale;
    bool autoScale;
    std::vector<qreal> mantissi;
};

/**
 * @brief JGLScalePrivate::floorExt
 * @param exponent
 * @param x
 * @param sortedMantissi
 * @return
 */
qreal JGLScalePrivate::floorExt(int &exponent, qreal x, const std::vector<qreal> &sortedMantissi)
{
    if (x == 0.0) {
        exponent = 0;
        return 0.0f;
    }

    qreal sign = (x > 0) ? 1.0f: -1.0f;
    qreal lx = log10(fabs(x));
    exponent = (int)floor(lx);
    qreal fr = pow(10.0, lx - exponent);
    if (fr >= 10.0) {
        fr = 1.0;
        ++exponent;
    } else {
        for (int i = (int)sortedMantissi.size() - 1; i >= 0; --i) {
            if (fr >= sortedMantissi[i]) {
                fr = sortedMantissi[i];
                break;
            }
        }
    }

    return sign * fr;
}

/**
 * @brief JGLScalePrivate::floor125
 * @param exponent
 * @param x
 * @return
 */
qreal JGLScalePrivate::floor125(int &exponent, qreal x)
{
    std::vector<qreal> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(5);
    return floorExt(exponent, x, m);
}

/**
 * @brief JGLScalePrivate::anchorValue
 * @param start
 * @param m
 * @param n
 * @return
 */
qreal JGLScalePrivate::anchorValue(qreal start, qreal m, int n)
{
    qreal stepVal = m * pow(10.0, n);
    return stepVal * ceil(start / stepVal);
}

/**
 * @brief JGLScalePrivate::segments
 * @param l_intervals
 * @param r_intervals
 * @param start
 * @param stop
 * @param anchor
 * @param m
 * @param n
 * @return
 */
int JGLScalePrivate::segments(int &l_intervals, int &r_intervals,
                              qreal start, qreal stop, qreal anchor, qreal m, int n)
{
    qreal val = m * pow(10.0, n);
    qreal delta = (stop - anchor) / val;
    r_intervals = (int)floor(delta);   // right side intervals
    delta = (anchor - start) / val;
    l_intervals = (int)floor(delta);   // left side intervals
    return r_intervals + l_intervals;
}

/**
 * @brief JGLScalePrivate::execute
 * @param a
 * @param b
 * @param start
 * @param stop
 * @param intervals
 * @return
 */
int JGLScalePrivate::execute(qreal &a, qreal &b, qreal start, qreal stop, int intervals)
{
    return execute(a, b, start, stop, intervals, mantissi);
}

/**
 * @brief JGLScalePrivate::execute
 * @param a
 * @param b
 * @param start
 * @param stop
 * @param intervals
 * @param sortedMantissi
 * @return
 */
int JGLScalePrivate::execute(qreal &a, qreal &b, qreal start, qreal stop,
                             int intervals, const std::vector<qreal> &mantissi)
{
    a = start;
    b = stop;
    if (intervals < 1) {
        intervals = 1;
    }

    qreal delta = qFabs(stop - start);
    if (isNull(delta)) {
        return intervals;
    }

    int n;
    qreal c = floorExt(n, delta, mantissi);
    int l_ival, r_ival;
    qreal anchor = anchorValue(start, c, n);
    int ival = segments(l_ival, r_ival, start, stop, anchor, c, n);
    if (ival >= intervals) {
        a = anchor - l_ival * c * pow(10.0, n);
        b = anchor + r_ival * c * pow(10.0, n);
        intervals = ival;
        return intervals;
    }

    int prev_ival, prev_l_ival, prev_r_ival;
    qreal prev_anchor;
    qreal prev_c;
    int prev_n;
    while(true) {
        prev_c = c;
        prev_n = n;
        prev_anchor = anchor;
        prev_ival = ival;
        prev_l_ival = l_ival;
        prev_r_ival = r_ival;
        if (int(c) == 1) {
            c = mantissi.back();
            --n;
        } else {
            for (unsigned int i = (unsigned int)mantissi.size() - 1; i > 0; --i) {
                if (int(c) == mantissi[i]) {
                    c = mantissi[i - 1];
                    break;
                }
            }
        }
        anchor = anchorValue(start, c, n);
        ival = segments(l_ival, r_ival, start, stop, anchor, c, n);
        int prev_diff = intervals - prev_ival;
        int actual_diff = ival - intervals;
        if (prev_diff >= 0 && actual_diff >= 0) {
            if (prev_diff < actual_diff) {
                n = prev_n;
                c = prev_c;
                anchor = prev_anchor;
                ival = prev_ival;
                l_ival = prev_l_ival;
                r_ival = prev_r_ival;
            }

            a = anchor - l_ival * c * pow(10.0, n);
            b = anchor + r_ival * c * pow(10.0, n);
            intervals = ival;
            break;
        }
    }

    return intervals;
}

/**
 * @brief JGLScalePrivate::autoScaled
 * @param new_start
 * @param new_stop
 * @param start
 * @param stop
 * @param intervals
 * @return
 */
int JGLScalePrivate::autoScaled(qreal &new_start, qreal &new_stop, qreal start, qreal stop, int intervals)
{
    return autoScaled(new_start, new_stop, start, stop, intervals, mantissi);
}

/**
 * @brief JGLScalePrivate::autoScaled
 * @param new_start
 * @param new_stop
 * @param start
 * @param stop
 * @param intervals
 * @param mantissi
 * @return
 */
int JGLScalePrivate::autoScaled(qreal &new_start, qreal &new_stop, qreal start, qreal stop,
                                int intervals, const std::vector<qreal> &mantissi)
{
    int number = execute(new_start, new_stop, start, stop, intervals, mantissi);
    if (number == 0) {
        return number;
    }

    qreal step = (new_stop - new_start) / number;
    if (new_start > start) {
        new_start -= step;
        ++number;
    }
    if (new_stop < stop) {
        new_stop += step;
        ++number;
    }

    return number;
}

/**
 * @brief JGLScalePrivate::init
 */
void JGLScalePrivate::init()
{
    Q_Q(JGLScale);
    q->setObjectName("JGLScane");
}

J3D_END_NAMESPACE

// - class JGLScale -

/**
 * @brief JGLScale::JGLScale
 * @param parent
 */
JGLScale::JGLScale(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JGLScalePrivate(this))
{
    Q_D(JGLScale);
    d->init();
}

/**
 * @brief JGLScale::~JGLScale
 */
JGLScale::~JGLScale()
{
    delete d_ptr;
}

/**
 * @brief JGLScale::draw
 * @param painter
 */
void JGLScale::draw(JGLPainter *painter)
{
    Q_UNUSED(painter);

    JGLObject::draw(painter);
}

/**
 * @brief JGLScale::autoScale
 * @return
 */
bool JGLScale::autoScale() const
{
    Q_D(const JGLScale);
    return d->autoScale;
}

/**
 * @brief JGLScale::resetRange
 */
void JGLScale::resetRange()
{
    setRange(JGLScalePrivate::defaultRange());
}

/**
 * @brief JGLScale::normalized
 * @param box
 * @return
 */
JRect3D JGLScale::normalized(const JRect3D &box)
{
    std::vector<qreal> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(5);

    JRect3D range = box;
    JGLScalePrivate::autoScaled(range(0, 0), range(1, 0), range.left(), range.right(), 5, m);
    JGLScalePrivate::autoScaled(range(0, 1), range(1, 1), range.floor(), range.ceil(), 5, m);
    JGLScalePrivate::autoScaled(range(0, 2), range(1, 2), range.back(), range.front(), 5, m);

    qreal dx = range.dx(), dy = range.dy(), dz = range.dz();
    QVector3D factor(qIsNull(dx) ? 1.0f : 1.0f / dx,
                     qIsNull(dy) ? 1.0f : 1.0f / dy,
                     qIsNull(dz) ? 1.0f : 1.0f / dz);

    return (box + range.minVector()) * factor;
}

/**
 * @brief JGLScale::update
 */
void JGLScale::update()
{
    JGLObject::update();
}

/**
 * @brief JGLScale::setAutoScale
 * @param value
 */
void JGLScale::setAutoScale(bool value)
{
    Q_D(JGLScale);
    if (value != d->autoScale) {
        d->autoScale = value;
        Q_EMIT autoScaleChanged(value);
        setScaleVector(QVector3D(1.0f, 1.0f, 1.0f));
    }
}

/**
 * @brief JGLScale::setRange
 * @param value
 * @param animation
 */
void JGLScale::setRange(const JRect3D &value, bool animation)
{
    Q_D(JGLScale);
    if (!d->autoScale) {
        return;
    }

    if (value != box()) {
        JRect3D range = value;
        d->autoScaled(range(0, 0), range(1, 0), range.left(), range.right(), 5);
        d->autoScaled(range(0, 1), range(1, 1), range.floor(), range.ceil(), 5);
        d->autoScaled(range(0, 2), range(1, 2), range.back(), range.front(), 5);

        qreal dx = range.dx(), dy = range.dy(), dz = range.dz();
        QVector3D factor(qIsNull(dx) ? 1.0f : 1.0f / dx,
                         qIsNull(dy) ? 1.0f : 1.0f / dy,
                         qIsNull(dz) ? 1.0f : 1.0f / dz);

        setBox(range);
        setOffsetVector(-range.minVector(), animation);
        setScaleVector(factor, animation);
    }
}

QT_END_NAMESPACE
