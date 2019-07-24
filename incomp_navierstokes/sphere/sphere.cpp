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
#define Growth 1
#define QuarterNodes 40
#define CircleNodes 40
#define AZIMUTH_ELEMENTS 40
namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;
namespace factory = gmsh::model::geo;

void sphereMesh2(double x1, double y1, double z1, double x2, double y2, double z2, double r1, double r2, double l, std::vector<int> &boundaries, std::vector<int> &surfaces, int sphere_tag){
    /*
     * POINTS
     */
    int v1=1;
    std::vector<std::pair<int, int> > ov, surfa;
    std::vector<std::pair<int, int> > ov2;
    std::vector<std::vector<std::pair<int, int> > > ovv;
    double lc=1;
    
    //SPHERE1 - center
    int p1 = geo::addPoint(x1   , y1    , z1, lc);
    //inner circle points
    int p2 = geo::addPoint(x1+r1, y1    , z1, lc);
    int p3 = geo::addPoint(x1   , y1+r1 , z1, lc);
    int p4 = geo::addPoint(x1-r1, y1    , z1, lc);
    //outer circle points
    int p5 = geo::addPoint(x1-r2, y1    , z1, lc);
    int p6 = geo::addPoint(x1+l/4   , y1+r2+l/2 , z1, lc);
    int p7 = geo::addPoint(x1+l/2+r2, y1, z1, lc);
    //bottom inner circle points
    int p8 = geo::addPoint(x1   , y1-r1 , z1, lc);
    int p9 = geo::addPoint(x1   , y1+r1 , z1, lc);
    
    int pc1 = geo::addPoint(l/4   , y1 , z1, lc);
    //
    //BOUNDARY SETUP
    //
    //circle lines -> zenith angle
    int c1 = geo::addCircleArc(p4, p1, p3); mesh::setTransfiniteCurve(c1,CircleNodes,"Progression",1);
    int c3 = geo::addCircleArc(p2, p1, p3); mesh::setTransfiniteCurve(c3,CircleNodes,"Progression",1);
    //int c2 = geo::addCircleArc(p5, p1, p6); mesh::setTransfiniteCurve(c2,CircleNodes,"Progression",1);
    int c2 = geo::addEllipseArc(p5, pc1, p6, p6); mesh::setTransfiniteCurve(c2,CircleNodes,"Progression",1);
    //int c4 = geo::addCircleArc(p7, p1, p6); mesh::setTransfiniteCurve(c4,CircleNodes,"Progression",1);
    //int c4 = geo::addSpline({p7, p6}); mesh::setTransfiniteCurve(c4,CircleNodes,"Progression",1);
    int c4 = geo::addEllipseArc(p6, pc1, p7, p7); mesh::setTransfiniteCurve(c4,CircleNodes,"Progression",1);
    //outer circle lines -> radial direction
    int l5 = geo::addLine(p4, p5); mesh::setTransfiniteCurve(l5,QuarterNodes,"Progression",Growth);
    int l6 = geo::addLine(p2, p7); mesh::setTransfiniteCurve(l6,QuarterNodes,"Progression",Growth);
    int l7 = geo::addLine(p3, p6); mesh::setTransfiniteCurve(l7,QuarterNodes,"Progression",Growth);
    
    //
    // HEMISPHERICAL SLICE SETUP
    //
    int cl1 = geo::addCurveLoop({-l5, c1, l7, -c2}); int s1 = geo::addPlaneSurface({cl1});
    int cl2 = geo::addCurveLoop({c3, l7, c4, -l6}); int s2 = geo::addPlaneSurface({cl2});
    mesh::setTransfiniteSurface(s1, "Left", {p4 , p5 , p3 , p6});
    mesh::setTransfiniteSurface(s2, "Left", {p7 , p2 , p3 , p6});
    //recombine triangles into quadrangles
    mesh::setRecombine(2, s1);
    mesh::setRecombine(2, s2);
    
    //
    // SPHERICAL VOLUME SETUP
    //
    geo::revolve({{2,s1}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell1 = ov[2].second;
    int Oshell1 = ov[4].second;
    
    geo::revolve({{2,24}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell2 = ov[2].second;
    int Oshell2 = ov[4].second;
    
    geo::revolve({{2,41}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell3 = ov[2].second;
    int Oshell3 = ov[4].second;
    
    geo::revolve({{2,58}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell4 = ov[2].second;
    int Oshell4 = ov[4].second;
    
    geo::revolve({{2,s2}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell5 = ov[2].second;
    int Oshell5 = ov[4].second;
    
    geo::revolve({{2,91}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell6 = ov[2].second;
    int Oshell6 = ov[4].second;
    
    geo::revolve({{2,108}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell7 = ov[2].second;
    int Oshell7 = ov[4].second;
    
    geo::revolve({{2,125}}, x1,y1,z1, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell8 = ov[2].second;
    int Oshell8 = ov[4].second;
    
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
    
    // SPHERE2 - center
    int p11 = geo::addPoint(x2   , y2    , z2, lc);
    //inner circle points
    int p12 = geo::addPoint(x2+r1, y2    , z2, lc);
    int p13 = geo::addPoint(x2   , y2+r1 , z2, lc);
    int p14 = geo::addPoint(x2-r1, y2    , z2, lc);
    //outer circle points
    int p15 = geo::addPoint(x2-l/2-r2, y2    , z2, lc);
    int p16 = geo::addPoint(x2-l/4, y2+r2+l/2 , z2, lc);
    int p17 = geo::addPoint(x2+r2, y2    , z2, lc);
    //bottom inner circle points
    int p18 = geo::addPoint(x2   , y2-r1 , z2, lc);
    int p19 = geo::addPoint(x2   , y2+r1 , z2, lc);
    
    int pc11 = geo::addPoint(x2-l/4, y2 , z2, lc);
    //sphere2
    //circle lines -> zenith angle
    int c5 = geo::addCircleArc(p14, p11, p13); mesh::setTransfiniteCurve(c5,CircleNodes,"Progression",1);
    int c6 = geo::addCircleArc(p12, p11, p13); mesh::setTransfiniteCurve(c6,CircleNodes,"Progression",1);
    int c7 = geo::addEllipseArc(p16, pc11, p15, p15); mesh::setTransfiniteCurve(c7,CircleNodes,"Progression",1);
    int c8 = geo::addEllipseArc(p16, pc11, p17, p17); mesh::setTransfiniteCurve(c8,CircleNodes,"Progression",1);
    //outer circle lines -> radial direction
    int l8 = geo::addLine(p14, p15); mesh::setTransfiniteCurve(l8,QuarterNodes,"Progression",Growth);
    int l9 = geo::addLine(p12, p17); mesh::setTransfiniteCurve(l9,QuarterNodes,"Progression",Growth);
    int l10 = geo::addLine(p13, p16); mesh::setTransfiniteCurve(l10,QuarterNodes,"Progression",Growth);
    
    /*
     * HEMISPHERICAL SURFACE SETUP
     */
    //int cl1 = geo::addCurveLoop({-l5, c1, l7, -c2}); int s1 = geo::addPlaneSurface({cl1});
    //int cl2 = geo::addCurveLoop({c3, l7, -c4, -l6}); int s2 = geo::addPlaneSurface({cl2});
    
    int cl3 = geo::addCurveLoop({-l8, c5, l10, c7}); int s3 = geo::addPlaneSurface({cl3});
    int cl4 = geo::addCurveLoop({c6, l10, c8, -l9}); int s4 = geo::addPlaneSurface({cl4});
    mesh::setTransfiniteSurface(s3, "Left");
    mesh::setTransfiniteSurface(s4, "Left");
    //recombine triangles into quadrangles
    mesh::setRecombine(2, s3);
    mesh::setRecombine(2, s4);
    
    //
    // SPHERICAL VOLUME SETUP
    //
    geo::revolve({{2,s3}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell9 = ov[2].second;
    int Oshell9 = ov[4].second;
    
    geo::revolve({{2,159}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell10 = ov[2].second;
    int Oshell10 = ov[4].second;
    
    geo::revolve({{2,176}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell11 = ov[2].second;
    int Oshell11 = ov[4].second;
    
    geo::revolve({{2,193}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell12 = ov[2].second;
    int Oshell12 = ov[4].second;
    
    geo::revolve({{2,s4}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell13 = ov[2].second;
    int Oshell13 = ov[4].second;
    
    geo::revolve({{2,226}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell14 = ov[2].second;
    int Oshell14 = ov[4].second;
    
    geo::revolve({{2,243}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell15 = ov[2].second;
    int Oshell15 = ov[4].second;
    
    geo::revolve({{2,260}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell16 = ov[2].second;
    int Oshell16 = ov[4].second;
    
    //
    // ENCLOSURE
    //
    
    //top plane
    int p21 = geo::addPoint( x1-r2 , r2 , 0, 1); //85
    
    //int l11 = geo::addEllipseArc(85, 5, 86, 86, 1000);
    //int l11 = geo::addLine(48, 85, 1000);
    int l11 = geo::addLine(49, 6, 1000); //49 instead of 48
    //int l12 = geo::addLine(5, 85, 1001);
    //int l13 = geo::addLine(p26, p22,1002);
    
    int cl5 = geo::addCurveLoop({1000, -3, -116 });
    int s5 = geo::addPlaneSurface({cl5});
    
    geo::revolve({{2,s5}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell17 = ov[2].second;
    int Oshell17 = ov[4].second;
    
    geo::revolve({{2,1015}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell18 = ov[2].second;
    int Oshell18 = ov[4].second;
    
    geo::revolve({{2,1030}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell19 = ov[2].second;
    int Oshell19 = ov[4].second;
    
    geo::revolve({{2,1045}}, x2,y2,z2, r1,0,0, M_PI/2, ov, {AZIMUTH_ELEMENTS}, {}, true);
    int Ishell20 = ov[2].second;
    int Oshell20 = ov[4].second;
    
    mesh::setTransfiniteCurve(l11,CircleNodes,"Progression",1);
    mesh::setTransfiniteCurve(1017,CircleNodes,"Progression",1);
    mesh::setTransfiniteCurve(1032,CircleNodes,"Progression",1);
    mesh::setTransfiniteCurve(1000,CircleNodes,"Progression",1);
    
    //PHYSICAL GROUPS
    //factory::addSurfaceLoop({Oshell1, Oshell2, Oshell3, Oshell4, Oshell5, Oshell6, Oshell7, Oshell8, Oshell9, Oshell10, Oshell11, Oshell12, Oshell13, Oshell14, Oshell15, Oshell16,s5,s6,s7,s8,s9,s10},128);
    //factory::addVolume({128}, 129);
    
    //int outershell1 = gmsh::model::addPhysicalGroup(2, {Oshell17,Oshell18,Oshell19,Oshell20});
    int outershell1 = gmsh::model::addPhysicalGroup(2, {106,123,140,89,1008,1023,1038,1053,158,175,192,209});
    int innershell1 = gmsh::model::addPhysicalGroup(2, {Ishell1,Ishell2,Ishell3,Ishell4,Ishell5,Ishell6,Ishell7,Ishell8});
    int innershell2 = gmsh::model::addPhysicalGroup(2, {Ishell9,Ishell10,Ishell11,Ishell12,Ishell13,Ishell14,Ishell15,Ishell16});
    int pg9 = model::addPhysicalGroup(3, {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});
    
    model::setPhysicalName(2, outershell1, "far");
    model::setPhysicalName(2, innershell1, "shell1");
    model::setPhysicalName(2, innershell2, "shell2");
    model::setPhysicalName(3, pg9, "volume");
    
}

int main(int argc, char **argv){
    std::vector<int> boundaries, surfaces, groups;
    double sep=atof(argv[3]), angle=atof(argv[4]);
    double x1=0, y1=0, z1=0;
    double x2=x1-sep*cos(angle*M_PI/180), y2=y1+sep*sin(angle*M_PI/180), z2=z1-0;
    double r1=atof(argv[1])/2;
    double r2=abs(x1-x2)/2.;
    double size=0.15, l=atof(argv[2]);
    
    //options
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    //gmsh::option::setNumber("Mesh.Algorithm", 6);
    //gmsh::option::setNumber("Mesh.Algorithm3D", 10);
    gmsh::option::setNumber("Mesh.CharacteristicLengthMin", size);
    gmsh::option::setNumber("Mesh.CharacteristicLengthMax", size);
    //gmsh::model::add("sphere1");
    
    //create sphere
    sphereMesh2(x1,y1,z1,x2,y2,z2,r1,r2,l,boundaries,surfaces,1);
    
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(3);
    gmsh::option::setNumber("Mesh.Smoothing", 100);
    //gmsh::write("mesh_sphere.msh");
    gmsh::write("mesh_sphere.su2");
    gmsh::write("mesh_sphere.vtk");
    gmsh::fltk::run();
    //gmsh::finalize();
    return 0;
    
}
