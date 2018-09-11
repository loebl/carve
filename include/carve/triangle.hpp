// Copyright 2006-2015 Tobias Sargeant (tobias.sargeant@gmail.com).
//
// This file is part of the Carve CSG Library (http://carve-csg.com/)
// For licensing terms see LICENSE

#pragma once

#include <carve/vector.hpp>
#include <array>

namespace carve {
namespace geom {
template <unsigned ndim>
struct tri {
  typedef vector<ndim> vector_t;

  std::array<vector_t,3> v;

  aabb<ndim> getAABB() const {
    aabb<ndim> box;
    box.fit(v[0], v[1], v[2]);
    return box;
  }
  vector_t normal() const { return cross(v[1] - v[0], v[2] - v[1]).normalized(); }

  //tri() = default;
  //tri(std::array<vector_t,3> const& _v) { std::copy(v, v + 3, _v); }
  //tri(const vector_t& a, const vector_t& b, const vector_t& c) {
  //  v[0] = a;
  //  v[1] = b;
  //  v[2] = c;
  //}
};

template <unsigned ndim>
vector<ndim> closestPoint(const tri<ndim>& tri, const vector<ndim>& pt);
template <unsigned ndim>
double distance(const tri<ndim>& tri, const vector<ndim>& pt);
template <unsigned ndim>
double distance2(const tri<ndim>& tri, const vector<ndim>& pt);

template <unsigned ndim>
std::ostream& operator<<(std::ostream& o, const tri<ndim>& tri);



//implementation

template <unsigned ndim>
std::ostream& operator<<(std::ostream& o, const carve::geom::tri<ndim>& tri) {
  o << "{tri " << tri.v[0] << ";" << tri.v[1] << ";" << tri.v[2] << "}";
  return o;
}

template <unsigned ndim>
double distance(const tri<ndim>& tri, const vector<ndim>& pt) {
  return distance(closestPoint(tri, pt), pt);
}

template <unsigned ndim>
double distance2(const tri<ndim>& tri, const vector<ndim>& pt) {
  return distance2(closestPoint(tri, pt), pt);
}

//template <>
//vector<2> closestPoint(const tri<2>& tri, const vector<2>& pt) {
//  return vector<2>::ZERO();
//}

extern template CARVE_API vector<3> closestPoint(const tri<3>& tri, const vector<3>& pt);

}
}

