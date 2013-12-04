#define LogTimer T2 

void addToLog(string msg) {
	log_logque[log_index] = msg;
	log_index++;
}

void addToLogWithTime(string msg) {
	int sec = time1[LogTimer] * 1000;
	int min = sec/60;
	sec = sec - min*60;
	string finalMsg;
	if(sec<10) {
		sprintf(finalMsg, "%d:0%d   %s", min, sec, msg);
	}
	else {
		sprintf(finalMsg, "%d:%d   %s", min, sec, msg);
	}
	addToLog(finalMsg);
}

bool log_running = true;
int log_index = 0;
int log_written = 0;
string log_que[255];

task Logger() {
	TFileHandle file;
	TFileIOResult result;
	string fileName = "data.txt";
	int fileSize = 1*1000;  // file size in bytes (currently 1 kb)

	char CR = 0x13; // carriage return
	char LF = 0x10; // line feed

	Delete(fileName, result);
	OpenWrite(file, result, fileName, fileSize);

	while(log_running) {
		if(log_index>log_written) {
			WriteText(file, result, log_que[log_written]);
			// writes new line
			WriteByte(file, result, CR);
			WriteByte(file, result, LF); 
			log_written++;
		}
	}

	Close(file, result);
	StopTask(Logger);
}