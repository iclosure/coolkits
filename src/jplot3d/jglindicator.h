#ifndef JGLINDICATOR_H
#define JGLINDICATOR_H

#include "jplot3d_global.h"
#include "jglitem.h"
#include <QObject>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JGLIndicator -

class JGLIndicatorPrivate;

class J3D_EXPORT JGLIndicator : public QObject, public JItemBase
{
    Q_OBJECT
    Q_PROPERTY(QQuaternion rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
public:
    explicit JGLIndicator(QObject *parent = 0);
    JGLIndicator(int x, int y, int width, int height, QObject *parent = 0);
    virtual ~JGLIndicator();

    QQuaternion rotation() const;

    static QColor defaultXColor();
    QColor xColor() const;
    void setXColor(const QColor &value);

    static QColor defaultYColor();
    QColor yColor() const;
    void setYColor(const QColor &value);

    static QColor defaultZColor();
    QColor zColor() const;
    void setZColor(const QColor &value);

Q_SIGNALS:
    void rotationChanged(const QQuaternion &);

public Q_SLOTS:
    void setRotation(const QQuaternion &value);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Q_DISABLE_COPY(JGLIndicator)
    J_DECLARE_PRIVATE(JGLIndicator)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLINDICATOR_H
