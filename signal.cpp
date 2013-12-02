#include "signal.hpp"

bool Signal::loadFromFile(const std::string& filename)
{
    SoundBuffer::loadFromFile(filename);
    m_data.clear();

    // normalize magnitude
    double max = ((1) << 15) - 1; // max int value
//    double max = *std::max_element(getSamples(), getSamples()+getSampleCount());

    for(int i = 0; i < getSampleCount(); i++) {
        m_data.push_back( getSamples()[i] / max );
    }
}

void Signal::setFftSize(size_t length)
{
    m_fftSize = length;
    m_fft = Aquila::FftFactory::getFft(length);
}

std::shared_ptr< Aquila::Fft > Signal::getFft()
{
    return m_fft;
}

QVector< QVector<double> > Signal::getSpectrum()
{
    QVector< QVector<double> > result;

    for(int i = 0; i < m_data.size(); i += m_fftSize) {
        if (i + m_fftSize >= m_data.size())
            break;
        Aquila::SpectrumType fft =  m_fft->fft(toArray()+i);
        QVector<double> temp;
        for(auto v : fft) {
            temp.push_back( v.real() );
        }
        result.push_back( temp );
    }

    return result;
}

//protected

void Signal::fftInitialize()
{
    m_fftSize = 128;
    m_fft = Aquila::FftFactory::getFft(m_fftSize);
}
