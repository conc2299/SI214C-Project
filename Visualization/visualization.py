import numpy as np
import matplotlib.pyplot as plt

def visualize_electromagnetic_field(field_matrix, dx=1, dy=1):
    """
    可视化二维电磁场的复数矩阵
    
    参数:
        field_matrix: 表示电场的二维复数numpy数组
        dx: x方向的网格间距 (默认为1)
        dy: y方向的网格间距 (默认为1)
    """
    # 计算场的幅值和相位
    magnitude = np.abs(field_matrix)
    phase = np.angle(field_matrix)
    
    # 创建坐标网格
    ny, nx = field_matrix.shape
    x = np.linspace(-(nx-1)*dx/2, (nx-1)*dx/2, nx)  # 居中坐标系
    y = np.linspace(-(ny-1)*dy/2, (ny-1)*dy/2, ny)
    X, Y = np.meshgrid(x, y)
    
    # 获取实部和虚部作为场向量的x和y分量
    Ex = np.real(field_matrix)
    Ey = np.imag(field_matrix)
    
    # 计算场强和归一化
    E_norm = np.sqrt(Ex**2 + Ey**2)
    eps = 1e-10  # 避免除零
    max_norm = np.max(E_norm)
    
    # 归一化，但保持方向信息
    Ex_norm = Ex / (max_norm + eps)
    Ey_norm = Ey / (max_norm + eps)
    
    # 创建图形
    fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(15, 5))
    
    # 1. 绘制场强度的热图
    im1 = ax1.pcolormesh(X, Y, magnitude, shading='auto', cmap='hot')
    ax1.set_title('Electric Field Magnitude')
    ax1.set_xlabel('x')
    ax1.set_ylabel('y')
    ax1.set_aspect('equal')
    plt.colorbar(im1, ax=ax1)
    
    # 2. 绘制相位图
    im2 = ax2.pcolormesh(X, Y, phase, shading='auto', cmap='hsv')
    ax2.set_title('Phase Distribution')
    ax2.set_xlabel('x')
    ax2.set_ylabel('y')
    ax2.set_aspect('equal')
    plt.colorbar(im2, ax=ax2)
    
    # 3. 绘制电场线（流线图）
    density = 2.0
    magnitude_normalized = magnitude / (np.max(magnitude) + eps)
    lw = 2 * magnitude_normalized  # 线宽随场强变化
    
    strm = ax3.streamplot(x, y, Ex, Ey,
                         density=density,
                         color=magnitude,
                         cmap='viridis',
                         linewidth=lw,
                         arrowsize=1.5)
    ax3.set_title('Electric Field Lines')
    ax3.set_xlabel('x')
    ax3.set_ylabel('y')
    ax3.set_aspect('equal')
    plt.colorbar(strm.lines, ax=ax3)
    
    plt.tight_layout()
    plt.savefig("./field.jpg")

if __name__ == "__main__":
    try:
        # 读取文件
        with open("field_matrix.txt", "r") as f:
            # 读取矩阵维度
            ny, nx = map(int, f.readline().split())
            # 读取复数数据
            data = []
            for line in f:
                real, imag = map(float, line.split())
                data.append(complex(real, imag))
            
            # 重塑为二维数组
            field_matrix = np.array(data).reshape(ny, nx)
            print("Successfully loaded field_matrix.txt")
            print("Matrix shape:", field_matrix.shape)
            
    except Exception as e:
        print(f"Error loading field_matrix.txt: {e}")
        print("Creating example data instead...")
        
        # 创建示例电磁场数据（保持原有的示例数据生成代码）
        nx, ny = 100, 100
        x = np.linspace(-5, 5, nx)
        y = np.linspace(-5, 5, ny)
        X, Y = np.meshgrid(x, y)
        R = np.sqrt(X**2 + Y**2)
        
        # 点电荷场
        eps = 0.1  # 避免奇点
        E_point = (X + 1j*Y) / (R + eps)**2
        
        # 行波场
        k1 = 2.0  # 波数
        sigma = 2.0  # 高斯包络的宽度
        wave1 = np.exp(-((X-2)**2 + Y**2)/(2*sigma**2)) * np.exp(1j*k1*X)
        wave2 = np.exp(-((X+2)**2 + Y**2)/(2*sigma**2)) * np.exp(-1j*k1*X)
        E_wave = wave1 + wave2
        
        # 合成场
        field_matrix = E_point + 0.5*E_wave
        
        print(field_matrix.shape)

        # 归一化场强
        print("Field matrix shape:", field_matrix.shape)
        print("Field matrix sample values:")
        print(field_matrix[0:5, 0:5])  # Print first 5x5 elements
        print("\nMax absolute value:", np.max(np.abs(field_matrix)))
        field_matrix = field_matrix / np.max(np.abs(field_matrix))
        
    visualize_electromagnetic_field(field_matrix)
 