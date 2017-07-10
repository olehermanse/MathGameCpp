from PIL import Image
import numpy as np
import os,sys
from scipy.misc import imresize

def img_open(path):
    imgPIL = Image.open(path)
    return np.array(imgPIL)

def resize(image, dirpath, dim, mult):
    total = dim * mult
    image = imresize(image, (total,total), 'nearest')
    name = dirpath + "icon_{}x{}".format(dim,dim)
    if mult != 1:
        name += "@{}x".format(mult)
    name += ".png"
    image = Image.fromarray(np.uint8(image))
    print(name)
    image.save(name)

img = img_open("res/icon.png")

sizes = [16,20,29,30,32,58,64,80,87,128,256,512]

os.makedirs("App.iconset")

for size in sizes:
    for mult in [1,2,3]:
        resize(img, "App.iconset/", size, mult)
