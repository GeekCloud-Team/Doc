
---
title: Docker-Primer
date: 2017-10-20 15:34:21
tags: docker
---


## 一、 Docker简介

Docker 是一个开源项目。

可以把它理解为是一种新兴的超轻量级虚拟化技术。

传统虚拟化技术需要模拟计算机的一整套硬件出来，而且还要有自己的一套操作系统。

而 Docker 却不需要，它只需要与主机共享同一个内核，并充分利用 Linux 上内核的“环境隔离方案”来实现轻量级的虚拟化。

它在一些特定场景下与传统虚拟化技术相比，效率大幅提高，而资源开销却大幅降低。

Docker 的迁移也是十分方便的，基本上只需要把整个 Docker 目录搬过去即可。

Docker 使用 服务器-客户端 架构。

如果想在 Docker 上运行 exe 软件的话，那不用看下去了，左转找 KVM 去吧。

## 二、理解 Docker 的结构
四个基本结构：容器（Container）、镜像（Image）、仓库（Repository）、注册点（Registry）。

看着一脸懵逼对吧！是的，这几个概念确实比较难理解。但是我用类比法还是把它搞明白了。

先想象一个无盘系统是怎么样的，下面我们用一般的无盘系统来类比。

### 2.1 镜像

无盘服务器硬盘内有各种软件。比如说有 Win 7，还有各类应用软件。

而这些软件是相互依赖的。比如微信需要装 Win 7 系统才能运行。

各个无盘计算机（容器）想要运行什么软件可以直接告诉无盘服务器。

无盘服务器会准备好一切所需软件，打成一个包（镜像），然后推送给无盘计算机。

假设整个无盘系统中只有两种包。一种包是 Win 7 & QQ，另一种包是 Win 7 & 微信。

但是无论这两种包有多少个，都不会占用额外的硬盘空间（利用 Union mount 实现镜像分层）。只有 Win 7（某个镜像层） 、QQ、微信 这三个软件会占用硬盘空间。

一个镜像是这样被标识的：<仓库名>:<标签名（版本号）> ，例如nginx:latest。如果不指定标签，默认为 latest。

### 2.2 容器

相当于无盘计算机。

无盘计算机启动（容器启动）时，要从无盘服务器上拉取所需文件。如果无盘计算机对硬盘有写入操作的话，写入的数据将保存到无盘服务器的缓存区（容器存储层）。

无盘计算机关机（容器停止）时，如果没有额外设置，所有保存到无盘服务器的缓存区的文件（容器存储层）都将丢失。除非另外保存在 U 盘等外接设备（数据卷）中。

各个无盘计算机之间的运行互不干扰。（利用 cgroups 、namespace 实现隔离）

### 2.3 仓库

相当于同一个软件所有版本的集合。

### 2.4 注册点

相当于一个应用商店。

无盘服务器会来这里查找并下载软件。

## 三、Docker安装


### 3.1 安装

Docker 有好几个版本，社区版（Community Edition）、企业基础版（Enterprise Edition Basic）、企业标准版（Enterprise Edition Standard）、企业高级版（Enterprise Edition Advanced）。对于我们一般学习使用而言，使用社区版就已足够，所以记住CE就可以了。

其次，我们会看到一堆平台特定的版本， `Docker for Mac `、` Docker for Windows `、 ` Docker Toolbox ` 、 ` Docker for Azure ` 、` Docker for AWS ` 等等，还有一堆不同 ` Linux ` 的发行版。那我们应该用哪个？其实不难选择，这都是平台特定的东西嘛，选择自己平台就完了：

* macOS 就选择 Docker for Mac；
    * 阿里云（未及时更新）：  https://mirrors.aliyun.com/docker-toolbox/mac/docker-for-mac/stable/
* Linux 就选择自己平台的 Docker 源：
    * Ubuntu: https://docs.docker.com/engine/installation/linux/docker-ce/ubuntu/
    * Debian: https://docs.docker.com/engine/installation/linux/docker-ce/debian/
    * CentOS: https://docs.docker.com/engine/installation/linux/docker-ce/centos/
    * Fedora: https://docs.docker.com/engine/installation/linux/docker-ce/fedora/
