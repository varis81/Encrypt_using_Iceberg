#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <signal.h>

int fl_s = 0;

void signalhandler()              //orismos tou signalhandler gia to sima SIGUSR1
{
   fl_s=1;
   printf("i have recieved a sigusr1 %d\n",getpid());
}

void sigquit()
{ 
   printf("CHILD: My DADDY has Killed me!!!\n");
   exit(0);
}


void A2B(unsigned char* ascii,unsigned char* binary)
{
   int i=0;
   unsigned char temp[65];
   int  k = 0, n = 0;
   unsigned int convert;
   int total; 
   int length; 	
   int l;
   
   length = strlen(ascii);
   for(i=0;i<length;i++)
   {
      total = 0;
      convert = ascii[i];    
      while(convert > 0)                        
      {
         if((convert%2)==0)
         {
            temp[total] = 0 + '0';
            convert = convert/2;
            total++;         }
         else
         {
            temp[total] = 1 + '0';
            convert = convert/2;
            total++;
         }
      }
      while(total < 8)
      {
         temp[total] = 0 + '0';
         total++;
      }
         
      temp[total]='\0';
      total--; 
      while(total>=0)
      {
         binary[n++] = temp[total];
         total--;
      }
   }
   binary[64]='\0';
}

void B2A(unsigned char* input,unsigned char* asc)
{
	int length;     //get length of string
	int x,y,a,counter,z,j;
	double a1,b1;
	int power[8];       //will set powers of 2 in an array
	int binary[8];    //array used to store 1 byte of binary number (1 character)
	int asciiNum = 0;      //the ascii number after conversion from binary
	unsigned char ascii;      //the ascii character itself
	
	length = strlen(input);
    z = 0;   //counter used
	
	for(x = 0; x < length / 8; x++)     //reading in bytes. total characters = length / 8
	{
		for(a = 0; a < 8; a++)      //store info into binary[0] through binary[7]
		{
			binary[a] = (int) input[z] - 48;      //z never resets
			z++;
		}
		
	    counter = 7;        //power starts at 2^0, ends at 2^7
		for(j = 0; j < 8; j++)
		{
			power[j] = counter;      //power[] = {7, 6, 5, ..... 1, 0}
			counter--;    //decrement counter each time
		}
		
		for(y = 0; y < 8; y++)    //will compute asciiNum
		{
			a1 = binary[y];    //store the element from binary[] as "a"
			b1 = power[y];    //store the lement from power[] as "b"
			
			asciiNum += a1* pow(2, b1);   //asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
		}
		ascii = asciiNum;   //assign the asciiNum value to ascii, to change it into an actual character
		asciiNum = 0;    //reset asciiNum for next loop
		
		//printf("%c\n",ascii);	//display the ascii character
		asc[x] = ascii;
	}
	asc[x]='\0';

}

