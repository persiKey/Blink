#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    inline constexpr int WINDOWS_WIDTH = 500;
    inline constexpr int WINDOWS_HEIGHT = 650;

    namespace Time
    {
        inline constexpr int SECONDS_MAX = 60;
        inline constexpr int SECONDS_MIN = 0;

        inline constexpr int MINUTES_MAX = 10;
        inline constexpr int MINUTES_MIN = 1;

        inline constexpr int SECONDS_STEP = 5;
        inline constexpr int MINUTES_STEP = 1;

        inline constexpr int SECONDS_DEFAULT = 30;
        inline constexpr int MINUTES_DEFAULT = 4;
    }
}

#endif // CONSTANTS_H
