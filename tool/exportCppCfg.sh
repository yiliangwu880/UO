#!/bin/sh

cd ../bin/Center
../../external/cpp_cfg/bin/export_cpp_cfg centerCfg.txt 
mv -f centerCfg.h ../../Center/DynamicCfg/
cd - # tool 

cd ../bin/Zone1
../../external/cpp_cfg/bin/export_cpp_cfg zoneCfg.txt 
mv -f zoneCfg.h ../../Zone/DynamicCfg/
cd - # tool 

cd ../bin/dbproxy_svr
../../external/cpp_cfg/bin/export_cpp_cfg Cfg.txt 
mv -f Cfg.h ../../dbproxy_svr/DynamicCfg/
cd - # tool 


cd ../bin/Center
../../external/cpp_cfg/bin/export_cpp_cfg ../comCfg.txt
cp -f comCfg.h ../../Center/DynamicCfg/
cp -f comCfg.h ../../Zone/DynamicCfg/
cp -f comCfg.h ../../access_svr/acc_svr/DynamicCfg/
cp -f comCfg.h ../../dbproxy_svr/DynamicCfg/
rm comCfg.h
