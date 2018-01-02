//
//  main.cpp
//  ZazerkalieTest
//
//  Created by Артем on 01.01.18.
//  Copyright © 2018 Артем. All rights reserved.
//
/*
 
 TASK:
 
 2. Написать код на С++для определения точки пересечения отрезка и треугольника в 3D пространстве.
 Отрезок задан координатами концов, треугольник задан координатами всех трех углов.
 
 The equation of the line is:
 
 p = p1 + mu (p2 - p1)
 
 The equation of the plane is:
 
 a x + b y + c z + d = 0
 n.x x + n.y y + n.z z + d = 0
 
 */
#include <iostream>

#define _USE_MATH_DEFINES
# include <cmath>

using namespace std;


#define EPS 0.000001
#define RTOD 180/M_PI;

struct point
{
    double x;
    double y;
    double z;
    
    point():
    x(0),y(0),z(0){}
    
    point(double a,double b,double c):
    x(a),y(b),z(c){}
};

struct Vector
{
    double x;
    double y;
    double z;

};
int LineFacet(point,point,point,point,point,point*);

int main(int argc, const char * argv[])
{
    point    p1(3,4,4),
             p2(-3,4,4),
             pa(0,2,3),
             pb(0,6,3),
             pc(0,4,6),
             p;
    
    if(LineFacet(p1, p2, pa, pb, pc, &p))
        cout<<"Point of intersection:"<<p.x<<';'<<p.y<<';'<<p.z<<endl;
    else
        cout<<"Segment and plane don't intersect"<<endl;
    
    
    return 0;
}

int LineFacet(point p1,point p2,point pa,point pb,point pc,point* p)
{
    double d;
    double a1,a2,a3;
    double total,denom,mu;
    Vector n,pa1,pa2,pa3;
    void Normalise(Vector&);
    
    /* Calculate the parameters for the plane */
    n.x = (pb.y - pa.y)*(pc.z - pa.z) - (pb.z - pa.z)*(pc.y - pa.y);
    n.y = (pb.z - pa.z)*(pc.x - pa.x) - (pb.x - pa.x)*(pc.z - pa.z);
    n.z = (pb.x - pa.x)*(pc.y - pa.y) - (pb.y - pa.y)*(pc.x - pa.x);
    Normalise(n);
    d = - n.x * pa.x - n.y * pa.y - n.z * pa.z;
    
    /* Calculate the position on the line that intersects the plane */
    denom = n.x * (p2.x - p1.x) + n.y * (p2.y - p1.y) + n.z * (p2.z - p1.z);
    if (abs(denom) < EPS)         /* Line and plane don't intersect */
        return false;
    mu = - (d + n.x * p1.x + n.y * p1.y + n.z * p1.z) / denom;
    p->x = p1.x + mu * (p2.x - p1.x);
    p->y = p1.y + mu * (p2.y - p1.y);
    p->z = p1.z + mu * (p2.z - p1.z);
    if (mu < 0 || mu > 1)   /* Intersection not along line segment */
        return false;
    
    /* Determine whether or not the intersection point is bounded by pa,pb,pc */
    pa1.x = pa.x - p->x;
    pa1.y = pa.y - p->y;
    pa1.z = pa.z - p->z;
    Normalise(pa1);
    pa2.x = pb.x - p->x;
    pa2.y = pb.y - p->y;
    pa2.z = pb.z - p->z;
    Normalise(pa2);
    pa3.x = pc.x - p->x;
    pa3.y = pc.y - p->y;
    pa3.z = pc.z - p->z;
    Normalise(pa3);
    a1 = pa1.x*pa2.x + pa1.y*pa2.y + pa1.z*pa2.z;
    a2 = pa2.x*pa3.x + pa2.y*pa3.y + pa2.z*pa3.z;
    a3 = pa3.x*pa1.x + pa3.y*pa1.y + pa3.z*pa1.z;
    total = (acos(a1) + acos(a2) + acos(a3)) * RTOD;
    if (abs(total - 360) > EPS)
        return false;
    
    return true;
}

void Normalise(Vector& t)
{
    double lenght = sqrt((t.x * t.x) + (t.y * t.y) + (t.z * t.z)) ;
    t.x = t.x / lenght;
    t.y = t.y / lenght;
    t.z = t.z / lenght;
}
