/*
	代码公共配置
*/
#pragma once

namespace
{
	//svr group id
	const uint16 CENTER_GROUP_ID = 10; 
	const uint16 ZONE_GROUP_ID = 1;  //zone svr id = [ZONE_GROUP_ID,MAX_ZONE_GROUP_ID] 
	const uint16 MAX_ZONE_GROUP_ID = 9;

	const uint32 SAVE_INTERVAL_SEC = 60 * 1;//save db interval 
	const uint32 MAX_CHAR_NUM_IN_ACC = 2; //CHAR NUM IN ACC
	const uint32 MAX_CHAR_NAME = 30;


}