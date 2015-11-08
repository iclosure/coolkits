#ifndef JPLOT3D_SHAPEITEM_H
#define JPLOT3D_SHAPEITEM_H

#include "jplot3d_global.h"
#include "jglmatrix.h"
#include "jglobject.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JShapeItem -

class JShapeItemPrivate;

class J3D_EXPORT JShapeItem : public JGLObject
{
    Q_OBJECT
    Q_ENUMS(ShapeType)
    Q_PROPERTY(ShapeType shapeType READ shapeType)
public:
    explicit JShapeItem(QObject *parent = 0);
    explicit JShapeItem(const QString &identity, const QColor &color, QObject *parent = 0);
    virtual ~JShapeItem();

    enum ShapeType {
        NoShape,
        ShapePoint,
        ShapeLine,
        ShapePlane,
        ShapeBox,
        ShapeEllipse
    };

    ShapeType shapeType() const;

    void setPoint(const QVector3D &pos, qreal size = 1.0f);
    void setLine(const QVector3D &minVector, const QVector3D &maxVector, qreal width = 1.0f);
    void setLine(const JRect3D &box, qreal width = 1.0f);
    void setBox(const QVector3D &minVector, const QVector3D &maxVector);
    void setBox(const JRect3D &box);
    void setCircle(const QVector3D &pos, qreal radius, int slices = 36, int stacks = 36);
    void setEllipse(const JRect3D &box, int slices = 36, int stacks = 36);

    void setPointSize(qreal size);
    void setLineWidth(qreal width);

public:
    virtual void draw(JGLPainter *painter);
    virtual void update();

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JShapeItem)
    J_DECLARE_PRIVATE(JShapeItem)
};

Q_INLINE_TEMPLATE
void JShapeItem::setLine(const JRect3D &box, qreal width)
{
    setLine(box.minVector(), box.maxVector(), width);
}

Q_INLINE_TEMPLATE
void JShapeItem::setBox(const JRect3D &box)
{
    setBox(box.minVector(), box.maxVector());
}

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_SHAPEITEM_H
