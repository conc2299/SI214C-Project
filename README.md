# SI214C-Project
Solving time-harmonic Maxwell's Equation using finite element method

Authors: Yikai Liu, ZhiYuan Cheng, QiZhang He.

## Weak formula of time-harmonic Maxwell's Equation
Note: all fields below are complex valued functions.(i.e. $\mathbb{R}^3\rightarrow \mathbb{C}$)
### Without free charge
$$
    \Delta \overrightarrow{E}+\omega^2\tilde{\mu}\tilde{\epsilon}\overrightarrow{E} = j\omega\tilde{\mu}\overrightarrow{J_{\alpha}}
$$
In one direction (e.g. $x$)
$$
    \Delta E_x+\omega^2\tilde{\mu}\tilde{\epsilon}E_x = j\omega\tilde{\mu}J_{\alpha x}
$$
weak form
$$
\begin{aligned}
    \int_{\Omega}(\Delta E_x+\omega^2\tilde{\mu}\tilde{\epsilon}E_x)vd\omega&=j\omega\tilde{\mu}\int_{\Omega}J_{\alpha x}vd\omega \\
    \int_{\Omega}\nabla E_x\cdot\nabla vd\omega - \int_{\Omega}\nabla\cdot(v\nabla E_x)d\omega+ \omega^2\tilde{\mu}\tilde{\epsilon}\int_{\Omega}E_xvd\omega &= j\omega\tilde{\mu}\int_{\Omega}J_{ax}vd\omega\\
    \int_{\Omega}\nabla E_x\cdot\nabla vd\omega-\int_{\partial\Omega}v\nabla E_xd\omega+\omega^2\tilde{\mu}\tilde{\epsilon}\int_{\Omega}E_xvd\omega&=j\omega\tilde{\mu}\int_{\Omega}J_{ax}vd\omega\\
\end{aligned}
$$
### With free charge
$$
    \Delta \overrightarrow{E}+\omega^2\tilde{\mu}\tilde{\epsilon}\overrightarrow{E} = j\omega\tilde{\mu}\overrightarrow{J_{\alpha}} + \nabla(\frac{\rho}{\epsilon})
$$

# TODO
1. Tetrahedra element in 3D space. Maybe we can solve in simple 2D space first
    - 2D 1st-order first kind $\text{N\'ed\'elec}$ element. $H(curl)$-comforming
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
    - Element 
4. Organization
    - Visualization (Zhiyuan Cheng)
    - Solver (QiZhang He)
    - Problem formulation(Yikai Liu)
    - add nothing