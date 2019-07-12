#pragma once

BEGIN_NAMESPACE_SLEEP

struct DeltaTimeData
{
    DeltaTimeData()
    {
        init();
    }

    DeltaTimeData(DeltaTimeData&& other)
        : LastDts(std::move(other.LastDts))
        , FrameStartTime(other.FrameStartTime)
        , AmortizedDt(other.AmortizedDt)
    {
        LastDt = LastDts.begin();
    }

    DeltaTimeData(DeltaTimeData const& other) = default;

    using DTContainer = std::array<float, 10>;

    DTContainer LastDts;
    DTContainer::iterator LastDt;

    double FrameStartTime = 0.f;
    float AmortizedDt = 0.f;

    void init()
    {
        std::fill(LastDts.begin(), LastDts.end(), 0.f);
        LastDt = LastDts.begin();
    }
};

END_NAMESPACE_SLEEP