* Windows 要麻烦些：
    * 如果是 Windows 10 专业版、企业版、教育版，并且版本在 ` 10586 ` 以后，并且不打算在 Docker 运行同时再运行其它虚拟机的情况下，可以装 `  Docker for Windows ` 。 
        * 阿里云（未及时更新）：https://mirrors.aliyun.com/docker-toolbox/windows/docker-for-windows/stable/
    * 其它情况都装 Docker Toolbox
        * 阿里云：https://mirrors.aliyun.com/docker-toolbox/windows/docker-toolbox/
* 如果是特定云服务平台，可以考虑特定服务平台的版本（当然，这不是必须）：
    * AWS：Docker for AWS
    * Azure：Docker for Azure

最后是发布通道，从今年初开始，也就是从 ` 1.13 ` 以后，Docker 使用了新的版本号规则，将采用类似 Ubuntu 那种 ` <年>.<月> ` 的形式，比如 ` 17.03 ` , ` 17.06 ` 等。并且，将发布通道分为前沿版本(Edge)和稳定版本(Stable)。前沿通道将基本每个月发布一个版本，而稳定通道将基本每3个月发布一个版本。这样 Docker 的发布将有规律可寻。对于喜欢尝鲜的可以选择前沿版本，对于需要稳定的，可以选择稳定版本。

> 这里面需要注意的是，在参考官方安装文档 (中文)配置 Linux 源的时候，如果是国内服务器，要将其中的 `  https://download.docker.com/linux/ ` 替换为   ` https://mirrors.aliyun.com/docker-ce/linux/ `。

比如，文档如果要求执行下面的命令：

```bash
$ sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
```

那么就替换为：

```bash
$ sudo add-apt-repository \
   "deb [arch=amd64] https://mirrors.aliyun.com/docker-ce/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
```

这样安装 ` Docker `就会使用阿里云的软件源，而不需要翻墙了。

> （注：这不是加速器，不要搞错了，加速器依旧需要配！）


#### 是直接用 yum / apt-get 安装 Docker 吗？ 

#### 很多人问到 docker, docker.io, docker-engine 甚至 lxc-docker 都有什么区别？

其中，RHEL/CentOS 软件源中的 Docker 包名为 docker；Ubuntu 软件源中的 Docker 包名为 docker.io；而很古老的 Docker 源中 Docker 也曾叫做 lxc-docker。这些都是非常老旧的 Docker 版本，并且基本不会更新到最新的版本，而对于使用 Docker 而言，使用最新版本非常重要。另外，17.04 以后，包名从 docker-engine 改为 docker-ce，因此从现在开始安装，应该都使用 docker-ce 这个包。

> 不要使用操作系统提供的软件源中的 Docker 包，去使用 Docker 官方源的包。


#### 正确的安装方法有两种：

一种是参考官方安装文档去配置 apt 或者 yum 的源；
另一种则是使用官方提供的安装脚本快速安装。
官方文档对配置源的方法已经有很详细的讲解，这里就不赘述，需要的直接去看官方文档。这里只介绍使用官方的脚本快速安装：

* 17.04 及以后的版本 

从 17.04 以后，可以用下面的命令安装。

```shell
export CHANNEL=stable
curl -fsSL https://get.docker.com/ | sh -s -- --mirror Aliyun
```

这里使用的是官方脚本安装，通过环境变量指定安装通道为 stable，（如果喜欢尝鲜可以改为 edge, test），并且指定使用阿里云的源(apt/yum)来安装 Docker CE 版本。


* 17.03 及以前的版本


早期的版本可以使用阿里云或者 DaoCloud 老的脚本安装：

使用阿里云的安装脚本：

```shell
curl -sSL http://acs-public-mirror.oss-cn-hangzhou.aliyuncs.com/docker-engine/internet | sh -
```

使用DaoCloud的Docker安装脚本：
```bash
curl -sSL https://get.daocloud.io/docker | sh
```
#### 不是都已经发布 Docker 17.07 了么？我怎么升级到最新还是 17.05 呀？ 

从 17.04 以后，Docker 的源的结构以及包名都进行了调整，因此如果你你还使用的是旧的源，那么需要参照官方文档，更新源的地址为新的源。前面的问答中已经给出了链接和替代用的阿里云源镜像地址，参照修改（apt/yum）源。

