ADD_EXECUTABLE(
    test_mesh
    test_mesh.cpp
    mesh.cpp
)

INCLUDE_DIRECTORIES (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/eigen
    ${PROJECT_SOURCE_DIR}/CDT
)