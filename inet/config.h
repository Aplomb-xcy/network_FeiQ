#pragma once
#include<string.h>

#define _DEF_RECVBUF_SIZE           (4096)
#define _DEF_HOST_NAME_SIZE         (60)
#define _DEF_CONTENT_SIZE           (1024)
#define SEND_HOST (24465)
#define SEND_IP ("192.168.0.222")

#define _DEF_PROTOCOL_BASE          (1000)
#define _DEF_UDP_ONLINE_RQ          (_DEF_PROTOCOL_BASE+1)
#define _DEF_UDP_ONLINE_RS          (_DEF_PROTOCOL_BASE+2)
#define _DEF_UDP_CHAT_RQ            (_DEF_PROTOCOL_BASE+3)
#define _DEF_UDP_OFFLINE_RQ         (_DEF_PROTOCOL_BASE+4)


//定义请求结构体
//上线请求，上线回复

struct STRU_UDP_ONLINE{
    STRU_UDP_ONLINE():type(_DEF_UDP_ONLINE_RQ){
        memset(name,0,_DEF_HOST_NAME_SIZE);
    }
    int type;

    char name[_DEF_HOST_NAME_SIZE];
};

//聊天请求
struct STRU_UDP_CHAT_RQ{
    STRU_UDP_CHAT_RQ():type(_DEF_UDP_ONLINE_RQ){
        memset(content,0,_DEF_CONTENT_SIZE);
    }
    int type;
    char content[_DEF_CONTENT_SIZE];
};

struct STRU_UDP_OFFLINE_RQ{
    STRU_UDP_OFFLINE_RQ():type(_DEF_UDP_OFFLINE_RQ){}
    int type;
};
