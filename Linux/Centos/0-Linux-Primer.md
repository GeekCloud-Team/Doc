#### GNOME的简单快捷键

- 图形界面帮助：F1
- 活动概述：super
- 切换工作区：shift+ctrl+alt+↑
- 运行命令：Alt+F2
- 锁定桌面:Alt+Ctrl+L
- 快速重启：Ctrl+Alt+Del

#### 基础命令：
```shell

lsblk 查看分区情况

ls -l  显示目录详细信息

ls -lh 详细显示大小

ls -a 显示全部文件（包括隐藏文件）

ls -d 查看目录本身属性 建议使用 ls -ld

ll 等价于ls -l

cp -a 复制并保留原有属性（不改变属主和组）

cp -r 拷贝跟目录下的

mv -f 强制移动（覆盖不提示）

rm -r 删除目录以及文件

rm -i 带提示的删除

rm -rf / 多多执行23333
```

#### 获取帮助的方法：

##### man  命令

> 手册级别是分类的意思 1（普通用户手册）5（配置文件手册）8（管理员命令手册）
``` shell 
man 5 passwd
```
>  g回到手册顶部 G回到底部  /输入搜索关键字

``` shell
man -a <命令>查看改命令所有手册
```

##### 通过info或pinfo活动帮助

> pinfo是info的升级版

首先查找passinfo文档，如果没有那就强制打开man文档（info不会）

- 空格 ：翻页
- HOME：回到顶部
- END：回到底部
- d： 返回首页

读取/usr/share/doc下的软件包帮助文档
```shell
 firefox /usr/share/doc #通过火狐打开
```
通过RED HAT官方获得帮助

**重定向：**

- 2>file 把错误重定向到文件
- &>file正确，错误都重定向到文件 等价于2>&1
- wc -l显示输入数据的行数
- tee命令用于管道符中把第一个命令的输出显示出来

```shell
lsblk | tee /tmp/list-blocks.txt | wc -l
```

#### vim编辑器

vimtutor命令进入vim编辑器向导

​              ↑

​              k

←h                  l→

​              j

​              ↓

命令模式切换到编辑模式： i（插入在前），I（插入行首），a（插入在后），A（插入末尾），o（新建下一行插入）,O（新建上一行插入），s（删除前面一个数进入编辑模式）,S（删除正行并进入编辑模式）

其他模式切换到命令模式：ESC 

- $快速到行末
- g来到文档顶部
- G来到文档底部
- dw删除连续的字母符号
- cw删除连续符号并进入编辑模式
- yy复制整行
- dd剪切
- 4yy复制4行
- p粘贴整行
- u撤销
- /搜索内容
- n向下寻找搜索相同的内容
- N向上寻找搜索 相同内容
- s替换
- s/host/HOST/ 当前行把host替换HOST  加g全局修改
- ：set number显示行号
- 1，2s/o/O/g   把1，2行o都变O
- %s/o/O/g 把整个文档都有替换
- gedit图形界面编辑器

#### 用户和组

相关文件/etc/passwd（用户名、密码，用户id，组id、组名、家目录、shell路径） 、/etc/group(组名、密码、id号，组成员)

>  id命令查看当前用户的信息

*用户可以属于多个组

！$是上个命令的最后一个字符

##### 需要了解的shell: 

- /bin/bash 系统默认shell
- /sbin/nologin 非交互式shell，禁止用户登录

#### 用户uid分类：

- 0 管理员
- 1-200系统用户，由系统静态分配给系统进程使用
- 201-999 系统用户2，在系统上一般不拥有文件，他们是动态地指定安装的软件作为运行身份
- 1000+ 常规用户

> su - =su - root 切换root账号也切换到默认目录
>
> exit 退出root账号
>
> su -root切换时会切换到root的默认家路径

/var/log/secure 保存每个用户使用的命令的log信息

**管理本地账号**

添加用户前需要确定：

1. 确定用户的默认组是否有特殊要求
2. 确定用户是否允许登录
3. 确定用户密码策略
4. 确定用户的有效期
5. 确定用户的uid是否有特殊需求

##### *重要：

useradd,usermod的参数：

- -u设置uid
- -c添加用户注释
- -g指定用户的默认组
- -G指定用户的附加组（覆盖以前的附加组）
- -a追加更多的附加组（以前的附加组还保存）最好使用-aG
- -d指定用户的家目录 
- -m家目录迁移必须和-d一起使用
- -s指定用户默认shell
- -L锁定用户
- -U解锁用户

> 搜索用户：grep user_name /etc/passwd



> Tip: `/etc/passwd`保存用户信息,  `/etc/group`保存组信息  `passwd user_name` 给指定用户设定密码

##### 如何查看用户被锁定：

```shell
grep user_name /etc/shadow#组密码的位置
```

密码首位加感叹号即被锁定

```shell
userdel user_name 命令执行后不会删除家目录和邮件目录

userdel -r user_name 删除彻底
```



##### 新建组：
``` shell
groupadd group_name

groupadd -g 1200 group_name 指定组的gid号120
```

