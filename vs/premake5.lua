--
-- premake5 file to build RecastDemo
-- http://premake.github.io/
--
require "lib"

local action = _ACTION or ""
local outdir = action


local comInclude={ 
	"../external/mysql_connector/include/",
	"../external",
	"../external/svr_util/include",
	"../external/libevent_cpp/include",
	"../external/libevent_cpp/External/libevent-2.1.8-stable/out/include/",
	"../com/",
	"../db_driver/include/",
	"../external/cpp_cfg/com/",
	"../dbProto/",
	"../cppProto/",
	"../access_svr/acc_driver/include/",
}

WorkSpaceInit  "UO"

Project "other"
	files {
	"../bin/**",
	"../cppProto/**",
	"../dbProto/**",
	"../tool/**",
	"../tempCode/**",
	"../doc/**",
	"../external/**",
	"../*.txt",
	"../*.md",
	}

Project "vs"
	files {
	"../vs/*.lua",
	"../vs/*.txt",
	}

Project "com"
	IncludeFile(comInclude)
	SrcPath { 
		"../com/**",  --**递归所有子目录，指定目录可用 "cc/*.cpp" 或者  "cc/**.cpp"
	}

Project "access_svr"
	IncludeFile(
	{
	"../access_svr/external",
	})
	SrcPath { 
		"../access_svr/acc_driver/**",
		"../access_svr/acc_svr/**",
		"../access_svr/acc_proto/**",
	}
	files {
		"../access_svr/*.sh",
		"../access_svr/*.txt",
		"../access_svr/*.md",
		"../access_svr/*.lua",
	}


Project "Center"
	IncludeFile(comInclude)
	IncludeFile { 
		"./Mgr/",
		"./Cfg/",
	}

	SrcPath { 
		"../center/**",  --**递归所有子目录，指定目录可用 "cc/*.cpp" 或者  "cc/**.cpp"
	}

Project "Zone"
	IncludeFile(comInclude)
	IncludeFile { 
		"./Mgr/",
		"./Cfg/",
	}

	SrcPath { 
		"../Zone/**",  
	}

 Project "dbproxy_svr"
	IncludeFile(comInclude)
	SrcPath { 
		"../dbproxy_svr/**",  
	}  
 
Project "db_driver"
	IncludeFile(comInclude)

	SrcPath { 
		"../db_driver/src/**",  
		"../db_driver/include/**",
	}
	




