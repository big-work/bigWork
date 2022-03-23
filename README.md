### 第一个星期

---

#### 1.定义结构体 chessboard(棋盘信息)

```c
struct Chessboard
{
    int  flag;  
    int  nearbyMineNum;
    int  tagOrNot;
}
```

| key           |                 instruction                 |
| ------------- | :-----------------------------------------: |
| flag          |          是否埋有雷，是为1，否为0           |
| nearbyMineNum | 周边一圈的雷数(默认为0，生成棋盘后自动计算) |
| tagOrNot      |      在游戏中是否被标记，是为1，否为0       |

#### 2.定义函数 createChessboard

```c
struct Chessboard **createChessboard(int x, int y, int MineNum);
```

> 二维动态数组的生成方法
>
> 为什么要选择生成动态数组？
>
> 用户可以选择自定义棋盘的大小，那数组的大小自然就要改变，原本的定义方法生成的是静态数组，不能改变大小，很捞（）
>
> 而动态数组可以通过自己分配内存释放内存来改变数组的大小（好耶）
>
> 此外，数组a\[i\]中的a就相当于指向a[0]的指针，反过来也一样
>
> 数组a\[x\]\[y\]就相当于a[x]的数组中存放了x个数组指针，每个指针都是指向一个长度为y的数组的首位置（）
>
> 或者实在不行就先学一下定义一维动态数组，在类推二维数组
>
> ```c
> #include<stdio.h>
> int **returnNum()//生成一个5*6的二维整形数组
> {
>   int **a,i,j;
>   //生成a[5]数组，其中存放指针
>   a = (int**)malloc(5*sizeof(int*));//申请内存，长度为5个整形指针
>   for(i=0;i<5;++i)
>   {
>       //在a[i]中存放长度为6的整形数组
>       a[i] = (int*)malloc(6*sizeof(int));//申请内存，长度为6个整形
>     for(j=0;j<5;++j)
>      {
>       //得到了a[5][6]的二维数组
>       a[i][j]=i;
>       }
>  }
>   return a;
> } 
> int main()
> {
>   //一维数组用一级指针，二维数组就要用二级指针了捏
>   int **cpy=returnNum();
>   int i,j;
>   for(i=0;i<5;++i)
>   {
>      for(j=0;j<5;++j)
>      {
>        printf("%d ", cpy[i][j]);
>       }
>      printf("\n");
>      free(cpy[i]);
>  }
>  //别忘了一个二维数组确定不会再被使用到的时候要先释放掉
>  free(cpy);
>   return 0;
> }
> ```

函数功能为返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）

| key     |      instruction       |
| :------ | :--------------------: |
| x       |     二维数组的宽度     |
| y       |     二维数组的长度     |
| MineNum | 二维数组需要埋下的雷数 |

| Value                        |                            status                            | 说明                                               |
| ---------------------------- | :----------------------------------------------------------: | -------------------------------------------------- |
| NULL，printf("...")          | x < 6 \|\| y < 10 \|\| MineNum > x * y - 10 \|\| MineNum < 10 | 棋盘大小或者埋雷个数不合法                         |
| struct Chessboard **myCBList |                              -                               | 返回一个已经随机埋好雷的结构体chessboard的二维数组 |

#### 3.定义函数 makeChessboard

```c
struct Chessboard **makeChessboard(struct Chessboard **myCBList, int MineNum);
```

函数功能为返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)

| key      |        instruction         |
| -------- | :------------------------: |
| myCBList | 传入未初始化的棋盘(已埋雷) |
| MineNum  |          埋雷总数          |

| Value      | status | 说明                                  |
| ---------- | :----: | ------------------------------------- |
| **myCBList |   -    | 返回计算nearbyMineNum后的棋盘         |
| NULL       |   -    | MineNum的值与传入的棋盘中已埋雷数不符 |