##### 修改组:

```shell
groupmod -g 1500 group_name 修改组的gid号为1500

groupmod -n  new_name group_name 修改组的名字
```

##### 查看组的情况：

```shell
grep group_name /etc/group
```

##### 删除组：
```shell
groupdel group_name
```

给组设定密码：
```shell
gpasswd group_name 

gpasswd -a user_name group_name#讲用户加入组

*组密码放在/etc/gshadow

当前用户临时切换组：

newgrp group_name #exit 复原
```



 **管理用户密码：**
```shell
vim /etc/login.defs #查看密码详细策略
```
###### `/etc/shadow`各个字段的内容：  

> 用户名：密码：用户密码上次更改时间（距离1970.1.1的天数）：密码最小修改频率（0代表随时可以改，2代表得过2天才可以改）：密码有效期（99999密码永不过期）：密码过期前几天发出警告：过期后几天内有效：账号有效期（距离1970年1.1）：



- 密码栏如果是*或者 ！！都表示密码无效
- 密码字段$加密方式（6代表SHA512）$加密种子也叫随机加密数$加密后的密码

##### 查看用户密码策略：

```shell
chage -l   user_name #查看用户密码信息
```

列表：

- 修改密码时间 
- 密码过期时间
- 密码过期多少天不可以使用 
- 账号过期
- 密码最小修改日期也就是密码最小修改频率
- 密码最大修改日期（有效期）
- 密码过期多少天发出警告

##### chage命令：

- -l显示详细账号信息
- -E账号过期时间
- -d 0下次登录系统强制修改密码
- -M两次改密码的最大天数
- -m两次改密码的最小天数
- -W过期警告天数
- -I过期多少天后设定密码为失效状态

```shell
chage -m 1  -M 14 -W 5 -I 3 -E 2016-12-12 user_name #修改用户密码最小修改频率为1天，有效期14天，5天前发出警告，过期3天内，过期时间为2016-12-12 还可以使用

date -d +"60 days" +"%Y-%m-%d" #距离当天60天后是哪一天

chage -d 0 user_name #用户下次登录系统强制修改密码
```
#### 文件系统权限

>  一个用户要对目录有基本访问操作，必须有r，x权限

 用户对资源来说用三种角色：

| 文件权限      | 说明       |
| ------------- | ---------- |
| User（u）主人 | 文件所有者 |
| Group（g）    | 所属组     |
| Other（o）    | 其他人     |



##### `drwxrwxrwx`对应

| 文件权限    | 用户权限 | 组权限 | 其他人权限 |
| ----------- | -------- | ------ | ---------- |
| d（文件夹） | rwx      | rwx    | rwx        |



> 使用者如果所在目录有写权限就可以删除目录中的文件

##### 修改权限

例:
```shell

chmod  u+x,g+w,o-r file_name

chmod go=rw file_name

chmod u-x go=r file_name

chmod o=--- file_name #对其他人移除所有权限

chmod -R o-- dir #递归使用，对dir文件夹下的所有文件全部生效
```

##### 更改目录/文件的所有者

```shell

chown host_name:group_name file_name#同时修改文件属主和属组

chown host_name file_name#修改文件的属主

chown :group_name file_name#修改文件的属组

chgrp root file_name #修改文件属组效果和上面等价
```

> -R递归使用，在文件夹里面的文件也生效

> 特权位(s)和粘贴位(t)权限，用户权限掩码（umask）

> setuid（修改文件的特权位权限）=u+s=4

> 文件执行有效身份为文件的**拥有者**，而不是执行者的身份

##### 例子1:

```shel
chmod 4(755)  file_name #u+s
```

> setgid=g+s=2
>
> 文件执行有效身份是文件的属组，而不是执行者
>
> 目录里新建的文件的拥有组也会自动继承目录的拥有组身份

##### 例子2：

```she
chmod 2(755)/g+s file_name #g+s
```

> sticky = o+t =1
>
> 对目录有写权限的用户仅仅可以删除自己的文件，不能删除其他用户的文件

```she
chmod o+t file_name #o+t
```



##### umask

>  用于设置默认权限

默认新建文件最大权限0666

默认新建目录最大权限0777

- 如果student用户的umask为0002，那么新建文件的权限为0666-0002=0664，目录权限为0775

修改umask：
```shell
umask 0000、0001 #此修改只影响当前终端
```

>  掩码机制保存在/etc/profile

>  修改umask 在 ~/.bash_profile后加入umask 0002重新登录系统后生效

#### 进程

> 执行程序被执行后的事例

包括：

- 分配内存的地址空间
- 进程的运行身份和权限的安全属性
- 一个或多个进程
- 进程状态
- pid=progress id    进程id号
- ppid=parent progress id 父进程id号

##### 进程的7种状态：

- R进程运行中
- S不可中断睡眠状态
- D可中断睡眠状态
- K可被结束的不可中断睡眠状态
- Z僵尸进程
- X进程已经退出
- T进程被暂停

##### 查看进程ps命令

