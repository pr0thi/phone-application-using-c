//Phone_book_application_using_c_language
//C-Mini-Project

/*Memebers - Harsh Pruthi (RA2111003010107)
             Sneha Mazumdar (RA2111003010103)       
*/
#include<stdio.h>
#include<string.h>

//Function Declarations in the beginning of the program and definitions at the end 
void addrecord();
void deleterecord();
void modifyrecord();
void searchrecord();
void listrecord();
void menu();

//creating user defined date type to store the data as per contacts application
struct person{
    char name[35];
    char address[50];
    char mble_no[20];
    char mail[100];
};
typedef struct person ch;   //ch is a short name/nickname given to entire datatype struct person
//creating variables using structure 
ch p;

//function to insert contact details by the user 
void addrecord(){
    FILE *f,*ft;    //creating file pointors 
    char name[100];
    f=fopen("project","ab+");
    printf("Enter name: \n");
    scanf("%s",name);
   
    if(f!=NULL){
        ft=fopen("temp","wb+"); {   //open binary file in read and write mode
            if(strcmp(p.name,name)==0){     //if strings are equal that means name is already present in file
                printf("Name already exists \n");
                printf("Enter another name\n");
                scanf("%s",p.name);
            }
            else{
                strcpy(p.name,name);//copy name to p variable 

            }

        }  
    }
    printf("Enter the address:");
    scanf("%s",p.address);
    char mobno[20]="";
    while(1){
        printf("Enter 10 digit mobile number:");
        scanf("%s",mobno);
    
    if(strcmp(p.mble_no,mobno)==0) //phone number already exists 
    {
    printf("Contact already exists\n");
    continue;
    }
    

    if(strlen(mobno)<10||strlen(mobno)>10) //phone number < or > than 10 digits 
    {
    printf("Only 10 digits are allowed \n");
    continue;
    }

    strcpy(p.mble_no,mobno);
    break;
}

    char mail[50];
    printf("Enter E-mail: \n");
    scanf("%s",mail);

    strcpy(p.mail,mail);

    fwrite(&p,sizeof(p),1,f);
    

    printf("Record Saved \n");
    fclose(ft);
    fclose(f);
    menu();
    
}

void deleterecord(){
    FILE *f,*ft;
    int flag;
    char name[100];
    f=fopen("project","rb+");//opens a new file project in read and write binary format 
    if(f!=NULL){
        ft=fopen("temp","wb+");//create temp file allowing read and write operation
        {
            printf("Enter contact name:");
            scanf("%s",name);
            
            while (fread(&p,sizeof(p),1,f))//fread() function is used to read bytes from the file
            {
                if(strcmp(p.name,name)!=0)
                    fwrite(&p,sizeof(p),1,ft);//fwrite() function is used to write records (sequence of bytes) to the file
                if(strcmp(p.name,name)==0)
                    flag=1;

            }
            fclose(f);
            fclose(ft);
            if(flag!=1){
                printf("Invalid contact name");
                remove("temp.txt");

            }
            else{
                remove("project");
                rename("temp","project");
                printf("Record deleted successfully\n");
            }
            
        }

    }
    else{
        printf("Contact is empty\n");
    }
    menu();
        
}


//function to list all contacts in file in order entered by user
void listrecord(){
    FILE *f;
    char *temp;
    f=fopen("project","rb"); //opens a new file project in read mode in binary format 
    if(f!=NULL){
        printf("---------------------------------\n");
        printf("Phonebook Record\n");
        printf("----------------------------------------------------------------------------------");
      printf("\nName\t\tAddress\t\tPhone Number\t\tMail_Id\n");
      printf("----------------------------------------------------------------------------------\n");
	  while(fread(&p,sizeof(p),1,f)==1)
      {
          printf("%s\t\t%s\t\t%s\t\t%s\n",p.name,p.address,p.mble_no,p.mail);
      }
      printf("----------------------------------------------------------------------------------\n");
    }
    else
    {
       printf("No Records\n");
    } 
    menu();
}
    
//function to modify contact details 
void modifyrecord(){
    FILE *f;
    int flag=0;
    struct person p,s;
    char name[50];
    f=fopen("project","rb+"); //opens a new project file in read and write mode in binary format 
    if(f==NULL){
        printf("Contact is empty \n");
    }
    else{
        printf("Enter contact name to be modified :");
        scanf("%s",name);
            while(fread(&p,sizeof(p),1,f)==1)
            {
                if(strcmp(name,p.name)==0)// if entered name matches with names in file then modify contact
                {
                    printf("\nEnter name:");
                    scanf("%s",s.name);
                    printf("\nEnter the address: ");
                    scanf("%s",s.address);
                   char mobno[20]="";
                   while(1){   
	                printf("\nEnter 10 digit phone no:");
	                scanf ("%s",mobno);
	                if(strlen(mobno)<= 0)
	               {
	                   	printf("Please enter ph num\n");
		                continue;
	               }
	              
	              if(strlen(mobno)< 10 || strlen(mobno)> 10)
	              {
		           printf("Only 10 digit is allowed\n");
		           continue;
	              }
	             strcpy(s.mble_no, mobno);
	               break;
               }
               printf ("Enter e-mail ID: ");
	           scanf ("%s",s.mail);
                    fseek(f,-sizeof(p),SEEK_CUR);
                    fwrite(&s,sizeof(p),1,f);
                    flag=1;//flag is set to 1 if contact is modified
                    break;
                }
                

            }
        if(flag==1)
        {
                printf("\nContact is modified");         
        }
        else
        {
                printf("\nContact not found");
        }
            fclose(f);
    
    }
    
    menu();

}

//function to search contact name and retrieve contact details
void searchrecord()
{
  char name[100];
  FILE *f;
  f=fopen("project","rb+");//opens a new file project in read and write in binary format
  if(f==NULL)//if file is null
  {
    printf("\nContact is empty");
    
  }
  else
  {
    printf("\nEnter contact name to search:");
    scanf("%s",name);
    if(strcmp(p.name,name)!=0)//if name doesn’t  match with names in file
    {
         printf("Contact not found\n");
    }
    else
    {
        printf("\nContact Details About %s",name);//print all details of that contact
        printf("\nName:%s\nAddress:%s\nMobile no:%s\nE-mail:%s\n",p.name,p.address,p.mble_no,p.mail);
    }
  }
    menu();
}
    
void menu(){
    int choice;
    printf("Phone Book Mini-Project Program using C\n");
    printf("Menu\n");
    printf("1.Add Contact\n");
    printf("2.Delete Contact\n");
    printf("3.Modify Contact\n");
    printf("4.Search Contact\n");
    printf("5.List Contact\n");
    printf("6.Exit\n");
    printf("Enter choice:");
    scanf("%d",&choice);
    int a=1;
    while(a==1){
        switch (choice)
        {
        case 1:
            addrecord();
            break;
        case 2:
            deleterecord();
            break;
        case 3:
            modifyrecord();
            break;
        case 4:
            searchrecord();
            break;
        case 5:
            listrecord();
            break;
        case 6:
            a=0;
            break;
        default:
            printf("Invalid Choice entered\n Please enter valid choice\n");

            break;
        }

    }

}

int main(){
    menu();
    return 0;

}