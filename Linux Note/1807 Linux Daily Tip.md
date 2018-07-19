### 1807 Linux Daily Tip

------

#### <u>180717</u>

- **Install roboware studio**

```bash
$ cd /path/to/deb/file/
$ sudo dpkg -i roboware-studio_<version>_<architecture>.deb
```

- **安装chrome**

```bash
$ sudo wget http://www.linuxidc.com/files/repo/google-chrome.list -P /etc/apt/sources.list.d/
$ wget -q -O - https://dl.google.com/linux/linux_signing_key.pub  | sudo apt-key add -
$ sudo apt-get update
$ sudo apt-get install google-chrome-stable
$ /usr/bin/google-chrome-stable
```

#### <u>180719</u>

- **Install Terminator**

安装并打开配置文件

```bash
$ sudo add-apt-repository ppa:gnome-terminator
$ sudo apt-get update
$ sudo apt-get install terminator

$ cd ~/.config/terminator/ && sudo gedit config
```

编辑配置文件

```
[global_config]
  title_transmit_bg_color = "#d30102"
  focus = system
  suppress_multiple_term_dialog = True
[keybindings]
[profiles]
  [[default]]
    palette = "#2d2d2d:#f2777a:#99cc99:#ffcc66:#6699cc:#cc99cc:#66cccc:#d3d0c8:#747369:#f2777a:#99cc99:#ffcc66:#6699cc:#cc99cc:#66cccc:#f2f0ec"
    background_color = "#2D2D2D" # 背景颜色
    background_image = None   
    background_darkness = 0.85 
    cursor_color = "#2D2D2D" # 光标颜色
    cursor_blink = True # 光标是否闪烁
    foreground_color = "#EEE9E9" # 文字的颜色
    use_system_font = False # 是否启用系统字体
    font = Ubuntu Mono 13  # 字体设置，后面的数字表示字体大小
    copy_on_selection = True # 选择文本时同时将数据拷贝到剪切板中
    show_titlebar = False # 不显示标题栏，也就是 terminator 中那个默认的红色的标题栏
[layouts]
  [[default]]
    [[[child1]]]
      type = Terminal
      parent = window0
      profile = default
    [[[window0]]]
      type = Window
      parent = ""
[plugins]
```

参考：

1. [terminator 安装与配置](https://blog.csdn.net/ipatient/article/details/51547658)
2. [ubuntu安装增强版终端Terminator](https://blog.csdn.net/chinabhlt/article/details/8766806)