修改好后，卸载旧的 docker-engine，安装新的 docker-ce 即可。

### 3.2 配置加速器

首先，要“感谢”伟大的墙及其亲属。

然后，我们可以使用 Docker 镜像加速器来解决这个问题，加速器就是镜像、代理的概念。国内有不少机构提供了免费的加速器以方便大家使用，这里列出一些常用的加速器服务：

* Docker 官方的中国镜像加速器：从2017年6月9日起，Docker 官方提供了在中国的加速器，以解决墙的问题。不用注册，直接使用加速器地址：` https://registry.docker-cn.com ` 即可。
中国科技大学的镜像加速器：中科大的加速器不用注册，直接使用地址 ` https://docker.mirrors.ustc.edu.cn/ ` 配置加速器即可。进一步的信息可以访问：` http://mirrors.ustc.edu.cn/help/dockerhub.html?highlight=docker `

* 阿里云加速器：注册阿里云开发账户(免费的)后，访问这个链接就可以看到加速器地址： ` https://cr.console.aliyun.com/#/accelerator `

* DaoCloud 加速器：注册 DaoCloud 账户(支持微信登录)，然后访问： ` https://www.daocloud.io/mirror#accelerator-doc `

注意：不要使用加速器网站所给的配置脚本，容易导致错误。我们只需获取其提供的加速器地址即可。

#### Ubuntu 14.04 配置加速器（或其它使用 Upstart 的系统） 

Ubuntu 14.04 是使用 upstart 进行系统初始化的，对于这类系统，可以用通过编辑配置文件的方法来配置加速器。

如果是 Ubuntu 14.04，那么编辑 ` /etc/default/docker ` ，在里面寻找 DOCKER_OPTS 环境变量设置的这一行，在其后添加  ` -–registry-mirror=<加速器地址> `。如果发现该行已被注释，或者不存在该行，那么新添一行即可。

比如，在使用官方源安装了 ` docker-engine ` 后，会建立一个默认的 `  /etc/default/docker `，其中相关 ` DOCKER_OPTS ` 的行是这样的：

```bash
# Use DOCKER_OPTS to modify the daemon startup options.
#DOCKER_OPTS="--dns 8.8.8.8 --dns 8.8.4.4"
```

假设我们的加速器地址为 ` https://registry.docker-cn.com `，我们添加一行配置，将其改为：
```bash
# Use DOCKER_OPTS to modify the daemon startup options.
#DOCKER_OPTS="--dns 8.8.8.8 --dns 8.8.4.4"
DOCKER_OPTS="--registry-mirror=https://registry.docker-cn.com"
```

保存文件后，重启 Docker 引擎：

```bash
$ sudo service docker restart
docker stop/waiting
docker start/running, process 3620
```

重启成功后，确认一下配置是否已经生效：
```bash
$ sudo ps -ef | grep dockerd
root      3620     1  0 04:26 ?        00:00:00 /usr/bin/dockerd --registry-mirror=https://registry.docker-cn.com --raw-logs
```
如果配置成功，生效后这里就会看到自己所配置的加速器的内容。

#### Ubuntu 16.04 或 CentOS 7 配置加速器（或其它使用 Systemd 的系统） 

Ubuntu 16.04 和 CentOS 7 这类系统都已经开始使用 systemd 进行系统初始化管理了，对于使用 systemd 的系统，应该通过编辑服务配置文件 docker.service 来进行加速器的配置。

在启用服务后
```bash
$ sudo systemctl enable docker
```
可以直接编辑 ` /etc/systemd/system/multi-user.target.wants/docker.service ` 文件来进行配置。
```bash
sudo vi /etc/systemd/system/multi-user.target.wants/docker.service
```
在文件中找到 ExecStart= 这一行，并且在其行尾添加上所需的配置。假设我们的加速器地址为 ` https://registry.docker-cn.com ` ，那么可以这样配置：
```bash
ExecStart=/usr/bin/dockerd --registry-mirror=https://registry.docker-cn.com
```

更多请参考官方文档：
` https://docs.docker-cn.com/engine/installation/linux/docker-ce/ubuntu/ `

