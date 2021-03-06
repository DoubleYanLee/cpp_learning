## 第六章 函数

## 6.1 基础概念

* 函数的调用完成两项任务：一是用实参初始化函数对应的形参，二是将控制权转移给被调用函数。
* 函数的返回值类型不能是数组和函数类型，但是可以是指向数组或函数的指针
* 实参与形参的区别：实参是形参的初始值

### 6.1.1 局部对象

* c++中名字有作用域，对象有生命周期
* 函数体是一个语句块，块构成一个新的作用域   只存在块执行期间的对象称为自动对象
* 形参和函数体内部定义的变量统称为`局部变量`
* 内置类型的未初始化局部变量将产生未定义的值（所以局部变量要赋初值）
* 为了让局部变量的生命周期贯穿函数调用前后，可将局部变量定义为static类型
* **局部静态对象**在程序第一次经过对象定义语句时初始化，并直到程序终止才销毁。在此期间，即使函数结束执行也不会对其有影响。
* 内置类型的局部静态变量初始化为0

### 6.1.2 函数声明

* 函数只能定义一次，但可以声明多次
* 函数的名字必须在使用前声明    函数的声明无须函数体，用一个分号替代即可
* 在函数声明中经常省略形参的名字（因为没有函数体，有名字也没用呀），但是形参的类型不能省略哦
* 函数也应该在头文件中声明而在源文件中定义

### 6.1.3 分离式编译

* 分离式编译允许我们把程序分割到几个文件中去，每个文件独立编译

* fact.h 保存函数的声明  fact.cpp保存函数的定义  fact main.cpp编写的是main函数，其调用fact中的函数，编译过程如下：

  ```c++
  g++ factmain.cpp fact.cpp -o factmain
  ./factmain
  ```

  如果修改了其中一个源文件，则只需重新编译那个改动了的文件

  ```c++
  g++ -c fact.cpp //得到fact.o文件  编译
  g++ -c factmain.cpp //得到factmain.o文件
  g++ fact.o factmain.o -o factmain  //链接形成factmain可执行文件
  ./factmain
  ```



## 6.2 参数传递 

### 6.2.1 复合类型（compound type）

* 复合类型是指基于其他类型定义的类型 （这里先只了解 引用和指针）
* 一条声明语句由一个`基本数据类型`和一个`声明符列表`组成  声明符可以为变量名也可以为更复杂的声明符

#### 引用

* **引用**为对象起了另外一个名字 通过将声明符写成`&变量名`的形式来定义引用类型

  ```c++
  int ival = 1024;
  int &refval = ival;
  int &refval1; //报错 引用必须初始化
  int &refval2 = ival, refval3 = ival; //refval2是引用 refval3是int
  ```

  定义引用时，程序将引用和初始值绑定在一起，而不是初始值拷贝给引用。一旦初始化完成，引用和它的初始值对象一直绑定在一起，无法重新绑定到另一个对象上，所以引用必须初始化。

* 引用并非对象，它只是为一个已经存在的对象所起的另一个名字。为引用赋值，实际上就是把值赋给了与引用绑定的对象

* 引用可以绑定到引用上。其实际是以与引用绑定的对象作为初始值

* 由于引用本身不是一个对象，所以不能定义引用的引用。(这里不是说引用不能用引用赋值，而是这样的)

  ![Screenshot 2020-12-04 at 10.35.09 AM](/Users/yannie/Desktop/c++primer/chapter_six/reference.jpg)

* 引用只能绑定到对象上，而不能与字面值或某个表达式的计算结果绑定在一起

  ```c++
  int &refval = 10; //错的！！！
  double dval = 3.14;
  int &refval5 = dval; //错误！ 此时初始值必须为int型对象
  ```

#### 指针

* 指针是“指向”另一种类型的复合类型。
* 指针与引用不同之处：
  1. 指针本身是一个对象，允许对指针赋值和拷贝
  2. 在指针生命周期内，其可先后指向几个不同的对象
  3. 指针无需在定义时赋初值，但是其将拥有一个不确定的值。(但建议初始化所有指针)

* 通过将声明符写成`*变量名`的形式来定义指针类型

* 指针存放某个对象的地址，想要获取地址要用取地址符（&） 因为引用不是对象，没有实际地址，所以不能定义指向引用的指针

  ```c++
  int val = 42;
  int *p = &val;
  ```

* 如果指针指向了一个对象，则允许使用解引用符(*)来访问该对象

  ```c++
  cout << *p; //输出42
  ```

* 在试图使用一个指针之前，代码可以首先检查其是否为空

  - 得到空指针最直接的办法就是用字面值**nullptr**来初始化指针，nullptr是一种特殊类型的字面值，它可以被转换成任意其他的指针类型。
  - 过去使用一个预处理变量**NULL**来给指针赋值，预处理器是运行于编译过程之前，所以其不属于命名空间std，则无须在前面加上std::

* 赋值永远改变的是等号左侧的对象

  ```c++
  int * pi = 0;
  pi = &val; // pi的值被改变了，其现在指向val
  * pi = 0; //val的值改变了，指针pi并没有改变
  ```

* 任何非0指针对应的条件值都是true

* void* 是一种特殊的指针类型，其可存放任意对象的地址。但不能直接操作void*指针所指的对象，因为我们并不知道这个对象到底是什么类型

* 声明符列表

  ```c++
  int i = 1024, *p = &i, &r = i; //i是一个int型的数 p是一个int型指针 r是一个int型引用
  ```

  int 是基本数据类型， 后面的 i *p  &r 只不过是声明符的一部分

* 通过*个数可以区分指针的级别   **表示指针的指针（因为指针本身是一个对象，其也有地址）

* 解引用指向指针的指针会得到一个指针

  ```c++
  int ival = 1024;
  int *pi = &ival;  int **ppi = &pi;
  cout << **ppi;  cout << *pi;
  ```