void H2B(char* hex,char* binary)
{
   int i=0;
   int k=0;
   int j=0;
   int temp;
   
   while(hex[i] != '\0')
   {
      switch(hex[i])
      {
         case '0': binary[k++] = '0'; 
                   binary[k++] = '0';
                   binary[k++] = '0';
                   binary[k++] = '0';                                                       
                   break;
         case '1': binary[k++] = '0'; 
                   binary[k++] = '0';
                   binary[k++] = '0';
                   binary[k++] = '1';                                                     
                   break;
         case '2': binary[k++] = '0'; 
                   binary[k++] = '0';
                   binary[k++] = '1';
                   binary[k++] = '0';                                                      
                   break;
         case '3': binary[k++] = '0'; 
                   binary[k++] = '0';
                   binary[k++] = '1';
                   binary[k++] = '1';                                                       
                   break;
         case '4': binary[k++] = '0'; 
                   binary[k++] = '1';
                   binary[k++] = '0';
                   binary[k++] = '0';                                                        
                   break;
         case '5': binary[k++] = '0'; 
                   binary[k++] = '1';
                   binary[k++] = '0';
                   binary[k++] = '1';                                                        
                   break;
         case '6': binary[k++] = '0'; 
                   binary[k++] = '1';
                   binary[k++] = '1';
                   binary[k++] = '0';                                                       
                   break;
         case '7': binary[k++] = '0'; 
                   binary[k++] = '1';
                   binary[k++] = '1';
                   binary[k++] = '1';                                                      
                   break;
         case '8': binary[k++] = '1'; 
                   binary[k++] = '0';
                   binary[k++] = '0';
                   binary[k++] = '0';                                                      
                   break;
         case '9': binary[k++] = '1'; 
                   binary[k++] = '0';
                   binary[k++] = '0';
                   binary[k++] = '1';                                                      
                   break;
         case 'a': binary[k++] = '1'; 
                   binary[k++] = '0';
                   binary[k++] = '1';
                   binary[k++] = '0';                                                       
                   break;
         case 'b': binary[k++] = '1'; 
                   binary[k++] = '0';
                   binary[k++] = '1';
                   binary[k++] = '1';                                                      
                   break;
         case 'c': binary[k++] = '1'; 
                   binary[k++] = '1';
                   binary[k++] = '0';
                   binary[k++] = '0';                                                        
                   break;
         case 'd': binary[k++] = '1'; 
                   binary[k++] = '1';
                   binary[k++] = '0';
                   binary[k++] = '1';                                                     
                   break;
         case 'e': binary[k++] = '1'; 
                   binary[k++] = '1';
                   binary[k++] = '1';
                   binary[k++] = '0';                                                      
                   break;
         case 'f': binary[k++] = '1'; 
                   binary[k++] = '1';
                   binary[k++] = '1';
                   binary[k++] = '1';                                                       
                   break;
         default:  fprintf(stderr, "wrong input!\n");
                   exit(EXIT_FAILURE);
      }
      i++;
   }

   
   binary[k] = '\0'; // end with NULL
}

void B2H(char* bin,char* hex)
{
   int i=0;
   int k=0;
   
   while(bin[i] != '\0')
   {
      if(bin[i] == '0' && bin[i+1] == '0' && bin[i+2] == '0' && bin[i+3] == '0')
         hex[k++] = '0';
      else if(bin[i] == '0' && bin[i+1] == '0' && bin[i+2] == '0' && bin[i+3] == '1')
         hex[k++] = '1';
      else if(bin[i] == '0' && bin[i+1] == '0' && bin[i+2] == '1' && bin[i+3] == '0')
         hex[k++] = '2';
      else if(bin[i] == '0' && bin[i+1] == '0' && bin[i+2] == '1' && bin[i+3] == '1')
         hex[k++] = '3';
      else if(bin[i] == '0' && bin[i+1] == '1' && bin[i+2] == '0' && bin[i+3] == '0')
         hex[k++] = '4';
      else if(bin[i] == '0' && bin[i+1] == '1' && bin[i+2] == '0' && bin[i+3] == '1')
         hex[k++] = '5'; 
      else if(bin[i] == '0' && bin[i+1] == '1' && bin[i+2] == '1' && bin[i+3] == '0')
         hex[k++] = '6';
      else if(bin[i] == '0' && bin[i+1] == '1' && bin[i+2] == '1' && bin[i+3] == '1')
         hex[k++] = '7';
      else if(bin[i] == '1' && bin[i+1] == '0' && bin[i+2] == '0' && bin[i+3] == '0')
         hex[k++] = '8';
      else if(bin[i] == '1' && bin[i+1] == '0' && bin[i+2] == '0' && bin[i+3] == '1')
         hex[k++] = '9';
      else if(bin[i] == '1' && bin[i+1] == '0' && bin[i+2] == '1' && bin[i+3] == '0')
         hex[k++] = 'a';
      else if(bin[i] == '1' && bin[i+1] == '0' && bin[i+2] == '1' && bin[i+3] == '1')
         hex[k++] = 'b';
      else if(bin[i] == '1' && bin[i+1] == '1' && bin[i+2] == '0' && bin[i+3] == '0')
         hex[k++] = 'c';
      else if(bin[i] == '1' && bin[i+1] == '1' && bin[i+2] == '0' && bin[i+3] == '1')
         hex[k++] = 'd';
      else if(bin[i] == '1' && bin[i+1] == '1' && bin[i+2] == '1' && bin[i+3] == '0')
         hex[k++] = 'e';
      else if(bin[i] == '1' && bin[i+1] == '1' && bin[i+2] == '1' && bin[i+3] == '1')
         hex[k++] = 'f';
      i = i + 4;
   }   
   hex[k] = '\0';
}

