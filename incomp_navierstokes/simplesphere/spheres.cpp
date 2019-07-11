#include <cstdio>
#include <iostream>
#include <cmath>
#include <gmsh.h>

using namespace std;
namespace model = gmsh::model;

int main(int argc, char **argv)
{
    std::vector<std::pair<int, int> > ov;
    std::vector<std::vector<std::pair<int, int> > > ovv;
    double R = atof(argv[1]), L = 2*R*atof(argv[2]), size=1, lc=1e-1;

    //INITS
    gmsh::initialize(argc, argv);
    gmsh::option::setNumber("General.Terminal", 2);
    gmsh::model::add("sphere1");
    //gmsh::fltk::initialize();
    gmsh::model::add("boolean");
    //gmsh::option::setNumber("Mesh.Algorithm", 8);

    //MESH OPTIONS
    //gmsh::option::setNumber("Mesh.IgnorePeriodicity",1);
    //gmsh::option::setNumber("Mesh.RecombinationAlgorithm", 3);
    //gmsh::option::setNumber("Mesh.Algorithm3D", 8);
    //gmsh::option::setNumber("Mesh.RecombineAll", 3);
    //gmsh::option::setNumber("Mesh.RecombineAll", 3);
    //gmsh::option::setNumber("Mesh.Recombine3DAll",3);
    //gmsh::option::setNumber("Mesh.Recombine3DLevel",0);
    gmsh::option::setNumber("Mesh.CharacteristicLengthMin", size/2);
    gmsh::option::setNumber("Mesh.CharacteristicLengthMax", size);
    
    //GEOMETRY
    //gmsh::model::occ::addBox(-L,-L,-L, 2*L,2*L,2*L, 1);
    gmsh::model::occ::addSphere(0,0,0,L, 1);
    gmsh::model::occ::addSphere(0,0,0,R, 2);
    gmsh::model::occ::addSphere(0,3,0,R, 3);
    gmsh::model::occ::cut({{3, 1}}, {{3, 2},{3, 3}}, ov, ovv, 4);

    //FIELD OPTIONS
    //model::mesh::field::add("Distance", 1);
    //model::mesh::field::setNumbers(1, "FacesList", {7});
    //model::mesh::field::add("Threshold", 2);
    //model::mesh::field::setNumber(2, "LcMin", lc / 25);
    //model::mesh::field::setNumber(2, "LcMax", 2*lc);
    //model::mesh::field::add("Threshold", 7);
    //model::mesh::field::setNumber(7, "IField", 1);
    //model::mesh::field::setNumber(7, "LcMin", 1e-2 / 30);
    //model::mesh::field::setNumber(7, "LcMax", 1e-2);
    //model::mesh::field::setNumber(7, "DistMin", 1);
    //model::mesh::field::setNumber(7, "DistMax", 2);

    //DEFINE PHYSICAL GROUP
    int outershell = gmsh::model::addPhysicalGroup(2, {7});
    //int boxshell = gmsh::model::addPhysicalGroup(2, {1,2,3,4,5,6});
    int filling = gmsh::model::addPhysicalGroup(3, {3});
    gmsh::model::setPhysicalName(2, outershell, "eggshell");
    //gmsh::model::setPhysicalName(2, boxshell, "farfield");
    gmsh::model::setPhysicalName(3, filling, "volume");

    //OUTPUT
    gmsh::model::occ::synchronize();
    gmsh::model::mesh::generate(3);
    gmsh::write("msh/junk.msh");
    gmsh::write("msh/junk.su2");
    gmsh::write("msh/junk.vtk");
    gmsh::fltk::run();
    gmsh::finalize();
    return 0;

}