* 指向指针的应用

```c++
int i = 42; int *p ;  int *&r = p; 
r = &i; //r引用了一个指针，则给r赋值&i就是令p指向i
*r = 0; //解引用r得到i，将i的值改为0
```

* **要理解 r 类型到底是什么，从右向左阅读 r 的定义，离变量名最近的符号对变量的类型有最直接的影响。声明符其他部分用以确认r引用的类型是什么，最后声明符的基本数据类型部分指出r引用的是一个int型指针**

```c++
int *&r = p; //因此这里r是一个引用 声明符剩余的*表明r引用的是一个指针
```

### 6.2.2 基本概念

* 形参的类型决定了形参与实参交互的方式。若形参是引用类型，它将绑定到对应的实参上；否则，将实参的值拷贝后赋值给实参
* 当形参是引用类型时，其对应的实参被**引用传递** 。 引用形参是它对应的实参的别名。
* 当实参的值被拷贝给形参的时候，形参和实参是两个独立的对象。此时实参被**值传递**。

### 6.2.3 传值参数

* 此时形参对变量的改动不会影响初始值实参
* 指针形参也是值传递，其传递时拷贝的是指针的值，拷贝之后，两个指针是不同的指针。但可以通过指针修改它所指对象的值。

```c++
void reset(int *ip){
	*ip = 0;
	ip = 0;
}

int main(int argc, char const *argv[])
{
	int i = 42;
	std::cout << &i << std::endl;
	reset(&i);
	std::cout << i << std::endl;
	std::cout << &i << std::endl;
	return 0;
}
```

![运行结果](/Users/yannie/Desktop/c++primer/chapter_six/zhizhen.jpg)

### 6.2.4 使用引用避免拷贝

* 拷贝大的类类型对象或者容器对象太低效了，设置有的类类型（如IO类型）不支持拷贝，此时只能用引用形参来访问该类型的对象。
* 当函数无须修改引用形参值的时候，最好使用常量引用。
* 使用引用形参可以返回额外的信息 

### 6.2.5 const形参和实参 

#### const限定符用法回顾

* const对象一旦创建后其值就不能再改变，所以const对象必须初始化，其初始值可以是任意复杂的表达式

* const对象被设定为仅在文件内有效。当多个文件中出现了同名const变量时，其等同于在不同文件中定义了独立的变量。

* 当const变量初始值不是一个常量表达式时，若要在文件中共享const变量，可以在其声明和定义的部分都添加extern关键字。

* const的引用（也叫对常量的引用）

  ```c++
  const int ci = 1024; const int &r1 = ci;
  r1 = 42; //错误 r1是对常量的引用
  int &r2 = ci; //错误 让一个非常量引用指向一个常量对象
  ```

  ```c++
  double dval = 3.14;  const int &ri = dval; //不会报错
  ```

  编译器优化如下：

  ```c++
  const int temp = dval; //生成一个临时的整型常量  
  const int &ri = temp; //ri绑定了一个临时量对象。 临时量对象是当编译器需要一个空间来暂存表达式的求值结果时临时创建的一个未命名的对象
  ```

  但当为

  ```c++
  double dval = 3.14;   int &ri = dval; //会报错
  ```

  因为此时ri绑定的是一个临时量而并非dval（按道理此时应该ri值为3，因为临时量值为int型，截断为3），而既然想要让ri绑定dval，就肯定是想用ri修改dval的值，这里根本没法做到，所以就是非法行为。

* 对const的引用可以绑定一个非常量数，但const数不能绑定到一个非const的引用上

  ```c++
  int i = 42; int &r1 = i; const int &r2 = i;
  //r2不能修改i的值，但是i的值可以由r1修改
  ```

#### 指针和const

* 要想存放常量对象的地址，只能使用指向常量的指针
* const指针：把*放在const关键字之前用以说明指针是一个常量

```c++
int err = 0;  int *const curErr = &err; //curErr将一直指向err
```

这样书写也表明，不变的是指针本身的值，而并非指向的那个值

从右往左读，const表示curErr本身是一个常量对象，对象类型由声明符其余部分确定。声明符中下一个是*，表示其为一个常量指针。声明语句中的基本数据类型int表示常量指针指向的是一个int对象。

* 指针本身是一个常量并不意味着不能通过指针修改其所指对象的值，能否这样做完全取决于所指对象的类型。

#### 顶层const

* 使用**顶层const**表示指针本身是一个常量  **底层const**表示指针所指的对象是一个常量

  ```c++
  const int ci = 42;
  const int *p2 = &ci; //允许改变p2的值，这是一个底层const
  //从右往左看，它首先是一个指针对象，声明符剩余的部分表示对象类型，其是一个指向常量int型数的指针
  const int *const p3 = p2; //靠右的const是顶层const，靠左的是底层const
  const int &r = ci; //用于声明引用的const都是底层const
  ```

  * 拷贝的时候顶层const不受什么影响，底层const却有所限制（非常量可以转化成常量，而常量不能转化成非常量）

  #### 常量表达式

  * 常量表达式表示值不会改变并且在编译过程就能得到计算结果的表达式

    ```c++
    const int max_files = 20; //是常量表达式
    int staff_size = 27; //不是常量表达式 因为其数据类型不是 const int
    const int sz = get_size(); //不是常量表达式 因为它的具体值直到运行时才能获得到
    ```

  * 将变量声明为`constexpr`类型，以便编译器来检验变量的值是否为一个常量表达式

  * 在constexpr声明中如果定义了一个指针，限定符constexpr仅和指针有关，与指针所指对象无关

#### 指针或引用形参与const

* 当形参有顶层const时，传给它常量对象或者非常量对象都是可以的

  ```c++
  void fcn(const int i);
  void fcn(int i); //不合法 因为在上一行中顶层const被忽略了 跟这一行表达的意思就一样了
  ```