char S_BOX(char in,int s_type)
{
   int i=0;
   int k=0;
   char temp;

   switch(s_type)                                
   {
      case 0:switch(in)                                //S0 type
             {
                case '0': temp = 'd';break;
                case '1': temp = '7';break;
                case '2': temp = '3';break;
                case '3': temp = '2';break;
                case '4': temp = '9';break;
                case '5': temp = 'a';break;
                case '6': temp = 'c';break;
                case '7': temp = '1';break;
                case '8': temp = 'f';break;
                case '9': temp = '4';break;
                case 'a': temp = '5';break;
                case 'b': temp = 'e';break;
                case 'c': temp = '6';break;
                case 'd': temp = '0';break;
                case 'e': temp = 'b';break;
                case 'f': temp = '8';break;
                default: fprintf(stderr, "wrong input!\n");
                   exit(EXIT_FAILURE);
             }
             break;
      case 1: switch(in)                                //S1 type
              {
                 case '0': temp = '4';break;
                 case '1': temp = 'a';break;
                 case '2': temp = 'f';break;
                 case '3': temp = 'c';break;
                 case '4': temp = '0';break;
                 case '5': temp = 'd';break;
                 case '6': temp = '9';break;
                 case '7': temp = 'b';break;
                 case '8': temp = 'e';break;
                 case '9': temp = '6';break;
                 case 'a': temp = '1';break;
                 case 'b': temp = '7';break;
                 case 'c': temp = '3';break;
                 case 'd': temp = '5';break;
                 case 'e': temp = '8';break;
                 case 'f': temp = '2';break;
                 default: fprintf(stderr, "wrong input!\n");
                    exit(EXIT_FAILURE);
              }
              break;
      case 2: switch(in)                       //D type
              {
                 case '0': temp = '0';break;
                 case '1': temp = 'e';break;
                 case '2': temp = 'd';break;
                 case '3': temp = '3';break;
                 case '4': temp = 'b';break;
                 case '5': temp = '5';break;
                 case '6': temp = '6';break;
                 case '7': temp = '8';break;
                 case '8': temp = '7';break;
                 case '9': temp = '9';break;
                 case 'a': temp = 'a';break;
                 case 'b': temp = '4';break;
                 case 'c': temp = 'c';break;
                 case 'd': temp = '2';break;
                 case 'e': temp = '1';break;
                 case 'f': temp = 'f';break;
                 default: fprintf(stderr, "wrong input!\n");
                    exit(EXIT_FAILURE);
              }
              break;                                       
   }  
   return temp;
}