```shell
ps aux #linux样式

ps lax #linux样式

ps -ef #unix样式

ps j 进程命令的详细参数
```



##### TTY下显示进程在哪个终端进行

> tty命令可以显示当前终端号

##### 使用jobs控制进程

进程在shell里分为前台进程和后台进程

前台进程会占用shell，后台进程不会占用

##### `&`

在命令后加&将执行的命令放入后台进行

##### `jobs`

##### 查看后台的进程
```shell
fg %jobs最前面的号（信号参数）
```

> Ctrl+Z 暂停当前程序 ,也可以通过fg来挂到前台运行
>
> Ctrl+C 强制结束前台进程

**使用信号管理进程：**

常见信号列表：

| 数字信号(signal) | 信号别名 | 作用                                                 |
| ---------------- | -------- | ---------------------------------------------------- |
| 1                | HUP      | 挂起信号，可以让进程重新配置                         |
| 2                | INT      | 中断信号，结束进程的作用，等价于Ctrl+c               |
| 3                | QUIT     | 让进程退出，即进程结束                               |
| 9                | KILL     | 直接结束进程  不被进程捕获（系统执行）               |
| 15               | TEAM     | 进程终止，这是默认信号（给进程信号，让进程自己退出） |
| 18               | CONT     | 被暂停的进程继续恢复运行                             |
| 19               | STOP     | 暂停进程                                             |
| 20               | TSTP     | 用户停止请求，类似于Ctrl+z                           |



##### kill命令发送信号：

```sh
kill PID（默认的发15）

kill -signal PID（执行相关信号）

kill -l（显示kill支持的型号表）

# pstree (打印进程树)

pstree -p user_name （列出student用户的进程树）

# killall 可以通过模糊匹配同时给多个进程发送信号（需要输入完整的进程名：ps）

killall <完整进程的名字>

killall -signal command_pattern

killall -signal -u username command_pattern #管理员才可以使用

# pkill命令类似killall（不需要输入完整的进程名，支持模糊匹配）

pkill command_pattern

pkill -signal command_pattern（精确匹配执行相关进程，并执行相关信号）

pkill -G GID command_pattern（kill固定组下的进程）

pkill -p PPID command_pattern（kill父进程下的子进程）

pkill -t terminal_name  command_pattern (杀死指定终端下的进程，不写进程默认杀死所有，但是杀不死bash需要-9才能杀死，并且让他退出终端)

#  w -h -u （查看用户会话情况  也就是每个用户登录的终端）

pkill -U UID  command_pattern （杀死相应用户的进程，不写默认杀死所有）

# pgrep命令捕捉进程（命令中的选项和pkill差不多）

pgrep -l -u student（-u是指定用户 -l输出pid）

```

> *一般而言，kill别的用户的进程都需要启用root用户

 

**监控进程活动**

> 系统负载：进程以及子进程和线程产生的计算指令都会让cpu执行，产生请求的这些进程组成“运行队列”，等待cpu执行，这个队列就是系统负载，系统负载是所有CPU运行队列的总和

系统负载计算：

​                     如：4CPU，当前负载2.92 单位是进程

cpu核心数                         cpu1              cpu2         cpu3        cpu4

cpu使用情况                    2。92/4          2.92/4       2.92/4      2.92/4=73%

剩下的27%的资源是空闲的

>  PS:linux的计算器     `echo | awk ‘｛print 2.92/4｝’`

显示服务器硬件下的详细信息：`  cat /proc/cpuinfo`  

可以通过下面的命令过滤出CPU核心数(其实是线程数)：` grep "model name" /proc/cpuinfo`



##### uptime

> 显示：当前时间 ，服务器状态（up） ，机器运行时间 ，当前登录的用户，系统平均负载在过五分钟，十分钟，十五分钟

 

##### 命令top

显示：

> PID 使用者 优先级1   优先级2 虚拟内存（进程内的所有内存） 助理内存（进程本身的物理内存） S代表状态S是sleep 

常见选项

- h 查看帮助
- 1  输出每个CPU使用情况
- s   设置刷新时间
- b  高亮输出处于R状态的进程
- M 按内存使用百分比培训输出
- P  按CPU使用百分比排序输出
- k  kill掉指定PID进程
- q  退出


#### 系统服务和守护进程管理

RH LINUX中的系统启动和服务进程都是由systemd管理，这个systemd负责在系统启动或系统运行过程中激活系统资源，服务守护进程和其他进程

systemd取代了RHEL以往的system v和init程序启动做法，最终目的是提供更优秀的框架以表示系统服务直接的依赖关系，并以此达到提供系统初始化服务的并行启动效率，降低shell脚本使用和系统开销的效果（貌似debian和arch这些也都有）

systemd使用服务单元为基本单位管理系统的启动

systemd服务管理：服务启动脚本被服务单元所取代，服务单元以.service文件扩展结束，提供了与服务启动脚本一样的功能

服务单元为systemd读取的配置文件

##### 服务状态说明

