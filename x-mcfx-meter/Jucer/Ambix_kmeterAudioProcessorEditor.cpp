/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.1

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Ambix_kmeterAudioProcessorEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Ambix_kmeterAudioProcessorEditor::Ambix_kmeterAudioProcessorEditor (Ambix_kmeterAudioProcessor* ownerFilter)
    : AudioProcessorEditor (ownerFilter)
{
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Ambix::kmeter")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::yellow);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sld_hold = new Slider ("new slider"));
    sld_hold->setTooltip (TRANS("hold time in ms"));
    sld_hold->setRange (0, 5, 0.1);
    sld_hold->setSliderStyle (Slider::Rotary);
    sld_hold->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 18);
    sld_hold->setColour (Slider::rotarySliderFillColourId, Colours::white);
    sld_hold->addListener (this);

    addAndMakeVisible (sld_fall = new Slider ("new slider"));
    sld_fall->setTooltip (TRANS("fall dB/s"));
    sld_fall->setRange (0, 99, 1);
    sld_fall->setSliderStyle (Slider::Rotary);
    sld_fall->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 18);
    sld_fall->setColour (Slider::rotarySliderFillColourId, Colours::white);
    sld_fall->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("hold [s]\n")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("fall [dB/s]\n")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (tgl_pkhold = new ToggleButton ("new toggle button"));
    tgl_pkhold->setButtonText (TRANS("peak hold"));
    tgl_pkhold->addListener (this);
    tgl_pkhold->setColour (ToggleButton::textColourId, Colours::white);

    addAndMakeVisible (sld_offset = new Slider ("new slider"));
    sld_offset->setTooltip (TRANS("offset scale"));
    sld_offset->setRange (-36, 18, 1);
    sld_offset->setSliderStyle (Slider::LinearVertical);
    sld_offset->setTextBoxStyle (Slider::NoTextBox, true, 40, 18);
    sld_offset->setColour (Slider::rotarySliderFillColourId, Colours::white);
    sld_offset->addListener (this);

    cachedImage_meter_scale_png = ImageCache::getFromMemory (meter_scale_png, meter_scale_pngSize);
    cachedImage_meter_scale_png = ImageCache::getFromMemory (meter_scale_png, meter_scale_pngSize);

    //[UserPreSize]
    //[/UserPreSize]

    setSize (500, 210);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Ambix_kmeterAudioProcessorEditor::~Ambix_kmeterAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    sld_hold = nullptr;
    sld_fall = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    tgl_pkhold = nullptr;
    sld_offset = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Ambix_kmeterAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1a1a1a));

    g.setColour (Colours::black);
    g.drawImage (cachedImage_meter_scale_png,
                 39, 26, 17, 167,
                 0, 0, cachedImage_meter_scale_png.getWidth(), cachedImage_meter_scale_png.getHeight());

    g.setColour (Colours::black);
    g.drawImage (cachedImage_meter_scale_png,
                 348, 29, 17, 167,
                 0, 0, cachedImage_meter_scale_png.getWidth(), cachedImage_meter_scale_png.getHeight());

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Ambix_kmeterAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label->setBounds (0, 0, 104, 16);
    sld_hold->setBounds (166, 0, 70, 24);
    sld_fall->setBounds (307, 0, 70, 24);
    label2->setBounds (111, 3, 64, 16);
    label3->setBounds (239, 3, 77, 16);
    tgl_pkhold->setBounds (382, 0, 91, 24);
    sld_offset->setBounds (4, 23, 18, 167);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Ambix_kmeterAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sld_hold)
    {
        //[UserSliderCode_sld_hold] -- add your slider handling code here..
        //[/UserSliderCode_sld_hold]
    }
    else if (sliderThatWasMoved == sld_fall)
    {
        //[UserSliderCode_sld_fall] -- add your slider handling code here..
        //[/UserSliderCode_sld_fall]
    }
    else if (sliderThatWasMoved == sld_offset)
    {
        //[UserSliderCode_sld_offset] -- add your slider handling code here..
        //[/UserSliderCode_sld_offset]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void Ambix_kmeterAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tgl_pkhold)
    {
        //[UserButtonCode_tgl_pkhold] -- add your button handler code here..
        //[/UserButtonCode_tgl_pkhold]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Ambix_kmeterAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor"
                 constructorParams="Ambix_kmeterAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor (ownerFilter)"
                 snapPixels="8" snapActive="0" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="500" initialHeight="210">
  <BACKGROUND backgroundColour="ff1a1a1a">
    <IMAGE pos="39 26 17 167" resource="meter_scale_png" opacity="1" mode="0"/>
    <IMAGE pos="348 29 17 167" resource="meter_scale_png" opacity="1" mode="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="b45e45d811b90270" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 104 16" textCol="ffffff00" edTextCol="ff000000"
         edBkgCol="0" labelText="Ambix::kmeter" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="d5c1a3078147bf28" memberName="sld_hold"
          virtualName="" explicitFocusOrder="0" pos="166 0 70 24" tooltip="hold time in ms"
          rotarysliderfill="ffffffff" min="0" max="5" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="18" skewFactor="1"/>
  <SLIDER name="new slider" id="edc665213f83e06b" memberName="sld_fall"
          virtualName="" explicitFocusOrder="0" pos="307 0 70 24" tooltip="fall dB/s"
          rotarysliderfill="ffffffff" min="0" max="99" int="1" style="Rotary"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="40"
          textBoxHeight="18" skewFactor="1"/>
  <LABEL name="new label" id="e30a8f204d299927" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="111 3 64 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="hold [s]&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a7997dcae0239c4c" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="239 3 77 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="fall [dB/s]&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="14961239a30aaf85" memberName="tgl_pkhold"
                virtualName="" explicitFocusOrder="0" pos="382 0 91 24" txtcol="ffffffff"
                buttonText="peak hold" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="new slider" id="42b67ea3b0dcd357" memberName="sld_offset"
          virtualName="" explicitFocusOrder="0" pos="4 23 18 167" tooltip="offset scale"
          rotarysliderfill="ffffffff" min="-36" max="18" int="1" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="40"
          textBoxHeight="18" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: meter_scale_png, 6973, "../Source/meter_scale.png"
static const unsigned char resource_Ambix_kmeterAudioProcessorEditor_meter_scale_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,17,0,0,0,167,8,6,0,0,0,247,254,183,146,0,0,23,246,105,67,
67,80,73,67,67,32,80,114,111,102,105,108,101,0,0,88,195,173,89,119,84,20,207,147,239,153,141,176,44,97,201,57,231,156,115,206,81,114,18,132,37,47,153,37,163,68,17,5,20,21,20,9,98,0,68,64,16,19,81,68,65,
48,34,34,40,130,17,69,4,20,253,2,138,136,164,27,16,253,221,253,238,238,143,123,239,250,189,158,249,80,83,93,93,93,85,221,93,197,2,192,117,141,28,29,29,14,51,2,16,17,25,71,117,52,55,18,112,247,240,20,192,
189,6,48,96,2,36,32,8,228,200,254,177,209,134,246,246,54,224,127,109,63,70,0,180,249,30,150,221,148,5,254,111,141,41,32,48,214,31,0,200,30,193,126,1,177,254,17,8,190,6,0,170,205,63,154,26,7,0,102,83,158,
72,98,92,244,38,62,130,96,22,42,162,32,130,171,55,113,240,111,220,182,137,253,126,227,254,45,30,103,71,99,4,143,3,128,167,35,147,169,193,0,16,103,17,186,64,130,127,48,34,135,158,14,0,44,41,50,128,18,137,
176,10,32,88,207,63,132,28,0,0,151,47,194,35,19,17,17,181,137,15,34,88,194,239,63,201,9,254,47,50,253,254,202,36,147,131,255,226,223,107,217,106,120,19,74,108,116,56,57,25,252,127,183,136,240,248,63,115,
240,33,157,46,54,204,201,26,121,179,33,118,75,242,39,155,58,33,152,3,193,5,33,129,150,54,219,244,154,232,56,35,199,109,122,39,37,206,210,121,211,70,8,126,26,18,111,225,178,141,167,227,195,92,12,17,204,
131,224,213,176,40,235,77,126,196,78,48,71,164,159,221,14,4,147,16,44,226,31,107,236,249,91,38,172,150,18,226,236,182,205,99,19,16,104,98,138,96,36,138,96,119,106,148,227,31,254,144,216,4,167,63,244,148,
148,16,99,187,63,252,161,100,171,77,127,211,35,56,143,76,221,90,11,162,3,92,18,24,110,190,57,175,16,130,27,162,227,236,157,183,231,26,136,12,183,219,94,11,252,33,136,106,230,184,141,127,5,198,110,173,
119,107,174,184,16,103,139,223,242,81,140,113,72,0,252,150,137,226,9,162,152,89,254,214,1,165,16,66,181,248,67,55,136,14,223,138,105,100,44,202,153,26,239,184,105,7,17,4,7,5,70,186,108,203,68,229,5,144,
77,172,127,219,4,117,18,152,1,50,160,130,64,224,7,34,193,12,16,0,54,192,24,152,108,63,5,16,122,36,242,244,7,81,32,28,233,84,1,134,63,95,48,31,49,79,48,239,49,207,48,227,152,177,191,220,198,127,248,0,5,
4,32,239,63,116,255,255,68,119,2,41,224,11,34,53,16,196,254,153,13,205,133,214,67,107,163,109,144,167,1,210,149,208,26,104,205,63,223,6,102,91,103,255,106,245,91,215,96,100,172,236,54,197,104,91,251,4,
68,226,218,31,62,31,74,22,245,223,198,248,253,29,241,223,117,50,3,31,182,164,110,115,40,92,80,152,81,88,253,51,254,95,43,198,154,98,77,176,22,88,51,172,36,234,0,234,42,234,46,170,27,117,31,213,137,106,
5,2,168,155,168,54,84,63,234,198,38,254,183,89,200,219,86,161,110,173,215,26,153,49,16,196,111,253,21,249,63,106,20,255,151,99,155,74,47,69,175,10,28,183,248,195,144,111,148,191,51,184,110,105,77,249,
111,82,226,145,238,135,72,10,69,190,89,255,93,227,31,75,139,33,214,85,69,27,161,117,17,59,35,54,70,179,161,185,128,44,90,5,177,184,33,90,31,241,129,42,66,53,254,247,81,219,79,89,16,180,101,203,132,173,
181,132,129,143,8,142,136,11,76,138,219,12,116,227,168,232,100,42,37,56,36,78,192,16,57,45,3,101,4,44,35,253,229,100,4,148,20,20,149,193,230,217,251,123,107,127,115,220,58,83,33,182,199,255,162,133,238,
6,64,157,31,33,222,254,23,45,112,4,128,142,215,200,113,67,251,47,154,216,62,100,107,161,1,184,239,235,31,79,77,248,77,67,111,62,48,128,22,48,32,209,207,137,156,28,194,64,2,209,83,9,168,1,109,96,0,76,129,
21,216,1,156,129,7,216,133,88,55,4,68,32,26,39,130,61,32,19,228,128,124,112,4,28,7,101,224,52,168,2,181,160,17,92,1,173,160,19,116,131,59,224,33,24,4,207,192,75,48,14,38,193,103,48,7,126,128,21,8,130,
112,16,17,98,134,56,33,126,72,20,146,134,148,32,13,72,15,50,133,108,32,71,200,3,242,133,130,161,72,40,30,218,3,237,133,242,161,66,168,12,58,11,213,65,151,161,118,168,27,186,15,61,129,198,160,119,208,12,
180,0,253,130,81,48,29,204,2,243,194,98,176,60,172,1,27,194,214,176,51,236,13,7,195,49,112,10,156,13,23,192,37,112,37,220,0,183,192,221,240,67,248,25,60,14,127,134,23,81,0,69,64,177,161,4,81,178,40,13,
148,49,106,7,202,19,21,132,162,162,210,80,121,168,98,84,37,234,34,170,3,137,197,97,212,56,106,22,181,140,198,162,153,209,2,104,89,196,147,22,104,23,180,63,58,6,157,134,62,136,46,67,215,162,91,208,189,
232,97,244,59,244,28,122,29,67,196,240,96,164,49,90,24,75,140,59,38,24,147,136,201,193,20,99,106,48,205,152,62,100,63,79,98,126,96,177,88,54,172,56,86,29,137,118,15,108,40,118,55,246,32,182,2,219,132,
189,133,125,130,157,192,46,226,112,56,78,156,52,78,23,183,3,71,198,197,225,114,112,165,184,6,220,77,220,16,110,18,247,19,79,192,243,227,149,240,102,120,79,124,36,62,11,95,140,175,199,119,225,135,240,83,
248,21,26,70,26,81,26,45,154,29,52,1,52,201,52,135,105,170,105,58,104,30,211,76,210,172,208,50,209,138,211,234,210,58,211,134,210,102,210,150,208,94,164,237,163,125,69,251,141,64,32,8,17,52,9,14,4,10,
33,131,80,66,184,68,184,71,120,71,88,166,35,209,73,209,25,211,121,209,197,211,21,208,157,167,187,69,55,70,247,141,72,36,138,17,13,136,158,196,56,98,1,177,142,120,155,248,134,248,147,158,153,94,142,222,
146,62,128,62,157,190,156,190,133,126,136,254,43,3,13,131,40,131,33,195,46,134,20,134,98,134,171,12,143,25,102,25,105,24,197,24,141,25,201,140,105,140,229,140,237,140,207,25,23,153,152,153,20,153,118,
48,69,48,29,100,170,103,186,207,52,77,194,145,196,72,166,164,0,82,54,169,138,116,155,52,193,140,98,22,102,54,102,246,103,222,203,92,205,220,199,60,201,130,101,17,103,177,100,9,101,201,103,105,100,25,96,
153,99,37,177,170,176,186,178,38,177,150,179,222,96,29,103,67,177,137,177,89,178,133,179,29,102,187,194,54,194,246,139,157,151,221,144,61,144,61,151,253,34,251,16,251,18,7,55,135,1,71,32,71,30,71,19,199,
51,142,95,156,2,156,166,156,97,156,71,57,91,57,95,115,161,185,164,184,28,184,18,185,78,113,245,113,205,114,179,112,107,115,251,115,231,113,95,225,126,193,3,243,72,241,56,242,236,230,169,226,233,231,89,
228,229,227,53,231,141,230,45,229,189,205,59,203,199,198,103,192,23,202,119,140,175,139,111,134,159,153,95,143,159,194,127,140,255,38,255,39,1,86,1,67,129,112,129,18,129,94,129,57,65,30,65,11,193,120,
193,179,130,3,130,43,66,226,66,46,66,89,66,77,66,175,133,105,133,53,132,131,132,143,9,247,8,207,137,240,139,216,138,236,17,185,32,242,66,148,70,84,67,52,68,244,132,232,93,209,37,49,113,49,55,177,253,98,
173,98,211,226,28,226,150,226,41,226,23,196,95,73,16,37,244,37,98,36,42,37,158,74,98,37,53,36,195,36,43,36,7,165,96,41,85,169,16,169,114,169,199,210,176,180,154,52,69,186,66,250,137,12,70,70,83,38,82,
166,82,230,185,44,157,172,161,108,130,236,5,217,119,114,108,114,54,114,89,114,173,114,95,229,69,228,61,229,143,202,223,149,95,87,80,85,8,87,168,86,120,169,72,82,180,82,204,82,236,80,92,80,146,82,242,87,
42,87,122,170,76,84,54,83,78,87,110,83,158,87,145,86,9,84,57,165,50,170,202,172,106,171,186,95,181,71,117,77,77,93,141,170,118,81,109,70,93,68,221,87,253,164,250,115,13,22,13,123,141,131,26,247,52,49,
154,70,154,233,154,157,154,203,90,106,90,113,90,87,180,254,209,150,213,14,211,174,215,158,214,17,215,9,212,169,214,153,208,21,210,37,235,158,213,29,215,19,208,243,213,59,163,55,174,47,168,79,214,175,212,
127,111,32,108,16,96,80,99,48,101,40,105,24,106,216,96,248,213,72,193,136,106,212,108,180,100,172,101,156,106,124,203,4,101,98,110,146,103,50,96,74,50,117,49,45,51,125,99,38,100,22,108,118,193,108,206,
92,213,124,183,249,45,11,140,133,181,197,81,139,231,150,188,150,254,150,117,150,115,86,234,86,169,86,189,214,116,214,78,214,101,214,239,109,164,108,168,54,29,182,176,173,149,109,145,237,43,59,81,187,72,
187,214,29,96,135,229,142,162,29,175,237,197,237,99,236,175,59,96,29,236,29,202,29,62,58,42,58,238,113,188,235,196,236,228,227,84,239,244,195,217,200,249,176,243,75,23,9,151,120,151,30,87,6,87,47,215,
58,215,37,55,19,183,66,183,113,119,121,247,84,247,135,30,92,30,20,143,54,79,156,167,171,103,141,231,226,78,211,157,199,119,78,122,169,122,229,120,141,120,139,123,39,121,223,223,197,181,43,124,215,13,31,
6,31,178,207,85,95,140,175,155,111,189,239,42,121,7,185,146,188,232,103,233,119,210,111,206,223,216,255,132,255,231,0,131,128,99,1,51,129,186,129,133,129,83,65,186,65,133,65,211,193,186,193,69,193,51,
33,250,33,197,33,179,20,99,74,25,101,62,212,34,244,116,232,82,216,142,176,243,97,27,225,110,225,77,17,248,8,223,136,246,72,82,100,88,100,111,20,95,84,82,212,147,104,233,232,156,232,241,24,173,152,227,
49,115,84,107,106,77,44,20,235,29,219,22,199,130,36,185,253,241,18,241,251,226,223,37,232,37,148,39,252,76,116,77,188,154,196,148,20,153,212,159,44,149,156,155,60,149,98,150,114,110,55,122,183,255,238,
158,61,130,123,50,247,188,75,53,76,61,155,6,165,249,165,245,164,11,167,103,167,79,102,152,103,212,102,210,102,134,101,62,202,82,200,42,204,250,190,215,109,111,71,54,111,118,70,246,196,62,243,125,23,114,
232,115,168,57,207,247,107,239,63,125,0,125,128,114,96,32,87,57,183,52,119,61,47,32,239,65,190,66,126,113,254,234,65,255,131,15,14,41,30,42,57,180,81,16,84,48,112,88,237,240,169,35,216,35,145,71,70,142,
234,31,173,45,100,42,76,41,156,40,178,45,106,57,38,112,44,239,216,247,227,62,199,239,23,171,20,159,62,65,123,34,254,196,120,137,77,73,91,169,72,233,145,210,213,178,144,178,103,229,70,229,77,39,121,78,
230,158,92,170,8,168,24,58,101,112,234,226,105,222,211,249,167,127,157,161,156,25,61,107,126,182,165,82,172,178,184,10,91,149,80,245,177,218,181,250,238,57,141,115,117,53,92,53,249,53,107,231,35,207,143,
215,58,214,246,214,169,215,213,213,243,212,31,190,0,95,136,191,48,211,224,213,48,216,104,210,216,118,81,246,226,217,38,182,166,252,75,224,82,252,165,79,151,125,47,143,92,177,190,210,115,85,227,234,197,
107,162,215,78,54,51,55,231,181,64,45,201,45,115,173,33,173,227,109,30,109,79,218,173,218,123,58,180,59,154,175,203,93,63,223,41,216,89,126,131,245,198,225,46,218,174,236,174,141,155,41,55,23,111,69,223,
154,237,14,238,158,232,241,233,121,121,219,253,246,211,94,135,222,129,62,235,190,123,119,204,238,220,190,107,120,247,230,61,221,123,157,247,181,238,183,63,208,120,208,250,80,237,97,75,191,106,127,243,
35,213,71,205,3,106,3,45,143,213,31,183,13,106,14,118,60,209,121,210,53,164,63,212,61,108,50,124,231,169,229,211,135,207,236,158,61,25,113,25,25,125,238,245,124,124,52,96,116,122,44,124,108,254,69,194,
139,149,151,25,175,48,175,242,94,51,190,46,126,195,243,166,242,173,228,219,166,113,181,241,27,239,76,222,245,191,119,122,255,114,194,127,226,243,135,216,15,171,147,217,31,137,31,139,167,248,167,234,166,
149,166,59,103,204,102,6,63,237,252,52,249,57,250,243,202,108,206,23,166,47,39,191,74,124,189,246,143,193,63,253,115,238,115,147,243,212,249,141,133,131,223,56,191,157,255,174,242,189,103,209,126,241,
205,143,136,31,43,75,121,63,57,127,214,46,107,44,223,253,229,246,107,106,37,113,21,183,90,178,38,185,214,177,110,189,254,106,35,98,99,35,154,76,37,111,165,2,40,164,195,65,65,0,44,156,71,234,22,15,0,152,
7,1,160,165,255,93,27,109,55,20,146,124,192,91,188,68,36,183,209,65,242,164,34,48,0,145,32,119,168,22,134,225,8,120,2,21,136,90,64,231,99,20,48,227,216,10,92,40,222,132,70,140,150,158,0,211,161,136,76,
244,210,12,150,140,84,166,179,164,215,44,124,172,126,108,87,56,208,156,190,92,183,120,248,121,115,249,230,5,188,5,31,10,107,137,156,19,99,17,207,144,152,146,178,147,110,146,165,151,243,151,191,170,176,
162,164,173,28,171,114,90,181,87,237,157,250,178,38,157,22,151,182,148,142,134,174,137,158,157,190,167,65,136,97,130,81,142,113,177,73,173,105,135,217,3,243,23,22,211,150,75,214,104,27,70,91,30,59,241,
29,138,246,90,14,70,142,150,78,118,206,142,46,46,174,110,110,238,238,30,30,158,158,158,59,61,189,60,189,61,119,185,251,184,250,58,146,109,253,204,252,245,2,84,3,165,130,248,131,153,67,112,33,43,148,175,
161,239,194,158,134,223,69,118,229,133,168,138,232,67,49,201,84,114,172,97,28,103,220,215,248,238,132,19,137,81,73,86,201,194,201,107,41,207,119,55,237,57,144,234,155,166,158,78,143,236,173,235,153,133,
89,33,123,117,179,153,179,167,247,117,229,20,237,15,57,160,147,203,150,187,150,143,62,168,119,168,241,176,198,145,43,71,215,138,248,143,73,31,151,43,86,56,161,88,162,92,170,82,166,90,174,122,82,173,66,
235,148,217,233,192,51,37,103,71,171,88,171,13,207,121,215,68,158,79,169,205,169,59,90,95,126,225,92,67,83,99,251,197,219,77,67,151,190,92,17,188,26,125,109,176,69,178,53,188,173,164,189,165,227,241,245,
169,206,245,46,182,155,138,183,92,187,11,123,166,123,45,250,202,239,60,186,251,238,222,220,3,236,67,209,126,243,71,1,3,177,143,195,7,93,158,168,15,241,13,211,14,47,63,157,120,246,104,228,230,243,142,209,
206,177,155,47,186,95,118,189,106,122,125,244,77,248,91,163,113,206,241,133,119,131,239,219,39,106,63,148,79,30,249,184,111,42,121,58,98,198,247,147,237,103,229,89,210,236,231,47,119,190,86,255,147,51,
23,58,111,183,160,242,77,232,187,228,162,247,143,174,159,10,203,199,126,189,93,229,92,115,95,175,222,216,216,140,19,64,0,220,72,150,232,136,212,34,13,224,35,36,14,69,65,183,96,110,56,11,94,64,69,163,126,
162,15,96,4,49,125,216,56,156,28,238,27,190,135,166,130,54,149,16,64,231,78,116,162,119,103,240,99,140,103,202,39,213,50,15,178,252,100,19,103,247,230,40,226,124,204,77,228,177,225,61,200,55,32,64,20,
116,16,58,42,60,40,74,16,51,21,79,144,168,145,124,34,245,93,134,81,86,66,78,69,94,83,65,83,81,89,73,82,153,79,133,81,21,82,253,174,54,137,220,86,247,52,219,181,234,180,203,116,242,117,119,235,133,234,
239,52,176,51,52,50,82,55,150,51,17,49,229,50,99,52,199,154,175,88,204,89,78,90,141,90,247,219,116,217,94,178,171,220,81,100,159,237,16,235,72,118,178,119,214,115,145,118,229,112,195,184,205,187,191,242,
184,231,121,117,231,105,175,92,239,216,93,222,62,166,190,50,100,102,242,79,191,215,254,221,1,213,129,7,130,194,130,109,67,228,41,76,148,111,161,207,194,90,194,75,34,146,35,221,163,212,162,73,209,51,49,
55,169,69,177,1,113,170,241,152,248,145,132,115,137,241,73,166,201,44,201,19,41,87,118,103,236,177,75,229,73,253,148,214,145,126,40,35,52,211,49,203,4,137,12,173,125,106,57,10,251,165,15,136,230,242,231,
113,230,147,14,18,14,161,15,173,21,252,56,60,127,100,225,232,114,17,238,24,199,113,137,98,245,19,38,37,246,165,59,203,130,203,169,39,83,43,246,159,42,60,125,242,204,249,179,109,149,67,85,203,231,36,107,
188,206,231,215,54,215,189,168,95,111,16,108,52,189,24,210,116,232,82,235,229,175,87,85,175,237,107,126,210,74,108,211,109,167,116,148,94,127,216,185,209,165,122,51,252,86,117,247,171,219,76,189,6,125,
148,59,249,119,235,239,221,187,63,243,144,216,175,252,200,115,32,235,113,195,224,243,33,236,176,202,83,159,103,217,35,213,207,123,71,63,190,160,125,41,255,202,249,117,242,155,83,111,239,142,47,189,87,
156,160,126,184,58,185,48,37,51,29,60,83,245,233,237,44,247,23,247,175,39,255,153,155,79,248,38,187,72,90,162,93,134,127,125,94,189,190,78,217,246,63,45,96,7,50,192,2,169,98,78,128,7,16,22,50,135,142,
66,19,176,46,124,22,69,68,237,67,227,208,133,24,49,204,45,108,0,142,132,187,143,63,64,99,71,203,79,187,76,120,74,215,70,60,71,95,202,80,200,120,152,169,144,84,198,124,142,165,133,245,30,219,27,246,101,
78,18,151,44,183,25,15,153,119,15,223,9,254,139,2,61,130,79,133,38,133,191,136,44,136,206,33,89,211,168,68,143,228,57,169,189,210,158,50,242,178,144,236,144,92,181,124,162,130,149,162,128,226,146,210,
128,114,141,74,154,170,139,154,140,58,172,62,170,209,168,153,165,229,170,45,165,189,166,51,168,91,165,151,168,111,101,192,111,176,104,216,111,116,206,56,205,196,213,84,206,12,99,246,202,252,154,69,158,
165,175,149,154,53,193,122,220,166,217,54,215,206,27,57,41,48,246,99,14,13,142,25,78,78,206,162,206,63,92,238,185,150,185,133,185,107,123,16,60,94,122,94,216,153,226,101,225,205,230,253,97,215,101,159,
116,95,107,50,59,121,194,239,162,127,74,128,89,32,83,224,203,160,154,224,152,16,109,10,154,50,16,122,34,204,55,92,50,124,62,162,45,50,35,202,44,154,38,186,63,230,32,213,42,22,31,219,23,151,21,175,23,191,
146,208,154,24,155,36,151,52,147,92,157,226,179,155,107,247,211,61,5,169,22,105,112,90,87,122,90,134,69,38,111,230,74,214,248,222,123,217,151,247,149,231,100,239,143,56,224,154,171,151,39,150,79,204,95,
60,248,234,208,237,130,250,195,199,142,100,30,77,44,164,22,69,31,67,210,130,226,152,19,49,37,209,165,145,101,148,114,223,147,78,21,86,167,108,78,123,159,73,62,91,81,217,87,245,245,28,107,141,250,121,155,
90,199,58,135,250,157,23,118,55,92,107,92,105,50,191,84,116,249,237,85,233,107,9,205,221,173,132,54,167,246,146,142,151,157,130,55,194,187,110,220,98,238,14,237,185,221,203,221,23,119,103,224,158,216,
253,212,7,79,251,165,30,101,13,76,12,186,62,25,25,246,127,186,56,114,96,148,107,172,241,165,193,171,145,55,25,227,182,239,157,62,28,249,184,52,115,108,182,111,222,121,105,108,211,255,191,255,71,182,217,
176,106,0,156,51,3,192,245,24,0,78,154,8,46,0,64,180,22,185,63,116,0,176,39,2,224,172,9,96,206,82,0,221,136,6,144,151,196,223,251,131,15,24,34,119,199,94,80,13,250,144,211,3,139,156,31,150,80,24,116,8,
106,66,106,189,239,48,59,172,13,251,192,123,225,90,120,0,254,134,226,66,25,162,66,80,71,80,109,168,247,104,2,90,13,77,70,31,66,183,163,167,48,172,24,83,76,60,82,117,141,98,233,176,134,216,68,236,69,236,
52,78,8,231,131,59,133,123,131,23,194,135,224,47,225,215,104,108,104,206,208,252,160,181,167,109,36,16,9,145,132,33,58,13,186,179,68,2,49,129,56,65,239,64,223,205,160,196,80,205,200,201,120,132,137,134,
105,31,9,38,101,49,99,152,115,89,24,89,74,89,69,89,175,178,153,176,141,178,71,113,224,57,170,57,141,57,63,112,237,231,150,229,126,198,147,206,43,195,251,138,175,128,223,132,127,77,160,67,48,69,72,79,24,
35,252,88,228,164,104,152,152,174,56,73,252,147,68,175,100,165,84,150,116,160,140,141,172,166,156,156,188,188,130,158,162,139,82,184,242,94,228,200,111,86,27,86,255,161,201,171,101,174,157,160,83,167,
251,86,159,211,192,205,176,212,232,173,137,132,105,188,217,29,11,46,203,96,171,227,214,39,108,18,108,13,108,55,236,186,119,28,180,15,117,160,56,102,59,93,114,254,224,202,229,230,228,94,224,209,191,147,
232,229,224,93,188,107,212,151,129,172,236,103,238,239,18,16,16,152,30,116,33,120,154,162,24,154,25,54,28,33,129,68,222,139,24,117,106,113,236,207,120,183,132,134,196,47,201,236,41,10,187,141,246,120,
164,166,167,181,103,208,100,134,100,61,202,86,219,87,185,159,225,64,90,238,84,190,225,193,236,67,205,5,227,71,232,143,218,21,94,58,166,114,188,239,132,93,201,163,50,139,242,59,21,14,167,126,158,185,87,
217,85,125,165,230,68,109,74,61,165,97,231,69,195,75,172,151,223,93,109,108,78,111,221,213,238,121,125,207,141,214,155,203,61,154,189,17,119,242,238,149,62,168,238,111,26,232,26,124,50,52,245,12,255,92,
119,236,208,203,239,111,60,199,155,39,8,147,228,169,142,79,248,89,241,175,224,159,138,121,190,133,146,239,60,139,45,75,17,203,170,191,86,87,91,214,125,182,206,15,17,96,13,98,64,49,232,4,239,33,60,36,7,
57,67,41,80,37,82,233,207,195,156,176,17,28,6,31,135,111,193,159,145,154,221,24,185,77,42,80,253,168,21,180,52,218,11,93,128,238,70,47,98,164,48,100,76,9,230,9,150,128,53,199,238,195,246,226,176,56,43,
220,97,220,40,94,4,31,139,239,163,225,161,73,164,25,161,213,164,61,67,160,37,36,18,166,232,220,233,30,17,141,137,157,244,26,244,45,12,106,12,237,140,250,140,119,144,26,117,140,20,72,90,96,206,98,97,97,
169,101,213,103,29,99,139,103,103,97,111,225,240,228,132,57,27,184,60,184,105,184,59,121,98,17,95,79,243,157,231,167,8,200,9,252,16,236,22,58,44,236,35,162,44,74,43,250,65,172,71,188,90,34,87,50,86,202,
87,218,65,198,84,86,71,78,93,94,85,65,77,81,75,201,72,217,86,101,167,106,164,90,142,122,141,198,99,205,117,109,21,157,40,221,139,122,11,6,154,134,217,70,195,38,226,166,233,102,47,45,180,45,43,172,214,
108,236,109,139,236,30,236,88,117,144,115,12,112,58,229,252,2,241,177,151,251,89,143,79,59,85,189,246,122,15,251,136,250,198,146,59,253,214,3,116,3,83,131,186,67,104,40,174,161,231,194,150,34,108,34,171,
162,86,99,60,168,109,113,156,241,123,18,94,36,41,36,239,78,185,177,251,87,170,86,90,102,250,64,166,80,86,242,222,225,125,10,57,5,251,191,230,218,229,213,231,175,28,50,40,216,115,184,249,200,98,161,73,
81,229,113,154,98,234,137,209,82,189,178,170,147,248,138,168,83,35,103,116,207,214,84,177,84,231,214,96,207,23,212,241,213,95,107,176,109,156,104,74,186,76,184,114,250,154,74,243,131,86,223,182,197,142,
3,157,60,55,154,111,186,117,195,61,205,189,148,59,60,119,7,238,103,60,84,233,255,52,80,53,184,115,136,105,248,230,51,255,231,96,180,252,133,230,203,215,175,247,191,85,26,127,251,254,224,7,237,201,217,
169,83,51,118,159,22,103,15,124,89,254,199,114,110,223,252,229,133,129,111,211,223,55,126,112,44,41,255,116,94,222,243,171,126,229,211,154,198,250,241,45,255,75,2,103,144,14,234,192,48,88,135,36,17,239,
103,64,13,208,40,140,133,85,96,63,248,40,220,141,100,17,194,40,87,84,46,234,6,234,27,90,18,237,139,46,69,15,99,24,48,54,152,124,204,67,44,17,235,136,45,197,190,199,201,226,82,113,143,241,98,248,76,252,
59,26,115,154,43,180,34,180,229,4,54,194,113,58,54,186,50,34,63,177,134,94,129,190,147,193,134,225,45,146,111,48,48,53,144,108,73,243,204,165,44,38,44,11,172,85,108,174,236,4,246,110,142,20,78,53,206,
31,92,237,220,233,60,150,188,236,136,175,111,240,31,23,160,34,25,136,138,48,151,8,26,185,123,38,196,198,196,135,36,30,35,149,249,51,233,55,50,159,101,87,229,73,10,50,138,86,200,142,46,82,233,82,253,162,
46,160,225,166,89,168,53,164,195,170,235,173,87,175,191,98,104,111,84,111,66,99,26,97,246,220,194,202,242,142,181,141,205,168,29,197,30,56,148,59,233,56,191,119,45,112,215,247,88,220,121,217,155,234,163,
230,187,224,87,30,32,29,216,24,44,21,82,19,42,22,86,23,33,31,217,30,109,30,51,26,27,17,143,77,168,76,50,76,126,187,59,41,21,155,86,144,193,146,89,186,87,40,187,49,71,123,255,163,92,255,124,232,224,133,
2,175,35,216,163,229,69,124,199,142,23,227,78,36,150,76,149,121,150,15,87,184,159,250,126,166,174,50,176,26,119,46,175,230,71,173,123,93,243,5,150,134,184,198,145,38,205,75,167,174,96,174,70,94,27,107,
49,111,109,111,87,232,168,239,20,185,81,126,147,254,86,106,247,167,219,110,189,189,119,148,238,158,189,79,122,144,253,112,233,81,248,192,135,65,239,39,99,195,110,79,159,143,56,63,191,63,166,244,162,240,
229,231,215,122,111,10,222,190,126,39,251,62,109,98,112,82,248,99,210,212,163,25,225,79,9,159,111,205,174,127,85,252,199,106,206,99,222,99,193,238,155,206,119,225,69,220,226,251,31,29,75,25,63,117,127,
206,45,103,254,34,253,58,179,66,179,18,179,50,182,106,180,90,186,58,189,166,190,182,111,237,233,186,240,58,101,189,113,125,110,67,101,35,105,227,250,166,255,99,131,148,149,182,174,15,136,206,8,0,204,155,
141,141,111,98,0,224,10,1,88,59,186,177,177,82,185,177,177,86,133,20,25,175,0,184,21,254,251,119,151,173,187,134,17,128,147,167,55,81,223,49,145,35,255,254,251,199,127,0,165,229,183,49,180,206,53,54,0,
0,0,6,98,75,71,68,0,26,0,26,0,26,63,192,235,128,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,221,4,18,9,22,35,220,202,99,175,0,0,2,200,73,68,65,84,104,222,237,152,79,
72,20,97,24,198,127,223,172,3,9,82,200,22,200,206,161,67,144,7,147,174,6,93,162,75,39,37,243,22,97,39,15,65,22,121,144,29,19,19,219,153,221,144,66,169,131,5,226,161,163,40,117,172,123,117,233,16,225,197,
251,71,91,65,101,40,41,179,243,125,29,154,133,105,255,239,84,96,248,205,101,254,241,253,120,231,157,225,121,158,121,69,38,147,225,79,55,139,191,176,117,212,186,88,40,200,254,48,100,13,32,149,98,120,114,
210,121,223,54,68,41,114,64,30,32,12,185,11,12,181,13,209,154,129,32,224,42,128,109,227,39,237,73,119,79,15,91,125,125,124,7,186,19,245,68,107,190,21,139,28,41,22,193,182,249,154,8,98,89,188,182,109,46,
2,8,193,155,164,149,220,134,95,111,71,107,134,155,65,196,190,249,216,12,196,64,12,196,64,12,196,64,12,196,64,254,117,142,245,60,169,1,92,215,17,173,100,219,154,149,196,23,215,200,182,249,40,219,54,174,
164,221,108,219,78,79,234,102,219,142,122,61,104,39,219,118,52,91,220,74,182,181,26,189,157,242,62,150,109,179,64,54,58,54,57,214,64,12,196,64,12,196,64,12,196,64,14,88,142,245,60,57,166,53,57,33,248,
1,220,114,93,103,181,89,142,173,130,8,193,169,84,138,147,165,18,103,129,101,96,181,34,199,86,205,104,171,32,217,172,51,14,48,59,43,223,218,54,31,18,231,88,41,165,176,109,22,180,102,34,113,142,93,89,225,
33,240,98,106,202,121,153,40,199,230,114,50,39,4,239,92,215,121,210,106,142,173,213,88,55,170,110,41,106,98,231,244,180,179,219,104,70,107,114,172,129,24,136,129,28,0,243,242,125,121,77,107,230,128,109,
96,34,145,121,105,77,111,24,114,194,178,56,29,25,87,251,230,229,186,206,13,128,124,94,134,74,241,169,21,243,170,59,83,82,138,93,173,25,172,52,175,116,26,177,185,249,187,121,89,229,69,241,49,199,232,40,
150,214,92,16,130,199,149,230,181,177,193,97,104,98,94,190,47,39,151,151,89,176,109,14,41,69,103,34,243,138,22,124,86,138,143,192,88,197,16,198,152,151,129,24,200,190,215,216,152,48,221,4,30,148,101,162,
45,141,5,152,159,151,71,247,246,184,44,98,163,222,70,26,91,243,113,130,128,57,224,81,133,128,15,4,1,235,65,192,58,112,166,97,79,10,5,217,15,156,235,237,229,105,197,173,186,63,8,85,26,27,134,220,87,138,
252,200,136,83,170,168,164,174,198,86,41,91,92,176,99,54,34,124,95,62,215,154,103,145,198,14,101,179,206,96,35,223,17,113,96,249,220,104,172,129,24,136,129,252,191,190,179,184,40,187,118,118,88,82,138,
65,33,232,74,228,59,219,219,220,1,142,149,74,28,159,153,113,190,180,226,59,181,204,235,146,101,113,37,14,72,50,152,202,40,197,117,223,151,91,158,39,199,18,249,14,176,5,220,19,130,243,128,151,40,219,107,
205,171,84,138,242,121,152,52,219,187,90,179,166,20,105,203,98,220,100,123,3,217,87,144,159,76,54,160,53,240,12,22,63,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* Ambix_kmeterAudioProcessorEditor::meter_scale_png = (const char*) resource_Ambix_kmeterAudioProcessorEditor_meter_scale_png;
const int Ambix_kmeterAudioProcessorEditor::meter_scale_pngSize = 6973;


//[EndFile] You can add extra defines here...
//[/EndFile]