 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/ipc.h>
 #include <string.h>
 #include <sys/msg.h>
 
 struct msgbuf {
               long mtype;       /* message type, must be > 0 */
               char mtext[100];    /* message data */
};

 
 int main(){
   key_t key=ftok("/home/ubuntu/environment/key.txt", 7);
   int mailbox=msgget(key, IPC_CREAT|0666);
   struct msgbuf m;
   int value=msgrcv(mailbox, &m, sizeof(struct msgbuf), 0, IPC_NOWAIT);
   if(value==-1){
    printf("there was no message with that type\n");
   }else{
    printf("Read message: %s\n", m.mtext);
   }
 }