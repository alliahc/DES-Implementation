#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int init_perm[64]={ 58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17, 9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7 };;

int final_perm[] =
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};

int parity_drop[56] = 
{ 
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4 
};

int key_comp[48] = { 14, 17, 11, 24, 1, 5,
                    3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32 };

int shift_table[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int expansion_dbox[48] ={ 32, 1, 2, 3, 4, 5, 4, 5,
                        6, 7, 8, 9, 8, 9, 10, 11,
                        12, 13, 12, 13, 14, 15, 16, 17,
                        16, 17, 18, 19, 20, 21, 20, 21,
                        22, 23, 24, 25, 24, 25, 26, 27,
                        28, 29, 28, 29, 30, 31, 32, 1 };

int sbox[8][4][16] = {{ {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13} },
                        { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                          {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                          {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                          {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9} },
                        { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                          {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                          {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                          {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12} },
                        { {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                          {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                          {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                          {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} },
                        { {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                          {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                          {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                          {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3} },
                        { {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                          {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                          {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                          {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13} },
                        { {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                          {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                          {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                          {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} },
                        { {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                          {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                          {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                          {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
                        };

int straight_perm[32] ={16, 7, 20, 21,
                        29, 12, 28, 17,
                        1, 15, 23, 26,
                        5, 18, 31, 10,
                        2, 8, 24, 14,
                        32, 27, 3, 9,
                        19, 13, 30, 6,
                        22, 11, 4, 25 };

char round_keys[16][48];

char *permute(int n, char text[], int *perm_table,char *perm){
    int tmp;
    char ch;
    for (int i = 0; i <n; i++) {
        tmp= perm_table[i]-1;
        ch = text[tmp];
        strncat(perm,&ch,1);
    }
    return perm;
}

char *ShiftLeft(char *key, int shifts){
    for (int i=0; i <shifts; i++){
        char shifted[29]="";
        for (int j=1; j<28; j++){
            strncat(shifted,&key[j],1);
        }
        strncat(shifted,&key[0],1);
        strcpy(key,shifted);
    }
    return key;
}

void RoundKeys(char *key){
    char key64to56[57]="";
    permute(56,key,parity_drop,key64to56);
    //printf("key64to56:%s\n",key64to56);
    char leftsubkey[29],rightsubkey[29]; //29 cause of null-terminator
    leftsubkey[28]='\0';
    rightsubkey[28]='\0';
    memcpy(leftsubkey,&key64to56,28);
    memcpy(rightsubkey,&key64to56[28],28);
    //printf("leftsubkey:%s\n",leftsubkey);
    //printf("rightsubkey:%s\n",rightsubkey);
    for (int i=0; i < 16; i++){
        ShiftLeft(leftsubkey,shift_table[i]);
        ShiftLeft(rightsubkey,shift_table[i]);
        //printf("leftsubkey at round %d:%s\n",i,leftsubkey);
        //printf("rightsubkey at round %d:%s\n",i,rightsubkey);
        char combine[58]="";
        strcpy(combine,leftsubkey);
        strcat(combine,rightsubkey);
        //printf("combine at round %d:%s\n",i,combine);
        char roundkey[49]="";
        permute(48,combine,key_comp,roundkey);
        strcpy(round_keys[i],roundkey);
        //printf("roundkey at round %d:%s\n",i,round_keys[i]);
    }
}

void *reverse(char *s){
    int length = strlen(s);
    for (int i = 0; i < length / 2; i++){
        char ch = s[i];
        s[i] = s[length - i - 1];
        s[length - i - 1] = ch;
    }
}
char *PlainToBin(char *plaintext, char *binary){
    //char temp[351]="";
    char pad='0';
    for (int i = strlen(plaintext)-1; i>=0; i--) {
        int ascii = plaintext[i];
        //printf("char: %c ascii:%d\n",plaintext[i],ascii);
        int new_ascii;
        char ch;
        int j=0;
        while (ascii>0){
            new_ascii=ascii/2;
            int rem =ascii%2;
            ch=rem +'0';
            strncat(binary,&ch,1);
            ascii=new_ascii;
            j++;
        }
        for(int h=j; h<8; h++){
            strncat(binary,&pad,1);
        }
    }
    reverse(binary);
    int n= strlen(binary)%64;
    if(n!=0){
        for (int i=0; i<(64-n); i++){
            strncat(binary,&pad,1);
        }
    }
    //binary=strcat(binary,temp);
    return binary;
}
char *XOR(char *block, char *key, char *out){
    char ch[3]="01";
    int length=strlen(block);
    //printf("length of block:%d\n",length);
    for (int i=0; i < length;i++){
        if(block[i]==key[i]){
           strncat(out,&ch[0],1);
        }
        else{
            strncat(out,&ch[1],1);
        }
    }
    return out;
}

char *Encrypt(char *plainblock, char *encrypted){
    char temp[65]="";
    permute(64,plainblock,init_perm,temp);
    //printf("initial permutation:%s\n",temp);
    char leftblock[33],rightblock[33];
    leftblock[32]='\0';
    rightblock[32]='\0';
    memcpy(leftblock,&temp,32);
    memcpy(rightblock,&temp[32],32);
    //printf("L0:%s\n",leftblock);
    //printf("R0:%s\n",rightblock);
    for (int i=0; i<16; i++){
        //mixer
        char right32to48[49]="";
        permute(48,rightblock,expansion_dbox,right32to48);
        //printf("right32to48:%s\n",right32to48);
        char xor_right[49]="";
        XOR(right32to48,round_keys[i],xor_right);
        //printf("XOR right:%s\n", xor_right);
        //substitute
        char sub[33]=""; //32 lang ata instead na 48
        for (int j=0; j<8; j++){
            int row = 2 * (xor_right[j * 6] - '0') + (xor_right[j * 6 + 5] - '0'); // -'0' to convert to int
            int col = (8 * (xor_right[j * 6 + 1] - '0')) + (4 * (xor_right[j * 6 + 2] - '0')) + (2 * (xor_right[j * 6 + 3] - '0')) + (xor_right[j * 6 + 4] - '0');
            int value = sbox[j][row][col];
            //printf("j:%d, row:%d, col:%d\n",j,row,col);
            //printf("value:%d\n",value);
            int temp=value/8;
            char t1=temp + '0';
            strncat(sub,&t1,1);
            value=value%8;
            temp=value/4;
            char t2=temp + '0';
            strncat(sub,&t2,1);
            value=value%4;
            temp=value/2;
            char t3=temp + '0';
            strncat(sub,&t3,1);
            value=value%2;
            char t4=value + '0';
            strncat(sub,&t4,1);
            //printf("t1 to t4:%c %c %c %c\n",t1,t2,t3,t4);
            //printf("sub:%s\n",sub);
        }

        char straight[33]="";
        permute(32,sub,straight_perm,straight);
        char xor_left[33]="";
        XOR(leftblock,straight,xor_left);
        strcpy(leftblock,xor_left); 
        //printf("sub:%s\n",sub);
        //printf("straight:%s\n",straight);
        //printf("xor_left:%s\n",xor_left);
        //swap
        if (i!=15){
            char temp[33]="";
            strcpy(temp,rightblock);
            strcpy(rightblock,leftblock);
            strcpy(leftblock,temp);
            //printf("after swap leftblock:%s\n",leftblock);
            //printf("after swap rightblock:%s\n",rightblock);
        }
        //printf("leftblock:%s\t rightblock:%s\n",leftblock,rightblock);
        //printf("roundkeys at round %d:%s\n\n",i+1,round_keys[i]);
    }
    //combine
    char combine[66]="";
    strcat(combine,leftblock);
    strcat(combine,rightblock);
    permute(64,combine,final_perm,encrypted);
    return encrypted;
}

int ParityCheck(char *key){
    int length=strlen(key);
    int ones=0;
    for (int i=0; i<length; i++){
        if(i%7!=0 || i==0){
            //printf("%c",key[i]);
            if(key[i]=='1'){
                ones++;
            }
        }
        else{
            //printf(" %c ",key[i]);
            if((ones%2==0 && key[i]=='0')){
                printf("invalid key");
                return 0; //may error
            }
            ones=0;
        }  
    }
    return 1;
}
int main(){
    char plaintext[51];
    char key[65];
    fgets(plaintext, sizeof(plaintext), stdin);
    fgets(key, sizeof(key), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';
    int is_valid=ParityCheck(key);
    if(!is_valid) return 0;
    char converted[351]=""; //max of 50 chars * max 7 bits
    PlainToBin(plaintext,converted);
    //printf("in binary: %s\n",converted);
    RoundKeys(key);
    char encrypted[351]="";
    for (int i=0; i<strlen(converted);i+=64){
        char plainblock[65]="";
        memcpy(plainblock,&converted[i],64);
        //printf("plain block %d: %s\n",i,plainblock);
        char encryptedblock[65]="";
        Encrypt(plainblock,encryptedblock);
        //printf("encrypted block:%s\n",encryptedblock);
        strcat(encrypted,encryptedblock);
    }
    printf("%s",encrypted);
    return 0;
}