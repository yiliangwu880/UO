# UO
uo server

# 开发目的
	演练一遍游戏实现，如何做得高效，代码质量高，可复用。
	同时看有没有希望设计好玩的游戏。

# tempCode
临时伪代码，目的快速演练一遍整体代码设计模式。后期参考他构建代码

#编译
external目录，参考每个项目说明，编译
access_svr目录，参考项目说明，编译
UO目录执行 sh clearBuild.sh

#tool
  exportCppCfg.sh --根据配置导出h文件供项目都配置用。配置文件格式有修改才需要使用。

# 目录介绍
access_svr   --接入服
center		 --中心服
zone		 --场景服
dbproxy_svr  --db代理服

db_driver	 --dbproxy_svr的驱动库
dbProto		 --db代理服和业务服协议
cppProto	 --业务服之间协议
com			 --多个进程复用的源码
bin			 --执行文件