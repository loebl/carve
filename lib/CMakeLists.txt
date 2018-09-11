include_directories("${carve_SOURCE_DIR}/include")

# When building static libraries, cmake won't expose the created pdb file
# (for installing with TARGET_PDB_FILE)
# So we embed debug information into the static library using the /Z7 debugging format
if(MSVC AND NOT BUILD_SHARED_LIBS)
    string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_DEBUG  ${CMAKE_CXX_FLAGS_DEBUG})
    string(REPLACE "/Zi" "/Z7" CMAKE_CXX_FLAGS_RELWITHDEBINFO  ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
ENDIF()

add_definitions(-DCOMPILING_LIBRARY)

add_library(carve
            carve.cpp
            convex_hull.cpp
            csg.cpp
            csg_collector.cpp
            edge.cpp
            face.cpp
            geom2d.cpp
            geom3d.cpp
            intersect.cpp
            intersect_classify_edge.cpp
            intersect_classify_group.cpp
            intersect_debug.cpp
            intersect_face_division.cpp
            intersect_group.cpp
            intersect_half_classify_group.cpp
            intersection.cpp
            math.cpp
            mesh.cpp
            octree.cpp
            pointset.cpp
            polyhedron.cpp
            polyline.cpp
            tag.cpp
            timing.cpp
            triangulator.cpp
            triangle.cpp
            triangle_intersection.cpp
            shewchuk_predicates.cpp)

set_target_properties(carve PROPERTIES
                      VERSION   "${carve_VERSION_MAJOR}.${carve_VERSION_MINOR}.${carve_VERSION_PATCH}"
                      SOVERSION "${carve_VERSION_MAJOR}.${carve_VERSION_MINOR}")

install(TARGETS carve
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

if(MSVC AND BUILD_SHARED_LIBS)
    IF(CMAKE_GENERATOR MATCHES "^Visual Studio")
        install(FILES  $<TARGET_PDB_FILE:carve> DESTINATION lib OPTIONAL)
    ENDIF()
ENDIF ()
