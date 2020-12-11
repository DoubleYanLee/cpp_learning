# 第一章

## 1.4 控制流

### for循环的四种写法

```c++
void myfunc( int i ){
    cout << i << " ";
}

int main(){

    vector<int> nums = {2,4,3,3,5,4,9,6};
    int n = nums.size();

    // 基础for循环 （初始化语句 循环条件  表达式）
    for( int i = 0; i < n; i ++ )
        cout << nums[i] << " ";
    cout << endl;

    //迭代器for循环
    for( vector<int>::iterator it = nums.begin(); it != nums.end(); it ++ )
        cout << (*it) << " ";
    cout << endl;

    //for_each == function template

    for_each( nums.begin(), nums.end(), myfunc);
    cout << endl;

    // for :
    for( auto it : nums )
        cout << it << " ";
    cout << endl;

}


```



### 读取数量不定的输入数据

`while(std::cin >> value)`

* 由于输入运算符返回其左侧对象，则该循环条件实际上是检测std::cin
* 当一个istream对象作为条件时，其效果是检测流的状态。当遇到文件结束符或者遇到一个无效输入时，istream对象状态会变为无效，无效的流对象会使条件变假

## 1.5 类简介

* c++中通过定义一个类来定义自己的数据结构。
* c++设计焦点：像使用内置类型一样自然的使用类类型

#### **文件重定向**

`$Sales_item < inputfile` 输入重定向

`$Sales_item > outfile` 输出重定向

也可以合并到一行

`$Sales_item <inputfile >outfile`

#### 成员函数

* 点运算符( ▪️ )只能用于类类型对象。其左侧运算对象必须是一个类类型对象，右侧运算对象必须是该类型的一个成员名。

* ```c++
  if(std::cin >> total){
    Sales_item trans;
    while(std::cin >> trans{
      //statement;
    }
     //先用if读取一条记录，然后用while读取剩下的记录 
  }
  ```

# 第二章 变量和基本类型

* c++是一种静态数据类型语言，它的类型检查发生在编译时，因此编译器必须知道程序中每一个变量对应的数据类型

## 2.1 基本内置类型

### 算数类型需要注意的点

* `因为int型变量溢出，以下循环无法退出：`

  ```c++
  for(int i = 0;i <= 2147483647;i++)if(i<0)cout<<"overflow";
  ```

*  类型 int short long 和 long long都是带符号的，通过在其前面添加unsigned可以得到无符号类型

* ```c++
  | 数据类型 | 范围 | 数量级 |
  | :----：| :----: | :----: |
  | int | min -2147483648 |-10^10 |
  | int | max 2147483647 | 10^10 |
  | unsigned int | min 0 | 0 |
  | unsigned int | max 4294967295 | 10^10 |
  | long long | min -9223372036854775808 | -10^19 |
  | long long | max 9223372036854775807 | 10^19 |
  ```

* 在使用char时，最好显式的指定其类型 signed char /  unsigned char

* 在算数表达式中不要使用char/bool

* 在算法竞赛中，将无穷大设置为0x3f3f3f3f 要好过设置为0x7fffffff(很容易溢出)  0x3f3f3f3f的十进制是1061109567，是10^9级别的（和0x7fffffff一个数量级）

### 类型转换

* unsigned char c = -1;  // c值为255  unsigned char 可表示范围为[0，255]
* signed char c = 256;  //当我们赋值给带符号类型一个超出它表示范围的值，结果是未定义的，程序可能继续工作/崩溃/生成垃圾数据

（第59页）



 





