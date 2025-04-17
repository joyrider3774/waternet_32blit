#include <cstring>
#include <stdint.h>
#include <32blit.hpp>

#include "commonvars.hpp"
#include "sound.hpp"

#include <32blit.hpp>

blit::Timer timer_music;

//I (joyrider3774) created the music in this tool : https://onlinesequencer.net

uint8_t prev_music, music_on, sound_on, music_pause, music_selecting;
uint16_t track[255];
uint16_t music_note, music_tempo, tracklen;
uint8_t music_loop;

constexpr uint8_t sfxSustain = 100 * 15 / frameRate;

constexpr uint8_t pause1 = 13;
constexpr uint8_t pause2 = 4;
constexpr uint8_t pause3 = 12;
constexpr uint8_t pause4 = 11;

constexpr uint8_t NOTE_REST = 0;
constexpr uint16_t NOTE_D6 = 1175;  // 1174.66 Hz
constexpr uint16_t NOTE_DS6 = 1245; // 1244.51 Hz
constexpr uint16_t NOTE_E6 = 1319;  // 1318.51 Hz
constexpr uint16_t NOTE_F6 = 1397;  // 1396.91 Hz
constexpr uint16_t NOTE_C4 = 262;   // 261.63 Hz
constexpr uint16_t NOTE_CS4 = 277;  // 277.18 Hz
constexpr uint16_t NOTE_D4 = 294;   // 293.66 Hz
constexpr uint16_t NOTE_DS4 = 311;  // 311.13 Hz
constexpr uint16_t NOTE_E4 = 330;   // 329.63 Hz
constexpr uint16_t NOTE_F4 = 349;   // 349.23 Hz



//https://onlinesequencer.net/2498607
const uint16_t music_levelsCleared[] ={
    NOTE_D6,pause4,
    NOTE_DS6,pause4,
    NOTE_D6,pause4,
    NOTE_REST,pause4,
    NOTE_D6,pause4,
    NOTE_E6,pause4,
    NOTE_F6,pause4,
    NOTE_E6,pause4,
    NOTE_E6,pause4,
    NOTE_E6,pause4,
    NOTE_D6,pause4,
    NOTE_REST,pause4,
    NOTE_DS6,pause4,
    NOTE_E6,pause4,
    NOTE_DS6,pause4,
    NOTE_REST,pause4,
    NOTE_E6,pause4,
    NOTE_F6,pause4,
    NOTE_E6,pause4,
    NOTE_REST,pause4,
    NOTE_D6,pause4,
    NOTE_DS6,pause4,
    NOTE_D6,pause4,
    NOTE_E6,pause4,
    NOTE_E6,pause4,
    NOTE_DS6,pause4,
    NOTE_DS6,pause4,
    NOTE_D6,pause4,
    NOTE_D6,pause4,
    NOTE_DS6,pause4,
    NOTE_E6,pause4,
    NOTE_DS6,pause4,
    NOTE_REST,pause4,
    NOTE_E6,pause4,
    NOTE_DS6,pause4,
    NOTE_E6,pause4,
    NOTE_DS6,pause4,
    NOTE_DS6,pause4,
    NOTE_E6,pause4,
    NOTE_REST,pause4,
    NOTE_E6,pause4,
    NOTE_F6,pause4,
    NOTE_DS6,pause4,
    NOTE_E6,pause4,
    NOTE_REST,pause4,
    NOTE_F6,pause4,
    NOTE_E6,pause4,
    NOTE_F6,pause4,
};

//https://onlinesequencer.net/2484974
const uint16_t music_won[] ={
  NOTE_DS6,pause2,
  NOTE_D6,pause2,
  NOTE_DS6,pause2,
  NOTE_E6,pause2,
  NOTE_DS6,pause2,
  NOTE_E6,pause2,
  NOTE_F6,pause2 << 2,
  NOTE_REST,pause2,
};