## 四、运行第一个容器
### 4.1 运行 Helloworld 容器
```bash
    docker run hello-world
```
### 4.2 过程解析

- Docker 客户端向 Docker 守护进程发出运行命令。
>
- Docker 守护进程发现没有 hello-world 这个镜像，于是从仓库中寻找并下载它。
>
- 下载完毕之后，Docker 守护进程以 hello-world 这个镜像创建一个新的容器。
>
- 容器向 Docker 守护进程输出内容之后，容器停止。Docker 守护进程把输出的内容传递给 Docker 客户端。

## 五、Docker的基本操作

下面以创建一个 Ubuntu 系统的容器为例来了解一下 Docker 的基本操作。

为了方便理解，我把命令完整地写出来。

本节的命令参数只有最基本的参数，需要其他设置（如数据卷）的话会在后面讲到。

> PS:   Docker 命令支持自动补全

### 5.1 常用格式
```bash
    docker image pull [<注册点名>/]<仓库名>[:<标签名（版本号）>]
```

>若不指定注册点名，将使用默认的 library/。

>若不指定标签名，将使用默认的 latest。

例如 
```bash
    docker image pull ubuntu
```
执行结果
```bash
Using default tag: latest
latest: Pulling from library/ubuntu
d5c6f90da05d: Pull complete 
1300883d87d5: Pull complete 
c220aa3cfc1b: Pull complete 
2e9398f099dc: Pull complete 
dc27a084064f: Pull complete 
Digest: sha256:34471448724419596ca4e890496d375801de21b0e67b81a77fd6155ce001edad
Status: Downloaded newer image for ubuntu:latest
```
可以明显地看出，镜像被分为了多个块。523315523315

### 5.2 以某个镜像建立一个容器

常用格式
```bash
docker container create --interactive --tty [--name=<容器名>] <镜像名> [要运行的程序和参数]
```

- 如果不指定容器名，系统会自动为之分配一个无重复的容器名。

- 如果本地不存在指定的镜像，会自动从注册点中拉取。

> --interactive 表示持续为容器打开 stdin 以便随时接受操作。

> --tty 表示为容器分配一个伪终端，这样我们才可以方便的操作容器。

要运行的程序和参数 指定容器启动后要运行镜像里的哪一个程序。这个程序运行结束后，容器也会停止。如果不指定，则使用镜像的默认值。

例如

以 ubuntu 为镜像，建立一个名为 ubuntu_test 的容器
```bash
docker container create --interactive --tty --name=ubuntu_test ubuntu
```

执行结果
```bash
46cc818c92f0780ccd89811c12906c4527b554d18a61e72b0b2337b663ebab5f
```

> 这是自动生成的容器唯一长 ID。

### 5.3 启动一个容器

常用格式
```bash
docker container start <容器名> [容器名] [容器名] ...
```
可同时启动多个容器。

例如

启动刚才创建的 ubuntu_test 容器。
```bash
docker container start ubuntu_test
```
执行结果
```bash
ubuntu_test
```
返回容器名称，说明启动成功。

### 5.4 查看容器信息

常用格式
```bash
docker container ls [--all] [--no-trunc]
```
- 如果不加 --all 选项，则只显示运行中的容器。

> --no-trunc 表示完整显示容器的长 ID （形如 7.2 中命令的执行结果）。为了方便查看，一般不需要加此选项。

例如

查看本机所有容器的状态。
```bash
docker container ls --all
```
执行结果
```bash
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS                      PORTS               NAMES
#<容器ID>         <镜像名>               <命令参数>          <创建时间>          <状态>                        <打开的端口>         <容器名称>
d4bc3be9148d        hello-world         "/hello"            5 hours ago         Exited (0) 5 hours ago                          practical_rosalind
46cc818c92f0        ubuntu              "/bin/bash"         3 hours ago         Up 2 minutes                                    ubuntu_test
```
可以看到，除了刚创建的 ubuntu_test 容器之外，还有一个名为 practical_rosalind 容器。practical_rosalind 这个容器正是刚才运行 docker run hello-world 时生成的。

### 5.5 操作一个容器 & 容器内外进程简析

#### 5.5.1 操作一个容器

