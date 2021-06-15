#!/bin/bash

#ulimit -c 10240000
#ulimit -s 16384

start() {
	echo "start all svr"

	cd dbproxy_svr
	./dbproxy_svr d
	cd -

	cd Acc
	./acc_svr d
	cd -

	sleep 1

	cd Center
	./center d  # 后台启动 ./center d 
	cd -
	

	cd Zone1
	./zone d
	cd -

}

stop() {
	echo "stop all svr"
	cd dbproxy_svr
	./dbproxy_svr stop
	cd -

	cd Center
	./center stop
	cd -

	cd Acc
	./acc_svr stop
	cd -

	cd Zone1
	./zone stop
	cd -

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
