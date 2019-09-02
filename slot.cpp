/****************************************

Grade 11 Final Project - SLOT MACHINE

@author Atharva Patil
Written on 4th March 2018

****************************************/

#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<iomanip.h>
#include<constrea.h>

int main()
{
	void spin(int &coins); //spins the wheel
	void space(int);

	char ch;
	int coins=1000; //player starts with 1000 coins

	do
	{
		coins-=100; //player uses 100 coins to play once
		clrscr();
		spin(coins);

		cout << '\n';
		do
		{
			cout << '\n';
			space(28);
			cout << "Continue? (y)YES (n)NO: ";
			ch=getch();
		}while(ch!='y'&&ch!='n');

	}while(ch=='y'&&coins>=100);

	if(ch=='y') //when player becomes bankrupt
	{
		space(29);
		cout << "G A M E  O V E R";
		getch();
	}
  
  return 1;
}

int a; // current iteration (0-51 per spin)

void spin(int &coins)
{
	void print(int rand[9], int, int &coins);
	void random_no(int rand[9]);
	void blink(int rand[9], int arr[9], int, int, int, int);

	int time=70;

	clrscr();
	randomize();
	for(a=0; a<=51; a++)
	{
		clrscr();

		int rand[9];

		if(a<=45)
			random_no(rand); //generates random no. every loop

		int wins; // no. of matches across column/row/diagonal
		int index; // index no. of mid[]

		int arr[9];  // duplicate array used for comparison
		for(int i=0; i<9; i++)
			arr[i]=rand[i];

		if(arr[0]==arr[1]&&arr[1]==arr[2])
		{
			wins++;
			index=0;
			blink(rand, arr, 0, 1, 2,index);
		}

		if(arr[3]==arr[4]&&arr[4]==arr[5])
		{
		  wins++;
			index=1;
			blink(rand, arr, 3, 4, 5,index);
		}

		if(arr[6]==arr[7]&&arr[7]==arr[8])
		{
			wins++;
			index=2;
			blink(rand, arr, 6, 7, 8,index);
		}

		if(arr[0]==arr[3]&&arr[3]==arr[6])
		{
			wins++;
			index=3;
			blink(rand, arr, 0, 3, 6,index);
		}

		if(arr[1]==arr[4]&&arr[4]==arr[7])
		{
			wins++;
			index=4;
			blink(rand, arr, 1, 4, 7,index);
		}

		if(arr[2]==arr[5]&&arr[5]==arr[8])
		{
			wins++;
			index=5;
			blink(rand, arr, 2, 5, 8,index);
		}

		if(arr[0]==arr[4]&&arr[4]==arr[8])
		{
			wins++;
			index=6;
			blink(rand, arr, 0, 4, 8,index);
		}

		if(arr[2]==arr[4]&&arr[4]==arr[6])
		{
			wins++;
			index=7;
			blink(rand, arr, 2, 4, 6,index);
		}

		if(a<45)
			wins=0;
		if(a==51)
			wins/=6;

		print(rand, wins, coins);

		delay(time);
		if(a>35&&a<=45)
			time+=30;    //spinning speed slows down at the end

		if(a>45&&wins==0)    // no blinking
			time=0;

		else if(wins>0&&a>45) // blinking
			time=300;
      }
}

void print(int rand[9], int wins, int &coins)
{
	void space(int);
	void symbol(int);

	textcolor(RED);
	cout << "\n\n\n";
	space(28);
	cout << "*****(SLOT MACHINE)*****\n";
	cout << setw(52) << "100 COINS PER PLAY\n\n\n";

	space(31);
	cout << char(201);

	int i;
	// line 1
	for(i=0; i<15; i++)
		cout << char(205);
	cout << char(187) << '\n';

	// line 2
	space(31);
	cout << char(186);
	symbol(rand[0]);
	symbol(rand[1]);
	symbol(rand[2]);
	cout << "   " << char(186) << '\n';

	// line 3
	space(31);
	cout << char(186);
	symbol(rand[3]);
	symbol(rand[4]);
	symbol(rand[5]);
	cout << "   " << char(186) << '\n';

	// line 4
	space(31);
	cout << char(186);
	symbol(rand[6]);
	symbol(rand[7]);
	symbol(rand[8]);
	cout << "   " << char(186) << '\n';

	// line 5
	space(31);
	cout << char(200);
	for(i=0; i<15; i++)
	     cout << char(205);
	cout << char(188);

	int winnings=0; // no. of coins the player wins
	if(a==51)
	{
		switch(wins)
		{
			case 0: break;
			case 1: winnings=200;
				break;
			case 2: winnings=350;
				break;
			case 3: winnings=600;
				break;
			case 4: winnings=1000;
				break;
			case 5: winnings=2000;
				break;
			case 6: winnings=5000;
				break;
			case 7: winnings=10000;
				break;
			case 8: winnings=50000;
				break;
		}

		coins+=winnings;
		cout << "\n\n";
		if(wins==0)
			space(32);
		else
			space(31);
		cout << "You won " << winnings << " Coins!";
		}

	if(wins>=1)
		textcolor(GREEN);   // everything turns green if player wins

	cout << "\n\n";
	space(34);
	cout << "Coins: " << coins;
}

void random_no(int rand[9])
{
	// Diff. cols start/end spinning at diff. times

	// Column 1
	if(a<=30)
	{
		rand[0] = random(4);
		rand[3] = random(4);
		rand[6] = random(4);
	}

	// Column 2
	if(a==0||(a>10&&a<38))
	{
		rand[1] = random(4);
		rand[4] = random(4);
		rand[7] = random(4);
	}

	// Column 3
	if(a==0||a>20)
	{
		rand[2] = random(4);
		rand[5] = random(4);
		rand[8] = random(4);
	}
}

int mid[8]; // array to store values during blinking

void blink(int rand[9], int arr[9], int num1,  
	   int num2, int num3, int index)         //blinking
{
	if(a%2==0&&a>45)
	{
		mid[index]=arr[num1];
		rand[num1]=4;
		rand[num2]=4;
		rand[num3]=4;
	}

	else if(a%2==1&&a>45)
	{
		rand[num1]=mid[index];
		rand[num2]=mid[index];
		rand[num3]=mid[index];
	}
}

void symbol(int dig) // accepts rand[] value and prints corresponding symbol
{
	cout << "   ";
	switch(dig)
	{
		case 0: cout << '*';
			break;
		case 1: cout << '#';
			break;
		case 2: cout << '$';
			break;
		case 3: cout << '7';
			break;
		case 4: cout << ' ';
			break;
	}
}

void space(int num) // to overcome the limitations of setw()
{
	for(int i=0; i<num; i++)
		cout << ' ';
}
