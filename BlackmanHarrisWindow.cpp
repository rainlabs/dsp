#include "BlackmanHarrisWindow.hpp"

namespace Aquila {
    /**
    * Creates Blackman-Harris window of given size.
    *
    * @param size window length
    */
    BlackmanHarrisWindow::BlackmanHarrisWindow(std::size_t size): SignalSource()
    {
        m_data.reserve(size);
        for (std::size_t n = 0; n < size; n++) {
            m_data.push_back(
                        0.35875 - 0.48829 * cos(2. * M_PI * n / (size - 1.)) +
                        0.14128 * cos(4. * M_PI * n / (size - 1)) -
                        0.01168 * cos(6. * M_PI * n / (size - 1))
            );
        }
    }
}
