
#ifndef _CapSensor_
#define _CapSensor_

const int led[] = {21, 3, 18, 22, 23};
const int wire[] = {13, 12, 14, 27, 33, 32, 15, 2};
int cap[] = {30, 38, 40, 30, 30, 35, 35, 35};

void readCap(uint8_t output[]){
  int media[] = {0,0,0,0,0,0,0,0,0,0};
  for(int i = 0; i < 50; i++){
    for (int j=0; j < 5; j++){
      media[j] += touchRead(wire[j]);
    }
  }
  for(int k =0; k < 8; k++){
    media[k] = media[k] / 50;
    if(media[k] < cap[k]){
      output[k] = 1;
    }else{
      output[k] = 0;
    }
  }
}

#endif
