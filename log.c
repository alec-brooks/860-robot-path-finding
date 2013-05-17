
TFileHandle logFile;
  TFileIOResult result;

string term = "\r\n";

void openLogFile(void) {
  string logFileName = "log.txt";
  int size = 10_000;
  OpenWrite(logFile, result, logFileName, size);
}

void logInt(int i) {
  string in = "";
  StringFormat(in, "%i ", i);
  WriteText(logFile, result, in);
}

void logChar(char c) {
 WriteByte(logFile, result, c);
}

void logLine(string text) {
   WriteText(logFile, result, text);
   WriteText(logFile, result, term);
}

void closeLogFile(void) {
  Close(logFile, result);
}
