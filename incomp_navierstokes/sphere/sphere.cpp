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
#define Growth 1.3
#define QuarterNodes 50
#define CircleNodes 50
#define AZIMUTH_ELEMENTS 50
namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void sphereMesh(double x, double y, double z, double r1, double r2, int v1, std::vector<int> &boundaries, std::vector<int> &surfaces){
    /*
     * POINTS
     */
    std::vector<std::pair<int, int> > ov, ovv, surfa;
    //center
    int p1 = geo::addPoint(x   , y    , z, 1e-1);
    //inner circle points
    int p2 = geo::addPoint(x+r1, y    , z, 1e-1);
    int p3 = geo::addPoint(x   , y+r1 , z, 1e-1);
    int p4 = geo::addPoint(x-r1, y    , z, 1e-1);
    //outer circle points
    int p5 = geo::addPoint(x-r2, y    , z, 1e-1);
    int p6 = geo::addPoint(x   , y+r2 , z, 1e-1);
    int p7 = geo::addPoint(x+r2, y    , z, 1e-1);
    //bottom inner circle points
    int p8 = geo::addPoint(x   , y-r1 , z, 1e-1);
    int p9 = geo::addPoint(x   , y+r1 , z, 1e-1);

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
    //mesh::setTransfiniteSurface(s1, "Left", {p4 , p5 , p3 , p6});
    //mesh::setTransfiniteSurface(s2, "Left", {p7 , p2 , p3 , p6});
    //recombine triangles into quadrangles
    //mesh::setRecombine(2, s1);
    //mesh::setRecombine(2, s2);

    /*
     * SPHERICAL VOLUME SETUP
     */
    geo::revolve({{2,s1}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell1 = ov[2].second;
    int Oshell1 = ov[4].second;

    geo::revolve({{2,24}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell2 = ov[2].second;
    int Oshell2 = ov[4].second;

    geo::revolve({{2,41}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell3 = ov[2].second;
    int Oshell3 = ov[4].second;

    geo::revolve({{2,58}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell4 = ov[2].second;
    int Oshell4 = ov[4].second;

    geo::revolve({{2,s2}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell5 = ov[2].second;
    int Oshell5 = ov[4].second;
    
    geo::revolve({{2,91}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell6 = ov[2].second;
    int Oshell6 = ov[4].second;
    
    geo::revolve({{2,108}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell7 = ov[2].second;
    int Oshell7 = ov[4].second;
    
    geo::revolve({{2,125}}, 0,0,0, 1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell8 = ov[2].second;
    int Oshell8 = ov[4].second;
    
    /*
     * PHYSICAL GROUPS
     */
    //curves
    //int pg1 = model::addPhysicalGroup(1, {c1});
    //int pg2 = model::addPhysicalGroup(1, {c3});
    //set surface physical group
    //int pg3 = gmsh::model::addPhysicalGroup(2, {s1});
    //int pg4 = gmsh::model::addPhysicalGroup(2, {s2});
    
    int outershell1 = gmsh::model::addPhysicalGroup(2, {Oshell1});
    int outershell2 = gmsh::model::addPhysicalGroup(2, {Oshell2});
    int outershell3 = gmsh::model::addPhysicalGroup(2, {Oshell3});
    int outershell4 = gmsh::model::addPhysicalGroup(2, {Oshell4});
    int outershell5 = gmsh::model::addPhysicalGroup(2, {Oshell5});
    int outershell6 = gmsh::model::addPhysicalGroup(2, {Oshell6});
    int outershell7 = gmsh::model::addPhysicalGroup(2, {Oshell7});
    int outershell8 = gmsh::model::addPhysicalGroup(2, {Oshell8});
    int innershell1 = gmsh::model::addPhysicalGroup(2, {Ishell1});
    int innershell2 = gmsh::model::addPhysicalGroup(2, {Ishell2});
    int innershell3 = gmsh::model::addPhysicalGroup(2, {Ishell3});
    int innershell4 = gmsh::model::addPhysicalGroup(2, {Ishell4});
    int innershell5 = gmsh::model::addPhysicalGroup(2, {Ishell5});
    int innershell6 = gmsh::model::addPhysicalGroup(2, {Ishell6});
    int innershell7 = gmsh::model::addPhysicalGroup(2, {Ishell7});
    int innershell8 = gmsh::model::addPhysicalGroup(2, {Ishell8});
    //set volume group
    int pg9 = model::addPhysicalGroup(3, {v1});
    int pg10 = model::addPhysicalGroup(3, {v1+1});
    int pg11 = model::addPhysicalGroup(3, {v1+2});
    int pg12 = model::addPhysicalGroup(3, {v1+3});
    int pg13 = model::addPhysicalGroup(3, {v1+4});
    int pg14 = model::addPhysicalGroup(3, {v1+5});
    int pg15 = model::addPhysicalGroup(3, {v1+6});
    int pg16 = model::addPhysicalGroup(3, {v1+7});

    model::setPhysicalName(2, outershell1, "far1");
    model::setPhysicalName(2, outershell2, "far2");
    model::setPhysicalName(2, outershell3, "far3");
    model::setPhysicalName(2, outershell4, "far4");
    model::setPhysicalName(2, outershell5, "far5");
    model::setPhysicalName(2, outershell6, "far6");
    model::setPhysicalName(2, outershell7, "far7");
    model::setPhysicalName(2, outershell8, "far8");
    model::setPhysicalName(2, innershell1, "bound1");
    model::setPhysicalName(2, innershell2, "bound2");
    model::setPhysicalName(2, innershell3, "bound3");
    model::setPhysicalName(2, innershell4, "bound4");
    model::setPhysicalName(2, innershell5, "bound5");
    model::setPhysicalName(2, innershell6, "bound6");
    model::setPhysicalName(2, innershell7, "bound7");
    model::setPhysicalName(2, innershell8, "bound8");
    //model::setPhysicalName(1, pg1, "circle1");
    //model::setPhysicalName(1, pg2, "circle2");
    //model::setPhysicalName(2, pg3, "circleFace1");
    //model::setPhysicalName(2, pg4, "circleFace2");
    model::setPhysicalName(3, pg9, "quadrantSphere1");
    model::setPhysicalName(3, pg10, "quadrantSphere2");
    model::setPhysicalName(3, pg11, "quadrantSphere3");
    model::setPhysicalName(3, pg12, "quadrantSphere4");
    model::setPhysicalName(3, pg13, "quadrantSphere5");
    model::setPhysicalName(3, pg14, "quadrantSphere6");
    model::setPhysicalName(3, pg15, "quadrantSphere7");
    model::setPhysicalName(3, pg16, "quadrantSphere8");
    /*
     * SAVE TO ARRAY
     */
    //save circle boundary curves
    //boundaries.push_back(c1);
    //boundaries.push_back(c2);
    //save spherical shell surfaces
    //surfaces.push_back(s1);
    //surfaces.push_back(s2);
    //save physical groups
    //groups.push_back(pg1)
}

int main(int argc, char **argv)
{
    std::vector<int> boundaries, surfaces, groups;
    double x=0, y=0, z=0, r1=atof(argv[1]), r2=r1*atof(argv[2]), lc=1e-1;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");

    //create sphere
    sphereMesh(x,y,z,r1,r2,1,boundaries,surfaces);
    
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(3);
    gmsh::write("msh/sphere.msh");
    gmsh::write("msh/sphere.su2");
    gmsh::write("msh/sphere.vtk");
    //gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}
