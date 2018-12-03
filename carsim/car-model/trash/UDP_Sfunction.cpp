/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 *  -------------------------------------------------------------------------
 *  | See matlabroot/simulink/src/sfuntmpl_doc.c for a more detailed template |
 *  -------------------------------------------------------------------------
 *
 * Copyright 1990-2002 The MathWorks, Inc.
 * $Revision: 1.27.4.2 $
 */


/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  UDP_Sfunction
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"
#include <winsock2.h>  
//#include "mex.h" 
#include "UDP_Sfunction.h"

#pragma comment(lib,"ws2_32.lib")  

real_T yTemp[7];



/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 * See matlabroot/simulink/src/sfuntmpl_doc.c for more details.
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    /* See sfuntmpl_doc.c for more details on the macros below */

    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 28);
	ssSetInputPortRequiredContiguous(S, 0, true); 
	ssSetInputPortDirectFeedThrough(S, 0, 1);
	
    //ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
     */
    //ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1)) return;
    
	ssSetOutputPortWidth(S, 0, 7);
    

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);
	
	ssSetNumPWork(S, 3);
	
	yTemp[0]=0; //方向盘角度
	yTemp[1]=0; //节气门开度
	yTemp[2]=0; //主缸压力
	yTemp[3]=0; //挡位
    yTemp[4]=0; //speed error
    yTemp[5]=0; //lateral error
    yTemp[6]=0; //target speed
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
  }
#endif /* MDL_INITIALIZE_CONDITIONS */

void UseFun_StartSock(SimStruct *S)
{
    int iResult;
    WSADATA wsaData;


    SOCKET *pSendSocket = new SOCKET;
    *pSendSocket = INVALID_SOCKET;

    sockaddr_in *pRecvAddr = new sockaddr_in;

    unsigned short Port = 8888;
   
    printf("Start socket communication, please wait...\n");

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return ;
    }

    //---------------------------------------------
    // Create a socket for sending data
    *pSendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (*pSendSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return ;
    }
	
	int recvbuf = 1;
    setsockopt(*pSendSocket,SOL_SOCKET,SO_RCVBUF,(char*)&recvbuf,sizeof(int));
    //设置为非阻塞模式  
    int imode=1;  
    int rev=ioctlsocket(*pSendSocket,FIONBIO,(u_long *)&imode);  
    if(rev == SOCKET_ERROR)  
    {  
        printf("ioctlsocket failed!");  
        closesocket(*pSendSocket);  
        WSACleanup();  
        return;  
    }  

    //---------------------------------------------
    // Set up the RecvAddr structure with the IP address of
    // the receiver (in this example case "192.168.1.1")
    // and the specified port number.
    pRecvAddr->sin_family = AF_INET;
    pRecvAddr->sin_port = htons(Port);
    pRecvAddr->sin_addr.s_addr = INADDR_ANY;
	
	if (bind(*pSendSocket, (SOCKADDR *)pRecvAddr, sizeof(*pRecvAddr)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(*pSendSocket);
		return;
	}

    ssGetPWork(S)[1] = pSendSocket;
    ssGetPWork(S)[2] = pRecvAddr;
}


