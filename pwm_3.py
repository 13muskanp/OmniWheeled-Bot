import math

import numpy as np

from numpy.linalg import inv

a1=math.radians(120)

a2=math.radians(240)

a3=math.radians(360)

x1=math.cos(a1)

x2=math.cos(a2)

x3=math.cos(a3)

y1=math.sin(a1)

y2=math.sin(a2)

y3=math.sin(a3)

x=int(input("Enter x:"))

y=int(input("Enter y:"))

w=int(input("Enter w:"))

I=np.array([[x], [y], [w]])

X=np.array([[x1, x2, x3], [y1, y2, y3], [1, 1, 1]])

invx=inv(X)

S=np.matmul(invx, I)

s1=S[0]

s2=S[1]

s3=S[2]

print "S1, S2, S3:", s1, s2, s3
