//
// Created by pc on 15-5-22.
//

#include "Voice.h"

#include "../misc/functions.h"

bool Voice::canPlaySound(juce::SynthesiserSound* sound) {
    return dynamic_cast<Sound*>(sound) != nullptr;
}

void Voice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int) {
    d_adsr.noteOn();
    d_adsr.setParameters(d_adsrParameters);
    d_osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));

    //    currentAngle = 0.0;
    //    level        = d_volume * velocity;
    //    tailOff      = 0.0;
    //
    //    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    //    auto cyclesPerSample = cyclesPerSecond / getSampleRate();
    //
    //    angleDelta = cyclesPerSample;
}

void Voice::stopNote(float, bool allowTailOff) {
    d_adsr.noteOff();
    //    if (allowTailOff) {
    //        // start a tail-off by setting this flag. The render callback will pick up on
    //        // this and do a fade out, calling clearCurrentNote() when it's finished.
    //
    //        if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
    //            tailOff = 1.0;  // stopNote method could be called more than once.
    //    } else {
    //        // we're being told to stop playing immediately, so reset everything..
    //        clearCurrentNote();
    //        angleDelta = 0.0;
    //    }
}

void Voice::pitchWheelMoved(int) {
}

void Voice::fillCurrentSample(AudioBuffer<float>& outputBuffer, int startSample) {
    float left  = 0.0f;
    float right = 0.0f;
    for (size_t i = 0; i != 10; ++i) {
        float interpolant = d_voices == 1 ? 0.0f : (static_cast<float>(2 * i) / static_cast<float>(d_voices - 1)) - 1.0f;
        auto  panLr       = getPanCoefficients(interpolant);

        auto signal = 2.0 * fns::modOne(0.5 * currentAngle / (1.0f + 0.3f * d_width * interpolant)) - 1.0;
        signal      = std::sin(M_PI * signal);
        left += signal * panLr.left;
        right += signal * panLr.right;
    }

    outputBuffer.addSample(0, startSample, level * left);
    outputBuffer.addSample(1, startSample, level * right);
}

void Voice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) {
    juce::dsp::AudioBlock<float> audioBlock{outputBuffer};
    d_osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    d_gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    d_adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

    //    if (angleDelta != 0.0) {
    //        if (tailOff > 0.0) {
    //            while (--numSamples >= 0) {
    //                fillCurrentSample(outputBuffer, startSample);
    //                currentAngle += angleDelta;
    //                ++startSample;
    //                tailOff *= 0.99;
    //
    //                if (tailOff <= 0.005) {
    //                    clearCurrentNote();
    //
    //                    angleDelta = 0.0;
    //                    break;
    //                }
    //            }
    //        } else {
    //            while (--numSamples >= 0) {
    //                fillCurrentSample(outputBuffer, startSample);
    //                currentAngle += angleDelta;
    //                ++startSample;
    //            }
    //        }
    //    }
}

void Voice::controllerMoved(int, int) {
}

void Voice::setWidth(double width) {
    d_width = width;
}

void Voice::setVolume(double volume) {
    d_volume = volume;
}

void Voice::setVoices(size_t voices) {
    d_voices = voices;
}

Voice::LeftRightChannel Voice::getPanCoefficients(float pan) {
    return {std::min(1.0f, 1.0f - pan), std::min(1.0f, pan + 1.0f)};
}

void Voice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    d_adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec{};
    spec.maximumBlockSize = static_cast<uint32>(samplesPerBlock);
    spec.sampleRate       = sampleRate;
    spec.numChannels      = static_cast<uint32>(outputChannels);

    d_osc.prepare(spec);
    d_gain.prepare(spec);

    d_gain.setGainLinear(0.5f);
}
