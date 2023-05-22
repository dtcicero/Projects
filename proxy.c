/* CMPS2300 Proxy Lab
 * proxy - a caching, concurrent HTTP proxy server
 * 
 * Put your name and Tulane email address here
 * Daniel Cicero, dcicero@tulane.edu */

#include <stdio.h>
#include "csapp.h"
#include <string.h>
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *conn_hdr = "Connection: close\r\n";
static const char *prox_hdr = "Proxy-Connection: close\r\n";
static const char *host_hdr_format = "Host: %s\r\n";
static const char *requestlint_hdr_format = "GET %s HTTP/1.0\r\n";
static const char *endof_hdr = "\r\n";


static const char *connection_key = "Connection";
static const char *user_agent_key= "User-Agent";
static const char *proxy_connection_key = "Proxy-Connection";
static const char *host_key = "Host";

/* Struct to hold values of HTTP request */
/* typedef struct struct_request{
   short valid;
   char url[MAXLINE];
   char hostname[MAXLINE];
   char hostheader[MAXLINE];
   char path[MAXLINE];
   char serverport[6];
   char otherheaders[MAXLINE];
   char method[5];
    } Request; */
    
/* struct cache_block{
   char request[MAXLINE];
   char content[MAX_OBJECT_SIZE];
   size_t size;
   struct cache_block *next;
   struct cache_block *head = NULL;
    } ; */

/* Function initializations */
void proxy(int connfd);
void *thread(void *vargp);
/* You won't lose style points for including this long line in your code */


int main(int argc, char **argv)
{
    int listenfd, *connfdp;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE] = {0}, client_port[MAXLINE] = {0};
    pthread_t tid;
   

    if (argc != 2) {
      fprintf(stderr, "usage: %s <port>\n", argv[0]);
      exit(1);
   }
    listenfd = Open_listenfd(argv[1]);
    while (1) {
       clientlen = sizeof(struct sockaddr_storage);
       connfdp = Malloc(sizeof(int));
       *connfdp = Accept(listenfd, (SA *)&clientaddr, &clientlen); /* Open socket with server */
       Pthread_create(&tid, NULL, thread, connfdp); /* Create thread to execute proxy() without stopping loop*/
    }
    return 0;
}
/* Creates thread to call and execute proxy(), then close*/
void *thread(void *vargp) {
   int connfd = *((int *)vargp); 
   Pthread_detach(pthread_self());
   Free(vargp);
   proxy(connfd);
   Close(connfd);
   return NULL;

}

/* Initializes values in request struct to necessary value */ /*
void initialize_request(Request *req) {
   strcat(req->hostname, ""); 
   strcat(req->path, "/");
   strcat(req->hostheader, "Host: ");   
   strcpy(req->serverport, "80");
   req->valid= 1;
   strcpy(req->method, "GET");
   strcpy(req->otherheaders, user_agent_hdr);
   return;
}
*/
void proxy(int connfd){
 char buf[MAXLINE], method[MAXLINE], url[MAXLINE], version[MAXLINE];
 char hostname[MAXLINE], path[MAXLINE];
 int port;
 int end_serverfd;
 char endserver_http_header[MAXLINE];


 rio_t rio, server_rio;
/*Extracts method, url, version from buffer*/
 Rio_readinitb(&rio, connfd);
 Rio_readlineb(&rio, buf, MAXLINE);
 sscanf(buf, "%s %s %s", method, url, version);



 if (strcasecmp(method, "GET")){
   printf("Proxy does not implement the method");
   return;
 }
 // parse url for hostname, path and port and build request for server
 parse_url(url,hostname,path, &port);//Parses url and extracts hostname, path, port
 build_http_header(endserver_http_header, hostname, path, port, &rio);
 

/*Establishes connection to specified server. Alerts user if connection failed*/
 end_serverfd = connect_endServer(hostname, port, endserver_http_header);
 if (end_serverfd < 0){
   printf("connection failed\n");
   return;
 }

 Rio_readinitb(&server_rio, end_serverfd);
 Rio_writen(end_serverfd, endserver_http_header, strlen(endserver_http_header));
  size_t n;
 while((n = Rio_readlineb(&server_rio, buf, MAXLINE)) != 0){
     printf("server recieved %ld bytes\n", n);
     Rio_writen(connfd, buf, n);// Forwards server response to client (via connfd)
 }
 close(end_serverfd);
}


/*Connects to server. Returns fd for socket created*/
inline int connect_endServer(char *hostname,int port,char *http_header){
   char portStr[100];
   sprintf(portStr,"%d",port);
   return Open_clientfd(hostname,portStr);
}

// Parses url to extract hostname, serverport, and path into distinct variables

void parse_url(char *url, char*hostname, char*path, int *port)
{
   *port = 80; 
   char* start = strstr(url, "//");

   if (start != NULL) {
       start += 2;
   }
   else {
       start = url;
   }
   char*end = strstr(start, ":");

   if(end != NULL){
       *end = '\0';
       sscanf(start, "%s", hostname);//stores hostname
       sscanf(end+1, "%d%s", port, path);// stores port and path 
   }
   else{
       end = strstr(start, "/");
       if(end != NULL)/*if a colon, replaced with '\0'*/
       {
           *end = '\0';
           sscanf(start, "%s", hostname);
           *end = '/';
           sscanf(end, "%s", path);
       }
       else{
           sscanf(start, "%s",hostname);/* If no forward slash, entire string is considered the hostname */
       }
   }
   return;
}


/*
void add_to_cache(cache_block *newblock) {
   if (c->head == NULL) {
      c->head = c;
      c->next = NULL;
   }
   else if (c->next == NULL) {
      c->next = c;
   }
   else {
      c->head = c->next;
      c->next = c;
   }
} */

void build_http_header(char *http_header,char *hostname,char *path,int port,rio_t *client_rio)
{
   char buf[MAXLINE],request_hdr[MAXLINE],other_hdr[MAXLINE],host_hdr[MAXLINE];
  
   
   sprintf(request_hdr,requestlint_hdr_format,path);
  
   while(Rio_readlineb(client_rio,buf,MAXLINE)>0)//parses client request
   {
       if(strcmp(buf,endof_hdr)==0) break;
       if(!strncasecmp(buf,host_key,strlen(host_key)))
       {
           strcpy(host_hdr,buf);
           continue;
       }


       if(!strncasecmp(buf,connection_key,strlen(connection_key))
               &&!strncasecmp(buf,proxy_connection_key,strlen(proxy_connection_key))
               &&!strncasecmp(buf,user_agent_key,strlen(user_agent_key)))
       {
           strcat(other_hdr,buf);//Appends the source string stored in buf to the the destination string
       }
   }
   if(strlen(host_hdr)==0)
   {
       sprintf(host_hdr,host_hdr_format,hostname);
   }
   /*Stores the header values */
   sprintf(http_header,"%s%s%s%s%s%s%s",
           request_hdr,
           host_hdr,
           conn_hdr,
           prox_hdr,
           user_agent_hdr,
           other_hdr,
           endof_hdr);


   return ;
}