- loaded 服务单元配置文件已经被处理（系统已经读取了该服务的配置文件）
- active(running) 服务的一个或多个进程正在运行
- active(exited) 某些一次性的服务已经整个被执行并退出(一次性服务即为服务运行完成相关进程会自动退出)
- active(waiting) 服务已经运行但是在等待某个事件
- inactive 服务没有在运行
- enabled 服务设定开机运行
- disabled 服务没有设定开机运行
- static 服务不能被设置为开机运行，但可以用其他服务来启动该服务

#### systemctl命令

```shell
systemctl is-enabled sth.service #查询服务是否开机启动

systemctl is-active sth.service #查询服务是否正在运行

systemctl status sth.service #查询服务的运行状态

systemctl --failled --type=service  #查询启动失败的服务(--type指定只看.service服务)

systemctl list-units --type=service #列出所有已经加载并激活（运行中）的unit，--type指定unit的类别，--all列出所有的unit，包括非活动状态的（非运行的）
```

> 显示：服务  加载情况 活跃情况 执行情况 描述

```sh
systemctl list-unit-files --type=service #列出所有的开机启动设置（相当于以前的chkconfig --list）
```



显示：服务文件 开机启动状态 

```sh
systemctl list-dependencies [sth.unit] #输出服务启动顺序（启动树）
```

##### 启动控制系统服务

```sh
systemctl enable sth.service 设置服务开机启动

systemctl disable sth.service 设置服务不要开机启动

systemctl start sth.service 设置服务启动

systemctl stop sth.service 设置服务停止

systemctl  restart sth.service 设置服务重启

systemctl reload sth.service  设置服务重新加载

systemctl mask sth.service 禁止服务被运行（开启启动和手工后期启动服务也会被禁止，当前已经运行的服务）

systemctl unmask sth.service 取消禁止服务运行
```

#### openssh配置与安全

openssh提供一个安全的远程shell，用于远程linux系统

openssh使用非对称加密手段加密保护通信数据

##### SSH基本命令

```she
ssh remotehost

ssh remoteuser@remotehost 或者 ssh -l remoteuser remotehost  #输入登录用户和服务器名或ip地址

ssh remoteuser@remotehost remote-command #输入用户和地址 加命令登录服务器

w -f #输出当前有哪些账户登录操作系统
```





- 本地ssh公钥保存位置： ~/.ssh/known_hosts
- 远程主机(服务端)公钥保存位置： /etc/ssh/*key*/ssh_host_xxx_key.pub

##### 配置SSH的秘钥验证

> 默认情况下通过SSH登录到远程系统，需要提供远程系统的账号和密码，但为了降低密码泄露的几率和提高登录的方便性，可使用基于秘钥的认证

清空文件命令：

:> ~/.ssh/known_hosts

（1）客户端生成秘钥对

ssh-keygen -t rsa#生成秘钥对

（2）客户端把秘钥发送给远程系统

ssh-copy-id -i ~/.ssh/id_rsa.pub user_name@server_hostname/IP #将秘钥发给服务器

cat ~/.ssh//authorized_keys #服务器端保存公钥的位置

（3）登录

`ssh  ip/host_name`

自定义优化ssh服务配置：

SSHD服务的配置文件：

```shell
# vim /etc/ssh/sshd_config

#systemctl restart sshd #修改完重启生效
```

需要了解的安全选项：

​     permitRootLogin yes|no 是否允许root通过ssh到本机

​     PermitRootLogin without-password 只允许root通过秘钥验证手段ssh到本机

​     PasswordAuthentication yes| no 默认yes 运行ssh通过密码验证方式到本机，如果设定为no，那么只能通过秘钥验证登录

#### 系统日志架构分析

目前linux系统有两种日志服务，分别是传统的`rsyslog`和新添加的`systemd-journal`

`systemd-journald`是一个改进型的日志管理服务，可以收集来自内核，系统早期启动阶段的日志、系统守护进程在启动和运行中的标准输出和错误信息，还有syslog的日志，该服务仅仅把日志集中保存在单一结构化的日志文件/run/log中，默认情况下并不会持久化保存日志，每次启动后，之前的日志就会丢失，另外，一些rsyslog无法收集的日志也会被他记录

rsyslog作为传统的日志服务，把所有收集到的日志都记录到/var/log/目录下的各个日志文件中，常见的日志文件：

- /var/log/messages 绝大多数的系统日志
- /var/log/secure  所有跟安全相关的系统日志
- /var/log/maillog  邮件服务日志
- /var/log/cron   crond计划服务日志
- /var/log/boot.log 系统启动相关日志

##### 审查rsyslog日志

###### 检查日志文件服务情况：
```shell
systemctl is-enabled rsyslog

systemctl status rsyslog
```

日志文件路径       /etc/rsyslog.conf   配置完需要重启方可生效

​       rsyslog日志类型:

​                           auth(认证)

​                           authpriv(授权)  

​                           cron（计划任务）  

​                           daemon(守护进程)  

​                           kern（内核）  

​                           lpr（打印服务）

​                           mail（邮件服务）  

​                           mark （时间戳标记）  

​                           news（新闻服务）  

​                           security（安全相关，等价与auth）

