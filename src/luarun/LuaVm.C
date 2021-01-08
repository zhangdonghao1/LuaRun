#include "LuaVm.h"
#include "mythread.h"

LuaCo::LuaCo()
{
}

LuaCo::~LuaCo()
{
}

LuaVm::LuaVm()
{
    m_L = luaL_newstate();
    luaL_openlibs(m_L);
}

LuaVm::~LuaVm()
{
}

/*--------------------------------------------------------------
 *  函数名称：iniLuaVms
 *  功能描述：初始化lua虚拟机
 *  参数说明：
 *  返 回 值：true=成功；false=出错；
 *  备    注：
 */
bool LuaVm::iniLuaVm()
{
    // 创建 LuaVms 线程：指定调度优先级别为 50
	int res = createThread(&m_tid, SCHED_RR, 50 /* sched_priority */, 1024 * 1024 * 10, LuaVms::vmsThreadRun, this);
	if (res != 0)
	{
		// error("LuaVms(%s) create thread error: %s", serviceId, strerror(res));
		return false;
	}
}