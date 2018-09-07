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
  //has local placement (should not be relevant now?)
  auto data_collector = carve::input::PolyhedronData{};
  //TODO: add vertices, faces
  auto left_meshset = unique_ptr<MeshSet<3>>(data_collector.createMesh({}));
  data_collector.clearFaces();
  data_collector.points.clear();
  //TODO: add vertices, faces
  auto right_meshset = unique_ptr<MeshSet<3>>(data_collector.createMesh({}));

  auto csg_operator = CSG{};

  auto result = unique_ptr<MeshSet<3>>(
    csg_operator.compute(left_meshset.get(), right_meshset.get(),
    CSG::OP::A_MINUS_B, nullptr, CSG::CLASSIFY_TYPE::CLASSIFY_EDGE));

  return 0;
}

