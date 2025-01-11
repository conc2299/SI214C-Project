ADD_EXECUTABLE(
    element_test
    element_test.cpp
    ${PROJECT_SOURCE_DIR}/elements/nedelecp1.cpp
)

INCLUDE_DIRECTORIES (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/eigen
)