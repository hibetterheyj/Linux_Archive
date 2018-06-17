## Linux Error Collection I

```
Update Log:
1806 first setup
180616 adding 2
```

---

### I. when install something

```bash
E: Could not get lock /var/lib/dpkg/lock - open (11: Resource temporarily unavailable)
E: Unable to lock the administration directory (/var/lib/dpkg/), is another process using it?
```

**Solution or References:**

- https://www.linuxidc.com/Linux/2014-06/103437.htm
- http://www.cnblogs.com/leijiangtao/p/4509519.html
- http://blog.163.com/cobyeah@126/blog/static/140137653201142354756503/

### II.由于已经达到 MaxReports 限制，没有写入 apport 报告。

包冲突或者是没卸载干净造成的。解决办法如下：

```
# cd /var/lib/dpkg  
# mv info/ info-bak  
# mkdir info  
# apt-get update  
# apt-get install -f

# mv info/* info-bak/  
# ls info  
# rm -rf info  
# mv info-bak/ info
```

