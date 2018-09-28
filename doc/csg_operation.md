@page csg_mode_of_operation How CSG operations work

The following graph illustrates the calls made during a single compute call for two meshes.

@dot
digraph call_sequence {
  compute;
  construct_STR;
  calc;
  generateIntersections;
  generateIntersectionCandidates;
  generateVertexVertexIntersections;
  generateVertexEdgeIntersections;
  generateEdgeEdgeIntersections;
  generateVertexFaceIntersections;
  generateEdgeFaceIntersections;
  compute -> construct_STR [label=1.];
  compute -> calc [label=2.];
  calc -> generateIntersections [label=3.];
  generateIntersections -> generateIntersectionCandidates [label=4.];
  generateIntersections -> generateVertexVertexIntersections [label=5.];
  generateIntersections -> generateVertexEdgeIntersections [label=6.];

  generateIntersections -> generateEdgeEdgeIntersections [label=7.];
  generateIntersections -> generateVertexFaceIntersections [label=8.];
  generateIntersections -> generateEdgeFaceIntersections [label=9.];
}
@enddot

Detailed explanations follow.

Step 1 builds a R-tree for each input mesh. These will be used to speed up finding intersections. \n
Calc in step 2 is the main work function to find intersecting faces and define the new geometry. \n
Then in step 3 find intersecting and touching vertices, edges and faces with multiple sub-steps.
GenerateIntersectionCandidates in step 4 first recurses down to the leaf level. Then it compares
bounding boxes of the nodes to find possible intersecting faces. All candidates are returned in the
`face_pairs` variable. After returning it fill the `vert_to_edge` member of the `data` struct with
vertices as index and edges containing those vertices as values.

Steps 5 till 9 test the candidates for certain types of intersections.
GenerateVertexVertexIntersections tests for touching vertices. GenerateVertexEdgeIntersections tests
for intersections by building a cross product between the line and the vertex. and test if the
length of the resulting vector is small enough (mathematically zero when exactly on the line).


Continue at: intersect.cpp:1018

