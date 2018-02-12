#include "mathematics.h"

int Mathematics::nCk(int n, int k)
{
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k==0) return 1;

    int result = n;
    for ( int i = 2; i <= k; ++i)
    {
        result *= (n -i + 1);
        result /=i;
    }
    return result;
}

double Mathematics::compXPtBezMan(double u,QVector<double> *qv_x)
{
    QVector<double> bVals;
    int size =  qv_x->size() - 1;
    for(int n = 0; n < size + 1; n++)
    {
        double currB = nCk(size, n) * pow(u ,(double)n) * pow((1.0 - u),((double)size - n));
        bVals.append(currB);
    }
    double ans = 0;
    int d = 0;
    while(bVals.size() != 0){
        ans += qv_x->at(d) * bVals.front();
        bVals.pop_front();
        d++;
    }
    return ans;
}

double Mathematics::compYPtBezMan(double u,QVector<double> *qv_y)
{
    QVector<double> bVals;
    int size =  qv_y->size() - 1;
    for(int n = 0; n < size + 1; n++)
    {
        double currB = nCk(size, n) * pow(u ,(double)n) * pow((1.0 - u),((double)size - n));
        bVals.append(currB);
    }
    double ans = 0;
    int d = 0;
    while(bVals.size() != 0){
        ans += qv_y->at(d) * bVals.front();
        bVals.pop_front();
        d++;
    }
    return ans;
}


QVector<int> Mathematics::calcT(int qsize)
{
    int wantedSize = qsize + 4;
    QVector<int> retVal;
    retVal.append(0);
    retVal.append(0);
    retVal.append(0);
    retVal.append(0);
    int idx = 4;
    int topVal = qsize - 1 - 4 + 2;
    while (retVal.size() < wantedSize)
    {
        if(idx >= 4 && idx <= qsize - 1){
            retVal.append(idx - 4 + 1);
            idx++;
        }
        else
            retVal.append(topVal);
    }
    return retVal;
}

double Mathematics::calcN(int idx, int deg, double u, QVector<int> t)
{
    if (deg == 1){
        int ti1 = t.at(idx + 1);
        int ti = t.at(idx);
        if (u < ti1 && u >= ti)
            return 1;
        else if (idx == t.size() - 5 && (u < (double)ti1 + 0.05 && u > (double)ti1 - 0.05))
            return 1;
        else
            return 0;
    }
    else
    {
        int LD = t.at(idx + deg - 1) - t.at(idx);
        double LT = 0;

        if(LD != 0){
            double LN = (u - t.at(idx)) * calcN(idx,deg - 1, u, t);
            LT = LN / LD;
        }
        int RD = t.at(idx + deg) - t.at(idx + 1);
        double RT = 0;
        if (RD != 0 && idx < t.size() - 5)
        {
            double RN = (t.at(idx + deg) - u) * calcN(idx + 1, deg - 1, u, t);
            RT = RN / RD;
        }
        return LT + RT;
    }
}

QVector<double> Mathematics::calcN4s(double u, QVector<int> t)
{
    int ctrlPts = t.size() - 4;
    QVector<double> n4s;
    for(int i = 0; i < ctrlPts; i++){
        n4s.append(calcN(i,4,u,t));
    }
    return n4s;
}

QVector<double> Mathematics::oneSubdivide(QVector<double> qv, QVector<double> poly1, QVector<double> poly2, double u)
{
    if(qv.size()==1){
        qv.append(poly2);
        poly1.append(qv);
        return poly1;
    }
    else
    {
        poly1.append(qv.front());
        poly2.insert(0,qv.last());
        QVector<double> qvPrime;
        for(int i = 0; i < qv.size() - 1; i++){
            double val = qv.at(i) + u * (qv.at(i + 1) - qv.at(i));
            qvPrime.append(val);
        }
        return oneSubdivide(qvPrime,poly1,poly2,u);
    }
}

QVector<double> Mathematics::subdivide(QVector<double> qv, int m, double u)
{
    QVector<double> pol1,pol2;
    if(m ==1 )
        return oneSubdivide(qv, pol1, pol2, u);
    else
    {
        QVector<double> oneSub, leftsub, rightsub;
        oneSub = oneSubdivide(qv, pol1, pol2, u);
        leftsub = subdivide(oneSub.mid(0,qv.size()), m - 1, u);
        if ((qv.size() - oneSub.size()) != 0)
            rightsub = subdivide(oneSub.mid(qv.size(),oneSub.size()), m - 1, u);
        leftsub.append(rightsub);
        return leftsub;
    }
}

QVector<double> Mathematics::oneDivBspl(QVector<double> qv)
{
    QVector<double> ans;
    if(qv.size() > 2)
    {
        double threeFourth = 3.0 / 4.0;
        double oneFourth = 1.0 / 4.0;
        double qIM = threeFourth * qv.at(0) + oneFourth * qv.at(1);
        double qI = oneFourth * qv.at(0) + threeFourth * qv.at(1);
        ans.append(qIM);
        ans.append(qI);
        double rI,rIP;
        for(int i = 1; i < qv.size() - 1; i++)
        {
            rI = threeFourth * qv.at(i) + oneFourth * qv.at(i + 1);
            rIP = oneFourth * qv.at(i) + threeFourth * qv.at(i + 1);
            ans.append(rI);
            ans.append(rIP);
        }
    }
    return ans;
}

QVector<double> Mathematics::subdivBspl(QVector<double> qv, int m)
{
    QVector<double> ans;
    if (m >= 1)
    {
        ans = oneDivBspl(qv);
        m--;
    }

    while (m > 0)
    {
        ans = oneDivBspl(ans);
        m--;
    }
    return ans;
}

double Mathematics::fRand(double min, double max)
{
    double ans = (double)rand() / RAND_MAX;
    return min + ans * (max - min);
}
