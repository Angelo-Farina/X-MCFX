/*
 ==============================================================================
 
 This file is part of the mcfx (Multichannel Effects) plug-in suite.
 Copyright (c) 2013/2014 - Matthias Kronlachner
 www.matthiaskronlachner.com
 
 Permission is granted to use this software under the terms of:
 the GPL v2 (or any later version)
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 mcfx is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "PluginView.h"

//==============================================================================

Mcfx_convolverAudioProcessorEditor::Mcfx_convolverAudioProcessorEditor(Mcfx_convolverAudioProcessor& processorToUse)
    : AudioProcessorEditor (&processorToUse), processor(processorToUse)
{
//    LookAndFeel::setDefaultLookAndFeel(&MyLookAndFeel);

    tooltipWindow.setMillisecondsBeforeTipAppears (700); // tooltip delay
    
    view.changePathBox.pathButton.addListener(this);
    view.filterManagingBox.filterSelector.addListener(this);
    view.filterManagingBox.reloadButton.addListener(this);
    
    view.convManagingBox.bufferCombobox.addListener(this);
    view.convManagingBox.maxPartCombobox.addListener(this);
    
    view.inputChannelDialog.OKButton.addListener(this);
//    view.inputChannelDialog.saveIntoMetaToggle.addListener(this);
    
    view.ioDetailBox.gainKnob.addListener(this);
    
    setNewGeneralPath.addItem(-1, "Set new generic path");
    
    addAndMakeVisible(view);

    setSize (460, 420); //originally 350, 330
    
    UpdateText();
    
    UpdateFiltersMenu();
    
    processor.addChangeListener(this);

    timerCallback();

    startTimer(1000);
}

Mcfx_convolverAudioProcessorEditor::~Mcfx_convolverAudioProcessorEditor()
{
    processor.removeChangeListener(this);
}

//==============================================================================
void Mcfx_convolverAudioProcessorEditor::paint (Graphics& g)
{

}

void Mcfx_convolverAudioProcessorEditor::resized()
{
    auto test = getLocalBounds();
    view.setBounds(test);
}

void Mcfx_convolverAudioProcessorEditor::timerCallback()
{
    view.convManagingBox.skippedCyclesValue.setText(String(processor.getSkippedCyclesCount()), sendNotification);
    
    view.debugText.setText(processor.getDebugString(), true);   //notify for what purpose?
    view.debugText.moveCaretToEnd();
}

void Mcfx_convolverAudioProcessorEditor::changeListenerCallback (ChangeBroadcaster *source)
{
    UpdateFiltersMenu();
    UpdateText();
    repaint();
}

/// update the overall plugin text based on the processor data and the stored one
void Mcfx_convolverAudioProcessorEditor::UpdateText()
{
    
    view.filterManagingBox.filterSelector.setText(processor.filterNameToShow,dontSendNotification);
    view.filterManagingBox.filterSelector.setTooltip(view.filterManagingBox.filterSelector.getText()); //to see all the string
    
    view.changePathBox.pathText.setText(processor.defaultFilterDir.getFullPathName(), dontSendNotification);
    
    String inChannels;
    inChannels << String(processor.activeNumInputs) << " in";
    view.ioDetailBox.inputValue.setText(inChannels, dontSendNotification);
    
    String outChannels;
    outChannels << String(processor.activeNumOutputs) << " out";
    view.ioDetailBox.outputValue.setText(outChannels, dontSendNotification);
    
    view.ioDetailBox.IRValue.setText(String(processor.activeNumIRs), dontSendNotification);
    view.ioDetailBox.diagonalValue.setVisible(processor.tempNumInputs == -1);
    
    view.ioDetailBox.sampleRateNumber.setText(String(processor.getSamplerate()), dontSendNotification);
    view.ioDetailBox.hostBufferNumber.setText(String(processor.getBufferSize()), dontSendNotification);
    
    view.ioDetailBox.filterLengthInSeconds.setText(String(processor.filterLenghtInSecs, 2), dontSendNotification);
    view.ioDetailBox.filterLengthInSamples.setText(String(processor.filterLenghtInSmpls), dontSendNotification);
    view.ioDetailBox.resampledLabel.setVisible(processor.wavefileHasBeenResampled.get());
    
    view.ioDetailBox.gainKnob.setValue(processor.masterGain.get());
    
    view.convManagingBox.latencyValue.setText(String(processor.getLatencySamples()), sendNotification);
    
//    view.inputChannelDialog.saveIntoMetaToggle.setToggleState(processor.storeNumInputsIntoWav.get(), dontSendNotification);
    
    if(processor.restoredSettings.get())
        view.filterManagingBox.restoredSettingsLabel.setVisible(true);
    else
        view.filterManagingBox.restoredSettingsLabel.setVisible(false);
    
    switch (processor.getConvolverStatus())
    {
        case Mcfx_convolverAudioProcessor::ConvolverStatus::Unloaded :
            view.statusLed.setStatus(View::StatusLed::State::red);
            view.UnlockSensibleElements();
            break;
        case Mcfx_convolverAudioProcessor::ConvolverStatus::Loading:
            view.statusLed.setStatus(View::StatusLed::State::yellow);
            view.LockSensibleElements();
            break;
        case Mcfx_convolverAudioProcessor::ConvolverStatus::Loaded:
            view.statusLed.setStatus(View::StatusLed::State::green);
            view.UnlockSensibleElements();
            break;
        default:
            break;
    }
    
    if (processor.getTargetFilter().existsAsFile()
    &&  processor.getConvolverStatus() != Mcfx_convolverAudioProcessor::ConvolverStatus::Loading)
        view.filterManagingBox.reloadButton.setEnabled(true);
    else
        view.filterManagingBox.reloadButton.setEnabled(false);
    
    if (processor.newStatusText)
    {
        view.statusText.setText(processor.getStatusText());
        processor.newStatusText = false;
    }
    
    switch (processor.numInputsStatus)
    {
        case Mcfx_convolverAudioProcessor::NumInputsStatus::missing:
            view.inputChannelDialog.setVisible(true);
            view.inputChannelDialog.textEditor.grabKeyboardFocus();
            break;
        case Mcfx_convolverAudioProcessor::NumInputsStatus::notFeasible:
            view.inputChannelDialog.setVisible(true);
            view.inputChannelDialog.invalidState(View::InputChannelDialog::InvalidType::notFeasible) ;
            view.inputChannelDialog.textEditor.grabKeyboardFocus();
            break;
        case Mcfx_convolverAudioProcessor::NumInputsStatus::notMultiple:
            view.inputChannelDialog.setVisible(true);
            view.inputChannelDialog.invalidState(View::InputChannelDialog::InvalidType::notMultiple) ;
            view.inputChannelDialog.textEditor.grabKeyboardFocus();
            break;
        case Mcfx_convolverAudioProcessor::NumInputsStatus::requested:
            view.inputChannelDialog.setVisible(true);
            if(processor.tempNumInputs == -1)
                view.inputChannelDialog.diagonalToggle.setToggleState(true, sendNotification);
            else
                view.inputChannelDialog.textEditor.setText((String)processor.tempNumInputs);
                
            view.inputChannelDialog.textEditor.grabKeyboardFocus();
            break;
        
        default:
            break;
    }
    
//  ---------------------------------------------------------------------------------------
    view.convManagingBox.bufferCombobox.clear(dontSendNotification);
    
    unsigned int buf = jmax(processor.getBufferSize(), (unsigned int) 1);
    unsigned int conv_buf = jmax(processor.getConvBufferSize(), buf);
  
    int sel = 0;
    unsigned int val = 0;
    
    for (int i=0; val < 8192; i++) {
        
        val = (unsigned int)floor(buf*pow(2,i));
        
        view.convManagingBox.bufferCombobox.addItem(String(val), i+1);
        
        if (val == conv_buf)
            sel = i;
    }
     view.convManagingBox.bufferCombobox.setSelectedItemIndex(sel, dontSendNotification);
    
//  ---------------------------------------------------------------------------------------
    view.convManagingBox.maxPartCombobox.clear(dontSendNotification);
    sel = 0;
    val = 0;
    unsigned int max_part_size = processor.getMaxPartitionSize();
    for (int i=0; val < 65536; i++)
    {
      
      val = (unsigned int)floor(conv_buf*pow(2,i));
      
      view.convManagingBox.maxPartCombobox.addItem(String(val), i+1);
      
      if (val == max_part_size)
        sel = i;
    }
    view.convManagingBox.maxPartCombobox.setSelectedItemIndex(sel, dontSendNotification);
     
}

/// Update the filters  popup menu  based on a predefined folder
void Mcfx_convolverAudioProcessorEditor::UpdateFiltersMenu()
{
    view.filterManagingBox.filterSelector.clear(dontSendNotification);
    filterSubmenus.clear(); // contains submenus
    
    StringArray subDirectories; // hold name of subdirectories, they will be the just the first parent directory name
    String lastSubdirectory;
    int j = 1;
    int tickedFolder = -1;
    int tickedItem = -1;
    
    for (int i=0; i < processor.filterFilesList.size(); i++)
    {
        // add separator for new subfolder
        String currentFilterDir = processor.filterFilesList.getUnchecked(i).getParentDirectory().getFileNameWithoutExtension();
        
        //check if the current filter file has the same parent directory as the precedent one
        if (!lastSubdirectory.equalsIgnoreCase(currentFilterDir))
        {
            filterSubmenus.add(new PopupMenu());
            subDirectories.add(currentFilterDir);
            
            j++;
            lastSubdirectory = currentFilterDir;
        }
        
        // add item to submenu
        filterSubmenus.getLast()->addItem(i+1, processor.filterFilesList.getUnchecked(i).getFileNameWithoutExtension());
        
        // save indexes of current item and folder if it's the target one for loading
        if (processor.getTargetFilter() == processor.filterFilesList.getUnchecked(i))
        {
            tickedFolder = subDirectories.size()-1;
            tickedItem = i;
        }
        
    }
    
    // add all subdirs to main menu
    for (int i=0; i < filterSubmenus.size(); i++)
    {
        if (i == tickedFolder)
            view.filterManagingBox.filterSelector.getRootMenu()->addSubMenu(subDirectories.getReference(i), *filterSubmenus.getUnchecked(i), true, nullptr, true);
        else
            view.filterManagingBox.filterSelector.getRootMenu()->addSubMenu(subDirectories.getReference(i), *filterSubmenus.getUnchecked(i));
    }
    
    if (processor.getTargetFilter().existsAsFile())
    {
        view.filterManagingBox.filterSelector.addSeparator();
        view.filterManagingBox.filterSelector.getRootMenu()->addItem(-2, String("Export filter with metadata info..."), processor.readyToExportWavefile.get());
    }

    view.filterManagingBox.filterSelector.addSeparator();
    view.filterManagingBox.filterSelector.getRootMenu()->addItem(-1, String("Open filter from file..."));
    
    //tick the selected item (if present)
    if (tickedItem != -1)
        view.filterManagingBox.filterSelector.setSelectedItemIndex(tickedItem,dontSendNotification);
}

void Mcfx_convolverAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    /*
    if (buttonThatWasClicked == &(view.FilterManagingBox.chooseButton))
    {
        filterMenu.showMenuAsync(PopupMenu::Options().withTargetComponent (view.FilterManagingBox.chooseButton), ModalCallbackFunction::forComponent (menuItemChosenCallback, this));
    }
    else*/ if (buttonThatWasClicked == &(view.changePathBox.pathButton) )
    {
        if (view.changePathBox.pathButton.rightclick)
        {
            setNewGeneralPath.showMenuAsync(PopupMenu::Options().withTargetComponent(view.changePathBox.pathButton), ModalCallbackFunction::forComponent (righClickButtonCallback, this));
        }
        else
        {
            FileChooser myChooser ("Please select the new filter folder...",
                                   processor.defaultFilterDir,
                                   "");
            if (myChooser.browseForDirectory())
            {
                File mooseFile (myChooser.getResult());
                processor.defaultFilterDir = mooseFile;
                
                processor.SearchFilters(mooseFile);
                
                processor.lastSearchDir = mooseFile.getParentDirectory();
                processor.sendChangeMessage();
            }
        }
    }
    else if (buttonThatWasClicked == &(view.filterManagingBox.reloadButton))
    {
        processor.changeNumInputChannels = true;
        processor.ReloadConfiguration();
    }
    else if (buttonThatWasClicked == &(view.inputChannelDialog.OKButton))
    {
        if (view.inputChannelDialog.diagonalToggle.getToggleState())
        {
            processor.tempNumInputs = -1;
            ///reset input dialog with toggle uncheck
            view.inputChannelDialog.resetState(true);
        }
        else
        {
            processor.tempNumInputs = getInputChannelFromDialog();
            view.inputChannelDialog.resetState();
        }
        processor.notify();
    }
    /*
    else if (buttonThatWasClicked == &(view.inputChannelDialog.saveIntoMetaToggle))
    {
        if(view.inputChannelDialog.saveIntoMetaToggle.getToggleState())
            processor.storeNumInputsIntoWav.set(true);
        else
            processor.storeNumInputsIntoWav.set(false);
    }
     */
}

