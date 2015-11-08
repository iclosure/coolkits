#ifndef JGLITEM_H
#define JGLITEM_H

#include "jplot3d_global.h"
#include <QGraphicsItem>
#include <QVector3D>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JItemBase -

class JItemBasePrivate;

class J3D_EXPORT JItemBase : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    JItemBase(int x, int y, int width, int height);
    virtual ~JItemBase();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual int type() const;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *e);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *e);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *e);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void wheelEvent(QGraphicsSceneWheelEvent *e);

private:
    Q_DISABLE_COPY(JItemBase)
    J_DECLARE_PRIVATE(JItemBase)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JGLITEM_H
