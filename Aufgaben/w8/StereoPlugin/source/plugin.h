#ifndef __plugin__
#define __plugin__
#include "pluginadapter.h"
#include "GainProcessor.h"

namespace Steinberg {
namespace Vst {

// change these numbers!
// every plugin needs a unique UID
static const FUID PluginProcessorUID (0x34E8DE5F, 0x92554F53, 0x19FAE413, 0x3C935A18);
static const FUID PluginControllerUID (0xD39D3B65, 0xD7BF42FA, 0x843F4AC8, 0x44EB04F0);

// define parameter tags here:
enum
{
	kGainId = 0,
	kBalanceId
};


class Plugin : public PluginAdapter
{
public:
	Plugin ();
	virtual ~Plugin (){}
	tresult PLUGIN_API process (ProcessData& data);
	void startProcessing(int numChannels, SampleRate sampleRate);	
	static FUnknown* createInstance (void*) { return (IAudioProcessor*)new Plugin (); }
private:
	int numChannels;
	SampleRate sampleRate;
private:
	GainProcessor leftProcessor;
	GainProcessor rightProcessor;
	ParamValue gain;
	ParamValue balance;

};




}} // namespaces

#endif //__plugin__
