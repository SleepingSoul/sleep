#pragma once
#include <Engine/Render/DrawCall.h>

BEGIN_NAMESPACE_SLEEP

// stores render data
// syncs it between update and render
class UpdateRenderBridge
{
public:
    CONST_REF_GETTER(getUpdatedData, m_updatedData)
    CONST_REF_GETTER(getLastUpdatedData, m_lastUpdatedData)
    REF_GETTER(getRenderedData, m_renderedData)

    // swaps last UPD data with current UPD data, clears current UPD data
    // atomic
    void renewLastUpdatedData()
    {
        threadSafeSwap(m_updatedData, m_lastUpdatedData);
    }
    // swaps RND data with last UPD data
    // atomic
    void renewRenderData()
    {
        threadSafeSwap(m_lastUpdatedData, m_renderedData);
    }

    void addUpdatedDrawCall(DrawCall&& drawCall)
    {
        m_updatedData.emplace_back(std::move(drawCall));
    }

    template <class... Args>
    void emplaceUpdatedDrawCall(Args&&... args)
    {
        m_updatedData.emplace_back(std::forward<Args>(args)...);
    }

    void f();

private:
    using LockGuard = std::lock_guard<std::mutex>;

    // constantly being rendered
    std::vector<DrawCall> m_renderedData;
    std::vector<DrawCall> m_lastUpdatedData;
    // constantly being updated - when UPD thread finishes 1 iteration, 
    std::vector<DrawCall> m_updatedData;

    std::mutex m_swapMutex;

    void threadSafeSwap(std::vector<DrawCall>& v1, std::vector<DrawCall>& v2)
    {
        LockGuard lk(m_swapMutex);
        v1.swap(v2);
    }
};

END_NAMESPACE_SLEEP
