from PIL import Image,ImageDraw
import os
import json
#http://www.objgen.com/json/models/GViA

#http://www.objgen.com/json/models/sCSiQ
levelRaw=[]
level1=[]
level1Data=[]
level1Color=[]
pixels={}
pixelist=[]
appixels={}
force=True
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
        pixel=level.getpixel((x,y))
        r,g,b=level.getpixel((x,y))
        if pixel not in pixels:
            pixlist=[]
            pixlistAdd={}
            color=[]
            rDict={}
            gDict={}
            bDict={}
            solidT={}
            solidB={}
            solidL={}
            solidR={}
            water={}
            gravity={}
            goal={}
            death={}
            bounce={}
            toggles={}
            toggledby={}
            isPlayer={}
            solidT["solidTop"]=False
            solidB["solidBottom"]=False
            solidL["solidLeft"]=False
            solidR["solidRight"]=False
            water["isWater"]=False
            gravity["gravity"]=False
            goal["goal"]=False
            death["death"]=False
            bounce["bounce"]=False
            toggles["toggles"]=-1
            toggledby["toggledBy"]=-1
            isPlayer["isPlayer"]=False
            rDict["r"]=r
            gDict["g"]=g
            bDict["b"]=b
            tmpPxl={str(len(pixels)):str(pixel)}
            pixels[pixel]=len(pixels)
            level1Color.append(tmpPxl)
            color.append(rDict)
            color.append(gDict)
            color.append(bDict)
            pixlist.append(color)
            pixlist.append(solidT)
            pixlist.append(solidB)
            pixlist.append(solidL)
            pixlist.append(solidR)
            pixlist.append(water)
            pixlist.append(gravity)
            pixlist.append(death)
            pixlist.append(goal)
            pixlist.append(bounce)
            pixlist.append(toggles)
            pixlist.append(toggledby)
            pixlist.append(isPlayer)
            pixlistAdd[str(len(pixels)-1)]=pixlist
            pixelist.append(pixlistAdd)
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
if force==True:
    with open("level1blocks.json","r+") as f:
        f.truncate()
        f.write(json.dumps(pixelist))
