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
#define L 1
#define R1 10
#define R2 0.5
#define RAD_LAYERS 80
#define AZIMUTH_LAYERS 20
#define GROWTH 1.5

namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void sphereMesh(double x, double y, double r1, double r2, double lc, std::vector<int> &boundaries, std::vector<int> &surfaces){
    /*
     * INTERIOR SPHERE
     */
    std::vector<std::pair<int, int> > ov, ovv, ovvv, surfa, lines;

    int p0 = geo::addPoint(   0,  0,   0, L, 1);
    int p1 = geo::addPoint(  R2, R2, -R2, L, 102);
    int p2 = geo::addPoint( -R2, R2, -R2, L, 103);
    int p3 = geo::addPoint( -R2,-R2, -R2, L, 104);
    int p4 = geo::addPoint(  R2,-R2, -R2, L, 105);
    
    int c1 = geo::addCircleArc(p2, p0, p1);
    int c2 = geo::addCircleArc(p1, p0, p4);
    int c3 = geo::addCircleArc(p4, p0, p3);
    int c4 = geo::addCircleArc(p3, p0, p2);
    
    int loop1 = geo::addCurveLoop({c1,c2,c3,c4});
    int s1 = geo::addSurfaceFilling({loop1});
    
    surfa.push_back({2,s1}); //side 1
    geo::copy({{2, s1}}, ov);
    geo::rotate( {{2,ov.back().second}}, 0,0,0 , 1,0,0 , M_PI/2 );
    
    surfa.push_back({2,ov.back().second}); //side 2
    geo::copy({{2, ov.back().second}}, ov);
    geo::rotate( {{2,ov.back().second}}, 0,0,0 , 1,0,0 , M_PI/2 );
    
    surfa.push_back({2,ov.back().second}); //side 3
    geo::copy({{2,ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, 0,0,0 , 1,0,0 , M_PI/2 );
    
    surfa.push_back({2,ov.back().second}); //side 4
    
    geo::copy({{2, s1}}, ovv);
    surfa.push_back({2,ovv.back().second}); //side 5
    geo::rotate( {{2,ovv.back().second}}, 0,0,0 , 0,1,0 , M_PI/2 );
    
    geo::copy({{2, s1}}, ovvv);
    surfa.push_back({2,ovvv.back().second}); //side 6
    geo::rotate( {{2,ovvv.back().second}}, 0,0,0 , 0,1,0 , -M_PI/2 );
    
    /*
     * TRANSFINITE MESH SETUP
     */
    mesh::setTransfiniteCurve(c1,10,"Progression",1);
    mesh::setTransfiniteCurve(c3,10,"Progression",1);
    mesh::setTransfiniteCurve(c2,10,"Progression",1);
    mesh::setTransfiniteCurve(c4,10,"Progression",1);
    mesh::setTransfiniteCurve(18,10,"Progression",1);
    mesh::setTransfiniteCurve(19,10,"Progression",1);
    mesh::setTransfiniteCurve(21,10,"Progression",1);
    mesh::setTransfiniteCurve(23,10,"Progression",1);
    mesh::setTransfiniteCurve(24,10,"Progression",1);
    mesh::setTransfiniteCurve(26,10,"Progression",1);
    mesh::setTransfiniteCurve(29,10,"Progression",1);
    mesh::setTransfiniteCurve(31,10,"Progression",1);

    mesh::setTransfiniteSurface(s1, "Left"); mesh::setRecombine(2, s1);
    mesh::setTransfiniteSurface(17, "Left"); mesh::setRecombine(2, 17);
    mesh::setTransfiniteSurface(22, "Left"); mesh::setRecombine(2, 22);
    mesh::setTransfiniteSurface(27, "Left"); mesh::setRecombine(2, 27);
    mesh::setTransfiniteSurface(32, "Left"); mesh::setRecombine(2, 32);
    mesh::setTransfiniteSurface(33, "Left"); mesh::setRecombine(2, 33);
    
    //model::getEntities(surfa, 2);
    //model::getBoundary(surfa, lines, false, false, true);
    int l1 = geo::addLine(102, 2, 1000); mesh::setTransfiniteCurve(l1,10,"Progression",GROWTH);
    int l2 = geo::addLine(108, 22, 1001); mesh::setTransfiniteCurve(l2,10,"Progression",GROWTH);
    int l3 = geo::addLine(105, 5, 1002); mesh::setTransfiniteCurve(l3,10,"Progression",GROWTH);
    int l4 = geo::addLine(111, 55, 1003); mesh::setTransfiniteCurve(l4,10,"Progression",GROWTH);
    int l5 = geo::addLine(103, 3, 1004); mesh::setTransfiniteCurve(l5,10,"Progression",GROWTH);
    int l6 = geo::addLine(109, 44, 1005); mesh::setTransfiniteCurve(l6,10,"Progression",GROWTH);
    int l7 = geo::addLine(104, 4, 1006); mesh::setTransfiniteCurve(l7,10,"Progression",GROWTH);
    int l8 = geo::addLine(106, 33, 1007); mesh::setTransfiniteCurve(l8,10,"Progression",GROWTH);
    
    int loopx1 = geo::addCurveLoop({-1001, 19, 1000,-9},2000); int sx1 = geo::addPlaneSurface({loopx1});
    int loopx2 = geo::addCurveLoop({-1007, 18, 1001,5},2001); int sx2 = geo::addPlaneSurface({loopx2});
    int loopx3 = geo::addCurveLoop({-1004, 21, 1007, 10},2002); int sx3 = geo::addPlaneSurface({loopx3});
    int loopx4 = geo::addCurveLoop({-1000,-13, 1004,-1},2003); int sx4 = geo::addPlaneSurface({loopx4});
    int loopx5 = geo::addCurveLoop({-1003,-29, 1002, -12},2004); int sx5 = geo::addPlaneSurface({loopx5});
    int loopx6 = geo::addCurveLoop({-1005, 31, 1006, -11},2005); int sx6 = geo::addPlaneSurface({loopx6});
    int loopx7 = geo::addCurveLoop({-1003, -23, 1005, 7},2006); int sx7 = geo::addPlaneSurface({loopx7});
    int loopx8 = geo::addCurveLoop({-1006, -15, 1002, -3},2007); int sx8 = geo::addPlaneSurface({loopx8});
    int loopx9 = geo::addCurveLoop({-1003, 24, 1001, -8},2008); int sx9 = geo::addPlaneSurface({loopx9});
    int loopx10 = geo::addCurveLoop({-1002, -14, 1000, -4},2009); int sx10 = geo::addPlaneSurface({loopx10});
    int loopx11 = geo::addCurveLoop({-1005, -26, 1007, 6},2010); int sx11 = geo::addPlaneSurface({loopx11});
    int loopx12 = geo::addCurveLoop({-1006, 16, 1004, 2},2011); int sx12 = geo::addPlaneSurface({loopx12});

    int sl1 = geo::addSurfaceLoop({35,22,44,40,42,2}); int v1 = geo::addVolume({sl1});
    int sl2 = geo::addSurfaceLoop({34,42,33,43,38,4}); int v2 = geo::addVolume({sl2});
    int sl3 = geo::addSurfaceLoop({37,7,43,45,41,1}); int v3 = geo::addVolume({sl3});
    int sl4 = geo::addSurfaceLoop({36,32,39,45,44,5}); int v4 = geo::addVolume({sl4});
    int sl5 = geo::addSurfaceLoop({40,27,39,38,41,6}); int v5 = geo::addVolume({sl5});
    int sl6 = geo::addSurfaceLoop({36,17,34,37,35,3}); int v6 = geo::addVolume({sl6});

    mesh::setTransfiniteSurface(sx1, "Left"); mesh::setRecombine(2, sx1);
    mesh::setTransfiniteSurface(sx2, "Left"); mesh::setRecombine(2, sx2);
    mesh::setTransfiniteSurface(sx3, "Left"); mesh::setRecombine(2, sx3);
    mesh::setTransfiniteSurface(sx4, "Left"); mesh::setRecombine(2, sx4);
    mesh::setTransfiniteSurface(sx5, "Left"); mesh::setRecombine(2, sx5);
    mesh::setTransfiniteSurface(sx6, "Left"); mesh::setRecombine(2, sx6);
    mesh::setTransfiniteSurface(sx7, "Left"); mesh::setRecombine(2, sx7);
    mesh::setTransfiniteSurface(sx8, "Left"); mesh::setRecombine(2, sx8);
    mesh::setTransfiniteSurface(sx9, "Left"); mesh::setRecombine(2, sx9);
    mesh::setTransfiniteSurface(sx10, "Left"); mesh::setRecombine(2, sx10);
    mesh::setTransfiniteSurface(sx11, "Left"); mesh::setRecombine(2, sx11);
    mesh::setTransfiniteSurface(sx12, "Left"); mesh::setRecombine(2, sx12);
    
    mesh::setTransfiniteVolume(v1); mesh::setRecombine(3, v1);
    mesh::setTransfiniteVolume(v2); mesh::setRecombine(3, v2);
    mesh::setTransfiniteVolume(v3); mesh::setRecombine(3, v3);
    mesh::setTransfiniteVolume(v4); mesh::setRecombine(3, v4);
    mesh::setTransfiniteVolume(v5); mesh::setRecombine(3, v5);
    mesh::setTransfiniteVolume(v6); mesh::setRecombine(3, v6);

    cout << "number of surfaces = " << surfa.size() << endl;
    for(std::size_t i = 0; i < surfa.size(); i++){
        int dim = surfa[i].first;
        int surf = surfa[i].second;
        if (dim==2){
            cout << "dim = " << dim << " surf " << surf << endl;
            //mesh::setTransfiniteSurface(surf, "Left", {p1 , p2 , p3 , p4});
        }
    }
}

int main(int argc, char **argv)
{
    std::vector<std::pair<int, int> > ov;
    std::vector<int> boundaries, surfaces, groups;
    double x=0, y=0, r1=atof(argv[1]), r2=r1+1, l=r2*4, lc=1e-1;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");
    
    // exterior cube
    int p2 = geo::addPoint( R1, R1, -R1, L, 2);
    int p3 = geo::addPoint(-R1, R1, -R1, L, 3);
    int p4 = geo::addPoint(-R1, -R1, -R1, L, 4);
    int p5 = geo::addPoint( R1, -R1, -R1, L, 5);
    int p22 = geo::addPoint( R1, R1, R1, L, 22);
    int p33 = geo::addPoint(-R1, R1, R1, L, 33);
    int p44 = geo::addPoint(-R1, -R1, R1, L, 44);
    int p55 = geo::addPoint( R1, -R1, R1, L, 55);
    
    int l1 = geo::addLine(p2, p3,1);
    int l2 = geo::addLine(p3, p4,2);
    int l3 = geo::addLine(p4, p5,3);
    int l4 = geo::addLine(p5, p2,4);
    
    int l5 = geo::addLine(p22, p33,5);
    int l6 = geo::addLine(p33, p44,6);
    int l7 = geo::addLine(p44, p55,7);
    int l8 = geo::addLine(p55, p22,8);
    
    int l9 = geo::addLine(p22, p2,9);
    int l10 = geo::addLine(p33, p3,10);
    int l11 = geo::addLine(p44, p4,11);
    int l12 = geo::addLine(p55, p5,12);
    
    mesh::setTransfiniteCurve(l1,10,"Progression",1);
    mesh::setTransfiniteCurve(l2,10,"Progression",1);
    mesh::setTransfiniteCurve(l3,10,"Progression",1);
    mesh::setTransfiniteCurve(l4,10,"Progression",1);

    mesh::setTransfiniteCurve(l5,10,"Progression",1);
    mesh::setTransfiniteCurve(l6,10,"Progression",1);
    mesh::setTransfiniteCurve(l7,10,"Progression",1);
    mesh::setTransfiniteCurve(l8,10,"Progression",1);
    
    mesh::setTransfiniteCurve(l9,10,"Progression",1);
    mesh::setTransfiniteCurve(l10,10,"Progression",1);
    mesh::setTransfiniteCurve(l11,10,"Progression",1);
    mesh::setTransfiniteCurve(l12,10,"Progression",1);
    
    int loop1 = geo::addCurveLoop({l4, l1, l2, l3}); int s1 = geo::addPlaneSurface({loop1},1);
    int loop2 = geo::addCurveLoop({l8, l5, l6, l7}); int s2 = geo::addPlaneSurface({loop2},2);
    int loop3 = geo::addCurveLoop({l5, l10, -l1, -l9}); int s3 = geo::addPlaneSurface({loop3},3);
    int loop4 = geo::addCurveLoop({l8, l9, -l4, -l12}); int s4 = geo::addPlaneSurface({loop4},4);
    int loop5 = geo::addCurveLoop({l6, l11, -l2, -l10}); int s5 = geo::addPlaneSurface({loop5},5);
    int loop6 = geo::addCurveLoop({l7, l12, -l3, -l11}); int s6 = geo::addPlaneSurface({loop6},6);
    
    mesh::setTransfiniteSurface(s1, "Left"); mesh::setRecombine(2, s1);
    mesh::setTransfiniteSurface(s2, "Left"); mesh::setRecombine(2, s2);
    mesh::setTransfiniteSurface(s3, "Left"); mesh::setRecombine(2, s3);
    mesh::setTransfiniteSurface(s4, "Left"); mesh::setRecombine(2, s4);
    mesh::setTransfiniteSurface(s5, "Left"); mesh::setRecombine(2, s5);
    mesh::setTransfiniteSurface(s6, "Left"); mesh::setRecombine(2, s6);
    
    surfaces.push_back(s1);
    surfaces.push_back(s2);
    surfaces.push_back(s3);
    surfaces.push_back(s4);
    surfaces.push_back(s5);
    surfaces.push_back(s6);

    /*
    mesh::setRecombine(2, surfaces.back());
    geo::extrude({{2,s1}}, 0,0,0, ov, {10}, {}, true);
    geo::remove({{3,1}});
    */
    
    //mesh::setTransfiniteCurve(16,10,"Progression",1);
    //mesh::setTransfiniteCurve(12,10,"Progression",1);
    //mesh::setTransfiniteCurve(20,10,"Progression",1);
    //mesh::setTransfiniteCurve(11,10,"Progression",1);
    
    /*
    cout << "test size: " << ov.size() << endl;
    for(std::size_t i = 0; i < ov.size(); i++){
        int dim = ov[i].first;
        int surf = ov[i].second;
        if (dim==2){
            cout << "dim = " << dim << " surf " << surf << endl;
            surfaces.push_back(surf);
        }
    }*/
    
    //create sphere
    sphereMesh(x,y,r1,r2,lc,boundaries,surfaces);
    
    gmsh::model::geo::synchronize();
    gmsh::model::mesh::generate(3);
    //gmsh::write("msh/spherical.msh");
    //gmsh::write("msh/spherical.su2");
    
    gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}
