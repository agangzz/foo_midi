#ifndef __BMPlayer_h__
#define __BMPlayer_h__

#include "MIDIPlayer.h"

#include "bassmidi.h"

extern bool g_get_soundfont_stats( uint64_t & total_sample_size, uint64_t & sample_loaded_size );

class BMPlayer : public MIDIPlayer
{
public:
	// zero variables
	BMPlayer();

	// close, unload
	virtual ~BMPlayer();

	// configuration
	void setSoundFont( const char * in );
	void setFileSoundFont( const char * in );
	void setSincInterpolation(bool enable = true);
	void setEffects(bool enable = true);

private:
	virtual void send_event(uint32_t b);
	virtual void render(float * out, unsigned long count);

	virtual void shutdown();
	virtual bool startup();

	virtual bool get_last_error(std::string & p_out);

	void compound_presets( std::vector<BASS_MIDI_FONTEX> & out, std::vector<BASS_MIDI_FONTEX> & in, std::vector<long> & channels );

	void reset_parameters();

	bool load_font_item(std::vector<BASS_MIDI_FONTEX> & presetList, std::string path);

	std::string        sLastError;

	std::vector<HSOUNDFONT> _soundFonts;
    std::string        sSoundFontName;
    std::string        sFileSoundFontName;

	HSTREAM            _stream[3];

	bool               bSincInterpolation;
	bool               bEffects;

	bool               bank_lsb_overridden;
	uint8_t            bank_lsb_override[48];
};

#endif