void P_BOX(char* in,char* out,int type)
{
   switch(type)
   {
      case 4: out[0] = in[1];
              out[1] = in[0];
              out[2] = in[3];
              out[3] = in[2];
              break;
      case 8: out[0] = in[0];
              out[1] = in[1];
              out[2] = in[4];
              out[3] = in[5];
              out[4] = in[2];
              out[5] = in[3];
              out[6] = in[6];
              out[7] = in[7];
              break;
      case 64: out[0] = in[0];
               out[1] = in[12];
               out[2] = in[23];
               out[3] = in[25];
               out[4] = in[38];
               out[5] = in[42];
               out[6] = in[53];
               out[7] = in[59];
               out[8] = in[22];
               out[9] = in[9];
               out[10] = in[26];
               out[11] = in[32];
               out[12] = in[1];
               out[13] = in[47];
               out[14] = in[51];
               out[15] = in[61];
               out[16] = in[24];
               out[17] = in[37];
               out[18] = in[18];
               out[19] = in[41];
               out[20] = in[55];
               out[21] = in[58];
               out[22] = in[8];
               out[23] = in[2];
               out[24] = in[16];
               out[25] = in[3];
               out[26] = in[10];
               out[27] = in[27];
               out[28] = in[33];
               out[29] = in[46];
               out[30] = in[48];
               out[31] = in[62];
               out[32] = in[11];
               out[33] = in[28];
               out[34] = in[60];
               out[35] = in[49];
               out[36] = in[36];
               out[37] = in[17];
               out[38] = in[4];
               out[39] = in[43];
               out[40] = in[50];
               out[41] = in[19];
               out[42] = in[5];
               out[43] = in[39];
               out[44] = in[56];
               out[45] = in[45];
               out[46] = in[29];
               out[47] = in[13];
               out[48] = in[30];
               out[49] = in[35];
               out[50] = in[40];
               out[51] = in[14];
               out[52] = in[57];
               out[53] = in[6];
               out[54] = in[54];
               out[55] = in[20];
               out[56] = in[44];
               out[57] = in[52];
               out[58] = in[21];
               out[59] = in[7];
               out[60] = in[34];
               out[61] = in[15];
               out[62] = in[31];
               out[63] = in[63];
               break;
      case 128: out[0] = in[76];
                out[1] = in[110];
                out[2] = in[83];
                out[3] = in[127];
                out[4] = in[67];
                out[5] = in[114];
                out[6] = in[92];
                out[7] = in[97];
                out[8] = in[98];
                out[9] = in[65];
                out[10] = in[121];
                out[11] = in[106];
                out[12] = in[78];
                out[13] = in[112];
                out[14] = in[91];
                out[15] = in[82];
                out[16] = in[71];
                out[17] = in[101];
                out[18] = in[89];
                out[19] = in[126];
                out[20] = in[72];
                out[21] = in[107];
                out[22] = in[81];
                out[23] = in[118];
                out[24] = in[90];
                out[25] = in[124];
                out[26] = in[73];
                out[27] = in[88];
                out[28] = in[64];
                out[29] = in[104];
                out[30] = in[100];
                out[31] = in[85];
                out[32] = in[109];
                out[33] = in[87];
                out[34] = in[75];
                out[35] = in[113];
                out[36] = in[120];
                out[37] = in[66];
                out[38] = in[103];
                out[39] = in[115];
                out[40] = in[122];
                out[41] = in[108];
                out[42] = in[95];
                out[43] = in[69];
                out[44] = in[74];
                out[45] = in[116];
                out[46] = in[80];
                out[47] = in[102];
                out[48] = in[84];
                out[49] = in[96];
                out[50] = in[125];
                out[51] = in[68];
                out[52] = in[93];
                out[53] = in[105];
                out[54] = in[119];
                out[55] = in[79];
                out[56] = in[123];
                out[57] = in[86];
                out[58] = in[70];
                out[59] = in[117];
                out[60] = in[111];
                out[61] = in[77];
                out[62] = in[99];
                out[63] = in[94];
                out[64] = in[28];
                out[65] = in[9];
                out[66] = in[37];
                out[67] = in[4];
                out[68] = in[51];
                out[69] = in[43];
                out[70] = in[58];
                out[71] = in[16];
                out[72] = in[20];
                out[73] = in[26];
                out[74] = in[44];
                out[75] = in[34];
                out[76] = in[0];
                out[77] = in[61];
                out[78] = in[12];
                out[79] = in[55];
                out[80] = in[46];
                out[81] = in[22];
                out[82] = in[15];
                out[83] = in[2];
                out[84] = in[48];
                out[85] = in[31];
                out[86] = in[57];
                out[87] = in[33];
                out[88] = in[27];
                out[89] = in[18];
                out[90] = in[24];
                out[91] = in[14];
                out[92] = in[6];
                out[93] = in[52];
                out[94] = in[63];
                out[95] = in[42];
                out[96] = in[49];
                out[97] = in[7];
                out[98] = in[8];
                out[99] = in[62];
                out[100] = in[30];
                out[101] = in[17];
                out[102] = in[47];
                out[103] = in[38];
                out[104] = in[29];
                out[105] = in[53];
                out[106] = in[11];
                out[107] = in[21];
                out[108] = in[41];
                out[109] = in[32];
                out[110] = in[1];
                out[111] = in[60];
                out[112] = in[13];
                out[113] = in[35];
                out[114] = in[5];
                out[115] = in[39];
                out[116] = in[45];
                out[117] = in[59];
                out[118] = in[23];
                out[119] = in[54];
                out[120] = in[36];
                out[121] = in[10];
                out[122] = in[40];
                out[123] = in[56];
                out[124] = in[25];
                out[125] = in[50];
                out[126] = in[19];
                out[127] = in[3];
                break; 
   }
}

//synartisi gyrou

