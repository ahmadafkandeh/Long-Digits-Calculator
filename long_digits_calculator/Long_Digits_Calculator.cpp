/************************************************************************************
   Copyright AUG-2016 Ahmad Afkandeh (github.com/ahmadafkandeh)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
************************************************************************************/

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//-------------------------------------------------
void PrintAnswer(char * ans);
void Reverse(char * input);
void ReadNumber(char * input); //read a number from keyboard
char ReadFunction(); //read a function from keyboard
int  GetSign(char * input); //get input number sign
void AddSign(char * input,int sign); //add a sign into number
void RemoveSign(char * input); //remove sign from number
char IsIn1BigerThanIn2(char * in1,char * in2);
//-------------------------------------------------
void Add(char * input1,char * input2);
void Neg(char * input1,char * input2);
void Div(char * input1,char * input2,char Div_Mod); //division mode(Div_Mod) when 0 input1=input1 / input2 , when 1 input1=input1 % input2
void Mul(char * input1,char * input2);
void Exp(char * input1,char * input2);
//-------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::cin;
	std::cout;
	char ANS[1000],nextNum[20];
	 char Func;
	 char Flag=0;

	while(1){
		memset(ANS,0,1000);
		memset(nextNum,0,20);

		system("cls");
		printf("Long Digits calculator\r\n");
		printf("Arithmatic Functions:( + , - , * , / , %% , ^ , = ).\r\n");
		printf("you can use both signed or unsigned Numbers.\r\n");
		printf("Enter a Number:\r\n");
		ReadNumber(ANS);
		do {
			Flag=0;
			printf("Enter an Arithmatic Function:\r\n");
			Func=ReadFunction();

			switch (Func){
				case '+':
					printf("Enter Next Number:\r\n");
					ReadNumber(nextNum);
					Add(ANS,nextNum);
					Flag=1;
					break;
				case '-':
					printf("Enter Next Number:\r\n");
					ReadNumber(nextNum);
					Neg(ANS,nextNum);
					Flag=1;
					break;
				case '*':
					printf("Enter Next Number:\r\n");
					ReadNumber(nextNum);
					Mul(ANS,nextNum);
					Flag=1;
					break;
				case '/':
					printf("Enter Next Number:\r\n");
					ReadNumber(nextNum);
					Div(ANS,nextNum,0);
					Flag=1;
					break;
				case '^':
					printf("Enter Next Number:\r\n");
					ReadNumber(nextNum);
					Exp(ANS,nextNum);
					Flag=1;
					break;
				case '%':
					printf("Enter Next Number:\r\n");
					ReadNumber(nextNum);
					Div(ANS,nextNum,1);
					Flag=1;
					break;
				case '=':
					PrintAnswer(ANS);
					Flag=0;
					break;
				default:
					Flag=1;
					printf("Invalid Function.\r\n");
			}

		}while(Flag);
		printf("Press Enter to continue.\r\n");
		getchar();
	}
	return 0;
}

void Add(char * input1,char * input2)
{
	int len1,len2;
	int i=0;
	int ci=1;
	char temp1,temp2,carry=0;

	int in1sign,in2sign;
	in1sign=GetSign(input1);
	in2sign=GetSign(input2);
	if((in1sign==0?+1:in1sign)!=(in2sign==0?+1:in2sign))
	{
		RemoveSign(input2);
		in2sign=(in2sign==0?-1:in2sign*-1);
		AddSign(input2,in2sign);
		Neg(input1,input2);
		return;
	}
	RemoveSign(input1);
	RemoveSign(input2);

	len1=strlen(input1);
	len2=strlen(input2);

	Reverse(input1);
	Reverse(input2);

	if(len2>len1) {
		memset(&input1[len1],'0',len2-len1); 
		input1[len2]=0;
	}
	for (i=0;i<len2;i++){
		
		temp1=input1[i]-'0';
		if (temp1<0 || temp1>9)temp1=0;
		temp2=input2[i]-'0';
		if ((temp1+=temp2)>9) {temp1-=10; carry=1;}
		ci=1;
		while (carry==1){
			temp2=input1[i+ci]-'0';
			if (temp2<0 || temp2>9)temp2=0;
			if ((temp2+=1)>9) {
				temp2-=10;
				carry=1;
			}
			else{
				carry=0;
				if ((i+ci+1)>len1) 
					input1[i+ci+1]=0;
			}
			input1[i+ci]=temp2+'0';
			ci++;
		}

		input1[i]=temp1+'0';
	}
	Reverse(input1);
	Reverse(input2);

	AddSign(input1,in1sign);
	AddSign(input2,in2sign);
	if (i>len1) input1[i]=0;

}

