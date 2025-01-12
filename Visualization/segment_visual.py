import numpy as np
import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
import matplotlib.colors as colors

class FieldVisualizer:
    def __init__(self):
        self.segments = []  # 存储线段数据
        self.field_strengths = []  # 存储场强数据
        self.domain = None  # 存储计算域范围
        
    def load_segments(self, filename):
        """从文件加载线段和场强数据"""
        with open(filename, 'r') as f:
            # 读取计算域范围
            domain = f.readline().strip()
            # 解析域范围字符串 "(0 0),(1 1)"
            domain = domain.replace(' ', ',')  # 将空格替换为逗号
            domain_points = domain.split('),(')
            start = tuple(map(float, domain_points[0].strip('(').split(',')))
            end = tuple(map(float, domain_points[1].strip(')').split(',')))
            self.domain = (start, end)
            
            # 读取线段数量
            n_segments = int(f.readline().strip())
            
            # 读取每个线段数据
            for line in f.readlines():
                if not line.strip():
                    continue
                    
                # 分割坐标和场强
                parts = line.split(':')
                if len(parts) == 2:
                    coords, strength = parts
                else:
                    coords = parts[0]
                    strength = '(0,0)'
                
                # 处理坐标
                start_str, end_str = coords.split('),(')
                start = tuple(map(float, start_str.strip('(').split()))
                end = tuple(map(float, end_str.strip(')').split()))
                
                # 处理场强
                strength = strength.strip('()\n')
                real, imag = map(float, strength.split(','))
                
                self.segments.append([start, end])
                self.field_strengths.append(complex(real, imag))
                
    def plot_field_lines(self, n_points=100):
        """绘制电场线"""
        fig, ax = plt.subplots(figsize=(12, 10))
        
        # 绘制边界线段
        segments = np.array(self.segments)
        strengths = np.abs(self.field_strengths)
        
        # 创建颜色映射
        norm = colors.LogNorm(vmin=max(1e-10, min(strengths)), vmax=max(strengths))
        lc = LineCollection(segments, cmap='viridis', norm=norm)
        lc.set_array(strengths)
        
        ax.add_collection(lc)
        plt.colorbar(lc, label='场强大小 |E|')
        
        # 使用文件中给定的计算域范围
        x_min, y_min = self.domain[0]
        x_max, y_max = self.domain[1]
        
        # 添加边界余量
        margin = 0.1 * max(x_max - x_min, y_max - y_min)
        x_min -= margin
        x_max += margin
        y_min -= margin
        y_max += margin
        
        # 创建网格点
        x = np.linspace(x_min, x_max, n_points)
        y = np.linspace(y_min, y_max, n_points)
        X, Y = np.meshgrid(x, y)
        
        # 计算每个点的电场
        Ex = np.zeros_like(X)
        Ey = np.zeros_like(Y)
        
        for (start, end), strength in zip(self.segments, self.field_strengths):
            dx = end[0] - start[0]
            dy = end[1] - start[1]
            length = np.sqrt(dx**2 + dy**2)
            direction = np.array([dx/length, dy/length])
            
            # 使用向量化操作加速计算
            for i in range(n_points):
                points = np.column_stack((X[i,:], Y[i,:]))
                for j, point in enumerate(points):
                    r = point - np.array(start)
                    r_mag = np.linalg.norm(r)
                    if r_mag > 0:
                        field = direction * np.abs(strength) / (r_mag)
                        Ex[i,j] += field[0]
                        Ey[i,j] += field[1]
        
        # 绘制电场箭头
        skip = (slice(None, None, 3), slice(None, None, 3))
        magnitude = np.sqrt(Ex**2 + Ey**2)
        ax.quiver(X[skip], Y[skip], Ex[skip]/magnitude[skip], Ey[skip]/magnitude[skip],
                 magnitude[skip], cmap='viridis', scale=30)
        
        ax.set_aspect('equal')
        ax.set_xlim(x_min, x_max)
        ax.set_ylim(y_min, y_max)
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_title('电场可视化')
        
        plt.show()

    def plot_field_strength(self, n_points=100):
        """绘制电场强度热图"""
        fig, ax = plt.subplots(figsize=(12, 10))
        
        # 使用文件中给定的计算域范围
        x_min, y_min = self.domain[0]
        x_max, y_max = self.domain[1]
        
        # 添加边界余量
        margin = 0.1 * max(x_max - x_min, y_max - y_min)
        x_min -= margin
        x_max += margin
        y_min -= margin
        y_max += margin
        
        # 创建更密集的网格点以获得更平滑的可视化效果
        x = np.linspace(x_min, x_max, n_points)
        y = np.linspace(y_min, y_max, n_points)
        X, Y = np.meshgrid(x, y)
        
        # 计算每个点的电场强度
        Ex = np.zeros_like(X)
        Ey = np.zeros_like(Y)
        
        for (start, end), strength in zip(self.segments, self.field_strengths):
            dx = end[0] - start[0]
            dy = end[1] - start[1]
            length = np.sqrt(dx**2 + dy**2)
            direction = np.array([dx/length, dy/length])
            
            # 使用向量化操作计算场强
            for i in range(n_points):
                points = np.column_stack((X[i,:], Y[i,:]))
                for j, point in enumerate(points):
                    r = point - np.array(start)
                    r_mag = np.linalg.norm(r)
                    if r_mag > 0:
                        field = direction * np.abs(strength) / (r_mag)
                        Ex[i,j] += field[0]
                        Ey[i,j] += field[1]
        
        # 计算场强大小
        E_magnitude = np.sqrt(Ex**2 + Ey**2)
        
        # 使用对数标度绘制热图
        im = ax.pcolormesh(X, Y, E_magnitude, 
                          norm=colors.LogNorm(vmin=max(1e-10, E_magnitude.min()), 
                                            vmax=E_magnitude.max()),
                          cmap='hot')
        
        # 绘制边界线段
        segments = np.array(self.segments)
        lc = LineCollection(segments, colors='white', linewidths=1, alpha=0.5)
        ax.add_collection(lc)
        
        # 添加颜色条
        plt.colorbar(im, label='电场强度 |E|')
        
        ax.set_aspect('equal')
        ax.set_xlim(x_min, x_max)
        ax.set_ylim(y_min, y_max)
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_title('电场强度分布')
        
        plt.show()

    def visualize_all(self, n_points=50):
        """同时显示电场线和电场强度分布"""
        # 创建一个包含两个子图的图形
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 8))
        
        # 第一个子图：电场线
        segments = np.array(self.segments)
        strengths = np.abs(self.field_strengths)
        
        norm = colors.LogNorm(vmin=max(1e-10, min(strengths)), vmax=max(strengths))
        lc = LineCollection(segments, cmap='viridis', norm=norm)
        lc.set_array(strengths)
        
        ax1.add_collection(lc)
        plt.colorbar(lc, ax=ax1, label='场强大小 |E|')
        
        # 计算和绘制电场箭头
        x_min, y_min = self.domain[0]
        x_max, y_max = self.domain[1]
        margin = 0.1 * max(x_max - x_min, y_max - y_min)
        
        x = np.linspace(x_min-margin, x_max+margin, n_points)
        y = np.linspace(y_min-margin, y_max+margin, n_points)
        X, Y = np.meshgrid(x, y)
        
        Ex = np.zeros_like(X)
        Ey = np.zeros_like(Y)
        
        # 计算电场
        for (start, end), strength in zip(self.segments, self.field_strengths):
            dx = end[0] - start[0]
            dy = end[1] - start[1]
            length = np.sqrt(dx**2 + dy**2)
            direction = np.array([dx/length, dy/length])
            
            for i in range(n_points):
                points = np.column_stack((X[i,:], Y[i,:]))
                for j, point in enumerate(points):
                    r = point - np.array(start)
                    r_mag = np.linalg.norm(r)
                    if r_mag > 0:
                        field = direction * np.abs(strength) / (r_mag)
                        Ex[i,j] += field[0]
                        Ey[i,j] += field[1]
        
        # 绘制电场箭头
        skip = (slice(None, None, 3), slice(None, None, 3))
        magnitude = np.sqrt(Ex**2 + Ey**2)
        ax1.quiver(X[skip], Y[skip], Ex[skip]/magnitude[skip], Ey[skip]/magnitude[skip],
                  magnitude[skip], cmap='viridis', scale=30)
        
        ax1.set_aspect('equal')
        ax1.set_xlim(x_min-margin, x_max+margin)
        ax1.set_ylim(y_min-margin, y_max+margin)
        ax1.set_xlabel('X')
        ax1.set_ylabel('Y')
        ax1.set_title('电场线分布')
        
        # 第二个子图：电场强度热图
        im = ax2.pcolormesh(X, Y, magnitude,
                           norm=colors.LogNorm(vmin=max(1e-10, magnitude.min()),
                                             vmax=magnitude.max()),
                           cmap='hot')
        
        # 在热图上绘制边界线段
        lc2 = LineCollection(segments, colors='white', linewidths=1, alpha=0.5)
        ax2.add_collection(lc2)
        
        plt.colorbar(im, ax=ax2, label='电场强度 |E|')
        
        ax2.set_aspect('equal')
        ax2.set_xlim(x_min-margin, x_max+margin)
        ax2.set_ylim(y_min-margin, y_max+margin)
        ax2.set_xlabel('X')
        ax2.set_ylabel('Y')
        ax2.set_title('电场强度分布')
        
        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    visualizer = FieldVisualizer()
    visualizer.load_segments("a.txt")
    # 显示所有可视化结果
    visualizer.visualize_all()
    # 或者单独显示电场强度分布
    # visualizer.plot_field_strength() 