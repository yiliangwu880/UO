rem 复制文件，去掉Tmp,修改本地开发配置使用
rem 复制linux新的导出文件到 win

set linux_path=G:\test\UO
set win_path=F:\codelib\UO



xcopy /y/i/e/s   %linux_path%\Center\DynamicCfg\* %win_path%\Center\DynamicCfg\
xcopy /y/i/e/s   %linux_path%\Zone\DynamicCfg\* %win_path%\Zone\DynamicCfg\
xcopy /y/i/e/s   %linux_path%\dbproxy_svr\cpp_cfg\* %win_path%\dbproxy_svr\cpp_cfg\
xcopy /y/i/e/s   %linux_path%\access_svr\acc_svr\DynamicCfg\* %win_path%\access_svr\acc_svr\DynamicCfg\




pause

