// AL2 code originally from: nsd.dyndns.org/speech/ 

#define VOICE_SPEED   1; // 1 = 4mhz clock ( higher pitched ), 2 = 2.66 ( lower pitched ), 3 = crazy low

// SPO pin assignments on arduino
#define SPO_A1    2
#define SPO_A2    3
#define SPO_A3    4
#define SPO_A4    5
#define SPO_A5    6
#define SPO_A6    7
#define SPO_ALD   8
#define SPO_LRQ   9
#define SPO_RESET 10
#define SPO_OSC1  11

// SPO-256-AL2 phonemes
enum {
  // Silence
  pPA1 = 0x00, // before BB,DD,GG,JH (10 msec)
  pPA2 = 0x01, // before BB,DD,GG,JH (30 msec)
  pPA3 = 0x02, // before PP,TT,KK,CH and between words (50 msec)
  pPA4 = 0x03, // between clauses and sentences (100 msec)
  pPA5 = 0x04, // between clauses and sentences (200 msec)
  
  // Short Vowels
  pIH  = 0x0c, // sIt
  pEH  = 0x07, // End, gEntlemen, Extend
  pAE  = 0x1a, // hAt, extrAct, Act
  pUH  = 0x1e, // bOOk, cOOkie, fUll
  pAO  = 0x17, // tALk, sOng, AUght
  pAX  = 0x0f, // sUCCeed, lApel, intrUCt
  pAA  = 0x18, // hOT, pOTtery, cOTen

  // Long Vowels
  pIY  = 0x13, // sEE, trEAt, pEOple, pEnny
  pEY  = 0x14, // bEIge, grEAt, stAte, trAY
  pAY  = 0x06, // skY, kIte, mIGHty
  pOY  = 0x05, // bOY, nOIse, vOIce
  pUW1 = 0x16, // compUter (after clusters with YY)
  pUW2 = 0x1f, // fOOd, tWO (monosyllabic words)
  pOW  = 0x35, // zOne, clOse, snOW, bEAU
  pAW  = 0x20, // OUt, sOUnd, mOUse, dOWn
  pEL  = 0x3e, // saddLE, littLE, angLE, gentLEmen

  // R-Colored Vowels
  pER1 = 0x33, // lettER, furnitURE, intERRupt
  pER2 = 0x34, // bIRd, fERn, bURn (monosyllabic words)
  pOR  = 0x3a, // stORe, adORn, fORtune
  pAR  = 0x3b, // alARm, fARm, gARment
  pYR  = 0x3c, // clEAR, EARring, IResponsible
  pXR  = 0x2f, // repaiR, haiR, declaRE, staRE

  // Resonants
  pWW  = 0x2e, // Wool, We, lingUIst
  pRR1 = 0x0e, // Rural, WRite, x-Ray (initial position)
  pRR2 = 0x27, // bRain, bRown, gRease (initial clusters)
  pLL  = 0x2d, // Lake, Like, heLLo, steeL
  pYY1 = 0x31, // cUte, bEAUty, compUter (clusters)
  pYY2 = 0x19, // Yes, Yarn, Yo-Yo (initial position)

  // Voiced Fricatives
  pVV  = 0x23, // Vest, proVE, eVen
  pDH1 = 0x12, // THis, THen, THey (initial position)
  pDH2 = 0x36, // baTHe, baTHing (word-final and between vowels)
  pZZ  = 0x2b, // Zoo, phaSE
  pZH  = 0x26, // aZure, beiGE, pleaSUre

  // Voiceless Fricatives
  pFF  = 0x28, // Food (can be doubled for initial position)
  pTH  = 0x1d, // THin (can be doubled for initial position)
  pSS  = 0x37, // Snake, veSt (can be doubled for initial position)
  pSH  = 0x25, // SHip, SHirt, leaSH, naTion
  pHH1 = 0x1b, // He (before front vowels YR,IY,IH,EY,EH,XR,AE)
  pHH2 = 0x39, // Hoe (before back vowels UW,UH,OW,OY,AO,OR,AR)
  pWH  = 0x30, // WHig, WHite, tWenty
  
