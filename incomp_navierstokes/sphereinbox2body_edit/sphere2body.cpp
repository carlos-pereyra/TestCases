/*
 * Author: Carlos Pereyra
 * Purpose: Create mesh of circle in a box
 * Use: g++ -std=c++11 -Iinclude circleBox.cpp -o run -lgmsh
 * Use: ./run
 * Use: gmsh msh/circbox.msh
 *
 */

// The Gmsh API is entirely defined in the <gmsh.h> header. Read this file: it
// contains the documentation for all the functions in the API.
#include <iostream>
#include <cstdio>
#include <cmath>
#include <gmsh.h>
using namespace std;
#define RAD_ELEM 31
#define AZIMUTH_ELEM 31
#define GROWTH 1.1
#define FAR 0
#define FAR_RAD_ELEM 31
#define TRANS 1
#define LC 1

namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void squareMesh(double Xc, double Yc, double Zc, double S, double L){
    // EXTERIOR CUBE
    std::vector<std::pair<int, int> > ov, ovv, ovvv;
    int p1,p2,p3,p4,p5,p6,p7,p8,p9;
    int l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12;
    int loop1,loop2,loop3,loop4,loop5,loop6;
    int s1,s2,s3,s4,s5,s6;
    
    double enlg=4;
    
    p1 = geo::addPoint(  Xc+enlg ,  Yc+enlg , Zc-enlg, LC);
    p2 = geo::addPoint(  Xc+enlg ,  Yc-enlg , Zc-enlg, LC);
    p3 = geo::addPoint(  Xc-enlg ,  Yc+enlg , Zc-enlg, LC);
    p4 = geo::addPoint(  Xc-enlg ,  Yc-enlg , Zc-enlg, LC);
    
    l1 = geo::addLine(p1, p2);
    l2 = geo::addLine(p2, p4);
    l3 = geo::addLine(p4, p3);
    l4 = geo::addLine(p3, p1);
    
    loop1 = geo::addCurveLoop({l1, l2, l3, l4});

    s1 = geo::addPlaneSurface({loop1});
    
    //ROTATIONS
    geo::copy({{2, s1}}, ov); //FORWARD
    geo::rotate({{2,ov.back().second}}, Xc,0,0 , 1,0,0 , M_PI/2 );
    
    geo::copy({{2, ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, Xc,0,0 , 1,0,0 , M_PI/2 );
    
    geo::copy({{2, ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, Xc,0,0 , 1,0,0 , M_PI/2 );
    
    geo::copy({{2, s1}}, ovv); //LEFT
    geo::rotate({{2,ovv.back().second}}, Xc,0,0 , 0,1,0 , M_PI/2 );
    
    geo::copy({{2, s1}}, ovvv); //RIGHT
    geo::rotate({{2,ovvv.back().second}}, Xc,0,0 , 0,1,0 , -M_PI/2 );
    
    //TRANSFINITE DEF
    mesh::setTransfiniteCurve(l1,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l2,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l3,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l4,AZIMUTH_ELEM+1,"Progression",1);

    mesh::setTransfiniteSurface(s1, "Right"); mesh::setRecombine(2, s2);

    //PHYSICAL NAMING
    int pg = model::addPhysicalGroup(2,{s1}); model::setPhysicalName(2,pg,"far");

}


void sphereMesh(double x, double y, double z, double r1, double l, double lc, std::vector<int> &surfaces, std::vector<int> &volumes, double S){
    
    std::vector<std::pair<int, int> > ov, ovv, ovvv, surfa, linessave;
    std::vector<int> tagss;
    
    // BETWEEN SPHERES POINT
    int p0= geo::addPoint( x-S/2,   0 ,     0, lc);

    // SPHERE 1: CENTER
    int p1= geo::addPoint(     x,    y,     z, LC);
    
    // SPHERE 1: CIRCLE POINTS
    int p2= geo::addPoint( -r1+x, r1+y, -r1+z, LC);
    int p3= geo::addPoint(  r1+x, r1+y, -r1+z, LC);
    int p4= geo::addPoint(  r1+x,-r1+y, -r1+z, LC);
    int p5= geo::addPoint( -r1+x,-r1+y, -r1+z, LC);
    
    // SPHERE 1: CONNECT SPHERE CIRCLE
    int c1= geo::addCircleArc(p2, p1, p3);
    int c2= geo::addCircleArc(p3, p1, p4);
    int c3= geo::addCircleArc(p4, p1, p5);
    int c4= geo::addCircleArc(p5, p1, p2);
    
    // SPHERE 1: CREATE SPHERICAL SURFACE
    int loop1 = geo::addCurveLoop({c1,c2,c3,c4});
    int s1 = geo::addSurfaceFilling({loop1});
    
    // SPHERE 2: CENTER
    int p11= geo::addPoint(    x-S,    y,     z, LC);
    
    // SPHERE 2: CIRCLE POINTS
    int p22= geo::addPoint( -r1+x-S, r1+y, -r1+z, LC);
    int p33= geo::addPoint(  r1+x-S, r1+y, -r1+z, LC);
    int p44= geo::addPoint(  r1+x-S,-r1+y, -r1+z, LC);
    int p55= geo::addPoint( -r1+x-S,-r1+y, -r1+z, LC);
    
    // SPHERE 2: CONNECT SPHERE CIRCLE
    int c11= geo::addCircleArc(p22, p11, p33);
    int c22= geo::addCircleArc(p33, p11, p44);
    int c33= geo::addCircleArc(p44, p11, p55);
    int c44= geo::addCircleArc(p55, p11, p22);
    
    // SPHERE 2: CREATE SPHERICAL SURFACE
    int loop2= geo::addCurveLoop({c11,c22,c33,c44});
    int s2= geo::addSurfaceFilling({loop2});
    
    // SPHERE 3: CONNECTOR
    int e1 = geo::addEllipseArc(33,p0,27,27);
    int e2 = geo::addEllipseArc(30,p0,34,34);
    
    // SPHERE 3: CREATE SPHERICAL SURFACE
    int loop3 = geo::addCurveLoop({e1,-c4,e2,-c22});
    int s3 = geo::addSurfaceFilling({loop3});

    //============================================================
    
    // SPHERE 1: ROTATE SURFACE
    surfa.push_back({2,s1}); //side 1
    geo::copy({{2, s1}}, ov);
    geo::rotate({{2,ov.back().second}}, x,y,z , r1,0,0 , M_PI/2 );
    
    surfa.push_back({2,ov.back().second}); //side 2
    geo::copy({{2, ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, x,y,z , r1,0,0 , M_PI/2 );
    
    surfa.push_back({2,ov.back().second}); //side 3
    geo::copy({{2,ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, x,y,z , r1,0,0 , M_PI/2 );
    
    surfa.push_back({2,ov.back().second}); //side 4
    geo::copy({{2, s1}}, ovv);
    
    surfa.push_back({2,ovv.back().second}); //side 5
    geo::rotate( {{2,ovv.back().second}}, x,y,z , 0,r1,0 , M_PI/2 );
    geo::copy({{2, s1}}, ovvv);
    
    surfa.push_back({2,ovvv.back().second}); //side 6
    geo::rotate( {{2,ovvv.back().second}}, x,y,z , 0,r1,0 , -M_PI/2 );
    linessave.push_back({1,ovvv.back().first});
    
    //============================================================

    // SPHERE 2: ROTATE SURFACE
    surfa.push_back({2,s2}); //side 1
    geo::copy({{2, s2}}, ov);
    geo::rotate({{2,ov.back().second}}, x-S,y,z , 1,0,0 , M_PI/2 );
    
    //PHYSICAL NAMING
    int pg = model::addPhysicalGroup(2,{s1}); model::setPhysicalName(2,pg,"far");

}

int main(int argc, char **argv)
{
    std::vector<std::pair<int, int> > ov, ovv, ovvv, surfacetags;
    std::vector<int> surfaces, volumes, groups;
    double sep=2*atof(argv[3]), angle=atof(argv[4]);
    double r1=atof(argv[1])/2, L=atof(argv[2])*2*r1, lc=1, l=atof(argv[2])*2*r1;
    double x1=0, y1=0, z1=0;
    double x2=x1-sep*cos(angle*M_PI/180)    , y2=y1        , z2=z1;
    double xc=(x1-sep*cos(angle*M_PI/180))/2, yc=(y1-y2)/2 , zc=(z1-z2)/2;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");
    
    //create sphere
    squareMesh( xc, yc, zc, sep, l);
    sphereMesh(x1,y1,z1,r1,l,lc,surfaces,volumes,sep);
    //sphereMesh(x2,y2,z2,r1,l,lc,surfaces,volumes,2,sep);

    // MESH
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(2);
    gmsh::model::mesh::removeDuplicateNodes();
    //gmsh::model::geo::removeAllDuplicates();
    //gmsh::model::geo::symmetrize({{3,6}}, 10,0,0,0);
    //gmsh::model::mesh::refine();
    //gmsh::model::mesh::smooth();
    //gmsh::model::mesh::setOrder(2);
    //gmsh::model::mesh::recombine("sphere1");
    
    // OUTPUT
    //gmsh::write("msh/spherical.cgns");
    //gmsh::write("mesh_sphere.msh");
    //gmsh::write("mesh_sphere.su2");
    //gmsh::write("mesh_sphere.vtk");
    //gmsh::view::add("test");
    gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}
