#include <VernierLib.h>   //include Vernier functions in this sketch
#include <math.h>

VernierLib Vernier;     //create an instance of the VernierLib library

// create global variable to store sensor reading
float sensorReading; 

// global multipurpose counter
int i;

// For Time measurement
unsigned long StartTime, EndTime, CheckTime, StartLoop, EndLoop;
unsigned long DelayLoop = 10000; // (microsecond)

// For Peak detection
int PeakScanArray[20], PrePeak, PostPeak;
int PeakScanSide = 2;
int IsPeak = 0;
int PeakLag = 100; // (millisecond)

// For Period and Frequency
float Period, Frequency, FrequencyValid, FrequencyOut;
float Weight = 0.8;


void setup() {
  Serial.begin(9600);       //setup communication to display
  Vernier.autoID();       //identify the sensor being used
  
  //  Some useful initialization
  for (int i = 0; i <= 2 * PeakScanSide; i++) {PeakScanArray[i] = 0;}
  FrequencyValid = 0;
  StartTime = millis();
}

void loop() {
  StartLoop = micros();       // Start measuring Loop duration
  sensorReading = Vernier.readSensor();   // Read data

  // Shift each data point one step, intake new data,
  // prepare to scan for peaks
  for (i = 2 * PeakScanSide; i >= 1; i--) {
    PeakScanArray[i] = PeakScanArray[i - 1];
  }
  PeakScanArray[0] = sensorReading;

  // Find Peak: Left Slope (PrePeak) - Right Slope (PostPeak) - Combine
  PrePeak = 0;
  for (i = 0; i <= PeakScanSide - 1; i++) {
    if (PeakScanArray[i] < PeakScanArray[i+1]) {PrePeak++;}
  }
  PostPeak = 0;
  for (i = PeakScanSide; i <= 2 * PeakScanSide - 1; i++) {
    if (PeakScanArray[i] > PeakScanArray[i+1]) {PostPeak++;}
  }
  
  // Find Peaks  
  CheckTime = millis();

  // Ensure sensitivity for peaks     
  if ((PrePeak >= PeakScanSide - 1) && (PostPeak >= PeakScanSide - 1)

  // Discard falsely redundant peaks, when multiple data points of one peak return
  // as many peaks close to each other. 
    && (CheckTime - StartTime >= PeakLag)
      ) {IsPeak = 1;}
  else {IsPeak = 0;}
  

// Only if at Peak, proceed to measure period (by timestamps) and calculate and frequency.
  if (IsPeak == 1) {
    EndTime = millis();
    Period = (EndTime - StartTime); // millisecond
    StartTime = millis();
    Frequency = 1000 / Period*60;
// Only output valid frequencies, discard others.
// Smoothen data by weighted averages with previous data. 
    if ((Frequency < 200)&&(Frequency > 20)){FrequencyValid = FrequencyValid*Weight + Frequency*(1-Weight);}
    FrequencyOut = FrequencyValid;
  }

// Print out
  Serial.print(round(FrequencyOut));
  Serial.print("/");
  Serial.println(sensorReading);

// Delay using Arduino internal clock instead of delay() to enhance accuracy
  EndLoop = micros();
  while (EndLoop - StartLoop < DelayLoop) {EndLoop = micros();}
}