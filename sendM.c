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
   strcpy(m.mtext, "1");
   m.mtype=2;
   msgsnd(mailbox, &m, sizeof(struct msgbuf), 0);
 }