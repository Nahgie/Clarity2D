module;
    #include "c2d_dx.h"
export module c2d.system.component.timer;

import c2d.core.types;

using namespace c2d;
using namespace std::chrono;

export namespace c2d
{
    class Timer final
    {
    private:
        c2time_point _startPoint;
        c2time_point _endPoint;

    private:
        void Start() noexcept { _startPoint = c2clock::now(); }
        void Stop()  noexcept { _endPoint   = c2clock::now(); }

        uint64 ElapsedTime() const noexcept
        {
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(_endPoint - _startPoint);
            return static_cast<uint64>(ms.count());
        }

        float64 HighElapsedTime() const noexcept
        {
            auto ms = std::chrono::duration_cast<std::chrono::duration<float64>>(_endPoint - _startPoint);
            return static_cast<float64>(ms.count());
        }
    };
}