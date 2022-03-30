//
//// word gebruikt om te kijken of er een trein is.
//boolean isTrein= false;
//
//// word gebruikt voor de state machine
//int overgangState;
//
//void overgangStateSetup(){
//  overgangState = GEEN_KNOPPEN_GEDRUKT;
//}
//
//void overgangLoop(){
//  switch(overgangState){
//    case GEEN_KNOPPEN_GEDRUKT:
//    Serial.println("case: GEEN_KNOPPEN_GEDRUKT");
////    Doe helemaal niks.
//    case VOETGANGER_NOORD:
//    Serial.println("case: VOETGANGER_NOORD");
////    1. check of zuid groen heeft.
//    if(getButtonPressed[2] == 1){
//      // zuid heeft dus groen op dit moment.
//    } else {
//      // zuid heeft geen groen op dit moment.
//      // dus noord kan direct op groen komen
//      ledControlSetLedOn(leds[1],leds[3]);
//    }
////lampen voor zuid moeten op rood gaan.
////    2. lampen voor noord moeten op groen gaan.  
//    
//    case TREIN_AANWEZIG:
////    lampen gaan onmidderlijk op geel
//      ledControlSetLedOn(leds[5], leds[8]);
//  }
//}
//
//void setOvergangState(int optie){
//  overgangState = optie;
//}
