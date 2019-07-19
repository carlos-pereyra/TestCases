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
#define RAD_ELEM 21
#define AZIMUTH_ELEM 21
#define GROWTH 1.1
#define FAR 0
#define FAR_RAD_ELEM 31


namespace model = gmsh::model;
namespace geo = gmsh::model::geo;
namespace mesh = gmsh::model::geo::mesh;

void sphereMesh(double x, double y, double z, double r1, double l, double lc, std::vector<int> &surfaces, std::vector<int> &volumes, int sphere_tag, double sep){
    
    std::vector<std::pair<int, int> > ov, ovv, ovvv, surfa, linessave;
    std::vector<int> tagss;
    
    // SPHERE 1
    
    // EXTERIOR CUBE
    int p1,p2,p3,p4,p5,p6,p7,p8,p9;
    int l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12;
    int loop1,loop2,loop3,loop4,loop5,loop6;
    int s1,s2,s3,s4,s5,s6;
    double enlg=0;
    if (sphere_tag==1) {
        p1 = geo::addPoint(   x,  y,  z, lc); //1
        p2 = geo::addPoint( sep/2+x+enlg ,  sep/2+y+enlg , -sep/2+z-enlg, lc); //2
        p3 = geo::addPoint(-sep/2+x      ,  sep/2+y+enlg , -sep/2+z-enlg, lc); //3
        p4 = geo::addPoint(-sep/2+x      , -sep/2+y-enlg , -sep/2+z-enlg, lc); //4
        p5 = geo::addPoint( sep/2+x+enlg , -sep/2+y-enlg , -sep/2+z-enlg, lc); //5
        p6 = geo::addPoint( sep/2+x+enlg ,  sep/2+y+enlg ,  sep/2+z+enlg, lc); //6 - 22
        p7 = geo::addPoint(-sep/2+x      ,  sep/2+y+enlg ,  sep/2+z+enlg, lc); //7 - 33
        p8 = geo::addPoint(-sep/2+x      , -sep/2+y-enlg ,  sep/2+z+enlg, lc); //8 - 44
        p9 = geo::addPoint( sep/2+x+enlg , -sep/2+y-enlg ,  sep/2+z+enlg, lc); //9 - 55
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
        
        loop1 = geo::addCurveLoop({l4, l5, l6, l9});
        loop2 = geo::addCurveLoop({l10, -l11, -l12, l9});
        loop3 = geo::addCurveLoop({l1, l2, l3, l11});
        loop4 = geo::addCurveLoop({l7, -l1, -l10, l4});
        loop5 = geo::addCurveLoop({l6, l12, -l3, -l8});
        loop6 = geo::addCurveLoop({-l7, l5, l8, -l2});
        
        s1 = geo::addPlaneSurface({loop1});
        s2 = geo::addPlaneSurface({loop2});
        s3 = geo::addPlaneSurface({loop3});
        s4 = geo::addPlaneSurface({loop4});
        s5 = geo::addPlaneSurface({loop5});
        s6 = geo::addPlaneSurface({loop6});
        
        mesh::setTransfiniteSurface(s1, "Right"); mesh::setRecombine(2, s1);
        mesh::setTransfiniteSurface(s2, "Right"); mesh::setRecombine(2, s2);
        mesh::setTransfiniteSurface(s3, "Right"); mesh::setRecombine(2, s3);
        mesh::setTransfiniteSurface(s4, "Right"); mesh::setRecombine(2, s4);
        mesh::setTransfiniteSurface(s5, "Right"); mesh::setRecombine(2, s5);
        mesh::setTransfiniteSurface(s6, "Right"); mesh::setRecombine(2, s6);

    }
    if (sphere_tag==2) {
        p1 = geo::addPoint(   x,  y,  z, lc); //1
        //p2 = geo::addPoint( l+x,  l+y, -l+z, lc); //2
        p3 = geo::addPoint(-sep/2+x-enlg,  sep/2+y+enlg, -sep/2+z-enlg, lc); //3
        p4 = geo::addPoint(-sep/2+x-enlg, -sep/2+y-enlg, -sep/2+z-enlg, lc); //4
        //p5 = geo::addPoint( l+x, -l+y, -l+z, lc); //5
        //p6 = geo::addPoint( l+x,  l+y,  l+z, lc); //6 - 22
        p7 = geo::addPoint(-sep/2+x-enlg,  sep/2+y+enlg,  sep/2+z+enlg, lc); //7 - 33
        p8 = geo::addPoint(-sep/2+x-enlg, -sep/2+y-enlg,  sep/2+z+enlg, lc); //8 - 44
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
    int loopx1,loopx2,loopx3,loopx4,loopx5,loopx6,loopx7,loopx8,loopx9,loopx10,loopx11,loopx12,loopx13,loopx14,loopx15,loopx16,loopx17;
    int sx1,sx2,sx3,sx4,sx5,sx6,sx7,sx8,sx9,sx10,sx11,sx12,sx13,sx14,sx15,sx16,sx17;
    if (sphere_tag==1) {
        l32 = geo::addLine(16, 6); mesh::setTransfiniteCurve(l32,RAD_ELEM+1,"Progression",GROWTH);
        l33 = geo::addLine(10, 2); mesh::setTransfiniteCurve(l33,RAD_ELEM+1,"Progression",GROWTH);
        l34 = geo::addLine(13, 5); mesh::setTransfiniteCurve(l34,RAD_ELEM+1,"Progression",GROWTH);
        l35 = geo::addLine(19, 9); mesh::setTransfiniteCurve(l35,RAD_ELEM+1,"Progression",GROWTH);
        l36 = geo::addLine(14, 7); mesh::setTransfiniteCurve(l36,RAD_ELEM+1,"Progression",GROWTH);
        l37 = geo::addLine(11, 3); mesh::setTransfiniteCurve(l37,RAD_ELEM+1,"Progression",GROWTH);
        l38 = geo::addLine(12, 4); mesh::setTransfiniteCurve(l38,RAD_ELEM+1,"Progression",GROWTH);
        l39 = geo::addLine(17, 8); mesh::setTransfiniteCurve(l39,RAD_ELEM+1,"Progression",GROWTH);
        
        loopx1= geo::addCurveLoop({33, -10, -32 ,19});
        loopx2= geo::addCurveLoop({34, 11, -33 ,14});
        loopx3= geo::addCurveLoop({35, 9, -32, -24});
        loopx4= geo::addCurveLoop({29, -34, 12, 35});
        loopx5= geo::addCurveLoop({39, 6, -35, -23});
        loopx6= geo::addCurveLoop({39, -5, -36, 26});
        loopx7= geo::addCurveLoop({32, 4, -36, 18});
        loopx8= geo::addCurveLoop({36, 7, -37, 21});
        loopx9= geo::addCurveLoop({34, -3, -38, -15});
        loopx10= geo::addCurveLoop({38, -2, -37, -16});
        loopx11= geo::addCurveLoop({39, 8, -38, -31});
        loopx12= geo::addCurveLoop({37, -1, -33, -13});

        sx1 = geo::addPlaneSurface({loopx1});
        sx2 = geo::addPlaneSurface({loopx2});
        sx3 = geo::addPlaneSurface({loopx3});
        sx4 = geo::addPlaneSurface({loopx4});
        sx5 = geo::addPlaneSurface({loopx5});
        sx6 = geo::addPlaneSurface({loopx6});
        sx7 = geo::addPlaneSurface({loopx7});
        sx8 = geo::addPlaneSurface({loopx8});
        sx9 = geo::addPlaneSurface({loopx9});
        sx10 = geo::addPlaneSurface({loopx10});
        sx11 = geo::addPlaneSurface({loopx11});
        sx12 = geo::addPlaneSurface({loopx12});

        mesh::setTransfiniteSurface(sx1, "Right"); mesh::setRecombine(2, sx1);
        mesh::setTransfiniteSurface(sx2, "Right"); mesh::setRecombine(2, sx2);
        mesh::setTransfiniteSurface(sx3, "Right"); mesh::setRecombine(2, sx3);
        mesh::setTransfiniteSurface(sx4, "Right"); mesh::setRecombine(2, sx4);
        mesh::setTransfiniteSurface(sx5, "Right"); mesh::setRecombine(2, sx5);
        mesh::setTransfiniteSurface(sx6, "Right"); mesh::setRecombine(2, sx6);
        mesh::setTransfiniteSurface(sx7, "Right"); mesh::setRecombine(2, sx7);
        mesh::setTransfiniteSurface(sx8, "Right"); mesh::setRecombine(2, sx8);
        mesh::setTransfiniteSurface(sx9, "Right"); mesh::setRecombine(2, sx9);
        mesh::setTransfiniteSurface(sx10, "Right"); mesh::setRecombine(2, sx10);
        mesh::setTransfiniteSurface(sx11, "Right"); mesh::setRecombine(2, sx11);
        mesh::setTransfiniteSurface(sx12, "Right"); mesh::setRecombine(2, sx12);
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
        
        loopx1 = geo::addCurveLoop({69, -2, -68, 49});
        loopx2 = geo::addCurveLoop({67, 7, -68, -54});
        loopx3 = geo::addCurveLoop({70, -5, -67, -59});
        loopx4 = geo::addCurveLoop({69, -8, -70, -64});
        loopx5 = geo::addCurveLoop({70, -42, -74, 58});
        loopx6 = geo::addCurveLoop({74, 45, -73, -66});
        loopx7 = geo::addCurveLoop({73, 43, -69, 50});
        loopx8 = geo::addCurveLoop({72, 40, -68, -48});
        loopx9 = geo::addCurveLoop({71, -47, -72, 56});
        loopx10 = geo::addCurveLoop({67, -41, -71, 53});
        loopx11 = geo::addCurveLoop({74, -44, -71, 61});
        loopx12 = geo::addCurveLoop({73, 46, -72, -51});
        loopx13 = geo::addCurveLoop({47, 41, 7, -40});
        loopx14 = geo::addCurveLoop({45, 46, 47, 44});
        loopx15 = geo::addCurveLoop({-8, 43, 45, -42});
        loopx16 = geo::addCurveLoop({44, 42, -5, -41});
        loopx17 = geo::addCurveLoop({46, 40, 2, -43});
        
        sx1 = geo::addPlaneSurface({loopx1});
        sx2 = geo::addPlaneSurface({loopx2});
        sx3 = geo::addPlaneSurface({loopx3});
        sx4 = geo::addPlaneSurface({loopx4});
        
        sx5 = geo::addPlaneSurface({loopx5});
        sx6 = geo::addPlaneSurface({loopx6});
        sx7 = geo::addPlaneSurface({loopx7});
        sx8 = geo::addPlaneSurface({loopx8});
        
        sx9 = geo::addPlaneSurface({loopx9});
        sx10 = geo::addPlaneSurface({loopx10});
        sx11 = geo::addPlaneSurface({loopx11});
        sx12 = geo::addPlaneSurface({loopx12});
        
        sx13 = geo::addPlaneSurface({loopx13});
        sx14 = geo::addPlaneSurface({loopx14});
        sx15 = geo::addPlaneSurface({loopx15});
        sx16 = geo::addPlaneSurface({loopx16});
        
        sx17 = geo::addPlaneSurface({loopx17});
        
        mesh::setTransfiniteSurface(sx1, "Right"); mesh::setRecombine(2, sx1);
        mesh::setTransfiniteSurface(sx2, "Right"); mesh::setRecombine(2, sx2);
        mesh::setTransfiniteSurface(sx3, "Right"); mesh::setRecombine(2, sx3);
        mesh::setTransfiniteSurface(sx4, "Right"); mesh::setRecombine(2, sx4);
        mesh::setTransfiniteSurface(sx5, "Right"); mesh::setRecombine(2, sx5);
        mesh::setTransfiniteSurface(sx6, "Right"); mesh::setRecombine(2, sx6);
        mesh::setTransfiniteSurface(sx7, "Right"); mesh::setRecombine(2, sx7);
        mesh::setTransfiniteSurface(sx8, "Right"); mesh::setRecombine(2, sx8);
        mesh::setTransfiniteSurface(sx9, "Right"); mesh::setRecombine(2, sx9);
        mesh::setTransfiniteSurface(sx10, "Right"); mesh::setRecombine(2, sx10);
        mesh::setTransfiniteSurface(sx11, "Right"); mesh::setRecombine(2, sx11);
        mesh::setTransfiniteSurface(sx12, "Right"); mesh::setRecombine(2, sx12);
        mesh::setTransfiniteSurface(sx13, "Right"); mesh::setRecombine(2, sx13);
        mesh::setTransfiniteSurface(sx14, "Right"); mesh::setRecombine(2, sx14);
        mesh::setTransfiniteSurface(sx15, "Right"); mesh::setRecombine(2, sx15);
        mesh::setTransfiniteSurface(sx16, "Right"); mesh::setRecombine(2, sx16);
        mesh::setTransfiniteSurface(sx17, "Right"); mesh::setRecombine(2, sx17);
    }
    
    
    // FILL INTERNAL VOLUME
    //int sl1 = geo::addSurfaceLoop({sx2,ss2,sx11,sx7,sx9,s2}); int v1 = geo::addVolume({sl1});
    int sl1,sl2,sl3,sl4,sl5,sl6,sl7,sl8,sl9,sl10;
    int v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12;
    if (sphere_tag==1) {
        sl1 = geo::addSurfaceLoop({33,35,37,36,34,2}); v1 = geo::addVolume({sl1});
        sl2 = geo::addSurfaceLoop({22,39,40,36,38,1}); v2 = geo::addVolume({sl2});
        sl3 = geo::addSurfaceLoop({38,37,42,44,27,5}); v3 = geo::addVolume({sl3});
        sl4 = geo::addSurfaceLoop({40,41,45,34,17,4}); v4 = geo::addVolume({sl4});
        sl5 = geo::addSurfaceLoop({35,42,43,7,45,3}); v5 = geo::addVolume({sl5});
        sl6 = geo::addSurfaceLoop({44,39,41,43,32,6}); v6 = geo::addVolume({sl6});
        
        mesh::setTransfiniteVolume(v1); //mesh::setRecombine(3, v1);
        mesh::setTransfiniteVolume(v2); //mesh::setRecombine(3, v2);
        mesh::setTransfiniteVolume(v3); //mesh::setRecombine(3, v3);
        mesh::setTransfiniteVolume(v4); //mesh::setRecombine(3, v4);
        mesh::setTransfiniteVolume(v5); //mesh::setRecombine(3, v5);
        mesh::setTransfiniteVolume(v6); //mesh::setRecombine(3, v6);
        
        volumes.push_back(v1);
        volumes.push_back(v2);
        volumes.push_back(v3);
        volumes.push_back(v4);
        volumes.push_back(v5);
        volumes.push_back(v6);
    }
    if (sphere_tag==2) {
        sl7 = geo::addSurfaceLoop({84,57,71,78,79,73}); v7 = geo::addVolume({sl7});
        sl8 = geo::addSurfaceLoop({82,74,79,67,80,77}); v8 = geo::addVolume({sl8});
        sl9 = geo::addSurfaceLoop({81,76,77,78,70,52}); v9 = geo::addVolume({sl9});
        sl4 = geo::addSurfaceLoop({68,70,69,72,71,6}); v10 = geo::addVolume({sl4});
        sl5 = geo::addSurfaceLoop({83,73,72,75,74,62}); v11 = geo::addVolume({sl5});
        sl6 = geo::addSurfaceLoop({80,75,85,69,76,46}); v12 = geo::addVolume({sl6});
        
        mesh::setTransfiniteVolume(v7); //mesh::setRecombine(3, v1);
        mesh::setTransfiniteVolume(v8); //mesh::setRecombine(3, v2);
        mesh::setTransfiniteVolume(v9); //mesh::setRecombine(3, v3);
        mesh::setTransfiniteVolume(v10); //mesh::setRecombine(3, v4);
        mesh::setTransfiniteVolume(v11); //mesh::setRecombine(3, v5);
        mesh::setTransfiniteVolume(v12); //mesh::setRecombine(3, v6);
        
        volumes.push_back(v7);
        volumes.push_back(v8);
        volumes.push_back(v9);
        volumes.push_back(v10);
        volumes.push_back(v11);
        volumes.push_back(v12);
    }
    
    if (sphere_tag == 1){
        int pg7 = model::addPhysicalGroup(2,{ss1,ss2,ss3,ss4,ss5,s7}); model::setPhysicalName(2,pg7,"shell1");
    }
    if (sphere_tag == 2) {
        int pg7 = model::addPhysicalGroup(2,{ss1,ss2,ss3,ss4,ss5,s7}); model::setPhysicalName(2,pg7,"shell2");
        if (FAR != 1) {
            int pg3 = model::addPhysicalGroup(2,{1,2,3,4,5,84,81,83,82,85}); model::setPhysicalName(2,pg3,"far");
            int pv = model::addPhysicalGroup(3,{v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12});
            model::setPhysicalName(3,pv,"volume");
        }
    }
    
    

}

int main(int argc, char **argv)
{
    std::vector<std::pair<int, int> > ov, ovv, ovvv, surfacetags;
    std::vector<int> surfaces, volumes, groups;
    double sep=0, angle=0;
    double r1=atof(argv[1])/2, L=atof(argv[2])*2*r1, lc=1, l=atof(argv[2])*2*r1;
    double x1=0, y1=0, z1=0;
    double x2=x1-sep*cos(angle*M_PI/180), y2=y1+sep*sin(angle*M_PI/180), z2=z1-0;
    double x3=(x1-sep*cos(angle*M_PI/180))/2, y3=(y1+sep*sin(angle*M_PI/180))/2, z3=(z1-z2)/2;
    
    gmsh::initialize();
    gmsh::option::setNumber("General.Terminal", 1);
    gmsh::model::add("sphere1");
    
    //create sphere
    sphereMesh(x1,y1,z1,r1,l,lc,surfaces,volumes,1,sep);
    //sphereMesh(x2,y2,z2,r1,l,lc,surfaces,volumes,2,sep);
    
    // MESH
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(3);
    //gmsh::model::geo::removeAllDuplicates();
    //gmsh::model::geo::symmetrize({{3,6}}, 10,0,0,0);
    //gmsh::model::mesh::refine();
    //gmsh::model::mesh::smooth();
    //gmsh::model::mesh::setOrder(2);
    //gmsh::model::mesh::recombine("sphere1");
    
    // OUTPUT
    //gmsh::write("msh/spherical.cgns");
    gmsh::write("mesh_sphere.msh");
    gmsh::write("mesh_sphere.su2");
    gmsh::write("mesh_sphere.vtk");
    //gmsh::view::add("test");
    gmsh::fltk::run();
    gmsh::finalize();
    return 0;
}