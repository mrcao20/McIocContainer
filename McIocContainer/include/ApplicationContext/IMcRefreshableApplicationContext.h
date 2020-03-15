#pragma once

#include "../McMacroGlobal.h"

MC_INTERFACE IMcRefreshableApplicationContext {
public:
    virtual ~IMcRefreshableApplicationContext() = default;
    
    /*************************************************
     @Funcname  refresh
     @Brief     刷新上下文，初始化上下文内容，同时初始化bean容器，使bean容器中对象全部加载
     @Params
     @Return
     @Author    mrcao
     @Date      2020-02-23
    **************************************************/
    virtual void refresh(QThread *thread = nullptr) noexcept = 0;
};