void Mcfx_convolverAudioProcessorEditor::righClickButtonCallback(int result, Mcfx_convolverAudioProcessorEditor* demoComponent)
{
    // file chooser....
    if (result == 0)
    {
        // do nothing
    }
    else if (result == -1)
    {
        FileChooser myChooser ("Please select the new generic filter folder...",
                               demoComponent->processor.defaultFilterDir,
                               "");
        if (myChooser.browseForDirectory())
        {
            File mooseFile (myChooser.getResult());
            
            demoComponent->processor.SearchFilters(mooseFile);
            demoComponent->processor.defaultFilterDir = mooseFile;
            demoComponent->processor.lastSearchDir = mooseFile.getParentDirectory();
            
            demoComponent->processor.setNewGlobalFilterFolder(mooseFile);
            demoComponent->processor.sendChangeMessage();
            
        }
    }
}

/*
void Mcfx_convolverAudioProcessorEditor::menuItemChosenCallback (int result, Mcfx_convolverAudioProcessorEditor* demoComponent)
{
    // file chooser....
    if (result == 0)
    {
        // do nothing
    }
    else if (result == -1)
    {
        String extension = "*.wav";
        
        FileChooser myChooser ("Please select the filter file to load...",
                               demoComponent->processor.lastSearchDir, //old version: ourProcessor->lastSearchDir,
                               extension);
        if (myChooser.browseForFileToOpen())
        {
            File mooseFile (myChooser.getResult());
            demoComponent->processor.LoadFilterFromFile(mooseFile);
            demoComponent->processor.lastSearchDir = mooseFile.getParentDirectory();
        }
        else
        {
            if(demoComponent->processor.filterNameToShow.isEmpty())
                demoComponent->view.filterManagingBox.filterSelector.setText("",dontSendNotification);
            else
            {
                String previousName = demoComponent->processor.filterNameToShow;
                demoComponent->view.filterManagingBox.filterSelector.setText(previousName, dontSendNotification);
            }
        }
    }
    else if (result == -2)
    {
        demoComponent->chooseExportFile();
              
        MessageManager::callAsync([&] () {
            if (demoComponent->exportFile.getFullPathName().isNotEmpty())
            {
                 ScopedLock lock(demoComponent->exportFileMutex);
                 demoComponent->processor.exportWavefileWithMetadata(File(demoComponent->exportFile));//demoComponent->exportFile);
                 demoComponent->processor.lastSearchDir = demoComponent->exportFile.getParentDirectory();
             
            }
        });
        
    }
    else // load filter from menu based on chosen index
    {
        File empty;
        demoComponent->processor.LoadFilterFromMenu(result - 1);
    }
}
*/

