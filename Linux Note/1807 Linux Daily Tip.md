### 1807 Linux Daily Tip

------

#### <u>180717</u>

- **Install roboware studio**

```
$ cd /path/to/deb/file/
$ sudo dpkg -i roboware-studio_<version>_<architecture>.deb
```

- **安装chrome**

```
232  sudo wget http://www.linuxidc.com/files/repo/google-chrome.list -P /etc/apt/sources.list.d/
  233  wget -q -O - https://dl.google.com/linux/linux_signing_key.pub  | sudo apt-key add -
  234  sudo apt-get update
  235  sudo apt-get install google-chrome-stable
  236  /usr/bin/google-chrome-stable
```