void Neg(char * input1,char * input2)
{
	int len1,len2;
	int in1sign,in2sign;
	in1sign=GetSign(input1);
	in2sign=GetSign(input2);

	if((in1sign==0?+1:in1sign)!=(in2sign==0?+1:in2sign))
	{
		RemoveSign(input2);
		in2sign=(in2sign==0?-1:in2sign*-1);
		AddSign(input2,in2sign);
		Add(input1,input2);
		return;
	}

	RemoveSign(input1);
	RemoveSign(input2);

	char temp1,temp2,carry=0,flag=0;
	len1=strlen(input1);
	len2=strlen(input2);

	Reverse(input1);
	Reverse(input2);
	if(len2>len1) {
		char* temp=new char[len2+1];
		memcpy(temp,input2,len2+1);
		memcpy(input2,input1,len1+1);
		memcpy(input1,temp,len2+1);
		len1=strlen(input1);
		len2=strlen(input2);
		delete [] temp;
			flag=1;
	}

	for (int i=0;i<len2;i++)
	{
			temp1=input1[i]-'0';
			if (temp1<0 || temp1>9)
				temp1=0;
			temp2=input2[i]-'0';
			temp2=~temp2+1;
			temp1+=temp2;
			if (temp1 & 0x80) carry=1;
			else carry=0;
			
			if (temp1>9)
			{
				temp1-=10;
				if(input1[i+1]!=0)input1[i+1]=((input1[i+1]-'0')-1)+'0';				
			}
			if (carry)
			{
				temp1=~temp1+1;
				if (temp1 & 0x0f)
				{
					temp1=10-temp1;
					if (input1[i+1]!=0)
					{
						int index=i+1;
						while(input1[index]=='0' && index<len1)
							index++;
					if (input1[index]!='0'  ) 
						input1[index]=((input1[index]-'0')-1)+'0';
					while(index-- && (index>=i))
					{
						input1[index]='9';
					}
					}
					else if (input1[i+1]==0 && temp1==9)temp1=0;
				}
			}
			
			input1[i]=temp1+'0';
	}
	if (len1<=len2 || flag==1)
	if (carry==1 || flag==1)in1sign=-1;

	for (int i=len1-1;i>0;i--)
	if (input1[i]=='0')input1[i]=0;
	else break;

	Reverse(input1);
	Reverse(input2);
	AddSign(input1,in1sign);
	AddSign(input2,in2sign);
	
}

void Mul(char * input1,char * input2)
{
	int len1,len2;
	int i=0;
	char * temp;
	char * ans;
	len1=strlen(input1);
	len2=strlen(input2);
	i=len1+len2;
	ans=new char[i*2];
	memset(ans,0,i*2);
	int in1sign=GetSign(input1);
	int in2sign=GetSign(input2);

	RemoveSign(input1);
	RemoveSign(input2);

	if (len2==1 && input2[0]=='0' || len1==1 && input1[0]=='0') {
		memset(input1,0,len1+1);
		input1[0]='0';
	}
	else{
		int count=0;
		Reverse(input2);

		for (i=0;i<len2;i++){
			char tt=(input2[i]-'0');
			if ((input2[i]-'0')!=0){
				len1=strlen(input1);
				temp=new char[len1+1];
				memset(temp,0,len1+1);
				memcpy(temp,input1,len1);	
				for (count=0;count<(tt);count++)
					Add(ans,temp);
				delete [] temp;
			}
			if (len2>1 && i<(len2-1)){
				int lenT=strlen(input1);
				char * temp2=new char [lenT+2];
				memset(temp2,0,lenT+2);
					temp2[0]='0';
				int index=0;
				Reverse(input1);
				memcpy(&temp2[1],input1,lenT);
				memcpy(input1,temp2,lenT+2);
				Reverse(input1);
				delete [] temp2;
			}
		}
		Reverse(input2);
		memcpy(input1,ans,strlen(ans)+1);
		if ((in1sign==0?+1:in1sign)!=(in2sign==0?+1:in2sign))
		{
			AddSign(input1,-1);
		}
		AddSign(input2,in2sign);
		delete [] ans;	
	}
}

void Div(char * input1,char * input2,char Div_Mod)
{
	int len1,len2;
	int in1sign,in2sign;
	in1sign=GetSign(input1);
	in2sign=GetSign(input2);

	RemoveSign(input1);
	RemoveSign(input2);

	char temp1,temp2,carry=0,flag=0;
	len1=strlen(input1);
	len2=strlen(input2);
	
	if (len2>len1)
	{
		input1[0]='0';
		input1[1]=0;
		return;
	}
	if (input2[0]=='0' || ((input2[0]=='=' |input2[0]=='+')&& input2[1]=='0'))
	{
		input1[0]='0';
		input1[1]=0;
		return;
	}
	char * temp=new char [len2];
	memcpy(temp,input2,len2+1);
	int count=0;
	Reverse(input2);
	while (IsIn1BigerThanIn2(input1,temp))
	{
			Neg(input1,temp);
				count++;
	}
	count++;
	if (Div_Mod==0)
	{	
		if ((in1sign==0?+1:in1sign)!=(in2sign==0?+1:in2sign)) AddSign(input1,-1);
		sprintf(input1,"%d",count);
	}

	Reverse(input2);
}

