#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
        
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
        
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
        
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
        
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
        
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
        
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
        
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
        
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] 
        != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return  - 1;
}


void board()
{

    cout<<"\t\t\t\t\n\n\t          Tic Tac Toe\n\n";

    cout<<"            CLIENT (X)  -  SERVER (O)\n\n\n";


    cout<<"\t\t    |     |     \n";
    cout<<"\t\t "<< square[1]<<"  | "<<square[2]<<"   |  "<<square[3] <<"\n";

    cout<<"\t\t____|_____|______\n";
    cout<<"\t\t    |     |     \n";

    cout<<"\t\t "<< square[4]<<"  | "<<square[5]<<"   |  "<<square[6] <<"\n";

    cout<<"\t\t____|_____|_____\n";
    cout<<"\t\t    |     |     \n";

    cout<<"\t\t "<<square[7]<<"  | "<<square[8]<<"   |  "<<square[9] <<"\n";

    cout<<"\t\t    |     |     \n";
}


int main()
{
    FILE *p;
    p=fopen("score.txt","a+");
    fclose(p);
    char player1[50],player2[50];
    int player=1;
    int choice,score=-1;
    char symbol;
	int csid;
	char str[100];
	int cid;
	int msgbyte;
	int a,b,s;
	int i;
	char mark;
	
   // rules();
    cout<<"\n\nType 1 to start the game:-\nType 2 to view leader board:-\n";
    cin>>s;
    if(s==2)
    {
leader:
	int cho;
        cout<<"\n\n";
        cout<<"\tLEADERBOARD\n\n";
        char c;
        p=fopen("score.txt","r");
	cout<<"\n";
        while((c=getc(p))!=EOF)
        {
            cout<<c;
        }
	cout<<"\n";
        fclose(p);
		cout<<"\n\nPress 1 to start the game:- ";
        cin>>cho;
        if(cho==1)
            goto jump;
        else
            getchar();
	}
	if(s==1)
	{
	jump:
		csid=socket(AF_INET,SOCK_STREAM,0);
		if(csid==-1)
		{
			cout<<"IN SOCKET CREATION IN CLIENT SIDE FAILURE\n";
			exit(0);
		}
		cout<<"IN SOCKET CREATION IN CLIENT SIDE SUCCESSFUL\n";
		
		struct sockaddr_in csadd;
		csadd.sin_family=AF_INET;
		csadd.sin_port=htons(6999);
		csadd.sin_addr.s_addr=inet_addr("10.0.2.15");
		int c=connect(csid,(struct sockaddr*)&csadd,sizeof(csadd));
		if(c==0)
		{
			cout<<"CONNECTION ESTABLISHMENT SUCCESSFUL\n";
		}
		if(c==(-1))
		{
			cout<<"CONNECTION ESTABLISHMENT UNSUCCESSFUL\n";
			exit(0);
		}

		i = checkwin();
		
		while(i!=1)
		{		
			board();
			cout<<"CLIENT Please Enter Your Choice\n";
			cin>>choice;
			if(!(choice>=1 && choice<=9))
			{

			   cout<<"Invalid move \n";
				cout<<"please enter a valid choice between 1-9\n";
			   cin>>choice;
			}
			
			mark='X';
			if (choice == 1 && square[1] == '1')
				square[1] = mark;
				
			else if (choice == 2 && square[2] == '2')
				square[2] = mark;
				
			else if (choice == 3 && square[3] == '3')
				square[3] = mark;
				
			else if (choice == 4 && square[4] == '4')
				square[4] = mark;
				
			else if (choice == 5 && square[5] == '5')
				square[5] = mark;
				
			else if (choice == 6 && square[6] == '6')
				square[6] = mark;
				
			else if (choice == 7 && square[7] == '7')
				square[7] = mark;
				
			else if (choice == 8 && square[8] == '8')
				square[8] = mark;
				
			else if (choice == 9 && square[9] == '9')
				square[9] = mark;
				
			
			msgbyte=send(csid,&choice,sizeof(choice),0);
			board();

		
			msgbyte=recv(csid,&choice,sizeof(choice),0);
			
			p=fopen("score.txt","a+");
			if(choice==10)
			{
				cout<<"You win";
				cout<<"\n";
				fprintf(p,"\t\nClient\n");
				cout<<"\n";
				getchar();
				fclose(p);
				close(csid);
				goto leader;
			}
			mark='O';
			if (choice == 1 && square[1] == '1')
					square[1] = mark;
				
				else if (choice == 2 && square[2] == '2')
					square[2] = mark;
				
				else if (choice == 3 && square[3] == '3')
					square[3] = mark;
				
				else if (choice == 4 && square[4] == '4')
					square[4] = mark;
				
				else if (choice == 5 && square[5] == '5')
					square[5] = mark;
				
				else if (choice == 6 && square[6] == '6')
					square[6] = mark;
				
				else if (choice == 7 && square[7] == '7')
					square[7] = mark;
					
				else if (choice == 8 && square[8] == '8')
					square[8] = mark;
				
				else if(choice == 9 && square[9] == '9')
					square[9] = mark;
				


			board();
			i = checkwin();
			cout<<"\n\n"<<i;
			p=fopen("score.txt","a+");
			if(i==1)
			{	board();
				int flag=11;
				cout<<"server win";
				cout<<"\n";
				fprintf(p,"\t\nServer\n");
				cout<<"\n";
				getchar();
				fclose(p);
				msgbyte=send(csid,&flag,sizeof(flag),0);
				close(csid);
				goto leader;
			}
			
		
		}
		close(csid);
		return 0;
	}  

}
        
