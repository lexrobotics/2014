#define LogTimer T2

bool log_running = true;
int log_index = 0;
int log_written = 0;
string log_que[255];

void addToLog(const string &msg) {
	writeDebugStreamLine(msg);
	log_que[log_index] = msg;
	log_index++;
}

void addToLogWithTime(const string &msg) {
	string debug;
	int sec = time1[LogTimer]/1000;
	int min = sec/60;
	sec = sec - min*60;
	writeDebugStreamLine(msg);
	string finalMsg;
	if(sec<10) {
		sprintf(finalMsg, "%d:0%d %s", min, sec, msg);
	}
	else {
		sprintf(finalMsg, "%d:%d %s", min, sec, msg);
	}

	addToLog(finalMsg);
}

void stopLogger() {
	log_running = false;
}

task Logger() {
	TFileHandle file;
	TFileIOResult result;
	string fileName = "data.txt";
	int fileSize = 1*1000;  // file size in bytes (currently 1 kb)
  char CR = 0x0d;   // define CR (carriage return)
  char LF = 0x0a;   // define LF (line feed)

	CloseAllHandles(result);

	Delete(fileName, result);
	OpenWrite(file, result, fileName, fileSize);

	while(log_running) {
		if(log_index>log_written) {
			WriteText(file, result, log_que[log_written]);
		//	writeDebugStreamLine(log_que[log_written]);
			WriteByte(file, result, CR);
			WriteByte(file, result, LF);

			log_written++;
		}
	}
	WriteDebugStream("Closing file");
	Close(file, result);
	StopTask(Logger);
}
