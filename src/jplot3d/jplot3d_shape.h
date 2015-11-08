#ifndef JPLOT3D_SHAPE_H
#define JPLOT3D_SHAPE_H

#include "jplot3d_global.h"
#include "jplot3d_shapeitem.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JShape -

class JShapePrivate;
class JGLPainter;
class JGLAbstractScene;

class J3D_EXPORT JShape : public JGLObject
{
    Q_OBJECT
public:
    explicit JShape(QObject *parent = 0);
    virtual ~JShape();

    void addPoint(const QString &identity, const QVector3D &pos,
                  const QColor &color, qreal size = 1.0f);
    void addLine(const QString &identity, const QVector3D &minVector,
                 const QVector3D &maxVector, const QColor &color,
                 qreal width = 1.0f);
    void addLine(const QString &identity, const JRect3D &box, const QColor &color,
                 qreal width = 1.0f);
    void addBox(const QString &identity, const QVector3D &minVector,
                const QVector3D &maxVector, const QColor &color);
    void addBox(const QString &identity, const JRect3D &box, const QColor &color);
    void addCircle(const QString &identity, const QVector3D &pos,
                   qreal radius, const QColor &color, int slices = 36, int stacks = 36);
    void setEllipse(const QString &identity, const JRect3D &box,
                    const QColor &color, int slices = 36, int stacks = 36);

    JShapeItem *findShape(unsigned int objectId) const;
    JShapeItem *findShape(const QString &identity) const;
    void removeShape(unsigned int objectId);
    void removeShape(const QString &identity);
    void removeShape(JShapeItem *item);
    void clearShape();

    JShapeItem *currentShape() const;
    void setCurrentShape(unsigned int id);
    void setCurrentShape(const QString &identity);
    void setCurrentShape(JShapeItem *item);

    virtual void initialize(JGLScene *scene);
    virtual void draw(JGLPainter *painter);

    void attach(QObject *object);
    void detach();

Q_SIGNALS:
    void currentShapeChanged(const QString &);

public Q_SLOTS:
    void sceneDoubleClicked();
    void objectPressed();
    void objectClicked();
    void objectReleased();
    void objectDoubleClicked();
    void objectEntered();
    void objectLeft();

private:
    Q_DISABLE_COPY(JShape)
    J_DECLARE_PRIVATE(JShape)
};

Q_INLINE_TEMPLATE
void JShape::addLine(const QString &identity, const JRect3D &box, const QColor &color, qreal width)
{
    addLine(identity, box.minVector(), box.maxVector(), color, width);
}

Q_INLINE_TEMPLATE
void JShape::addBox(const QString &identity, const JRect3D &box, const QColor &color)
{
    addBox(identity, box.minVector(), box.maxVector(), color);
}

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_SHAPE_H
