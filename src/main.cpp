#include <Arduino.h>
//#include <Plotter.h>

// Number of columns and Rows of the system
int num_columns = 1; //3
int num_rows = 1; //4
int vin = 5;
float R1[3] = {1000000, 10000, 1000};

//Mux control pins
int s0 = 8;
int s1 = 9;
int s2 = 10;
int s3 = 11;

int q0 = 3;
int q1 = 4;
int q2 = 5;
int q3 = 6;

//Mux in "SIG" pin
int SIG_pin_1 = 12;
int SIG_pin_2 = A1;

// Multiplexer 1
int rows_sensor_m1[4][4]={
  {0,0,0,0}, //channel 0 -> Linhas
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
};

// Multiplexer 2
int columns_sensor_m2[3][4]={
  {0,0,0,0}, //channel 0 -> Colunas
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
};

// Control Pins
int controlPin_m1[4] = {s0, s1, s2, s3};
int controlPin_m2[4] = {q0, q1, q2, q3};

void setup() {

// Multiplexer 1
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  digitalWrite(SIG_pin_1, HIGH);

// Multiplexer 2
  pinMode(q0, OUTPUT); 
  pinMode(q1, OUTPUT); 
  pinMode(q2, OUTPUT); 
  pinMode(q3, OUTPUT); 

  digitalWrite(q0, LOW);
  digitalWrite(q1, LOW);
  digitalWrite(q2, LOW);
  digitalWrite(q3, LOW);

  //digitalWrite(SIG_pin_2, HIGH);


  Serial.begin(9600);
}

void loop(){

    for (int row = 0; row < num_rows; row ++){

      for(int i = 0; i < 4; i ++){
        // Definition of the Channel for the row
        digitalWrite(controlPin_m1[i], rows_sensor_m1[row][i]);
      }

      for (int column = 0; column < num_columns; column ++){

        for(int i = 0; i < 4; i ++){
          // Definition of the Channel for the column
          digitalWrite(controlPin_m2[i], columns_sensor_m2[column][i]);
          // Serial.println(controlPin_m2[i]);
          // Serial.println(columns_sensor_m2[column][i]);
        }
        
        Serial.print("Row: ");
        Serial.print(row);
        Serial.print("\n");
        Serial.print("Column: ");
        Serial.print(column);
        Serial.print("\n");

        int val = analogRead(SIG_pin_2);//reads the analog input

        if (val){

        float buffer= val * vin;

        float vout= (buffer)/1024.0;

        buffer = (vin/vout) -1;

        float R2 = R1[column] * buffer;

        Serial.print("Leitura (Ohms): ");
        //Serial.println(R2);
        Serial.println(R2);
        Serial.print("\n");

        Serial.print("------\n"); 
        delay(1000);   
      }
    }
  }
}
