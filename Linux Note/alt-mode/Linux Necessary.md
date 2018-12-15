## Linux Necessary | 必备的几件事

---

> 以上想法来源：[安装完ubuntu 16.04 LTS后要做的11件事](https://www.bilibili.com/video/av4947544/)
>
> Thanks to https://www.youtube.com/watch?v=CwSOY9eB_6M
>
> Attention!!! Pls don't do **Step3: Install Video Graphics Driver**, or Ubuntu will crash!

- Update and Uninstall | 更新与卸载

```bash
sudo apt-get upgrade
sudo apt-get update
sudo apt-get dist-upgrade
sudo apt autoremove
```

- Install Unity Tweak Tool

```bash
sudo apt install unity-tweak-tool
```

- Improve Ubuntu's Appeal 调整与提升Ubuntu的感官体验

numix theme and icon | numix主题与软件包

```bash
sudo add-apt-repository ppa:numix/ppa
sudo apt-get update
sudo apt-get install numix-gtk-theme numix-icon-theme-circle
```

- Arc Theme

you can see at https://github.com/horst3180/Arc-theme

- install media codecd | 视频解码器

```
sudo apt-get install ubuntu-restricted-extras
```

Use `Tab` to choose bottom on the terminal

- Change Auto Screen Lock Settings | 改变自动熄屏时间
- Enable "Minimise on Click" | 点击任务栏最小化？
- **Change Where App Menus Show Up | 改变应用名字显示位置！**

