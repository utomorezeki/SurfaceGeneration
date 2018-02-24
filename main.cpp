#include "curvegenerator.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CurveGenerator w;
    w.show();

    return a.exec();
}
