#ifndef JPLOT3D_COORD_H
#define JPLOT3D_COORD_H

#include "jplot3d_global.h"
#include "jglobject.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace J3D {

// - class JCoord -

class JCoordPrivate;

class J3D_EXPORT JCoord : public JGLObject
{
    Q_OBJECT
    Q_ENUMS(Axis3D)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QFont labelFont READ labelFont WRITE setLabelFont NOTIFY labelFontChanged)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged)
    Q_PROPERTY(bool lineSmooth READ lineSmooth WRITE setLineSmooth NOTIFY lineSmoothChanged)
    Q_PROPERTY(qreal gridSpacing READ gridSpacing WRITE setGridSpacing NOTIFY gridSpacingChanged)
    Q_PROPERTY(bool tickDrawable READ tickDrawable WRITE setTickDrawable NOTIFY tickDrawableChanged)
    Q_PROPERTY(bool tickMajorDrawable READ tickMajorDrawable WRITE setTickMajorDrawable NOTIFY tickMajorDrawableChanged)
    Q_PROPERTY(bool tickMinorDrawable READ tickMinorDrawable WRITE setTickMinorDrawable NOTIFY tickMinorDrawableChanged)
    Q_PROPERTY(LineHints lineHints READ lineHints WRITE setLineHints NOTIFY lineHintsChanged)
    Q_PROPERTY(SideHints sideHints READ sideHints WRITE setSideHints NOTIFY sideHintsChanged)
public:
    explicit JCoord(QObject *parent = 0);
    virtual ~JCoord();

    enum Axis3D {
        NoAxis = 0x00,
        oAxis = 0x01,
        xAxis = 0x02,
        yAxis = 0x04,
        zAxis = 0x08,

        MajorAxes = xAxis | yAxis | zAxis,
        AllAxes = oAxis | MajorAxes
    };
    Q_DECLARE_FLAGS(Axes3D, Axis3D)

    QColor gridColor() const;
    QColor textColor() const;
    QFont labelFont() const;
    QColor labelColor() const;
    bool lineSmooth() const;
    qreal gridSpacing() const;
    bool tickDrawable() const;
    bool tickMajorDrawable() const;
    bool tickMinorDrawable() const;
    J3D::LineHints lineHints() const;
    J3D::SideHints sideHints() const;

    void setLineWidth(qreal value, qreal majorFactor, qreal minorFactor);
    void setTickLength(qreal major, qreal minor);

    void setAxisLabelHint(JCoord::Axis3D axis, bool visible = true);
    void setAxisLabelHints(JCoord::Axes3D axes);

    QString axisLabel(JCoord::Axis3D axis) const;
    void setAxisLabel(JCoord::Axis3D axis, const QString &text);

    virtual void draw(JGLPainter *painter);

protected:
    virtual void update();

Q_SIGNALS:
    void gridColorChanged(const QColor &);
    void textColorChanged(const QColor &);
    void labelFontChanged(const QFont &);
    void labelColorChanged(const QColor &);
    void lineSmoothChanged(bool);
    void gridSpacingChanged(qreal);
    void tickDrawableChanged(bool);
    void tickMajorDrawableChanged(bool);
    void tickMinorDrawableChanged(bool);
    void lineHintsChanged(J3D::LineHints);
    void sideHintsChanged(J3D::SideHints);

public Q_SLOTS:
    void setGridColor(const QColor &value);
    void setTextColor(const QColor &value);
    void setLabelFont(const QFont &value);
    void setLabelColor(const QColor &value);
    void setLineSmooth(bool value);
    void setGridSpacing(qreal value);
    void setTickDrawable(bool value);
    void setTickMajorDrawable(bool value);
    void setTickMinorDrawable(bool value);
    void setLineHint(J3D::LineHint hint, bool enable);
    void setLineHints(J3D::LineHints value);
    void setSideHint(J3D::SideHint hint, bool enable);
    void setSideHints(J3D::SideHints value);

private:
    Q_DISABLE_COPY(JCoord)
    J_DECLARE_PRIVATE(JCoord)
};

} // - end of namespace J3D

QT_END_NAMESPACE

QT_END_HEADER

#endif // JPLOT3D_COORD_H
