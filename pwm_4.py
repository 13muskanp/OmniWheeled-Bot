import math

import numpy as np

from numpy.linalg import inv

a1=math.radians(45)

a2=math.radians(135)

a3=math.radians(225)

a4=math.radians(315)

x1=math.cos(a1)

x2=math.cos(a2)

x3=math.cos(a3)

x4=math.cos(a4)

y1=math.sin(a1)

y2=math.sin(a2)

y3=math.sin(a3)

y4=math.sin(a4)

x=float(input("Enter x:"))

y=float(input("Enter y:"))

w=float(input("Enter w:"))

I=np.array([[x], [y], [w]])

X=np.array([[-y1, x1, 1], [-y2, x2, 1], [-y3, x3, 1], [-y4, x4, 1]])

S=np.matmul(X, I)/4

s1=S[0]

s2=S[1]

s3=S[2]

s4=S[3]

print "S1, S2, S3, S4:", s1, s2, s3, s4
