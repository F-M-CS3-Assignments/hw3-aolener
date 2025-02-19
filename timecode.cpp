/*
Author: Alex Olener
This is a c++ implementation of a TimeCode object which allows for manipulation of minute, second, and hour, objects. TimeCode only contains the number of seconds
*/

#include <iostream> 
#include "TimeCode.h"
using namespace std;

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = (hr*3600) + (min*60) + sec;
}
TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}
//TimeCode::~TimeCode(){}

void TimeCode::SetHours(unsigned int hours) {
    if (hours < 0){
        throw invalid_argument("time cannot be negative");
    }
    int hrDiff;
    hrDiff = hours - GetHours();
    t += hrDiff*3600;
}
void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes < 0){
        throw invalid_argument("time cannot be negative");
    }
    else if (minutes <= 59) {
        int minDiff;
        minDiff = minutes - GetMinutes();
        t += minDiff*60;
    } 
    else {
        throw invalid_argument("Roll over on SetMinutes " + to_string(minutes));
    }
}
void TimeCode::SetSeconds(unsigned int seconds){
    if (seconds < 0){
        throw invalid_argument("time cannot be negative");
    }
    else if (seconds <= 59){
        int secDiff;
        secDiff = seconds - GetSeconds();
        t += secDiff;
    } 
    else{
        throw invalid_argument("Roll over on SetSeconds " + to_string(seconds));
    }
}

void TimeCode::reset() {
    t = 0; // resets time
}

unsigned int TimeCode::GetHours() const {
    unsigned int hours;
    hours = t / 3600;
    return hours;
}
unsigned int TimeCode::GetMinutes() const {
    unsigned int min;
    min = (t % 3600) / 60;
    return min;
}
unsigned int TimeCode::GetSeconds() const {
    unsigned int sec;
    sec = t % 60;
    return sec;
}

//long long unsigned int TimeCode::GetTimeCodeAsSeconds() const {return t;};
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const  {
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = t % 60;
}
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long sec) {
    return (hr * 3600) + (min * 60) + sec;
}

string TimeCode::ToString() const {
    string timecode;
    timecode = to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSeconds());
    return timecode;
}

TimeCode TimeCode::operator+(const TimeCode& other) const {
    TimeCode add = TimeCode((GetHours() + other.GetHours()), (GetMinutes() + other.GetMinutes()), 
    (GetSeconds() + other.GetSeconds()));
    return add;
}

TimeCode TimeCode::operator-(const TimeCode& other) const {
    TimeCode diff = TimeCode();
    if (t < other.t){
        throw invalid_argument("Cannot produce negative time...." + to_string(t) + " < " + to_string(other.t));
    } else{
        diff.t = t - other.t;
    } return diff;
    
}

TimeCode TimeCode::operator*(double a) const {
    TimeCode mult = TimeCode();
    mult.t = t * a;
    return mult;
}

TimeCode TimeCode::operator/(double a) const {
    if (a == 0){
        throw invalid_argument("Can't divide by 0");
    } else if(a < 0){
        throw invalid_argument("Can't create negative time");
    }
    TimeCode div = TimeCode();
    div.t = t / a;
    return div;
}

bool TimeCode::operator== (const TimeCode& other) const{
    return (t == other.t);
}
bool TimeCode::operator != (const TimeCode& other) const{
    return (t != other.t);
}

bool TimeCode::operator < (const TimeCode& other) const{
    return (t < other.t);
}
bool TimeCode::operator <= (const TimeCode& other) const{
    return (t <= other.t);
}

bool TimeCode::operator > (const TimeCode& other) const{
    return (t > other.t);
}
bool TimeCode::operator >= (const TimeCode& other) const{
    return (t >= other.t);
}