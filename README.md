# 作业历程(早就懒得写了)



## 第一个星期

---

### 1.定义结构体 chessboard(棋盘信息)

```c
typedef struct
{
    int  flag;  
    int  nearbyMineNum;
    int  tagOrNot;
}Chessboard;
```

| key           |                 instruction                 |
| ------------- | :-----------------------------------------: |
| flag          |          是否埋有雷，是为1，否为0           |
| nearbyMineNum | 周边一圈的雷数(默认为0，生成棋盘后自动计算) |
| tagOrNot      |      在游戏中是否被标记，是为1，否为0       |

### 2.构建函数 createChessboard

```c
Chessboard **createChessboard(int x, int y, int MineNum);
```

> 二维动态数组的生成方法
>
> 为什么要选择生成动态数组？
>
> 用户可以选择自定义棋盘的大小，那数组的大小自然就要改变，原本的定义方法生成的是静态数组，不能改变大小，很捞
>
> 而动态数组可以通过自己分配内存释放内存来改变数组的大小（好耶）
>
> ```c
> #include<stdio.h>
> int **returnNum()//生成一个5*6的二维整形数组
> {
> int **a,i,j;
> //生成a[5]数组，其中存放指针
> a = (int**)malloc(5*sizeof(int*));//申请内存，长度为5个整形指针
> for(i=0;i<5;++i)
> {
> //在a[i]中存放长度为6的整形数组
>   a[i] = (int*)malloc(6*sizeof(int));//申请内存，长度为6个整形
> for(j=0;j<5;++j)
>  {
>   //得到了a[5][6]的二维数组
>   a[i][j]=i;
>    }
> }
> return a;
> } 
> int main()
> {
> //一维数组用一级指针，二维数组就要用二级指针了捏
> int **cpy=returnNum();
> int i,j;
> for(i=0;i<5;++i)
> {
> for(j=0;j<5;++j)
>  {
>    printf("%d ", cpy[i][j]);
>   }
>  printf("\n");
>  free(cpy[i]);
> }
> //别忘了一个二维数组确定不会再被使用到的时候要先释放掉
> free(cpy);
> return 0;
> }
> ```

函数功能为返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）

| key     |      instruction       |
| :------ | :--------------------: |
| x       |     二维数组的宽度     |
| y       |     二维数组的长度     |
| MineNum | 二维数组需要埋下的雷数 |

| Value                        | 说明                                                         |
| ---------------------------- | ------------------------------------------------------------ |
| NULL，printf("...")          | 棋盘大小或者埋雷个数不合法（x < 6 \|\|y < 10 \|\|MineNum > x * y - 10 \|\|MineNum < 10） |
| struct Chessboard **myCBList | 返回一个已经随机埋好雷的结构体chessboard的二维数组           |

### 3.构建函数 makeChessboard

```c
Chessboard **makeChessboard(Chessboard **myCBList, int MineNum, int cx, int cy);
```

函数功能为返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)

| key      |               instruction               |
| -------- | :-------------------------------------: |
| myCBList |       传入未初始化的棋盘(已埋雷)        |
| MineNum  |                埋雷总数                 |
| cx       | 传入数组的x长度(a\[5\]\[6\]的x为5,y为6) |
| cy       |             传入数组的y长度             |

| Value      | 说明                                  |
| ---------- | ------------------------------------- |
| **myCBList | 返回计算nearbyMineNum后的棋盘         |
| NULL       | MineNum的值与传入的棋盘中已埋雷数不符 |

## 第二个星期

---

### 1.修改结构体 chessboard(棋盘信息)

```c
typedef struct
{
    int  flag;  
    int  nearbyMineNum;
    int  tagOrNot;
    int  drawOrNot;
}Chessboard;
```

> 在第一个星期并没有考虑到用户实际操作时需要的各种情况的记录, 为了让结构体能够更好的记录当前棋盘的状况, 我们决定在函数中加入一个新的元素:drawOrNot, 来记录该点是否被玩家翻开。

| key           |                 instruction                 |
| ------------- | :-----------------------------------------: |
| flag          |          是否埋有雷, 是为1, 否为0           |
| nearbyMineNum | 周边一圈的雷数(默认为0, 生成棋盘后自动计算) |
| tagOrNot      |      在游戏中是否被标记, 是为1, 否为0       |
| drawOrNot     |        是非被玩家翻开, 是为1, 否为0         |

### 2.构建函数 drawOneChess

```c
Chessboard **drawOneChess(Chessboard **myCBList, int cx, int cy, int x, int y);
```

函数功能为翻开指定坐标的格子，并自动翻开根据规则同时翻开的格子，如果该格子埋有雷，直接返回NULL，如果指定的格子已被翻开，则返回原棋盘并输出错误。