​                           syslog（自身日志）  

​                           user（普通用户）  

​                           uucp（系统服务）  

​                           local0-7（本地设备）

​       rsyslog日志级别（越往上越紧急,但是级别越低，如info可以记录err级别的log，但是不会记录debug级别）：

​                         emerg  （内核崩溃级别）

​                         alert   （严重警告级别）

​                         crit   （验证错误级别）

​                         err    （错误级别）

​                         warnning （警告级别）

​                         notice （注意级别）

​                         info  （信息级别）

​                         debug（调试级别）

#### logger命令

​                  用于自己生成log并上传到相应的日志类型中去

​                          `logger -p <日志类型> -t “我的标题” “你输入的内容”`

例：

​                         `loggerr-p auth.info -t "ok"  "content"`

​                             -p   将自己产生的日志归类为某个日志类型加后缀可以表示级别，如.info就是info级别

​                      选项：

​                            -t “你的标题” #设置日志标题 

##### 审查systemd Journal日志

​     这是systemd自带的日志工具

​     所有日志记录到/run/log文件中

```shell
     journalctl 查看所有日志

     journalctl  -n 5 查看最后五条日志

     journalctl  -p err  查看err类型日志

     journalctl  -f   查看不断输出最后10条日志（保持不断刷新）

     journalctl  --since today  查看今天的日志

     journalctl  --since "2014-02-10 20:30:00"  --until  "2014-02-13 12:00:00" 查看固定时间段日志

     journalctl  -o verbose   查看日志的详细信息

     journalctl  _SYSTEMD_UNIT=sshd.service _PID=1182 （查看SSHD日志的信息，PID代表进程号）

```



>  更多参数参考journalctl(1) systemd.journalctl-fields(7)

##### 保存systemd Journal日志

​     持久化保存journal日志，默认只会保存一个月的日志

进入配置文件：
```shell
     vim /etc/systemd/journald.conf #在里面有一个MaxFileSec=1month不需要修改

     mkdir /var/log/journal

     chown root:systemd-journal /var/log/journal

     chmod 2755 /var/log/journal

     killall  -USR1 systemd-journald 
```
维护准确的系统时间：

`NTP=NetworkTimeProtol`

##### timedatectl 查看系统时间和设定

```shell
timedatectl list-timezones 列出可用时区

timedatectl set-timezone "Asia/Shanghai"设定时区

timedatectl set-time 22:19:00 设置时间

timedatectl set-ntp true 使用网络时间同步
```

##### 使用chronyd服务进行网络时间同步

>  文件路径 /etc/chrony.conf

例子：

```shell
timedatectl set-ntp true
vim /etc/chrony.conf

server content.example.com iburst

#把原来的rhel自带的注释掉

systemctl enable chronyd

systemctl restart chronyd

#验证：

chronyc sources -v

chronyc 

chronyc> waitsync #如果有输出tty那么同步成功

```

#### Linux网络基础 (网络基础知识不再赘述)

> 网络服务路径/etc/services

##### 网卡命名

传统的RHEL系统以eth0，eth1等名字命名网卡，在RHEL7系统开始使用新的命名规则：基于固件、设备结构、设备类型

（1）有两个字母开头表示固件

​          以太网网卡以en开头

​          无线网卡以   wl开头

（2）设备结构

​          o   表示板载网卡（on-board）

​          s    热拔插结构   （hotplug slot）

​          p   PCI插槽位置

（3）由一个数字表示设备的索引、ID或端口

如果网卡无法使用上述方法表示，则会用传统的ethN来表示

例子：

​          eno1 第一块板载网卡

​          enp2s0 第一块PCI插槽网卡

测试和验证网络配置：
```shell
ifconfig #一代查看网卡ip命令

ip addr show eth0 #二代查看网卡ip命令

ip link   #查看电脑所有网卡信息

ip -s link show eth0 #只看eth0的接口的，-s表示查看接口状态

ip route 或 route -n  #查看路由表

ping -c 3 baidu.com #发三个ping包给百度
```
##### 查看网络连接情况

>  ss命令查看网络连接情况，一般加选项-ta

选项：

- -t tcp协议连接
- -a 所有状态的连接
- -n 数字化输出
- -u udp协议连接
- -l  处于listen状态的连接
- -p 输出相应进程的名字

​          

##### 使用nmcli命令配置网络

NetworkManager是监控和管理网络设定的服务。该服务在GNOME桌面是有一个图形插件可以查看网络状态

他提供的命令行和图形工具都可以对网络进行 设定，设定保存配置文件在/etc/sysconfig/network-scripts目录下

开启图形界面：

`nm-connection-editor`

查看所有连接

`nmcli connection now`

查看所有活动连接

`nmcli connection show --active`

查看指定ID的连接情况

`nmcli connection show "System eth0"`

查看设备状态

`nmcli dev status`

查看指定设备状态

`nmcli dev show eth0`

通过nmcli修改网络连接

（1）定义一个名字为default的连接，该连接会通过DHCP自动配置

`nmcli con add con-name "default" type ethernet ifname eth0`

