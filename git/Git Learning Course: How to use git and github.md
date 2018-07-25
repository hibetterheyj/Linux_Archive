## Git Learning Course: How to use git and github

---

> 如何使用 Git 和 GitHub：[课程地址](https://cn.udacity.com/course/how-to-use-git-and-github--ud775)
>
> 完结于20180603

### 发现区别 | git diff

```
git log 查看历史
git diff <ID1> <ID2>
git --version 查看版本
```



### 克隆和探索版本库

```bash
克隆版本库
要克隆版本库，请运行 git clone（后跟空格和版本库 URL）。

Asteroids URL
使用以下 URL 克隆 Asteroids 版本库：https://github.com/udacity/asteroids.git

退出 git log
要停止查看 git log 的输出，请按 q（表示退出）。

$ cd asteriods 即可进入clone下来的文件夹
$ ls -a 列出隐藏文件，即可发现`.git`文件
```



### 创建修改代码库ose_ekf/CMakeLists.txt:6 (pkg_check_modules

```bash
% 初始化文件夹
$ git init
% 添加文件到暂存区提
$ git add <file> 单一文件
$ git rm --cached <file> 将某文件删除出暂存区域staging area
$ git reset HEAD <file> 也可以写成这种形式
$ git status 查询文件夹中git状态
$ git commit -m "Commit message" 提交相关信息

$ git diff 可以直接查询未commit时，folder与staging area的区别
$ git diff --staged 可以直接查询已commit时，staging area与repo的区别
$ git diff commit1 commit2 可以查询最近两次commit的区别

$ git reset --hard 强制删除所有git add，无法撤消
```



### 创建、修改分支

```bash
$ git checkout master 确认master分支的状态
$ git branch
* master
$ git branch <new branch>
$ git checkout <new branch> 确认new branch分支的状态，并转移至new branch分支
$ git checkout -b <new branch> 两步并为一步

$ git log --graph --oneline master <other branch>
$ git push origin <new branch> 直接上传
$ git show 可以查看某一次commit与其父级的区别
```

[个性化你的 Git Log 的输出格式](https://ruby-china.org/topics/939)

推荐了两个绘图工具

- [gliffy](https://www.gliffy.com/)
- [yUML](http://yuml.me/diagram/activity/draw)



### 添加远程仓库

```bash
% Create a repo
$ git remote
origin %首个远程仓库标准命名
$ git remote add origin git@github.com:XXX.git
$ git remote -v %查看相关版本
$ git push origin master %提交相关变化
---
% When local is out-of-date
$ git pull origin master
```

Related LInk: [Caching your GitHub password in Git](https://help.github.com/articles/caching-your-github-password-in-git/)



### 协作

> 代码库协作需要先在github上面添加collaborator
>
> 相关[协作合并更改视频](https://classroom.udacity.com/courses/ud775/lessons/3105028581/concepts/33526188150923)

```bash
% 防止发生冲突，先获取后合并
$ git fetch origin master
$ git log -p master origin/master
$ git merge origin/master
% 直接相当于这句话
$ git pull origin master
```

？？？Fast-forward merge
