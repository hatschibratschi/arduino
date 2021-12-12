// template is https://github.com/ejlabs/arduino-midi-sync/blob/master/Arduino_Master_Sync.ino

#include <TimerOne.h>
#include <EEPROM.h>
#include <Encoder.h>
#include <MIDI.h>

#define LED_PIN1 LED_BUILTIN // Tempo LED
//#define BLINK_TIME LED_BUILTIN // LED blink time
#define BUTTON_START 4 // Start/Stop Push Button here Rotary Encoder Button
//#define BUTTON_ROTARY 4 // Rotary Encoder Button

#define CLOCKS_PER_BEAT 24 // MIDI Clock Ticks
//#define AUDIO_SYNC 12 // Audio Sync Ticks
//#define AUDIO_SYNC2 12 // 2nd Audio Sync Ticks

#define MINIMUM_BPM 20
#define MAXIMUM_BPM 300

#define BLINK_TIME 4 // LED blink time

volatile int  blinkCount = 0,
              blinkCount2 = 0,
              AudioSyncCount = 0,
              AudioSyncCount2 = 0;

long intervalMicroSeconds,
      bpm,
      audio_sync2;

boolean playing = false,
      sync_editing = false,
      display_update = false;

Encoder myEnc(2, 3); // Rotary Encoder Pin 2,3 

void setup() {

  Serial.begin(9600);

  MIDI.begin(); // MIDI init
  MIDI.turnThruOff();

  bpm = EEPROMReadInt(0);
  if (bpm > MAXIMUM_BPM || bpm < MINIMUM_BPM) {
    bpm = 120;
  }
   
  Timer1.initialize(intervalMicroSeconds);
  Timer1.setPeriod(60L * 1000 * 1000 / bpm / CLOCKS_PER_BEAT);
  Timer1.attachInterrupt(sendClockPulse);  

  pinMode(BUTTON_START,INPUT_PULLUP);
  
  Serial.print("bpm ");
  Serial.println(bpm);
}

void bpm_display() { 
  updateBpm();
  EEPROMWriteInt(0,bpm);  
  display.setTextSize(4);
  display.setCursor(0,0);  
  display.setTextColor(WHITE, BLACK);
  display.print("     ");
  display.setCursor(0,0);
  display.print(bpm);
  display.display();
  display_update = false;
}

void updateBpm() { // update BPM function (on the fly)
  long interval = 60L * 1000 * 1000 / bpm / CLOCKS_PER_BEAT;  
  Timer1.setPeriod(interval);
}