  // Voiced Stops
  pBB1 = 0x1c, // riB, fiBBer, (in clusters) BLeed, BRown
  pBB2 = 0x3f, // Business, Beast (initial position before vowel)
  pDD1 = 0x15, // coulD, playeD, enD (final position)
  pDD2 = 0x21, // Do, Down, Drain (initial position and clusters)
  pGG1 = 0x24, // Got (before high front vowels YR,IY,IH,EY,EH,XR)
  pGG2 = 0x3d, // GUest, Glue, Green (before high back vowels UW,UH,OW,OY,AX)
  pGG3 = 0x22, // wiG, anGer (before low vowels AE,AW,AY,AR,AA,AO,OR,ER)
  
  // Voiceless Stops
  pPP  = 0x09, // Pow, triP, amPle, Pleasure
  pTT1 = 0x11, // parTs, tesTs, iTs (final cluster before SS)
  pTT2 = 0x0d, // To, TesT, sTreeT (all positions except before final SS)
  pKK1 = 0x2a, // Can't, Cute, Clown, sCream (before front vowels YR,IY,IH,EY,EH,XR,AY,AE,ER,AX and initial clusters)
  pKK2 = 0x29, // speaK, tasK (final position or final cluster)
  pKK3 = 0x08, // Comb, QUick, Crane, sCream (before back vowels UW,UH,OW,OY,OR,AR,AO and initial clusters)
  
  // Affricates
  pCH  = 0x32, // CHurCH, feaTure
  pJH  = 0x0a, // JudGE, inJUre, dodGE
  
  // Nasal
  pMM  = 0x10, // Milk, alarM, aMple
  pNN1 = 0x0b, // thiN, earN (before front and central vowels YR,IY,IH,EY,EH,XR,AE,ER,AX,AW,AY, and final clusters)
  pNN2 = 0x38, // No (before back vowels UH,OW,OY,OR,AR,AA)
  pNG  = 0x2c, // striNG, aNGer, aNchor
};

// CANNED PHRASES /////////////////////////////////////////////////////

static const uint8_t PROGMEM VoiceEnabled[] = {pVV,pOY,pSS,pPA5,pEH,pNN1,pEY,pBB1,pLL,pEL,pDD1,pPA5};

///////////////////////////////////////////////////////////////////////

const char COMMAND_BEGIN_CHAR = '<';
const char COMMAND_END_CHAR = '>';
const char* COMMAND_DIVIDER_CHAR = ":";
const char* COMMAND_DIVIDER_CHAR_SECONDARY = ",";
const byte COMMAND_LENGTH = 200;

char receivedChars[COMMAND_LENGTH];
boolean newData = false;
char receivedNewData[COMMAND_LENGTH];
uint8_t phraseBuffer[200] {}; 
int phraseLength = 0;

void setup() {

  Serial.begin(115200);

  pinMode(SPO_LRQ,INPUT_PULLUP);
  pinMode(SPO_A1,OUTPUT);
  pinMode(SPO_A2,OUTPUT);
  pinMode(SPO_A3,OUTPUT);
  pinMode(SPO_A4,OUTPUT);
  pinMode(SPO_A5,OUTPUT);
  pinMode(SPO_A6,OUTPUT);
  digitalWrite(SPO_A1,LOW);
  digitalWrite(SPO_A2,LOW);
  digitalWrite(SPO_A3,LOW);
  digitalWrite(SPO_A4,LOW);
  digitalWrite(SPO_A5,LOW);
  digitalWrite(SPO_A6,LOW);
  pinMode(SPO_ALD,OUTPUT);
  digitalWrite(SPO_ALD,HIGH);

  pinMode(SPO_OSC1,OUTPUT); // equivalent to DDRB |= (1<<3);
  // make sure timer2 is powered (it should be, but just in case)
  PRR &= ~(/*PRTIM2*/1<<6);
  // NOTE: Port B bit 3 on an arduino uno maps to the board pin 11 (digital)
  // then configure timer 2 to togging OC2A at as close to the desired frequency as we can get
  TCCR2B = (/*CS2=stopped*/0<<0); // keep the clock stopped as we configure the timer
  TIMSK2 = 0; // no interrupts
  TCNT2 = 0; // reset count to 0
  ASSR = 0; // use internal CLK_IO clock source
  OCR2A = VOICE_SPEED; // 1 -> 4MHz, 2 -> 2.66MHz on pin OC2A
  OCR2B = 0xff; // to keep it out of the way
  TCCR2A = (/*COM2A=toggle OC2A on match*/1<<6) + (/*WGM2=CTC*/3<<0);
  TCCR2B = (/*WGM2*/1<<3) + (/*CS2=CLK_IO (prescalar=1)*/1<<0); // and upper bit of WGM2 is 0; note that the timer starts running once prescalar is configured, so we do this last
  TIFR2 = TIFR2; // toss away any accidental pending interrupts (not that it matters, just being neat & tidy)

  pinMode(SPO_RESET,OUTPUT);
  digitalWrite(SPO_RESET,LOW);
  delay(100);
  digitalWrite(SPO_RESET,HIGH);
  delay(100);

  size_t len = sizeof(VoiceEnabled); 
  speakPROGMEMPhrase(VoiceEnabled, len);
  Serial.println("s,ready|");
}

