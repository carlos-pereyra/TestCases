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
#define QuarterNodes 10
#define CircleNodes 10

namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void sphereMesh(double x, double y, double z, double r1, double r2, double l, double lc, std::vector<int> &boundaries, std::vector<int> &surfaces){
    /*
     * POINTS
     */
    std::vector<std::pair<int, int> > ov, surfa;
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
    int p11 = geo::addPoint( l+x,    0,    0, lc,1000); //2
    int p12 = geo::addPoint(   0,  l+y,    0, lc,1001); //3
    int p13 = geo::addPoint(   0,    0,  l+z, lc,1002); //4
    int p14 = geo::addPoint(-l+x,    0,    0, lc,1003); //5
    int p15 = geo::addPoint(   0,  -l+y,    0, lc,1004); //3
    int p16 = geo::addPoint(   0,    0,  -l+z, lc,1005); //4
    int p19 = geo::addPoint( 0, l+y,  l+z, lc,1008); //4
    int p20 = geo::addPoint( l+x, 0,  l+z, lc,1009); //4
    int p21 = geo::addPoint(-l+x, 0,  l+z, lc,1010); //4
    
    int p22 = geo::addPoint( l+x, l+y,  l+z, lc,1011); //4
    int p23 = geo::addPoint(-l+x, l+y,  l+z, lc,1012); //4
    int p24 = geo::addPoint( l+x, -l+y, l+z, lc,1013); //4
    int p25 = geo::addPoint(-l+x, -l+y, l+z, lc,1014); //4

    int p17 = geo::addPoint( l+x, l+y,  0, lc,1006); //4
    int p18 = geo::addPoint(-l+x, l+y,  0, lc,1007); //4
    int p26 = geo::addPoint( l+x, -l+y, 0, lc,1015); //4
    int p27 = geo::addPoint(-l+x, -l+y, 0, lc,1016); //4

    int p29 = geo::addPoint(   0, -l+y, l+z, lc,1017); //4
    int p30 = geo::addPoint(   0, -l+y,-l+z, lc,1018); //4
    int p31 = geo::addPoint( l+x, -l+y,-l+z, lc,1019); //4
    int p32 = geo::addPoint( l+x,    0,-l+z, lc,1020); //4

    int p33 = geo::addPoint(-l+x, -l+y,-l+z, lc,1021); //4
    int p34 = geo::addPoint(-l+x,    0,-l+z, lc,1022); //4
    int p35 = geo::addPoint( l+x,  l+y,-l+z, lc,1023); //4
    int p36 = geo::addPoint(-l+x,  l+y,-l+z, lc,1024); //4

    int p37 = geo::addPoint(   0,  l+y,-l+z, lc,1025); //4

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
    geo::revolve({{2,s1}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,24}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,41}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,58}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,s2}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,91}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,108}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);
    geo::revolve({{2,125}}, 0,0,0, 1,0,0, M_PI/2, ov, {5}, {}, true);

    
    int l8 = geo::addLine(6, 1001); mesh::setTransfiniteCurve(l8,QuarterNodes,"Progression",Growth);//113
    int l9 = geo::addLine(7, 1000); mesh::setTransfiniteCurve(l9,QuarterNodes,"Progression",Growth);//114
    int l10 = geo::addLine(5, 1003); mesh::setTransfiniteCurve(l10,QuarterNodes,"Progression",Growth);//115
    int l11 = geo::addLine(1047, 1004); mesh::setTransfiniteCurve(l11,QuarterNodes,"Progression",Growth);//116
    
    int l13 = geo::addLine(1000, 1006); mesh::setTransfiniteCurve(l13,QuarterNodes,"Progression",Growth); //117
    int l14 = geo::addLine(1006, 1001); mesh::setTransfiniteCurve(l14,QuarterNodes,"Progression",Growth); //119
    int l15 = geo::addLine(1001, 1008); mesh::setTransfiniteCurve(l15,QuarterNodes,"Progression",Growth);
    
    int l16 = geo::addLine(1008, 1002); mesh::setTransfiniteCurve(l16,QuarterNodes,"Progression",Growth);
    int l17 = geo::addLine(1002, 1009); mesh::setTransfiniteCurve(l17,QuarterNodes,"Progression",Growth);
    int l18 = geo::addLine(1009, 1011); mesh::setTransfiniteCurve(l18,QuarterNodes,"Progression",Growth);
    int l19 = geo::addLine(1008, 1011); mesh::setTransfiniteCurve(l19,QuarterNodes,"Progression",Growth);

    int l20 = geo::addLine(1011, 1006); mesh::setTransfiniteCurve(l20,QuarterNodes,"Progression",Growth); //
    int l21 = geo::addLine(1009, 1000); mesh::setTransfiniteCurve(l21,QuarterNodes,"Progression",Growth);
    int l22 = geo::addLine(1002, 1010); mesh::setTransfiniteCurve(l22,QuarterNodes,"Progression",Growth);
    int l23 = geo::addLine(1010, 1012); mesh::setTransfiniteCurve(l23,QuarterNodes,"Progression",Growth);

    int l24 = geo::addLine(1012, 1008); mesh::setTransfiniteCurve(l24,QuarterNodes,"Progression",Growth);
    int l25 = geo::addLine(1010, 1003); mesh::setTransfiniteCurve(l25,QuarterNodes,"Progression",Growth);
    int l26 = geo::addLine(1012, 1007); mesh::setTransfiniteCurve(l26,QuarterNodes,"Progression",Growth);
    int l27 = geo::addLine(1007, 1001); mesh::setTransfiniteCurve(l27,QuarterNodes,"Progression",Growth);
    
    int l28 = geo::addLine(1007, 1003); mesh::setTransfiniteCurve(l28,QuarterNodes,"Progression",Growth);
    int l29 = geo::addLine(1036, 1002); mesh::setTransfiniteCurve(l29,QuarterNodes,"Progression",Growth); //
    int l30 = geo::addLine(1006, 1023); mesh::setTransfiniteCurve(l30,QuarterNodes,"Progression",Growth); //-135
    int l31 = geo::addLine(1001, 1025); mesh::setTransfiniteCurve(l31,QuarterNodes,"Progression",Growth); //136

    int l32 = geo::addLine(1007, 1024); mesh::setTransfiniteCurve(l32,QuarterNodes,"Progression",Growth);
    int l33 = geo::addLine(1024, 1025); mesh::setTransfiniteCurve(l33,QuarterNodes,"Progression",Growth);
    int l34 = geo::addLine(1025, 1023); mesh::setTransfiniteCurve(l34,QuarterNodes,"Progression",Growth); //+138
    int l35 = geo::addLine(1058, 1005); mesh::setTransfiniteCurve(l35,QuarterNodes,"Progression",Growth);

    int l36 = geo::addLine(1000, 1020); mesh::setTransfiniteCurve(l36,QuarterNodes,"Progression",Growth); //140
    int l37 = geo::addLine(1020, 1005); mesh::setTransfiniteCurve(l37,QuarterNodes,"Progression",Growth); //141
    int l38 = geo::addLine(1020, 1023); mesh::setTransfiniteCurve(l38,QuarterNodes,"Progression",Growth); //142
    int l39 = geo::addLine(1005, 1025); mesh::setTransfiniteCurve(l39,QuarterNodes,"Progression",Growth);

    int loop1 = geo::addCurveLoop({-134, 138, 135, 118}); int s3 = geo::addPlaneSurface({loop1});
    int loop2 = geo::addCurveLoop({70, 113, 135, -143, -139}); int s4 = geo::addPlaneSurface({loop2});
    int loop3 = geo::addCurveLoop({4, 113, -118, -117, -114}); int s5 = geo::addPlaneSurface({loop3});
    int loop4 = geo::addCurveLoop({112, 114, 140, 141, -139}); int s6 = geo::addPlaneSurface({loop4});
    int loop5 = geo::addCurveLoop({140, 142, -134, -117}); int s8 = geo::addPlaneSurface({loop5});
    int loop6 = geo::addCurveLoop({-141, 142, -138, -143}); int s9 = geo::addPlaneSurface({loop6});
    //int loop7 = geo::addCurveLoop({3, 113, -131, 132, -115}); int s7 = geo::addPlaneSurface({loop7});
    
    int sl1 = geo::addSurfaceLoop({s3,s4,s5,s6,s8,s9}); int v1 = geo::addVolume({sl1});
    
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
    double x=0, y=0, z=0, r1=atof(argv[1]), r2=r1+1, l=r1*2*atof(argv[2]), lc=1e-1;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");

    //create circle
    sphereMesh(x,y,z,r1,r2,l,lc,boundaries,surfaces);
    
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
    gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}
