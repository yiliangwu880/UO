#!/bin/sh

cd ../bin/Center
../../external/cpp_cfg/bin/export_cpp_cfg centerCfg.txt 
mv -f centerCfg.h ../../Center/Cfg/
cd - # tool 

cd ../bin/Zone1
../../external/cpp_cfg/bin/export_cpp_cfg zoneCfg.txt 
mv -f zoneCfg.h ../../Zone/Cfg/
cd - # tool 

cd ../bin/dbproxy_svr
../../external/cpp_cfg/bin/export_cpp_cfg Cfg.txt 
mv -f Cfg.h ../../dbproxy_svr/Cfg/
cd - # tool 


cd ../bin/Center
../../external/cpp_cfg/bin/export_cpp_cfg ../comCfg.txt
cp -f comCfg.h ../../Center/Cfg/
cp -f comCfg.h ../../Zone/Cfg/
cp -f comCfg.h ../../access_svr/acc_svr/Cfg/
cp -f comCfg.h ../../dbproxy_svr/Cfg/
rm comCfg.h
