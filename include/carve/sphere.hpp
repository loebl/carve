// Copyright 2006-2015 Tobias Sargeant (tobias.sargeant@gmail.com).
//
// This file is part of the Carve CSG Library (http://carve-csg.com/)
// For licensing terms see LICENSE

#pragma once

#include <ostream>
#include <algorithm>
#include <carve/vector.hpp>
#include <carve/aabb.hpp>

namespace carve {
namespace geom {

template <unsigned ndim>
struct sphere {
  vector<ndim> C;
  double r = 1.0;

  sphere() { C.setZero(); }

  aabb<ndim> getAABB() const {
    aabb<ndim> box;
    box.fit(C - r, C + r);
    return box;
  }
};

template <unsigned ndim, typename val_t>
inline auto distance(const sphere<ndim>& sphere, const val_t& point) {
  return std::max(0.0, distance(sphere.C, point) - sphere.r);
}

template <unsigned ndim, typename val_t>
inline auto distance2(const sphere<ndim>& sphere, const val_t& point) {
  return std::max(0.0, distance2(sphere.C, point) - sphere.r * sphere.r);
}

template <unsigned ndim>
inline auto closestPoint(const sphere<ndim>& sphere,
                          const vector<ndim>& point) {
  return (point - sphere.C).normalized() * sphere.r;
}

template <unsigned ndim>
inline std::ostream& operator<<(std::ostream& o,
                         const sphere<ndim>& sphere) {
  o << "{sphere " << sphere.C << ";" << sphere.r << "}";
  return o;
}

//forward declarations of instantiations in lib
extern template struct sphere<2>;
extern template struct sphere<3>;

}
}
