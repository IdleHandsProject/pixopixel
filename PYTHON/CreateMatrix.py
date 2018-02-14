import sys
from PIL import Image


img = sys.argv[1]
size = 16, 16

im = Image.open(img)
smallim = im.resize(size, Image.ANTIALIAS);
smallim = smallim.convert('RGB') 
pixels = list(smallim.getdata())

imgstr = str(pixels).strip('[]')
imgstr = imgstr.replace('(','{')
imgstr = imgstr.replace(')','}')

f = open(img + '.h', 'w')
f.write('int imageArray[256][3] = {' + imgstr + '};')
f.close()
