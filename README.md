# SI214C-Project
Solving time-harmonic Maxwell's Equation using finite element method

Authors: Yikai Liu, ZhiYuan Cheng, QiZhang He.

# TODO
1. Tetrahedra element in 3D space 
2. Libraries
    - Matrix solving (Eigen, SuiteSparse)
    - Visualization
3. Basic abstractions (Important: If you come up with better abstractions, modify directly)
    - Solving space (The space where finite elements exists, should be a connected subset of R^3)
    - Region (A region is the space where EM-fields exist and has the same permeability(mu) and permitivity(epsilon))
        - Different types of regions
            - Polyhedron (Maybe too complex??)
                - Cuboid (necessary)
                - Tetrahedra
            - Sphere (necessary)
    - Constraint (the conditions that EM-fields must satisfy at certain points (usually at boundary))
    - Element ()
