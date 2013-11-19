#include "plugin.h"
#include <math.h>
#include <stdio.h>

namespace Steinberg {
namespace Vst {


const float GAIN_DEFAULT_DB = 0;
const float GAIN_MIN_DB = -100;
const float GAIN_MAX_DB = 6;
//-----------------------------------------------------------------------------
// member function of PluginController!
// define parameter definitions here...
void PluginController::setupParameters(){
	parameters.addParameter(new RangeParameter(STR16("Gain"), kGainId, STR16("dB"), GAIN_MIN_DB, GAIN_MAX_DB, GAIN_DEFAULT_DB));
	parameters.addParameter(new RangeParameter(STR16("Balance"), kBalanceId, STR16("%"), -100, 100, 0));

	// fix for RangeParameter (default value is not yet set)
	for(int i = 0; i < parameters.getParameterCount(); i++){
		Parameter* p = parameters.getParameterByIndex(i);
		p->setNormalized(p->getInfo().defaultNormalizedValue);
	}
}


//-----------------------------------------------------------------------------
Plugin::Plugin ()
: numChannels(0)
, sampleRate(0)
, gain(1)
, balance(0.5f)
{
	setControllerClass (PluginControllerUID);
}
//-----------------------------------------------------------------------------
void Plugin::startProcessing(int numChannels, SampleRate sampleRate){
	this->numChannels = numChannels;
	this->sampleRate = sampleRate;
	leftProcessor.initialize(sampleRate);
	rightProcessor.initialize(sampleRate);
}
tresult PLUGIN_API Plugin::process (ProcessData& data)
{
	if (hasInputParameterChanged(data, kGainId)){
        gain = getInputParameterChange(data, kGainId);
    }
    if (hasInputParameterChanged(data, kBalanceId)){
        balance = getInputParameterChange(data, kBalanceId);
    }
    
	// Umrechnung Parameter 0...1 in dB: -100 ... 0 dB
	float db = gain * 106 - 100;
	float factor = pow(10, db/20);

	float gainLeft = factor;
	float gainRight = factor;
	if (balance < 0.5){
		gainRight *= (2 * balance);
	}
	else{
		gainLeft *= (2* (1 - balance));
	}    
	leftProcessor.setGain(gainLeft);
	rightProcessor.setGain(gainRight);


 	if (numChannels > 0){
		float* leftInputChannel = data.inputs[0].channelBuffers32[0];
		float* leftOutputChannel = data.outputs[0].channelBuffers32[0];
		leftProcessor.process(leftInputChannel, leftOutputChannel, data.numSamples);
	}
	if (numChannels > 1){
		float* rightInputChannel = data.inputs[0].channelBuffers32[1];
		float* rightOutputChannel = data.outputs[0].channelBuffers32[1];
		rightProcessor.process(rightInputChannel, rightOutputChannel, data.numSamples);
	}
	return kResultTrue;
}


}} // namespaces

