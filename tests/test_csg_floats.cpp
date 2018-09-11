// Copyright 2006-2015 Tobias Sargeant (tobias.sargeant@gmail.com).
//
// This file is part of the Carve CSG Library (http://carve-csg.com/)
// See LICENSE for licensing terms

#include <iostream>
#include <memory>
#include <array>
#include <limits>
#include <initializer_list>

#include <carve/csg.hpp>
#include <carve/input.hpp>

using std::unique_ptr;
using carve::mesh::MeshSet;
using carve::csg::CSG;

int main(int, char const**)
{
  //model accuracy: 10^-5
  auto data_collector = carve::input::PolyhedronData{};
  //IFC4_AC20-Institute-Var-2.ifc; #229944
  //taken from memory while debugging app
  auto vertex = carve::geom::vector<3>{};
  vertex.x = 6.9536057896031247;
  vertex.y = -0.29999999999999999;
  vertex.z = 1.6401676805800001;
  data_collector.addVertex(vertex); //[0]
  vertex.x = 11.699999999999999;
  vertex.y = -0.29999999999999999;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[1]
  vertex.x = 0.29999999999999999;
  vertex.y = -0.29999999999999999;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[2]
  vertex.x = 7.0171795089100000;
  vertex.y = -0.29999999999999999;
  vertex.z = 1.6401676805800001;
  data_collector.addVertex(vertex); //[3]
  vertex.x = 0.29999999999999999;
  vertex.y = -0.29999999999999999;
  vertex.z = 0.00000000000000000;
  data_collector.addVertex(vertex); //[4]
  vertex.x = 4.9828204910900000;
  vertex.y = -0.29999999999999999;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[5]
  vertex.x = 7.0171795089100000;
  vertex.y = -0.29999999999999999;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[6]
  vertex.x = 7.0171795089100000;
  vertex.y = -0.29999999999999999;
  vertex.z = 2.0151676805799994;
  data_collector.addVertex(vertex); //[7]
  vertex.x = 11.699999999999999;
  vertex.y = -0.29999999999999999;
  vertex.z = 0.00000000000000000;
  data_collector.addVertex(vertex); //[8]
  vertex.x = 0.00000000000000000;
  vertex.y = 0.00000000000000000;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[9]
  vertex.x = 4.9828204910900000;
  vertex.y = -0.12776462797666668;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[10]
  vertex.x = 0.00000000000000000;
  vertex.y = 0.00000000000000000;
  vertex.z = 0.00000000000000000;
  data_collector.addVertex(vertex); //[11]
  vertex.x = 4.9828204910900000;
  vertex.y = -0.29999999999999999;
  vertex.z = 1.6401676805800001;
  data_collector.addVertex(vertex); //[12]
  vertex.x = 4.9828204910900000;
  vertex.y = 0.00000000000000000;
  vertex.z = 2.0151676805799994;
  data_collector.addVertex(vertex); //[13]
  vertex.x = 7.0171795089100000;
  vertex.y = 0.00000000000000000;
  vertex.z = 1.6401676805800001;
  data_collector.addVertex(vertex); //[14]
  vertex.x = 4.9828204910900000;
  vertex.y = -0.018262195184533370;
  vertex.z = 2.7000000000000011;
  data_collector.addVertex(vertex); //[15]
  vertex.x = 12.000000000000000;
  vertex.y = 0.00000000000000000;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[16]
  vertex.x = 7.0171795089100000;
  vertex.y = 0.00000000000000000;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[17]
  vertex.x = 12.000000000000000;
  vertex.y = 0.00000000000000000;
  vertex.z = 0.00000000000000000;
  data_collector.addVertex(vertex); //[18]
  vertex.x = 7.0171795089100000;
  vertex.y = -0.28173780481546662;
  vertex.z = 2.7000000000000011;
  data_collector.addVertex(vertex); //[19]
  vertex.x = 7.0171795089100000;
  vertex.y = -0.17992767971564103;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[20]
  vertex.x = 5.0463942103968753;
  vertex.y = 0.00000000000000000;
  vertex.z = 1.6401676805800001;
  data_collector.addVertex(vertex); //[21]
  vertex.x = 4.9828204910900000;
  vertex.y = 0.00000000000000000;
  vertex.z = 1.6401676805800001;
  data_collector.addVertex(vertex); //[22]
  vertex.x = 4.9828204910899991;
  vertex.y = 0.00000000000000000;
  vertex.z = 2.7000000000000002;
  data_collector.addVertex(vertex); //[23]
  vertex.x = 7.0171795089100000;
  vertex.y = -0.29999999999999999;
  vertex.z = 0.0;
  data_collector.addVertex(vertex); //[24]
  vertex.x = 7.0171795089100000;
  vertex.y = 0.00000000000000000;
  vertex.z = 0.0;
  data_collector.addVertex(vertex); //[25]
  //first cut inside left
  auto faces = std::vector<int>{12, 22, 13, 23, 15, 10, 5};
  data_collector.addFace(std::begin(faces), std::end(faces));
  //data_collector.addFace(2, 9, 11, 4); //left outside
  faces = {2, 5, 10, 15, 23, 9}; //left top
  data_collector.addFace(std::begin(faces), std::end(faces));
  //faces = {14, 3, 0, 12, 22, 21}; //mid sunken
  //data_collector.addFace(std::begin(faces), std::end(faces));
  //data_collector.addFace(25, 24, 3, 14); //right outside
  faces = {3, 24, 4, 2, 5, 12, 0}; //front
  data_collector.addFace(std::begin(faces), std::end(faces));
  //data_collector.addFace(4, 8, 1); //[0]
  //data_collector.addFace(12, 2, 4); //[1]
  //data_collector.addFace(12, 5, 2); //[2]
  //data_collector.addFace(1, 6, 7); //[3]
  //data_collector.addFace(1, 7, 3); //[4]
  //data_collector.addFace(4, 1, 3); //[5]
  //data_collector.addFace(0, 12, 4); //[6]
  //data_collector.addFace(3, 0, 4); //[7]
  //data_collector.addFace(4, 11, 8); //[8]
  //data_collector.addFace(16, 1, 8); //[9]
  //data_collector.addFace(1, 20 ,19); //[10]
  //data_collector.addFace(6, 1, 19); //[11]
  //data_collector.addFace(2, 5, 10); //12
  //data_collector.addFace(2, 10, 9); //13
  //data_collector.addFace(11, 4, 2); //14
  //data_collector.addFace(8, 11, 18); //15
  //data_collector.addFace(8, 18, 16); //16
  //data_collector.addFace(17, 20 ,1); //17
  //data_collector.addFace(1, 16, 17); //18
  //data_collector.addFace(2, 9, 11); //19
  //data_collector.addFace(23, 9, 10); //20
  //data_collector.addFace(23, 10, 15); //21
  //data_collector.addFace(18, 11, 9); //22
  //data_collector.addFace(14, 16, 18); //23
  //data_collector.addFace(14, 17, 16); //24
  //data_collector.addFace(22, 23, 13); //25
  //data_collector.addFace(9, 23, 22); //26
  //data_collector.addFace(18, 9, 22); //27
  //data_collector.addFace(21, 14, 18); //28
  //data_collector.addFace(22, 21, 18); //29
  //data_collector.addFace(14, 3, 7); //30
  //data_collector.addFace(17, 14, 7); //31
  //data_collector.addFace(20, 17, 7); //32
  //data_collector.addFace(7, 19, 20); //33
  //data_collector.addFace(0, 3, 14); //34
  //data_collector.addFace(0, 14, 21); //35
  //data_collector.addFace(7, 6, 19); //36
  //data_collector.addFace(21, 22, 12); //37
  //data_collector.addFace(21, 12, 0); //38
  //data_collector.addFace(12, 22, 13); //39
  //data_collector.addFace(5, 12, 13); //40
  //data_collector.addFace(10, 5, 13); //41
  //data_collector.addFace(13, 15, 10); //42
  //data_collector.addFace(13, 23, 15); //43
  auto left_meshset = unique_ptr<MeshSet<3>>(data_collector.createMesh({}));

  data_collector.clearFaces();
  data_collector.points.clear();
  //problematic polygonal half space
  vertex.x = 2.970799475980000;
  vertex.y = -0.31;
  vertex.z = 1.3395216292826466;
  data_collector.addVertex(vertex); //0
  vertex.x = 4.982820491090000;
  vertex.y = -0.31;
  vertex.z = 1.6401676805811138;
  data_collector.addVertex(vertex); //1
  vertex.x = 4.982820491090000;
  vertex.y = 0.01;
  vertex.z = 1.6401676805811138;
  data_collector.addVertex(vertex); //2
  vertex.x = 2.970799475980000;
  vertex.y = 0.01;
  vertex.z = 1.3395216292826466;
  data_collector.addVertex(vertex); //3
  vertex.x = 2.970799475980000;
  vertex.y = -0.31;
  vertex.z = 13.339521629282647;
  data_collector.addVertex(vertex); //4
  vertex.x = 4.982820491090000;
  vertex.y = -0.31;
  vertex.z = 13.640167680581117;
  data_collector.addVertex(vertex); //5
  vertex.x = 4.982820491090000;
  vertex.y = 0.01;
  vertex.z = 13.640167680581117;
  data_collector.addVertex(vertex); //6
  vertex.x = 2.970799475980000;
  vertex.y = 0.01;
  vertex.z = 13.339521629282647;
  data_collector.addVertex(vertex); //7
  data_collector.addFace(0, 1, 2, 3);
  data_collector.addFace(7, 6, 5, 4);
  data_collector.addFace(0, 4, 5, 1);
  data_collector.addFace(6, 7, 3, 2);
  data_collector.addFace(2, 1, 5, 6);
  data_collector.addFace(0, 3, 7, 4);
  auto right_meshset = unique_ptr<MeshSet<3>>(data_collector.createMesh({}));

  auto csg_operator = CSG{};
  auto result = unique_ptr<MeshSet<3>>(
    csg_operator.compute(left_meshset.get(), right_meshset.get(),
    CSG::OP::A_MINUS_B, nullptr, CSG::CLASSIFY_TYPE::CLASSIFY_EDGE));

  return 0;
}