void gama(char *a,char* out)
{
   char hexout[17];           //metatropi eisodou se 16iko
   char hexout1[17];          //eksodos protou epipedou 16 S0
   char binary[65];           //metatropi tis eksodou 16S0 se binary
   char pbin1[9];              //temp for P8
   char pbin2[9];
   char binary1[65];           //bin eksodos 8 P8
   char hexout2[17];            //metatropi eksodou 8 P8 se 16diko
   char hexout3[17];           //efarmogi 16-S1 sto hexout3
   char binary2[65];           //eksodos meta to epipedo efarmogis 8-P8(deyteri fora)
   char hexout4[65];           //metatropi ths eksodou tou epipedou 8-P8(deyteri fora) se 16-diko
   char hexout5[65];           //output of gama()
   int i;  
     
   B2H(a,hexout);
   for(i=0;i<16;i++)                        //efarmogi 16 S0-Box
      hexout1[i] = S_BOX(hexout[i],0);
   hexout1[i] = '\0';
   
   H2B(hexout1,binary);
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+8];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+8] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+16];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+16] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+24];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+24] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+32];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+32] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+40];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+40] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+48];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+48] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+56];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary1[i+56] = pbin2[i]; 
      
   binary1[64] = '\0';
   
   B2H(binary1,hexout2);
   
   for(i=0;i<16;i++)                        //efarmogi 16 S1-Box
      hexout3[i] = S_BOX(hexout2[i],1);
   hexout3[i] = '\0';

   H2B(hexout3,binary);
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+8];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+8] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+16];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+16] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+24];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+24] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+32];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+32] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+40];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+40] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+48];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+48] = pbin2[i]; 
   
   for(i=0;i<8;i++)
      pbin1[i] = binary[i+56];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,8);
   pbin2[8] = '\0';
   for(i=0;i<8;i++)
      binary2[i+56] = pbin2[i]; 
      
   binary2[64] = '\0';
  
   B2H(binary2,hexout4);
   
   for(i=0;i<16;i++)                        //efarmogi 16 S0-Box
      hexout5[i] = S_BOX(hexout4[i],0);
   hexout5[i] = '\0';  
   
   H2B(hexout5,binary);
   
   for(i=0;i<64;i++)
      out[i] = binary[i];
   out[i] ='\0';
}

void SK(char* a,char* b,char* out)
{
   int i;
   int a1,b1,out1;
   

   for(i=0;i<64;i++)
   {
      a1 = a[i] - '0';
      b1 = b[i] - '0';
      out1 = a1^b1;
      
      out[i] = out1 + '0';
   }
   out[i] = '\0';   
}


void EK(char* a,char* b,char *out)
{
   int i;
   char binary[65];         //eksodos protou epipedou efarmogis P-64
   char hexout[17];         //metatropi ths eksodou tou protou epipedou p64 se 16diko
   char hexout1[17];        //efarmogi 16 D BOXes
   char binary1[65];        //metatropi se binary meta tin eksodo ap to 2o epipedo
   char binary2[65];         //eksodos ths SK
   char pbin1[5];
   char pbin2[5];
   char binary3[65];          //eksodos meta apo 16 P4
   
   P_BOX(a,binary,64);                            //efarmogi P64
   binary[64] = '\0';
   
   B2H(binary,hexout);

   for(i=0;i<16;i++)
      hexout1[i] = S_BOX(hexout[i],2);                //efarmogi 16 D-Box
   hexout1[i] = '\0';
   
   H2B(hexout1,binary1);                            //metatropi se binary
       
   SK(binary1,b,binary2);                          //binary2 == eksodos ths SK
   
   for(i=0;i<4;i++)
      pbin1[i] = binary2[i];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i] = pbin2[i];
      
   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+4];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+4] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+8];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+8] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+12];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+12] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+16];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+16] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+20];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+20] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+24];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+24] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+28];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+28] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+32];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+32] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+36];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+36] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+40];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+40] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+44];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+44] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+48];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+48] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+52];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+52] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+56];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+56] = pbin2[i];

   for(i=0;i<4;i++)
      pbin1[i] = binary2[i+60];
   pbin1[i] = '\0';
   P_BOX(pbin1,pbin2,4);
   pbin2[4] = '\0';
   for(i=0;i<4;i++)
      binary3[i+60] = pbin2[i];
      
   binary3[64] = '\0';
   
   P_BOX(binary3,out,64);
   out[64] = '\0';
}

