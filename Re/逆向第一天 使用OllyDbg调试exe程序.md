## 逆向第一天 使用OllyDbg调试exe程序

1. 使用OllyDbg打开程序后，暂停在位置：FE12C8，此处是程序执行的起始位置，EP（入口点），是一段程序的EP代码，call与jump指令

![1566993764828](../noteimage/1566993764828.png)

2. 使用F7（step in）执行call指令，进入到被调用函数内部，FE1748，是被调用函数的第一条指令

![1566993845907](../noteimage/1566993845907.png)

3. 使用Ctrl-F9执行到return，然后f7或者f8退出当前接口函数
4. 继续F7执行，如果能确定调用的函数是API函数而不是main函数，可直接使用F8直接跳过
5. 一直F8直到到达main的call语句，然后F7进入，进入之后可以看到在调用窗口函数之前进行了数据压栈，四个参数，如图：

![1566999995462](../noteimage/1566999995462.png)

6. 找到了MessageBox函数使用的字符串保存的地址，然后CTRL+G，进行跟随，输入地址，在下方可以看到其在机器码中的对应位置，选中之后可以修改

   ![1567000585954](../noteimage/1567000585954.png)

修改之后继续执行。Ctrl+F9，调到main的return处，然后F7久执行完整个程序。看到弹出窗口数据已经被改变
