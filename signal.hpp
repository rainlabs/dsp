#ifndef Signal_HPP
#define Signal_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <QVector>
#include <QVector3D>

#include <SFML/Audio/SoundBuffer.hpp>
//#include <SFML/Audio/Sound.hpp>
#include <aquila/global.h>
#include <aquila/source/generator/SineGenerator.h>

#include <aquila/transform/FftFactory.h>
#include <aquila/source/window/BlackmanWindow.h>

#include <BlackmanHarrisWindow.hpp>

/**
 * @brief The Signal class as sound buffer and sine or WhiteNoise generator
 */
class Signal : public sf::SoundBuffer, public Aquila::SineGenerator
{
public:
    Signal() : SoundBuffer(), SineGenerator(0) {fftInitialize();}
    Signal(const SoundBuffer &copy) : SoundBuffer(copy), SineGenerator(0) {fftInitialize();}
    Signal(Aquila::FrequencyType sampleFrequency) : SoundBuffer(), SineGenerator(sampleFrequency) {fftInitialize();}
    bool loadFromFile(const std::string& filename);

    void setFftSize(size_t length);
    void setOverlapSize(size_t length);
    QVector< QVector3D > getSpectrum();

protected:
    void fftInitialize();
    size_t m_fftSize, m_overlapSize;
};

#endif // Signal_HPP