void Mcfx_convolverAudioProcessorEditor::menuItemChosenCallback (int result)
{
    // file chooser....
    if (result == 0)
    {
        // do nothing
    }
    else if (result == -1)
    {
        String extension = "*.wav";
        
        FileChooser myChooser ("Please select the filter file to load...",
                               processor.lastSearchDir, //old version: ourProcessor->lastSearchDir,
                               extension);
        if (myChooser.browseForFileToOpen())
        {
            File mooseFile (myChooser.getResult());
            processor.LoadFilterFromFile(mooseFile);
            processor.lastSearchDir = mooseFile.getParentDirectory();
        }
        else
        {
            if(processor.filterNameToShow.isEmpty())
                view.filterManagingBox.filterSelector.setText("",dontSendNotification);
            else
            {
                String previousName = processor.filterNameToShow;
                view.filterManagingBox.filterSelector.setText(previousName, dontSendNotification);
            }
        }
    }
    else if (result == -2)
    {
        FileChooser myChooser("Export filter as .wav file...",
                                  processor.lastSearchDir.getChildFile(processor.filterNameForStoring),
                                  "*.wav"
                                  );
        if (myChooser.browseForFileToSave(true))
        {
            File mooseFile =  myChooser.getResult();
            processor.exportWavefileAsync(mooseFile);
            processor.lastSearchDir = mooseFile.getParentDirectory();
        }
        else
            UpdateText();
    }
    else // load filter from menu based on chosen index
    {
        File empty;
        processor.LoadFilterFromMenu(result - 1);
    }
}