（2）定义一个名为static的连接并手工指定所配置的IP和网关，该连接不会自动激活、

`nmcli con add con-name "static" ifname eth0 autoconnect no type ethernet ip4 123.23.23.23/25 gw4 123.23.23.24 `

（3）激活指定名字的连接

`nmcli con up "static"`

（4）激活默认连接

`nmcli con up default`

使用nmcli修改已有网络连接

（1）让连接取消自动激活

`nmcli con mod "static" connection.autoconnect yes`

（2）修改连接的DNS

`nmcli con mod "static" ipv4.dns 172.8.8.8`

（3）给连接添加DNS，有些设定可以通过+-添加或者移除设定

`nmcli con mod "static" +ipv4.dns 8.8.8.8`
（4）替换连接的静态IP和默认网关

`nmcli con mod "static" ipv4.address "123.23.23.23/24 123.23.23.23.1"`

（5）添加一个没有默认网关的IP

`nmcli con mod "static" +ipv4.address "10.10.10.10/16"`

（6）修改完毕。nmcli仅仅修改并保存了配置，需要激活更改，重新激活连接

`nmcli con up "static"`

其余的用法：

```shell
nmcli con del <ID> 删除接口

nmcli net off  关闭所有管理窗口

nmcli dev dis <DEV>  关闭某个接口，并临时禁用自动连接

nmcli con down "<ID>"  断开某个连接
```

编辑网络配置文件：

所有的连接定义配置文件都在`/etc/sysconfig/network-scripts/ifcfg-<name> `中

需要掌握的选项：

静态配置：                                                  动态配置：                    两者都配：

BOOTPROTO=none（静态）               

IPADDR0=172.25.0.10                      BOOTPROTO=dhcp               DEVICE=eth0

PREFIX0=24          #掩码                              空                                NAME="System eth0"

GATEWAY0=172.25.0.254                           空                                ONBOOT=yes

DEFROUTE=yes                                           空                                UUID=f3e8dd32-3a2c

DNS1=172.25.254.254                                空                                USERCTL=yes

选项说明：

 某选项0，后选项1代表该选项可以有多个设定值

DEFROUTE=yes 将接口设定为默认路由，no则否

USERCTL=yes   允许非root用户管理接口，no则否

手工编辑了配置文件需要重载才能生效

```shel
nmcli con reload 重载配置文件

nmcli con down "<name>"   关闭连接

nmcli con  up "<name>"    激活连接
```

设定主机名和域名解析

查看主机名：

`hostname`

临时修改主机名：

```shell
hostname "yourname"
```

在RHEL7，静态主机名设定保存在/etc/hostname 并且建议使用hostnamectl命令修改和查看系统FQDN主机名

```shell
hostnamectl set-hostname desktop0.example.com

hostnamectl status 

cat /etc/hostname
```



##### 配置域名解析

​       域名解析可以通过DNS或者本机/etc/hosts实现，默认配置是先hosts文件后查询DNS

​       指定DNS地址：/etc/resolv.conf

​        本地解析文件：/etc/hosts

#### 文件归档
##### 使用tar管理归档文件：

- c 创建新的归档文件
- x 对归档文件解包
- t 列出归档文件里的文件列表
- v 输出命令的归档或解包过程
- f 指定文件
- z 使用gzip压缩归档后的文件（.tar.gz）
- j 使用bzip压缩归档后的文件（.tar.bz2）
- J 使用xz压缩归档后的文件（.tar.xz）

##### 使用例子：

归档：
```shell
tar cf arch.tar file1 file2 file3

tar cf /root/etc.tar /etc

tar tf /root/etc.tar
```
解包：
```shell
mkdir /root/etcbackup

cd /root/etcbackip

tar xf /root/etc.tar 或者 # tar xf /root/etc.tar -C /root/etcbackup
```
归档并压缩：
```shell
tar czf /root/etc.tar.gz /etc

tar cjf  /root/etc.tar.bz2 /etc

tar  cJf /root/etc.tar.xz /etc
```
解压缩并且解包：
```shell
tar xf /etc.tar.xz
```
使用scp，sftp，rsync实现远程文件传输
```shell
scp 从本地把文件拷贝到远程

scp 把远程文件拷贝到本地 ， -r  拷贝目录(他们使用的都是SSH所建立的服务)

scp /etc/fstab server0:/tmp

scp server0:/etc/hosts /tmp/

scp -r /var/log server0:/tmp
```
##### sftp

> sftp是一个使用ssh加密文件传输的ftp服务，能够保证文件传输过程中是安全的

sftp 10.10.10.10 输入系统账号对应的密码 ，sftp [user@12.12.12.12](mailto:user@12.12.12.12) 指定登录用户名
```shell
sftp>put /etc/hosts /tmp/sftp/host #put上传的意思，前者是本地路径，后者是目标路径，不写就上传到当前路径

sftp>get  /etc/rc.d/rc.local  #get下载的意思
```
> quit 退出登录

#### rsync 远程同步命令（常用，并且效率很高）

