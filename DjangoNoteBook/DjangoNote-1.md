## Django2.0 Note No.1

## 简易入门

查看Django安装版本

```bash
python -m django --version
```
创建项目
```bash
django-admin startproject mysite

#执行之后创建的文件:
mysite/
    manage.py
    mysite/
        __init__.py
        settings.py
        urls.py
        wsgi.py
```


最外层的:file: mysite/ 根目录只是你项目的容器， Django 不关心它的名字，你可以将它重命名为任何你喜欢的名字。

`manage.py`: 一个让你用各种方式管理 Django 项目的命令行工具。

里面一层的` mysite/` 目录包含你的项目，它是一个纯`Python` 包。它的名字就是当你引用它内部任何东西时需要用到的 `Python` 包名。 (比如 `mysite.urls`).

`mysite/__init__.py`：一个空文件，告诉` Python` 这个目录应该被认为是一个 `Python` 包。如果你是` Python `初学者，阅读官方文档中的 更多关于包的知识。

`mysite/settings.py`：`Django` 项目的配置文件。

`mysite/urls.py`：Django 项目的 URL 声明，就像你网站的“目录”。

mysite/wsgi.py：作为你的项目的运行在 WSGI 兼容的Web服务器上的入口。

### 用于开发的简易服务器
让我们来确认一下你的 Django 项目是否真的创建成功了。如果你的当前目录不是外层的 mysite 目录的话，请切换到此目录，然后运行下面的命令：
```bash
python manage.py runserver
# python manage.py runserver 8080 #更换端口
# python manage.py runserver 0:8000 #更换IP 0代表0.0.0.0
```
你应该会看到如下输出：
```bash
Performing system checks...

System check identified no issues (0 silenced).

You have unapplied migrations; your app may not work properly until they are applied.
Run 'python manage.py migrate' to apply them.

三月 31, 2018 - 15:50:53
Django version 2.0, using settings 'mysite.settings'
Starting development server at http://127.0.0.1:8000/
Quit the server with CONTROL-C.
```

> 忽略有关未应用最新数据库迁移的警告，稍后我们处理数据库。

### 创建投票应用

创建一个叫polls的应用
```bash
python manage.py startapp polls

#创建后的polls目录结构
polls/
    __init__.py
    admin.py
    apps.py
    migrations/
        __init__.py
    models.py
    tests.py
    views.py
```

### 编写第一个视图
打开 `polls/views.py`，把下面这些 Python 代码输入进去：

```python
from django.http import HttpResponse


def index(request):
    return HttpResponse("Hello, world. You're at the polls index.")

```

如果想看见效果，我们需要将一个 `URL` 映射到它——这就是我们需要 `URLconf` 的原因了。

为了创建` URLconf`，请在` polls `目录里新建一个 `urls.py `文件。你的应用目录现在看起来应该是这样：
```bash
polls/
    __init__.py
    admin.py
    apps.py
    migrations/
        __init__.py
    models.py
    tests.py
    urls.py
    views.py
```
在 polls/urls.py 中，输入如下代码：

```python
from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
]
```

下一步要在主`URLCONF`文件中指定`polls.urls`模块,在 `mysite/urls.py` 文件的 `urlpatterns` 列表里插入一个 `include()`， 如下：
```python
from django.contrib import admin
from django.urls import include, path

urlpatterns = [
    path('polls/', include('polls.urls')),
    path('admin/', admin.site.urls),
]
```

函数` include() `允许引用其它 `URLconfs`。每当 `Django` 遇到 :`func：~django.urls.include `时，它会截断与此项匹配的` URL `的部分，并将剩余的字符串发送到 `URLconf `以供进一步处理。

我们设计 `include() `的理念是使其可以即插即用。因为投票应用有它自己的 `URLconf( polls/urls.py )`，他们能够被放在` "/polls/"` ， `"/fun_polls/"` ，`"/content/polls/"`，`或者其他任何路径下，这个应用都能够正常工作。

> 当包括其它 URL 模式时你应该总是使用 include() ， admin.site.urls 是唯一例外。

测试
```bash
 python manage.py runserver
```

#### path() 参数： route
route 是一个匹配 URL 的准则（类似正则表达式）。当 Django 响应一个请求时，它会从 urlpatterns 的第一项开始，按顺序依次匹配列表中的项，直到找到匹配的项。

这些准则不会匹配 GET 和 POST 参数或域名。例如，URLconf 在处理请求 https://www.example.com/myapp/ 时，它会尝试匹配 myapp/ 。处理请求 https://www.example.com/myapp/?page=3 时，也只会尝试匹配 myapp/。

#### path() 参数： view
当 Django 找到了一个匹配的准则，就会调用这个特定的视图函数，并传入一个 HttpRequest 对象作为第一个参数，被“捕获”的参数以关键字参数的形式传入。稍后，我们会给出一个例子。

#### path() 参数： kwargs
任意个关键字参数可以作为一个字典传递给目标视图函数。本教程中不会使用这一特性。

#### path() 参数： name
为你的 URL 取名能使你在 Django 的任意地方唯一地引用它，尤其是在模板中。这个有用的特性允许你只改一个文件就能全局地修改某个 URL 模式。

