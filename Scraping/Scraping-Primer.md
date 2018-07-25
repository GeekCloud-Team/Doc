---
title: Docker-Primer
date: 2018-7-1 12:14:00
tags: scraping
---

## Scraping Primer

#### 识别网站

##### builtwith模块

- 安装

  ```shell
  pip installl builtwith	
  ```

- 使用

  ```python
  import builtwith
  print(builtwith.parse('http://example.webscraping.com'))
  
  ## 输出结果
  {'web-servers': ['Nginx'], 'web-frameworks': ['Web2py', 'Twitter Bootstrap'], 'programming-languages': ['Python'], 'javascript-frameworks': ['jQuery', 'Modernizr', 'jQuery UI']}
  ```

#### 寻找网站所有者

##### python-whois

- 安装

  ```shell
  pip install python-whois
  ```

- 使用

  ```python
  import whois
  print(whois.whois('appspot.com'))
  
  ## 输出结果
  {
    "domain_name": [
      "APPSPOT.COM",
      "appspot.com"
    ],
    "registrar": "MarkMonitor, Inc.",
    "whois_server": "whois.markmonitor.com",
    "referral_url": null,
    "updated_date": [
      "2018-02-06 10:30:28",
      "2018-02-06 02:30:29-08:00"
    ],
    "creation_date": [
      "2005-03-10 02:27:55",
      "2005-03-09 18:27:55-08:00"
    ],
    "expiration_date": [
      "2019-03-10 01:27:55",
      "2019-03-09 00:00:00-08:00"
    ],
    "name_servers": [
      "NS1.GOOGLE.COM",
      "NS2.GOOGLE.COM",
      "NS3.GOOGLE.COM",
      "NS4.GOOGLE.COM",
      "ns1.google.com",
      "ns4.google.com",
      "ns2.google.com",
      "ns3.google.com"
    ],
    "status": [
      "clientDeleteProhibited https://icann.org/epp#clientDeleteProhibited",
      "clientTransferProhibited https://icann.org/epp#clientTransferProhibited",
      "clientUpdateProhibited https://icann.org/epp#clientUpdateProhibited",
      "serverDeleteProhibited https://icann.org/epp#serverDeleteProhibited",
      "serverTransferProhibited https://icann.org/epp#serverTransferProhibited",
      "serverUpdateProhibited https://icann.org/epp#serverUpdateProhibited",
      "clientUpdateProhibited (https://www.icann.org/epp#clientUpdateProhibited)",
      "clientTransferProhibited (https://www.icann.org/epp#clientTransferProhibited)",
      "clientDeleteProhibited (https://www.icann.org/epp#clientDeleteProhibited)",
      "serverUpdateProhibited (https://www.icann.org/epp#serverUpdateProhibited)",
      "serverTransferProhibited (https://www.icann.org/epp#serverTransferProhibited)",
      "serverDeleteProhibited (https://www.icann.org/epp#serverDeleteProhibited)"
    ],
    "emails": [
      "abusecomplaints@markmonitor.com",
      "whoisrelay@markmonitor.com"
    ],
    "dnssec": "unsigned",
    "name": null,
    "org": "Google LLC",
    "address": null,
    "city": null,
    "state": "CA",
    "zipcode": null,
    "country": "US"
  }
  ```

  

####  编写第一个网络爬虫

##### 下载网页

```python
import urllib.request

def download(url,  user_agent='wswp', num_retries=2):
    print("Downloading:"+url)
    headers = {'User_agent': user_agent}
    request = urllib.request.Request(url, headers=headers)
    try:
        html = urllib.request.urlopen(request).read()
    except urllib.request.URLError as e:
        print("Error:"+e.reason)
        html = None
        if num_retries > 0:
            if hasattr(e,'code') and 500 <= e.code < 600:
                return download(url, user_agent, num_retries-1)
    return html

## 尝试下载并捕获异常
download("http://httpstat.us/500")

## 输出
Downloading:http://httpstat.us/500
Error:Internal Server Error
Downloading:http://httpstat.us/500
Error:Internal Server Error
Downloading:http://httpstat.us/500
Error:Internal Server Error

```

##### 网站地图爬虫

```python
def crawl_sitemap(url):
    sitemap = download(url)
    links = re.findall('<loc>(.*?)</loc>', sitemap.decode('utf-8'))
    for link in links:
        html = download(link)
        
## 测试
crawl_sitemap("http://example.webscraping.com/sitemap.xml")

## 输出
Downloading:http://example.webscraping.com/sitemap.xml
Downloading:http://example.webscraping.com/places/default/view/Afghanistan-1
Downloading:http://example.webscraping.com/places/default/view/Aland-Islands-2
Downloading:http://example.webscraping.com/places/default/view/Albania-3
Downloading:http://example.webscraping.com/places/default/view/Algeria-4
Downloading:http://example.webscraping.com/places/default/view/American-Samoa-5
```