//https://onlinesequencer.net/2485064
const uint16_t music_game[] ={ 
    NOTE_REST,pause3,
    NOTE_C4,pause3,
    NOTE_CS4,pause3,
    NOTE_REST,pause3,
    NOTE_C4,pause3,
    NOTE_CS4,pause3,
    NOTE_CS4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_E4,pause3,
    NOTE_F4,pause3,
    NOTE_REST,pause3,

    NOTE_C4,pause3,
    NOTE_CS4,pause3,
    NOTE_REST,pause3,
    NOTE_C4,pause3,
    NOTE_CS4,pause3,
    NOTE_CS4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_E4,pause3,
    NOTE_F4,pause3,
    NOTE_REST,pause3,

    NOTE_D4,pause3,
    NOTE_C4,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_DS4,pause3,
    NOTE_D4,pause3,
    NOTE_C4,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_D4,pause3,
    NOTE_C4,pause3,
    NOTE_REST,pause3,
    NOTE_D4,pause3,
    NOTE_C4,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_DS4,pause3,
    NOTE_E4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_C4,pause3,
    NOTE_CS4,pause3,
    NOTE_DS4,pause3,
    NOTE_F4,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_DS4,pause3,
    NOTE_DS4,pause3,
    NOTE_REST,pause3,
    NOTE_E4,pause3,
    NOTE_D4,pause3,
    NOTE_D4,pause3,
    NOTE_REST,pause3,
    NOTE_DS4,pause3,
    NOTE_CS4,pause3,
    NOTE_CS4,pause3,
    NOTE_REST,pause3,
    NOTE_D4,pause3,
};

//https://onlinesequencer.net/2484977
const uint16_t music_intro[] = {
    NOTE_C4,pause1,
    NOTE_C4,pause1 * 2,
    NOTE_D4,pause1,
    NOTE_DS4,pause1,
    NOTE_C4,pause1,
    NOTE_REST,pause1 * 8,
    
    NOTE_C4,pause1,
    NOTE_C4,pause1 * 2,
    NOTE_D4,pause1,
    NOTE_DS4,pause1,
    NOTE_C4,pause1,
    NOTE_D4,pause1,
    NOTE_C4,pause1,
    NOTE_CS4,pause1,
    NOTE_REST,pause1 * 4,

    NOTE_C4,pause1,
    NOTE_C4,pause1 * 2,
    NOTE_D4,pause1,
    NOTE_DS4,pause1,
    NOTE_C4,pause1,
    NOTE_REST,pause1 * 8,
    
    NOTE_C4,pause1,
    NOTE_C4,pause1 * 2,
    NOTE_D4,pause1,
    NOTE_DS4,pause1,
    NOTE_C4,pause1,
    NOTE_D4,pause1,
    NOTE_C4,pause1,
    NOTE_CS4,pause1,
    NOTE_REST,pause1 * 4,

    NOTE_D4,pause1,
    NOTE_D4,pause1, 
    NOTE_CS4,pause1,
    NOTE_C4,pause1,
    NOTE_DS4,pause1,
    NOTE_CS4,pause1,
    NOTE_D4,pause1,
    NOTE_DS4,pause1,
    NOTE_CS4,pause1,
    NOTE_DS4,pause1,
    NOTE_D4,pause1,
    NOTE_D4,pause1,
    NOTE_D4,pause1,
    NOTE_E4,pause1,
    NOTE_C4,pause1,
    NOTE_CS4,pause1,
    NOTE_E4,pause1,
    NOTE_D4,pause1 * 3,
    NOTE_REST,pause1 * 4,
};

void playMusicTone(uint16_t tone, uint16_t sustain)
{
    if((tone == 0) || music_selecting)
        channels[1].off();
    else
    {
        channels[1].waveforms   = Waveform::SQUARE;
        channels[1].attack_ms   = 1;
        channels[1].decay_ms    = 60*sustain;
        channels[1].sustain     = 0;
        channels[1].release_ms  = 0;
        channels[1].volume      = 0xffff;
        channels[1].frequency   = tone;
        channels[1].trigger_attack();
    }
}

