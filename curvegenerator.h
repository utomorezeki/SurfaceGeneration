#ifndef CURVEGENERATOR_H
#define CURVEGENERATOR_H

#include <QMainWindow>

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


private slots:
    void on_bezier_clicked();
    void clickedGraph(QMouseEvent *event);
    void uUpdate(int);
    void ctrlUpdate(int);
    void on_clear_clicked();
    void on_bSplines_clicked();
    void on_casteljauSubd_clicked();
    void xUpdate(int);
    void yUpdate(int);
    void subdUpdate(int);
    void on_quadricSubd_clicked();

    void on_double_2_clicked();

    void on_triple_clicked();

private:
    Ui::CurveGenerator *ui;
    QVector<double> qv_x,qv_y,gr_x,gr_y,pt_x,pt_y;
    int ptIdx,subd;
    bool bez,cbBS,cSD,qSD,init;
    double subdivideU;
};

#endif // CURVEGENERATOR_H
