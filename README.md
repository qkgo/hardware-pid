PhysicalDrive



# 2020.1 
更新支持传入参数
```shell script
cmake-build-debug/cdevice.exe 1/2/3/4/5/6/7/8/9/10
配合wmic diskdrive使用
```


# TODO的文档:windows获取逻辑区号的物理分区
windows的磁盘操作之四——根据逻辑分区号获得物理磁盘号(转)
https://www.bbsmax.com/A/Ae5RQb2rJQ/
https://blog.csdn.net/pud_zha/article/details/19070511

表 1. Windows 设备名称（x = 0，1，2 等）
设备	路径名
软盘驱动器	A: B:
硬盘逻辑子区	C: D: E: . . .
物理驱动器	PhysicalDrivex
CD-ROM、DVD/ROM	CdRomx
磁带驱动器	Tapex
COM 端口	COMx


# 可靠的已用的文档doc from:
https://blog.csdn.net/tody_guo/article/details/42059125
https://www.bbsmax.com/A/x9J2WRWe56/


# 参考但不good
https://www.npmjs.com/search?q=systemInfo
http://chenzhiguo.cn/get_diskdriver_serialnumber/