常用格式
```bash
docker container attach <容器名>
```
例如
```bash
docker container attach ubuntu_test
```
执行之后按几下回车，如果出现类似 root@46cc818c92f0:/# 的提示符，那说明您已经在容器内操作了。

我们来查看下系统的版本。
```bash
uname -a

Linux 46cc818c92f0 3.10.0-514.26.2.el7.x86_64 #1 SMP Tue Jul 4 15:04:05 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
```
好像看不出是 Ubuntu 系统，没关系，我们再执行下以下命令。
```bash
cat /etc/os-release

NAME="Ubuntu"
VERSION="16.04.3 LTS (Xenial Xerus)"
ID=ubuntu
ID_LIKE=debian
PRETTY_NAME="Ubuntu 16.04.3 LTS"
VERSION_ID="16.04"
HOME_URL="http://www.ubuntu.com/"
SUPPORT_URL="http://help.ubuntu.com/"
BUG_REPORT_URL="http://bugs.launchpad.net/ubuntu/"
VERSION_CODENAME=xenial
UBUNTU_CODENAME=xenial
```
好，已经确定了是在虚拟的 Ubuntu 系统中操作了！我们再来看一下容器内都有什么进程吧。

#### 5.5.2 容器内进程简析

在容器内执行以下命令：
```bash
ps aux
```
执行结果
```bash
USER PID %CPU %MEM VSZ  RSS TTY STAT START  TIME COMMAND
root 1 0.0 0.0 18304 2072 pts/0 Ss  05:19  0:00 /bin/bash
root 229 0.0 0.0 34416 1436 pts/0 R+  07:27  0:00 ps aux
```
可以看到，容器中目前只存在 bash 和刚开启的 ps 这两个进程，而且 bash 的 PID 为 1 ！

这说明了容器处在与实体机不同的 namespace 中，容器看不到实体机的进程。

容器进程数目与传统虚拟机的进程数目相比大幅减少了，所以说容器的效率非常高，启动基本上是毫秒级的！

#### 5.5.3 容器外进程简析

实体机可以看到容器内的进程吗？答案是可以的。

我们来看下实体机上的进程树。
```bash
systemd─┬─ModemManager───2*[{ModemManager}
        ├─dockerd─┬─docker-containe─┬─docker-containe─┬─bash
        │         │                 │                 └─8*[{docker-containe}]
        │         │                 └─12*[{docker-containe}]
        │         └─11*[{dockerd}]
#无关部分已省略
```
可以看出，bash 属于 dockerd 的子进程。

这说明了容器处在实体机的子 namespace 中，同时需要依赖实体机中的进程才可以运行。

所以，容器并不是完全的“虚拟化”。

### 5.6 从容器中脱开

前面 5.2 我们已经说过了：容器启动时会运行镜像里指定的应用程序，而这个程序运行结束后，容器也会停止。

现在这个容器启动时运行了镜像默认设定的的 /bin/bash ，所以当 /bin/bash 关闭时，容器就会跟着关闭。

如果直接按 Ctrl + D 退出容器操作的话，bash 就会退出而使整个容器停止运行，我们显然不希望这样。

正确的脱开方法是 先按 Ctrl+P 再按 Q （跟 Screen 的操作方法非常相似）。

执行完该操作之后，如果出现 read escape sequence ，就说明已经从容器中脱开了。

### 5.7 停止一个容器

常用格式
```bash
docker container stop <容器名>
```
执行完以上命令之后，实体机将向容器内所有的进程发送 SIGTERM 信号，然后给 10 秒的时间，让容器内的进程可以“优雅地”结束。

如果容器内的进程在 10 秒内没有结束，则实体机向未结束的进程发送 SIGKILL 信号来强制结束。

如果想立即强制结束容器的话把 stop 换成 kill 就行了。

例如
```bash
docker container stop ubuntu_test
```
执行结果
```bash
ubuntu_test
```
返回容器名称，说明容器已经停止。

### 5.8 删除一个容器

常用格式
```bash
docker container rm <容器名>
```
请注意：运行中的容器不能被删除。

例如

