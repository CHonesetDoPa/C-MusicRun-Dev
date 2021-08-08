
int melody[1]={};
int noteDurations[1]={};
void setup() {
}
void loop(){ 
            for(int thisNote = 0; thisNote < sizeof(melody)/4; thisNote ++){
                tone(8,melody[thisNote],noteDurations[thisNote]);
                delay(noteDurations[thisNote]);
                noTone(8);
            }
        }