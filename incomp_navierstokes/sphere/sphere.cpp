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
#include <cmath>
#include <gmsh.h>
using namespace std;
#define Growth 1.2
#define QuarterNodes 20
#define CircleNodes 20

namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void sphereMesh(double x, double y, double r1, double r2, double lc, std::vector<int> &boundaries, std::vector<int> &surfaces){
    /*
     * POINTS
     */
    //center
    int p1 = geo::addPoint(x   , y    , 0, lc);
    //inner circle points
    int p2 = geo::addPoint(x+r1, y    , 0, lc);
    int p3 = geo::addPoint(x   , y+r1 , 0, lc);
    int p4 = geo::addPoint(x-r1, y    , 0, lc);
    //outer circle points
    int p5 = geo::addPoint(x-r2, y    , 0, lc);
    int p6 = geo::addPoint(x   , y+r2 , 0, lc);
    int p7 = geo::addPoint(x+r2, y    , 0, lc);
    //bottom inner circle points
    int p8 = geo::addPoint(x   , y-r1 , 0, lc);
    int p9 = geo::addPoint(x   , y+r1 , 0, lc);
    //int p9 = geo::addPoint(x  , y    , z-r1, lc);
    //int p9 = geo::addPoint(x   , y    , 0   , lc);
    
    /*
     * BOUNDARY SETUP
     */
    //circle lines -> zenith angle
    int c1 = geo::addCircleArc(p4, p1, p3); mesh::setTransfiniteCurve(c1,CircleNodes,"Progression",1);
    int c3 = geo::addCircleArc(p2, p1, p3); mesh::setTransfiniteCurve(c3,CircleNodes,"Progression",1);
    int c2 = geo::addCircleArc(p5, p1, p6); mesh::setTransfiniteCurve(c2,CircleNodes,"Progression",1);
    int c4 = geo::addCircleArc(p7, p1, p6); mesh::setTransfiniteCurve(c4,CircleNodes,"Progression",1);
    //outer circle lines -> radial direction
    int l5 = geo::addLine(p4, p5); mesh::setTransfiniteCurve(l5,QuarterNodes,"Progression",Growth);
    int l6 = geo::addLine(p2, p7); mesh::setTransfiniteCurve(l6,QuarterNodes,"Progression",Growth);
    int l7 = geo::addLine(p3, p6); mesh::setTransfiniteCurve(l7,QuarterNodes,"Progression",Growth);

    /*
     * HEMISPHERICAL SLICE SETUP
     */
    int cl1 = geo::addCurveLoop({-l5, c1, l7, -c2}); int s1 = geo::addPlaneSurface({cl1});
    int cl2 = geo::addCurveLoop({c3, l7, -c4, -l6}); int s2 = geo::addPlaneSurface({cl2});
    mesh::setTransfiniteSurface(s1, "Left", {p4 , p5 , p3 , p6});
    mesh::setTransfiniteSurface(s2, "Left", {p7 , p2 , p3 , p6});
    //recombine triangles into quadrangles
    mesh::setRecombine(2, s1);
    mesh::setRecombine(2, s2);
    
    /*
     * SPHERICAL VOLUME SETUP
     */
    std::vector<std::pair<int, int> > ov;
    geo::revolve({{2,s1}}, 0,0,0, 1,0,0, M_PI, ov, {5}, {}, true); //v=1
    geo::revolve({{2,s2}}, 0,0,0, 1,0,0, M_PI, ov, {5}, {}, true); //v=2
    //geo::revolve({{2,s2}}, 0,0,0, 1,0,0, -M_PI, ov, {5}, {}, true); //v=4
    
    /*
     * PHYSICAL GROUPS
     */
    //set cylindrical boundary physical group names
    int pgl1 = model::addPhysicalGroup(1, {c1}); model::setPhysicalName(1, pgl1, "hemiLine1");
    int pgl2 = model::addPhysicalGroup(1, {c3}); model::setPhysicalName(1, pgl2, "hemiLine2");
    //set surface physical group
    int pgs1 = gmsh::model::addPhysicalGroup(2, {s1}); model::setPhysicalName(2, pgs1, "hemiFace1");
    int pgs2 = gmsh::model::addPhysicalGroup(2, {s2}); model::setPhysicalName(2, pgs2, "hemiFace2");
    //set surface physical group
    int pgv1 = model::addPhysicalGroup(3, {1}); model::setPhysicalName(3, pgv1, "quadrantSphere1");
    int pgv2 = model::addPhysicalGroup(3, {2}); model::setPhysicalName(3, pgv2, "quadrantSphere2");
    int pgv3 = model::addPhysicalGroup(3, {3}); model::setPhysicalName(3, pgv3, "quadrantSphere3");
    
    //geo::extrude({{2,s1}}, 1,0,0, 0,0,0, M_PI/2, true);
    //cout << "s1" << s1 << endl;
    //int rev1 =
    /*
     * SAVE TO ARRAY
     */
    //save circle boundary curves
    boundaries.push_back(c1);
    boundaries.push_back(c2);
    //save spherical shell surfaces
    surfaces.push_back(s1);
    surfaces.push_back(s2);
    //save physical groups
    //groups.push_back(pg1)
}

int main(int argc, char **argv)
{
    std::vector<int> boundaries, surfaces, groups;
    double x=0, y=0, r1=atof(argv[1]), r2=r1+1, l=r2*4, lc=1e-1;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");

    //create circle
    sphereMesh(x,y,r1,r2,lc,boundaries,surfaces);
    
    //box points
    /*
    int pb1 = gmsh::model::geo::addPoint( -l, -l, 0, LC);
    int pb2 = gmsh::model::geo::addPoint( -l,  l, 0, LC);
    int pb3 = gmsh::model::geo::addPoint(  l,  l, 0, LC);
    int pb4 = gmsh::model::geo::addPoint(  l, -l, 0, LC);
    
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
    //circle curve loop
    int cl5 = gmsh::model::geo::addCurveLoop({boundaries.at(0),boundaries.at(1),boundaries.at(2),boundaries.at(3)});
    
    //box to circle surface area
    int newsurtag = surfaces.back()+boundaries.back()+1;
    int s1 = gmsh::model::geo::addPlaneSurface({cl5,cl0});
    int ps1 = gmsh::model::addPhysicalGroup(2, {s1}, newsurtag);
    gmsh::model::setPhysicalName(2, newsurtag, "boxSurface");
     */
    
    // Before it can be meshed, the internal CAD representation must be
    // synchronized with the Gmsh model, which will create the relevant Gmsh data
    // structures. This is achieved by the gmsh::model::geo::synchronize() API
    // call for the built-in CAD kernel. Synchronizations can be called at any
    // time, but they involve a non trivial amount of processing; so while you
    // could synchronize the internal CAD data after every CAD command, it is
    // usually better to minimize the number of synchronization points.
    
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(3);
    gmsh::write("msh/spherical.msh");
    gmsh::write("msh/spherical.su2");
    gmsh::finalize();
    return 0;
}
