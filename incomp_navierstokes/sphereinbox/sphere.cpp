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
#define RAD_ELEM 5
#define AZIMUTH_ELEM 5
#define GROWTH 1

namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void sphereMesh(double x, double y, double z, double r1, double l, double lc, std::vector<int> &boundaries, std::vector<int> &surfaces, int sphere_tag, double sep){
    
    std::vector<std::pair<int, int> > ov, ovv, ovvv, surfa, linessave;
    std::vector<int> tagss;
    
    // SPHERE 1
    
    // EXTERIOR CUBE
    int p1,p2,p3,p4,p5,p6,p7,p8,p9;
    int l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12;
    if (sphere_tag==1) {
        p1 = geo::addPoint(   x,  y,  z, lc); //1
        p2 = geo::addPoint( l+x,  l+y, -l+z, lc); //2
        p3 = geo::addPoint(-sep/2+x,  l+y, -l+z, lc); //3
        p4 = geo::addPoint(-sep/2+x, -l+y, -l+z, lc); //4
        p5 = geo::addPoint( l+x, -l+y, -l+z, lc); //5
        p6 = geo::addPoint( l+x,  l+y,  l+z, lc); //6 - 22
        p7 = geo::addPoint(-sep/2+x,  l+y,  l+z, lc); //7 - 33
        p8 = geo::addPoint(-sep/2+x, -l+y,  l+z, lc); //8 - 44
        p9 = geo::addPoint( l+x, -l+y,  l+z, lc); //9 - 55
        l1 = geo::addLine(p2, p3);
        l2 = geo::addLine(p3, p4);
        l3 = geo::addLine(p4, p5);
        l4 = geo::addLine(p6, p7);
        l5 = geo::addLine(p7, p8);
        l6 = geo::addLine(p8, p9);
        l7 = geo::addLine(p7, p3);
        l8 = geo::addLine(p8, p4);
        l9 = geo::addLine(p9, p6);
        l10 = geo::addLine(p6, p2);
        l11 = geo::addLine(p5, p2);
        l12 = geo::addLine(p9, p5);
        
        int loop1 = geo::addCurveLoop({l4, l5, l6, l9});
        int loop2 = geo::addCurveLoop({l10, -l11, -l12, l9});
        int loop3 = geo::addCurveLoop({l1, l2, l3, l11});
        int loop4 = geo::addCurveLoop({l7, -l1, -l10, l4});
        int loop5 = geo::addCurveLoop({l6, l12, -l3, -l8});
        int loop6 = geo::addCurveLoop({-l7, l5, l8, -l2});
        
        int s1 = geo::addPlaneSurface({loop1});
        int s2 = geo::addPlaneSurface({loop2});
        int s3 = geo::addPlaneSurface({loop3});
        int s4 = geo::addPlaneSurface({loop4});
        int s5 = geo::addPlaneSurface({loop5});
        int s6 = geo::addPlaneSurface({loop6});
    }
    if (sphere_tag==2) {
        p1 = geo::addPoint(   x,  y,  z, lc); //1
        //p2 = geo::addPoint( l+x,  l+y, -l+z, lc); //2
        p3 = geo::addPoint(-l+x,  l+y, -l+z, lc); //3
        p4 = geo::addPoint(-l+x, -l+y, -l+z, lc); //4
        //p5 = geo::addPoint( l+x, -l+y, -l+z, lc); //5
        //p6 = geo::addPoint( l+x,  l+y,  l+z, lc); //6 - 22
        p7 = geo::addPoint(-l+x,  l+y,  l+z, lc); //7 - 33
        p8 = geo::addPoint(-l+x, -l+y,  l+z, lc); //8 - 44
        //p9 = geo::addPoint( l+x, -l+y,  l+z, lc); //9 - 55
        
        l1 = geo::addLine(21, 3);
        l2 = geo::addLine(23, 7);
        l3 = geo::addLine(24, 8);
        l4 = geo::addLine(22, 4);
        l5 = geo::addLine(23, 24);
        l6 = geo::addLine(24, 22);// bottom front
        l7 = geo::addLine(22, 21);
        l8 = geo::addLine(21, 23);
    }
    
    mesh::setTransfiniteCurve(l1,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l2,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l3,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l4,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l5,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l6,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l7,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(l8,AZIMUTH_ELEM+1,"Progression",1);
    if (sphere_tag==1) {
        mesh::setTransfiniteCurve(l9,AZIMUTH_ELEM+1,"Progression",1);
        mesh::setTransfiniteCurve(l10,AZIMUTH_ELEM+1,"Progression",1);
        mesh::setTransfiniteCurve(l11,AZIMUTH_ELEM+1,"Progression",1);
        mesh::setTransfiniteCurve(l12,AZIMUTH_ELEM+1,"Progression",1);
    }
    if (sphere_tag==2) {
        mesh::setTransfiniteCurve(l9,AZIMUTH_ELEM+1,"Progression",1);
        mesh::setTransfiniteCurve(l10,AZIMUTH_ELEM+1,"Progression",1);
        mesh::setTransfiniteCurve(l11,AZIMUTH_ELEM+1,"Progression",1);
        mesh::setTransfiniteCurve(l12,AZIMUTH_ELEM+1,"Progression",1);
    }
    //mesh::setTransfiniteSurface(s1, "Left"); mesh::setRecombine(2, s1); surfaces.push_back(s1);
    //mesh::setTransfiniteSurface(s2, "Left"); mesh::setRecombine(2, s2); surfaces.push_back(s2);
    //mesh::setTransfiniteSurface(s3, "Left"); mesh::setRecombine(2, s3); surfaces.push_back(s3);
    //mesh::setTransfiniteSurface(s4, "Left"); mesh::setRecombine(2, s4); surfaces.push_back(s4);
    //mesh::setTransfiniteSurface(s5, "Left"); mesh::setRecombine(2, s5); surfaces.push_back(s5);
    //mesh::setTransfiniteSurface(s6, "Left"); mesh::setRecombine(2, s6); surfaces.push_back(s6);
    
    // INTERIOR SPHERE

    int p10 = geo::addPoint(  r1+x, r1+y, -r1+z, lc,p8+2); //10 - 100
    int p11 = geo::addPoint( -r1+x, r1+y, -r1+z, lc,p8+3); //11 - 101
    int p12 = geo::addPoint( -r1+x,-r1+y, -r1+z, lc,p8+4); //12 - 102
    int p13 = geo::addPoint(  r1+x,-r1+y, -r1+z, lc,p8+5); //13 - 103
    int c1 = geo::addCircleArc(p11, p1, p10); //13
    int c2 = geo::addCircleArc(p10, p1, p13); //14
    int c3 = geo::addCircleArc(p13, p1, p12); //15
    int c4 = geo::addCircleArc(p12, p1, p11); //16
    
    int loop7 = geo::addCurveLoop({c1,c2,c3,c4});
    int s7 = geo::addSurfaceFilling({loop7});
    
    // ROTATE SURFACE
    surfa.push_back({2,s7}); //side 1
    geo::copy({{2, s7}}, ov);
    geo::rotate({{2,ov.back().second}}, x,y,z , r1,0,0 , M_PI/2 );
    surfa.push_back({2,ov.back().second}); //side 2
    geo::copy({{2, ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, x,y,z , r1,0,0 , M_PI/2 );
    surfa.push_back({2,ov.back().second}); //side 3
    geo::copy({{2,ov.back().second}}, ov);
    geo::rotate({{2,ov.back().second}}, x,y,z , r1,0,0 , M_PI/2 );
    surfa.push_back({2,ov.back().second}); //side 4
    geo::copy({{2, s7}}, ovv);
    surfa.push_back({2,ovv.back().second}); //side 5
    geo::rotate( {{2,ovv.back().second}}, x,y,z , 0,r1,0 , M_PI/2 );
    geo::copy({{2, s7}}, ovvv);
    surfa.push_back({2,ovvv.back().second}); //side 6
    geo::rotate( {{2,ovvv.back().second}}, x,y,z , 0,r1,0 , -M_PI/2 );
    linessave.push_back({1,ovvv.back().first});

    // TRANSFINITE SPHERE MESH SETUP
    mesh::setTransfiniteCurve(c1,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(c3,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(c2,AZIMUTH_ELEM+1,"Progression",1);
    mesh::setTransfiniteCurve(c4,AZIMUTH_ELEM+1,"Progression",1);
    int l18 = c4+2; mesh::setTransfiniteCurve(c4+2,AZIMUTH_ELEM+1,"Progression",1); //18
    int l19 = c4+3; mesh::setTransfiniteCurve(c4+3,AZIMUTH_ELEM+1,"Progression",1); //19
    int l20 = c4+5; mesh::setTransfiniteCurve(c4+5,AZIMUTH_ELEM+1,"Progression",1); //21
    int l23 = c4+7; mesh::setTransfiniteCurve(c4+7,AZIMUTH_ELEM+1,"Progression",1); //23 -l21
    int l24 = c4+8; mesh::setTransfiniteCurve(c4+8,AZIMUTH_ELEM+1,"Progression",1); //24 -l22
    int l26 = c4+10; mesh::setTransfiniteCurve(c4+10,AZIMUTH_ELEM+1,"Progression",1); //26 -l23
    int l29 = c4+13; mesh::setTransfiniteCurve(c4+13,AZIMUTH_ELEM+1,"Progression",1); //29 - l24
    int l31 = c4+15;mesh::setTransfiniteCurve(c4+15,AZIMUTH_ELEM+1,"Progression",1); //31 - l25
    mesh::setTransfiniteSurface(s7, "Left"); mesh::setRecombine(2, s7);
    int ss1 = c4+1; mesh::setTransfiniteSurface(surfa.at(1).second, "Left"); mesh::setRecombine(2, c4+1);//17
    int ss2 = c4+6; mesh::setTransfiniteSurface(surfa.at(2).second, "Left"); mesh::setRecombine(2, c4+6); //22
    int ss3 = c4+11; mesh::setTransfiniteSurface(surfa.at(3).second, "Left"); mesh::setRecombine(2, c4+11); //27
    int ss4 = c4+16; mesh::setTransfiniteSurface(surfa.at(4).second, "Left"); mesh::setRecombine(2, c4+16); //32
    int ss5 = c4+17; mesh::setTransfiniteSurface(surfa.at(5).second, "Left"); mesh::setRecombine(2, c4+17); //33
    
    // CONNECT SPHERE TO CUBE
    int l32,l33,l34,l35,l36,l37,l38,l39;
    if (sphere_tag==1) {
        l32 = geo::addLine(16, 6); mesh::setTransfiniteCurve(l39,RAD_ELEM+1,"Progression",GROWTH); //l39 //l20
        l33 = geo::addLine(10, 2); mesh::setTransfiniteCurve(l32,RAD_ELEM+1,"Progression",GROWTH); //p10-p2 //l13
        l34 = geo::addLine(13, 5); mesh::setTransfiniteCurve(l33,RAD_ELEM+1,"Progression",GROWTH);//p9-p6  l14
        l35 = geo::addLine(19, 9); mesh::setTransfiniteCurve(l34,RAD_ELEM+1,"Progression",GROWTH); //l15
        l36 = geo::addLine(14, 7); mesh::setTransfiniteCurve(l35,RAD_ELEM+1,"Progression",GROWTH);//l16
        l37 = geo::addLine(11, 3); mesh::setTransfiniteCurve(l36,RAD_ELEM+1,"Progression",GROWTH); //l17
        l38 = geo::addLine(12, 4); mesh::setTransfiniteCurve(l37,RAD_ELEM+1,"Progression",GROWTH);//l18
        l39 = geo::addLine(17, 8); mesh::setTransfiniteCurve(l38,RAD_ELEM+1,"Progression",GROWTH); //l19
        
        int loopx1 = geo::addCurveLoop({33, -10, -32 ,19});
        int loopx2 = geo::addCurveLoop({34, 11, -33 ,14});
        int loopx3 = geo::addCurveLoop({35, 9, -32, -24});
        int loopx4 = geo::addCurveLoop({29, -34, 12, 35});
        int sx1 = geo::addPlaneSurface({loopx1}); //34
        int sx2 = geo::addPlaneSurface({loopx2}); //35
        int sx3 = geo::addPlaneSurface({loopx3}); //36
        int sx4 = geo::addPlaneSurface({loopx4}); //38
        
        int loopx5 = geo::addCurveLoop({39, 6, -35, -23});
        int loopx6 = geo::addCurveLoop({39, -5, -36, 26});
        int loopx7 = geo::addCurveLoop({32, 4, -36, 18});
        int loopx8 = geo::addCurveLoop({36, 7, -37, 21});
        int loopx9 = geo::addCurveLoop({34, -3, -38, -15});
        int loopx10 = geo::addCurveLoop({38, -2, -37, -16});
        
        int sx5 = geo::addPlaneSurface({loopx5}); //37
        int sx6 = geo::addPlaneSurface({loopx6}); //39
        int sx7 = geo::addPlaneSurface({loopx7}); //40
        int sx8 = geo::addPlaneSurface({loopx8}); //41
        int sx9 = geo::addPlaneSurface({loopx9}); //42
        int sx10 = geo::addPlaneSurface({loopx10}); //43

    }
    if (sphere_tag==2) {
        l32 = geo::addLine(32, 7); mesh::setTransfiniteCurve(l32,RAD_ELEM+1,"Progression",GROWTH); //l13
        l33 = geo::addLine(26, 3); mesh::setTransfiniteCurve(l33,RAD_ELEM+1,"Progression",GROWTH);//l14
        l34 = geo::addLine(29, 4); mesh::setTransfiniteCurve(l34,RAD_ELEM+1,"Progression",GROWTH); //l15
        l35 = geo::addLine(35, 8); mesh::setTransfiniteCurve(l35,RAD_ELEM+1,"Progression",GROWTH);//l16
        l36 = geo::addLine(30, 23); mesh::setTransfiniteCurve(l36,RAD_ELEM+1,"Progression",GROWTH); //l17
        l37 = geo::addLine(27, 21); mesh::setTransfiniteCurve(l37,RAD_ELEM+1,"Progression",GROWTH);//l18
        l38 = geo::addLine(28, 22); mesh::setTransfiniteCurve(l38,RAD_ELEM+1,"Progression",GROWTH); //l19
        l39 = geo::addLine(33, 24); mesh::setTransfiniteCurve(l39,RAD_ELEM+1,"Progression",GROWTH);//l20
        
        int loopx1 = geo::addCurveLoop({69, -2, -68, 49});   int sx1 = geo::addPlaneSurface({loopx1}); //45
        int loopx2 = geo::addCurveLoop({67, 7, -68, -54});   int sx2 = geo::addPlaneSurface({loopx2}); //45
        int loopx3 = geo::addCurveLoop({70, -5, -67, -59});   int sx3 = geo::addPlaneSurface({loopx3}); //45
        int loopx4 = geo::addCurveLoop({69, -8, -70, -64});   int sx4 = geo::addPlaneSurface({loopx4}); //45
        int loopx5 = geo::addCurveLoop({70, -42, -74, 58});   int sx5 = geo::addPlaneSurface({loopx5}); //45
        int loopx6 = geo::addCurveLoop({74, 45, -73, -66});   int sx6 = geo::addPlaneSurface({loopx6}); //45
        int loopx7 = geo::addCurveLoop({73, 43, -69, 50});  int sx7 = geo::addPlaneSurface({loopx7}); //44
        int loopx8 = geo::addCurveLoop({72, 40, -68, -48});  int sx8 = geo::addPlaneSurface({loopx8}); //44

        int loopx9 = geo::addCurveLoop({71, -47, -72, 56});  int sx9 = geo::addPlaneSurface({loopx9}); //44
        int loopx10 = geo::addCurveLoop({67, -41, -71, 53});  int sx10 = geo::addPlaneSurface({loopx10}); //44
        int loopx11 = geo::addCurveLoop({74, -44, -71, 61});  int sx11 = geo::addPlaneSurface({loopx11}); //44
        int loopx12 = geo::addCurveLoop({73, 46, -72, -51});  int sx12 = geo::addPlaneSurface({loopx12}); //44
        
        int loopx13 = geo::addCurveLoop({47, 41, 7, -40});  int sx13 = geo::addPlaneSurface({loopx13}); //44
        int loopx14 = geo::addCurveLoop({45, 46, 47, 44});  int sx14 = geo::addPlaneSurface({loopx14}); //44
        int loopx15 = geo::addCurveLoop({-8, 43, 45, -42});  int sx15 = geo::addPlaneSurface({loopx15}); //44

        int loopx16 = geo::addCurveLoop({44, 42, -5, -41});  int sx16 = geo::addPlaneSurface({loopx16}); //44


    }
    
    

    
    /*
    // FILL INTERNAL VOLUME
    int sl1 = geo::addSurfaceLoop({sx2,ss2,sx11,sx7,sx9,s2}); int v1 = geo::addVolume({sl1});
    int sl2 = geo::addSurfaceLoop({sx1,sx9,ss5,sx10,sx5,s4}); int v2 = geo::addVolume({sl2});
    int sl3 = geo::addSurfaceLoop({sx4,s7,sx10,sx12,sx8,s1}); int v3 = geo::addVolume({sl3});
    int sl4 = geo::addSurfaceLoop({sx3,ss4,sx6,sx12,sx11,s5}); int v4 = geo::addVolume({sl4});
    int sl5 = geo::addSurfaceLoop({sx7,ss3,sx6,sx5,sx8,s6}); int v5 = geo::addVolume({sl5});
    int sl6 = geo::addSurfaceLoop({sx3,ss1,sx1,sx4,sx2,s3}); int v6 = geo::addVolume({sl6});
    
    mesh::setTransfiniteSurface(sx1, "Alternated"); mesh::setRecombine(2, sx1);
    mesh::setTransfiniteSurface(sx2, "Right"); mesh::setRecombine(2, sx2);
    mesh::setTransfiniteSurface(sx3, "Right"); mesh::setRecombine(2, sx3);
    mesh::setTransfiniteSurface(sx4, "Right"); mesh::setRecombine(2, sx4);
    mesh::setTransfiniteSurface(sx5, "Right"); mesh::setRecombine(2, sx5);
    mesh::setTransfiniteSurface(sx6, "Right"); mesh::setRecombine(2, sx6);
    mesh::setTransfiniteSurface(sx7, "Right"); mesh::setRecombine(2, sx7);
    mesh::setTransfiniteSurface(sx8, "Right"); mesh::setRecombine(2, sx8);
    mesh::setTransfiniteSurface(sx9, "Right"); mesh::setRecombine(2, sx9);
    mesh::setTransfiniteSurface(sx10, "Left"); mesh::setRecombine(2, sx10);
    mesh::setTransfiniteSurface(sx11, "Left"); mesh::setRecombine(2, sx11);
    mesh::setTransfiniteSurface(sx12, "Left"); mesh::setRecombine(2, sx12);
    mesh::setTransfiniteVolume(v1); //mesh::setRecombine(3, v1);
    mesh::setTransfiniteVolume(v2); //mesh::setRecombine(3, v2);
    mesh::setTransfiniteVolume(v3); //mesh::setRecombine(3, v3);
    mesh::setTransfiniteVolume(v4); //mesh::setRecombine(3, v4);
    mesh::setTransfiniteVolume(v5); //mesh::setRecombine(3, v5);
    mesh::setTransfiniteVolume(v6); //mesh::setRecombine(3, v6);

    if (sphere_tag == 1){
        int pg1 = model::addPhysicalGroup(2,{s1}); model::setPhysicalName(2,pg1,"outlet");
        int pg2 = model::addPhysicalGroup(2,{s2}); model::setPhysicalName(2,pg2,"inlet1");
        int pg3 = model::addPhysicalGroup(2,{s3,s4,s5,s6}); model::setPhysicalName(2,pg3,"wall");
        int pg7 = model::addPhysicalGroup(2,{ss1,ss2,ss3,ss4,ss5,s7}); model::setPhysicalName(2,pg7,"sphere");
        int pg13 = model::addPhysicalGroup(3,{v1}); model::setPhysicalName(3,pg13,"v1");
        int pg14 = model::addPhysicalGroup(3,{v2}); model::setPhysicalName(3,pg14,"v2");
        int pg15 = model::addPhysicalGroup(3,{v3}); model::setPhysicalName(3,pg15,"v3");
        int pg16 = model::addPhysicalGroup(3,{v4}); model::setPhysicalName(3,pg16,"v4");
        int pg17 = model::addPhysicalGroup(3,{v5}); model::setPhysicalName(3,pg17,"v5");
        int pg18 = model::addPhysicalGroup(3,{v6}); model::setPhysicalName(3,pg18,"v6");
    }
    if (sphere_tag == 2) {
        int pg1 = model::addPhysicalGroup(2,{s1}); model::setPhysicalName(2,pg1,"outlet2");
        int pg2 = model::addPhysicalGroup(2,{s2}); model::setPhysicalName(2,pg2,"inlet2");
        int pg3 = model::addPhysicalGroup(2,{s3,s4,s5,s6}); model::setPhysicalName(2,pg3,"wall2");
        int pg7 = model::addPhysicalGroup(2,{ss1,ss2,ss3,ss4,ss5,s7}); model::setPhysicalName(2,pg7,"sphere2");
        int pg13 = model::addPhysicalGroup(3,{v1}); model::setPhysicalName(3,pg13,"v7");
        int pg14 = model::addPhysicalGroup(3,{v2}); model::setPhysicalName(3,pg14,"v8");
        int pg15 = model::addPhysicalGroup(3,{v3}); model::setPhysicalName(3,pg15,"v9");
        int pg16 = model::addPhysicalGroup(3,{v4}); model::setPhysicalName(3,pg16,"v10");
        int pg17 = model::addPhysicalGroup(3,{v5}); model::setPhysicalName(3,pg17,"v11");
        int pg18 = model::addPhysicalGroup(3,{v6}); model::setPhysicalName(3,pg18,"v12");
    }
     */
}

int main(int argc, char **argv)
{
    std::vector<std::pair<int, int> > ov;
    std::vector<int> boundaries, surfaces, groups;
    double sep=5, angle=0;
    double r1=atof(argv[1])/2, L=atof(argv[2])*2*r1, lc=1e-2, l=atof(argv[2])*2*r1;
    double x1=0, y1=0, z1=0;
    double x2=x1-sep*cos(angle*M_PI/180), y2=y1+sep*sin(angle*M_PI/180), z2=z1-0;
    double x3=(x1-sep*cos(angle*M_PI/180))/2, y3=(y1+sep*sin(angle*M_PI/180))/2, z3=(z1-z2)/2;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");
    
    //create sphere
    sphereMesh(x1,y1,z1,r1,l,lc,boundaries,surfaces,1,sep);
    sphereMesh(x2,y2,z2,r1,l,lc,boundaries,surfaces,2,sep);

    gmsh::model::geo::synchronize();
    int filling = gmsh::model::addPhysicalGroup(3, {22});
    gmsh::model::setPhysicalName(3, filling, "outervolume");
    
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(2);
    //gmsh::model::geo::removeAllDuplicates();
    //gmsh::model::geo::symmetrize({{3,6}}, 10,0,0,0);
    gmsh::model::mesh::refine();
    //gmsh::model::mesh::setOrder(3);
    //gmsh::model::mesh::recombine("sphere1");
    //gmsh::write("msh/spherical.cgns");
    //gmsh::write("msh/sphere.msh");
    //gmsh::write("msh/sphere.su2");
    //gmsh::write("msh/sphere.vtk");
    gmsh::view::add("test");
    gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}
