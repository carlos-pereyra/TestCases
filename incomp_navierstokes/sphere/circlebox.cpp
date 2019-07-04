/*
 * Author: Carlos Pereyra
 * Purpose: Create mesh of circle in a box
 * Use: g++ -std=c++11 -Iinclude circleBox.cpp -o circ -lgmsh
 * Use: ./circ
 * Use: gmsh msh/circbox.msh
 *
 */

// The Gmsh API is entirely defined in the <gmsh.h> header. Read this file: it
// contains the documentation for all the functions in the API.
#include <iostream>
#include <cstdio>
#include <gmsh.h>
using namespace std;
#define Increase 1.2 // growth
#define QuarterNodes 20
#define CircleNodes 80

void circ(double x, double y, double r1, double r2, double lc, std::vector<int> &boundaries, std::vector<int> &surfaces){
    //inner circle points
    int p1 = gmsh::model::geo::addPoint(x   , y-r1 , 0, lc, 10);
    int p2 = gmsh::model::geo::addPoint(x   , y+r1 , 0, lc, 11);
    int p3 = gmsh::model::geo::addPoint(x+r1, y    , 0, lc, 12);
    int p4 = gmsh::model::geo::addPoint(x-r1, y    , 0, lc, 13);
    //outer circle points
    int p5 = gmsh::model::geo::addPoint(x   , y-r2 , 0, lc, 14);
    int p6 = gmsh::model::geo::addPoint(x   , y+r2 , 0, lc, 15);
    int p7 = gmsh::model::geo::addPoint(x+r2, y    , 0, lc, 16);
    int p8 = gmsh::model::geo::addPoint(x-r2, y    , 0, lc, 17);
    //center of circle
    int p9 = gmsh::model::geo::addPoint(x   , y    , 0, lc, 18);
    
    cout<<"circ p1= "<<p1<<" p2= "<<p2<<" p3= "<<p3<<" p4= "<<p4<<" p5= "<<p5<<" p6= "<<p6<<" p7= "<<p7<<" p8= "<<p8<<" p9= "<<p9 << endl;

    
    /*
     * BOUNDARY SETUP
     */
    //inner circle lines
    int l1 = gmsh::model::geo::addCircleArc(p4, p9, p2); //tl
    int l2 = gmsh::model::geo::addCircleArc(p2, p9, p3); //tr
    int l3 = gmsh::model::geo::addCircleArc(p3, p9, p1); //br
    int l4 = gmsh::model::geo::addCircleArc(p1, p9, p4); //bl
    //outer circle lines
    int l5 = gmsh::model::geo::addCircleArc(p6, p9, p7); //tr
    int l6 = gmsh::model::geo::addCircleArc(p7, p9, p5); //br
    int l7 = gmsh::model::geo::addCircleArc(p5, p9, p8); //bl
    int l8 = gmsh::model::geo::addCircleArc(p8, p9, p6); //tl
    //quarter lines
    int l9 = gmsh::model::geo::addLine(p1, p5); //bottom
    int l10 = gmsh::model::geo::addLine(p3, p7); //right
    int l11 = gmsh::model::geo::addLine(p2, p6); //top
    int l12 = gmsh::model::geo::addLine(p4, p8); //left
    //transfinite circle lines - AZUMITHAL Direction
    gmsh::model::geo::mesh::setTransfiniteCurve(l1,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l2,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l4,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l3,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l8,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l5,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l7,CircleNodes,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l6,CircleNodes,"Progression",1);
    //transfinite quarter lines - RADIAL Direction
    gmsh::model::geo::mesh::setTransfiniteCurve(l9,QuarterNodes,"Progression",Increase);
    gmsh::model::geo::mesh::setTransfiniteCurve(l10,QuarterNodes,"Progression",Increase);
    gmsh::model::geo::mesh::setTransfiniteCurve(l11,QuarterNodes,"Progression",Increase);
    gmsh::model::geo::mesh::setTransfiniteCurve(l12,QuarterNodes,"Progression",Increase);
    //set cylindrical boundary physical group names
    int pgl1 = gmsh::model::addPhysicalGroup(1, {l1}); //, 1
    int pgl2 = gmsh::model::addPhysicalGroup(1, {l2}); //, 2
    int pgl3 = gmsh::model::addPhysicalGroup(1, {l3}); //, 3
    int pgl4 = gmsh::model::addPhysicalGroup(1, {l4}); //, 4
    gmsh::model::setPhysicalName(1, pgl1, "circleBoundary1");
    gmsh::model::setPhysicalName(1, pgl2, "circleBoundary2");
    gmsh::model::setPhysicalName(1, pgl3, "circleBoundary3");
    gmsh::model::setPhysicalName(1, pgl4, "circleBoundary4");

    /*
     * SURFACE SETUP
     */
    //construct curve loops.
    int cl1 = gmsh::model::geo::addCurveLoop({l2, l10, -l5, -l11}); //top-right
    int cl2 = gmsh::model::geo::addCurveLoop({l8, -l11, -l1, l12}); //top-left
    int cl3 = gmsh::model::geo::addCurveLoop({l4, l12, -l7, -l9}); //bottom-left
    int cl4 = gmsh::model::geo::addCurveLoop({l10, l6, -l9, -l3}); //bottom-right
    //circular surface area
    int s1 = gmsh::model::geo::addPlaneSurface({cl1});
    int s2 = gmsh::model::geo::addPlaneSurface({cl2});
    int s3 = gmsh::model::geo::addPlaneSurface({cl3});
    int s4 = gmsh::model::geo::addPlaneSurface({cl4});
    //transfinite interpolation
    gmsh::model::geo::mesh::setTransfiniteSurface(s1, "Left", {p6 , p7 , p3 , p2});
    gmsh::model::geo::mesh::setTransfiniteSurface(s2, "Left", {p8 , p6 , p2 , p4});
    gmsh::model::geo::mesh::setTransfiniteSurface(s3, "Left", {p5 , p8 , p4 , p1});
    gmsh::model::geo::mesh::setTransfiniteSurface(s4, "Left", {p7 , p5 , p1 , p3});
    //recombine triangles into quadrangles) are supported
    gmsh::model::geo::mesh::setRecombine(2, s1);
    gmsh::model::geo::mesh::setRecombine(2, s2);
    gmsh::model::geo::mesh::setRecombine(2, s3);
    gmsh::model::geo::mesh::setRecombine(2, s4);
    //set surface physical group names
    int pgs1 = gmsh::model::addPhysicalGroup(2, {s1}); //, 1
    int pgs2 = gmsh::model::addPhysicalGroup(2, {s2}); //, 2
    int pgs3 = gmsh::model::addPhysicalGroup(2, {s3}); //, 3
    int pgs4 = gmsh::model::addPhysicalGroup(2, {s4}); //, 4
    gmsh::model::setPhysicalName(2, pgs1, "circleSurface1");
    gmsh::model::setPhysicalName(2, pgs2, "circleSurface2");
    gmsh::model::setPhysicalName(2, pgs3, "circleSurface3");
    gmsh::model::setPhysicalName(2, pgs4, "circleSurface4");
    
    /*
     * SAVE TO ARRAY
     */
    //save circle boundary curves
    boundaries.push_back(l5);
    boundaries.push_back(l6);
    boundaries.push_back(l7);
    boundaries.push_back(l8);
    //save circle surfaces
    surfaces.push_back(s1);
    surfaces.push_back(s2);
    surfaces.push_back(s3);
    surfaces.push_back(s4);
}

