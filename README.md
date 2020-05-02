# Cproject-2020xjc

#### 介绍
这里是2020 程序设计专题xjc班第五组的project



开始使用   用appcode替换其中的的appcode  在解决方案--属性--vc++设置中除了加入libgraphics，再把appcode加入其中即可





Demo.c中添加

~~~
#elif Demo_ID==13
#include "MyMain.c"
将Demoid改为13即可
~~~



注意：该库使用GB2312的接口/api，请创建文件格式改为GBK/GB2312（汉字两个字节），如果使用UTF-8会导致严重问题



命名方法上：统一采用**大驼峰法**，将每个单词首字母大写，避免出现大小驼峰命名冲突的情况





简单介绍：

目前主要文件形式为：

- MyData.h中存放所有全局变量，每个文件都将其include
- PreWork.c进行准备工作，包括寻找csv文件，定义颜色，进行数据展示的计算（横纵坐标）
- MyDraw.c放各种画图函数
- MyDrawTable.c放三次线性插值算法和parspl插值算法
- Readcsv.c放置读取csv文件函数



### 已经实现：

打开文件   记得选demo1.csv

画出简单曲线

左侧勾选





### TODO



数据！！！！

数据！！！！



readcsv中

- 暂时由于读取算法受限未实现根据行数自动malloc，改进方向为根据行数自动malloc出内存

- 结构体命名问题太大，stu为随手打的，尽快改善
- ChooseData原意为是否选择展示某一列数据，例如展示是否展示湖北/全国疫情数据，但是命名问题太大





Prework中

- definecolor不够多，可以到https://coolors.co/  上直接调色，cxzの审美受限无法调的够好
- calculate 关键问题为计算显示位置  还有些适配小问题，稍微改进
- Findcsv尽量别动，用的direct.h的api，寻找当前目录下的csv文件







MyDrawTable 画图表算法

- 不好动，这个是lib库的问题，表现是锯齿感太强   解决办法想了好久了，呼~
- parspl这个是备用的 ，也是找了很久



MyDraw 画图

- 封装度不够高，代码重复度太高 应进行函数封装
- 还有好多细节  比如数据多的话翻页，显示位置限制未实现



MyData

- 命名  
- 命名
- 命名



整体功能**TODO**：

- 选中高亮

- 柱状图

- 放大放小

- 疫情预测

- 欢迎界面

- 用户手册

- 播放音乐就算了  挺严肃的

- 修改、写入数据

  

额外功能：

- 整个画Table部分拖拽移动，但是感觉不好

- 自动化检测？难道用pyautogui？不懂

- 在想了

  



