#include "precomp.h"
#include "jglitem.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JItemBasePrivate

/**
 * @brief The JItemBasePrivate class
 */
class JItemBasePrivate
{
    J_DECLARE_PUBLIC(JItemBase)
    public:
        JItemBasePrivate(JItemBase *parent)
      : q_ptr(parent)
      , size(0.0f, 0.0f)
    {

    }

private:
    void init();

private:
    QSize size;
};

/**
 * @brief JItemBasePrivate::init
 */
void JItemBasePrivate::init()
{
    //Q_Q(JItemBase);
    //q->setFlag(QGraphicsItem::ItemIsMovable, true);
    //q->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //q->setFlag(QGraphicsItem::ItemIsFocusable, true);
    //q->setAcceptHoverEvents(true);
}

J3D_END_NAMESPACE

// - class JItemBase -

/**
 * @brief JItemBase::JItemBase
 * @param x
 * @param y
 * @param width
 * @param height
 */
JItemBase::JItemBase(int x, int y, int width, int height)
    : QGraphicsItem()
    , d_ptr(new JItemBasePrivate(this))
{
    Q_D(JItemBase);
    d->init();
    d->size = QSize(width, height);
    setPos(x, y);
}

/**
 * @brief JItemBase::~JItemBase
 */
JItemBase::~JItemBase()
{
    delete d_ptr;
}

/**
 * @brief JItemBase::boundingRect
 * @return
 */
QRectF JItemBase::boundingRect() const
{
    Q_D(const JItemBase);
    return QRectF(0, -d->size.height(), d->size.width(), d->size.height());
}

/**
 * @brief JItemBase::paint
 * @param painter
 * @param option
 * @param widget
 */
void JItemBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QColor(200, 200, 200, 50));
    painter->drawRoundRect(boundingRect(), 10, 10);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

/**
 * @brief JItemBase::type
 * @return
 */
int JItemBase::type() const
{
    return Type;
}

/**
 * @brief JItemBase::contextMenuEvent
 * @param e
 */
void JItemBase::contextMenuEvent(QGraphicsSceneContextMenuEvent *e)
{
    Q_UNUSED(e);
}

/**
 * @brief JItemBase::mouseMoveEvent
 * @param e
 */
void JItemBase::mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
    Q_UNUSED(e);
}

/**
 * @brief JItemBase::hoverMoveEvent
 * @param e
 */
void JItemBase::hoverMoveEvent(QGraphicsSceneHoverEvent *e)
{
    Q_UNUSED(e);
}

/**
 * @brief JItemBase::mousePressEvent
 * @param e
 */
void JItemBase::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    Q_UNUSED(e);
}

/**
 * @brief JItemBase::mouseReleaseEvent
 * @param e
 */
void JItemBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    Q_UNUSED(e);
}

/**
 * @brief JItemBase::keyPressEvent
 * @param e
 */
void JItemBase::keyPressEvent(QKeyEvent *e)
{
    Q_UNUSED(e);
}

/**
 * @brief JItemBase::wheelEvent
 * @param e
 */
void JItemBase::wheelEvent(QGraphicsSceneWheelEvent *e)
{
    Q_UNUSED(e);
}

QT_END_NAMESPACE