void loop() {

  checkSerialData();
  delay(10);
}

static void say(uint8_t phoneme) {
  
  while (digitalRead(SPO_LRQ));
  digitalWrite(SPO_A1, (phoneme>>0) & 1 ? HIGH : LOW);
  digitalWrite(SPO_A2, (phoneme>>1) & 1 ? HIGH : LOW);
  digitalWrite(SPO_A3, (phoneme>>2) & 1 ? HIGH : LOW);
  digitalWrite(SPO_A4, (phoneme>>3) & 1 ? HIGH : LOW);
  digitalWrite(SPO_A5, (phoneme>>4) & 1 ? HIGH : LOW);
  digitalWrite(SPO_A6, (phoneme>>5) & 1 ? HIGH : LOW);
  digitalWrite(SPO_ALD, LOW);
  digitalWrite(SPO_ALD, HIGH);
}

void speakPROGMEMPhrase(const uint8_t *phrase, size_t len) {
    
  for (size_t i = 0; i < len; i++)
    say(pgm_read_byte(phrase + i));
}

void processSerialCommand(char* command, char* param) {

  // commands should be in the format "<COMMAND:PARAMER>"

  if (strcmp(command, "say") == 0) {

    char* phonem = strtok(param, COMMAND_DIVIDER_CHAR_SECONDARY);
    while (phonem != 0) {

      phraseBuffer[phraseLength] = atoi(phonem);
      phraseLength ++;
      phonem = strtok(NULL, COMMAND_DIVIDER_CHAR_SECONDARY);
    }

    if (phraseLength > 0) {

      // add silence to the end
      phraseBuffer[phraseLength] = pPA5;
      for (int i = 0; i <= phraseLength; i++)
        say(phraseBuffer[i]);
    }

    phraseLength = 0;
    Serial.println("s,ok|");
  }
}

void checkSerialData() {
  
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char rc;
  
  while (Serial.available() > 0 && newData == false) {
    
    rc = Serial.read();

    if (recvInProgress == true) {
      
        if (rc != COMMAND_END_CHAR) {
          
            receivedChars[ndx] = rc;
            ndx++;
            
            if (ndx >= COMMAND_LENGTH)              
                ndx = COMMAND_LENGTH - 1;
        } else {
          
            receivedChars[ndx] = '\0'; // terminate the string
            recvInProgress = false;
            ndx = 0;
            newData = true;
        }
    }

    else if (rc == COMMAND_BEGIN_CHAR)      
        recvInProgress = true;
  }

  if (newData == true) {

    newData = false;
    memcpy(
      receivedNewData, 
      receivedChars, 
      COMMAND_LENGTH * sizeof(char));
      
  } else {

    receivedNewData[0] = 0;
    receivedNewData[1] = 0;
    receivedNewData[2] = 0;
  }

  if (receivedNewData[0] != 0 && receivedNewData[1] != 0 && receivedNewData[2] != 0) {
  
    // seperate the command from the parameter and process it
    
    char* command = strtok(receivedNewData, COMMAND_DIVIDER_CHAR);
    char* param = strtok(NULL, COMMAND_DIVIDER_CHAR);
    processSerialCommand(command, param);
  }
}
