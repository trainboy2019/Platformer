from PIL import Image,ImageDraw
import os
import json
#http://www.objgen.com/json/models/GViA

#http://www.objgen.com/json/models/sCSiQ
def rgb2hex(r, g, b):
    return '#{:02x}{:02x}{:02x}'.format(r, g, b)
levelRaw=[]
level1=[]
level1Data=[]
level1Color=[]
pixels={}
pixelist=[]
appixels={}
level=Image.open(os.path.join("data","level1.png"))
width,height=level.size
final=Image.new("RGB",(400,240),(0,0,0))
for y in range(height):
    yData=[]
    for x in range(width):
        pasteX=x*8
        pasteY=y*8
        pasteX2=x*8+8
        pasteY2=y*8+8
        pixel=rgb2hex(level.getpixel((x,y))[0],level.getpixel((x,y))[1],level.getpixel((x,y))[2])
        if pixel not in pixels:
            tmpPxl={str(len(pixels)):str(pixel)}
            pixels[pixel]=len(pixels)
            level1Color.append(tmpPxl)
            pixelist.append(tmpPxl)
        yDict={str(x):pixels[pixel]}
        yData.append(yDict)
        final.paste(pixel,(pasteX,pasteY,pasteX2,pasteY2))
    level1Data.append((str(y), yData[:]))
    yData=[]

level1.append(level1Data)
level1.append(level1Color)
#final.save("test2.png","PNG")
##for item in level1:
##    print(item)
##    print()
with open("level1.json","r+") as f:
    f.truncate()
    f.write(json.dumps(level1))
