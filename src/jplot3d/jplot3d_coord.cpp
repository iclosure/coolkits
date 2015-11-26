#include "precomp.h"
#include "jplot3d_coord.h"
#include "jglindicator.h"
#include "jglpainter.h"
#include "jglfont.h"

QT_BEGIN_NAMESPACE

J3D_USE_NAMESPACE

J3D_BEGIN_NAMESPACE

// - class JCoordPrivate -

// grid data

static const GLfloat _vertex_grid_area[] =
{
    // left
    1.0f, 0.0f, 0.0f,   // normalize
    0.0f, 0.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.04f,
    0.0f, 1.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.24f,
    0.0f, 1.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.04f,
    0.0f, 0.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    0.0f, 0.0f, 1.0f,   // reverse
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    // right
    -1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.04f,
    1.0f, 1.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.24f,
    1.0f, 1.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.04f,
    1.0f, 0.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    // floor
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.31f,
    0.0f, 0.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    1.0f, 0.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    1.0f, 0.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.59f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    // ceil
    0.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.31f,
    0.0f, 1.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    1.0f, 1.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    1.0f, 1.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.59f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    // back
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.31f,
    1.0f, 0.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.20f,
    1.0f, 1.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    0.0f, 1.0f, 0.0f, 0.27f, 0.27f, 0.78f, 0.20f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    // front
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.31f,
    1.0f, 0.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.20f,
    1.0f, 1.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.00f,
    0.0f, 1.0f, 1.0f, 0.27f, 0.27f, 0.78f, 0.20f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

//
enum VertexGridLineArea
{
    VertextGridAreaLeft = 0,
    VertextGridAreaRight = 43,
    VertextGridAreaFloor = 86,
    VertextGridAreaCeil = 129,
    VertextGridAreaBack = 172,
    VertextGridAreaFront = 215,
};

/**
 * @brief The JCoordPrivate class
 */
class JCoordPrivate
{
    J_DECLARE_PUBLIC(JCoord)
public:
    JCoordPrivate(JCoord *parent)
        : q_ptr(parent)
        , areaDrawable(defaultAreaDrawable())
        , vertexRadius(defaultVertexRadius())
        , vertexColor(defaultVertexColor())
        , gridColor(defaultGridColor())
        , textColor(defaultTextColor())
        , lineSmooth(true)
        , gridSpacing(defaultGridSpacing())
        , tickDrawable(false)
        , tickMajorDrawable(false)
        , tickMinorDrawable(false)
        , lineHints(defaultLineHints())
        , sideHints(defaultSideHints())
        , labelFont(QApplication::font())
        , labelColor(defaultGridColor())
        , lineWidth(1.f)
        , lineMajorFactor(0.030f)
        , lineMinorFactor(0.015f)
        , tickLengthMajor(0.015f)
        , tickLengthMinor(tickLengthMajor * 0.5f)
        , interval(5, 5, 5)
        , axesLabel(defaultAxesLabel())
        , oAxisLabel("o")
        , xAxisLabel("x")
        , yAxisLabel("y")
        , zAxisLabel("z")
    {

    }

    static bool defaultAreaDrawable() { return true; }
    static qreal defaultVertexRadius() { return 0.008f; }
    static QColor defaultVertexColor() { return QColor(150, 150, 150, 255); }
    static QColor defaultGridColor() { return QColor(150, 150, 150, 255); }
    static QColor defaultTextColor() { return QColor(200, 200, 200, 255); }
    static qreal defaultGridSpacing() { return 0.1f; }
    static J3D::LineHints defaultLineHints() { return J3D::MajorLines; }
    static J3D::SideHints defaultSideHints() { return J3D::MajorSides; }
    static JCoord::Axes3D defaultAxesLabel() { return JCoord::AllAxes; }

    qreal scaledValue(qreal delta, qreal value, qreal e = 1e-4)
    { return (qFabs(delta) >= 1.0f && qFabs(value) < e) ? 0.0f : value; }

private:
    void init();
    void update();

    void genCoordList();
    void genGridLists();
    void genTickList();
    void createGridSideList(const QVector<QVector3D> &vertexes);
    void createGridSideAreaList(const GLfloat *vertexes);

private:
    bool areaDrawable;
    qreal vertexRadius;
    QColor vertexColor;
    QColor gridColor;
    QColor textColor;
    bool lineSmooth;
    qreal gridSpacing;
    bool tickDrawable;
    bool tickMajorDrawable;
    bool tickMinorDrawable;
    J3D::LineHints lineHints;
    J3D::SideHints sideHints;

    QFont labelFont;
    QColor labelColor;
    qreal lineWidth, lineMajorFactor, lineMinorFactor;
    qreal tickLengthMajor, tickLengthMinor;
    QVector3D interval;
    JCoord::Axes3D axesLabel;
    QString oAxisLabel, xAxisLabel, yAxisLabel, zAxisLabel;

    GLuint gridListId;
};

/**
 * @brief JCoordPrivate::init
 */
void JCoordPrivate::init()
{
    Q_Q(JCoord);
    q->setObjectName("JCoord");
    update();
}

/**
 * @brief JCoordPrivate::update
 */
void JCoordPrivate::update()
{
    Q_Q(JCoord);

    if (!q->beginContext()) {
        return;
    }

    if (q->isDirty()) {
        q->setGLListId(glGenLists(1));
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    glNewList(q->glListId(), GL_COMPILE);

    //
    genCoordList();
    //
    if (tickDrawable && (tickMajorDrawable || tickMinorDrawable)) {
        genTickList();
    }
    //
    genGridLists();

    glEndList();

    glDisableClientState(GL_VERTEX_ARRAY);

    if (!q->doneContext()) {
        return;
    }
}

/**
 * @brief JCoordPrivate::genCoordList
 */
void JCoordPrivate::genCoordList()
{
    if (lineHints == J3D::NoLine) {
        return;
    }

    QColor color;

    // point - o
    color = vertexColor;
    glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    glutSolidSphere(vertexRadius, 80, 80);

    GLUquadric *object = gluNewQuadric();

    // line - x
    if (lineHints & J3D::LeftLine) {
        color = JGLIndicator::defaultXColor();
        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(object, 0.001f, 0.001f, 1.05f, 30, 30);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(1.05f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glutSolidCone(0.006f, 0.03f, 50, 50);
        glPopMatrix();
    }
    // line - y
    if (lineHints & J3D::FloorLine) {
        color = JGLIndicator::defaultYColor();
        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        glPushMatrix();
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(object, 0.001f, 0.001f, 1.05f, 30, 30);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 1.05f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidCone(0.006f, 0.03f, 50, 50);
        glPopMatrix();
    }
    // line - z
    if (lineHints & J3D::BackLine) {
        color = JGLIndicator::defaultZColor();
        glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        gluCylinder(object, 0.001f, 0.001f, 1.05f, 30, 30);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.05f);
        glutSolidCone(0.006f, 0.03f, 50, 50);
        glPopMatrix();
    }

    gluDeleteQuadric(object);
}

/**
 * @brief JCoordPrivate::genGridLists
 */
void JCoordPrivate::genGridLists()
{
    QVector3D step = QVector3D(1./interval.x(), 1./interval.y(), 1./interval.z());
    int xInterval = (int)interval.x(), yInterval = (int)interval.y(), zInterval = (int)interval.z();
    qreal major = 0.;
    QVector<QVector3D> vertexes;

    /// grid

    // x
    for (int i = 1; i <= xInterval; ++i) {
        major = step.x() * i;
        if (sideHints & J3D::FloorSide) {
            vertexes << QVector3D(major, 0.0f, 0.0f) << QVector3D(major, 0.0f, 1.0f);   // x-z: x
        }
        if (sideHints & J3D::CeilSide) {
            vertexes << QVector3D(major, 1.0f, 0.0f) << QVector3D(major, 1.0f, 1.0f);   // x-z: x
        }
        if (sideHints & J3D::BackSide) {
            vertexes << QVector3D(major, 0.0f, 0.0f) << QVector3D(major, 1.0f, 0.0f);   // x-y: x
        }
        if (sideHints & J3D::FrontSide) {
            vertexes << QVector3D(major, 0.0f, 1.0f) << QVector3D(major, 1.0f, 1.0f);   // x-y: x
        }
    }

    // y
    for (int i = 1; i <= yInterval; ++i) {
        major = step.y() * i;
        if (sideHints & J3D::LeftSide) {
            vertexes << QVector3D(0.0f, major, 0.0f) << QVector3D(0.0f, major, 1.0f);   // y-z: y
        }
        if (sideHints & J3D::RightSide) {
            vertexes << QVector3D(1.0f, major, 0.0f) << QVector3D(1.0f, major, 1.0f);   // y-z: y
        }
        if (sideHints & J3D::BackSide) {
            vertexes << QVector3D(0.0f, major, 0.0f) << QVector3D(1.0f, major, 0.0f);   // x-y: y
        }
        if (sideHints & J3D::FrontSide) {
            vertexes << QVector3D(0.0f, major, 1.0f) << QVector3D(1.0f, major, 1.0f);   // x-y: y
        }
    }

    // z
    for (int i = 1; i <= zInterval; ++i) {
        major = step.z() * i;
        if (sideHints & J3D::LeftSide) {
            vertexes << QVector3D(0.0f, 0.0f, major) << QVector3D(0.0f, 1.0f, major);   // y-z: z
        }
        if (sideHints & J3D::RightSide) {
            vertexes << QVector3D(1.0f, 0.0f, major) << QVector3D(1.0f, 1.0f, major);   // y-z: z
        }
        if (sideHints & J3D::FloorSide) {
            vertexes << QVector3D(0.0f, 0.0f, major) << QVector3D(1.0f, 0.0f, major);   // x-z: z
        }
        if (sideHints & J3D::CeilSide) {
            vertexes << QVector3D(0.0f, 1.0f, major) << QVector3D(1.0f, 1.0f, major);   // x-z: z
        }
    }

    /// edge

    // left
    if ((sideHints & J3D::LeftSide) == 0 && (lineHints & J3D::LeftLine)) {
        if ((sideHints & J3D::CeilSide) == 0) {
            vertexes << QVector3D(0.0f, 1.0f, 0.0f) << QVector3D(0.0f, 1.0f, 1.0f);
        }
        if ((sideHints & J3D::FrontSide) == 0) {
            vertexes << QVector3D(0.0f, 0.0f, 1.0f) << QVector3D(0.0f, 1.0f, 1.0f);
        }
    }
    // right
    if ((sideHints & J3D::RightSide) == 0 && (lineHints & J3D::RightLine)) {
        if ((sideHints & J3D::CeilSide) == 0) {
            vertexes << QVector3D(1.0f, 1.0f, 0.0f) << QVector3D(1.0f, 1.0f, 1.0f);
        }
        if ((sideHints & J3D::FrontSide) == 0) {
            vertexes << QVector3D(1.0f, 0.0f, 1.0f) << QVector3D(1.0f, 1.0f, 1.0f);
        }
    }
    // floor
    if ((sideHints & J3D::FloorSide) == 0 && (lineHints & J3D::FloorLine)) {
        if ((sideHints & J3D::RightSide) == 0) {
            vertexes << QVector3D(1.0f, 0.0f, 0.0f) << QVector3D(1.0f, 0.0f, 1.0f);
        }
        if ((sideHints & J3D::FrontSide) == 0) {
            vertexes << QVector3D(0.0f, 0.0f, 1.0f) << QVector3D(1.0f, 0.0f, 1.0f);
        }
    }
    // ceil
    if ((sideHints & J3D::CeilSide) == 0 && (lineHints & J3D::CeilLine)) {
        if ((sideHints & J3D::RightSide) == 0) {
            vertexes << QVector3D(1.0f, 1.0f, 0.0f) << QVector3D(1.0f, 1.0f, 1.0f);
        }
        if ((sideHints & J3D::FrontSide) == 0) {
            vertexes << QVector3D(0.0f, 1.0f, 1.0f) << QVector3D(1.0f, 1.0f, 1.0f);
        }
    }
    // back
    if ((sideHints & J3D::BackSide) == 0 && (lineHints & J3D::BackLine)) {
        if ((sideHints & J3D::CeilSide) == 0) {
            vertexes << QVector3D(0.0f, 1.0f, 0.0f) << QVector3D(1.0f, 1.0f, 0.0f);
        }
        if ((sideHints & J3D::RightSide) == 0) {
            vertexes << QVector3D(1.0f, 0.0f, 0.0f) << QVector3D(1.0f, 1.0f, 0.0f);
        }
    }
    // front
    if ((sideHints & J3D::FrontSide) == 0 && (lineHints & J3D::FrontLine)) {
        if ((sideHints & J3D::CeilSide) == 0) {
            vertexes << QVector3D(0.0f, 1.0f, 1.0f) << QVector3D(1.0f, 1.0f, 1.0f);
        }
        if ((sideHints & J3D::RightSide) == 0) {
            vertexes << QVector3D(1.0f, 0.0f, 1.0f) << QVector3D(1.0f, 1.0f, 1.0f);
        }
    }

    if (!vertexes.isEmpty()) {
        createGridSideList(vertexes);
    }

    /// area

    if (areaDrawable) {
        // left side
        if (sideHints & J3D::LeftSide) {
            createGridSideAreaList(&_vertex_grid_area[VertextGridAreaLeft]);
        }
        // right side
        if (sideHints & J3D::RightSide) {
            createGridSideAreaList(&_vertex_grid_area[VertextGridAreaRight]);
        }
        // floor side
        if (sideHints & J3D::FloorSide) {
            createGridSideAreaList(&_vertex_grid_area[VertextGridAreaFloor]);
        }
        // ceil side
        if (sideHints & J3D::CeilSide) {
            createGridSideAreaList(&_vertex_grid_area[VertextGridAreaCeil]);
        }
        // back side
        if (sideHints & J3D::BackSide) {
            createGridSideAreaList(&_vertex_grid_area[VertextGridAreaBack]);
        }
        // front side
        if (sideHints & J3D::FrontSide) {
            createGridSideAreaList(&_vertex_grid_area[VertextGridAreaFront]);
        }
    }
}

/**
 * @brief JCoordPrivate::createGridSideList
 * @param vertexes
 */
void JCoordPrivate::createGridSideList(const QVector<QVector3D> &vertexes)
{
    glLineWidth(0.5f);
    glColor4f(gridColor.redF(), gridColor.greenF(), gridColor.blueF(), 0.2f);
    glVertexPointer(3, GL_FLOAT, 0, vertexes.constData());
    glDrawArrays(GL_LINES, 0, vertexes.count());
}

/**
 * @brief JCoordPrivate::createGridSideAreaList
 * @param vertexes
 */
void JCoordPrivate::createGridSideAreaList(const GLfloat *vertexes)
{
    glEnableClientState(GL_COLOR_ARRAY);
    glPushAttrib(GL_DEPTH_BITS);
    glDisable(GL_DEPTH_TEST);
    glNormal3fv(vertexes);
    glVertexPointer(3, GL_FLOAT, 7 * sizeof(GLfloat), &vertexes[3]);
    glColorPointer(4, GL_FLOAT, 7 * sizeof(GLfloat), &vertexes[6]);
    glDrawArrays(GL_QUADS, 0, 4);   // positive
    glVertexPointer(3, GL_FLOAT, 0, &vertexes[31]);
    glDrawArrays(GL_QUADS, 0, 4);   // negative
    glPopAttrib();
    glDisableClientState(GL_COLOR_ARRAY);
}

/**
 * @brief JCoordPrivate::genTickList
 */
void JCoordPrivate::genTickList()
{
    QVector3D step = QVector3D(1./interval.x(), 1./interval.y(), 1./interval.z());
    int xInterval = (int)interval.x(), yInterval = (int)interval.y(), zInterval = (int)interval.z();
    qreal major = 0., minor = 0.;
    QVector<QVector3D> vertexes;

    // x
    for (int i = 0; i < xInterval; ++i) {
        major = (i + 1) * step.x();
        if (tickMajorDrawable) {
            vertexes << QVector3D(major, 0.0f, 0.0f) << QVector3D(major, -tickLengthMajor, -tickLengthMajor);
        }
        if (tickMinorDrawable) {
            for (int j = 1; j < 5; ++j) {
                minor = major - step.x() + j * step.x() / 5.0f;
                vertexes << QVector3D(minor, 0.0f, 0.0f) << QVector3D(minor, -tickLengthMinor, -tickLengthMinor);
            }
        }
    }

    // y
    for (int i = 0; i < yInterval; ++i) {
        major = (i + 1) * step.y();
        if (tickMajorDrawable) {
            vertexes << QVector3D(0.0f, major, 0.0f) << QVector3D(-tickLengthMajor, major, -tickLengthMajor);
        }
        if (tickMinorDrawable) {
            for (int j = 1; j < 5; ++j) {
                minor = major - step.y() + j * step.y() / 5.0f;
                vertexes << QVector3D(0.0f, minor, 0.0f) << QVector3D(-tickLengthMinor, minor, -tickLengthMinor);
            }
        }
    }

    // z
    for (int i = 0; i < zInterval; ++i) {
        major = (i + 1) * step.z();
        if (tickMajorDrawable) {
            vertexes << QVector3D(0.0f, 0.0f, major) << QVector3D(-tickLengthMajor, -tickLengthMajor, major);
        }
        if (tickMinorDrawable) {
            for (int j = 1; j < 5; ++j) {
                minor = major - step.z() + j * step.z() / 5.0f;
                vertexes << QVector3D(0.0f, 0.0f, minor) << QVector3D(-tickLengthMinor, -tickLengthMinor, minor);
            }
        }
    }

    if (vertexes.isEmpty()) {
        return;
    }

    glLineWidth(1.0f);
    glColor4f(labelColor.redF(), labelColor.greenF(), labelColor.blueF(), labelColor.alphaF());
    glVertexPointer(3, GL_FLOAT, 0, vertexes.constData());
    glDrawArrays(GL_LINES, 0, vertexes.count());
}

J3D_END_NAMESPACE

// - class JCoord -

/**
 * @brief JCoord::JCoord
 * @param parent
 */
JCoord::JCoord(QObject *parent)
    : JGLObject(parent)
    , d_ptr(new JCoordPrivate(this))
{
    Q_D(JCoord);
    d->init();
}

/**
 * @brief JCoord::~JCoord
 */
JCoord::~JCoord()
{
    delete d_ptr;
}

/**
 * @brief JCoord::gridColor
 * @return
 */
QColor JCoord::gridColor() const
{
    Q_D(const JCoord);
    return d->gridColor;
}

/**
 * @brief JCoord::textColor
 * @return
 */
QColor JCoord::textColor() const
{
    Q_D(const JCoord);
    return d->textColor;
}

/**
 * @brief JCoord::labelFont
 * @return
 */
QFont JCoord::labelFont() const
{
    Q_D(const JCoord);
    return d->labelFont;
}

/**
 * @brief JCoord::labelColor
 * @return
 */
QColor JCoord::labelColor() const
{
    Q_D(const JCoord);
    return d->labelColor;
}

/**
 * @brief JCoord::setLineWidth
 * @param value
 * @param majorFactor
 * @param minorFactor
 */
void JCoord::setLineWidth(qreal value, qreal majorFactor, qreal minorFactor)
{
    Q_D(JCoord);
    if (value != d->lineWidth ||
            majorFactor != d->lineMajorFactor ||
            minorFactor != d->lineMinorFactor) {
        d->lineWidth = value;
        d->lineMajorFactor = majorFactor;
        d->lineMinorFactor = minorFactor;
        update();
    }
}

/**
 * @brief JCoord::setTickLength
 * @param major
 * @param minor
 */
void JCoord::setTickLength(qreal major, qreal minor)
{
    Q_D(JCoord);
    if (major != d->tickLengthMajor ||
            minor != d->tickLengthMinor) {
        d->tickLengthMajor = major;
        d->tickLengthMinor = minor;
        update();
    }
}

/**
 * @brief JCoord::setAxisLabelHint
 * @param axis
 * @param visible
 */
void JCoord::setAxisLabelHint(JCoord::Axis3D axis, bool visible)
{
    Q_D(JCoord);
    JCoord::Axes3D axes = d->axesLabel;
    if (visible) {
        axes |= axis;
    } else {
        axes &= ~axis;
    }

    if (axes != d->axesLabel) {
        d->axesLabel = axes;
        update();
    }
}

/**
 * @brief JCoord::setAxisLabelHints
 * @param axes
 */
void JCoord::setAxisLabelHints(JCoord::Axes3D axes)
{
    Q_D(JCoord);
    if (axes != d->axesLabel) {
        d->axesLabel = axes;
        update();
    }
}

/**
 * @brief JCoord::axisLabel
 * @param axis
 * @return
 */
QString JCoord::axisLabel(JCoord::Axis3D axis) const
{
    if (axis == JCoord::NoAxis) {
        return QString();
    }

    Q_D(const JCoord);
    switch (axis) {
    case JCoord::xAxis:
        return d->xAxisLabel;
    case JCoord::yAxis:
        return d->yAxisLabel;
    case JCoord::zAxis:
        return d->zAxisLabel;
    default:
        return QString();
    }
}

/**
 * @brief JCoord::setAxisLabel
 * @param axis
 * @param text
 */
void JCoord::setAxisLabel(JCoord::Axis3D axis, const QString &text)
{
    if (axis == JCoord::NoAxis) {
        return;
    }

    Q_D(JCoord);
    switch (axis) {
    case JCoord::xAxis:
        d->xAxisLabel = text;
        break;
    case JCoord::yAxis:
        d->yAxisLabel = text;
        break;
    case JCoord::zAxis:
        d->zAxisLabel = text;
        break;
    default:
        break;
    }
}

/**
 * @brief JCoord::lineSmooth
 * @return
 */
bool JCoord::lineSmooth() const
{
    Q_D(const JCoord);
    return d->lineSmooth;
}

/**
 * @brief JCoord::gridSpacing
 * @return
 */
qreal JCoord::gridSpacing() const
{
    Q_D(const JCoord);
    return d->gridSpacing;
}

/**
 * @brief JCoord::tickDrawable
 * @return
 */
bool JCoord::tickDrawable() const
{
    Q_D(const JCoord);
    return d->tickDrawable;
}

/**
 * @brief JCoord::tickMajorDrawable
 * @return
 */
bool JCoord::tickMajorDrawable() const
{
    Q_D(const JCoord);
    return d->tickMajorDrawable;
}

/**
 * @brief JCoord::tickMinorDrawable
 * @return
 */
bool JCoord::tickMinorDrawable() const
{
    Q_D(const JCoord);
    return d->tickMinorDrawable;
}

/**
 * @brief JCoord::lineHints
 * @return
 */
LineHints JCoord::lineHints() const
{
    Q_D(const JCoord);
    return d->lineHints;
}

/**
 * @brief JCoord::setLineSmooth
 * @param value
 */
void JCoord::setLineSmooth(bool value)
{
    Q_D(JCoord);
    if (value != d->lineSmooth) {
        d->lineSmooth = value;
        Q_EMIT lineSmoothChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setGridSpacing
 * @param value
 */
void JCoord::setGridSpacing(qreal value)
{
    Q_D(JCoord);
    if (value != d->gridSpacing) {
        d->gridSpacing = value;
        Q_EMIT gridSpacingChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setTickDrawable
 * @param value
 */
void JCoord::setTickDrawable(bool value)
{
    Q_D(JCoord);
    if (value != d->tickDrawable) {
        d->tickDrawable = value;
        Q_EMIT tickDrawableChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setTickMajorDrawable
 * @param value
 */
void JCoord::setTickMajorDrawable(bool value)
{
    Q_D(JCoord);
    if (value != d->tickMajorDrawable) {
        d->tickMajorDrawable = value;
        Q_EMIT tickMajorDrawableChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setTickMinorDrawable
 * @param value
 */
void JCoord::setTickMinorDrawable(bool value)
{
    Q_D(JCoord);
    if (value != d->tickMinorDrawable) {
        d->tickMinorDrawable = value;
        Q_EMIT tickMinorDrawableChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setLineHint
 * @param hint
 * @param enable
 */
void JCoord::setLineHint(J3D::LineHint hint, bool enable)
{
    Q_D(JCoord);
    J3D::LineHints hints = d->lineHints;
    if (enable) {
        hints |= hint;
    } else {
        hints &= ~hint;
    }

    if (hints != d->lineHints) {
        d->lineHints = hints;
        Q_EMIT lineHintsChanged(hints);
        update();
    }
}

/**
 * @brief JCoord::setLineHints
 * @param value
 */
void JCoord::setLineHints(J3D::LineHints value)
{
    Q_D(JCoord);
    if (value != d->lineHints) {
        d->lineHints = value;
        Q_EMIT lineHintsChanged(value);
        update();
    }
}

/**
 * @brief JCoord::sideHints
 * @return
 */
SideHints JCoord::sideHints() const
{
    Q_D(const JCoord);
    return d->sideHints;
}

/**
 * @brief JCoord::interval
 * @return
 */
QVector3D JCoord::interval() const
{
    Q_D(const JCoord);
    return d->interval;
}

/**
 * @brief JCoord::setSideHint
 * @param hint
 * @param enable
 */
void JCoord::setSideHint(SideHint hint, bool enable)
{
    Q_D(JCoord);
    J3D::SideHints hints = d->sideHints;
    if (enable) {
        hints |= hint;
    } else {
        hints &= ~hint;
    }

    if (hints != d->sideHints) {
        Q_EMIT sideHintsChanged(hints);
        update();
    }
}

/**
 * @brief JCoord::draw
 * @param painter
 */
void JCoord::draw(JGLPainter *painter)
{
    Q_D(JCoord);
    if (!painter->picking() && !isDirty()) {
        //
        JGLObject::draw(painter);
        //
        if (d->tickMajorDrawable) {
            JGLFont::instance()->setFont(QFont("Courier New", 15, QFont::Normal));
            glColor4f(d->textColor.redF(), d->textColor.greenF(),
                      d->textColor.blueF(), d->textColor.alphaF());

            QVector3D step = QVector3D(1./d->interval.x(), 1./d->interval.y(), 1./d->interval.z());
            int xInterval = (int)d->interval.x();
            int yInterval = (int)d->interval.y();
            int zInterval = (int)d->interval.z();
            qreal major = 0.;

            JRect3D box = this->box();
            qreal dx = box.dx(), dy = box.dy(), dz = box.dz();
            if (/*qIsNull(dx)*/true) {
                for (int i = 1; i <= xInterval; ++i) {
                    major = i * step.x();
                    JGLFont::instance()->drawText2D(QString("%1")
                                                    .arg(d->scaledValue(dx, box.left() + dx * major)),
                                                    QVector3D(major, -0.03f, -0.03f));
                }
            }
            if (/*qIsNull(dy)*/true) {
                for (int i = 1; i <= yInterval; ++i) {
                    major = i * step.y();
                    JGLFont::instance()->drawText2D(QString("%1")
                                                    .arg(d->scaledValue(dy, box.floor() + dy * major)),
                                                    QVector3D(-0.03f, major, -0.03f));
                }
            }
            if (/*qIsNull(dz)*/true) {
                for (int i = 1; i <= zInterval; ++i) {
                    major = i * step.z();
                    JGLFont::instance()->drawText2D(QString("%1")
                                                    .arg(d->scaledValue(dz, box.back() + dz * major)),
                                                    QVector3D(-0.03f, -0.03f, major));
                }
            }
        }
        if (d->axesLabel & JCoord::AllAxes) {
            JGLFont::instance()->setFont(QFont("Microsoft Yahei", 20, QFont::DemiBold));
            if (d->axesLabel & JCoord::oAxis) {
                JGLFont::instance()->drawText2D(d->oAxisLabel,
                                                QVector3D(-0.03f, 0.03f, -0.03f),
                                                d->textColor);
            }
            if (d->axesLabel & JCoord::xAxis) {
                JGLFont::instance()->drawText2D(d->xAxisLabel,
                                                QVector3D(1.1f, 0.03f, -0.03f),
                                                JGLIndicator::defaultXColor());
            }
            if (d->axesLabel & JCoord::yAxis) {
                JGLFont::instance()->drawText2D(d->yAxisLabel,
                                                QVector3D(-0.03f, 1.1f, -0.03f),
                                                JGLIndicator::defaultYColor());
            }
            if (d->axesLabel & JCoord::zAxis) {
                JGLFont::instance()->drawText2D(d->zAxisLabel,
                                                QVector3D(-0.03f, 0.03f, 1.1f),
                                                JGLIndicator::defaultZColor());
            }
        }
    }
}

/**
 * @brief JCoord::update
 */
void JCoord::update()
{
    Q_D(JCoord);
    d->update();

    JGLObject::update();
}

/**
 * @brief JCoord::setGridColor
 * @param value
 */
void JCoord::setGridColor(const QColor &value)
{
    Q_D(JCoord);
    if (value != d->gridColor) {
        d->gridColor = value;
        Q_EMIT gridColorChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setTextColor
 * @param value
 */
void JCoord::setTextColor(const QColor &value)
{
    Q_D(JCoord);
    if (value != d->textColor) {
        d->textColor = value;
        Q_EMIT textColorChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setLabelFont
 * @param value
 */
void JCoord::setLabelFont(const QFont &value)
{
    Q_D(JCoord);
    if (value != d->labelFont) {
        d->labelFont = value;
        Q_EMIT labelFontChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setLabelColor
 * @param value
 */
void JCoord::setLabelColor(const QColor &value)
{
    Q_D(JCoord);
    if (value != d->labelColor) {
        d->labelColor = value;
        Q_EMIT labelColorChanged(value);
        update();
    }
}

/**
 * @brief JCoord::setSideHints
 * @param value
 */
void JCoord::setSideHints(J3D::SideHints value)
{
    Q_D(JCoord);
    if (value != d->sideHints) {
        d->sideHints = value;
        Q_EMIT sideHintsChanged(value);
        update();
    }
}

void JCoord::setInterval(const QVector3D &value)
{
    Q_D(JCoord);
    if (value != d->interval) {
        d->interval = value;
        Q_EMIT intervalChanged(value);
        update();
    }
}

QT_END_NAMESPACE
