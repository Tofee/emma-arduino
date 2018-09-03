#include "arduino.h"
#include "mainwindow.h"

#include <QDateTime>
#include <QTimer>
#include <QThread>
#include <QApplication>

//const int analogInPin = A0;
int ledPin = 9;    // LED connected to digital pin 9 RED
int ledPin2 = 10;   // LED GREEN
int ledPin3 = 11;   // LED BLUE
int ledPin4 = 6;    // RED2
int ledPin5 = 5;    // GREEN2
int ledPin6 = 3;    //BLUE2

int led1_r, led1_g, led1_b;
int led2_r, led2_g, led2_b;

int current_H = 0;

Arduino::Arduino(MainWindow *parent) : QObject(parent)
{
}

void Arduino::analogWrite(int &pin, int value)
{
    MainWindow *ui = (MainWindow*)parent();
    if(&pin == &ledPin) {
        ui->Set1RGB(value, ui->GetPin1G(), ui->GetPin1B());
    }
    else if(&pin == &ledPin2) {
        ui->Set1RGB(ui->GetPin1R(), value, ui->GetPin1B());
    }
    else if(&pin == &ledPin3) {
        ui->Set1RGB(ui->GetPin1R(), ui->GetPin1G(), value);
    }
    else if(&pin == &ledPin4) {
        ui->Set2RGB(value, ui->GetPin2G(), ui->GetPin2B());
    }
    else if(&pin == &ledPin5) {
        ui->Set2RGB(ui->GetPin2R(), value, ui->GetPin2B());
    }
    else if(&pin == &ledPin6) {
        ui->Set2RGB(ui->GetPin2R(), ui->GetPin2G(), value);
    }
}

void Arduino::delay(int ms)
{
    QApplication::processEvents();
    QThread::msleep(ms);
}

float random(float max)
{
    return (qrand()%1000*max)/1000;
}

//// missing definitions in Qt
#define max qMax
#define min qMin
float constrain(float v, float fmin, float fmax) { return qMax(qMin(v, fmax), fmin); }

void Arduino::setup()  {
  //Serial.begin(9600);
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
    timer->start(2500);
}


// from https://gist.github.com/postspectacular/2a4a8db092011c6743a7
// HSV->RGB conversion based on GLSL version
// expects hsv channels defined in 0.0 .. 1.0 interval
float fract(float x) { return x - int(x); }
float mix(float a, float b, float t) { return a + (b - a) * t; }
float step(float e, float x) { return x < e ? 0.0 : 1.0; }

void hsv2rgb(float h, float s, float v, float &r, float &g, float &b) {
  r = v * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  g = v * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
  b = v * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
}

void rgb2hsv(float r, float g, float b, float &h, float &s, float &v) {
  float _s = step(b, g);
  float px = mix(b, g, _s);
  float py = mix(g, b, _s);
  float pz = mix(-1.0, 0.0, _s);
  float pw = mix(0.6666666, -0.3333333, _s);
  _s = step(px, r);
  float qx = mix(px, r, _s);
  float qz = mix(pw, pz, _s);
  float qw = mix(r, px, _s);
  float d = qx - min(qw, py);
  h = abs(qz + (qw - py) / (6.0 * d + 1e-10));
  s = d / (qx + 1e-10);
  v = qx;
}

void HSV_to_RGB(int H, int S, int V, int &R, int &G, int &B)
{
    float Hf = H/256.f, Sf = S/256.f, Vf = V/256.f;
    float Rf, Gf, Bf;

    hsv2rgb(Hf, Sf, Vf, Rf, Gf, Bf);
    R = 256*Rf;
    G = 256*Gf;
    B = 256*Bf;
}

void RGB_to_HSV(int R, int G, int B, int &H, int &S, int &V)
{
    float Hf, Sf, Vf;
    float Rf = R/256.f, Gf = G/256.f, Bf = B/256.f;

    rgb2hsv(Rf, Gf, Bf, Hf, Sf, Vf);
    H = 256*Hf;
    S = 256*Sf;
    V = 256*Vf;
}



void Arduino::loop()  {
   // increment Hue of HSV
    current_H = (current_H + 40) % 256;
    // Deduce RGB
    HSV_to_RGB(current_H, 128, 200, led1_r, led1_g, led1_b);
    HSV_to_RGB(current_H, 128, int(random(200)), led2_r, led2_g, led2_b);

  // we do a fade in, from 0% to 100% of the chosen RGB color
  for(int fadePercentage = 0 ; fadePercentage <= 100; fadePercentage +=1) {
      // leds 1
      analogWrite(ledPin,  fadePercentage*led1_r/100);
      analogWrite(ledPin2, fadePercentage*led1_g/100);
      analogWrite(ledPin3, fadePercentage*led1_b/100);
      // leds 2
      analogWrite(ledPin4, fadePercentage*led2_r/100);
      analogWrite(ledPin5, fadePercentage*led2_g/100);
      analogWrite(ledPin6, fadePercentage*led2_b/100);
      delay(10);
  }

  // now we do a fade out, from 100% to 0% of the chosen RGB color
   for(int fadePercentage = 100 ; fadePercentage >= 0; fadePercentage -=1) {
      // leds 1
      analogWrite(ledPin,  fadePercentage*led1_r/100);
      analogWrite(ledPin2, fadePercentage*led1_g/100);
      analogWrite(ledPin3, fadePercentage*led1_b/100);
      // leds 2
      analogWrite(ledPin4, fadePercentage*led2_r/100);
      analogWrite(ledPin5, fadePercentage*led2_g/100);
      analogWrite(ledPin6, fadePercentage*led2_b/100);
      delay(10);
  }
}
