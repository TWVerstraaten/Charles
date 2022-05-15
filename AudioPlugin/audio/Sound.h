//
// Created by pc on 15-5-22.
//

#ifndef AUDIO_PLUGIN_EXAMPLE_SOUND_H
#define AUDIO_PLUGIN_EXAMPLE_SOUND_H

#include "../JuceHeader.h"

struct Sound : public juce::SynthesiserSound {
    Sound() = default;

    bool appliesToNote(int /*midiNoteNumber*/) override;
    bool appliesToChannel(int /*midiChannel*/) override;
};

#endif // AUDIO_PLUGIN_EXAMPLE_SOUND_H
