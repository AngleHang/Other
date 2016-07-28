贪吃蛇
========

贪吃蛇游戏设计与实现
--------
* 目标：做一个贪吃蛇游戏。
* 衍生目标：
  * 可以双人游戏
  * 地图多样化
* 终极目标：
  * 可以联机游戏！！（向网络世界进军）
  * 用图片代替字符（向图形界面前进）
* 要求：
  * 蛇移动
  * 食物随机出现（不能出现在蛇的身体上）
  * 随时可以暂停且可以恢复
  * 蛇不能撞墙和吃自己的身体
  * 吃食物可以变长
  * 移动速度随时间的增长而加快
  * 可以设置地图大小和起始速度（有限制）
* 想法：
  * 利用双向链表来表示蛇的身体
  * 头节点即使蛇头，尾节点即使蛇尾
  * 利用队列的原理 添头去尾来做到蛇移动
  * 利用rand函数来随机食物出现的地方且判断是否可以放置该食物
  * 蛇不能向反方向移动（假如现在蛇是向上那么就不能向下移动）
  * 利用Sleep函数来控制蛇的速度

###程序中定义的宏：
|宏名|含义
|:--:|:--:
|`SIMPLE_MAP_X`    |   简单难度的地图X长度
|`SIMPLE_ MAP_Y`   |  简单难度的地图Y长度
|`ORDINARY_MAP_X`  |普通难度的地图X长度
|`ORDINARY_MAP_Y`  |普通难度的地图Y长度
|`DIFFICULT_MAP_X` |  困难难度的地图X长度
|`DIFFICULT_MAP_Y` |  困难难度的地图Y长度
|`INIT_LENGTH`     |   蛇的初始化长度
|`SIMPLE_SPEED`    |   简单难度的蛇初始化速度
|`ORDINARY_ SPEED` |  普通难度的蛇初始化速度
|`DIFFICULT_SPEED` |   困难难度的蛇初始化速度
|`WALL`            |    墙
|`SNAKE_BODY`      |  蛇体

###程序中的结构体：

* 蛇的身体节点的结构体：<br>
x,y 表示坐标 <br>
up,next表示上/下一个蛇身

```c
Typedef struct snake_body{
    Int x;
    Int y;
    struct snake_body up;
    struct snake_body next;
} Snake_body;
```

* 食物的结构体：<br>
x,y 表示坐标

```c
typedef struct food {
    int x;
    int y;
} Food; 
```

* 坐标类型：（与食物的结构体相同）

```c
typedef Food Coordinate;
```

* 蛇整体结构体：<br>
  head是蛇头
  tail是蛇尾
  
```c
typedef struct head_ tail {
    Snake_body *head;
    Snake_body *tail;
} Head_Tail;
```

###所需功能与实现的函数：

* 定位光标函数
利用windows API函数`GetStdHandle`函数和`SetConsoleCursorPosition`函数来做到光标定位
`GetStdHandle`函数的作用是获取标准输出的句柄，返回一个HANDLE类型的值  （此操作将在初始化函数中完成，避免重复获取）
`SetConsoleCursorPosition`函数的参数分别是获得到的句柄与`COORD`类型结构体
`COORD`类型结构体包含了x,y来表示坐标

使用示例：

```c
#include <windows.h>
int main()
{
    HANDLE hout;
    COORD coord;
    coord.X=30;
    coord.Y=10;
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout,coord); 
    return 0;
}
```

* 隐藏光标函数
利用Windows API函数
    `GetStdHandle`函数和`SetConsoleCursorInfo`函数来做到隐藏光标
`GetStdHandle`上面说过是用来获取标准输出的句柄的函数
`SetConsoleCursorInfo`函数的参数分别是标准输出的句柄以及`CONSOLE_CURSOR_INFO`类型的地址
`CONSOLE_CURSOR_INFO`类型的意思是光标是打开还是关闭，可以初始化为：

```c
CONSOLE_CURSOR_INFO cursor_info = {1,0};
```
然后
```c
SetConsoleCursorInfo(hout, cursor_info);
```

就可以做到隐藏光标了

###蛇移动思路：

利用添头去尾来做到蛇的移动，将蛇的身体做成双向链表，在移动时把最后一个节点去掉并且在头结点前面新建一个头结点，看起来就像蛇移动了

__[回到顶部](#贪吃蛇)__
###截图：
![](https://github.com/TianLanhe/Others/raw/master/tanchishe/screenshot.png)
![](https://github.com/TianLanhe/Others/raw/master/tanchishe/screenshot2.png)
![](https://github.com/TianLanhe/Others/raw/master/tanchishe/screenshot3.png)


