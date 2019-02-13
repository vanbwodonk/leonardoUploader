#include<windows.h>
#include<stdio.h>

// Local Functions
int cfileexists(const char * filename);
void updatePortList(int *list);
void makeAvrdudeCommand(int Port, char *filename);

// Port list
int ports[20]; // Array of PC ports 20 is a Big number of Serial ports
int num_ports = 0;  // number of Detected ports
char cmd[1024]; // large Enough !  command Buffer

// Main
int main(int argc, char *argv[])
{
  DCB dcbSerialParams = { 0 }; // Initializing DCB structure
  HANDLE hComm;
  //BOOL   Status;
  COMMTIMEOUTS timeouts = { 0 };
  char portName[40];  
  int retval, i;

  printf("\n\n ==========================================\n");
  // Print USAGE
  if (argc < 3)
  {
    printf("leonardoUploader [PORT] [FILE.hex]\n");
    return 0;
  }

  // Get Port name
  strcpy(portName, "\\\\.\\");
  strcat(portName, argv[1]);
  if (strlen(portName) < (4+4))
  {
    printf("  Error Invaid Port %s\n", argv[1]);
    return 1;
  }

  // Get File name
  if (cfileexists(argv[2]) == 0)
  {
    printf("  Error Invaid File or Non-existing  %s\n", argv[2]);
    return 1;
  }

  // Check if Multiple ports are connected:
  updatePortList(ports);
  if (num_ports > 1)
  {
    printf("  Error multiple Ports Connected total : %s\n", num_ports);
    printf("\n  Please have only one serial Port connected for this to work");
    return 1;
  }

  // Open Port
  printf(" \n Opening Port Name: %s\n", portName);
  hComm = CreateFile( portName,                //port name
                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                      0,                            // No Sharing
                      NULL,                         // No Security
                      OPEN_EXISTING,// Open existing port only
                      0,            // Non Overlapped I/O
                      NULL);        // Null for Comm Devices

  if (hComm == INVALID_HANDLE_VALUE)
  {
      printf("Error in opening serial port\n");
      return 1;
  }

  //Configure DCB
  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
  dcbSerialParams.BaudRate = CBR_1200;  // Setting BaudRate = 1200
  dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
  dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
  dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None

  if (SetCommState(hComm, &dcbSerialParams) == FALSE)
  {
    printf(" Error in Setting Serial Port parameters\n");
    return 2;
  }

  // Configure Timeouts
  timeouts.ReadIntervalTimeout         = 50;
  timeouts.ReadTotalTimeoutConstant    = 50;
  timeouts.ReadTotalTimeoutMultiplier  = 10;
  timeouts.WriteTotalTimeoutConstant   = 50;
  timeouts.WriteTotalTimeoutMultiplier = 10;
  
  if (SetCommTimeouts(hComm, &timeouts) == FALSE)
  {
			printf("  Error in Setting Timeouts\n");
      return 3;
  }

  // Reset Condition for Leonardo 
  if (EscapeCommFunction(hComm, SETRTS) == FALSE)
  {
    printf("  Error in Setting RTS\n");
    return 4;
  }

  if (EscapeCommFunction(hComm, CLRDTR) == FALSE)
  {
    printf("  Error in Clearing DTR");
    return 5;
  }

  CloseHandle(hComm);//Closing the Serial Port

  printf("\n\n --- Reset Arduino Leonardo.... \n");

  // Delay after Reset of Port - in milliseconds
  Sleep(2000);

  // Detect new list of ports
  updatePortList(ports);

  // Issue the Avrdude command
  for (i = 0; i < num_ports; i++)
  {
    printf("\n\n Trying with port COM%d\n", ports[i]);
    makeAvrdudeCommand(ports[i], argv[2]);
    retval = system(cmd);
    if (retval == 0) break;
  }
  printf("\n\n ==========================================\n");
	return retval;
}

/*
 * Check if a file exist using fopen() function
 * return 1 if the file exist otherwise return 0
 */
int cfileexists(const char * filename)
{
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

/**
 * Find out the number of Serial ports available
 */
void updatePortList(int *list)
{
  int k = 0;
  int ctr = 0;
  char port[32];
  HANDLE hSerial;

  while(++k < 255)  //1 to 256
  {   
    sprintf(port,"\\\\.\\COM%d",k);
    hSerial = CreateFile(port, GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if(hSerial!=INVALID_HANDLE_VALUE)
    { 
      // Add port
      list[ctr] = k;
      ++ctr;
      printf("\n    > Detected port:  COM%d\n",k);
      CloseHandle(hSerial);
      // Prevent any Overflow
      if (ctr == 20)
        return;
    }
  }

  // Number of Ports avialble
  num_ports = ctr;
}

void makeAvrdudeCommand(int Port, char *filename)
{
  // Prepare Avrdude Command
  sprintf(cmd, "avrdude -pm32u4 -cavr109 -F -D -P COM%d -Uflash:w:%s", Port, filename);
}