int UseFun_RWData(SimStruct *S, const float *data, int DataNumSend, float *dataReceive, int DataNumReceive)
{
	
	int iResult;

	char SendBuf[1024] = { '\0' };
	int BufLen = 1024;

	SOCKET *pSendSocket = static_cast<SOCKET *>(ssGetPWork(S)[1]);
	sockaddr_in *pRecvAddr = static_cast<sockaddr_in *>(ssGetPWork(S)[2]);
	
	if (*pSendSocket == SOCKET_ERROR) {
		printf("SOCKET_ERROR error: %d\n", WSAGetLastError());
		closesocket(*pSendSocket);
		WSACleanup();
		return -1;
	}

	fd_set         fdread;
    fd_set         fdwrite;;                     // 描述符集 这个将用来测试有没有一个可用的连接
	
	struct timeval timeout;
	timeout.tv_sec = 0;               
	timeout.tv_usec = 0;              //timeout设置为0，可以理解为非阻塞

	FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
	FD_SET(*pSendSocket, &fdread); //把sock放入要测试的描述符集
	FD_SET(*pSendSocket, &fdwrite); //把sock放入要测试的描述符集
	

	//printf("%d\n",SelectRcv);
	//---------------------------------------------
	// Receive a datagram to the receiver
	
	SOCKADDR_IN remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	int manner = 1; //传输方式，1：字符串，2：浮点标准

    int SelectRcv = select(*pSendSocket+1, &fdread, 0, NULL, &timeout); //检查该套接字是否可读
	
	if (SelectRcv <= 0)
	{
		//printf("监听读失败\n");
		return -1;
	}
    
    	if (FD_ISSET(*pSendSocket, &fdread))
	{	
		char recvData[1024];
		int ret = recvfrom(*pSendSocket, recvData, 1024, 0, (SOCKADDR *)pRecvAddr, &nAddrLen);
		
		if (ret > 0)
		{
			recvData[ret] = 0x00;
			//解析接收到的数据
			size_t len = strlen(recvData);
			//printf("%s\n",recvData);
			if (manner == 1)
			{
				char temp[64];
				int j = 0;
				int count = 0;

				for (int i = 0; i < len; ++i)
				{
					if (recvData[i] == '/')
					{
						temp[j] = 0x00;

						dataReceive[count] = atof(temp);

						++count;
						j = 0;

						if (count == DataNumReceive)
						{
							break;
						}

						continue;
					}
					else if (i == len - 1)
					{
						//最后一位
						temp[j] = recvData[i];

						j++;
						temp[j] = '\0';

						dataReceive[count] = atof(temp);

						break;
					}

					temp[j] = recvData[i];
					j++;
				}
			}
			else
			{
				for (int i = 0; i < DataNumReceive; ++i)
				{
					if (4 * i + 4 > len)
					{
						break;
					}

					memcpy(dataReceive + 4 * i, recvData + 4 * i, 4);
				}
			}
		}
	}

    int SelectRcv1 = select(*pSendSocket+1, 0, &fdwrite, NULL, &timeout); //检查该套接字是否可读
    
	if(SelectRcv1<=0)
	{
		printf("监听写失败\n");
		return -1;	
	}

	if (FD_ISSET(*pSendSocket, &fdwrite)) //yy mark
	{

		//发送数据	
		char sendData[2048];
		sendData[0]=0x00;

		if (manner == 1)
		{
			int ValidateBufLen = 0;
			for (int i = 0; i < DataNumSend; i++)
			{
				ValidateBufLen = strlen(sendData);
				sprintf(sendData + ValidateBufLen, "%.3f/", data[i]);
			}
		}
		else
		{
			for (int i = 0; i < DataNumSend; i++)
			{
				memcpy(sendData + 4 * i, data + 4 * i, 4);
			}

			sendData[4 * DataNumSend] = 0x00;
		}
		
		printf("%s\n",sendData);

		sendto(*pSendSocket, sendData, strlen(sendData), 0, (SOCKADDR *)pRecvAddr, nAddrLen);
	}
	
    
	return 1;
}
void UseFun_CloseSock(SimStruct *S)
{
    SOCKET *pSendSocket    = static_cast<SOCKET *>(ssGetPWork(S)[1]);
    sockaddr_in *pRecvAddr = static_cast<sockaddr_in *>(ssGetPWork(S)[2]);

    //---------------------------------------------
    // When the application is finished sending, close the socket.
    printf("Finished socket communication, Closing socket.\n");

    if (closesocket(*pSendSocket) == SOCKET_ERROR)
    {
        printf("closesocket failed with error: %d\n", WSAGetLastError());
    }
    //---------------------------------------------
    // Clean up and quit.

    WSACleanup();

    delete pSendSocket;
    pSendSocket = NULL;

    delete pRecvAddr;
    pRecvAddr = NULL;
}


#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
		DoubleAdder *da  = new DoubleAdder();
		ssGetPWork(S)[0] = da;

		UseFun_StartSock(S);
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
	// Retrieve C++ object from the pointers vector
    //DoubleAdder *da = static_cast<DoubleAdder *>(ssGetPWork(S)[0]);
    
    // Get data addresses of I/O
	const real_T *u = (const real_T*) ssGetInputPortSignal(S,0);
	real_T       *y = (real_T *)ssGetOutputPortSignal(S,0);

    int InputNum = ssGetInputPortWidth(S, 0);
	int OutputNum = ssGetOutputPortWidth(S, 0);
    
	float *data=(float*)malloc(InputNum*sizeof(float));
	
	for(int i=0;i<InputNum;i++)
    {
        data[i] = (float)u[i];
    }
	
	float *dataReceive=(float*)malloc(OutputNum*sizeof(float));
	
	if(UseFun_RWData(S, data, InputNum, dataReceive, OutputNum)!=-1)
	{
		for(int i=0;i<OutputNum;i++)
		{
			y[i] = (real_T)dataReceive[i];
			yTemp[i]=y[i];
		}	
	}
	else
	{
		for(int i=0;i<OutputNum;i++)
		{
			y[i]=yTemp[i];
		}
	}
	
    free(data);
	free(dataReceive);
}



#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
	// Retrieve and destroy C++ object
    DoubleAdder *da = static_cast<DoubleAdder *>(ssGetPWork(S)[0]);
    delete da;

    UseFun_CloseSock(S);
}


/*======================================================*
 * See sfuntmpl_doc.c for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