​     -r 同步整个目录

​     -l 同步字符连接文件

​     -p 保留文件权限

​     -t  保留文件时间

​     -g 保留文件属组的关系

​     -o 保留文件所有关系

​     -D 同步设备文件

​     -a  保留文件以上所有属性，但acl和selinux扩展属性忽略

​      -A 保留文件以上所以属性，同时保留acl和selinux1的扩展属性

​      -v 同步文件详情
```shell
rsync -av /var/log/     /tmp  本机同步

rsync  -av /var/log/    server0:/tmp  远程同步

rsync   -av /var/log/    [student@server0](mailto:student@server0):/tmp 指定用户名义同步
```
#### 了解rpm包

rpm全称 Redhat Package Manager， 用于软件包的安装和升级

rpm包的名字结构：

​       httpd-tools-2.4.6-7.el7.x86_64.rpm

​       http-tools 软件名

​       2.4.6 版本号

​       7.el7 rpm包发布编号，有rpm包封装者设置

​       x86_64 适用机型

rpm包的组成：

​       安装释放的软件

​       软件包的元数据（版本，发布号，架构，描述，要求，更改日志等）

​       脚本：安装前执行的脚本和安装后执行的脚本

```shell
rpm -qlp xx.rpm 显示rpm包释放的文件和相应路径

rpm -qip xx.rpm  显示rpm包的详细信息

rpm  -q --script -p  xxx.rpm 显示rpm安装前后的脚本
```



##### 使用 yum 管理软件包

yum包管理器，yum极大地方便了rpm包的安装和升级，能够自动解决依赖关系

##### 搜索软件包

```sh
  yum list 'http*'

  yum search all 'web server' <--软件名字或者概述字段包含的关键字

  yum info httpd 查看包的信息

  yum provides /var/www/html  #查找提供这个路径的软件

  yum provides '*/gnuplot'  #模糊匹配，或者说，那个文件支持这个命令

```



​   

##### 安装软件包

```shell
    yum install httpd

    yum  update 升级所有软件包

    yum remove  httpd 卸载软件包
```



> ​    -y 默认是yes

##### 软件分组

```sh
  yum grouplist 显示安装分组名

    yum  groupinfo "Identity Management Server" 查询组里的软件包

    yum groupinstall "Infiniband Support" 安装所在组里面的所有软件包

 #PS：

     tail -5 /var/log/yum.log 查看yum安装的历史 或者 yum history

     yum history info 6 查看指定的命令执行信息，数字看history里面的ID

     yum history undo 6 对id执行的命令取反，卸载的会重装，安装的会卸载

```



##### 管理yum软件仓库

   可以给yum配置第三方软件仓库，仓库可以使用http，ftp或者file（本地）协议提供的软件集合。

   软件仓库的定义存在于/etc/yum.repos.d/目录下以.repo结尾的配置文件

（1）使用yum-config-manager命令管理

\# yum-config-manager --add-repo="http://xx.asd.com/sda/qwe/rht"

\# yum repolist  查看系统上的软件仓库

（2）手工编辑配置文件：

```sh
vim /etc/yum.repos/errata.repo（名字随便起要.repo结尾）

[uodates]

name=Red Hat Updates （名字也可以随便气）

baseurl=http://xxx.asd.com/rhel7.0/asdad/extra

enable=1                                                  （enable设置是否启用该源）

gpgcheck=0                                           （gpg校验值，启动校验需要设置gpgkey）

```

（3）使用yum-config-manager 禁用某个软件仓库

```sh
yum-config-manager  --disable conetc.example.com_rhel7.0_rht
```



##### 校验RPM包

​     使用rpm命令校验软件的相关信息

​     语法：

​     rpm -q  [select-options]  [query-options]
```shell
 rpm -q yum #查询一个已经安装了的软件包

 rpm  -qa | grep yum  #只是包含关键字的软件包

 rpm -q -p <http://xx.xx.xx/xx.rpm>   #查看具体软件包实际的名字等

 rpm -q -f /etc/yum.repos.d/  #查看后面文件是否来自rpm包，并且输出来自于哪个RPM包

 rpm -q -l yum-rhn-plugin  #查询某个软件包给系统释放哪些文件

 rpm -q -c yum-rhn-plugin #查询某个已经安装的软件包的释放的配置文件

 rpm -q -d yum-rhn-plugin  #查询某个软件包释放的帮助文档文件

 rpm  -q --scripts openssh-server #查看某软件包的安装的前后脚本

 rpm -q --changelog audit #查看 某个已经安装的软件包的更改日志
```
使用wget安装本地文件
```shell
wget <http://xx.xx.xx/asd.rpm>

yum localinstall asd.rpm #或者rpm -ivh http://sad.asd.x/xxx.rpm

rpm -q asd
```
从rpm包中解压出文件
```shell
 rpm2cpio sss.rpm | cpio -id #提取包内的所有文件

 rpm2cpio xxx.rpm | cpio -id "*txt" #仅仅提取带txt后缀的文件
```

#### 文件系统和硬盘设备管理

