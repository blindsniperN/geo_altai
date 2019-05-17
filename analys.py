import numpy as np
import cv2 as cv

img = cv.imread("inp.jpg")
img2 = cv.imread("imp.jpg")
#cv.imshow("res", img)
m = img.shape[0] // 64
n = img.shape[1] // 64
dat = np.array([[0.0]*n]*m)
vod = np.array([[0.0]*n]*m)
hei = np.array([[0.0]*n]*m)
mod = cv.GaussianBlur(img, (7, 7), 0)
lakes = cv.inRange(mod, (235, 235, 175), (255, 255, 255))
kernel = np.ones((13,13),np.uint8)
lakes = cv.dilate(lakes, kernel, iterations=1)
cont, hier = cv.findContours(lakes, 1, 2)
#coz = [i.cen for i in cont]
for y in range(m):
    for x in range(n):
        dat[y, x] = img2[y * 64:(y + 1) * 64, x * 64:(x + 1) * 64, 2].mean()
        cx = x * 64 + 32
        cy = y * 64 + 32
        vod[y, x] = lakes[y * 64:(y + 1) * 64, x * 64:(x + 1) * 64].mean()
        hei[y, x] = img[y * 64:(y + 1) * 64, x * 64:(x + 1) * 64, 2].mean()
print(vod)
#lakes = cv.GaussianBlur(lakes, (5, 5), 0)
cont, hier = cv.findContours(lakes, 1, 2)
cv.imshow("lakes", lakes)
for i in cont:
    rect = cv.minAreaRect(i)
    box = cv.boxPoints(rect)
    box = np.int0(box)
    cv.drawContours(img,[box],0,(0,0,255),2)
cv.imshow("lakes2", img)

with open("y.txt", mode='w') as outy:
    for y in range(m):
        for x in range(n):
            outy.write(str(dat[y, x]) + '\n')

with open("x.txt", mode='w') as outx:
    outx.write(str(m * n) + '\n')
    outx.write(str(2) + '\n')
    for y in range(m):
        for x in range(n):
            outx.write(str(vod[y, x]) + ' ' + str(hei[y, x]) + '\n')

with open("a.txt", mode='w') as outa:
    outa.write(str(m * n) + '\n')
    for y in range(m):
        for x in range(n):
            outa.write(str(dat[y, x]) + ' ' + str(vod[y, x]) + ' ' + str(hei[y, x]) + '\n')

cv.waitKey()
cv.destroyAllWindows()


















































































