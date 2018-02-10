import json
with open('level1blocks.json','r+') as f:
    array=json.loads(f.read())
for i in range(len(array)):
    print(array[str(i)])
