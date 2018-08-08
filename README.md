# SP0256A-AL2-Voice-Synthesizer over serial

Firstly, let me give all the credit for this to the author of [this article](nsd.dyndns.org/speech/). Literally all the hard work here has ben figured out by them. I just added some extra sauce.

## Build video
COMING SOON

## Schematic
COMING SOON

## Usage
When the device is ready it will send back "s,ready|" via serial. s, meaning a system message, ready being the message.
Once you've received that you can send "say" commands via serial data to the arduino in the format:
<say:XX,XX,XX,XX>
Where XX is an integer representing the phoneme for that position. When it's done speaking it will reply with "s,ok|"
See below for a breakdown of all the phoneme integer values.

## Practical example
Wait for "s,ready|" and then send "<say:6,16,2,17,23,41,19,44,2,17,31,2,25,31>" which will say "I'm talking to you"

# Phoneme integer values for sending via serial.
0, // before BB,DD,GG,JH (10 msec)
1, // before BB,DD,GG,JH (30 msec)
2, // before PP,TT,KK,CH and between words (50 msec)
3, // between clauses and sentences (100 msec)
4, // between clauses and sentences (200 msec)
  
// Short Vowels
12, // sIt
7, // End, gEntlemen, Extend
26, // hAt, extrAct, Act
30, // bOOk, cOOkie, fUll
23, // tALk, sOng, AUght
15, // sUCCeed, lApel, intrUCt
24, // hOT, pOTtery, cOTen

// Long Vowels
19, // sEE, trEAt, pEOple, pEnny
20, // bEIge, grEAt, stAte, trAY
6, // skY, kIte, mIGHty
5, // bOY, nOIse, vOIce
22, // compUter (after clusters with YY)
31, // fOOd, tWO (monosyllabic words)
53, // zOne, clOse, snOW, bEAU
32, // OUt, sOUnd, mOUse, dOWn
62, // saddLE, littLE, angLE, gentLEmen

// R-Colored Vowels
51, // lettER, furnitURE, intERRupt
52, // bIRd, fERn, bURn (monosyllabic words)
58, // stORe, adORn, fORtune
59, // alARm, fARm, gARment
60, // clEAR, EARring, IResponsible
47, // repaiR, haiR, declaRE, staRE

// Resonants
46, // Wool, We, lingUIst
14, // Rural, WRite, x-Ray (initial position)
39, // bRain, bRown, gRease (initial clusters)
45, // Lake, Like, heLLo, steeL
49, // cUte, bEAUty, compUter (clusters)
25, // Yes, Yarn, Yo-Yo (initial position)

// Voiced Fricatives
35, // Vest, proVE, eVen
18, // THis, THen, THey (initial position)
54, // baTHe, baTHing (word-final and between vowels)
43, // Zoo, phaSE
38, // aZure, beiGE, pleaSUre

// Voiceless Fricatives
40, // Food (can be doubled for initial position)
29, // THin (can be doubled for initial position)
55, // Snake, veSt (can be doubled for initial position)
37, // SHip, SHirt, leaSH, naTion
27, // He (before front vowels YR,IY,IH,EY,EH,XR,AE)
57, // Hoe (before back vowels UW,UH,OW,OY,AO,OR,AR)
48, // WHig, WHite, tWenty
  
// Voiced Stops
28, // riB, fiBBer, (in clusters) BLeed, BRown
63, // Business, Beast (initial position before vowel)
21, // coulD, playeD, enD (final position)
33, // Do, Down, Drain (initial position and clusters)
36, // Got (before high front vowels YR,IY,IH,EY,EH,XR)
61, // GUest, Glue, Green (before high back vowels UW,UH,OW,OY,AX)
34, // wiG, anGer (before low vowels AE,AW,AY,AR,AA,AO,OR,ER)
  
// Voiceless Stops
9, // Pow, triP, amPle, Pleasure
17, // parTs, tesTs, iTs (final cluster before SS)
13, // To, TesT, sTreeT (all positions except before final SS)
42, // Can't, Cute, Clown, sCream (before front vowels YR,IY,IH,EY,EH,XR,AY,AE,ER,AX and initial clusters)
41, // speaK, tasK (final position or final cluster)
8, // Comb, QUick, Crane, sCream (before back vowels UW,UH,OW,OY,OR,AR,AO and initial clusters)
  
// Affricates
50, // CHurCH, feaTure
10, // JudGE, inJUre, dodGE
  
// Nasal
16, // Milk, alarM, aMple
11, // thiN, earN (before front and central vowels YR,IY,IH,EY,EH,XR,AE,ER,AX,AW,AY, and final clusters)
56, // No (before back vowels UH,OW,OY,OR,AR,AA)
44, // striNG, aNGer, aNchor