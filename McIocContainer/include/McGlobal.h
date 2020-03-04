#pragma once

#include "McMacroGlobal.h"

#include <functional>

namespace Mc {
namespace Ioc {

// 单位: ms
/*!
 * \brief waitForExecFunc
 *        注意：如果当前线程本身处于退出状态，那么此函数会立即返回
 * \param func
 * \param timeout
 * \return 
 */
MCIOCCONTAINER_EXPORT bool waitForExecFunc(
        const std::function<bool()> &func
        , qint64 timeout = -1) noexcept;

}
}
