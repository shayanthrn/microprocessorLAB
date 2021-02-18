#include "pitches.h"
#include "song.h"

float scale=0;

void playsong(){
  for(int note=0;note<sizeof(melody)/sizeof(int);note++){
    int duration=0;
    scale=analogRead(A8)/512;
    if(noteDurations[note]<0){
      duration=500/(-1*noteDurations[note]);
      duration=duration*1.5;
    }
    else{
      duration=500/noteDurations[note];
    }
    tone(8,(int)(melody[note]*scale),duration);
    delay((int)(duration*1.3));
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(10,INPUT);
  pinMode(A8,INPUT);
}

void loop() {
  int key=digitalRead(10);
  if(key==HIGH){
    playsong();
  }
}