* c++允许用字面值初始化常量引用

* 尽量使用常量引用

  - 函数不可以修改其值
  - const对象，字面值等不能传递给普通的引用形参 但常量引用可以

### 6.2.6 数组形参

* 数组两个性质：不允许拷贝数组 / 使用数组时会将其转化成指针

  ```c++
  void print(const int*);
  void print(const int []); //这两种写法等价
  ```

* 标记数组长度的方法（使用标准库规范/显示传递一个表示数组大小的形参）

```c++
void print(const int *beg, const int *end){
  while(beg != end)
    cout << *beg++ << endl;
}
void print(const int ia[], size_t size){ }
```

* c++函数的形参可以是数组的引用，此时引用形参绑定到对应的实参上，也就绑定到数组上了

```c++
void print( int (&arr)[10] ) { } //arr是具有10个整数的整型数组的引用
void print( int &arr[10] ){ } //arr是引用的数组
```

* 传递多维数组

  ```c++
  void print( int (*matrix)[10], int rowsize ){ } //*matrix两端括号不能少
  void print( int matrix[][10], int rowsize ){ }
  ```

### 6.2.7 main: 处理命令行选项

```c++
int main(int argc, char const *argv[]){ }
```

### 6.2.8 列表初始化

 C++初始化类成员时，是按照声明的顺序初始化的，而不是按照出现在初始化列表中的顺序。

```c++
class  CMyClass  {
    CMyClass(int x, int y);
    int m_x;
    int m_y;
} ;

CMyClass::CMyClass( int  x,  int  y) : m_y(y), m_x(m_y)
 { }
```

你可能以为上面的代码将会首先做m_y=y，然后做m_x=m_y，最后它们有相同的值。但是编译器先初始化m_x，然后是m_y,，因为它们是按这样的顺序声明的。结果是m_x将有一个不可预测的值。

### 6.2.9 含有可变形参的函数

```c++

void error_msg( initializer_list<string> il ){

    for( auto beg = il.begin(); beg != il.end(); ++beg )
        cout << *beg << " ";
    cout << endl;
}
int main() {
    string expected = "ok";
    error_msg( {"function", expected, "haha"} );
    error_msg( {"function", "wrong" } );
    return 0;

}
```



## 6.3 返回类型

### 有返回值函数

* 只要函数的返回类型不是void，则函数内每条return语句必须返回一个值
* 在含有return语句的循环后面应该也有一条return语句，很多编译器无法发现这个错误（leetcode上的可以发现这个错误。。。）
* 函数返回的值用于初始化调用点的一个临时量（即调用点会创建一个临时变量来存储这个返回值，然后再将其赋值给赋值符号左边的变量）
* 如果函数返回引用，则引用仅是它所引对象的一个别名，并不是拷贝该对象。
* 不要返回局部对象的引用或指针(局部对象返回其实是不报错的)

```c++
const string &manip(){ //一切问题出在返回值是引用 因为函数结束时临时对象占用的空间也就随之释放
  string ret; //这一句然后改变ret的值
  if( !ret.empty() ) return ret; //错误 返回局部对象的引用 直接报错无法返回
  else return "Empty"; //错误 “Empty”是一个局部临时变量 (但是可以输出正确结果)
//这里字符串字面值转换成一个局部临时string对象，对于mainip来说其和ret一样是局部的
}
```

* `函数返回局部对象`这个问题以后探讨

### 返回类类型函数和调用运算符

* 如果函数返回指针，引用或类的对象，则可以使用函数调用的结果访问结果对象的成员

  ```c++
  string s = Solution().getminstring("sahduibvuibne"); //这个应该跟这里说的不一样
  ```

* 如果函数返回值是引用，则这个值是左值，其他的值是右值

* 列表初始化返回值，即函数返回用花括号包围的值的列表

  ```c++
  vetcor<int> findnum( ){
    return {1,2}; //类似于这种
  }
  ```

* main函数返回0表示执行成功，返回其他值都认为是失败

### 返回数组指针

* 因为数组不能被拷贝（这里指不能直接用赋值符号将一个数组拷贝给另一个数组,但vector可以哦），所以函数不能返回数组，但是可以返回数组的指针或引用。

* 使用类型别名来返回数组的指针或引用

  ```c++
  typedef int arrT[10] ; //arrT是一个类型别名，它表示的类型是含有10个整数的数组
  using arrT = int[10]; //使用using来给int[10]声明一个别名 arrT
  arrT* func(int i); //返回一个指向含有10个整数的数组的指针 
  ```

* 声明一个返回数组指针的函数

  ```c++
  int (*func(int i))[10]; 
  ```

* 使用尾置返回类型，尾置返回类型跟在形参列表后面并以一个**->**符号开头，在本该出现返回类型的地方用auto。这种返回方式适合返回类型比较复杂的函数，如数组的指针或引用。

  ```c++
  //func 接受一个int类型的实参，返回一个指针，该指针指向含有10个整数的数组
  auto func(int i) -> int(*)[10];
  ```

* 使用decltype关键字

```c++
int odd[] = {1,3,5,7}; int even[] = {2,4,6,8};
decltype(odd) *arrPtr(int i)  //arrPtr返回一个指向含有5个整数的数组的指针
  return (i%2) ? &odd : &even;
```

## 6.4 函数重载

* 如果形参是某种类型的指针或引用，则通过区分其指向的是常量对象还是非常量对象可以实现重载

```c++
Record lookup(Account&);
Recore lookup(const Account&); //这个顶层和底层const好容易忘记。。。
```

* const_cast

## 6.5 c++的特殊语言特性

### 默认实参

```c++
string screen( size_type ht = 24, size_type wid = 80, char background = '' ); //为每一个形参都提供了默认的实参,某个形参赋了默认值之后，其后的所有形参都必须有默认值 而其前面的不要求
```

