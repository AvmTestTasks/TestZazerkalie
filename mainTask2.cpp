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

    Vector():
    x(0),y(0),z(0){}
    
    Vector(point a,point b):
    x(b.x-a.x),y(b.y-a.y),z(b.z-a.z){}
    
    //Init vector by 2 points
    Vector operator()(point a,point b)
    {
        x= b.x - a.x;
        y= b.y - a.y;
        z= b.z - a.z;
        return *this;
    }
    
    // Vector cross product
    Vector operator()(Vector a,Vector b)
    {
        x = a.y*b.z - a.z*b.y;
        y = -a.x*b.z + a.z*b.x;
        z = a.x*b.y - a.y*b.x;
        
        return *this;
    }
    // Scalar cros product
    double operator*(Vector obj)
    {
        double res = x*obj.x + y*obj.y + z*obj.z;
        return res;
    }
    double operator*(point obj)
    {
        double res = x*obj.x + y*obj.y + z*obj.z;
        return res;
    }
};
int LineFacet(point,point,point,point,point,point*);

int main(int argc, const char * argv[])
{
    point    p1,p2,pa,pb,pc,p;
    
    char ch;
    do
    {
    
    cout<<"Enter end points of segment x0 y0 z0 x1 y1 1:";
    cin>> p1.x>> p1.y>> p1.z >> p2.x >> p2.y >> p2.z;
   
    cout<<"Enter plane cordinates xa ya za xb yb zb xc yc zc:";
    cin>> pa.x>> pa.y>> pa.z>> pb.x>> pb.y>> pb.z >> pc.x>>  pc.y>> pc.z;
    
     
    
    if(LineFacet(p1, p2, pa, pb, pc, &p))
        cout<<"Point of intersection:"<<p.x<<';'<<p.y<<';'<<p.z<<endl;
    else
        cout<<"Segment and plane don't intersect"<<endl;
    
    cout<< "Repeate with new values?(y/n):"<<endl;
        cin>>ch;
    }while(ch !='n');
    
    return 0;
}

int LineFacet(point p1,point p2,point pa,point pb,point pc,point* p)
{
    double d;
    double a1,a2,a3;
    double total,denom,mu;
    Vector n,pa1,pa2,pa3,AB(pa,pb),AC(pa,pc);
    
    void Normalize(Vector&);
    
    /* Calculate the parameters for the plane */
    //vector AB*AC cross product
    n(AB,AC);
    
    Normalize(n);
    //d = - n.x * pa.x - n.y * pa.y - n.z * pa.z;
    d = -(n*pa);
    
    /* Calculate the position on the line that intersects the plane */
    Vector p1p2(p1,p2);
   //denom = n.x * (p2.x - p1.x) + n.y * (p2.y - p1.y) + n.z * (p2.z - p1.z);
    denom = n*p1p2;
    if (abs(denom) < EPS)         /* Line and plane don't intersect */
        return false;
    //mu = - (d + n.x * p1.x + n.y * p1.y + n.z * p1.z) / denom;
    mu = - (d + n*p1) / denom;
    p->x = p1.x + mu * (p2.x - p1.x);
    p->y = p1.y + mu * (p2.y - p1.y);
    p->z = p1.z + mu * (p2.z - p1.z);
    if (mu < 0 || mu > 1)   /* Intersection not along line segment */
        return false;
    
    /* Determine whether or not the intersection point is bounded by pa,pb,pc */
    /*
    pa1.x = pa.x - p->x;
    pa1.y = pa.y - p->y;
    pa1.z = pa.z - p->z;
    */
    pa1(*p,pa);
    Normalize(pa1);
    /*
    pa2.x = pb.x - p->x;
    pa2.y = pb.y - p->y;
    pa2.z = pb.z - p->z;
    */
    pa2(*p,pb);
    Normalize(pa2);
    /*
    pa3.x = pc.x - p->x;
    pa3.y = pc.y - p->y;
    pa3.z = pc.z - p->z;
     */
    pa3(*p,pc);
    Normalize(pa3);
    
    /*
    a1 = pa1.x*pa2.x + pa1.y*pa2.y + pa1.z*pa2.z;
    a2 = pa2.x*pa3.x + pa2.y*pa3.y + pa2.z*pa3.z;
    a3 = pa3.x*pa1.x + pa3.y*pa1.y + pa3.z*pa1.z;
    */
    
    a1 = pa1*pa2;
    a2 = pa2*pa3;
    a3 = pa3*pa1;
    
    total = (acos(a1) + acos(a2) + acos(a3)) * RTOD;
    if (abs(total - 360) > EPS)
        return false;
    
    return true;
}

void Normalize(Vector& t)
{
    double lenght = sqrt((t.x * t.x) + (t.y * t.y) + (t.z * t.z)) ;
    if (lenght != 0 )
    {
    t.x = t.x / lenght;
    t.y = t.y / lenght;
    t.z = t.z / lenght;
    }
}
