#ifndef CURVEGENERATOR_H
#define CURVEGENERATOR_H

#include <QMainWindow>
#include "mesh.h"
#include "nncrust.h"

namespace Ui {
class CurveGenerator;
}

class CurveGenerator : public QMainWindow
{
    Q_OBJECT

public:
    explicit CurveGenerator(QWidget *parent = 0);
    ~CurveGenerator();


    void addPoint(double x, double y);
    void plot();
    void print3D(Mesh mesh, std::string fileNm);

private slots:
    void on_bezier_clicked();
    void clickedGraph(QMouseEvent *event);
    void clickedGraphTwo(QMouseEvent *event);
    void uUpdate(int);
    void ctrlUpdate(int);
    void on_clear_clicked();
    void on_bSplines_clicked();
    void on_casteljauSubd_clicked();
    void xUpdate(int);
    void yUpdate(int);
    void xUpdate2(int);
    void yUpdate2(int);
    void subdUpdate(int);
    void on_quadricSubd_clicked();

    void on_double_2_clicked();

    void on_triple_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_bezier2_clicked();

    void on_bSplines2_clicked();

    void on_pushButton_3_clicked();


    void on_revSpinBx_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_uSpin_valueChanged(double arg1);

    void on_wSpin_valueChanged(double arg1);

private:
    Ui::CurveGenerator *ui;
    QVector<double> qv_x,qv_y,gr_x,gr_y,pt_x,pt_y, qv2_x, qv2_y,gr2_x,gr2_y,pt2_x,pt2_y;
    int ptIdx,subd, ptIdx2, revSlices, extDepth;
    bool bez,cbBS,cSD,qSD,init, init2,bez2,cbBS2;
    double subdivideU, uThreeD,wThreeD;
};

#endif // CURVEGENERATOR_H
