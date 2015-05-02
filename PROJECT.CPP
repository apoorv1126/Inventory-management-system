                                       #include<iostream.h>
#include<conio.h>
#include<iomanip.h>
#include<fstream.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<stdio.h>
#include <time.h>
#include<ctype.h>

fstream inoutfile;

//Menu Global Item
//Macros defined
#define pixTOrc(x) (8*(x-1))  //convert pixel into row and col format
#define INC 5  //Increment Distance Between Menu Items
#define ROW 15 //Row Value for Menu Item
#define COL 3 //Column Value for Menu Item

// To display the Inventory Main menu options
typedef char option[15];
option mainMenu [ ] =
{
 "New Record",
 "Display",
 "Search",
 "Updation",
 "Deletion",
 "Analysis",
 "Exit"
} ;


/*-------------------Inventory Class--------------------*/

class Inventory
{
	char itemNo [4] ,itemName [20] ;
	int qty;
	double price, amt ;

	public :

	char *getno ( )
	{ return itemNo ; }
	char *getitem( )
	{ return itemName ; }
	double getamt ( )
	{ return amt ; }
	void getdata ( ) ;
	void showdata (int , int ) ;
	void showspecific ( ) ;
	void alterspecific (char * , char *) ;
} ;

void Inventory :: getdata ( )
{
	gotoxy (30,12);
	cout<<"Enter Item Number : ?\b";
	cin>>itemNo;
	gotoxy (30,14);
	cout<<"Enter Item Name : ?\b";
	cin>>itemName;
	gotoxy (30,16);
	cout<<"Enter Quantity : ?\b";
	cin>>qty;
	gotoxy (30,18);
	cout<<"Enter Price : ?\b";
	cin>>price;
	amt = price * qty;
}

void Inventory :: showdata (int x , int y)
{
	gotoxy (x,y);
	cout.setf (ios::left,ios::adjustfield);
	cout<<setw(4)<<itemNo;
	cout.setf (ios::left,ios::adjustfield);
	cout<<setw(10)<<itemName;
	cout.setf (ios::right,ios::adjustfield);
	cout<<setw(5)<<qty;
	cout.setf (ios::right,ios::adjustfield);
	cout.setf (ios::showpoint);
	cout.setf (ios::fixed,ios::floatfield);
	cout<<setprecision(2)<<setw(13)<<price;
	cout.setf (ios::right,ios::adjustfield);
	cout.setf (ios::showpoint);
	cout.setf (ios::fixed,ios::floatfield);
	cout<<setprecision(2)<<setw(13)<<amt;
}

void Inventory :: showspecific ( )
{
	gotoxy (30,13);
	cout<<"--Search Item Found--";
	gotoxy (30,15);
	cout<<"Item No : ";
	cout.setf (ios::left,ios::adjustfield);
	cout<<itemNo;
	gotoxy (30,17);
	cout<<"Item Name : ";
	cout.setf (ios::left,ios::adjustfield);
	cout<<itemName;
	gotoxy (30,19);
	cout<<"Quantity : ";
	cout<<qty;
	cout.setf (ios::right,ios::adjustfield);
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed,ios::floatfield);
	gotoxy(30,21);
	cout<<"Price : ";
	cout<<setprecision(2)<<price;
	gotoxy(30,23);
	cout<<"Amount : ";
	cout.setf(ios::right,ios::adjustfield);
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed,ios::floatfield);
	cout<<setprecision(2)<<amt;
}

void Inventory :: alterspecific(char itmno[2],char itmname[20])
{
	strcpy(itemNo,itmno);
	strcpy(itemName,itmname);
	gotoxy(30,16);
	cout<<"Enter Quantity : ?\b";
	cin>>qty;
	gotoxy(30,18);
	cout<<"Enter Price : ?\b";
	cin>>price;
	amt = price * qty;
}

/*--------------Menu and all other functions Code--------------*/

//Displays Graphic text in delaying fashion
void displaydelay(int x,int y,const char *ch,int delayTime)
{
   char d[2];
   int len=strlen(ch);
   for(int i=0;i<=len;i++)
   {
     d[0]=ch[i];
     d[1]='\0';
     outtextxy(x+pixTOrc((i+1)*2),y,d);
     delay(delayTime);
    }
}

//Function which shows loading...progress bar
void loading()
{
	   int i=1,j,clrflag=0;
	   float cnt;
	   setcolor(YELLOW);
	   j=100;
	   cnt=0;
	   outtextxy(270,300,"LOADING ");
	   setcolor(BLUE);
	   for(i=j;i<520;i++)
	   {
	      gotoxy(40,25);
	      cout<<int(cnt);
	      rectangle(j,375,i,405);
	      if(i==(j+11))
	      {
		 j=j+2;
		 i=j;
		 if(clrflag==1)
		 {
		   clrflag=0;
		   setcolor(BLUE);
		 }
		 else
		 {
		   clrflag=1;
		   setcolor(CYAN);
		 }
		 cnt=cnt+0.49;
	      }
	   }
   delay(1500);
}


