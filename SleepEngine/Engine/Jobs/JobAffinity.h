#pragma once

BEGIN_NAMESPACE_SLEEP

enum class JobAffinity
{
    Render, // executed only on the render thread
    Generic, // executed on any of worker threads
    Count,
    Invalid
};

END_NAMESPACE_SLEEP
