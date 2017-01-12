
int returnType(char input[]){//Returns input's type 0 string 1 integer 2 double 3 boolean 4 none of these
	
	if( input[1] == '\0' && ( input[0] == 't' || input[0] == 'T' || input[0] == 'f' || input[0] == 'F'))//control boolean 
		return 3;
	int i = 0, controlint=0, controlstr=0, controldob=0;
	while( input[i] != '\0'){
		if( input[i] < 58 && input[i] > 47 )
			controlint++;
		if(input[i] == '.')
			controldob++;
		if( (input[i] < 91 && input[i] > 64) || (input[i] < 123 && input[i] > 96) )	
			controlstr++;
		i++;		 
	}
	if(controldob > 1)
		return 4;
	if(controlint > 0 && controlstr == 0 && controldob == 1)
		return 2;
	if(controlint > 0 && controlstr == 0)	
		return 1;
	if(controlstr > 0 && controldob == 0)
		return 0;
	return 4;	
}

void deleteRow(char dir[],int rowIndex){//deletes given line from given text file :example filename"%s/%s.txt or %s.txt
	FILE *temp,*org;
	int counter=0;
	char str[270];
	
	org = fopen (dir,"r");
	temp = fopen("temp.txt","w");

	while( fgets(str,270,org) ){
		
		if( counter != rowIndex)
			fputs(str,temp);
		counter++;
	}
	fclose(temp);
	fclose(org);
	remove(dir);
	rename("temp.txt",dir);
}

char *findDatabaseName(int databaseIndex){//Returns database name that given index if database couldnt be found returns null
	FILE *fdb;
	int databaseCount,i;
	char *databaseName = (char*) malloc(25);
	
	fdb = fopen("databases.txt","r");
	if(!fdb)
		return 0;
		
	fscanf(fdb,"%d\n",&databaseCount);
	for( i = 1 ; i < databaseCount+1 ; i++ ){
		fscanf(fdb,"%s\n",databaseName);
		if( i == databaseIndex ){
			fclose(fdb);
			return databaseName;
		}			
	}
	fclose(fdb);
	return 0;
}

char *findTableName(int databaseIndex,int tableIndex){//Returns Table name that given index if table couldnt be found returns null

	char *databaseName = findDatabaseName(databaseIndex);
	char *tableName = (char*) malloc (25);
	char dir[55];
	int tableCount,i;
	sprintf(dir,"%s\\tables.txt",databaseName);
	FILE *ftable = fopen(dir,"r");
	if(!ftable){
		printf("File Could Not Be Opened...\n");
		getch();
		return 0;
	}	
	fscanf(ftable,"%d\n",&tableCount);
	for( i = 1 ; i < tableCount + 1 ; i++ ){
		fscanf(ftable,"%s\n",tableName);
		if( i == tableIndex){
			fclose(ftable);
			free(databaseName);
			return tableName;
		}
	}
	printf("Table Couldnt Be Found!\n");getch();
	free(databaseName);
	fclose(ftable);
	return 0;
}

int displayTableList(int databaseIndex){//Displays table List from database that given index
	
	char *databaseName = findDatabaseName(databaseIndex);	
	int tableCount,i,selection;
	char tableName[25];
	char dir[55];
	sprintf(dir,"%s\\tables.txt",databaseName);
	
	FILE *fp = fopen(dir,"r");
	fscanf(fp,"%d\n",&tableCount);
	if(!fp || tableCount == 0){
		printf("There is no table to display.\n");
	}
			
	for( i = 0 ; i < tableCount ; i++ ){
		fscanf(fp,"%s\n",tableName);
		printf("%d.%s\n",i+1,tableName);
	}
	printf("Select a table:\n");
	scanf("%d",&selection);
	
	fclose(fp);
	free(databaseName);
	return selection;
}

