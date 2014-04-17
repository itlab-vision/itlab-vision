#include "perf_utils.hpp"

using namespace cv;
using namespace perf;

double getRunningTime(performance_metrics& metrics)
{
    return metrics.gmean / metrics.frequency * 1000.0;
}
