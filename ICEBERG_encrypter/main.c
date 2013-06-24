#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>


typedef struct mlistnode *pmlist;

typedef struct mlistnode{
    char *key;
    char *l;
    int metritis;
	pmlist next;                      //deiktis se epomeno komvo ths listas
}mlistnode;

void createl(pmlist *listaptr)
{
     *listaptr = NULL;
}

void insert_node(pmlist *listaptr,char* ikey,char* length,int i)
{
   pmlist temp;
   pmlist temp2;
   if(*listaptr == NULL)  //periptosh adeias listas
   {
      temp = (pmlist)malloc(sizeof(struct mlistnode));
      if(temp==NULL)
      {
         fprintf(stderr,"Problem allocating new space.Program terminating..");
         exit(12);
      }
      temp->key = malloc((strlen(ikey)+1)*sizeof(char));
      temp->key = strcpy(temp->key,ikey);
      temp->l = malloc((strlen(length)+1)*sizeof(char));
      temp->l = strcpy(temp->l,length);
      temp->metritis=i;
      temp->next = NULL;
      *listaptr = temp;
   }
   else if(*listaptr != NULL) //periptosi p yparxei hdh enas komvos
   {
      temp2 = *listaptr;
      while(temp2->next != NULL)
      {
         temp2 = temp2->next;
      }
      temp = (pmlist)malloc(sizeof(struct mlistnode));
      if(temp==NULL)
      {
         fprintf(stderr,"Problem allocating new space.Program terminating..");
         exit(12);
      }
      temp->key = malloc((strlen(ikey)+1)*sizeof(char));
      temp->key = strcpy(temp->key,ikey);
      temp->l = malloc((strlen(length)+1)*sizeof(char));
      temp->l = strcpy(temp->l,length);
      temp->metritis=i;
      temp->next = NULL;
      temp2->next = temp;
   }
}

void complete_delete(pmlist *listaptr)
{
   pmlist temp;
   pmlist temp2;
   
   if(*listaptr == NULL)
      printf("List is empty\n");
   else
   {
      temp = *listaptr;
      while(temp != NULL)     //olikh diagrafh ths listas
      {
         temp2 = temp;
         temp = temp->next;
         free(temp2->key);
         free(temp2->l);
         free(temp2);
      }
   }
}
   
pmlist search(pmlist *listaptr,int counter) //epistrefei ekeino ton komvo pou ypodeiniei o counter
{
   pmlist temp;
   int i=0;
   
   if(*listaptr == NULL)
      printf("List is empty\n");
   else
   {
      temp = *listaptr;
      while(temp != NULL)
      {
         i++;
         if(counter != i)
            temp = temp->next;
         else 
            return temp;         
      }
   }
}

int return_lis(pmlist *listaptr,int counter)
{
   pmlist temp;
   int ep;
   int i=0;
   temp = *listaptr;
   
   while(temp!=NULL)
   {
      i++;
      if(counter != i)
         temp = temp->next;
      else 
      {
          ep= atoi(temp->l);
          return ep;
      }                
   }  
}   

void print(pmlist listaptr)
{
   pmlist temp;
   temp=listaptr;
   while(temp!=NULL)
   {
      printf("%s\n",temp->key);
      printf("%s\n",temp->l);
      printf("%d\n",temp->metritis);
      temp = temp->next;
   }
}

int sizel(pmlist *listaptr)
{
   pmlist temp;
   int size=0;
   
   temp = *listaptr;
   while(temp != NULL)
   {
        size++;          
        temp = temp->next;              //move to next node(if present)
   }  
    return size; 
}


