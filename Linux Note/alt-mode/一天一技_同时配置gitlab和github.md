## 一天一技_同时配置gitlab和github

##### 配置流程

###### 1. 配置 Git 用户名、邮箱

```
# 全局配置，Github仓库中默认使用此配置
git config --global user.name 'ciqing' && git config --global user.email 'championzhang007@gmail.com' 
# 团队项目配置，每次新创建一个项目，需要执行下
git init
git config --local user.name 'PhilHE' && git config --local user.email 'hyj.academic@outlook.com' 
```

###### 2.生成 ssh key 上传到 Github/Gitlab

ssh key 默认生成后保存在 ~/.ssh/目录下 ，默认为 id_rsa 和 id_rsa.pub 两个文件，由于我们需要分开配置，所以这么做：

```
# 生成公钥、密钥的同时指定文件名，Gitlab使用
ssh-keygen -t rsa -f ~/.ssh/id_rsa.gitlab -C "hyj.academic@outlook.com"
# 生成默认，Github使用
ssh-keygen -t rsa -C "championzhang007@gmail.com"
```

命令执行完成后，这时`~/.ssh`目录下会多出`id_rsa.gitlab`和`id_rsa.gitlab.pub`两个文件，`id_rsa.gitlab.pub`里保存的就是我们要使用的key，这个key就是用来上传到 Gitlab上的。

###### 3.配置 config 文件

在 `~/.ssh`目录下，如果不存在，则新建 `touch ~/.ssh/config`文件 ，文件内容添加如下：

```
Host *intra.xxx.com
     IdentityFile ~/.ssh/id_rsa.gitlab
     User zhangguanjun
```

配置完成后，符合 `intra.xxx.com`后缀的 Git 仓库，均采取`~/.ssh/id_rsa.gitlab` 密钥进行验证，其它的采取默认的。

###### 4.上传public key 到 Github/Gitlab

以Github为例，过程如下：

登录github
 点击右上方的Accounting settings图标
 选择 SSH key
 点击 Add SSH key
 在出现的界面中填写SSH key的名称，填一个你自己喜欢的名称即可，然后将上面拷贝的~/.ssh/id_rsa.pub文件内容粘帖到key一栏，在点击“add key”按钮就可以了。

添加过程github会提示你输入一次你的github密码 ，确认后即添加完毕。 上传Gitlab的过程一样，请自己操作。

###### 5.验证是否OK

由于每个托管商的仓库都有唯一的后缀，比如 Github的是 `git@github.com:*`，所以可以这样测试：

```
➜  ~  ssh -T git@github.com
Hi ciqing! You've successfully authenticated, but GitHub does not provide shell access.
➜  ~  ssh -T git@gitlab.dev
Welcome to GitLab, zhangguanjun!
```

看到这些`Welcome` 信息，说明就是 OK的了。



简书链接：https://www.jianshu.com/p/cbb7117986d8
