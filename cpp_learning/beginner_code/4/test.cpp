#include<iostream>

using namespace std;

int main(void){
    float FL, FR, RL, RR;
    int r_conv[4];
    cout<<"input motors' rpm"<<endl;
    cin>>FL>>FR>>RL>>RR;
    r_conv[0] = rpm_convert(FL);
    r_conv[1] = rpm_convert(FR);
    r_conv[2] = rpm_convert(RL);
    r_conv[3] = rpm_convert(RR);
    cout<<"Their convert is"<<r_conv[0]<<r_conv[1]<<r_conv[2]<<r_conv[3];

    return 0;
}

int rpm_convert(float rpm){
    float y1; //负极限占空比
    float y2; //静止对应占空比下限
    float y3; //静止对应占空比上限
    float y4; //正极限占空比
    float k1, k2; //斜率
    y1 = 1050.0;
    y2 = 1413.0;
    y3 = 1453.0;
    y4 = 1975.0;
    float MAX_SPEED = 4000.0;
    float rpm_conv;
    if(rpm > 0) {
        rpm_conv = (y4 - y3)/MAX_SPEED + y3;
    }
    else if(rpm < 0) {
        rpm_conv = (y2 - y1)/MAX_SPEED + y1;
    }
    else rpm_conv = (y2 + y3)/2;

    return int(rpm_conv);
}