* 在调用的时候，只可以省略尾部的实参  所以在设计含有默认实参的函数时，尽量让经常使用默认值的形参出现在后面

```c++
window = screen(, , '?'); //这样都不可以
```

### 内联函数和constexpr函数

* 内联函数可以避免函数调用的开销
* 在函数返回类型前面加上关键字 inline  内联机制用于优化规模较小，流程直接，频繁调用的函数
* constexpr函数是指能用于常量表达式的函数
* 内联函数和constexpr函数通常定义在头文件中

### assert预处理宏

* assert宏定义在cassert头文件中，预处理名字由预处理器而非编译器管理，因此我们可以直接使用预处理名字而无需提供using声明

### NDEBUG预处理变量

* 我们可以使用一个#define语句定义NDEBUG，从而关闭调试状态
* 定义NDEBUG能避免检查各种条件所需的运行时开销
* `__func__` 是编译器定义的一个局部静态变量，用于存放函数的名字
* `__FILE__`存放文件名的字符串字面值
* `__LINE__`存放当前行号的整型字面值
* `__TIME__`存放文件编译时间的字符串字面值
* `__DATE__`存放文件编译日期的字符串字面值

## 6.6 函数匹配 

* 未仔细看 243页

## 6.7函数指针

* 想要声明一个可以指向该函数的指针，只需要用指针替换函数名即可
* 248页



















































c++就带着学，每天看一个几点几



# 第7章

## 7.1 定义抽象数据类型

### 基础概念

* 类的基本思想是`数据抽象`和`封装`  （首先要定义一个抽象数据类型）
* `数据抽象`是一种依赖于`接口`和`实现`分离的编程技术。类的接口包括用户所能执行的操作；类的实现包括`类的成员`，负责接口实现的`函数体`以及定义类所需要的各种`私有函数`。
* `封装`实现了类的`接口`和`实现`的分离。封装后的类隐藏了它的实现细节。即类的用户只能使用接口而无法访问实现部分
* 类的用户可以直接访问它的数据成员的不是抽象数据类型。
* 定义在类内部的函数是隐式的inline函数
* 成员函数的声明必须在类的内部，但是定义不一定要在内部，也可以在外部

```c++
class Sales_data{
  std::string isbin( ) const { return bookNo; } //定义和声明都在内部
  Sales_data &combine( const Sales_data& ); //只有声明在内部
  double avg_price() const; //只有声明在内部
  std::string bookNo;
};
Sales_data add( const Sales_data&, const Sales_data& ); //Sales_data的非成员接口函数
```

* isbin()函数中，其返回的是Sales_data对象的bookNo数据成员。但是其是如何获得bookNo成员所依赖的对象的呢？

```c++
total.isbin();
//通过点运算符来访问total对象的isbin成员  当调用成员函数时，实际上是在替某个对象调用它
//这里isbin指向类的成员bookNo，则它其实隐式地指向调用isbin的类的对象的成员 这里是isbin返回bookNo时，实际上隐式地返回total.bookNo
```

### this指针

* 成员函数通过一个名为this的额外的隐式参数 来访问 调用它的那个对象，这里指isbin函数通过隐式参数this来访问total
* 如果调用**total.isbin() **编译器会负责把`total的地址`传给isbin的`隐式形参this` ，可以等价为下面这种形式

```c++
total.isbin(); //原来的
Sales_data::isbin(&total) //调用isbin成员时传入了total的地址
```

* 在成员函数内部，可以直接调用成员，而不需要用成员访问符，就是因为this所指的正是这个对象。 任何对类成员的直接访问都被看作this的隐式引用。

```c++
std::string isbin( ) const { return bookNo; }
```

* 这里的const关键字放在成员函数的参数列表之后，表示this是一个指向常量 的指针，这样就可以把this绑定到一个常量对象上，即一个常量对象上就可以调用普通的成员函数。 使用const的成员函数叫做**常量成员函数**

### 类作用域和成员函数

* 编译器会首先编译成员的声明，然后才轮到成员函数体。因此成员函数体可以随意使用类中的其他成员而无需在意这些成员出现的次序。

* 在类外部定义的成员函数，其函数名必须包含它所属的类名：

  ```c++
  double Sales_data::avg_price() const { 
    if( units_sold)
      return revenue / units_sold;
  }
  ```

  编译器一看到这个函数名，就能理解剩余代码是位于类的作用域内的。因此，当avg_price使用 revenue和units_sold时，实际上它隐式地使用了类的成员

### 定义一个返回this对象的函数

![](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic1.png)

(要仔细看啊，很重要的这一个小知识点)

* 非成员函数是类接口的组成部分，这些函数的声明（非定义）应该与类在同一个头文件内

![pic2](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic2.png)

* 默认情况下，拷贝类的对象其实拷贝的是对象的数据成员

### 构造函数

* 构造函数不能被声明为const类型。当创建类的一个const对象时，指导构造函数完成初始化过程，对象才能取得真正常量的属性，也就是说，构造函数在const对象的构造过程中可以向其写值。
* 指针和数组等复合类型或内置类型的对象被默认初始化的话，它们的值是未定义的。
* 构造函数初始值列表

```c++
Sales_data(const std::string &s, unsigned n) : bookNo (s),units_sold(n) { }
```

* c++中拷贝对象的情况：初始化变量  以值的方式传递或返回一个对象。 如果使用“=”号初始化一个变量，实际上执行的是拷贝初始化，编译器把等号右边的初始值拷贝到新创建的对象中去，与之相反，如果不使用等号，则执行是直接初始化。

## 7.2 访问控制与封装

