// This function tried to filter noise data when the device started
//set a threshould and calculate average IBI.
//if average IBI < threshould, define it as noise data.

int filter_noise(){
  int flag = 0;
  int IBI_list[10] ;
  int IBITotal = 0;

  for(int i=0; i<=10; i++){             // seed the running total to get a realisitic BPM at startup
          IBI_list[i] = IBI;                      
  }

  for(int i=0; i<=9; i++){                // shift data in the rate array
    IBI_list[i] = IBI_list[i+1];                  // and drop the oldest IBI value 
    IBITotal += IBI_list[i];// add up the 99 oldest IBI values
    IBITotal =  IBITotal/10;
  }
  sendDataToSerial('N', IBITotal);

  if(IBITotal < 50){
    flag = 1;
    }
  //sendDataToSerial('F', flag);
  return flag;
}

