#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <gmsh.h>

using namespace std;
namespace model = gmsh::model;

int main(int argc, char **argv)
{
    std::vector<std::pair<int, int> > ov;
    std::vector<std::vector<std::pair<int, int> > > ovv;
    double D= atof(argv[1]); //diameter of sphere
    double L= D*atof(argv[2]); //size of cube (2Lx2Lx2L)
    double sep= D*atof(argv[3]); //diameter size dist.
    double angle= atof(argv[4]); //rotation of sphere
    double size= 0.25, lc=1e-1; //mesh params
    double x1=0, y1=0, z1=0, x2=x1-sep*cos(angle*M_PI/180), y2=y1+sep*sin(angle*M_PI/180), z2=z1-0;

    //INITS
    gmsh::initialize(argc, argv);
    gmsh::option::setNumber("General.Terminal", 2);
    gmsh::model::add("sphere1");
    //gmsh::fltk::initialize();
    gmsh::model::add("boolean");

    //MESH OPTIONS
    gmsh::option::setNumber("Mesh.Algorithm", 6);
    gmsh::option::setNumber("Mesh.Algorithm3D", 10); //10HXT - HEXA ALG
    gmsh::option::setNumber("Mesh.CharacteristicLengthMin", size);
    gmsh::option::setNumber("Mesh.CharacteristicLengthMax", size);
    //gmsh::option::setNumber("Mesh.CharacteristicLengthExtendFromBoundary", size/25);
    //gmsh::option::setNumber("Mesh.SecondOrderLinear", 3);
    //gmsh::option::setNumber("Mesh.CharacteristicLengthFromPoints",1);
    //gmsh::option::setNumber("Mesh.RecombinationAlgorithm", 3);
    //gmsh::option::setNumber("Mesh.Algorithm3D", 8);
    //gmsh::option::setNumber("Mesh.RecombineAll", 3);
    //gmsh::option::setNumber("Mesh.Recombine3DAll",3);
    //gmsh::option::setNumber("Mesh.Recombine3DLevel",0);
    
    //GEOMETRY
    //gmsh::model::occ::addBox(-L,-L,-L, 2*L,2*L,2*L, 1);
    gmsh::model::occ::addSphere(abs(x1-x2)/2,abs(y1-y2)/2,abs(z1-z2)/2,L, 1);
    gmsh::model::occ::addSphere(x1,y1,z1,D/2, 2);
    gmsh::model::occ::addSphere(x2,y2,z2,D/2, 3);
    gmsh::model::occ::cut({{3, 1}}, {{3, 2},{3, 3}}, ov, ovv, 4);
    gmsh::model::occ::synchronize();

    cout << "sin(angle)= " << sin(angle*M_PI/180) << " angle " << angle << endl;
    //FIELD OPTIONS - DOESN'T WORK WITH OCC
    //model::mesh::field::add("Distance", 1);
    //model::mesh::field::setNumbers(1, "FacesList", {1,2,3,4,5,6,7});
    //model::mesh::field::add("Threshold", 2);
    //model::mesh::field::setNumber(2, "IField", 1);
    //model::mesh::field::setNumber(2, "LcMin", lc / 25);
    //model::mesh::field::setNumber(2, "LcMax", lc);
    //model::mesh::field::setNumber(2, "DistMin", 1);
    //model::mesh::field::setNumber(2, "DistMax", 1);
    //model::mesh::field::add("Threshold", 7);

    //DEFINE PHYSICAL GROUP - DOESN'T WORK WITH OCC
    //model::addPhysicalGroup(2,{1,2,3,4,5,6},1); model::setPhysicalName(2,1,"far");
    int far = gmsh::model::addPhysicalGroup(2, {1});
    int shell1 = gmsh::model::addPhysicalGroup(2, {2});
    int shell2 = gmsh::model::addPhysicalGroup(2, {3});
    int filling = gmsh::model::addPhysicalGroup(3, {4});
    gmsh::model::setPhysicalName(2, far, "far");
    gmsh::model::setPhysicalName(2, shell1, "shell2");
    gmsh::model::setPhysicalName(2, shell2, "shell1");
    gmsh::model::setPhysicalName(3, filling, "volume");

    //OUTPUT
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::refine();
    gmsh::model::mesh::setOrder(3);
    gmsh::model::mesh::generate(3);
    gmsh::write("mesh_sphere.msh");
    gmsh::write("mesh_sphere.su2");
    gmsh::write("mesh_sphere.vtk");
    
    //gmsh::fltk::run();
    gmsh::finalize();
    return 0;

}

