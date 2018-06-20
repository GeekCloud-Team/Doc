### Yum 命令用法

[yum](http://www.yanghengfei.com/tag/yum/)（全称为 Yellow dog Updater, Modified）是一个在Fedora和RedHat以及SUSE中的Shell前端软件包管理器。基於RPM包管理，能够从指定的服务器自动下载RPM包并且安装，可以自动处理依赖性关系，并且一次安装所有依赖的软体包，无须繁琐地一次次下载、安装。yum提供了查找、安装、删除某一个、一组甚至全部软件包的命令，而且命令简洁而又好记。

- yum的命令形式一般是如下：yum [options][command] [package ...]

>  其中的[options]是可选的，选项包括-h（帮助），-y（当安装过程提示选择全部为"yes"），-q（不显示安装的过程）等等。[command]为所要进行的操作，[package ...]是操作的对象。

概括了部分常用的命令包括：

- 自动搜索最快镜像插件：   yum install yum-fastestmirror
- 安装yum图形窗口插件：    yum install yumex
- 查看可能批量安装的列表： yum grouplist

#### 安装

```shell
yum install #全部安装

yum install package1 #安装指定的安装包package1

yum groupinsall group1 #安装程序组group1
```

#### 更新和升级

```shell
yum update #全部更新

yum update package1 #更新指定程序包package1

yum check-update #检查可更新的程序

yum upgrade package1 #升级指定程序包package1

yum groupupdate group1 #升级程序组group1
```

####  查找和显示

```shell
yum info package1 #显示安装包信息package1

yum list #显示所有已经安装和可以安装的程序包

yum list package1 #显示指定程序包安装情况package1

yum groupinfo group1 #显示程序组group1信息yum search string 根据关键字string查找安装包
```

####  删除程序

```shell 
yum remove package1; erase package1 #删除程序包package1

yum groupremove group1 #删除程序组group1

yum deplist package1 #查看程序package1依赖情况
```

#### 清除缓存

```shell
yum clean packages #清除缓存目录下的 headers

yum clean oldheaders #清除缓存目录下旧的 headers

yum clean, yum clean all (= yum clean packages; yum clean oldheaders) #清除缓存目录下的软件包及旧的headers
```



>  比如，要安装游戏程序组，首先进行查找：
>
> ```yum grouplist```
>
> 可以发现，可安装的游戏程序包名字是”Games and Entertainment“，这样就可以进行安装：
>
> ``` yum groupinstall "Games and Entertainment"```
>
> 所有的游戏程序包就自动安装了。在这里Games and Entertainment的名字必须用双引号选定，因为linux下面遇到空格会认为文件名结束了，因此必须告诉系统安装的程序包的名字是“Games and Entertainment”而不是“Games"。
>
> 此外，还可以修改配置文件/etc/yum.conf选择安装源。可见yum进行配置程序有多方便了吧。更多详细的选项和命令，当然只要在命令提示行下面:man yum

```shell
# 更多样例
yum groupinstall "KDE (K Desktop Environment)"

yum install pirut k3b mikmod

yum groupinstall "Server Configuration Tools"

yum groupinstall "Sound and Video"

#yum groupinstall "GNOME Desktop Environment"

yum groupinstall "Legacy Software Support"

yum groupinstall "Development Libraries"

yum groupinstall "Development Tools"

#yum groupinstall "Windows File Server"

yum groupinstall "System Tools"

yum groupinstall "X Window System"

yum install php-gd

yum install gd-devel

yum groupinstall "Chinese Support"

#yum install samba-common  //该执行会一起安装 samba-client

#yum install samba

yum install gcc

yum install cpp

yum install gcc-c++

yum install ncurses

yum install ncurses-devel

yum install gd-devel php-gd

yum install gd-devel

yum install gcc

yum install cpp

yum install gcc-c++

yum install ncurses

yum install ncurses-devel

yum install gd-devel php-gd

yum install gd-devel

yum install zlib-devel

yum install freetype-devel freetype-demos freetype-utils

yum install libpng-devel libpng10 libpng10-devel

yum install libjpeg-devel

yum install ImageMagick

yum install php-gd

yum install flex

yum install ImageMagick-devel

#yum install system-config-bind         

#yum groupinstall "DNS Name Server"      //安裝 bind 及 bind-chroot 套件

yum groupinstall "MySQL Database"'

yum clean all
```

>  装了个fedora linux不能用中文输入是一件很棘手的事，连搜解决方案都没法搜。只能勉强用几个拼音碰碰运气，看Google能不能识别了。而我就遇见了这样的事。
>
> 解决方案：
>
> ```shell yum install scim* -y ```

下面简单的对这一文件作简要的说明：

- cachedir：yum缓存的目录，yum在此存储下载的rpm包和数据库，一般是/var/cache/yum。

- debuglevel：除错级别，0──10,默认是2

- logfile：yum的日志文件，默认是/var/log/yum.log。

- exactarch，有两个选项1和0,代表是否只升级和你安装软件包cpu体系一致的包，如果设为1，则如你安装了一个i386的rpm，则yum不会用686的包来升级。

- gpgchkeck= 有1和0两个选择，分别代表是否是否进行gpg校验，如果没有这一项，默认好像也是检查的。

  



#### 安装最快源 yum install yum-fastestmirror

资源真的是非常丰富，从Centos到Ubuntu，ISO镜像、升级包，应有尽有，上交的兄弟们真是幸福，羡慕啊。不过还好，我们好歹也算是在教育网内，凑合着也可以沾点光，下载一些。
网址为：<ftp://ftp.sjtu.edu.cn/>

相应的yum的repo为
[updates]
name=Fedora updates
baseurl=ftp://ftp.sjtu.edu.cn/fedora/linux/updates/$releasever/$basearch/
enabled=1
gpgcheck=0
[fedora]
name=Fedora $releasever - $basearch
baseurl=ftp://ftp.sjtu.edu.cn/fedora/linux/releases/$releasever/Everything/$basearch/os/
enabled=1
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-fedora <file:///etc/pki/rpm-gpg/RPM-GPG-KEY>

如果在机器上安装了apt管理器，则相应的源为
repomd <ftp://ftp.sjtu.edu.cn/> fedora/linux/updates/$(VERSION)/$(ARCH)/

repomd <ftp://ftp.sjtu.edu.cn/> fedora/linux/releases/$(VERSION)/Everything/$(ARCH)/os/

