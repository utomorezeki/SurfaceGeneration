#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <QVector>


class Mathematics
{
public:
    static int nCk(int n, int k);
    static double compXPtBezMan(double u, QVector<double> *qv_x);
    static double compYPtBezMan(double u, QVector<double> *qv_y);
    static QVector<int> calcT(int qsize);
    static double calcN(int idx, int deg, double u, QVector<int> t);
    static QVector<double> calcN4s(double u, QVector<int> t);
    static double casteljau(QVector<double> qv, double u);
    static QVector<double> oneSubdivide(QVector<double> qv, QVector<double> poly1, QVector<double> poly2, double u);
    static QVector<double> subdivide(QVector<double> qv, int m, double u);
    static QVector<double> oneDivBspl(QVector<double> qv);
    static QVector<double> subdivBspl(QVector<double> qv, int m);
    static double fRand(double min, double max);

    static QVector<double> calcBernstein(int max, double u);
private:
    Mathematics(){}
};

#endif // MATHEMATICS_H
