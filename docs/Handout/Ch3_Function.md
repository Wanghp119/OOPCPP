# 第三章 函数
## 1. Lecture
正如前面第一次课所述，学习C++的方法，就是要在理解的基础上实践。本章介绍函数的相关内容，我们从Why、What、How三个角度来解释函数。
### 1.1 为什么需要函数？ - Why
我们知道，程序有一个很重要的目的——**复用**。为了达到*复用* 这个目的，在程序设计领域发明了很多种方法和技术，*函数*就是其中之一。函数实质上是面向过程遗留下来的“宝贝”，函数也是对象实现的重要组成部分。试想，在程序里可能会有某个过程是重复被使用，如果每次需要使用的时候，我们就写一段源代码，这样岂不是很浪费精力，而且还使得源代码变长，不好维护。

最最基本的函数就如数学上的函数，比如sin(x)，我们程序中可能会用到sin(0),sin(1),sin(2)...，我们是不是每次都写一个这样的函数呢？我们写一个函数sin(x)供调用，不是更合乎常理吗？

### 1.2 什么是函数？ - What
前述已经指出了使用函数的原因是 **复用** 。那么函数是什么呢？形象的说，函数就是提供一定功能的黑盒子。比如 **机顶盒** ，可以收看电视节目，其主要的功能就是将网络的信号转换为监视器能接收的视频和音频信号。 从 **机顶盒** 这个函数可以看出，函数所包含的内容，1）输入的网络信号；2）输出的视频和音频信号；3）解码的芯片。在这3大要素之中，我们可以看出一些端倪。如果你是一个使用机顶盒的用户，你需要关心 **3）解码芯片**吗？显然，你只需关心 **1）和2）**，哪里需要插入网线入口，哪里需要接视频和音频输出线，自此你就可以收看电视节目了。这个时候，机顶盒对你而言就是一个黑匣子，他干了什么我可以完全不必关心，而更多的只需要了解输入、输出接口是否连接正确。但如果你是一个机顶盒开发者，那么你就需要知道黑匣子里面的内容了。


### 1.3 如何实现自己的函数呢？ - How
根据前述的函数，你或许在考虑，我如何设计一个机顶盒呢？根据我们前面定义的三个要素，我们应该清楚，机顶盒函数应该包括：一个名字、输入参数、输出参数（返回值）。

机顶盒的函数是否可以写作： TVBox([intput]networks, [output]Video)呢？

实际的函数基本类似，只是我们用TVBox收看节目，要是有故障，是否需要返回一个错误码呢？这是有必要的，不然我们遇到问题了会非常费解，要是什么提示也没有，你会不会恨不得砸了不工作的机顶盒，所以这个时候机顶盒函数就变成了： int TVBox([intput]networks, [output]Video)，此处的int就是这个函数的返回值，也有些函数没有返回值，在c++语法里，没有返回值就是任意返回值，用void代替。

我们以第2章的判断闰年的例子，来简单示例函数的使用。
函数实现输出1-2000年中的所有闰年，示例代码如下：
```c++
#include <iostream>
int main()
{
	int		nYear;
	bool	bIsLeapYear;
	for (nYear=1; nYear<=2000; nYear++)
	{
		// 判断是否为闰年
		bIsLeapYear = (nYear%400==0) || (nYear%4==0 && nYear%100!=0);
		if (bIsLeapYear)
			std::cout << nYear << " is Leap Year." << endl;
	}
	return 0;
}
```

我们改写判断闰年的函数
```c++
#include <iostream>
// 判断是否为闰年
bool IsLeapYear(int nYear)
{ 
	return ((nYear%400==0) || (nYear%4==0 && nYear%100!=0));
}

int main()
{
	int		nYear;
	bool	bIsLeapYear;
	for (nYear=1; nYear<=2000; nYear++)
	{
		// 判断是否为闰年，调用IsLeapYear函数
		if (IsLeapYear(nYear))	// 用函数来替换
			std::cout << nYear << " is Leap Year." << endl;
	}
	return 0;
}
```


### 1.4 [课件下载](./PDFs/c%2B%2B3.pdf)

## 2. References

## 3. Exercises
1. 掌握本章例题： 输入源代码，编译程序、调试执行、输出正确
2. 完成课后习题：3-7、3-8、3-9、3-10、3-12、3-13、3-14、3-15
- **源代码发邮件**<cugwhp@qq.com>
- **为实习<2>做好前期准备，准备好上述课后习题的源代码.**

---
> [返回主目录](https://cugwhp.github.io/OOPCPP/) | [***上一章 C++程序设计***](./Ch2_C++Basic.md) | [下一章]()
---