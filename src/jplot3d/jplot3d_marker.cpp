#include "precomp.h"
#include "jplot3d_marker.h"
#include "jglscene.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JMarkerPrivate -

/**
 * @brief The JMarkerPrivate class
 */
class JMarkerPrivate
{
    J_DECLARE_PUBLIC(JMarker)
public:
    JMarkerPrivate(JGLScene *jscene, JMarker *parent)
        : q_ptr(parent)
        , jscene(jscene)
    {

    }

private:
    void init();

private:
    JGLScene *jscene;
    QLabel *label;
};

/**
 * @brief JMarkerPrivate::init
 */
void JMarkerPrivate::init()
{
    Q_Q(JMarker);
    q->setObjectName("JMarker");
    q->setWindowOpacity(0.99);

    QHBoxLayout *horiLayourMain = new QHBoxLayout(q);
    horiLayourMain->setContentsMargins(0, 0, 0, 0);

    label = new QLabel(q);
    label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    label->setFont(QFont("Consolas", 12));
    horiLayourMain->addWidget(label);
}

J3D_END_NAMESPACE

// - class JMarker -

/**
 * @brief JMarker::JMarker
 * @param jscene
 * @param parent
 */
JMarker::JMarker(JGLScene *jscene, QWidget *parent)
    : QWidget(parent)
    , d_ptr(new JMarkerPrivate(jscene, this))
{
    Q_D(JMarker);
    d->init();
    setMinimumWidth(80);
}

/**
 * @brief JMarker::~JMarker
 *
 */
JMarker::~JMarker()
{
    delete d_ptr;
}

/**
 * @brief JMarker::text
 * @return
 */
QString JMarker::text() const
{
    Q_D(const JMarker);
    return d->label->text();
}

/**
 * @brief JMarker::jscene
 * @return
 */
JGLScene *JMarker::jscene() const
{
    Q_D(const JMarker);
    return d->jscene;
}

/**
 * @brief JMarker::setText
 * @param text
 */
void JMarker::setText(const QString &text)
{
    Q_D(JMarker);
    if (d->label->text() != text) {
        d->label->setText(text);
        adjustSize();
        Q_EMIT textChanged(text);
    }
}

QT_END_NAMESPACE