我们把刚才第一个使用 hello-world 镜像的容器给删掉，容器名从上面 5.4 中得到。
```bash
docker container rm practical_rosalind
```
执行结果
```bash
practical_rosalind
```
返回容器名称，说明容器已经删除。

### 5.9 查看镜像信息

常用格式
```bash
docker images [--all]
```
没有加 -all 的话将只显示顶层镜像，加了 -all 的话除了显示顶层镜像之外还会显示中间层（依赖）镜像。

例如
```bash
docker images
```
执行结果

这里我们顺便回顾一下，一个镜像是这样标识的： <仓库名>:<标签名（版本号）> 。
```bash
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
#<所在仓库>        <标签>               <镜像 ID>            <创建时间>          <大小>
ubuntu              latest              ccc7a11d65b1        4 weeks ago         120MB
hello-world         latest              1815c82652c0        2 months ago        1.84kB
```
### 5.10 删除一个镜像

常用格式
```bash
docker image rm <镜像名>
```
请注意：如果有基于要删除镜像的容器，则该镜像不能被删除。

例如

我们把刚才第一个下载的 hello-world:latest 镜像给删掉。
```bash
docker image rm hello-world:latest
```
执行结果
```bash
Untagged: hello-world:latest
Untagged: hello-world@sha256:f3b3b28a45160805bb16542c9531888519430e9e6d6ffc09d72261b0d26ff74f
Deleted: sha256:1815c82652c03bfd8644afda26fb184f2ed891d921b20a0703b46768f9755c57
Deleted: sha256:45761469c965421a92a69cc50e92c01e0cfa94fe026cdd1233445ea00e96289a
```
镜像已经删除。

### 5.11 使用一次性容器（推荐用于测试或开发环境）

上述步骤目的其实是为了让大家更好地理解 Docker 的结构。

我认为 Docker 有一个缺点，那就是容器一旦创建完成之后，想要修改配置就有点麻烦。而在测试或开发环境中，经常需要修改容器的配置。

好在，容器非常轻，完全可以做到“用时创建、用完即删”！

所以，我还是推荐大家使用以下命令，来做到容器创建、启动、删除三合一。

常用格式
```bash
docker container run --rm [--detach] --interactive --tty [--name=<容器名>] <镜像名> [要运行的程序和参数]
```

>--rm 表示容器停止之后删除容器。

>--detach 表示容器启动之后不进入容器内操作。

- 其他选项请参考 5.2。

执行完该命令之后，容器会自动创建然后启动。如果没有加入 --detach 选项，容器启动完成后会直接进入到容器中操作（可随时脱开）。

而容器停止之后，容器就会马上被删除，非常方便。

下文均使用一次性容器。

### 5.12 配置容器的自重启（推荐用于生产环境）

常用格式

在 5.2 或 5.11 的 --tty 后面插入如下格式的内容：
```bash
--restart on-failure|unless-stopped|always
```
有三种自重启方式。

>on-failure 表示容器停止时，若出现错误则自动重启（进程返回值不为 0）。在 Docker 服务重启时，不能自动重启。

>unless-stopped 表示容器停止时，若没有出现错误则自动重启（进程返回值为 0）。在 Docker 服务重启时，通常可以自动重启。

>always 表示一旦容器停止，都将自动重启。在 Docker 服务重启时，可以自动重启。

- 请注意，如果执行了 docker container stop 或者 docker container kill 命令，容器自重启将失效。

- --restart 不能和 --rm 同时使用，也就是说不适用于一次性容器。

### 5.13 查看容器的详细配置信息

把容器所有配置参数以 json 格式显示出来，这里只做了解。

常用格式
```bash
docker container inspect <容器名>
```
### 5.14 查看镜像的详细信息

把镜像所有参数以 json 格式显示出来，这里只做了解。

常用格式
```bash
docker image inspect <镜像名>
```
### 5.15 快速删除所有容器

常用格式
```bash
docker container rm $(docker container ls --all -q)
```
请注意：运行中的容器不能被删除。

## 六、保存容器中的数据

前面我们已经说过，容器一旦停止，容器内文件的所有改动都将丢失。

所以，我们必须指定一个可以存储数据的方法，才能保存容器内的数据。

### 6.1 使用数据卷

