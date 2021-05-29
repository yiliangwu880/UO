#!/bin/bash

#ulimit -c 10240000
#ulimit -s 16384

start() {
	echo "start all svr"
	cd Center
	./center  # 后台启动 ./center d 
	cd ../Acc
	./acc_svr
	cd ../Zone1
	./zone
}

stop() {
	echo "stop all svr"
	cd Center
	./center stop
	cd ../Acc
	./acc_svr stop
	cd ../Zone1
	./zone stop
}

## 帮助函数
help () {
    echo "使用说明"
    echo "基本语法: sh run.sh [start|stop|restart|update] "
    echo "命令模块："
    echo "start                     启动游戏服务"
    echo "stop                      关闭游戏服务"
    echo "forcestop                 强制关闭游戏服务"
    echo ""
    exit 0
}
case $1 in
	start)		start $2 $3 ;;
	stop)		stop ${2};;

    *) help ;;
esac
