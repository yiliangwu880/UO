#!/bin/sh

../external/cpp_cfg/bin/export_cpp_cfg ../bin/Center/centerCfg.txt \
../bin/Zone1/zoneCfg.txt \
../bin/comCfg.txt


mv -f centerCfg.h ../Center/Cfg/
mv -f zoneCfg.h ../Zone/Cfg/
cp -f comCfg.h ../Center/Cfg/
cp -f comCfg.h ../Zone/Cfg/
rm comCfg.h