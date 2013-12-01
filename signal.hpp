#ifndef Signal_HPP
#define Signal_HPP

#include <iostream>
#include <memory>

#include <SFML/Audio/SoundBuffer.hpp>
//#include <SFML/Audio/Sound.hpp>
#include <aquila/global.h>
#include <aquila/source/generator/SineGenerator.h>

#include <aquila/transform/FftFactory.h>

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
    std::shared_ptr< Aquila::Fft > getFft();

protected:
    void fftInitialize();
    std::shared_ptr< Aquila::Fft > m_fft;
};

#endif // Signal_HPP
