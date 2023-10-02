// audio_pool.h
audio_buffer_pool_t *ap;

FIL fil_current;
char *fil_current_name;
bool fil_is_open;
uint8_t cpu_utilization;
uint8_t fil_buf[SAMPLES_PER_BUFFER * 4];
int32_t phases[2];
uint16_t phases_since_last[2];
int32_t phases_old[2];
int32_t phase_new;
int16_t mem_samples[2][44100];
uint16_t mem_index[2];
bool mem_use;
bool phase_change;
unsigned int fil_bytes_read;
unsigned int fil_bytes_read2;
// uint16_t sf->bpm_tempo = 185;
uint16_t bpm_last = 185;
uint8_t fil_current_id = 0;
uint8_t fil_current_id_next = 0;
uint8_t fil_current_bank = 0;
uint8_t fil_current_bank_next = 0;
uint8_t fil_current_bank_sel = 0;
bool fil_current_change = false;
FileList file_list[16];
FRESULT fil_result;
struct repeating_timer timer;
bool phase_forward = 1;
bool sync_using_sdcard = false;

// voice 1 + 2
// voice 1 is always an envelope UP
// voice 2 is always an envelope DOWN
// voice 1 is only voice that jumps
// voice 2 takes place of old voice and continues
Envelope2 *envelope1;
Envelope2 *envelope2;
Envelope2 *envelope3;
Envelope2 *envelope_pitch;
EnvelopeGate *envelopegate;
Noise *noise_wobble;
uint vols[2];

float vol3 = 0;
float envelope_pitch_val;
float envelope_wobble_val;
uint beat_current = 0;
uint beat_total = 0;
uint debounce_quantize = 0;
uint32_t bpm_timer_counter = 0;
uint16_t bpm_timer_reset = 96;
uint8_t retrig_beat_num = 0;
uint16_t retrig_timer_reset = 96;
bool retrig_first = false;
bool retrig_ready = false;
float retrig_vol = 1.0;
float retrig_vol_step = 0;

SaveFile *sf;
Charlieplex *cp;
PCA9552 *pca;

#ifdef INCLUDE_BASS
Bass *bass;
#endif

IIR *myFilter0;
IIR *myFilter1;
bool sdcard_startup_is_starting = false;

#ifdef INCLUDE_RGBLED
WS2812 *ws2812;
#endif