* 可以用class或struct中的任意一个定义类。但struct的成员访问权限默认为public，而class的成员访问权限默认为private
* 类可以允许其他类或者函数访问它的非公有成员，只要将其他类或者函数的**声明**为它的**友元(friend)**，只是声明部分需要加 friend哦，定义部分不用加
* 友元的声明仅仅指定了访问权限，而非一个通常意义上的函数声明。如果想要调用这个友元函数，应该再对该函数进行一次声明
* 通常将友元的声明与类本身放置在同一个头文件中，但是在类的外部

## 7.3 类的其他特性



























## 7.6 类的静态成员

* 类的静态成员存在于任何对象之外，其与类关联在一起，对象中不包含任何与静态数据成员有关的数据。静态成员函数也不与任何对象绑定在一起，它们不包含this指针

* 使用类的静态成员

  * 使用作用域运算符直接访问静态成员

  ```c++
  doublr r = Account :: rate();
  ```

  * 使用类的对象，引用或指针来访问静态成员

  ```c++
  Account ac1; Account *ac2 = &ac1;
  r = ac1.rate();  //通过Account的对象或引用访问
  r = ac2->rate(); //通过指向Account对象的指针访问
  ```

* 当静态成员函数在外部定义的时候，不能使用static关键字，只能在类内部声明的时候使用即可

```c++
void Account::rate(double newRate){
  interestRate = newRate;
}
```

* 静态数据成员一旦被定义，就存在于程序的整个生命周期中。
* 因为静态数据成员不属于类的任何一个对象，所以它们并不是在创建类的对象时被定义的。一般，我们必须在类外部定义和初始化每个静态成员

```c++
double Account::interestRate = initRate();
```

* 静态成员和普通成员的区别
  * 静态数据成员可以是不完全类型，可以就是它所属的类类型，而非静态数据成员只能声明称它所属类的指针或引用
  * 静态成员可以作为默认实参

















## 第九章 顺序容器

### 9.1 顺序容器概述

* 元素在顺序容器中的顺序与其加入容器时的位置相对应。关联容器中的元素的位置由元素相关联的关键字值决定。
* 所用容器类都共享公共的接口，不同容器按不同方式对其进行扩展
* 一个容器就是一些特定类型对象的集合。 容器都定义为模版类

![pic6](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic6.png)

* 第二个迭代器end往往指向尾元素之后的位置 [ begin, end )

```c++
list<string>:: iterator iter; //使用作用域运算符声明使用list<string>类的iterator成员
```

* 只有顺序容器的构造函数才能接受大小参数

```c++
C c1(n); //c1包含n个元素，这些元素进行了值初始化  
C c2(n,t);//c2包含n个初始化值为t的元素
```

* 将一个容器初始化为另一个容器的拷贝

```c++
C c1(c2); //拷贝整个容器
C c1(c2.begin()+2, c2.end()); //拷贝指定范围元素
```

* 初始化：初始化为拷贝 列表初始化 迭代器初始化 指定容器大小和值的初始化

* 当定义一个array时，除了指定元素类型，还要指定容器大小 。

  ```c++
  array<int, 42> i;
  ```

* 我们不能对内置数组类型进行拷贝或赋值操作，但是array并无此限制

```c++
array<int, 10> digits = {0,1,2,3,4,5,6,7,8,9};
array<int, 10> copy = digits;
```

* 如果两个容器原来大小不同，赋值运算后两者的大小都与右边容器的原大小相同。

* 顺序容器(除array)定义了一个assign成员，允许从容器的一个子序列或者不同但相容的类型赋值。

  ```c++
  list<string> names;  vector<const char*> oldstyle;
  names = oldstyle; //错误 容器类型不匹配
  names.assign( oldstyle.cbegin(), oldstyle.cend() ); //可以将const char*转换为string
  ```

* swap操作交换两个相同类型的容器的内容。除array外，交换两个容器内容的操作元素本身并没有交换，只是交换了两个容器内部的数据结构。因此如果之前有迭代器指向元素，现在该迭代器则指向另一个容器了。

* 统一使用非成员版本的swap是一个好习惯

* 容器是否可以用一个关系运算符取决于容器里的元素类型是否定义有该比较类型。比如容器里是类类型，类并没有定义关系比较运算，则就不能比较。

### 9.3 顺序容器操作

* push_back / emplace_back   push_front / emplace_front  insert
* 当我们用一个对象来初始化容器或者将一个对象插入到容器中时，实际上放入到容器中的是对象的拷贝，而不是对象本身。随后对容器中元素的任何改变也不会影响到原始对象。
* insert函数的用法

```c++
slist.insert( slist.begin(), "hello" ); //将“hello”插入到begin位置之前
slist.insert( slist.end(), 10, "Anna" ); //将10个元素插入到slist的末尾
```

* emplace 与 insert 的区别

  **当调用push或insert成员函数时，我们将元素类型的对象传递给他们，这些对象被拷贝到容器中。而当调用emplace成员函数时，则是将参数传递给元素类型的构造函数，emplace成员使用这些参数在容器管理的内存空间中直接构造元素。**

* 在容器中访问元素的成员函数(即front, back,at和下标)返回的都是引用，即可以作为左值

```c++
c.front() = 42; //将42赋值给c中第一个元素
auto &v = c.back(); v = 1024;//改变了c中元素
auto &v2 = c.back(); v2 = 0; //未改变c中元素 v2不是一个引用，是c.back()的一个拷贝
```

* 使用auto变量来保存这些函数返回值，并希望使用此变量来改变元素的值，要记得将其定义为引用 类型
* 删除元素  pop_back  pop_front  clear (前3个都返回void) erase(返回一个指向被删元素之后元素的迭代器)  
* 在删除元素之前，一定要保证他是存在的！！！
* 在forward_list中添加或删除元素的操作都是通过改变给定元素之后的元素来完成的
* 可以用resize来增大或缩小容器，array不支持resize

```c++
list<int> ilist(10,42); ilist.resize(15,-1); //将5个值为-1的元素添加到ilist的末尾
```

