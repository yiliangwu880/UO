
rem 复制linux新的导出文件到 win

set linux_path=G:\test\UO
set win_path=F:\codelib\UO



xcopy /y/i/e/s   %linux_path%\Center\Cfg\* %win_path%\Center\Cfg\
xcopy /y/i/e/s   %linux_path%\Zone\Cfg\* %win_path%\Zone\Cfg\




pause