int displayDatabaseList(){//Displays Database List if there is no database it will return 0 else 1

	FILE *fdatabases;
	int i,database_count;
	char database_name,temp[30];
	
	fdatabases = fopen("databases.txt","r");
	if(!fdatabases){
	
		printf("There is no Data Base to display.\n");
		fclose(fdatabases);	
		return 0;
	}	
	fscanf(fdatabases,"%s\n",&temp);
	database_count=atoi(temp);
	
	for(i=0;i<(database_count);i++){
		fscanf(fdatabases,"%s\n",&temp);	
		printf("%d.%s\n",i+1,temp);
	}
	fclose(fdatabases);
	return 1;
}

char *clearSpaces(char input[]){//returns input string without spaces in the end
	int i=0;
	while(input[i] != ' '){
		i++;
	}
	char ret[i];
	strcpy(ret,input);
	return ret;
}

char *returnElement(int row,int column,int rowCount,int columnCount,FILE *ftable){//returns the element that given row and column(Didnt used in the code)

	if(row >= rowCount || row < 0 || column >= columnCount || column<0){//Controlling if inputs are valid
		printf("Incorrect inputs\n");
		return 0;
	}
	int saveLocation=ftell(ftable);//keeping the indicator's location to not to lose...
	rewind(ftable);
	char temp[270],temp2[25];int i,j;
	fgets(temp,270,ftable);//row count and column count row.
	fgets(temp,270,ftable);//types row
	fgets(temp,270,ftable);//pk row
	fgets(temp,270,ftable);//column names row
	
	for( i = 0 ; i < rowCount ; i++ ){
		fgets(temp,270,ftable);					
		if( i == row ){
			for( j = 0 ; j < 15 ; j++ )
				temp2[j] = temp[ column*15 + j ];

			fseek(ftable,saveLocation,SEEK_SET);	
			return clearSpaces(temp2);	
		}						
	}
}

int findElement(char input[],int columnNumber,int rowCount,int columnCount,FILE *ftable){//finds row index of input and returns it if row doesnt exist returns -1
	if(rowCount == 0)
		return 0;
	int saveLocation=ftell(ftable);//keeping the indicator's location to not to lose...
	rewind(ftable);
	char temp[270];int j,k,i=0;
	fgets(temp,270,ftable);//row count and column count row.
	fgets(temp,270,ftable);//types row
	fgets(temp,270,ftable);//pk row
	fgets(temp,270,ftable);//Column Names row
	char temp2[25];	

	for( k = 0 ; k < rowCount ; k++ ){
		fgets(temp,270,ftable);
		i=0;			
		for( j = 0 ; j < 15 ; j++ ){
			if( temp[ columnNumber*15 + j ] != ' '){
				temp2[i] = temp[ columnNumber*15 + j ];
				i++;
			}			
		}
		temp2[i]='\0';		
		if( strcmp( temp2 , input ) == 0){
			fseek(ftable,saveLocation,SEEK_SET);
			return k;
		}
	}
	fseek(ftable,saveLocation,SEEK_SET);
	return -1;	
}

int controlPK(char input[],int columnNumber,int rowCount,int columnCount,int pks[],FILE *ftable){//if this function returns 1 this means input is not in the selected column 

	if(rowCount == 0)
		return 1;
	if( pks[columnNumber] == 1 ){
		
		if(findElement(input,columnNumber,rowCount,columnCount,ftable) == -1)
			return 1;
	}
	return 0;
}

int isSuitable(char input[],int columnNumber,int rowCount,int columnCount,int types[],int pks[],FILE *ftable){//-1 pk 0 suitable 1 type problem

	if( returnType(input) != types[columnNumber] ){
			if(types[columnNumber] == 0)
				printf("Your Entry is not Suitable with this Column Please Enter a String:\n");
			if(types[columnNumber] == 1)
				printf("Your Entry is not Suitable with this Column Please Enter an Integer:\n");
			if(types[columnNumber] == 2)
				printf("Your Entry is not Suitable with this Column Please Enter a Double:\n ");
			if(types[columnNumber] == 3)
				printf("Your Entry is not Suitable with this Column Please Enter a Boolean: (t/f)\n");
		return 1;
	}
	if(pks[columnNumber] == 1){
		if( controlPK(input,columnNumber,rowCount,columnCount,pks,ftable) == 0 ){
			printf("There is already an entry with this name. Please Enter again: \n");
			return -1;
		}
	}
	return 0;		
}

