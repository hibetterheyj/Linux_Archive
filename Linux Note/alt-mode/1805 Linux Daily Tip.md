### 1805 Linux Daily Tip

---

#### <u>180527</u>

- **Install Typora**

**facing the problem**

```bash
~$ sudo apt-get install typora
Reading package lists... Done
Building dependency tree       
Reading state information... Done
E: Unable to locate package typora
```

**I do the following:**

```bash
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys BA300B7755AFCFAE
sudo apt-get install typora
```

reference link: <https://typora.io/#linux>

- **Install git and add ssh**

```
sudo apt-get install git
git config --global user.name "hibetterheyj"
git config --global user.email "hyj1997wshhz@163.com"
git config --list
ssh-keygen -t rsa -C "hyj1997wshhz@163.com"
cat /home/philhe/.ssh/id_rsa.pub
```

reference link: https://blog.csdn.net/qq_26990831/article/details/51857399

- **Install Chromium**

Open Ubuntu to install  Chromium freely.

- **Install SougouPInyin**

Open the folder where the package is, and click twice!

reference link: 

1. https://www.cnblogs.com/darklights/p/7722861.html
2. https://pinyin.sogou.com/linux/
3. https://pinyin.sogou.com/linux/help.php

- Install Nixnote

Click Twice to open the installer

reference link: https://sourceforge.net/projects/nevernote/?source=typ_redirect

- **Install Shadowsocks**

https://blog.csdn.net/ddyyll988/article/details/54566201

https://addons.mozilla.org/zh-CN/firefox/addon/foxyproxy-standard/

推荐谷歌访问助手：http://www.ggfwzs.com/

- **Install Tim Related**

reference: https://github.com/askme765cs/Wine-QQ-TIM

------

#### <u>180531</u>

- **Install Tree**

`sudo apt-get install tree`

- **Learning ROS**

reference link: 

1. gitbook: https://sychaichangkun.gitbooks.io/ros-tutorial-icourse163/content/
2. github: https://github.com/DroidAITech/ROS-Academy-for-Beginners
3. mooc: https://www.icourse163.org/course/ISCAS-1002580008#/info

- **Apply Screenshot**

```
gnome screenshot －a
自由选定屏幕截图
```