void playNote()
{   
    if(music_selecting)
        return;

    if(music_note < tracklen)
    {
        //Set the new delay to wait
        music_tempo = track[music_note+1];
        playMusicTone(track[music_note],music_tempo);
        //printf("%d %d\n",track[music_note], track[music_note+1]);
        //Skip to the next note
        music_note += 2;
               
        if (music_note > tracklen - 1)
        {
            if(music_loop)
            {
                music_note = 0;
            }
        }
    }
}

void pauseMusic()
{
    music_pause = 1;
    stopMusic();
}

void unpauseMusic()
{
    music_pause = 0;
}

void musicTimer(blit::Timer &t)
{
    if(music_selecting)
        return;
    if(music_pause)
        return;
    //Play some music
    if (music_tempo == 0)
    {
        if(music_on)
        {
            playNote();
        }
    }
    //Else wait for the next note to play
    else 
    {
        music_tempo--;
    }
}

void stopMusic()
{
    channels[1].off();  
}

void setMusicOn(uint8_t value)
{
    music_on = value;
    if(music_on)
    {
        if (prev_music != 0)
            SelectMusic(prev_music, 1);
        else
        {
            //this can only happen on title screen
            //normally this does not belong here
            //but if music was off in eeprom no music was playing
            //before and you can only enable it in the main - options - menu
            //where title music plays
            if (gameState == gsTitle)
                SelectMusic(musTitle, 1);
        }
    }
    else
    {
        channels[1].off();
    }
}

void setSoundOn(uint8_t value)
{
    sound_on = value;
}

uint8_t isMusicOn()
{
    return music_on;
}

uint8_t isSoundOn()
{
    return sound_on;
}

void initSound()
{
    sound_on = 0;
}

void SelectMusic(uint8_t musicFile, uint8_t force)
{
    if (((prev_music != musicFile) || force) && music_on)
    {
        music_selecting = 1;
        music_pause = 0;
        prev_music = musicFile;
        channels[1].off();
        memset(track, 0, sizeof(track));
        switch (musicFile) 
        {
            case musTitle:
                memcpy(track, music_intro, sizeof(music_intro));
                tracklen = sizeof(music_intro) / sizeof(uint16_t);
                music_loop = true;
                break;
            case musLevelClear:
                memcpy(track, music_won, sizeof(music_won));
                tracklen = sizeof(music_won) / sizeof(uint16_t);
                music_loop = false;
                break;
            case musAllLevelsClear:
                memcpy(track, music_levelsCleared, sizeof(music_levelsCleared));
                tracklen = sizeof(music_levelsCleared) / sizeof(uint16_t);
                music_loop = true;
                break;
            case musGame:
                memcpy(track, music_game, sizeof(music_game));
                tracklen = sizeof(music_game) / sizeof(uint16_t);
                music_loop = true;
                break;
        }
        music_note = 0;
        music_tempo = 0;
        music_selecting = 0;
    }
}

void playSound(uint16_t tone)
{
    if(!sound_on)
        return;
    
    channels[0].waveforms   = Waveform::SQUARE;
    channels[0].attack_ms   = 16;
    channels[0].decay_ms    = sfxSustain;
    channels[0].sustain     = 0;
    channels[0].release_ms  = 32;
    channels[0].volume      = 0xffff;
    channels[0].frequency   = tone;
    channels[0].trigger_attack();
}

void initMusic()
{
    music_on = 0;
    prev_music = 0;
    timer_music.init(musicTimer, 16, -1);
    timer_music.start();
}

void playGameMoveSound()
{
    playSound(750);
}

void playErrorSound()
{
    playSound(210);
}

void playMenuSelectSound()
{
    playSound(1250);
}

void playMenuBackSound()
{
   playSound(1000);
}

void playMenuAcknowlege()
{
    playSound(900);
}

void playGameAction()
{
    playSound(600);
}