void displayTable(int selectedDatabase,int selectedTable){//displays selected table
	char *databaseName = findDatabaseName(selectedDatabase);
	char *tableName = findTableName(selectedDatabase,selectedTable);
	int columnCount,rowCount,i;
	char dir[50],temp2[270];
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	
	FILE *ftable = fopen(dir,"r+");
	if(!ftable){
		printf("Table Couldnt be found...\n");getch();
		return ;
	}
	fscanf(ftable,"%d %d\n",&columnCount,&rowCount);
	fgets(temp2,270,ftable);
	fgets(temp2,270,ftable);
	fgets(temp2,270,ftable);
	if(rowCount > 9)
		printf("   %s",temp2);
	else
		printf("  %s",temp2);		
	for( i = 0 ; i < columnCount ; i++ )
		printf("---------------");
	printf("\n");	
	for( i = 0 ; i < rowCount ; i++ ){
		fgets(temp2,270,ftable);
		printf("%d.%s",i+1,temp2);
	}
		
	free(databaseName);
	free(tableName);
	fclose(ftable);
}

void insertRow(int selectedDatabase,int selectedTable){//Inserts a row to selected table

	char *databaseName = findDatabaseName(selectedDatabase);
	char *tableName = findTableName(selectedDatabase,selectedTable);
	int rowCount,columnCount,i,j;
	char dir[50],temp[25],temp2[270];
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	
	FILE *ftable = fopen(dir,"r+");
	if(!ftable){
		printf("Table Couldnt be found...");getch();
		return ;
	}
	fscanf(ftable,"%d %d\n",&columnCount,&rowCount);

	int *pks = (int*)calloc(columnCount,sizeof(int));
	int *types = (int*)calloc(columnCount,sizeof(int));
	
	char **columnNames = (char**)calloc(columnCount,sizeof(char**));
	for( i = 0; i < columnCount ; i++ )
		columnNames[i] = (char*)calloc(25,sizeof(char*));
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		types[i]=temp2[i*2]-48;
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		pks[i]=temp2[i*2]-48;
	if( rowCount != 0 )	
		fgets(temp2,270,ftable);

	for( i = 0; i < columnCount ; i++ ){
		for( j = 0 ; j < 15 ; j++ )
			columnNames[i][j]=temp2[ i*15 + j ];
		strcpy(columnNames[i],clearSpaces(columnNames[i]));
	}	

	fseek(ftable,0,SEEK_END);
	for( i = 0; i < columnCount ; i++ ){
		printf("Column %s:\n",columnNames[i]);
		scanf("%s",temp);
		while( isSuitable(temp,i,rowCount,columnCount,types,pks,ftable) != 0)	
			scanf("%s",temp);					
		
		fprintf(ftable,"%-15s",temp);		
	}	
	fprintf(ftable,"\n");
	fseek(ftable,0,SEEK_SET);
	fprintf(ftable,"%d %d\n",columnCount,rowCount+1);
	printf("Row inserted Successfully...\n");
	getch();
	fclose(ftable);
	free(pks);
	free(types);
	free(databaseName);
	free(tableName);
	free(columnNames);
}