* 容器操作可能使迭代器失效,失效的迭代器，引用，指针是严重的运行时错误
  * 赋值等相关运算会导致指向左边容器内部的迭代器 引用 指针失效，而swap不会
  * 向一个vector，string或deque插入元素会使所有指向容器的迭代器 引用 指针失效
  * ![](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic7.png)

* 添加/删除vector string或deque元素的程序必须考虑迭代器，引用和指针可能失效的问题，程序必须保证每个循环步中都更新迭代器，引用或指针。
* 不要保存end返回的迭代器，因为已经失效了

### vector对象的增长方式

* vector是将元素连续存储的，为了避免空间不够时不停的重新分配空间，vector和string通常会分配比心的空间需求更大的内存空间，将其作为备用空间。 reverse允许我们通知容器应保存多少元素，其不会将空间变小
* 使用shrink_to_fit来请求容器退回不需要的空间。但该请求也可能被忽略

### 额外的string操作

* substr操作，返回一个string，它是原来string的一部分/全部的拷贝

```c++
string s("hello,world");
string s3 = s.substr(6);  string s4 = s.substr(6,11);  //结果都是world
```

* append: 在string末尾进行插入操作
* replace是调用erase和insert的一种间写形式 

```c++
s2.replace(11,3,"5th"); //在位置11开始，删除3个字符并插入"5th"
```

* string搜索函数返回string::size_type值，该类型是一个unsigned类型，不应该用int或者其他带符号类型来保存这些函数的返回值

```c++
auto / unsigned int pos1 = name.find("Anna");
```

* find_first_of: 从哪里开始搜索。 rfind: 逆向搜索
* compare函数 类似于 strcmp函数
* string的数值转换

```c++
int i = 42;
string s = to_string(i); //将i转化成字符表示形式
double d = stod(s); //将字符串转换成浮点数  stoi : int型 stol: long型 stof:float型
```

### 9.6 容器适配器

* 标准库定义了三个顺序容器适配器: stack queue (默认基于deque实现) 和 priority_queue (默认基于vector实现)
* 适配器使某种食物的行为看起来像另一种事物 如stack适配器接受一个顺序容器，使其操作起来像一个stack一样。

```c++
stack<int> s1; //默认等同于stack<int,dequeue<int>> s1
stack<string, vector<string>> str_stk; //stack由vector<string>实现了，而不是dequeue
```

* 栈适配器和队列适配器

* *什么应用场景下，需要覆盖基础容器类型？*

  - 关系运算
    支持关系运算：`==`,`!=`,`>`,`>=`,`<`,`<=`
    使用关系运算要求元素支持`==`和`<`两个运算符。

    

## 第十章 泛型算法

### 10.1 概述

* 标准库并未给每个容器都定义成员函数来完成特定的操作，而是定义了一组泛型算法。“算法”是因为它们实现了一些经典算法的公共接口，如排序和搜索；“泛型”是因为它们可以用于不同类型元素和多种容器类型。
* 这些算法通常是遍历由两个迭代器指定的一个元素范围来进行操作。

```c++
auto result = find(vec.cbegin(), vec.cend(), val); //查找元素中的特定值val 返回的是指向它的迭代器  如果没有找到，则返回第二个参数来表示搜索失败
```

* 迭代器使算法不依赖于容器，但是算法依赖于元素类型的操作，比如元素类型要支持==的操作
* 算法永远不会改变底层容器的大小，其可能改变容器中保存的值，或移动元素，但不会直接添加或删除元素  插入器(inserter)就可能做这个事情

### 10.2 初始泛型

* 除了少数例外，标准库算法都对一个范围内的元素进行操作。接受输入范围的算法总是使用前两个参数来表示此范围。

* 只读算法：只读取算法，并不改变元素

  * find函数   accumulate函数，定义在numeric中，前两个参数是范围，第三个参数是和的初值。accumulate的第三个参数类型决定了函数中使用哪个加法运算符以及返回值类型。
  * 调用accumulate将vector中所有string元素连在一起

  ```c++
  string sum = accumulate( v.cbegin(), v.cend(),string("") ); //第三个参数不能直接传一个""，因为这样，保存和的对象类型是const char*，而该类型没有定义+运算符
  ```

  * equal: 用于判断两个序列是否保存相同的值。此算法接受三个迭代器，前两个表示第一个序列中的元素范围，第三个表示第二个序列中的首元素

  ```c++
  equal(roster1.cbegin(), roster1.end(), roster2.begin() );
  ```

* 写容器元素算法: 记住算法不会执行容器操作，因此它们自身不可能改变容器的大小

  * fill算法，接受一对迭代器表示一个范围，还接受一个值作为第三个参数，将其赋值给输入序列中的每个元素

  ```c++
  fill(vec.begin(), vec.end(), 0); //将每个元素都置为0
  ```

  * fill_n接受一个单迭代器，一个计数值和一个值，它将给定值赋予迭代器指向的元素开始的指定个元素。

  ```c++
  fill_n( vec.begin(),vec.size(), 0 ); //将所有元素重置为0
  vector<int> res; //空向量
  fill_n(res.begin(),10, 0); //错误，修改不存在的元素
  ```

  * 当通过一个插入迭代器赋值时，一个与赋值号右侧值相等的元素被添加到容器中。
  * back_inserter  它定义在头文件 iterator中，其接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。当通过迭代器赋值时，赋值运算符会调用pu sh_back将一个具有给定值的元素添加到容器中

  ```c++
  vector<int> vec;
  auto it = back_inserter(vec);
  *it = 42; //此时元素才会被插入到vec中
  ```

  * 通常使用back_inserter来创建一个迭代器，作为算法的目的位置来使用

  ```c++
  vector<int> vec;
  fill_n(back_inserter(vec),10,0); //添加10个元素到vec
  ```

