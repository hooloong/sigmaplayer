#ifndef __UTILS_SOCKET__
#define __UTILS_SOCKET__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct{
	unsigned int  hdr_len;
 	unsigned char * hdr;
	unsigned int  data_len;//payload
	unsigned char * data;
	unsigned int  ret_len;  
	unsigned char * ret;  //filled by  socket
}packet;

#pragma pack(push)  
#pragma pack(1)
typedef struct CALLBACK_PARAM {
	unsigned int type;
	unsigned int inst;
	unsigned int size;
}cb_param;
#pragma pack(pop)


typedef int (*Observer)(void * inst,int event,void * data_cb);

int socket_connect(const char *host_name, int port, int dtimeout);
int socket_send(packet * pack);
void socket_setListener(Observer ob);
void socket_disconnect(void);

void  client_server_start(void);
void  client_server_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
