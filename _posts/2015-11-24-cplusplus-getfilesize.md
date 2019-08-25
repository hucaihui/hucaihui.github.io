---
layout: post
title: c++获得文件大小
tags: c++
---

# c++获得文件大小的几种方式


##第一种
    
{% highlight c++ %}
#include<io.h>
#include<iostream>
using namespace std;

int main()
{
    int handle;
    handle = open("text.txt", 0x100);
    long length = filelength(handle);
    cout<< "file size" << length <<endl;
    close(handle);
    return 0;
}
{% endhighlight %}

##第二种

{% highlight c++ %}
#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
    //创建文件句柄
    HANDLE fhandle = CreateFile("test.txt", 0, 0, 0, OPEN_EXISTING, 0, 0);
    DWORD size = GetFileSize(fhandle, 0);
    cout<< "filesize" << size <<endl;
    return 0;
}
{% endhighlight %}

##第三种

{% highlight c++ %}

#include<iostream>
int main()
{
    FILE * file = NULL;
    file = fopen("test.txt", "rb");
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fclose(file);
    std::cout<< "filesize" << length << std::endl;
    return 0;
}

{% endhighlight %}