* 拷贝算法：此算法接受三个迭代器，前两个表示一个输入范围，第三个表示目的序列的起始位置。此算法将输入范围中的元素拷贝到目的序列中。copy返回的是目的位置迭代器的值，即其恰好指向拷贝到a2的尾元素之后的位置。

```c++
int a1[] = {0,1,2,3,4,5};
int a2[sizeof(a1)/sizeof(*a1)];
auto ret = copy(begin(al),end(a1),a2);
```

		* replace算法，接受四个参数：前两个是迭代器，表示输入序列，后两个一个是要搜索的值，一个是新值。将所有等于给定值的元素都改为另一个值。

```c++
replace(ilst.begin(), ilst.end(), 0, 42);
replace_copy( ilst.cbegin(),ilst.cend(), back_inserter(ivec), 0, 42 );
//该算法中ilst并未改变，invec包含ilst的一份拷贝，但是原来在ilst中值为0的元素在ivec中都变成42
```

* 重排容器元素的算法
  * sort函数，默认按升序排列，unique标准库算法使不重复的元素出现在vector开始部分，返回指向不重复区域之后一个位置的迭代器。算法不能执行容器，所以要用erase成员函数来删除元素。
  * unique并不真删除任何元素，只是覆盖相邻的重复元素，所以后面位置的元素是未知的。

### 10.3 定制操作

#### 10.3.1 向算法传递函数

* sort的重载版本，接受第三个参数，此参数是一个**谓词**
* 谓词是一个可调用的表达式，其返回结果是一个能用作条件的值。谓词分为：一元谓词和二元谓词(意味着有两个参数)，接受谓词参数的算法对输入序列中的元素调用谓词。

```c++
bool isShorter( const string &s1, const string &s2 )
  return s1.size() < s2.size();
sort( words.begin(), words.end(), isShorter );
```

* stable_sort算法维持相等元素的原有顺序，其接受的参数和sort一样

#### 10.3.2 lambda表达式

* 为了解决不用为每个可能的大小都编写一个独立的谓词，引入了lambda表达式
* 使用find_if算法来查找第一个具有特定大小的元素。其接受一对迭代器表示一个范围，其第三个参数是一个谓词。 find_if算法对输入序列中的每个元素调用给定的谓词，其返回第一个使谓词返回非0值的元素。
* find_if只接受一元谓词，所以要用lambda表达式来解决
* 我们可以向一个算法传递任何类别的可调用对象（指可以用调用运算符()的对象或表达式）
* lambda表达式表示一个可调用的代码单元，可以将其理解为未命名的内联函数。一个lambda具有一个返回类型，一个参数列表和一个函数体。但与函数不同，lambda可以定义在函数内部。

```c++
[capture list](parameter list) -> return type { function body }
//capture list指其所在函数中定义的局部变量的列表 通常为空
//return type 返回类型  parameter list 参数列表 （前两个可忽略） function body 函数体
//lambda表达式必须用尾置返回来指定返回类型
```

* lambda的调用方式和普通函数的调用方式相同，都是使用调用运算符。

```c++
auto f = []{return 42;};  //定义一个可调用对象f，它不接受参数，返回42
cout << f() << endl; //打印42
```

* 向lambda传递参数 : 其调用的实参数目永远与形参数目相等

```c++
[](const string &a, const. string &b){ return a.size() < b.size(); } //按升序排序 空捕获列表说明此lambda不使用它所在函数中任何局部变量
//按长度排序，长度相同的维持字典序
stable_sort( words.begin(), word.end(),
           [](const string &a, const string &b)
            { return a.size() < b.size();} );
```

* 查找第一个长度大于等于sz的元素

```c++
auto wc = find_if( words.begin(), words.end(), 
                 [sz](const string &a){ return a.size() >= sz; }); 
//find_if返回的是迭代器
for_each( wc, words.end(), //这是两个迭代器，表示一个范围
        [](const string &s){ cout << s << " "; });
cout << endl; //打印长度大于等于给定值的单词，每个单词后面接一个空格
```

* For_each算法，接受一个可调用对象，并对输入序列中每个元素调用此对象。

#### 10.3.3 lambda捕获和返回

**捕获是指一个lambda表达式将局部变量包含在捕获列表，在捕获列表中的参数则可以被lambda函数体使用**

* 向一个函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象：传递的参数就是此编译器生成的类类型的未命名对象。
* lambda采用值捕获方式。与传值参数类似，采用值捕获的前提是变量可以拷贝。与参数不同，被捕获的变量的值是在lambda创建时拷贝，而不是调用时拷贝。

```c++
void fcn1(){
  size_t v1 = 42; 
  auto f = [v1] { return v1; };
  v1 = 0;
  auto j = f(); //j为42，因为是在创建的时候拷贝而不是调用时候拷贝，所以j并不为0
}
```

* 引用捕获， 在定义lambda时可以采用引用方式捕获变量

  ```c++
  void fcn2(){
    size_t v1 = 42; 
    auto f2 = [&v1] { return v1; };
    v1 = 0;
    auto j = f(); //j为0，f2保存的是v1的引用，而非拷贝
  }
  ```

* 引用捕获的问题：采用引用方式捕获一个变量，就必须保证被引用的对象在lambda执行的时候是存在的。lambda捕获的都是局部变量，这些变量在函数结束后就不存在了。如果lambda可能在函数结束后执行，捕获的引用指向的局部变量已经消失。

* 引用捕获的必要性：我们不能拷贝ostream对象，因此捕获os的唯一方法就是捕获其引用或指向os的指针

```c++
void biggies( vector<string> &words, vector<string>::size_type sz,
            ostream &os = cout, char c = ' '){
  for_each( words.begin(), words.end(),
          [&os, c](const string &s) { os << s << c;} );
}//接受一个ostream的引用用来输出数据，并接受一个字符作为分隔符
```

