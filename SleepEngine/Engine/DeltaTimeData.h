#pragma once

BEGIN_NAMESPACE_SLEEP

struct DeltaTimeData
{
    //using DeltaTime = TDeltaTime;

    DeltaTimeData()
    {
        std::fill(LastDts.begin(), LastDts.end(), 0.f);
        LastDtIter = LastDts.begin();
    }

    DeltaTimeData(DeltaTimeData&& other) = delete;
    DeltaTimeData(DeltaTimeData const& other) = delete;

    using DTContainer = std::array<float, 10>;

    DTContainer LastDts;
    DTContainer::iterator LastDtIter;

    double FrameStartTime = 0.f;
    std::atomic<float> AmortizedDt = 0.f;
};

END_NAMESPACE_SLEEP
