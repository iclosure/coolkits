
#include <QApplication>
#include "plot3d_view.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Plot3D::JView view;
    view.resize(800, 480);
    view.showMaximized();

    app.exec();

    return 0;
}