* 隐式捕获：让编译器根据lambda体中的代码来推断我们要使用哪些变量。为了指示编译器推断捕获列表，应在捕获列表中写&（捕获引用）或=（捕获值，也可以混合使用，但捕获列表中第一个元素必须是一个&或=）
* 默认情况下，对于一个值被拷贝的变量，lambda不会改变其值，若想改变一个被捕获的变量的值，可以在参数列表首加上关键字mutable

```c++
void fcn3(){
  size_t v1 = 42;
  auto f = [v1]()mutable { return ++v1; }; //f改变了捕获变量的值
  v1 = 0;
  auto j = f(); // j为43
}
```

```c++
void fcn4(){
  size_t v1 = 42;
  auto f = [&v1]{ return ++v1; };  //v1是一个非const变量的引用，可以通过f中的引用来改变他的值
  v1 = 0;
  auto j = f(); // j为1
}
```

* 指定lambda的返回类型

  ![](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic8.png)

#### 10.3.4 参数绑定

* 标准库函数bind，定义在头文件functional中。可将其看作一个通用的函数适配器，接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表:

```c++
auto newCallable = bind(callable, arg_list);
//newCallable本身是一个可调用对象 arg_list是一个逗号分隔的参数列表，对应于callable的参数
```

* 即当调用newCallable时,newCallable会调用callable函数，并传递它arg_list中的参数
* arg_list参数重可能包含形如_n的名字，其中n是一个整数。这些参数是"占位符"，_`_1`表示newCallable的第一个参数

```c++
auto check6 = bind(check_size, _1, 6);
//check6是一个可调用对象，接受一个string类型参数，并用其和6来调用check_size
//bind调用只有一个占位符，表示check6只接受单一参数
string s = "hello";  bool b1 = check6(s); //check(6)会调用check_size(s,6);
```

* 名字_n都定义在一个名为placeholders的命名空间中，这个命名空间本身又定义在std命名空间中

```c++
using std::placeholders::_1;
using namepsace std::placeholders; //这样就可以直接使用_n这个占位符名字了
```

```c++
auto g = bind(f, a, b, _2, c, _1 );
g(_1, _2)被映射为 f(a,b,_2,c,_1)
```

* 用bind重排参数顺序

```c++
sort( words.begin(), words.end(), isShorter); //单词长度由短至长
sort( words.begin(), words.end(), bind(isShorter, _2, _1) );//单词长度由长至短
```

* 绑定引用参数

  * 默认情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中，但有时候要绑定的参数类型无法拷贝，就需要绑定引用参数了
  * 如希望传递给bind一个对象而又不拷贝它，必须使用标准库ref函数

  ```c++
  for_each( words.begin(),words.end(), 
           bind(print, ref(os), _1, ' ') );
  //ref返回一个对象，包含给定的引用，此对象可以拷贝 cref生成的是保存const引用的类
  //ref cref也保存在functional中
  ```

  













































## 第12章 动态内存

### 12.1 动态内存与智能指针

* 局部static对象在第一次使用前分配，在程序结束时销毁。局部自动对象，当进入其定义所在的程序时被创建，离开块时销毁。
* c++支持动态分配对象。动态分配的对象的生存期与它们在哪里创建无关，只有当显式地被释放，这些对象才会销毁。
* 动态对象的正确释放极易出错，所以标准库定义来两个智能指针类型来管理动态分配的对象。当一个对象应该被释放时，指向它的智能指针可以确保自动地释放它。
* 分配在静态内存（static关键字定义的变量/数据成员）或者栈内存中的对象由编译器自动创建和销毁。除了静态内存和栈内存，程序中还有一个自由空间成为堆。程序用堆来存储动态分配的对象。动态对象的生存期由程序控制，即当我们不再用它时，我们的代码必须显示地销毁它们。

* 运算符new 在动态内存中为对象分配空间并返回一个指向该对象的指针
* 运算符delete接受一个动态对象的指针，销毁该对象，并且释放与之相关的内存

`动态内存使用易出问题！`

 * 忘记释放内存，就会出现内存泄漏

 * 在还有指针引用时，释放它，就会产生引用非法内存的指针

   ![pic3](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic3.png)

#### 12.1.1 shared_ptr类

坚持只使用智能指针

![pic4](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic4.png)

![pic5](/Users/yannie/Desktop/cpp_learning/c++primer/pic/pic5.png)





### 12.2 动态数组

* 当容器需要重新分配内存时，必须一次性为很多元素分配内存。大多数应用应该使用标准库容器，而不是动态分配的数组，因为不容易出现内存管理错误并且有更好的性能。
* 使用new分配一个对象数组

```c++
int *p = new int[get_size()]; //使用方括号   动态数组并不是数组类型
//我们使用new分配一个数组时，并未得到一个数组类型的对象，而是得到一个数组元素类型的指针
delete [] p;
```

* 使用一个元素初始化器的花括号列表

```c++
int *p3 = new int[10]{1,2,3,4,5,6,7,8,9,0};
```

* 使用unique_ptr来管理动态数组

```c++
unique_ptr<int[ ]> up( new int[10] );
up.release(); //自动用delete[]销毁其指针
```

#### 12.2.2 allocator类

* 希望将内存分配和对象构造分离。这意味着可以分配大块内存，但只在真正需要时才真正执行对象创建操作。
* new 将内存分配和对象构造组合在一起可能会导致不必要的浪费。
* allocator是一个模版  当一个allocator对象分配内存时，它会根据给定的对象类型来确定恰当的内存大小和对齐位置

```c++
allocator<string> alloc;  //可以分配string的allocator对象
auto const p = alloc.allocate(n); //分配n个未初始化的string
```

* allocator的construct成员函数接受一个指针和零个或多个额外参数，在给定位置构造元素，额外参数用来初始化构造的对象。为了使用allocate返回的内存，我们必须使用construct构造对象。使用未构造的内存，其行为是未定义的。

  

