void Exp(char * input1,char * input2)
{
	int len1,len2;
	char * temp;
	len1=strlen(input1);
	len2=strlen(input2);
	
	int in2sign=GetSign(input2);

	if (len2==1 && input2[0]=='0') 
	{
		memset(input1,0,len1+1);
		input1[0]='1';
	}
	else if (len1==1 && input1[0]=='0')
	{
		input1[0]='0';
	}
	else
	{
		Reverse(input2);
		temp=new char[len1+1];
		memset(temp,0,len1+1);
		memcpy(temp,input1,len1);
		for (int i=0;i<len2;i++)
		{
			
				if((input2[i]-'0')!=0)
					for (int count=0;count<(input2[i]-'0')-1;count++)
						Mul(input1,temp);
				else
				{
					i++;
					int zc=0;
					while(input2[i]=='0'){
						zc++;
						i++;
					}
					for (int y=0;y<(10*(input2[i]-'0'))-1;y++)
						for (int z=0;z<=zc;z++)
						Mul(input1,temp);
				}

		}
		Reverse(input2);
		delete [] temp;	
		if(in2sign==-1)
		{
			temp=new char[strlen(input1)+1];
			memcpy(temp,input1,strlen(input1)+1);
			input1[0]='1';
			input1[1]=0;
			Div(input1,temp,1);
			delete [] temp;
		}

	}

}

//---------------------------------------------------------------------------------------------
void PrintAnswer(char * ans)
{
	int s=strlen(ans);
	int i=0;
	printf("Ans: ");
	while (s--)
	{
		printf("%c",(const char *)ans[i++]);
		
	}
	printf("\r\n");


}

void Reverse(char * input)
{
	char * temp;
	int len=strlen(input);
	temp=new char[len];
	int index=len-1;
	memset(temp,0,len);
	for (int i=0;i<len;i++)
		temp[index--]=input[i];
	memcpy(input,temp,len);
	delete [] temp;

}

int GetSign(char * input)
{
	//call this function before using Reverse Function
	int len=strlen(input);
	if (input[0]=='+')		
		return +1;
	else if (input[0]=='-')
		return -1;
	return 0;
}

void RemoveSign(char * input)
{
	//call this function before using Reverse Function
	int len=strlen(input)-1;
	if (input[0]=='+' || input[0]=='-')
	{
		char *temp=new char[len+1];
		memset(temp,0,len+1);
		memcpy(temp,&input[1],len);
		memcpy(input,temp,len+1);
		delete [] temp;
	}
}

void AddSign(char * input,int sign)
{
	//call this function after calling Reverse Function for the second time
	if (sign==0)return;
	int len=strlen(input);
	char *temp=new char[len+2];
	memset(temp,0,len+2);
	memcpy(&temp[1],input,len);
	temp[0]=(sign==-1?'-':'+');
	memcpy(input,temp,len+2);
	delete [] temp;

}

char IsIn1BigerThanIn2(char * in1,char * in2)
{
	int len1,len2;

	len1=strlen(in1);
	len2=strlen(in2);
	if (len1>len2)
		return 1;
	if (len1<len2)
		return 0;
	if (len1==len2)
	{

		for (int i=0;i<len1;i++)
		{
			if (in1[i]>in2[i])
				return 1;
		}
		return 0;
	}
return 0;
}

void ReadNumber(char * input)
{
#define Backspace 0x08
#define Enter	13
	int index=0;
	char key=0;
	
	std::cin;
	std::cout;

	while (key!=Enter | index==0 |(index==1 & (input[0]=='+' | input[0]=='-')))
	{
		key=_getch();
		if (key==Backspace && index!=0)
		{
			index--;
			input[index]=0;
			cout << "\b \b";
		}
		if (key==Enter && index==1 && (input[0]=='+' | input[0]=='-')) key=0;
		if ((key<'0' || key>'9') && (key!='+' && key!='-'))
			continue;
		if ((key=='-' || key=='+') && index!=0)
			continue;
		
		if (key=='0' && (input[0]=='0' || ((input[0]=='+' | input[0]=='-')&& input[1]=='0'))) continue;
		if (key!='0' && (input[0]=='0' || ((input[0]=='+' | input[0]=='-')&& input[1]=='0'))) 
		{
			input[index-1]=key;
			cout << '\b' <<key;
			continue;
		}
		_putch(key);
		input[index]=key;
		index++;
		if (index>19)break;
	}
	input[index]=0;
	cout << "\r\n";
}

char ReadFunction()
{
#define Backspace 0x08
	char func=0;
	char key;
lbl:
	key=0;
	//( + , - , * , / , %% , ^ , = )
	while (func!='+' && func!='-' && func!='*' && func!='/' && func!='%' && func!='^' && func!='=')
		func=_getch();
	_putch(func);
	while(key!=13)
	{
		key=_getch();
		if (key==Backspace)
		{
			cout << "\b \b";
			func=0;
			goto lbl;
		}
	}
	printf("\r\n");
	return func;
}