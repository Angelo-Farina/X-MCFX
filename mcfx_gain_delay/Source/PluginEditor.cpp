/*
 ==============================================================================
 
 This file is part of the mcfx (Multichannel Effects) plug-in suite.
 Copyright (c) 2013/2014 - Matthias Kronlachner
 www.matthiaskronlachner.com
 
 Permission is granted to use this software under the terms of:
 the GPL v2 (or any later version)
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 ambix is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Mcfx_gain_delayAudioProcessorEditor::Mcfx_gain_delayAudioProcessorEditor (Mcfx_gain_delayAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    // This is where our plugin's editor size is set.
    setSize (400, 300);
}

Mcfx_gain_delayAudioProcessorEditor::~Mcfx_gain_delayAudioProcessorEditor()
{
}

//==============================================================================
void Mcfx_gain_delayAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!",
                      0, 0, getWidth(), getHeight(),
                      Justification::centred, 1);
}
