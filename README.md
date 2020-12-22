# globalmem

看 linux 设备驱动开发详解时，字符设备驱动一章，注册globalmem驱动时，出现如下错误：

# 加载内核模块insmod globalmem.ko
insmod: can't insert 'globalmem.ko': Device or resource busy
 

# 原因：

模块使用的是静态分配设备号的方式，而这个设备号已经被系统中的其他设备所占用。查看未被占用的

设备号的方法：`# cat /proc/devices`
