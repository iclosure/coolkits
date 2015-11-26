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
class JGLScene;

class J3D_EXPORT JShape : public JGLObject
{
    Q_OBJECT
public:
    explicit JShape(QObject *parent = 0);
    virtual ~JShape();

    JShapeItem *addPoint(const QString &identity, const QVector3D &pos,
                         const QColor &color, qreal size = 1.0f);
    JShapeItem *addLine(const QString &identity, const JRect3D &box, const QColor &color,
                        qreal width = 1.0f);
    inline JShapeItem *addLine(const QString &identity, const QVector3D &minVector,
                               const QVector3D &maxVector, const QColor &color,
                               qreal width = 1.0f);
    JShapeItem *addPlane(const QString &identity, const JRect3D &box, const QColor &color);
    inline JShapeItem *addPlane(const QString &identity, const QVector3D &minVector,
                         const QVector3D &maxVector, const QColor &color);
    JShapeItem *addBox(const QString &identity, const JRect3D &box, const QColor &color);
    inline JShapeItem *addBox(const QString &identity, const QVector3D &minVector,
                const QVector3D &maxVector, const QColor &color);
    JShapeItem *addCircle(const QString &identity, const QVector3D &pos,
                   qreal radius, const QColor &color, int slices = 36, int stacks = 36);
    JShapeItem *addEllipse(const QString &identity, const JRect3D &box,
                    const QColor &color, int slices = 36, int stacks = 36);

    JShapeItem *findShape(unsigned int objectId) const;
    JShapeItem *findShape(const QString &identity) const;
    void removeShape(unsigned int objectId);
    void removeShape(const QString &identity);
    void removeShape(JShapeItem *item);
    void clearShape();

    QList<JShapeItem *> shapes() const;
    JShapeItem *currentShape() const;
    void setCurrentShape(unsigned int id);
    void setCurrentShape(const QString &identity);
    void setCurrentShape(JShapeItem *item);

    virtual void initialize(JGLScene *scene);
    virtual void draw(JGLPainter *painter);

    void attach(QObject *object);
    void detach();

    JGLScene *jscene() const;

    QVariant itemData(const QString &identity, int role = Qt::UserRole + 1) const;
    void setItemData(const QString &identity, const QVariant &value, int role = Qt::UserRole + 1);

Q_SIGNALS:
    void autoScaleChanged(bool);
    void currentItemChanged(const QString &);
    void clearPicked();
    void itemColorChanged(const QString &identity, const QColor &);
    void itemPressed(const QString &identity);
    void itemClicked(const QString &identity);
    void itemReleased(const QString &identity);
    void itemDoubleClicked(const QString &identity);
    void itemEntered(const QString &identity);
    void itemLeft(const QString &identity);
    void itemRightPressed(const QString &identity);
    void itemRightClicked(const QString &identity);

public Q_SLOTS:
    void sceneDoubleClicked();

private Q_SLOTS:
    void _emit_itemColorChanged(const QColor &color);
    void _emit_itemPressed();
    void _emit_itemClicked();
    void _emit_itemReleased();
    void _emit_itemDoubleClicked();
    void _emit_itemEntered();
    void _emit_itemLeft();
    void _emit_itemRightPressed();
    void _emit_itemRightClicked();

private:
    Q_DISABLE_COPY(JShape)
    J_DECLARE_PRIVATE(JShape)
};

/**
 * @brief JShape::addPlane
 * @param identity
 * @param minVector
 * @param maxVector
 * @param color
 * @return
 */
Q_INLINE_TEMPLATE
JShapeItem *JShape::addLine(const QString &identity,
                            const QVector3D &minVector,
                            const QVector3D &maxVector,
                            const QColor &color,
                            qreal width)
{
    return addLine(identity, JRect3D(minVector, maxVector), color, width);
}

/**
 * @brief JShape::addPlane
 * @param identity
 * @param minVector
 * @param maxVector
 * @param color
 * @return
 */
Q_INLINE_TEMPLATE
JShapeItem *JShape::addPlane(const QString &identity,
                             const QVector3D &minVector,
                             const QVector3D &maxVector,
                             const QColor &color)
{
    return addPlane(identity, JRect3D(minVector, maxVector), color);
}

/**
 * @brief JShape::addBox
 * @param identity
 * @param minVector
 * @param maxVector
 * @param color
 * @return
 */
Q_INLINE_TEMPLATE
JShapeItem *JShape::addBox(const QString &identity,
                           const QVector3D &minVector,
                           const QVector3D &maxVector,
                           const QColor &color)
{
    return addBox(identity, JRect3D(minVector, maxVector), color);
}

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_SHAPE_H
