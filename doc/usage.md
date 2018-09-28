@page using_carve Using Carve

First meshset of the used geometry have to be created. These can then be used to compute CSG
operations.

A meshset can be created with the carve::input::PolyhedronData helper class. All vertices and vertex
indices are entered into this class and a meshet can then be created with a call to
PolyhedronData::createMesh.