void createTable(int databaseIndex){//creates table in selected database 
	
	char tableName[25],dir[55],dir2[55],columnName[25],temp[270],pk,type;
	char *databaseName = findDatabaseName(databaseIndex);
	int i,j,columnCount,tableCount;
	FILE *ftable;

	printf("Enter the Table Name:\n");
	scanf("%s",&tableName);
	
	sprintf(dir,"%s\\tables.txt",databaseName);
	
	ftable = fopen(dir,"r+");
	if(!ftable){
		ftable = fopen(dir,"w");
		fprintf(ftable,"1 0\n%s\n",tableName);
	}
	else{
		fscanf(ftable,"%d\n",&tableCount);
		rewind(ftable);
		fprintf(ftable,"%d\n",tableCount+1);
		fseek(ftable,0,SEEK_END);
		fprintf(ftable,"%s\n",tableName);
	}
	fclose(ftable);

	sprintf(dir2,"%s\\%s.txt",databaseName,tableName);

	ftable = fopen(dir2,"w+");
	
	printf("Enter the number of column:\n");
	scanf("%d",&columnCount);
	
	char types[columnCount*2+1];
	char pks[columnCount*2+1];
	char Columns[columnCount][25];
	fprintf(ftable,"%d 0\n",columnCount);
	
	for(i = 0 ; i < columnCount ; i++ ){
		system("cls");
		printf("%d.Column Name: \n",i+1);
		scanf("%s",columnName);
		strcpy(Columns[i],columnName);
		
		//Column type
		printf("Choose Column Type:\n");
		printf("0-String\n1-Integer\n2-Double\n3-Boolean\n");
		type = getch();
		while( type != '0' && type != '1' && type != '2' && type != '3'){
			system("cls");
			printf("Please Enter Correct Entry!\n");
			printf("Choose Column Type:\n");
			printf("0-String\n1-Integer\n2-Double\n3-Boolean\n");
			type = getch();
		}
		types[i*2] = type;		
		types[i*2+1] =' ';
		
		printf("Is this column a primary key(y/n)?\n");
		pk = getch();
		while( pk != 'y' && pk != 'Y' && pk != 'n' && pk != 'N'){
			system("cls");
			printf("Please Enter Y or N:\n");
			scanf("%s",&pk);
		}
		if(pk == 'y' || pk == 'Y')
			pks[i*2] = '1';
				
		else
			pks[i*2] = '0';
		
		pks[i*2+1]=' ';	
		
	}
	char *t=(char*)calloc(columnCount*2,sizeof(char));
	for(i=0;i<columnCount*2;i++){
		t[i]=types[i];
	}
	fprintf(ftable,"%s",t);
//	fputs(t,ftable);
	fprintf(ftable,"\n");
	
	for(i=0;i<columnCount*2;i++){
		t[i]=pks[i];
	}
	fputs(t,ftable);
	fprintf(ftable,"\n");
	for(j = 0 ; j < columnCount ; j++ )
		fprintf(ftable,"%-15s",Columns[j]);
		
	free(t);	
	fprintf(ftable,"\n");
	fclose(ftable);
	free(databaseName);
}

void createDatabase(){//Create Database
	FILE *databases;

	int databaseCount,columnCount,i;
	char name[25],col_name[25],temp[38];

	printf("Enter the name of database:\n");
	scanf("%s",&name);
	while(controlDatabase(name) == 1){
		printf("There is already a Data Base with this name.\n");
		printf("Please enter a new name :\n");
		scanf("%s",&name);
	}
	
	databaseCount = databasecount();//if there is no "databases.txt" this will create one
	
	databases = fopen("databases.txt","r+");
	fprintf(databases,"%d\n",databaseCount+1);		
	fseek(databases,0,SEEK_END);
	fprintf(databases,"%s\n",name);

	fclose(databases);
	
	createFolder(name);
}

void deleteTable(int databaseIndex,int tableIndex){//deletes everything about a table
	
	int tableCount;
	char dir[60],dir2[60];
	char *databaseName = findDatabaseName(databaseIndex);
	char *tableName = findTableName(databaseIndex,tableIndex);
	//deleting the text file
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	remove(dir);
	//changing the table count in file
	sprintf(dir2,"%s\\tables.txt",databaseName);
	FILE *fp = fopen(dir2 ,"r+");
	fscanf(fp,"%d\n",&tableCount);
	rewind(fp);
	fprintf(fp,"%d\n",tableCount-1);
	//removing the name of table from tables.txt
	fclose(fp);
	deleteRow(dir2,tableIndex);
	free(databaseName);
	free(tableName);
}

