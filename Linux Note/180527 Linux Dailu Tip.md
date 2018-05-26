### 180527 Linux Dailu Tip

---

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



