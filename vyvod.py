import numpy as np
import cv2 as cv

img = cv.imread("inp.jpg")

msk = cv.imread("inp.jpg")
print(msk.shape)
m = img.shape[0] // 64
n = img.shape[1] // 64
with open('y.txt', mode='r') as inpy:
    y = np.array([float(i.strip()) for i in inpy])
with open('w.txt', mode='r') as inpw:
    w = np.array([float(i.strip()) for i in inpw])
with open('x.txt', mode='r') as inpx:
    x = np.zeros((int(inpx.readline().strip()), int(inpx.readline().strip())+ 1))
    for i in range(x.shape[0]):
        x[i] = [float(j) for j in inpx.readline().strip().split()] + [1.0]
d = x.dot(w)
d -= y
print(d)

for y in range(m):
    for x in range(n):
        msk[y*64:(y+1)*64, x*64:(x+1)*64] = [0, 100, 200 + d[y*n + x]]
dst = cv.addWeighted(img,0.5,msk,0.5,0)
cv.imshow("res", dst)
cv.imwrite("result.jpg", dst)

cv.waitKey()
cv.destroyAllWindows()
