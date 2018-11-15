#To work on files
import os
#To work on images
from PIL import Image 

#PNG have to be located in the folder 'rooms'
for filename in enumerate(os.listdir("rooms_png")):
    name, ext = os.path.splitext(filename[1])
    room_png = Image.open("rooms_png/"+name+ext,"r")
    pix = room_png.load()
    column, line = room_png.size
    mobs = ""
    spawn_coord = []
    correspondance_array = [[] for b in range(line)]

    for i in range(line):
        for j in range(column):
            color = pix[j,i]
            if color[:3] == (0,255,0): #Green stands for the floor
                correspondance_array[i].append('F')
            elif color[:3] == (0,200,0): #Darkest green stands for path
                correspondance_array[i].append('P')
            elif color[:3] == (255,220,0): #Yellow stands for shop
                correspondance_array[i].append('S')
            elif color[:3] == (0,255,255): #Cyan stands for house
                correspondance_array[i].append('M')
            elif color[:3] == (0,127,127): #Dark Cyan stands for gates
                correspondance_array[i].append('G')
            elif color[:3] == (0,0,0): #Black stands for the wall
                correspondance_array[i].append('W')
            elif color[:3] == (211,211,211): #Gray stands for block
                correspondance_array[i].append('B')
            elif color[:3] == (0,0,255): #Blue stands for the juice
                correspondance_array[i].append('J')
            elif color[:3] == (150,75,0): #Brown stands for the seed (switch)
                correspondance_array[i].append('W')
            elif color[:3] == (100,50,0): #Darkest brown stands for hole
                correspondance_array[i].append('H')
            elif color[:3] == (255,0,0): #Red stands for monster A
                correspondance_array[i].append('H')
                spawn_coord.append(("flying",i,j))
                mobs+='A'
            elif color[:3] == (180,0,255): #Red stands for monster B
                correspondance_array[i].append('F')
                spawn_coord.append(("terrain",i,j))
                mobs+='B'
            else:
                print("Error at "+str(i)+" "+str(j))
    
    room_png.close()

    #Name, size, kind of mobs allowed to spawn
    map_file = open("rooms_out/"+name+".loli","w") #Large Output Last Idea
    map_file.write(name+",\n")
    map_file.write("COLUMNS="+str(column)+",LINES="+str(line)+",\n")
    map_file.write("SET_MOB="+mobs+",\n")

    #Position allowed for mobs to spawn
    for coord in spawn_coord:
        map_file.write("SPAWN "+str(coord[0])+": "+str(coord[1])+"-"+str(coord[2])+"\n")

    #Tile map
    for i in range(line):
        for j in range(column):
            map_file.write(correspondance_array[i][j]+",")
        map_file.write("\n")
    print(name+": done.\n")
    map_file.close()
print("Done.")