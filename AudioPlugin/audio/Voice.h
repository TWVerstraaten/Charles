//
// Created by pc on 15-5-22.
//

#ifndef AUDIO_PLUGIN_EXAMPLE_VOICE_H
#define AUDIO_PLUGIN_EXAMPLE_VOICE_H

#include "../JuceHeader.h"
#include "Sound.h"

struct Voice : public juce::SynthesiserVoice {

    Voice() = default;

    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    using SynthesiserVoice::renderNextBlock;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    void setWidth(double width);
    void setVolume(double volume);
    void setVoices(size_t voices);

  private:
    struct LeftRightChannel {
        float left, right;
    };
    static LeftRightChannel getPanCoefficients(float pan);

    void fillCurrentSample(AudioBuffer<float>& outputBuffer, int startSample);

    juce::dsp::Oscillator<float> d_osc{[](float x) { return std::sin(x); }};
    juce::dsp::Gain<float>       d_gain;
    juce::ADSR                   d_adsr;
    juce::ADSR::Parameters       d_adsrParameters = {0.01f, 0.01f, 1.0f, 0.2f};
    juce::AudioBuffer<float>     d_audioBuffer;

    double d_width      = 0.0;
    double currentAngle = 0.0;
    double angleDelta   = 0.0;
    double level        = 0.0;
    double tailOff      = 0.0;
    double d_volume     = 0.0;
    size_t d_voices     = 1;
};

#endif // AUDIO_PLUGIN_EXAMPLE_VOICE_H
