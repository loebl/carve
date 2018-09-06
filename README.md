# Introduction

This is the Carve mesh modification library. It supports union,intersection and
difference of polygonal meshes. It assumes the polygons are flat (no support for
3d-polygons).

# Current changes to original carve

Mostly cosmetic changes.

- A few headers cleaned up
- Modifications from IfcPLusPlus for MSVC++ 2015
- Add declarations to export functions on Windows. Not everything is exported,
  just enough to get IfcPlusPlus working with Carve as dll. This might also be
  used to limit exports on Linux/Mac. YMMV.

