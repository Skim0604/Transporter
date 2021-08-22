
#include <PS2X_lib.h>
#include <Servo.h>

PS2X ps2x;
Servo lengan, capit;
const int IN1 = 9;
const int IN2 = 6;
const int IN3 = 8;
const int IN4 = 7;
const int ENA = 5;
const int ENB = 3;

int error = 0;
byte type = 0;
byte vibrate = 0;
int PlyStnLStickUpDn = 0;
int PlyStnLStickLtRt = 0;

void setup() {
  Serial.begin(57600);
  error = ps2x.config_gamepad(13, 11, 10, 12, false, false);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  lengan.attach(A0);
  capit.attach(A1);
  lengan.write(65);
  capit.write(130);

  if (error == 0) {
    Serial.println("CONECTING");
  }

  else if (error == 1)
    Serial.println("DISCONECT");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands");

  else if (error == 3)
    Serial.println("CONECTED");
}

void maju(int b, int a) {
  analogWrite(ENA, a);
  analogWrite(ENB, b);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);

}

void mundur(int b, int a) {
  analogWrite(ENA, a);
  analogWrite(ENB, b);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void kiri(int b, int a) {
  analogWrite(ENA, a);
  analogWrite(ENB, b);

  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void kanan(int b, int a) {
  analogWrite(ENA, a);
  analogWrite(ENB, b);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
}

void loop() {
  if (error == 1)
    return;

  else {
    ps2x.read_gamepad(false, vibrate);

    PlyStnLStickUpDn = ps2x.Analog(PSS_LY);
    PlyStnLStickLtRt = ps2x.Analog(PSS_LX);
    int joyLy = map(PlyStnLStickUpDn, 0, 255, -1023, 1023);
    int joyLx = map(PlyStnLStickLtRt, 0, 255, -1023, 1023);
    //analog
    //PELAN***********************************************//
    if (joyLy < -50 && ps2x.Button(PSB_L1)) {
      maju(45, 60);
      Serial.println(",Analog Forward PELAN 1");
    }

    else if (joyLy > 50 && ps2x.Button(PSB_L1)) {
      mundur(45, 60);
      Serial.println(",Analog Back PELAN 1");
    }
    //mode cepat 1 analog*********************************///
    else if (joyLy < -50 && ps2x.Button(PSB_R1)) {
      maju(150, 180);
      Serial.println(",Analog Forward 1");
    }

    else if (joyLy > 50 && ps2x.Button(PSB_R1)) {
      mundur(150, 180);
      Serial.println(",Analog Back 1");
    }
    
    //BELOK***********************************************//
    else if (joyLy < -50 && ps2x.Button(PSB_L2)) {
      maju(7, 240);
      Serial.println(",BELOK KIRI");
    }
    else if (joyLy < -50 && ps2x.Button(PSB_R2)) {
      maju(210, 10);
      Serial.println(",BELOK KANAN");
    }
    else if (joyLx < -50 && ps2x.Button(PSB_L1)) {
      kiri(75, 75);
      Serial.println(",Analog Left");
    }
    else  if (joyLx > 50 && ps2x.Button(PSB_L1)) {
      kanan(75, 75);
      Serial.println(",Analog Right");
    }
    else if (joyLx < -100) {
      kiri(100, 100);
      Serial.println(",Analog Left");
    }
    else  if (joyLx > 100) {
      kanan(100, 100);
      Serial.println(",Analog Right");
    }
     //Mode mormal analog**********************************//
    else  if (joyLy < -50) {
      maju(75, 100);
      Serial.println(",Analog Forward");
    }
     else if (joyLy > 50) {
      mundur(75, 100);
      Serial.println(",Analog Back");
    }
    //Button PAD*****************************************//
    else if (ps2x.Button(PSB_PAD_UP)) {
      lengan.write(60);
      Serial.println("lengan naik");
    }

    else if (ps2x.Button(PSB_PAD_DOWN)) {
      lengan.write(135);
      Serial.println("lengan turun");
    }
    //ACTION BUTTON
    else if (ps2x.Button(PSB_BLUE)) {
      capit.write(55);
      Serial.println("CAPIT CENGKRAM");
    }

    else if (ps2x.Button(PSB_PINK)) {
      capit.write(130);
      Serial.println("CAPIT LEPAS");
    }

    else {
      stop();
      Serial.println("Stop/no conditions");
    }
    delay(50);
  }
}
