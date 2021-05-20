#!/bin/sh

../external/cpp_cfg/bin/export_cpp_cfg ../bin/centerCfg.txt \
../bin/zoneCfg.txt \
../bin/comCfg.txt


mv -f centerCfg.h ../center/cfg/
mv -f zoneCfg.h ../zone/cfg/
cp -f comCfg.h ../center/cfg/
cp -f comCfg.h ../zone/cfg/
rm comCfg.h