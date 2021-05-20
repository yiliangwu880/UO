
rem 复制linux新的导出文件到 win

set linux_path=G:\test\UO
set win_path=F:\codelib\UO



xcopy /y/i/e/s   %linux_path%\center\cfg\* %win_path%\center\cfg\
xcopy /y/i/e/s   %linux_path%\zone\cfg\* %win_path%\zone\cfg\




pause

