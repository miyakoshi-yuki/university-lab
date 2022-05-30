#include "pattern_generator.h"
#include <Arduino.h>
// #include <math.h>
// #include <stdio.h>

const float gravity = 9.8; // m/s2
const float delta_time = 0.01; // s
const float centroid_height = 0.5; // m
const float step_time = 0.5;
const float ref_step_data[] = {0.05, 0.05, 0.0};
float centroid_position[] = {0, 0.04};
float centroid_velocity[] = {0,0};
float step_position[] = {0, 0.05};
float ref_step_position[] = {0, 0.05};


int step_count = 0;
float centroid_acceleration[] = {0,0};
float current_ref_step_data[] = {0,0,0};
float current_ref_step_angle = 0;
float current_ref_step_size[]={0,0};
float next_ref_step_data[]={0,0,0};
float next_ref_step_size[]={0,0};
float next_ref_step_angle = 0;
float Tc = 0;
float C = 0;
float S = 0;
float h_xy[] = {0,0};
float h_v_xy[] = {0,0};
float next_target_position[] = {0,0};
float next_target_velocity[] = {0,0};
float D = 0;

float xyi[] = {0,0};
float vxyi[] = {0,0};
float xyd[] = {0,0};
float vxyd[] = {0,0};
float next_step_position[] = {0,0};

// void setup(){
//     Serial.begin(9600);
// }

// void loop(void){
// Serial.print("積分回数step_time / delta_time=");
// Serial.println((int)(step_time / delta_time));
//    for(int i = 0;i <10; i++){
//        Serial.println("%d歩目\n",i);
//        for(int j = 0;j < 2; j++)Serial.println("実際の着地点step_position[%d]=%lfcm\n",j,step_position[j]*100);
//        for(int j = 0;j < 2; j++)Serial.println("現在重心centroid_position[%d]=%lfcm\n",j,centroid_position[j]*100);
//        for(int j = 0;j < 2; j++)Serial.println("1歩後の重心座標 next_target_position[%d]=%lfcm\n",j,next_target_position[j]*100);
//        Serial.println("\n");
//        spin();
//     }
// }

void spin(void){
        //線形倒立振子の方程式を積分して1歩分の重心運動を求める 
        for(int j = 0;j < (int)(step_time / delta_time); j++){
            for(int k = 0;k < 2; k++)centroid_acceleration[k] = gravity / centroid_height * (centroid_position[k] - step_position[k]);
            for(int k = 0;k < 2; k++)centroid_velocity[k] += centroid_acceleration[k] * delta_time;
            for(int k = 0;k < 2; k++)centroid_position[k] += centroid_velocity[k] * delta_time;
        }
        step_count += 1; // 1歩更新

        //次の目標着地点を求める
        for(int j = 0;j < 3; j++){
            current_ref_step_data[j] = ref_step_data[j];
        }
        current_ref_step_angle = current_ref_step_data[2];
        current_ref_step_size[0] = current_ref_step_data[0] * cos(current_ref_step_angle) - current_ref_step_data[1] * sin(current_ref_step_angle);
        current_ref_step_size[1] = current_ref_step_data[0] * sin(current_ref_step_angle) + current_ref_step_data[1] * cos(current_ref_step_angle);
        for(int j = 0;j < 2; j++)ref_step_position[j] = ref_step_position[j] + current_ref_step_size[j];

        // 次の1歩行周期後の重心座標と重心速度の目標値を求める
        for(int j = 0;j < 3; j++)next_ref_step_data[j] = ref_step_data[j];
        next_ref_step_angle = next_ref_step_data[2];
        next_ref_step_size[0] = next_ref_step_data[0] * cos(next_ref_step_angle) - next_ref_step_data[1] * sin(next_ref_step_angle);
        next_ref_step_size[1] = next_ref_step_data[0] * sin(next_ref_step_angle) + next_ref_step_data[1] * cos(next_ref_step_angle);

        Tc = sqrt(centroid_height / gravity);
        C = cosh(step_time / Tc);
        S = sinh(step_time / Tc);

        for(int j = 0;j < 2; j++)h_xy[j] = next_ref_step_size[j] / 2;
        h_v_xy[0] = (C + 1) / (Tc * S) * h_xy[0];
        h_v_xy[1] = (C - 1) / (Tc * S) * h_xy[1];
        for(int j = 0;j < 2; j++)next_target_position[j] = ref_step_position[j] + h_xy[j];
        for(int j = 0;j < 2; j++)next_target_velocity[j] = h_v_xy[j];

        //次の修正した着地点を求める
        D = 10 * pow((C - 1),2.0) + 1 * pow((S / Tc),2.0);

        for(int j = 0;j < 2; j++)xyi[j] = centroid_position[j];
        for(int j = 0;j < 2; j++)vxyi[j] = centroid_velocity[j];
        for(int j = 0;j < 2; j++)xyd[j] = next_target_position[j];
        for(int j = 0;j < 2; j++)vxyd[j] = next_target_velocity[j];
        for(int j = 0;j < 2; j++)next_step_position[j] = -10 * (C - 1) / D * (xyd[j] - C * xyi[j] - Tc * S * vxyi[j]) - 1 * S / (Tc * D) * (vxyd[j] - S / Tc * xyi[j] - C * vxyi[j]);
        for(int j = 0;j < 2; j++)step_position[j] = next_step_position[j];
}
