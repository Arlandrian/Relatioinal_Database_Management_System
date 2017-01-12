int databasecount(){//Returns current data base count if there is no "databases.txt" creates one
	FILE *fdatabases;
	int database_count;
	
	fdatabases = fopen("databases.txt","r");
	if(!fdatabases){
		fdatabases = fopen("databases.txt","w");
		fputc('0',fdatabases);
		fputc('\n',fdatabases);
		fclose(fdatabases);
		return 0;
	}
		
	fscanf(fdatabases,"%d\n",&database_count);
	fclose(fdatabases);
	return database_count;
}
int controlDatabase(char name[]){//controls the database list if the database we want to create exist returns 1 if exist else returns 0
	char temp[25];
	int databaseCount,i;

	FILE *databases;
	databases = fopen("databases.txt","r");
	if(!databases)
		return 0;
		
	fscanf(databases,"%d\n",&databaseCount);
	
	for(i=0;i<databaseCount;i++){
		fscanf(databases,"%s\n",&temp);
		if( strcmp(temp,name) == 0){
			fclose(databases);
			return 1;
		}		
	}
	fclose(databases);
	return 0;
}
char printMainMenu(){//prints main menu and returns the choice
	char a;
	printf("Chose an Option\n");
	printf("1.Display Data Bases\n");
	printf("2.Create a Data Base\n");
	printf("3.Press q for exit...\n");
	a=getch();
//	while(a < 49 || a > 51)
	//	a=getch();
	return a;
}
char printMenu2(){
	char a;
	printf("1.Display tables\n");
	printf("2.Create a new table\n");
	printf("3.Go back to Previous Menu\n");
	a=getch();
//	while(a < 49 || a > 51)
	//	a=getch();
	return a;
}
char printMenu3(){
	char a;
	printf("What do you want to do with this table?\n");
	printf("1.Delete it and its contents\n");
	printf("2.Insert a new row\n");
	printf("3.Display Table\n");
	printf("4.Delete Row(s)\n");
	printf("5.Update Row(s)\n");
	printf("6.Add primary key functionality to the Row(s)\n");
	printf("7.Go back to Previous Menu\n");
	a=getch();
//	while(a < 49 || a > 55)
	//	a=getch();
	
	return a;
}

void createFolder(char database_name[]){//creates a new folder
	char folder[32];

	sprintf(folder,"mkdir %s",database_name);
	system(folder);//creating a new folder
}