// Function to displays all the menu prompt
//messages from the pointer array of option a[ ]
void normaltext(int x,int y,char *str)
{
    x = pixTOrc(x);
    y = pixTOrc(y);
    outtextxy(x,y,str);
}

// Function to move the cursor on the menu prompt
//with an alternate colour
void colourtext(int x,int y,char *str)
{
	x = pixTOrc(x);
	y = pixTOrc(y);
	setcolor(YELLOW);  //Selected Item
	sound(400);
	delay(100);
	nosound();
	outtextxy(x,y,str);
	setcolor(WHITE); //Unselected Item
	sound(500);
	delay(100);
	nosound();
}

//Keep Track of which arrow key is displayed
char menu()
{
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	setcolor(WHITE);  //Initial Menu Item Color
	int i,done;
	time_t t;
	for(i = 1; i < 7; i++)
	    normaltext(COL, (i*INC)+ROW, mainMenu[i]);
	colourtext(COL,ROW, mainMenu[0]);
	i = done = 0;
	do
	{
			/**status Bar **/
			//Message will be displayed as status bar guide-line
			setfillstyle(SOLID_FILL,BLUE);
			settextstyle(SMALL_FONT,HORIZ_DIR,5);
			bar(pixTOrc(2),pixTOrc(52.5),pixTOrc(75),pixTOrc(55));
			setcolor(LIGHTCYAN);
			switch(i){
				case 0 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Add New Item to Inventory");
					 break;
				case 1 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Display All Items available in Inventory");
					 break;
				case 2 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Search for a specific Item in Inventory");
					 break;
				case 3 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Modify the quantiy and price information of Item available in Inventory");
					 break;
				case 4 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Deletion of item from Inventory ");
					 break;
				case 5 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Managerial Analysis To take Decisions...");
					 break;
				case 6 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Close the Program");
					 break;
			}
			/**status Bar ends**/

			/*****Time display****/
			//Displaying Time logic
			 while(!kbhit())
			 {
			      time(&t);
			      bar(pixTOrc(2),pixTOrc(55.5),pixTOrc(75),pixTOrc(58));
			      outtextxy(pixTOrc(5),pixTOrc(56),ctime(&t));
			      delay(200);
			 }
			 /*****Time display Ends****/

			 //Restore Orignal Color and Font Setting
			 setcolor(WHITE);
			 settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);

		int key = getch();
		switch (key)
		{

			case 00:
				key = getch();
				switch (key)
				{
					case 72:
						normaltext(COL, (i*INC)+ROW, mainMenu[i]);
						i--;
						if (i == -1)
							i = 6;
						colourtext(COL,(i*INC)+ROW,mainMenu[i]);
						break;
					case 80:
						normaltext(COL, (i*INC)+ROW, mainMenu[i]);
						i++;
						if (i == 7)
							i = 0;
						colourtext(COL, (i*INC)+ROW, mainMenu[i]);
						break;
				}
				break;
			case 13:
				done = 1;
		}
	}
	while (!done);
	return(i+49);
}

