#include "mood.hpp"
#include "esp_random.h"

const char* Idlemood::name() const{
    return "IDLE";
} 
uint32_t Idlemood::blinkInterval()const{
    return 2000+(esp_random()%3000);
}
uint32_t Idlemood::blinkDuration()const{
    return 300;
}
float Idlemood::pupilRange()const{
    return 0.5f;
}
float Idlemood::pupilbias()const{
    return 0.0f;
}

//Happy
const char* Happymood::name()const{
    return "HAPPY";
}
uint32_t Happymood::blinkInterval()const{
    return 1000+(esp_random()%1000);
}
uint32_t Happymood::blinkDuration()const{
    return 250;
}
float Happymood::pupilRange()const{
    return 0.7f;
}
float Happymood::pupilbias()const{
    return -0.2f;
}

//Suprise
const char* Suprisedmood::name() const{
    return "SURPRISED"; 
}

uint32_t Suprisedmood::blinkInterval() const {
    return 300 + (esp_random() % 500);
}

uint32_t Suprisedmood::blinkDuration() const {
    return 200;
}

float Suprisedmood::pupilRange() const {
    return 0.8f;
}
float Suprisedmood::pupilbias()const{
    return 0.0f;
}

//Sleepy
const char* Sleepymood::name() const{ 
    return "SLEEPY"; 
}

uint32_t Sleepymood::blinkInterval() const {
    return 4000 + (esp_random() % 4000);
}

uint32_t Sleepymood::blinkDuration() const {
    return 700;
}

float Sleepymood::pupilRange() const {
    return 0.3f;
}
float Sleepymood::pupilbias()const{
    return 0.6f;
}