import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.art3d as art3d
from islplot.support import *
from islpy import *


def plot_points(ax, points):
    xs = list([point[0] for point in points])
    ys = list([point[1] for point in points])
    zs = list([point[2] for point in points])
    ax.scatter(xs, ys, zs, c='#4c4c4c', s=8.0)


def plot_set_3d_shape(ax, vertices, faces, color):
    for face in faces:
        vertices_in_order = []
        for p in face:
            vertices_in_order.append(vertices[p])
        tri = art3d.Poly3DCollection([vertices_in_order])
        tri.set_facecolor(color)
        tri.set_alpha(0.5)
        tri.set_edgecolor('k')
        ax.add_collection3d(tri)


def plot_3d_set(set_data):
    plot_3d_sets([set_data])


def plot_3d_sets(sets_data):
    try:
        fig = plt.figure()
        ax = fig.gca(projection='3d')
        face_colors = ['#468ad4', '#FF8000']
        for i, data in enumerate(sets_data):
            vertices, faces = get_vertices_and_faces(data)
            plot_points(ax, vertices)
            plot_set_3d_shape(ax, vertices, faces, face_colors[i % 2])

        ax = fig.gca(projection='3d')
        ax.set_xlabel('$i$')
        ax.set_ylabel('$j$')
        ax.set_zlabel('$k$')
        ax.view_init(20, -120)
    except:
        print('Error while trying to plot 3D sets')


def split_affine(s, aff_str):
    if not aff_str:
        return [s]
    cut = BasicSet('{{[i,j,k] : {}}}'.format(aff_str))
    # build two pieces from the split
    i = s.intersect(cut)
    diff = s - i
    p1, p2 = diff.get_basic_sets()
    p1 = p1.union(i).convex_hull()
    return [p1, p2]


def split_vertices(s, *vertices):
    num_indices = s.get_space().dim(dim_type.out)
    patch = Set('{{{}}}'.format('; '.join(vertices))).convex_hull()
    eq_constraints = [c for c in patch.get_constraints() if c.is_equality()]
    assert len(eq_constraints) == 1
    eqc = eq_constraints[0]
    cut = BasicSet.universe(s.get_space()).add_constraint(eqc)
    i = s.intersect(cut)
    diff = s - i
    p1, p2 = diff.get_basic_sets()
    p1 = p1.union(i).convex_hull()
    return [p1, p2]
