## My Linux Improvement Log

---

```
My Linux Update Log:
20180526 First Setup
20180527 install ROS and related software!
```

---

> Maybe a little similar to the last note!

### 基础提升！

- **Update and Uninstall | 更新与卸载**

    sudo apt-get upgrade
    sudo apt-get update
    sudo apt-get dist-upgrade
    sudo apt autoremove

- **Change Where App Menus Show Up | 改变应用名字显示位置！**

---

### 安装软件

- **Install Unity Tweak Tool**

    sudo apt install unity-tweak-tool

- **Improve Ubuntu's Appeal 调整与提升Ubuntu的感官体验**

numix theme and icon | numix主题与软件包

    sudo add-apt-repository ppa:numix/ppa
    sudo apt-get update
    sudo apt-get install numix-gtk-theme numix-icon-theme-circle

- **Install Typora**
- **Install git and add ssh**
- **Install Chromium**
- **Install Sougoupinyin**
- **Install ROS!**

---

### 改变安装带来的坑爹

- **Change Resolution | 改变分辨率**

One-time

```
sudo vim /etc/default/grub
搜索 #1GRUB_GFXMODE=640x480
修改640x480并且去掉#成你想要的分辨率如1024x768
最后 sudo update-grub
reboot
```

**vim/vi: http://www.runoob.com/linux/linux-vim.html**

still some problem but no damage:

```
none of the selected modes were compatible with the possible modes:
Trying modes for CRTC 622
CRTC 622: trying mode 1024x768@76Hz with output at 800x600@75Hz (pass 0)
CRTC 622: trying mode 1024x768@76Hz with output at 800x600@75Hz (pass 1)
```

references:

1. https://askubuntu.com/questions/681821/monitor-resolution-reseted-after-reboot-one-monitor
2. https://jingyan.baidu.com/article/d45ad148a269b969552b80e4.html
3. https://blog.csdn.net/ghostyusheng/article/details/52641843
4. https://blog.csdn.net/u013764485/article/details/78007370

[**解决Nvidia显卡的电脑安装Ubuntu及驱动的各种坑**](https://blog.csdn.net/ysy950803/article/details/78507892)

**https://blog.csdn.net/cosmoshua/article/details/76644029**

- `aspi_osi=linux nomodeset` related

https://zhidao.baidu.com/question/431573582369695444.html 方法二，解决方法同上