//programmatismos kleidiou

void TC(char* a,int C,char* temp)                 //128 bit input/output
{
   int i;
     
   for(i=0;i<128;i++)
   {
      if(C==1){temp[i]=a[(i+8)%128];}
      if(C==0){temp[i]=a[(128+i-8)%128];}
   }
   temp[128]='\0'; 
}

void BC(char* a,int C,char *out)                  //128 bit input/output
{
   int i;
   char binary[129];                           //eksodos ths protis olisthisis
   char binary1[129];                          //binary eksodos meta to proto P128
   char hexout[33];                            //hex eksodos meta to proto P128
   char hexout1[33];                           //efarmogi 32 S0 boxes
   char binary2[129];
   char binary3[129];                          //eksodos deyterou P128

   TC(a,C,binary);
   
   P_BOX(binary,binary1,128);
   binary1[128] = '\0';
   
   B2H(binary1,hexout);
   
   for(i=0;i<32;i++)                        //efarmogi 32 S0-Box
      hexout1[i] = S_BOX(hexout[i],0);
   hexout1[i] = '\0';
   
   H2B(hexout1,binary2);
   
   P_BOX(binary2,binary3,128);
   binary3[128] = '\0';
   
   TC(binary3,C,out);
   out[128] = '\0';
   
}

void E(char *a,char* out)    //sybiezei kratwntas mono ta perrita bytes
{
   int i;  
     
   for(i=0;i<8;i++)
      out[i] = a[i+8];
     
   for(i=0;i<8;i++)
      out[i+8] = a[i+24];
     
   for(i=0;i<8;i++)
      out[i+16] = a[i+40];
     
   for(i=0;i<8;i++)
      out[i+24] = a[i+56];
     
   for(i=0;i<8;i++)
      out[i+32] = a[i+72];
     
   for(i=0;i<8;i++)
      out[i+40] = a[i+88];
     
   for(i=0;i<8;i++)
      out[i+48] = a[i+104];
     
   for(i=0;i<8;i++)
      out[i+56] = a[i+120];    
}

void f(char* a,int sel,char* temp)
{
   int i;
   int a1,a2,a3,a4,out1,out2,out3,out4;
   //For each of the 4-bit groups of the input (0-3,4-7,...) do
   for(i=0;i<64;i = i+4)
   {
      if(sel == 0)
      {
         a1 = a[i] - '0';                   //metatropi se int  
         a2 = a[i+1] - '0';    
         a3 = a[i+2] - '0';
         a4 = a[i+3] - '0';
          
         out1 = a1 ^ a2;
         out2 = a2;
         out3 = a3 ^ a4;
         out4 = a4; 
         
         temp[i] = out1 + '0';
         temp[i+1] = out2 + '0';
         temp[i+2] = out3 + '0';
         temp[i+3] = out4 + '0';
             
      }
      else if(sel == 1)
      {
         a1 = a[i] - '0';                   //metatropi se int  
         a2 = a[i+1] - '0';    
         a3 = a[i+2] - '0';
         a4 = a[i+3] - '0';
          
         out1 = a1 ^ a2 ^ a3;
         out2 = a2 ^ a3;
         out3 = a3 ^ a4 ^ a1;
         out4 = a4 ^ a1; 
         
         temp[i] = out1 + '0';
         temp[i+1] = out2 + '0';
         temp[i+2] = out3 + '0';
         temp[i+3] = out4 + '0';
         
      }  
   } 
   temp[i] = '\0';
}

//kryptografisi/apokriptografisi

void iceberg_encrypt(char *key,char* m,int N,char* c)//to c dinetai ws orisma kai einai h eksodos ths iceberg encrypt
{
    int i;
    char *temp_key;
    char sel_key[129];
    char temp[129];
    char exit[129];    //voithitiki metavliti
     
   // ROUND 0
   temp_key = malloc((strlen(key)+1)*sizeof(char));
   //temp_key = key;
   strcpy(temp_key,key);
   
   E(key,exit);
   f(exit,1,sel_key);
   SK(m,sel_key,temp);
   // ROUNDS 1 - N/2
   for(i=0;i<(N/2);i++) 
   {
      BC(temp_key,0,temp_key);
      E(temp_key,exit);                  
      f(exit,1,sel_key);
      gama(temp,exit);
      EK(exit,sel_key,temp);
   }
   // ROUNDS N/2+1 - N-1
   for(i=0;i<(N/2)-1;i++)
   {
      BC(temp_key,1,temp_key);
      E(temp_key,exit);
      f(exit,1,sel_key);
      gama(temp,exit);
      EK(exit,sel_key,temp);
   }
   // ROUND N
   BC(temp_key,1,temp_key);
   E(temp_key,exit);
   f(exit,0,sel_key);
   gama(temp,exit);
   SK(exit,sel_key,c);
   free(temp_key);
}