/*
void Mcfx_convolverAudioProcessorEditor::chooseExportFile()
{
    ScopedLock lock(exportFileMutex);
    exportFile = File();
    FileChooser myChooser("Export filter as .wav file...",
                              processor.lastSearchDir.getChildFile(processor.filterNameForStoring),
                              "*.wav"
                              );
    if (myChooser.browseForFileToSave(true))
    {
        exportFile = myChooser.getResult();
    }
}
*/

void Mcfx_convolverAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == &view.filterManagingBox.filterSelector)
    {
//        MessageManager::callAsync([&] () {
//            menuItemChosenCallback(view.filterManagingBox.filterSelector.getSelectedId(), this);
//            menuItemChosenCallback(view.filterManagingBox.filterSelector.getSelectedId());
//        });
//        menuItemChosenCallback(view.filterManagingBox.filterSelector.getSelectedId(), this);
        menuItemChosenCallback(view.filterManagingBox.filterSelector.getSelectedId());
    }
    else if (comboBoxThatHasChanged == &view.convManagingBox.bufferCombobox)
    {
        int val = view.convManagingBox.bufferCombobox.getText().getIntValue();
        
        // std::cout << "set size: " << val << std::endl;
        processor.setConvBufferSize(val);
    }
    else if (comboBoxThatHasChanged == &view.convManagingBox.maxPartCombobox)
    {
        int val = view.convManagingBox.maxPartCombobox.getText().getIntValue();
        processor.setMaxPartitionSize(val);
    }
}
  
int Mcfx_convolverAudioProcessorEditor::getInputChannelFromDialog()
{
    if (!view.inputChannelDialog.textEditor.isEmpty())
    {
        String temp =  view.inputChannelDialog.textEditor.getText();
        int value = temp.getIntValue();
        return value;
    }
    else
        return -2;
}

void Mcfx_convolverAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &view.ioDetailBox.gainKnob)
    {
        if(view.ioDetailBox.gainKnob.getValue() != -60)
            processor.masterGain.set(view.ioDetailBox.gainKnob.getValue());
        else
            processor.masterGain.set(0);
    }
}
