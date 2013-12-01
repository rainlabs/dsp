#include "signal.hpp"

bool Signal::loadFromFile(const std::string& filename)
{
    SoundBuffer::loadFromFile(filename);
    m_data.clear();

    for(int i = 0; i < getSampleCount(); i++) {
        m_data.push_back( getSamples()[i] );
    }
}

void Signal::setFftSize(size_t length)
{
    m_fft = Aquila::FftFactory::getFft(length);
}

std::shared_ptr< Aquila::Fft > Signal::getFft()
{
    return m_fft;
}

//protected

void Signal::fftInitialize()
{
    m_fft = Aquila::FftFactory::getFft(128);
}
