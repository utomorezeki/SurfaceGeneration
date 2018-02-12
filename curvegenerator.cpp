#include "curvegenerator.h"
#include "ui_curvegenerator.h"
#include "mathematics.h"
#include <QDebug>

CurveGenerator::CurveGenerator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CurveGenerator)
{
    ui->setupUi(this);
    //connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->progressBar,SLOT(setValue(int)));

    ui->plot->addGraph();
    ui->plot->addGraph();
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus));
    ui->plot->xAxis->setRange(0, 400);
    ui->plot->yAxis->setRange(0,400);
    ui->uSlider->setMaximum(100);
    ui->uSlider->setTickInterval(1);
    ui->ctrlSlider->setMaximum(15);
    ui->ctrlSlider->setTickInterval(1);
    ui->xSlider->setMaximum(400);
    ui->xSlider->setTickInterval(1);
    ui->ySlider->setMaximum(400);
    ui->ySlider->setTickInterval(1);
    ui->subdSlider->setMaximum(20);
    ui->subdSlider->setMinimum(1);
    ui->subdSlider->setTickInterval(1);
    init = true;
    bez = false;
    cbBS = false;
    cSD = false;
    qSD = false;
    subd = 1;
    subdivideU = 0;
    ptIdx = -1;
    ui->double_2->setEnabled(false);
    ui->triple->setEnabled(false);
    connect(ui->plot,SIGNAL(mousePress(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
    connect(ui->uSlider,SIGNAL(valueChanged(int)),this,SLOT(uUpdate(int)));
    connect(ui->ctrlSlider,SIGNAL(valueChanged(int)),this,SLOT(ctrlUpdate(int)));
    connect(ui->xSlider,SIGNAL(valueChanged(int)),this,SLOT(xUpdate(int)));
    connect(ui->ySlider,SIGNAL(valueChanged(int)),this,SLOT(yUpdate(int)));
    connect(ui->subdSlider,SIGNAL(valueChanged(int)),this,SLOT(subdUpdate(int)));
}

void CurveGenerator::clickedGraph(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        //QCPAbstractPlottable *plottable = ui->plot->plottableAt(event->localPos());
        //if(plottable) {}
        QPoint p= event->pos();
        if (p.x() > 35 && p.x() < 430 && p.y() > 15 && p.y() < 206){
            double x = ui->plot->xAxis->pixelToCoord(event->localPos().x());
            double y = ui->plot->yAxis->pixelToCoord(event->localPos().y());
            addPoint(x,y);
            ui->ctrlSlider->setValue(qv_x.size());
            plot();
            //qDebug() << x;
            //qDebug() << y;
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        pt_x.clear();
        pt_y.clear();
        double x = ui->plot->xAxis->pixelToCoord(event->localPos().x());
        double y = ui->plot->yAxis->pixelToCoord(event->localPos().y());
        for(int n = 0; n < qv_x.size(); n++){
            if(x > qv_x.at(n) - 10 && x < qv_x.at(n) + 10 && y > qv_y.at(n) - 10 && y < qv_y.at(n) + 10){
                pt_x.append(qv_x.at(n));
                pt_y.append(qv_y.at(n));
                ptIdx = n;
                ui->xSlider->setEnabled(true);
                ui->ySlider->setEnabled(true);
                ui->xSlider->setValue(qv_x.at(n));
                ui->ySlider->setValue(qv_y.at(n));

                QString printedX = "X value: ";
                printedX.append(QString::number(pt_x.front()));
                ui->xLabel->setText(printedX);

                QString printedY = "Y value: ";
                printedY.append(QString::number(pt_y.front()));
                ui->yLabel->setText(printedY);

                ui->double_2->setEnabled(true);
                ui->triple->setEnabled(true);
                plot();
            }
        }
    }
}

void CurveGenerator::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void CurveGenerator::subdUpdate(int subDiv)
{
    QString printedS = "Subdivision #: ";
    subd = subDiv;
    printedS.append(QString::number(subDiv));
    ui->subLabel->setText(printedS);
    plot();
}

void CurveGenerator::uUpdate(int largeU)
{
    subdivideU = largeU / 100.0;
    QString printedU = "U value: ";
    printedU.append(QString::number(subdivideU));
    ui->uLabel->setText(printedU);
    plot();
}

void CurveGenerator::xUpdate(int xUp)
{
    if(ptIdx != -1)
    {
        double *x = qv_x.data();
        x[ptIdx] = xUp/1.0;
        double *xTar = pt_x.data();
        xTar[0] = xUp/1.0;
        QString printedX = "X value: ";
        printedX.append(QString::number(pt_x.front()));
        ui->xLabel->setText(printedX);
        plot();
    }
}

void CurveGenerator::yUpdate(int yUp)
{
    if(ptIdx != -1)
    {
        double *y = qv_y.data();
        y[ptIdx] = yUp/1.0;
        double *yTar = pt_y.data();
        yTar[0] = yUp/1.0;
        QString printedY = "Y value: ";
        printedY.append(QString::number(pt_y.front()));
        ui->yLabel->setText(printedY);
        plot();
    }
}

void CurveGenerator::ctrlUpdate(int ctrlPts)
{
    QString printed = "# of ctrlpoints: ";
    if (ctrlPts > qv_x.size()){
        double maxX = 50;
        for(int n = 0; n < qv_x.size(); n++)
            if(maxX < qv_x.at(n)) maxX = qv_x.at(n);
        double x = Mathematics::fRand(maxX,maxX + 40);
        double y = Mathematics::fRand(50.0,350.0);
        addPoint(x,y);
    }
    else if (ctrlPts < qv_x.size()){
        qv_x.removeLast();
        qv_y.removeLast();
    }
    plot();
    printed.append(QString::number(qv_x.size()));
    ui->ctrlLabel->setText(printed);
}

void CurveGenerator::on_clear_clicked()
{
    qv_x.clear();
    qv_y.clear();
    gr_x.clear();
    gr_y.clear();
    pt_x.clear();
    pt_y.clear();
    ui->ctrlSlider->setValue(0);
    ui->xSlider->setEnabled(false);
    ui->ySlider->setEnabled(false);
    ui->double_2->setEnabled(false);
    ui->triple->setEnabled(false);
    bez = false;
    cbBS = false;
    cSD = false;
    qSD = false;

    plot();
}

void CurveGenerator::plot()
{
    gr_x.clear();
    gr_y.clear();
    if(bez)
    {
        for(double i = 0.0; i < 1.0; i += 0.1){
            double x = Mathematics::compXPtBezMan(i,&qv_x);
            double y = Mathematics::compYPtBezMan(i,&qv_y);
            gr_x.append(x);
            gr_y.append(y);
        }
    }
    else if(cbBS && qv_x.size() > 0)
    {
        QVector<int> t = Mathematics::calcT(qv_x.size());
        for(double u = 0.0; u < t.last(); u += 0.1){
            QVector<double> n4s = Mathematics::calcN4s(u,t);
            double x = 0;
            double y = 0;
            for(int n = 0; n < qv_x.size(); n++)
            {
                x += qv_x.at(n) * n4s.at(n);
                y += qv_y.at(n) * n4s.at(n);
            }
            gr_x.append(x);
            gr_y.append(y);
        }
    }
    else if(cSD && qv_x.size() > 0)
    {
        gr_x = Mathematics::subdivide(qv_x,subd,subdivideU);
        gr_y = Mathematics::subdivide(qv_y,subd,subdivideU);
    }
    else if(qSD)
    {
        gr_x = Mathematics::subdivBspl(qv_x,subd);
        gr_y = Mathematics::subdivBspl(qv_y,subd);
    }
    ui->plot->graph(0)->setData(qv_x,qv_y);
    static QCPCurve *curve;
    if(init){
        curve = new QCPCurve(ui->plot->xAxis,ui->plot->yAxis);
        init =false;
    }
    curve->setData(gr_x,gr_y);
    //ui->plot->graph(1)->setData(gr_x,gr_y);
    ui->plot->graph(2)->setData(pt_x,pt_y);
    ui->plot->replot();
    ui->plot->update();
}

CurveGenerator::~CurveGenerator()
{
    delete ui;
}

void CurveGenerator::on_bezier_clicked()
{
    bez = true;
    cbBS = false;
    cSD = false;
    qSD = false;
    plot();
}

void CurveGenerator::on_bSplines_clicked()
{
    bez = false;
    cbBS = true;
    cSD = false;
    qSD = false;
    plot();
}

void CurveGenerator::on_casteljauSubd_clicked()
{
    bez = false;
    cbBS = false;
    cSD = true;
    qSD = false;
    plot();
}


void CurveGenerator::on_quadricSubd_clicked()
{
    bez = false;
    cbBS = false;
    cSD = false;
    qSD = true;
    plot();
}

void CurveGenerator::on_double_2_clicked()
{
    if(ptIdx != -1)
    {
        qv_x.insert(ptIdx,pt_x.front());
        qv_y.insert(ptIdx,pt_y.front());
        QString printed = "# of ctrlpoints: ";
        printed.append(QString::number(qv_x.size()));
        ui->ctrlLabel->setText(printed);
        ui->ctrlSlider->setValue(qv_x.size());
        plot();
    }

}

void CurveGenerator::on_triple_clicked()
{
    if(ptIdx != -1)
    {
        qv_x.insert(ptIdx,pt_x.front());
        qv_y.insert(ptIdx,pt_y.front());
        qv_x.insert(ptIdx,pt_x.front());
        qv_y.insert(ptIdx,pt_y.front());
        QString printed = "# of ctrlpoints: ";
        printed.append(QString::number(qv_x.size()));
        ui->ctrlLabel->setText(printed);
        ui->ctrlSlider->setValue(qv_x.size());
        plot();
    }
}