/* The function is used to display the main menu*/
void control_menu( )
{
     char choice;
	do
	{
		choice = menu();
		switch (choice)
		{
		   case '1':    //Add New Item
				Inventory additem;
				inoutfile.open("c:\\stock.dat",ios::ate | ios::out | ios::binary);
				inoutfile.seekg(0,ios::end);
				setfillstyle(SOLID_FILL,BLACK);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				setcolor(YELLOW);
				outtextxy(pixTOrc(40),pixTOrc(15),"Add New Item");
				additem.getdata();
				char ch;
				cin.get(ch);
				inoutfile.write((char *) &additem, sizeof(additem));
				gotoxy(30,22);
				cout<<"-> Item Added in Inventory <-";
				flush(inoutfile);
				inoutfile.close();
				getch();
				setfillstyle(SOLID_FILL,LIGHTGRAY);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				break;

		   case '2':    //Display All Item in inventory
				Inventory showitem;
				static int count=0;
				count++;
				inoutfile.open("c:\\stock.dat",ios::ate| ios::in | ios::binary);
				setfillstyle(SOLID_FILL,BLACK);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				setcolor(YELLOW);
				outtextxy(pixTOrc(40),pixTOrc(15),"Inventory Stock");
				inoutfile.seekg(0,ios::beg); //goto start of file
				gotoxy(28,11);
				cout<<" No  "<<" Item Name  "<<"  Qty "<<"      Price "<<"      Amount";
				gotoxy(28,12);
				cout<<"-----------------------------------------------";
				int x=30,y=13;
				while(inoutfile){
					inoutfile.read((char *) &showitem, sizeof(showitem));
					if(!inoutfile.eof())
						showitem.showdata(x,y++);
				}
				inoutfile.close( );
				getch( );
				setfillstyle(SOLID_FILL,LIGHTGRAY);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				break;

		   case '3':    //Search for specific Item in inventory
				Inventory srchitem;
				inoutfile.open("c:\\stock.dat",ios::ate |ios::in| ios::out | ios::binary);
				setfillstyle(SOLID_FILL,BLACK);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				setcolor(YELLOW);
				outtextxy(pixTOrc(40),pixTOrc(15),"Search Item");
				gotoxy(30,11);
				cout<<"Enter Item Name : ";
				char name[20];
				cin>>name;
				inoutfile.seekg(0,ios::beg);
				int found=0;
				while(inoutfile){
					inoutfile.read((char *) &srchitem, sizeof(srchitem));
					if(strcmp(srchitem.getitem(),name)==0){
						found=1;
						srchitem.showspecific();
					}
				}
				if(found==0){
					gotoxy(30,15);
					cout<<"SEARCH ITEM NOT FOUND";
				}
				inoutfile.close();
				inoutfile.close();
				getch();
				setfillstyle(SOLID_FILL,LIGHTGRAY);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				break;

		   case '4':    //Modify the status of item in inventory
				Inventory alteritem;
				inoutfile.open("c:\\stock.dat",ios::ate |ios::in| ios::out | ios::binary);
				setfillstyle(SOLID_FILL,BLACK);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				setcolor(YELLOW);
				outtextxy(pixTOrc(40),pixTOrc(15),"Modify Item Details");
				gotoxy(30,13);
				cout<<"Enter Item Name : ";
				cin>>name;
				inoutfile.seekg(0,ios::beg);
				found=0;
				int rec=0;
				while(inoutfile){
					rec++;
					inoutfile.read((char *) &alteritem, sizeof(alteritem));
					if(strcmp(alteritem.getitem(),name)==0){
						found=1;
						int location = (rec-1) * (sizeof(alteritem));
						inoutfile.seekp(location);
						alteritem.alterspecific(alteritem.getno(),alteritem.getitem());
						cin.get(ch);
						inoutfile.write((char *) &alteritem, sizeof(alteritem));
						break;
					}
				}
				if(found==0){
					gotoxy(30,15);
					cout<<"ITEM NOT FOUND -- NO Modification Possible";
				}
				else{
					gotoxy(30,24);
					cout<<"ITEM Updated Successfully";
				}
				inoutfile.close();
				inoutfile.close();
				getch();
				setfillstyle(SOLID_FILL,LIGHTGRAY);				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				break;

		   case '5':    //Delete Item in inventory
				Inventory delitem;
				inoutfile.open("c:\\stock.dat",ios::ate |ios::in| ios::out | ios::binary);
				setfillstyle(SOLID_FILL,BLACK);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				setcolor(YELLOW);
				outtextxy(pixTOrc(40),pixTOrc(15),"Delete  Item");
				gotoxy(30,11);
				cout<<"Enter Item Name : ";
				cin>>name;
				inoutfile.seekg(0,ios::beg);
				fstream tempFile("c:\\stock1.dat",ios::ate |ios::out| ios::out | ios::binary);
				found=0;
				while(inoutfile){
					inoutfile.read((char *) &delitem, sizeof(delitem));
					if(strcmp(delitem.getitem(),name)!=0 && !inoutfile.eof())
					{
						cin.get(ch);
						tempFile.write((char *) &delitem, sizeof(delitem));
					}
					else
					{
						gotoxy(30,18);
						cout<<"Wait Please...Deletion may take few seconds";
						found=1;
					}
				}
				if(found==0)
				{
					gotoxy(30,15);
					cout<<"ITEM NOT FOUND -- No Deletion Possible";
				}
				else
				{
					gotoxy(30,15);
					cout<<"ITEM FOUND -- Deleted Successfully";
				}
				tempFile.flush();
				inoutfile.flush();
				tempFile.close();
				inoutfile.close();
				remove("c:\\stock.dat");
				rename("c:\\stock1.dat","c:\\stock.dat");
				getch();
				setfillstyle(SOLID_FILL,LIGHTGRAY);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				break;


		   case '6':    //Analysis of Inventory Items
Inventory anitem;
				inoutfile.open("c:\\stock.dat",ios::ate |ios::in| ios::binary);
				setfillstyle(SOLID_FILL,BLACK);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				setcolor(YELLOW);
				outtextxy(pixTOrc(40),pixTOrc(15),"Managerial Analysis");
				gotoxy(30,16);
				int last=inoutfile.tellg();
				int n = last/sizeof(anitem);
				cout<<"Total Items in Inventory : "<<n;
				inoutfile.seekg(0,ios::beg); //goto start of file
				double total=0.0;
				while(inoutfile){
					inoutfile.read((char *) &anitem, sizeof(anitem));
					if(!inoutfile.eof())
					    total=total + anitem.getamt();
				}
				inoutfile.close();
				gotoxy(30,18);
				cout<<"Total Investements : "<<total;
				getch();
				setfillstyle(SOLID_FILL,LIGHTGRAY);
				bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
				break;

		   case '7' :   //Exit
				goto out;
	   }
	  } while (choice != 7);
		out:
}


