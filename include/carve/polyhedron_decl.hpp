// Copyright 2006-2015 Tobias Sargeant (tobias.sargeant@gmail.com).
//
// This file is part of the Carve CSG Library (http://carve-csg.com/)
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <carve/carve.hpp>

#include <carve/geom3d.hpp>

#include <carve/collection_types.hpp>
#include <carve/octree_decl.hpp>
#include <carve/polyhedron_base.hpp>

#include <cassert>
#include <list>

namespace carve {
namespace mesh {
template <unsigned ndim>
class MeshSet;
}

namespace poly {
class Polyhedron;
}

poly::Polyhedron* polyhedronFromMesh(const mesh::MeshSet<3>*, int);

namespace poly {

class Polyhedron : public Geometry<3> {
 private:
  friend Polyhedron* carve::polyhedronFromMesh(const mesh::MeshSet<3>*, int);

  CARVE_API Polyhedron() = default;

  CARVE_API Polyhedron& operator=(const Polyhedron&) = default;

  // *** initialization

  bool initSpatialIndex();
  void initVertexConnectivity();
  void setFaceAndVertexOwner();

  bool initConnectivity();
  bool markManifolds();
  bool calcManifoldEmbedding();

  bool init();
  void faceRecalc();

  void commonFaceInit(bool _recalc);

 public:
   CARVE_API static void collectFaceVertices(
      std::vector<face_t>& faces, std::vector<vertex_t>& vertices,
      std::unordered_map<const vertex_t*, const vertex_t*>& vmap);

   CARVE_API static void collectFaceVertices(std::vector<face_t>& faces,
                                  std::vector<vertex_t>& vertices);

  std::vector<bool> manifold_is_closed;
  std::vector<bool> manifold_is_negative;

  carve::geom3d::AABB aabb;
  carve::csg::Octree octree;

  // *** construction of Polyhedron objects

  CARVE_API Polyhedron(const Polyhedron&);

  // copy a single manifold
  CARVE_API Polyhedron(const Polyhedron&, int m_id);

  // copy a subset of manifolds
  CARVE_API Polyhedron(const Polyhedron&, const std::vector<bool>& selected_manifolds);

  CARVE_API Polyhedron(std::vector<face_t>& _faces, std::vector<vertex_t>& _vertices,
             bool _recalc = false);

  CARVE_API Polyhedron(std::vector<face_t>& _faces, bool _recalc = false);

  CARVE_API Polyhedron(std::list<face_t>& _faces, bool _recalc = false);

  CARVE_API Polyhedron(const std::vector<carve::geom3d::Vector>& vertices, int n_faces,
             const std::vector<int>& face_indices);

  CARVE_API ~Polyhedron();

  // *** containment queries

  CARVE_API void testVertexAgainstClosedManifolds(const carve::geom3d::Vector& v,
                                        std::map<int, PointClass>& result,
                                        bool ignore_orentation) const;

  CARVE_API PointClass containsVertex(const carve::geom3d::Vector& v,
                            const face_t** hit_face = nullptr,
                            bool even_odd = false, int manifold_id = -1) const;

  // *** locality queries

  CARVE_API void findEdgesNear(const carve::geom::aabb<3>& aabb,
                     std::vector<const edge_t*>& edges) const;
  CARVE_API void findEdgesNear(const carve::geom3d::LineSegment& l,
                     std::vector<const edge_t*>& edges) const;
  CARVE_API void findEdgesNear(const carve::geom3d::Vector& v,
                     std::vector<const edge_t*>& edges) const;
  CARVE_API void findEdgesNear(const face_t& face,
                     std::vector<const edge_t*>& edges) const;
  CARVE_API void findEdgesNear(const edge_t& edge,
                     std::vector<const edge_t*>& edges) const;

  CARVE_API void findFacesNear(const carve::geom::aabb<3>& aabb,
                     std::vector<const face_t*>& faces) const;
  CARVE_API void findFacesNear(const carve::geom3d::LineSegment& l,
                     std::vector<const face_t*>& faces) const;
  CARVE_API void findFacesNear(const edge_t& edge,
                     std::vector<const face_t*>& faces) const;

  // *** manifold queries

  inline bool vertexOnManifold(const vertex_t* v, int m_id) const;
  inline bool edgeOnManifold(const edge_t* e, int m_id) const;

  template <typename T>
  int vertexManifolds(const vertex_t* v, T result) const;

  template <typename T>
  int edgeManifolds(const edge_t* e, T result) const;

  inline size_t manifoldCount() const;

  inline bool hasOpenManifolds() const;

  // *** transformation

  // flip face directions
  CARVE_API void invertAll();
  CARVE_API void invert(const std::vector<bool>& selected_manifolds);

  inline void invert(int m_id);
  inline void invert();

  // matrix transform of vertices
  CARVE_API void transform(const carve::math::Matrix& xform);

  // arbitrary function transform of vertices
  template <typename T>
  void transform(const T& xform);

  CARVE_API void print(std::ostream&) const;

  CARVE_API void canonicalize();
};

std::ostream& operator<<(std::ostream&, const Polyhedron&);
}  // namespace poly
}  // namespace carve
