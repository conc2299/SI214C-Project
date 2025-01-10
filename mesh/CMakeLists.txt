ADD_EXECUTABLE(
    test_mesh
    test_mesh.cpp
    mesh.cpp
    ${PROJECT_SOURCE_DIR}/region/cuboid.cpp
    ${PROJECT_SOURCE_DIR}/elements/nedelecp1.cpp
)

INCLUDE_DIRECTORIES (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/eigen
    ${PROJECT_SOURCE_DIR}/CDT
)