int temper = 0;
float EropaTemper = 0.0;
int pepa;
const uint8_t BUTTON = 2;
int counter = 0;
double wind_speed_kmH;
const uint8_t BUTTON2 = 3;
int rain_counter = 0;
double rainMM = 0.0;
int windDirCode;
int wind_dirReturn;
float temperatureReturn;
double rainReturn;
double wind_speedReturn;


unsigned long currentMillis;
unsigned long startMillisTemperture; 
unsigned long startMillisWindDirection;
unsigned long startMillisWindspeed; 
unsigned long startMillisRain;    




void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON),switchPressed, CHANGE);
  pinMode(BUTTON2, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON2),switchPressed2, CHANGE);
  pinMode(7,OUTPUT);
  startMillisTemperture = millis();
  startMillisWindDirection = millis();
  startMillisWindspeed = millis();
  startMillisRain = millis();
}

void loop()
{
  
  currentMillis = millis();
  temperatureReturn = checkTemperature();
  wind_dirReturn = CheckWindDirection();
  wind_speedReturn = CheckWindSpeed();
  rainReturn = CheckRain();
  Serial.print(temperatureReturn) ; Serial.print(':') ;
  Serial.print(wind_dirReturn) ; Serial.print(':') ;
  Serial.print(wind_speedReturn) ; Serial.print(':') ;
  Serial.print(rainReturn) ; Serial.print('\n') ;
  delay(100);
  

  
  }


float checkTemperature()
{
   if (currentMillis - startMillisTemperture >= 100)
  {
  temper = analogRead(A0);

  startMillisTemperture = currentMillis;

  return (0.488155 * (temper -20) -40);
  }
}

int CheckWindDirection(){
  if (currentMillis - startMillisWindDirection >= 100)
  {
  pepa = analogRead(A1); //TODO: colebrate
  if (pepa >= 525 && pepa <= 540){windDirCode = 0;} //N
  else if (pepa >= 270 && pepa <= 285){windDirCode = 1;} //NNE
  else if (pepa >= 300 && pepa <= 330){windDirCode = 2;} //NE
  else if (pepa >= 50 && pepa <= 60){windDirCode = 3;} //ENE
  else if (pepa >= 60 && pepa <= 65){windDirCode = 4;} //E
  else if (pepa >= 40 && pepa <= 50){windDirCode = 5;} // ESE
  else if (pepa >= 120 && pepa <= 130){windDirCode = 6;} //SE
  else if (pepa >= 80 && pepa <= 90){windDirCode = 7;} //SSE
  else if (pepa >= 190 && pepa <= 200){windDirCode = 8;} //S
  else if (pepa >= 160 && pepa <= 170){windDirCode = 9;} //SSW
  else if (pepa >= 425 && pepa <= 440){windDirCode = 10;} //SW 
  else if (pepa >= 405 && pepa <= 415){windDirCode = 11;} //WSW
  else if (pepa >= 560 && pepa <= 570){windDirCode = 12;} //W
  else if (pepa >= 600 && pepa <= 610){windDirCode = 13;} //WNW
  else if (pepa >= 475 && pepa <= 480){windDirCode = 14;} // NW
  else if (pepa >= 300 && pepa <= 330){windDirCode = 15;} //NNW
  else {windDirCode = pepa;} //No Direction Found
  startMillisWindDirection = currentMillis;
  return windDirCode;

  }
}
double CheckWindSpeed(){
  if (currentMillis - startMillisWindspeed >= 1000){
    wind_speed_kmH = counter * 2.4;
    counter = 0;
    startMillisWindspeed = currentMillis;
    return wind_speed_kmH;
  }
}
float CheckRain(){
  if (currentMillis - startMillisRain >= 10000){ 
    rainMM = rain_counter * 0.2794;
    rain_counter = 0;
    startMillisRain = currentMillis;
    return rainMM;
  }

}
void switchPressed() {
  if (digitalRead(BUTTON) == HIGH){
    counter++;
    }
}
void switchPressed2() {
  if (digitalRead(BUTTON2) == HIGH){
    rain_counter++;
    }
}



