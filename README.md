# globalmem

看 linux 设备驱动开发详解时，字符设备驱动一章，注册globalmem驱动时，出现如下错误：

# 加载内核模块insmod globalmem.ko
insmod: can't insert 'globalmem.ko': Device or resource busy
 

# 原因：

模块使用的是静态分配设备号的方式，而这个设备号已经被系统中的其他设备所占用。查看未被占用的

设备号的方法：`# cat /proc/devices`

# 加载模块之后使用lsmod查看模块
```
weiqifa@bsp-ubuntu1804:~/c/globalmem$ lsmod |grep global
globalmem              16384  0
weiqifa@bsp-ubuntu1804:~/c/globalmem$

weiqifa@bsp-ubuntu1804:~/c/globalmem$ cat /proc/devices |grep global
230 globalmem
weiqifa@bsp-ubuntu1804:~/c/globalmem$
```

# 创建设备文件节点
```
weiqifa@bsp-ubuntu1804:~/c/globalmem$ sudo mknod /dev/globalmem c 230 0
weiqifa@bsp-ubuntu1804:~/c/globalmem$ ls /dev/globalmem -al
crw-r--r-- 1 root root 230, 0 Dec 22 16:19 /dev/globalmem
weiqifa@bsp-ubuntu1804:~/c/globalmem$
```

# 读写设备文件
```
weiqifa@bsp-ubuntu1804:~/c/globalmem$ sudo chmod 777 /dev/globalmem
weiqifa@bsp-ubuntu1804:~/c/globalmem$ sudo echo "linux" > /dev/globalmem
weiqifa@bsp-ubuntu1804:~/c/globalmem$ cat /dev/globalmem
linux
cat: /dev/globalmem: No such device or address
weiqifa@bsp-ubuntu1804:~/c/globalmem$ cat /dev/globalmem
linux
cat: /dev/globalmem: No such device or address
weiqifa@bsp-ubuntu1804:~/c/globalmem$ sudo echo "linuxgdb" > /dev/globalmem
weiqifa@bsp-ubuntu1804:~/c/globalmem$ cat /dev/globalmem
linuxgdb
cat: /dev/globalmem: No such device or address
weiqifa@bsp-ubuntu1804:~/c/globalmem$
```

# 通过代码来读写设备文件
```
weiqifa@bsp-ubuntu1804:~/c/globalmem$ gcc app-main.c && ./a.out
str:LINUX,GDB
weiqifa@bsp-ubuntu1804:~/c/globalmem$
```

