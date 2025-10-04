
#include "WindowUtility.hpp"

#ifdef _WIN32
#define _WIN32_WINNT 0x0603
#include <shellscalingapi.h>
#include <windows.h>
#pragma comment(lib, "Shcore.lib")
#elif defined(__APPLE__)
#include <CoreGraphics/CoreGraphics.h>
#endif

float MCEngine::WindowUtility::GetDPIScale()
{
#ifdef _WIN32

    HMONITOR monitor = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTONEAREST);
    UINT dpiX = 96, dpiY = 96;
    HRESULT hr = GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY);
    if (FAILED(hr))
    {
        dpiX = dpiY = 96;
    }
    return dpiX / 96.0f;

#elif defined(__APPLE__)

    CGDirectDisplayID displayID = CGMainDisplayID();
    CGSize displaySize = CGDisplayScreenSize(displayID);
    size_t pixelWidth = CGDisplayPixelsWide(displayID);
    float scaleX = (float)pixelWidth / (displaySize.width / 25.4f * 72.0f);
    return scaleX;

#else // Linux
    return 1.0f;
#endif
}