简单地说，数据卷就是在容器内指定一个目录，存储在这个目录下的数据都可以持久化保存。

常用格式

在 5.2 或 5.11 的 --tty 后面插入如下格式的内容

>--volume [<实体机文件或目录>:]<容器内文件或目录> [--volume [<实体机文件或目录>:]<容器内文件或目录>] ...

为了方便容器的迁移以及维护工作，通常会指定实体机内的某个文件或目录映射到容器内的某个文件或目录中。

如果不指定实体机文件或目录，Docker 将会自动分配一个实体机目录。

可以创建多个数据卷。

例如

以 ubuntu 为镜像，建立一个名为 ubuntu_test2 的容器并启动，将实体机上的 /root/ubuntu_files1目录挂载到容器中的 /test/ubuntu_files1 目录中去（实体机上的目录已存在）。
```bash
docker container run --rm --interactive --tty --volume /root/ubuntu_files1:/test/ubuntu_files1 --name=ubuntu_test2 ubuntu:latest
```
执行完该命令后，我们已经是在容器内操作了。此时我们来看看容器内是否出现了挂载的目录。
```bash
ls /test/ubuntu_files1
```

如果没有返回错误信息，说明挂载成功。现在我们来向里面写一点东西，看下能不能保存。
```bash
echo "File saved" > /test/ubuntu_files1/1.txt
```
然后按 Ctrl + D 关闭容器。我们就来到实体机下了，接下来我们来看看实体机有没有这个文件。
```bash
cat /root/ubuntu_files1/1.txt
```
- 如果返回了  ` File saved ` ，说明数据已经可以保存了！

您也可以再次创建容器，然后在容器内看看 `  /test/ubuntu_files1/1.txt ` 这个文件在不在。

### 6.2 打包一个新的镜像（不推荐）

这种方法十分简单粗暴，就是把容器内现有文件全部打包成一个新的镜像，然后新建一个使用该映像的容器即可实现文件的保存。

之所以不推荐，主要是因为这样做会把容器内运行程序的缓存等无用文件一并打包下来。如果多次执行该操作，容器会变得非常臃肿。其次也可能会造成一定的安全隐患。

常用格式

```bash
docker container commit <需要保存的容器名> <打包之后的镜像名>
```

这里就不举例了。

## 七、容器的网络连接

### 7.1 容器联网的基本方式

NAT 模式是容器默认的联网模式。

在启动 Docker 服务之后，Docker 会自动往实体机内添加一个名为 docker0 的网桥，这个网桥默认可以与实体机内所有的网络接口通信。

我们通过执行 ` brctl show `  这条命令来看一下 docker0 网桥的状态。

执行结果
```bash
bridge name  bridge id  STP enabled  interfaces
docker0  8000.024229c84e5a  no
```
当容器启动之后，会生成一个形如 vethXXXXXXX 的容器专用接口。这个接口也会加入到 docker0 的桥接列表中。

docker0 上面有 IP 地址，也可以自动为每个容器分配 IP 地址（非 DHCP 协议）。

我们通过执行 ` ip addr show dev docker0 ` 还有  ` brctl show docker0 ` 这条两命令来看一下。

执行结果
```bash
6: docker0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP 
 link/ether 02:42:29:c8:4e:5a brd ff:ff:ff:ff:ff:ff
 inet 172.17.0.1/16 scope global docker0
 valid_lft forever preferred_lft forever
 inet6 fe80::42:29ff:fec8:4e5a/64 scope link
 valid_lft forever preferred_lft forever

bridge name  bridge id  STP enabled  interfaces
docker0  8000.024229c84e5a  no  vethcd2a637
```
其实 docker0 就相当于一个普通的路由器，通过 NAT 转换实现容器间的相互通信和连接外网。

我们通过执行 ` iptables -t nat -L POSTROUTING -v -n ` 来查看相关的 NAT 规则。

执行结果
```bash
Chain POSTROUTING (policy ACCEPT 373 packets, 31640 bytes)
 pkts bytes target  prot opt in  out  source  destination         
 12  729 MASQUERADE all -- * !docker0 172.17.0.0/16 0.0.0.0/0
```
很显然，存在 docker0 网段的 SNAT 规则，说明容器都是通过 NAT 的方式与实体机共享网络的。

