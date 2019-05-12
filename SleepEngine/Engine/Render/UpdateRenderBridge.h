#pragma once
#include <Engine/Render/DrawCall.h>

BEGIN_NAMESPACE_SLEEP

// stores render data
// syncs it between update and render
class UpdateRenderBridge
{
public:
    std::vector<DrawCall> const& getUpdatedData() { return m_updatedData; }
    std::vector<DrawCall> const& getLastUpdatedData() { return m_lastUpdatedData; }
    std::vector<DrawCall>& getRenderedData() { return m_renderedData; }

    // swaps last UPD data with current UPD data, clears current UPD data
    // atomic
    void renewLastUpdatedData()
    {
        LockGuard lk(m_swapMutex);
        m_updatedData.swap(m_lastUpdatedData);
        m_updatedData.clear();
    }

    // swaps RND data with last UPD data
    // atomic
    void renewRenderData()
    {
        threadSafeSwap(m_lastUpdatedData, m_renderedData);
    }

    template <class... Args>
    void emplaceUpdatedDrawCall(Args&&... args)
    {
        m_updatedData.emplace_back(std::forward<Args>(args)...);
    }

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