void iceberg_decrypt(char* key,char *c,int N,char *m)
{
   int i;
   char* temp_key;  
   char sel_key[129];
   char temp[129];
   char exit[129];            //voithitiki metavliti
    
   // ROUND 0
   temp_key = malloc((strlen(key)+1)*sizeof(char));
   strcpy(temp_key,key);
   
   E(key,exit); 
   f(exit,0,sel_key);
   SK(c,sel_key,exit);
   gama(exit,temp);
   // ROUNDS 1 - N/2
   for(i=0;i<(N/2);i++)
   {
      BC(temp_key,0,temp_key);
      E(temp_key,exit);
      f(exit,0,sel_key);
      EK(temp,sel_key,exit);
      gama(exit,temp);
   }
   // ROUNDS N/2+1 - N-1
   for(i=0;i<(N/2)-1;i++)
   {
      BC(temp_key,1,temp_key);
      E(temp_key,exit);
      f(exit,0,sel_key);
      EK(temp,sel_key,exit);
      gama(exit,temp);
   }
   // ROUND N
   BC(temp_key,1,temp_key);
   E(temp_key,exit);
   f(exit,1,sel_key);
   SK(temp,sel_key,m);
   free(temp_key);
}

main(int argc,char **argv)
{
   FILE *in,*out;
   int N,prevpid,length,offset,i,j;
   unsigned char *key,*input,*output;
   unsigned char ascii[9],binary[65],bkey[129],boutput[65];
    
   if(argc != 9)
   {
      fprintf(stderr,"Usage: ./iceberg input_file offset length output_file prevpid key N [-e/-d]\n");
                              /*argv[0] argv[1] argv[2] argv[3] argv[4] argv[5] argv[6] argv[7] argv[8] */
      exit(EXIT_FAILURE);
   }      
   
   signal(SIGUSR1,signalhandler);
   signal(SIGQUIT,sigquit);
   
   offset = atoi(argv[2]);
   length = atoi(argv[3]);
   N = atoi(argv[7]);
   prevpid = atoi(argv[5]);
   input = malloc((strlen(argv[1])+1)*sizeof(char));
   strcpy(input,argv[1]);
   output = malloc((strlen(argv[4])+1)*sizeof(char));
   strcpy(output,argv[4]);
   key = malloc((strlen(argv[6])+1)*sizeof(char));
   strcpy(key,argv[6]);

   in = fopen(input,"r");
   if(in == NULL)
   {
      fprintf(stderr,"error opening file!\n");
      exit(EXIT_FAILURE);
   }
   out = fopen(output,"r+");
   if(out == NULL)
   {
      fprintf(stderr,"error opening file for writing!\n");
      exit(EXIT_FAILURE);   
   }

   if(prevpid != 0)
   {
      while(!fl_s)
         pause();  
      kill(prevpid,SIGUSR1);
   }
    while(!fl_s)
         pause();  
         
   fseek(in,offset,SEEK_SET);
   fseek(out,offset,SEEK_SET);
   for(i=1;i<=length;i++)
   {
     for(j=0;j<8;j++)
       ascii[j] = fgetc(in);
     
      A2B(ascii,binary);
      H2B(key,bkey);
      if(strcmp(argv[8],"-e") == 0)
         iceberg_encrypt(bkey,binary,N,boutput);
      else if(strcmp(argv[8],"-d") == 0)
         iceberg_decrypt(bkey,binary,N,boutput);
      else{
         fprintf(stderr,"give correct argument\n");
         exit(EXIT_FAILURE);}
      B2A(boutput,ascii); 

      for(j=0;j<8;j++)
         fputc(ascii[j],out);     
   }
      
   fclose(in);
   fclose(out);   
   exit(EXIT_SUCCESS);
}