void deleteTableRow(int selectedDatabase,int selectedTable,int selectedRow){//deletes a row from selected table
	
	char *databaseName = findDatabaseName(selectedDatabase);
	char *tableName = findTableName(selectedDatabase,selectedTable);
	int rowCount,columnCount;
	char dir[50];
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	
	deleteRow(dir,selectedRow+4);//deleting row 
	FILE *ftable = fopen(dir,"r+");//decreasing row count in the table
	fscanf(ftable,"%d %d",&columnCount,&rowCount);
	fseek(ftable,0,SEEK_SET);
	fprintf(ftable,"%d %d\n",columnCount,rowCount-1);
	printf("Row Deleted Successfully...\n");getch();
	free(databaseName);
	free(tableName);
	fclose(ftable);
}

void updateRow(int selectedDatabase,int selectedTable,int selectedRow){//updates a row from selected table
	
	char *databaseName = findDatabaseName(selectedDatabase);
	char *tableName = findTableName(selectedDatabase,selectedTable);
	int rowCount,columnCount,i,j;
	char dir[50],temp[25],temp2[270];
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	
	FILE *ftable = fopen(dir,"r+");
	if(!ftable){
		printf("Table Couldnt be found...\n");getch();
		return ;
	}
	fscanf(ftable,"%d %d\n",&columnCount,&rowCount);

	int *pks = (int*)calloc(columnCount,sizeof(int));
	int *types = (int*)calloc(columnCount,sizeof(int));
	
	char **columnNames = (char**)calloc(columnCount,sizeof(char**));
	for( i = 0; i < columnCount ; i++ )
		columnNames[i] = (char*)calloc(25,sizeof(char*));
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		types[i]=temp2[i*2]-48;
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		pks[i]=temp2[i*2]-48;
	if( rowCount != 0 )	
		fgets(temp2,270,ftable);

	for( i = 0; i < columnCount ; i++ ){
		for( j = 0 ; j < 15 ; j++ )
			columnNames[i][j]=temp2[ i*15 + j ];
		strcpy(columnNames[i],clearSpaces(columnNames[i]));
	}
	for( i = 0 ; i < selectedRow ; i++ )//
		fgets(temp2,270,ftable);
		
	for( i = 0; i < columnCount ; i++ ){
		printf("Column %s:\n",columnNames[i]);
		scanf("%s",temp);
		while( isSuitable(temp,i,rowCount,columnCount,types,pks,ftable) != 0)	
			scanf("%s",temp);					
		
		fprintf(ftable,"%-15s",temp);		
	}	
	
	printf("Row Updated Successfully...\n");
	getch();
	fclose(ftable);
	free(pks);
	free(types);
	free(databaseName);
	free(tableName);
	free(columnNames);	
}

void whereDeleteUpdate(int selectedDatabase,int selectedTable,char function){//delete and update function with where functionality
	char *databaseName = findDatabaseName(selectedDatabase);
	char *tableName = findTableName(selectedDatabase,selectedTable);
	int rowCount,columnCount,columnNumber,i,j,index,location;
	char dir[50],temp[25],temp2[270],selection[25];
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	FILE *ftable = fopen(dir,"r+");
	if(!ftable){
		printf("Table Couldnt be found...\n");getch();
		return ;
	}
	fscanf(ftable,"%d %d\n",&columnCount,&rowCount);
	int *pks = (int*)calloc(columnCount,sizeof(int));
	int *types = (int*)calloc(columnCount,sizeof(int));
	
	char **columnNames = (char**)calloc(columnCount,sizeof(char**));
	for( i = 0; i < columnCount ; i++ )
		columnNames[i] = (char*)calloc(25,sizeof(char*));
		
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		types[i]=temp2[i*2]-48;
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		pks[i]=temp2[i*2]-48;
	if( rowCount != 0 )	
		fgets(temp2,270,ftable);

	for( i = 0; i < columnCount ; i++ ){
		for( j = 0 ; j < 15 ; j++ )
			columnNames[i][j]=temp2[ i*15 + j ];
		strcpy(columnNames[i],clearSpaces(columnNames[i]));
	}

	for( i = 0; i < columnCount ; i++ )
		printf("%d.%s\n",i+1,columnNames[i]);
	printf("With which Column Do You Want To Select Rows:\n");	
	scanf("%d",&columnNumber);
	columnNumber--;
		
	if(function == '4')	{
		printf("Enter the Name of the row you want to delete:\n");
		scanf("%s",temp);
		index=findElement(temp,columnNumber,rowCount,columnCount,ftable);
		if(index == -1)
			printf("Name could not be found...\n");
		else{
			while(index != -1){
				location = ftell(ftable);
				fclose(ftable);
				deleteTableRow(selectedDatabase,selectedTable,index);
				ftable = fopen(dir,"r+");
				fseek(ftable,location,SEEK_SET);
				index=findElement(temp,columnNumber,rowCount,columnCount,ftable);
			}
			printf("Rows Deleted Successfully...\n");getch();
		}
		getch();	
	}
	
	if(function == '5')	{
		printf("Enter the Name of the row you want to update:\n");
		scanf("%s",temp);
		index=findElement(temp,columnNumber,rowCount,columnCount,ftable);
		if(index == -1)
			printf("Name could not be found...\n");
		else{
			while(index != -1){
			location = ftell(ftable);
			fclose(ftable);
			updateRow(selectedDatabase,selectedTable,index);
			ftable = fopen(dir,"r+");
			fseek(ftable,location,SEEK_SET);
			index=findElement(temp,columnNumber,rowCount,columnCount,ftable);
			}	
			printf("Rows Updated Successfully...\n");	
		}	
		getch();
	}
	
	fclose(ftable);
	free(pks);
	free(types);
	free(databaseName);
	free(tableName);
	free(columnNames);	
}

