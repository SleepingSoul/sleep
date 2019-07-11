#pragma once

BEGIN_NAMESPACE_SLEEP

struct DeltaTimeData
{
    DeltaTimeData()
    {
        std::fill(LastDts.begin(), LastDts.end(), 0.f);
        LastDt = LastDts.begin();
    }

    using DTContainer = std::array<float, 10>;

    DTContainer LastDts;
    DTContainer::iterator LastDt;

    double FrameStartTime = 0.f;
    float AmortizedDt = 0.f;
};

END_NAMESPACE_SLEEP
