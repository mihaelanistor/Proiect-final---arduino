////
////tetrisMelody
////tetrisNoteDurations
////
////nationalAnthemMelody
////nationalAnthemNoteDurations
////
////marioMelody
////marioNoteDurations
////
//
//
//// tetris theme
////  //41
//  int tetrisMelody[] = {
//    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5,
//    NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
//    NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, 0
//  };
//  int tetrisNoteDurations[] = {
//    4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 3, 8,
//    4, 4, 4, 4, 8, 8, 8, 8, 3, 8, 4, 8, 8, 3,
//    8, 4, 8, 8, 4, 8, 8, 4, 4, 4, 4, 4, 4
//  };
//
//    // notes in the melody:
//  //imn
//    int nationalAnthemMelody[] = {
//      NOTE_A3, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_D5,
//      NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
//      NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4,
//      NOTE_D4, NOTE_D4, NOTE_D5, NOTE_D5, NOTE_D5,
//      NOTE_D5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
//      NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4
//    };
//  
//    // note durations: 4 = quarter note, 8 = eighth note, etc.:
//    // 77 notes
//    int nationalAnthemNoteDurations[] = {
//      4, 3, 8, 4, 4, 2, 4, 4, 3, 8, 4, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4,
//      4, 2, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4, 4, 4, 4, 4, 2, 4, 3, 8, 4, 4,
//      2, 4, 4, 3, 8, 4, 4, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4,
//      4, 2, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4, 4, 4, 4, 4, 2
//    };
//
//
// //rolex 
////    int melody[] = {
////      NOTE_B5, NOTE_B5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, NOTE_D5, NOTE_D5, NOTE_A5, NOTE_B5, NOTE_A5,
////      NOTE_B5, NOTE_B5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F6,
////      NOTE_F6, NOTE_F6, NOTE_D6, NOTE_F6, NOTE_F6, NOTE_D6, NOTE_F6, NOTE_D6, NOTE_F6, NOTE_D6, NOTE_F6, NOTE_D6, NOTE_F6, NOTE_D6, NOTE_G6,
////      NOTE_D6, NOTE_D6, NOTE_B5, NOTE_B5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5
////  
////    };
////    int noteDurations[] = {
////      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
////      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
////      4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
////      4, 4, 4, 4, 4, 4, 4, 4, 4, 4
////    };
//
//
//  //Mario main theme melody
//int marioMelody[] = {
//  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0,
//  NOTE_G6, 0, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0,
//  0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
// 
//  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7,
//  NOTE_D7, NOTE_B6, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0,
//  0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7,
//  NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0
//};
////Mario main them tempo
//int marioNoteDurations[] = {
//  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
//  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
//  12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9,
//  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
//  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
//  12, 12, 12, 12, 9, 9, 9,
//  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
//};