void addPK(int selectedDatabase,int selectedTable){//adds primary key functionality to selected column
	
	char *databaseName = findDatabaseName(selectedDatabase);
	char *tableName = findTableName(selectedDatabase,selectedTable);
	int rowCount,columnCount,i,j;
	char dir[50],temp[25],temp2[270];
	sprintf(dir,"%s\\%s.txt",databaseName,tableName);
	
	FILE *ftable = fopen(dir,"r+");
	if(!ftable){
		printf("Table Couldnt be found...");getch();
		return ;
	}
	fscanf(ftable,"%d %d\n",&columnCount,&rowCount);

	int *pks = (int*)calloc(columnCount,sizeof(int));
	int *types = (int*)calloc(columnCount,sizeof(int));
	
	char **columnNames = (char**)calloc(columnCount,sizeof(char**));
	for( i = 0; i < columnCount ; i++ )
		columnNames[i] = (char*)calloc(25,sizeof(char*));
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		types[i]=temp2[i*2]-48;
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )
		pks[i]=temp2[i*2]-48;
	if( rowCount != 0 )	
		fgets(temp2,270,ftable);

	for( i = 0; i < columnCount ; i++ ){
		for( j = 0 ; j < 15 ; j++ )
			columnNames[i][j]=temp2[ i*15 + j ];
		strcpy(columnNames[i],clearSpaces(columnNames[i]));
	}
	for( i = 0; i < columnCount ; i++ ){
		if( pks[i] == 1)
		 printf("%d.%s is Primary Key\n",i,columnNames[i]);
		else
		 printf("%d.%s is NOT Primary Key\n",i,columnNames[i]);
	}
	printf("How many column do you want to select:");
	scanf("%d",&j);
	for( i = 0; i < j ; i++ ){
		printf("%d.Selection:\n",i);
		scanf("%d",&i);
		while( pks[i] == 1 ){
			printf("Column that you selected is already a primary key.\n");
			printf("Please Select again:\n");
			scanf("%d",&i);
		}
		pks[i] = 1;				
	}
	rewind(ftable);
	fgets(temp2,270,ftable);
	fgets(temp2,270,ftable);
	for( i = 0; i < columnCount ; i++ )	
		fprintf(ftable,"%d ",pks[i]);
	fprintf(ftable,"\n");
	if( j > 1 )
		printf("Primary key added successfully...\n");
	else
		printf("Primary keys added successfully...\n");	
	
	fclose(ftable);
	free(pks);
	free(types);
	free(databaseName);
	free(tableName);
	free(columnNames);	
}