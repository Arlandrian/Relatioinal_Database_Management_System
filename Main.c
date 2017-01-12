/**
@file
Programming Languages fall2016 TermProject.
*/
Relational Database System :A system that user can create databases and tables or edit existing databases and tables...
#include <stdio.h>
#include <stdlib.h>
#include "fun.h"
#include "fun2.h"
#include <string.h>

int main(int argc, char *argv[]) {
	char main,menu2,menu3,where;
	int i,selectedDatabase,selectedTable,selection,temp;
	
	system("color 70");
	do{
		main = printMainMenu();
		switch( main ){
			
			case '1':
				system("cls");
				if(displayDatabaseList() == 0){//If there is no database to show, program will take user to main menu
					menu2 = '3';
					getch();
					break;
				} 
				printf("Please Select a Database: \n");
				scanf("%d",&selectedDatabase);
					
				do{
					menu2=printMenu2();
					printf("%c Selected\n",menu2);
					switch( menu2 ){
						case '1':
							//DisplayTable
							system("cls");							
							selectedTable = displayTableList(selectedDatabase);
							system("cls");
							do{
								menu3=printMenu3();
								printf("%s Is Selected\n",findTableName(selectedDatabase,selectedTable));
								switch(menu3){
									case '1'://Delete table
										deleteTable(selectedDatabase,selectedTable);	
										printf("Table Deleted Succesfully...\n");
										getch();menu3 = '7';
										break;
									case '2'://Insert Row
										system("cls");
										printf("How many rows do you want to insert:\n");
										scanf("%d",&temp);
										for( i = 0 ; i < temp ; i++){										
											insertRow(selectedDatabase,selectedTable);										
										}
										break;
									case '3':
										system("cls");
										displayTable(selectedDatabase,selectedTable);
										getch();										
										break;
									case '4':
										system("cls");
										displayTable(selectedDatabase,selectedTable);
										printf("1.Select with indexes:\n");
										printf("2.select with names:\n");
										where='0';
										where=getch();
										
										if(where == '1'){
											printf("How many rows do you want to delete:\n");
											scanf("%d",&temp);
											for( i = 0 ; i < temp ; i++){
												printf("Select the row you want to delete:\n");
												scanf("%d",&selection);
												deleteTableRow(selectedDatabase,selectedTable,selection-1);
												system("cls");
												displayTable(selectedDatabase,selectedTable);
											}
										}
										if(where =='2'){
											
											whereDeleteUpdate(selectedDatabase,selectedTable,menu3);																					
										}		
										
										break;
									case '5':
										system("cls");
										displayTable(selectedDatabase,selectedTable);
										printf("1.Select with indexes:\n");
										printf("2.select with names:\n");
										where='0';
										where=getch();
																		
										if(where == '1')	{
											printf("How many rows do you want to Update:\n");
											scanf("%d",&temp);	
											for( i = 0 ; i < temp ; i++){
												printf("Select the row you want to Update:\n");
												scanf("%d",&selection);
												updateRow(selectedDatabase,selectedTable,selection-1);
												system("cls");
												displayTable(selectedDatabase,selectedTable);
											}
										}
										if(where == '2'){
											whereDeleteUpdate(selectedDatabase,selectedTable,menu3);																					
										}
										
										break;
									case '6':
										system("cls");
										addPK(selectedDatabase,selectedTable);										
										break;
									default:
										printf("Please Enter Right Entry\n");getch();
										break;
								}
								system("cls");
							}while(menu3 != '7');
								
							break;
						case '2':
							//CreateTable
							system("cls");
							createTable(selectedDatabase);
							printf("Table has been created Succesfully.");getch();	
							break;
						case '3':
							menu2='3';				
							break;		
					}
					system("cls");
				}while(menu2 != '3');
				
				
				
				break;
				
			case '2':
				//Create a new data base
				system("cls");
				createDatabase();
				printf("Data Base Has been created Succesfully.\n");getch();
				break;
			
			case 'q':
				break;
					
			default:
				printf("You have entered wrong entry please enter again.");getch();
				system("cls");
				break;
				
		}
		system("cls");
	}while(main != 'q');
	printf("Program Ended...");getch();
	return 0;
}
//TEMERIA WILL BE VICTORIOUS!!!

