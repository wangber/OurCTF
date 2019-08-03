# CTF 5月第一期

[TOC]



## flag在index里

<http://123.206.87.240:8005/post/>

文件包含漏洞

`http://123.206.87.240:8005/post/index.php?file=show.php`

构造url`http://120.24.86.145:8005/post/index.php?file=php://filter/read=convert.base64-encode/resource=index.php`

查看源码：

```HTML
<html>
    <title>Bugku-ctf</title>
    
<?php
	error_reporting(0);
	if(!$_GET[file]){echo '<a href="./index.php?file=show.php">click me? no</a>';}
	$file=$_GET['file'];
	if(strstr($file,"../")||stristr($file, "tp")||stristr($file,"input")||stristr($file,"data")){
		echo "Oh no!";
		exit();
	}
	include($file); 
//flag:flag{edulcni_elif_lacol_si_siht}
?>
</html>

```



解释url含义：

```
这是一个file关键字的get参数传递，php://是一种协议名称，php://filter/是一种访问本地文件的协议，/read=convert.base64-encode/表示读取的方式是base64编码后，resource=index.php表示目标文件为index.php。

通过传递这个参数可以得到index.php的源码，下面说说为什么，看到源码中的include函数，这个表示从外部引入php文件并执行，如果执行不成功，就返回文件的源码。

而include的内容是由用户控制的，所以通过我们传递的file参数，是include（）函数引入了index.php的base64编码格式，因为是base64编码格式，所以执行不成功，返回源码，所以我们得到了源码的base64格式，解码即可。

如果不进行base64编码传入，就会直接执行，而flag的信息在注释中，是得不到的
--------------------- 
作者：安~然 
来源：CSDN 
原文：https://blog.csdn.net/zpy1998zpy/article/details/80585443 
版权声明：本文为博主原创文章，转载请附上博文链接！
```

参考wp:

https://blog.csdn.net/zpy1998zpy/article/details/80585443

## 变量1（代码审计）

```php

http://120.24.86.145:8004/index1.php
flag In the variable ! <?php   
 
 
error_reporting(0);                    // 关闭php错误显示
include "flag1.php";                   // 引入flag1.php文件代码
highlight_file(__file__);              //对文件进行语法高亮显示
if(isset($_GET['args'])){              // 条件判断 get方法传递                                         的args参数是否存在 
    $args = $_GET['args'];             //赋值给变量  $args
    if(!preg_match("/^\w+$/",$args)){  // /^开始, \w表示任意一个单词字符，即[a-zA-Z0-9_] ,+将前面的字符匹配一次或多次，$/结尾
        
        die("args error!");            //输出 args error! 
    }
    eval("var_dump($$args);");         // 将字符串作为php代码执行结尾加分号 var_dump()函数 显示关于一个或多个表达式的结构信息，包括表达式的类型与 值。数组将递归展开值，通过缩进显示其结构。$$args 可以理解为$($args)
}
?>
```

var_dump()函数 显示关于一个或多个表达式的结构信息包括表达式的类型与值

* 可变变量

![img](D:\Desktop\webclass\note\Center)

我们想到构造   php中超全局变量 $GLOBALS  ，PHP 在名为 $GLOBALS[index] 的数组中存储了所有全局变量。变量的名字就是数组的键。

参考：

https://blog.csdn.net/xuchen16/article/details/82737194

https://blog.csdn.net/anjiaowangmenghan/article/details/76460872

## 网站被黑

关于后台shell(参考百度百科)

```
webshell就是以asp、php、jsp或者cgi等网页文件形式存在的一种命令执行环境，也可以将其称做为一种网页后门。黑客在入侵了一个网站后，通常会将asp或php后门文件与网站服务器WEB目录下正常的网页文件混在一起，然后就可以使用浏览器来访问asp或者php后门，得到一个命令执行环境，以达到控制网站服务器的目的。
顾名思义，“web”的含义是显然需要服务器开放web服务，“shell”的含义是取得对服务器某种程度上操作权限。webshell常常被称为入侵者通过网站端口对网站服务器的某种程度上操作的权限。由于webshell其大多是以动态脚本的形式出现，也有人称之为网站的后门工具。
```

扫描后台，得到其后台网页 shell.php

进入后台网页后，利用burp自带字典爆破即可得到密码。

## 管理员系统

这是一个XXF问题

XFF:

```
X-Forwarded-For(XFF)是用来识别通过HTTP代理或负载均衡方式连接到Web服务器的客户端最原始的IP地址的HTTP请求头字段。通俗来说，就是浏览器访问网站的IP。获取http请求段真实的ip。
```

通过伪造XFF头绕过服务器ip过滤

源码的最最最最后有base64加密的管理员密码。

burp抓包修改XFF头重放，获得flag.

## 备份是个好习惯

在目录中某个文件的.bak文件可以访问

尝试访问index.php.bak

得到源码：

```php
<?php
/**
 * Created by PhpStorm.
 * User: Norse
 * Date: 2017/8/6
 * Time: 20:22
*/

include_once "flag.php";
ini_set("display_errors", 0);
$str = strstr($_SERVER['REQUEST_URI'], '?');
$str = substr($str,1);
$str = str_replace('key','',$str);
parse_str($str);
echo md5($key1);

echo md5($key2);
if(md5($key1) == md5($key2) && $key1 !== $key2){
    echo $flag."鍙栧緱flag";
}
?>

```

str_replace()只匹配一次，用kkeyey绕过匹配。

将获得两个key用MD5加密，然后比较，相同就输出flag.

## 成绩单

* 使用sqlmap进行post请求注入

  利用burp抓包，将包保存为txt文件，将txt文件通过-r 参数传给sqlmap，然后-p指定参数。其他的与get方式类似。

* 使用手工注入

  参考：https://blog.csdn.net/xuchen16/article/details/82785371

## 秋名山老司机

利用python抓取页面表达式并计算出值post回去。

参考代码：

```python
import requests
import re
k=0
while k<=20:
    k=k+1
    s =requests.Session()
    r =s.get("http://123.206.87.240:8002/qiumingshan/")
    searchObj = re.search(r'^<div>(.+)=\?;</div>$',r.text,re.M|re.S)#re.M|re.S匹配多行或匹配一行
    data = {
        "value":eval(searchObj.group(1))#这里是value是从网页提示中得到的
    }
    flag = s.post("http://123.206.87.240:8002/qiumingshan/",data=data)
    print(flag.text)

```

## 速度要快

利用脚本，提取请求头内部信息并利用base64解密，利用post传回参数得到post回应。参考：https://blog.csdn.net/destiny1507/article/details/82426436



