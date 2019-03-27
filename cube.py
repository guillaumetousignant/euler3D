import numpy as np

ni = 3
nj = 3
nk = 3

nii = 4
njj = 4
nkk = 4

dx = 1.0 / float(ni)
dy = 1.0 / float(nj)
dz = 1.0 / float(nk)

nNodes = (ni+1) * (nj+1) * (nk+1)
X = np.zeros(((nk+1),(nj+1),(ni+1)))
Y = np.zeros(((nk+1),(nj+1),(ni+1)))
Z = np.zeros(((nk+1),(nj+1),(ni+1)))

z = -dz
for k in range(nk+1):
    z += dz
    y = -dy
    for j in range(nj+1):
        y += dy
        x = -dx
        for i in range(ni+1):
            x += dx
            X[k,j,i] = x
            Y[k,j,i] = y
            Z[k,j,i] = z

fid = open("cube.su2","w")

fid.write("NDIME= 3\n")
fid.write("NELEM= %d\n" % (nk*nj*ni))

for k in range(nk):
    for j in range(nj):
        for i in range(ni):
            n1 = k * njj * nii + j       * nii + i
            n2 = k * njj * nii + j       * nii + i + 1
            n3 = k * njj * nii + (j + 1) * nii + i + 1
            n4 = k * njj * nii + (j + 1) * nii + i
            n5 = (k + 1) * njj * nii + j       * nii + i
            n6 = (k + 1) * njj * nii + j       * nii + i + 1
            n7 = (k + 1) * njj * nii + (j + 1) * nii + i + 1
            n8 = (k + 1) * njj * nii + (j + 1) * nii + i
            fid.write("12 %d %d %d %d %d %d %d %d\n" % (n1,n2,n3,n4,n5,n6,n7,n8))

fid.write("NPOIN= %d\n" % (nNodes))
for k in range(nk+1):
    for j in range(nj+1):
        for i in range(ni+1):
            fid.write("%.12lf %.12lf %.12lf\n" % (X[k,j,i],Y[k,j,i],Z[k,j,i]))

fid.write("NMARK= %d\n" % (2))
fid.write("MARKER_TAG= AIRFOIL\n")
fid.write("MARKER_ELEMS= %d\n" % (ni * nj))

j = 0
for k in range(nk):
    for i in range(ni):
        n1 = k * njj * nii + j       * nii + i
        n2 = k * njj * nii + j       * nii + i + 1
        n3 = (k + 1) * njj * nii + j       * nii + i
        n4 = (k + 1) * njj * nii + j       * nii + i + 1
        fid.write("4 %d %d %d %d\n" % (n1,n2,n3,n4))

fid.write("MARKER_TAG=WALL\n")
fid.write("MARKER_ELEMS= %d\n" % (ni * nj))
j = nj
for k in range(nk):
    for i in range(ni):
        n1 = k * njj * nii + j       * nii + i
        n2 = k * njj * nii + j       * nii + i + 1
        n3 = (k + 1) * njj * nii + j       * nii + i
        n4 = (k + 1) * njj * nii + j       * nii + i + 1
        fid.write("4 %d %d %d %d\n" % (n1,n2,n3,n4))

fid.close()
