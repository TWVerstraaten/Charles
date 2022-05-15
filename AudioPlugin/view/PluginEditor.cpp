#include "PluginEditor.h"

AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p) : AudioProcessorEditor(&p), processorRef(p) {
    initSlider(d_volumeSlider, 0.0, 1.0, 0.01, 1.0);
    d_volumeSlider.onValueChange = [&]() { p.setVolume(d_volumeSlider.getValue()); };
    d_volumeLabel.setText("volume", juce::dontSendNotification);
    d_volumeLabel.attachToComponent(&d_volumeSlider, false);
    d_volumeLabel.setJustificationType(juce::Justification::centred);

    initSlider(d_widthSlider, 0.0, 1.0, 0.01, 0.0);
    d_widthSlider.onValueChange = [&]() { p.setWidth(d_widthSlider.getValue()); };
    d_widthSlider.setSkewFactor(0.7);
    d_widthLabel.setText("width", juce::dontSendNotification);
    d_widthLabel.attachToComponent(&d_widthSlider, false);
    d_widthLabel.setJustificationType(juce::Justification::centred);

    initSlider(d_voicesSlider, 1, 64, 1, 1);
    d_voicesSlider.onValueChange = [&]() { p.setVoices(d_voicesSlider.getValue()); };
    d_voicesLabel.setText("voices", juce::dontSendNotification);
    d_voicesLabel.attachToComponent(&d_voicesSlider, false);
    d_voicesLabel.setJustificationType(juce::Justification::centred);

    setSize(400, 300);
}

void AudioPluginAudioProcessorEditor::initSlider(Slider& slider, double min, double max, double step, double initial) {
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setDoubleClickReturnValue(true, initial);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    slider.setNumDecimalPlacesToDisplay(10);
    addAndMakeVisible(slider);
    slider.setScrollWheelEnabled(true);
    slider.setRange(min, max, step);
    slider.setValue(initial);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized() {
    d_volumeSlider.setBounds(Rectangle(0, 30, 60, 75));
    d_widthSlider.setBounds(Rectangle(70, 30, 60, 75));
    d_voicesSlider.setBounds(Rectangle(140, 30, 60, 75));
}
