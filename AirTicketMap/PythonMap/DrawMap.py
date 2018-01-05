
from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
import pandas as pd
import numpy as np
import sys

posi=pd.read_excel("./2018Cities-CHINA.xlsx") #读取中国城市数据
short=np.array(posi["short"][0:130])					  #获取城市名称缩写
lat = np.array(posi["lat"][0:130])                        # 获取纬度值
lon = np.array(posi["lon"][0:130])                        # 获取经度值

map = Basemap(projection='merc', 
	              lat_0=42.5, lon_0=120,
	              llcrnrlon=70.33,llcrnrlat=3.01,urcrnrlon=138.16,urcrnrlat=56.123)   #地图初始化

map.readshapefile("./CHN_adm_shp/CHN_adm1",'states',drawbounds=True)
#画省界线
posj=pd.read_excel("./2019Cities-CHINA.xlsx") #读取中国城市数据
short1=np.array(posj["short1"][0:100])					  #获取起飞城市名称缩写
short2=np.array(posj["short2"][0:100])					  #获取起飞城市名称缩写
def draww(Tt_City,Ll_City):
	global llx
	global lly
	for i in range(99):
		if short[i]==Tt_City:
			tx,ty =map(lon[i],lat[i]) 
			ttx,tty=lon[i],lat[i]
			map.scatter(tx,ty,s=50,marker='.',facecolors='r',edgecolors='r') # 绘制城市i
		elif short[i]==Ll_City:
			lx,ly =map(lon[i],lat[i]) 
			llx,lly=lon[i],lat[i]
			map.scatter(lx,ly,s=50,marker='*',facecolors='r',edgecolors='r') # 绘制城市i
	#map.drawgreatcircle(116.4, 39.9, 104.1, 30.65,linewidth=1,color='r')
	map.drawgreatcircle(ttx,tty,llx,lly,linewidth=1,color='r')

def testMap(argv1=0, argv2=0, argv3=0):
	for j in range(99):
		T_City=short1[j]
		L_City=short2[j]
		draww(T_City,L_City)
	map.drawcoastlines()
	plt.show()
	
if __name__ == '__main__':
	if len(sys.argv) > 1:
        #testMap(sys.argv[1], sys.argv[2], sys.argv[3])
		for i in range(len(sys.argv)):
			print(sys.argv[i])
	else:
		testMap()

#map.etopo() # 绘制地形图，浮雕样式