//At BEGINNING the cover function will be called
void cover()
{
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(0,0,640,480);
	int i,j;
	setfillstyle(LINE_FILL,DARKGRAY);
	for(i=0,j=80;i<50||j>50;i++,j--)
	{
		bar(pixTOrc(2),pixTOrc(10),pixTOrc(i),pixTOrc(55));
		delay(10);
		bar(pixTOrc(j),pixTOrc(10),pixTOrc(80),pixTOrc(55));
		sound(400+(i*50));
		delay(10);
		nosound();
	}
	float qw;
	settextstyle(SMALL_FONT,HORIZ_DIR,9);
	setcolor(BLUE);
	displaydelay(pixTOrc(23.00),pixTOrc(1),"COMPUTER PROJECT",10);
	for(qw=23.01;qw<=23.35;qw=qw+0.01)
	displaydelay(pixTOrc(qw),pixTOrc(1),"COMPUTER PROJECT",0);
	setcolor(GREEN);
	displaydelay(pixTOrc(25),pixTOrc(5),"L.I.S.T BHOPAL",10);
	setcolor(RED);
	for(qw=25.01;qw<=25.35;qw=qw+0.01)
	displaydelay(pixTOrc(qw),pixTOrc(5),"L.I.S.T BHOPAL",0);
	setcolor(LIGHTGREEN);
	displaydelay(pixTOrc(5),pixTOrc(10),"INVENTORY MANAGEMENT SYSTEM",10);
	for(qw=5.01;qw<=5.25;qw=qw+0.01)
	displaydelay(pixTOrc(qw),pixTOrc(10),"INVENTORY MANAGEMENT SYSTEM",0);
	setcolor(YELLOW);
	displaydelay(pixTOrc(5),pixTOrc(20),"By : Apoorv Chitray",10);
	displaydelay(pixTOrc(5),pixTOrc(25),"     Markandey singh     ",10);
	displaydelay(pixTOrc(5),pixTOrc(30),"     Vikash Kumar",10);
	displaydelay(pixTOrc(5),pixTOrc(35),"     Anoop Prabhakaran",10);
	setcolor(LIGHTCYAN);
	displaydelay(pixTOrc(5),pixTOrc(40),"6th Sem CSE",10);
	setcolor(LIGHTMAGENTA);
	outtextxy(pixTOrc(6),pixTOrc(45),"Year 2008-12");
	for(qw=6.01;qw<=6.25;qw=qw+0.01)
	outtextxy(pixTOrc(qw),pixTOrc(45),"Year 2008-12");
	delay(2000);
	getch();
}
/*-------------------MAIN FUNCTION--------------------*/
void main()
{       int i,j;
	int gd=DETECT,gm=0;
	initgraph(&gd,&gm,"c:\\tc\\BGI");

/*--------Title of Inventory Management system--------*/
	clrscr();
	cover();
	for(int v=0;v<81;v++)
	cout<<"\n";
	loading();
	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(0,0,640,480);
	setcolor(DARKGRAY);
	rectangle(0,0,639,480);
	rectangle(1,1,638,479);
	setcolor(BLACK);
	rectangle(2,1,637,478);
	rectangle(3,1,636,477);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
	setcolor(BLUE);
	outtextxy(pixTOrc(8),pixTOrc(2),"Inventory Management System");
	setfillstyle(LINE_FILL,DARKGRAY);
	for(i=15,j=70;i<40||j>40;i++,j--)
	{
		bar(pixTOrc(8),pixTOrc(7),pixTOrc(i),pixTOrc(7.5));
		delay(10);
		bar(pixTOrc(j),pixTOrc(7),pixTOrc(70),pixTOrc(7.5));
		delay(20);
	}

	bar(pixTOrc(2),pixTOrc(14),pixTOrc(20),pixTOrc(50));








/*--------End of title code of Inventory Management system--------*/

	//Calling Menu
	control_menu ( );

	//on exit

	quit:
	closegraph ( );
}
