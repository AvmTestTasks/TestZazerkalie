//
//  main.cpp
//  ZazerkalieTest2
//
//  Created by Артем on 02.01.18.
//  Copyright © 2018 Артем. All rights reserved.
//
/*
 
 TASK:
 
 Написать код на С++ для определения кратчайшего расстояния между двумя отрезками в 3D пространстве.
 Отрезки заданы координатами концов.

 

 */


#include <iostream>
#include <cmath>


using namespace std;


struct point
{
    double x;
    double y;
    double z;
    
    point():
    x(0),y(0),z(0){}
    
    
    point(double x0,double y0,double z0):
    x(x0),y(y0),z(z0){}
};

double computeDistance(double,double,double,double,double,double,double,double,double,double,double);
double dist3D_Segment_to_Segment( point p0, point p1 , point p2 ,point p3);



int main(int argc, const char * argv[]) {
    point pA(0,0,0),
          pB(0,0,1),
          pC(0,1,2),
          pD(0,3,1);
    
    double result=dist3D_Segment_to_Segment(pA, pB, pC, pD);
    cout<<"Close distance between segments:"<< result<<endl;
    
    
    return 0;
}
// dist3D_Segment_to_Segment(): get the 3D minimum distance between 2 segments
//    Input:  two 3D line segments S1 and S2
//    Return: the shortest distance between S1 and S2
double dist3D_Segment_to_Segment( point pA, point pB , point pC ,point pD)
{
    double d11=pB.x-pA.x;
    double d21=pB.y-pA.y;
    double d31=pB.z-pA.z;
    
    double d12=pD.x-pC.x;
    double d22=pD.y-pC.y;
    double d32=pD.z-pC.z;
    
    double d112=pC.x-pA.x;
    double d212=pC.y-pA.y;
    double d312=pC.z-pA.z;
    
    
    double R = d11*d12+d21*d22+d31*d32;
    
    double S1 = d11*d112+d21*d212+d31*d312;
    
    double S2 = d12*d112+d22*d212+d32*d312;
    
    double D1 = d11*d11+d21*d21+d31*d31;
    
    double D2 = d12*d12+d22*d22+d32*d32;
    
    
    // t = (S1*D2-S2*R)/(D1*D2 - R*R)
    // u = -(S2*D1-S1*R)/(D1*D2-R*R)
    
    double t,u;
    
    if(D1 == 0)
    {
        t = 0;
        u = -(S2*D1-S1*R)/(D1*D2-R*R);
        if(u<0)
            u=0;
        if(u>1)
            u=1;
       return computeDistance(t,u,d11,d21,d31,d12,d22,d32,d112,d212,d312);
    }
    
    if(D2 == 0)
    {
        u=0;
        t = (S1*D2-S2*R)/(D1*D2 - R*R);
        if(t<0)
            t=0;
        if(t>1)
            t=1;
        return computeDistance(t,u,d11,d21,d31,d12,d22,d32,d112,d212,d312);
    }
    
    if( D1==0 && D2==0)
    {
        t=u=0;
        return computeDistance(t,u,d11,d21,d31,d12,d22,d32,d112,d212,d312);
    }
    
    
    if(D1*D2-R*R==0)
    {
        t=0;
        u = -(S2*D1-S1*R)/(D1*D2-R*R);
        if(u<0)
            u=0;
        if(u>1)
            u=1;
        return computeDistance(t,u,d11,d21,d31,d12,d22,d32,d112,d212,d312);
    }
    
    t = (S1*D2-S2*R)/(D1*D2 - R*R);
    if(t<0)
        t=0;
    if(t>1)
        t=1;
    
    u = -(S2*D1-S1*R)/(D1*D2-R*R);
    if(u<0)
        u=0;
    if(u>1)
        u=1;
    return computeDistance(t,u,d11,d21,d31,d12,d22,d32,d112,d212,d312);
}
double computeDistance(double t,double u,double d11,double d21,double d31,double d12,double d22 ,double d32 ,double d112,double d212,double d312)
{
    double temp = (d11*t - d12*u-d112)*(d11*t - d12*u-d112)+(d21*t-d22*u-d212)*(d21*t-d22*u-d212)+(d31*t-d32*u-d312)*(d31*t-d32*u-d312);
    return sqrt(temp);
}
