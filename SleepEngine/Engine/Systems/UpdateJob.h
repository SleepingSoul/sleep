#pragma once
#include <Engine/Jobs/Job.h>

BEGIN_NAMESPACE_SLEEP

std::unique_ptr<DelegateJob> createUpdateJob();

END_NAMESPACE_SLEEP
