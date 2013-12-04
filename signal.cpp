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
}

void Signal::setOverlapSize(size_t length)
{float
    m_overlapSize = length;
}

QVector< QVector3D > Signal::getSpectrum()
{
    QVector< QVector3D > result;

    auto fft      = Aquila::FftFactory::getFft(m_fftSize);
    auto * window = new Aquila::BlackmanWindow(m_fftSize);

    // TODO if m_data.size() < window.size()

    int ncol = (int) (m_data.size() - m_overlapSize) / (m_fftSize - m_overlapSize);
    QVector< int > colIndex, rowIndex;

    for(int i = 0; i < ncol; i++) {
        colIndex.push_back( i * (m_fftSize - m_overlapSize) + 1 );
    }

    for(int i = 1; i <= m_fftSize; i++) {
        rowIndex.push_back( i );
    }

//    if (m_data.size() < (m_fftSize + colIndex[ncol] - 1)) {
//        m_data[m_fftSize + colIndex[ncol] - 1] = 0;
//    }

    QVector< double > fftInput(m_fftSize, 0.);
    QVector< Aquila::SpectrumType > fftValues;

    for(int i = 0; i < ncol; i++) {
        for(int j = 0; j < m_fftSize; j++) {
            fftInput[j] = m_data[colIndex[i] + rowIndex[j] - 1] * window->toArray()[j];
        }
        fftValues.push_back( fft->fft(fftInput.constData()) );
    }
    size_t select = m_fftSize / 2 + 1;
    for(int i = 0; i < fftValues.size(); i++) {
        fftValues[i].resize(select);
    }

    QVector< float > f, t;
    for(int i = 0; i < select; i++) {
        f.push_back( 2. / m_fftSize * i );
    }
    for(auto i : colIndex) {
        t.push_back( (i - 1) / 2. );
    }

    for(int i = 0; i < fftValues.size(); i++) {
        for(int j = 0; j < fftValues[i].size(); j++) {
            result.push_back( QVector3D(t[i], f[j], 20. * log10(std::abs(fftValues[i][j] + 0.000001))) );
        }
    }

    return result;
}

//protected

void Signal::fftInitialize()
{
    m_fftSize = 256;
    m_overlapSize = 128;
}
