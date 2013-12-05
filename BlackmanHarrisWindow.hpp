#ifndef BLACKMANHASRRISWINDOW_HPP
#define BLACKMANHASRRISWINDOW_HPP

#include <aquila/global.h>
#include <aquila/source/SignalSource.h>

namespace Aquila {
    /**
     * Blackman-Harris window.
     */
    class AQUILA_EXPORT BlackmanHarrisWindow : public SignalSource
    {
    public:
        BlackmanHarrisWindow(std::size_t size);
    };
}
#endif // BLACKMANHASRRISWINDOW_HPP