main(int argc,char **argv)
{
   FILE *fout,*fcon;
   int N,workers,lcounter=0,i,*pids,*succesful_pids,prevpid,status,kidcounter=0,gl,offset1,*array,size,j=0,rw,l=0,k,p,flag;
   char c='k',buffer[1024],buffer1[33],buffer2[128],prp[16],*gkey,length[32],offset[32],Ni[32];
   char new_argv[3][50];
   pmlist lista,temp;
   
   if(argc != 8)
   {
      fprintf(stderr,"Usage: ./progname [-e/-d] -i input_file -o output_file -c configuration_file\n");
      exit(EXIT_FAILURE);
   }
   
   if(strcmp(argv[2],"-i") == 0 && strcmp(argv[4],"-o") == 0 && strcmp(argv[6],"-c") == 0)//new_argv -> input,output,configuration
   {
     
      strcpy(new_argv[0],argv[3]);
      strcpy(new_argv[1],argv[5]);      
      strcpy(new_argv[2],argv[7]);
   }
   if(strcmp(argv[2],"-i") == 0 && strcmp(argv[4],"-c") == 0 && strcmp(argv[6],"-o") == 0)
   {
      strcpy(new_argv[0],argv[3]);      
      strcpy(new_argv[1],argv[7]);
      strcpy(new_argv[2],argv[5]);
   }
   if(strcmp(argv[2],"-o") == 0 && strcmp(argv[4],"-i") == 0 && strcmp(argv[6],"-c") == 0)
   {
      strcpy(new_argv[0],argv[5]);
      strcpy(new_argv[1],argv[3]);
      strcpy(new_argv[2],argv[7]);
   }
   if(strcmp(argv[2],"-o") == 0 && strcmp(argv[4],"-c") == 0 && strcmp(argv[6],"-i") == 0)
   {
      strcpy(new_argv[0],argv[7]);
      strcpy(new_argv[1],argv[3]);
      strcpy(new_argv[2],argv[5]);
   }
   if(strcmp(argv[2],"-c") == 0 && strcmp(argv[4],"-i") == 0 && strcmp(argv[6],"-o") == 0)
   {
      strcpy(new_argv[0],argv[5]);
      strcpy(new_argv[1],argv[7]);
      strcpy(new_argv[2],argv[3]);
   }
   if(strcmp(argv[2],"-c") == 0 && strcmp(argv[4],"-o") == 0 && strcmp(argv[6],"-i") == 0)
   {
      strcpy(new_argv[0],argv[7]);
      strcpy(new_argv[1],argv[5]);
      strcpy(new_argv[2],argv[3]);
   }
    createl(&lista);                          //dhmiourgia tis listas  
    
    fout = fopen(new_argv[1]/*"output.txt"*/,"w");
    if(fout == NULL)
    {
       fprintf(stderr,"error opening output file for writing!\n");
       exit(EXIT_FAILURE);
    }
   
    fcon = fopen(new_argv[2]/*"configuration.txt"*/,"r");
    if(fcon == NULL)
    {
       fprintf(stderr,"error opening configuration file!\n");
       exit(EXIT_FAILURE);
    }
    
    fscanf(fcon,"%d",&N);
    
    if(N % 2 != 0 || N <= 2)
    {
       printf("Enter correct N.Must be even number and >2\n");
       exit(-1);
    }
   while(fgets(buffer,1024,fcon) != NULL) //apothikeysi stin lista ta dedomena gia kathe ergati(kleidi,l)
   {
       fscanf(fcon,"%s",buffer1);      
       fscanf(fcon,"%s",buffer2);
       insert_node(&lista,buffer1,buffer2,++lcounter);
   }
   workers = lcounter;
   size = sizel(&lista);
   array = malloc(size*sizeof(int));
   for(i=1;i<=size;i++)
   {
      array[i-1] = return_lis(&lista,i);
      j = j + array[i-1];
   }
   free(array);    
   for(i=0;i<j*8;i++)
      fputc((int)c,fout);
   rewind(fout);
   
   pids=malloc(workers*sizeof(int));
   for(i=0;i<workers;i++)
   {  
      if((pids[i] = fork()) == -1)
      {
         perror("fork");
         exit(EXIT_FAILURE);
      }
      if(i==0)
         offset1 = 0;
      else
      {
         temp = search(&lista,kidcounter);                                   //psaksimo stin lista gia na vroume to katallilokey kai li
         offset1 = offset1 + atoi(temp->l)*8;
      }
      if(i==0)
         prevpid =0;
      else
         prevpid = pids[i-1];
      kidcounter++;
      if(pids[i] == 0)              //child process
      {  
         temp = search(&lista,kidcounter);                                   //psaksimo stin lista gia na vroume to katallilokey kai li
         gkey = malloc((strlen(temp->key)+1)*sizeof(char));
         strcpy(gkey,temp->key);
         gl = atoi(temp->l);
         sprintf(length,"%d",gl);
         sprintf(offset,"%d",offset1);
         sprintf(prp,"%d",prevpid);
         sprintf(Ni,"%d",N);
         execl("/home/users/std07077/OS2/iceberg","./iceberg",new_argv[0],offset,length,new_argv[1],prp,gkey,Ni,argv[1],(char*)NULL);
         perror("exec");
      }
      else         //parent process
      {
         sleep(2);                 //wait for all children to set their signalhandlers
         
         if(i == workers -1)
            kill(pids[i],SIGUSR1);
      }
   }
   succesful_pids = malloc(workers*sizeof(int));
   for(i=0;i<workers;i++)
   {   
      rw = wait(&status);
      if(rw == -1)                      //h parent process den exei paidia
      {
			perror("wait");
			exit(1);
      }
      for(j=0;j<workers;j++)
      {
         if(rw == pids[j])
         { 
            if((status & 0377)== 0) 
            {
               printf("+++ Parent: Child Exited Normally: %d\n", status >> 8);
               succesful_pids[l++] = pids[j];
               
            }
            else 
            {
               printf("+++ Parent: Child Exited due to signal: %d\n", status & 0177);
               if((status & 0177) == EXIT_FAILURE)                      //se periptosi pou kapoio apo ta paidia apotyxei termatizoun osa trexoun akoma(mesw sigquit)
               {
                  for(k=0;k<workers;k++)
                  {
                     flag=1;
                     for(p=0;p<l;p++)                
                     {
                        if(pids[k] == succesful_pids[p])
                           flag=0;
                     }
                     if(flag != 0)
                        kill(pids[k],SIGQUIT);
                  }
               }
            }
         }
      }
   }
   free(succesful_pids);
   free(pids);
   complete_delete(&lista);
   fclose(fout);
   fclose(fcon);
}