int main(int argc, char **argv)
{
    std::vector<int> boundaries, surfaces;
    double x=0, y=0, r1=1, r2=r1+atof(argv[1]), l=20, lc=1e-1;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("circle1");

    //box points
    int pb1 = gmsh::model::geo::addPoint( -l, -l, 0, lc);
    int pb2 = gmsh::model::geo::addPoint( -l,  l, 0, lc);
    int pb3 = gmsh::model::geo::addPoint(  l,  l, 0, lc);
    int pb4 = gmsh::model::geo::addPoint(  l, -l, 0, lc);
    
    //box lines
    int l1 = gmsh::model::geo::addLine(pb4, pb1);
    int l2 = gmsh::model::geo::addLine(pb1, pb2);
    int l3 = gmsh::model::geo::addLine(pb3, pb4);
    int l4 = gmsh::model::geo::addLine(pb2, pb3);
    gmsh::model::geo::mesh::setTransfiniteCurve(l1,21,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l2,21,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l4,21,"Progression",1);
    gmsh::model::geo::mesh::setTransfiniteCurve(l3,21,"Progression",1);
    
    //box physical line and names
    int pgl1 = gmsh::model::addPhysicalGroup(1, {l1}); //, 9 inlet
    int pgl2 = gmsh::model::addPhysicalGroup(1, {l2}); //, 10 wall1
    int pgl3 = gmsh::model::addPhysicalGroup(1, {l3}); //, 11 outlet
    int pgl4 = gmsh::model::addPhysicalGroup(1, {l4}); //, 12 wall2
    gmsh::model::setPhysicalName(1, pgl1, "inlet");
    gmsh::model::setPhysicalName(1, pgl2, "wall1");
    gmsh::model::setPhysicalName(1, pgl3, "wall2");
    gmsh::model::setPhysicalName(1, pgl4, "outlet");
    
    //box-circle curve line
    int cl0 = gmsh::model::geo::addCurveLoop({l1, l2, l3, l4});

    //create circle
    circ(x,y,r1,r2,lc,boundaries,surfaces);
    
    //circle curve loop
    int cl5 = gmsh::model::geo::addCurveLoop({boundaries.at(0),boundaries.at(1),boundaries.at(2),boundaries.at(3)});
    
    //box to circle surface area
    int newsurtag = surfaces.back()+boundaries.back()+1;
    int s1 = gmsh::model::geo::addPlaneSurface({cl5,cl0});
    int ps1 = gmsh::model::addPhysicalGroup(2, {s1}, newsurtag);
    gmsh::model::setPhysicalName(2, newsurtag, "boxSurface");

    // Before it can be meshed, the internal CAD representation must be
    // synchronized with the Gmsh model, which will create the relevant Gmsh data
    // structures. This is achieved by the gmsh::model::geo::synchronize() API
    // call for the built-in CAD kernel. Synchronizations can be called at any
    // time, but they involve a non trivial amount of processing; so while you
    // could synchronize the internal CAD data after every CAD command, it is
    // usually better to minimize the number of synchronization points.
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(2);
    gmsh::write("msh/circbox.msh");
    gmsh::write("msh/circbox.su2");
    gmsh::finalize();
    return 0;
}
