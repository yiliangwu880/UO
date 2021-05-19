# UO
uo server

# 开发目的
	演练一遍游戏实现，如何做得高效，代码质量高，可复用。
	同时看有没有希望设计好玩的游戏。

# tempCode
临时伪代码，目的快速演练一遍整体代码设计模式。后期参考他构建代码

#编译
external目录，参考每个项目说明，全部编译
UO目录执行 sh clearBuild.sh

# 目录介绍
access_svr   --接入服
Center		 --中心服
Zone		 --场景服
dbproxy_svr  --db代理服

db_driver	 --dbproxy_svr的驱动库
dbProto		 --db代理服和业务服协议
CppProto	 --业务服之间协议
Com			 --多个进程复用的源码
bin			 --执行文件