#pragma once

#include "../audio/PluginProcessor.h"

class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
  public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

  private:
    AudioPluginAudioProcessor& processorRef;
    juce::Slider               d_widthSlider;
    juce::Label                d_widthLabel;
    juce::Slider               d_voicesSlider;
    juce::Label                d_voicesLabel;
    juce::Slider               d_volumeSlider;
    juce::Label                d_volumeLabel;

    void initSlider(Slider& slider, double min, double max, double step, double initial);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