>#### 扫雷翻牌规则介绍：
>
>点击一个区域的时候，有三种情况：
>
>1. 周围8个格子有雷，也就是这个区域上应该有数字标明，只翻一个
>2. 中卫8个格子没有雷，该区域没有数字，为空地，向外翻开一个由数字块围成的区域(只有边缘是数字，里面全是空地)
>3. 该区域为雷，game over~

| key      |               instruction               |
| -------- | :-------------------------------------: |
| myCBList |           传入已初始化的棋盘            |
| cx       | 传入数组的x长度(a\[5\]\[6\]的x为5,y为6) |
| cy       |             传入数组的y长度             |
| ｘ       |         需要翻开的格子的ｘ坐标          |
| ｙ       |         需要翻开的格子的ｙ坐标          |

| Value                     | 说明                               |
| ------------------------- | ---------------------------------- |
| **myCBList                | 返回翻开格子后的棋盘               |
| NULL                      | 翻开的格子中埋有雷（忽略错误处理） |
| **myCBList，printf("...") | 输出“该格子已被翻开”并返回原棋盘   |

### 3.构建函数 markOneChess

```
Chessboard **markOneChess(Chessboard **myCBList, int cx, int cy, int x, int y);
```

函数功能为标记指定坐标的格子为红旗，如果此时所有雷都已被标记且标记的格子内全部含有雷，直接返回NULL，如果指定的格子已被标记，则返回原棋盘并输出错误。

>#### 扫雷标记规则介绍：
>
>扫雷的规则就是在避开雷的前提下，标注出所有的雷。
>
>扫雷游戏中红旗用于标记已明确的地雷，标志了红旗，就不能按了，要取消才可以。

| key      |               instruction               |
| -------- | :-------------------------------------: |
| myCBList |           传入已初始化的棋盘            |
| cx       | 传入数组的x长度(a\[5\]\[6\]的x为5,y为6) |
| cy       |             传入数组的y长度             |
| ｘ       |         需要标记的格子的ｘ坐标          |
| ｙ       |         需要标记的格子的ｙ坐标          |

| Value                     | 说明                                                     |
| ------------------------- | -------------------------------------------------------- |
| **myCBList                | 返回翻开格子后的棋盘                                     |
| NULL                      | 所有雷都已被标记且标记的格子内全部含有雷（忽略错误处理） |
| **myCBList，printf("...") | 输出“该格子已被标记”并返回原棋盘                         |

## 第三个星期

---

### 懒得写了，就这样吧，反正没什么技术含量。

## 第十二个星期

---

有生之年还能想起来这个文档……

### 1.  打分系统

初始分数：1000分
最高分数：上不封顶（通关者一般在4000分以上，但鲜有5000分以上 ）
最低分数：0分（不会出现负分，扣分至0分为止，且扣分效应不累积）
加分：1、每点开一个无雷区加50分；
2、游戏通关额外加1000分；
扣分：
1、游戏期间每消耗1秒钟扣1分。

### 2.  数据库读写

#### 棋盘自定义

输入：



一个结构体

```c
typedef struct
{
    int   line; // 长度  
    int   column; // 宽度
    char  chessboard[20001]; // 字符串
}Chessboard;
```

对于chessboard来说，格式为：

每个棋格由两个数字数字组成，分别为是否该格子埋雷和周边雷数，例如某个格子埋有雷且周边有3个雷，则表示为13，如果不埋雷且周边无雷则表示为00

将一个棋盘所有的棋格从左到右从上到下依次排列。例如：011001000000000101010000......

## 第十三个星期

### 大的要来了！！！



#### 1. mysql数据库建立

在华为云ECS云服务器上提前购买服务器并安装mysql，在云服务器上创建bigWork数据库，并在数据库中建立表格 minesweeper；

```mysql
create database bigWork;
use bigWork;
create table minesweeper
(
    ID         int auto_increment,
    name       varchar(100) default 'anonymous_chessboard' not null,
    `lines`    int                                         not null,
    columns    int                                         not null,
    chessboard TEXT(20001)                              not null,
    mines      int                                         not null,
    best_score int          default 0                      not null,
    constraint minesweeper_pk
        primary key (ID)
);

create unique index minesweeper_ID_uindex
    on minesweeper (ID);


create table User
(
    UserID   int auto_increment,
    username varchar(200) not null,
    password varchar(200) not null,
    constraint User_pk
        primary key (UserID)
);

create unique index User_UserID_uindex
    on User (UserID);


```

## 第十四个星期

我已经......不想再战斗了

反正写是写完了，估计一堆bug（）
