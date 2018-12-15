### 1806 Linux Daily Tip

------

#### <u>180616</u>

- **Install on-my-zsh**

https://github.com/robbyrussell/oh-my-zsh/wiki/Installing-ZSH

**Zsh Should be installed first!**

```shell
$ sudo apt-get install zsh
$ zsh --version
Make it your default shell
$ chsh -s $(which zsh)
/bin/zsh
$ $SHELL --version
```

https://github.com/robbyrussell/oh-my-zsh

```shell
sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
```

主题：https://github.com/robbyrussell/oh-my-zsh/wiki/themes

```shell
％更换主题
$ cd ~/.oh-my-zsh/themes
$ cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc
$ gedit ~/.zshrc
％　将ZSH_THEME="robbyrussell"后面进行更改！变为
```

插件：https://github.com/robbyrussell/oh-my-zsh/tree/master/plugins

```BASH
zsh 配置 ROS
$ echo "source /opt/ros/indigo/setup.zsh" >> ~/.zshrc
$ source ~/.zshrc
```

ROS 1 ---- 在zsh中安装ros: https://blog.csdn.net/qq_23225073/article/details/70137981

官网：http://ohmyz.sh/

中文介绍：

https://www.jianshu.com/p/ceb3f3bad95b 

https://blog.csdn.net/hsd2012/article/details/54292192

- **Install powerline for zsh/vim**（存疑）

```
pip install --user powerline-status
sudo apt-get install fonts-powerline
```

官网：https://github.com/powerline/powerline

- **Install thefuck**

https://github.com/nvbn/thefuck

```
sudo apt update
sudo apt install python3-dev python3-pip
sudo pip3 install thefuck
%%% 最终测试完毕，成功
$ pip3 install thefuck
```

- **Install Wiz Note**

http://www.wiz.cn/download.html

所下载的绿色版文件为`.AppImage`的文件格式，按照官方所提供的`sudo apt install openssl1.0 libssl1.0-dev`无法执行；

网上寻找关于上述文件格式的官网，根据tutorial可以得出根据以下操作即可

```bash
%%% 第一步：打开下载文件所在文件夹，并打开终端
%%% 第二步：输入下述指令
$ chmod a+x *.AppImage
$ ./*.AppImage
%%% PS:若文件中存在其他相同格式，则需将*替换为全名！
```

- **Upgrade pip & pip3**（存疑）

```shell
$ sudo apt-get install python-pip
$ pip install -U pip
%%% 下载无法至最新版
$ python -m pip install -U pip
$ pip3 --version
```

- **wget & curl 使用**





