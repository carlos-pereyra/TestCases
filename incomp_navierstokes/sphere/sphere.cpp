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
#define RAD_LAYERS 20
#define AZIMUTH_LAYERS 20
#define GROWTH 1.2

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
    mesh::setTransfiniteSurface(s1, "Left", { p1, p2, p3, p4});
    mesh::setRecombine(2, s1);
    
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
    
    mesh::setTransfiniteCurve(c1,10,"Progression",1);
    mesh::setTransfiniteCurve(c3,10,"Progression",1);
    mesh::setTransfiniteCurve(c2,10,"Progression",1);
    mesh::setTransfiniteCurve(c4,10,"Progression",1);
    mesh::setTransfiniteCurve(22,10,"Progression",1);
    mesh::setTransfiniteCurve(23,10,"Progression",1);
    mesh::setTransfiniteCurve(24,10,"Progression",1);
    mesh::setTransfiniteCurve(21,10,"Progression",1);
    mesh::setTransfiniteCurve(30,10,"Progression",1);
    mesh::setTransfiniteCurve(29,10,"Progression",1);
    mesh::setTransfiniteCurve(32,10,"Progression",1);
    mesh::setTransfiniteCurve(34,10,"Progression",1);
    mesh::setTransfiniteCurve(42,10,"Progression",1);
    mesh::setTransfiniteCurve(40,10,"Progression",1);
    mesh::setTransfiniteCurve(35,10,"Progression",1);
    mesh::setTransfiniteCurve(37,10,"Progression",1);
    
    //model::getEntities(surfa, 2);
    //model::getBoundary(surfa, lines, false, false, true);
    
    /*
     * TRANSFINITE MESH SETUP
     */
    cout << "number of surfaces = " << surfa.size() << endl;
    for(std::size_t i = 0; i < surfa.size(); i++){
        int dim = surfa[i].first;
        int surf = surfa[i].second;
        if (dim==2){
            cout << "dim = " << dim << " surf " << surf << endl;
            //mesh::setTransfiniteSurface(surf, "Left", {p1 , p2 , p3 , p4});
        }
    }

    mesh::setTransfiniteSurface(33, "Left", { 108, 111, 109, 106});
    mesh::setRecombine(2, 33);
    
    mesh::setTransfiniteSurface(28, "Left", { 103, 102, 108, 106});
    mesh::setRecombine(2, 28);
    
    mesh::setTransfiniteSurface(43, "Left", { 104, 109, 106, 103});
    mesh::setRecombine(2, 43);
    
    mesh::setTransfiniteSurface(38, "Left", { 104, 105, 111, 109});
    mesh::setRecombine(2, 38);

    mesh::setTransfiniteSurface(44, "Left", { 105, 111, 108, 102});
    mesh::setRecombine(2, 44);
    
    int l1 = geo::addLine(106, 11);
    int l2 = geo::addLine(103, 3);
    int l3 = geo::addLine(102, 2);
    int l4 = geo::addLine(108, 7);
    int l5 = geo::addLine(111, 6);
    int l6 = geo::addLine(109, 15);
    int l7 = geo::addLine(104, 4);
    int l8 = geo::addLine(105, 5);
    
    
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

    int l1 = geo::addLine(p2, p3,1);
    int l2 = geo::addLine(p3, p4,2);
    int l3 = geo::addLine(p4, p5,3);
    int l4 = geo::addLine(p5, p2,4);
    
    mesh::setTransfiniteCurve(l1,10,"Progression",1);
    mesh::setTransfiniteCurve(l2,10,"Progression",1);
    mesh::setTransfiniteCurve(l3,10,"Progression",1);
    mesh::setTransfiniteCurve(l4,10,"Progression",1);
    
    int loop1 = geo::addCurveLoop({l4, l1, l2, l3});
    int s1 = geo::addPlaneSurface({loop1}, 1);
    surfaces.push_back(s1);
    mesh::setTransfiniteSurface(surfaces.back(), "Left", {p2 , p3 , p4 , p5});
    mesh::setRecombine(2, surfaces.back());
    geo::extrude({{2,s1}}, 0,0,2*R1, ov, {2}, {1}, true);
    geo::remove({{3,1}});
    
    cout << "test size: " << ov.size() << endl;
    for(std::size_t i = 0; i < ov.size(); i++){
        int dim = ov[i].first;
        int surf = ov[i].second;
        if (dim==2){
            cout << "dim = " << dim << " surf " << surf << endl;
            surfaces.push_back(surf);
        }
    }
    
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
