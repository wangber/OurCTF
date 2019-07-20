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