如需查看容器的 IP 地址，请执行以下命令：
```bash
docker container inspect --format='{{.NetworkSettings.IPAddress}}' <容器名>
```
### 7.2 自定义网桥 & 容器 IP 地址

使用默认网桥一般是不能自定义容器 IP 地址的，会提示以下错误：
```bash
User specified IP address is supported only when connecting to networks with user configured subnets
```
这时候，我们就需要自定义一个网桥。

#### 7.2.1 自定义网桥

常用格式
```bash
docker network create --driver bridge --subnet <网桥网段> <网桥名>
```
例如

创建一个名为 docker_br1 的网桥，网段为 192.168.10.0/24
```bash
docker network create --driver bridge --subnet 192.168.10.0/24 docker_br1
```
执行结果
```bash
46cc818c92f0780ccd89811c12906c4527b554d18a61e72b0b2337b663ebab5f
```
这是自动生成的网桥唯一长 ID。

网桥的管理和删除命令格式和上面镜像管理的相似，这里就不再说了。

#### 7.2.2 自定义容器 IP 地址

常用格式

在 5.2 或 5.11 的 --tty 后面插入如下格式的内容

>--network=<网桥名> --ip=<IP地址>

例如

创建并运行一个使用刚才创建的 docker_br1 网桥的容器，把 IP 地址设定为 192.168.10.211 ，然后验证结果。

为了方便，这里将直接运行一个包含 ifconfig 命令的镜像的容器，然后执行 ifconfig eth0 命令来验证。
```bash
docker container run --rm --interactive --tty --network=docker_br1 --ip=192.168.10.211 --name=see_ip_addr ianneub/network-tools ifconfig eth0
```
执行结果
```bash
#镜像下载过程略
eth0 Link encap:Ethernet HWaddr 02:42:c0:a8:0a:02  
 inet addr:192.168.10.211 Bcast:0.0.0.0 Mask:255.255.255.0
 UP BROADCAST RUNNING MULTICAST MTU:1500 Metric:1
 RX packets:2 errors:0 dropped:0 overruns:0 frame:0
 TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 collisions:0 txqueuelen:0
 RX bytes:180 (180.0 B) TX bytes:0 (0.0 B)
 ```
显然，这里的 IP 地址已经是我们设定的 192.168.10.211 。

### 7.3 端口映射

如果容器需要对外提供服务，在默认情况下需要把容器内的端口映射到实体机上。

常用格式

在 5.2 或 5.11 的 --tty 后面插入如下格式的内容
> -p [<实体机接口 IP 地址>:]<实体机端口>:<容器内端口>[/<tcp|udp>] [-p [<实体机接口 IP 地址>:]<实体机端口>:<容器内端口>[/<tcp|udp>]] ...

可以创建多个端口映射。

如果不指定实体机接口 IP 地址，则容器内端口将映射到实体机的所有网络接口上。

如果不指定 TCP 或 UDP 协议，默认使用 TCP 协议。

例如

运行一个提供 HTTP 服务的镜像（这里用 nginx）的容器，然后把容器中的 80 端口映射到实体机上的 8888 端口，最后测试能否访问。

```bash
docker container run --detach --rm --interactive --tty -p 8888:80 --name=nginx_test nginx && curl 127.0.0.1:8888
```

执行结果
```html 
<html>
<head>
<title>Welcome to nginx!</title>
```


如果含有以上内容的界面，说明端口映射成功。

### 7.4 为容器设置域名解析(不建议使用)

在很多情况下，我们需要在容器之间进行网络通信。而它们的 IP 地址又是不固定的，这就需要为容器固定一个 DNS 名称。

假设现在有一个容器 A ，而新建的容器 B 需要访问容器 A 上的网络服务，在没设置域名解析的情况下容器 B 只能通过容器 A 的 IP 地址来访问容器 A 。而如果在容器 B 建立的时候设置了域名解析，容器 B 就可以通过容器 A 的名称或别名来访问容器 A 。

常用格式

在 5.2 或 5.11 的 --tty 后面插入如下格式的内容

>--link <容器名称>[:<容器别名>]
如果不设置容器别名，将自动使用容器名称。

