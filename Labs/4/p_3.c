#include <stdio.h>
float function(float cal, float phy, float lab){
float sum= (cal*3)+(phy*2)+(lab*1);
float average = sum/6;
return average;
}
int main(void){
float cal=18 , phy=17 , lab=19;
printf("average= %f\n",function(cal , phy ,lab));
return 0;}