硬盘设备是支持随机读写的数据设备

在物理机器上设备文件默认都存放在/dev/目录下，第一个硬盘是/dev/sda,第二个硬盘是/dev/sdb,一次类推，第一个硬盘分区是/dev/sda1,第二个分区是/dev/sda2

在xen或者kvm虚拟机上，硬盘名字则是/dev/xvda或/dev/vda等，以此类推

有些存放数据的设备并不是直接硬件对应的设备文件，而是通过软件生成的块设备文件，例如lvm和软raid设备文件。

##### 文件系统

​     建立在硬盘设备之上，让系统支持以文件、目录形式访问设备的数据。
```shell
df -h

du root

du -sh /var/log
```
##### 文件系统的挂载和卸载

​       要以目录、文件形式访问设备上的数据，设备必须使用文件系统格式化。格式化后再挂载使用

```sh
 blkid  （b是块设备，该命令是查看建立文件系统的块设备）

 blkid /dev/vda1 （查看具体的一台块设备）

```



挂载：
```shell
mount  /dev/sda1 /mnt/mydata

mount UUID="XXXXX" /mnt/mydata

lsof /mnt/mydata 查看当前路径的使用情况

cd

umount /mnt/mydata
```
##### 管理链接文件

​     字符链接文件（软链接文件）

​                        相当于Windows的快捷方式

​                        他是一个独立的文件，该文件指向另一个文件

​                        他占用磁盘空间

​                        可以跨文件系统创建

​                        可以对目录建立字符链接文件

​      硬链接文件

​                         相当于同一份数据多个名字，拥有源文件的一些属性，仅仅是路径不同

​                         它不会另外占用磁盘空间

​                         起到文件数据冗余的作用

​                         仅仅支持同一个文件系统的文件创建硬链接

​                         不支持对目录的创建

##### 创建硬链接文件

链接文件和源文件的索引节点号是一样的，可以用ls -li查看

```sh
echo "hello world" > newfile.txt

ls -l newfile.txt

ln newfile.txt /tmp/newfile-hlink.txt
```



如果删除newfile，那么newfile-hlink依旧还在

不支持链接目录

###### 创建软链接文件

链接文件和源文件索引节点号是不一样的

`ln -s /tmp/newfile-hlink.txt /tmp/newfile-symlink.txt`

如果删除newfile-hlink那么newfile-symlink就失效了。

支持链接目录

查找文件

```sh
updatedb #更新扫描系统里的所有文件，把所有的文件路径保存在一个文件里

locate passwd # 查找路径带passwd的文件的绝对路径

locate -i passwd  #忽略大小写查找路径带passwd的文件的绝对路径

locate -n 5 snow.png #只输出5个结果

find / -name sshd_config #从根目录开始通过名字sshd_config查找

find / -iname '*.txt'  # 使用通配符查找，并且不区分大小写

find / -uid 1000 passwd #查找uid是1000的文件，即指定用户

find / -gid 1000 passwd #查找指定gid的文件，可以叠加选项

find / -user root -group student passwd #指定用户和组

find / -perm 764 #查找匹配权限的文件

find / -perm -324 #查找文件权限至少为324的文件

find / -perm /442 #查找文件u满足4或者g满足4或者o满足2

find /asd/asd/ -size 10M #查找大小为10M的文件

find  /asd/asd -size +10G#查找大于10G的文件

find /ad/asd -size -10K#查找小于10K的文件

find /ad/asd -mmin 120 #查找离修改时间正好是120分钟的文件

find /asd/asd -mmin+200 #查找已经修改200分钟的文件

find  /asd/asd -mmin -120 #查找修改时间不到120分钟的文件

find /etc -type [d/l/b/f] #查找属于d是目录，l字符链接，b块设备，f硬链接可以加-links +1硬链接数大于1的

find /usr/bin -size +50k -exec cp {} /tmp/bin \; #将usr/bin目录下的大于50K的文件拷贝到bin目录下

```



#### 管理本地的虚拟化主机

​             kvm需要的软件包

​                          核心包：qemu-kvm qemu-img

​                          工具包：virt-manager libvirt libvirt-python libvirt-client virt-install

​                          工具：

​                                        virsh管理虚拟机的命令行工具

​                                        virt-manager 管理虚拟机的图形工具
```shell
virsh list 查看正在运行虚拟机列表

virsh destory server 给某个虚拟机断电关机

virsh list --all 查看所有虚拟机列表

virsh start server 启动虚拟机

virt-manager #启动图形界面KVM
```

###### 创建新的虚拟化主机

- ctrl + alt + F1 安装主程序的终端，包含想要anaconda的输出调试信息
- ctrl + alt + F2 具有root权限的简单shell
- ctrl + alt + F3 安装日志，保存在/tmp/anaconda.log中
- ctrl + alt + F4 存储设备标准，保存内核识别的相关存储设备的信息和系统服务的信息
- ctrl + alt + F5 程序日志，输出启动系程序产生的日志
- ctrl + alt + F6 配用shell
- ctrl + alt + F7 默认的图形安装向导界面