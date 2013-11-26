#include "drivers/hitechnic-accelerometer.h"

int size(int *arr) {
	return sizeof(arr)/sizeof(int);
}

int TIME_THRESH = 4;
const int ARRAY_SIZE = 25;
int THRESH = 15;

bool stationary=false;

void addData(int n, int *data) {
	for(int i=0; i<size(data)-1; i++)
		data[i] = data[i+1];
	data[size(data)-1] = n;
}

int calculateError(int *data) {
	int sum = 0;
	for(int i=0; i<size(data); i++)
		sum+=abs(data[i+1]-data[i]);

	return sum/size(data);
}

task ReadAccel() {
	int data[ARRAY_SIZE];
	int count = 0;

  int _x_axis = 0;
  int _y_axis = 0;
  int _z_axis = 0;

	for(int i=0; i<size(data); i++) {
		HTACreadAllAxes(HTAC, _x_axis, _y_axis, _z_axis);
		data[i] = _x_axis;
	}

  while(true) {
    if (!HTACreadAllAxes(HTAC, _x_axis, _y_axis, _z_axis)) {
      nxtDisplayTextLine(4, "ERROR!!");
      wait1Msec(2000);
      StopAllTasks();
    }

    addData(_x_axis, data);
    int error = calculateError(data);
    if(error>THRESH)
    	count = 0;
   	else
     	count++;

    stationary = (count>TIME_THRESH);

	 	nxtDisplayTextLine(2, "%d", count);

    wait1Msec(100);
  }
}
