/* @Author 
* Student Name: Muhammed Furkan Kamer 
* Student ID : 150160013
* Date:8.11.2018 
*/




#include<iostream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<string.h>
#include<fstream>
using namespace std;
struct node {
  int x;
  char y;
  node *next;
  node *next2;
};


struct occur_node {
    char character;
    occur_node* next;
    int occurence;
};
struct vocab_node {
    char character;
    vocab_node* next;
    occur_node* list;
};










int main(int argc, char* argv[])
{
	
	char a[200];
	int count=0;
	int m=0;
	char temp;
	for(int i=0;i<200;i++)
	{
		a[i]='\0';
	}
	int sizea=strlen(a);
	std::ifstream input(argv[1]);
	for( std::string linee; getline( input, linee ); )
	{
		m=0;
		for(int i=0;i<=linee.size();i++)
		{
			linee[i]=tolower(linee[i]);
		}
		if(strlen(a) == 0)
		{
		
		for(int i=0;i<=linee.size();i++)
		{
			a[i]=linee[i];
		}
		a[linee.size() + 1]='\0';
	}
	    else{
	    	for(int i=0;i<=linee.size();i++)
	    	{
	    		count=0;
	    		for(int j=0;j<=strlen(a);j++)
	    		{
	    			if(linee[i] == a[j])
	    			{
	    				count=1;
	    				break;
					}
				}
				if(count != 1)
				{
					a[strlen(a)+m]=linee[i];
					m++;
				}
			}
		}
		
		
	}
  
  char special_characters[20];
  for(int i=0;i<20;i++)
  {
  	  special_characters[i]='\0';
  }
  int f=0;
  for(int h=0;h<=strlen(a);h++)
 {
 	if((a[h] - '\0' < 127 && a[h] - '\0' >122) || (a[h] - '\0'< 97 && a[h] - '\0'>31))
 	{
 		special_characters[f]=a[h];
 		
 		f++;
	 }
 }
 
 sizea=strlen(a);
 cout<<a<<"\n";
 for(int i=0;i<sizea;i++)
  {
  	for(int j=i;j<sizea;j++)
  	{
  		
  		if(a[i]-'\0' > a[j] - '\0')
  		{
  			temp=a[i];
  			a[i]=a[j];
  			a[j]=temp;
  			
		  }
	  }
  }
 
 int k=0;
 
 char b[strlen(a)];
 for(int i=0;i<strlen(a);i++)
 {
 		b[i]='\0';
	 
 }
  for(int i=0;i<=strlen(a);i++)
  {
  	
  	if(a[i]-'\0'>96 && a[i]-'\0'<123)
  	{
	  
  	b[k]=a[i];
  
    k++;
}
}

  
  
  
  strcat(b,special_characters);
  
  int u=0;
for (int i=0; i<1000; i++) { 
         
      
     int j;   
     for (j=0; j<i; j++)  
        if (b[i] == b[j]) 
           break; 
       
   
     if (j == i) 
        b[u++] = b[i]; 
   } 
   cout<<b<<"\n";
  
  
  
  int array[123][123];
  int array2[123];
  int array3[123][123];
 for(int i=0;i<123;i++)
    {
    	for(int j=0;j<123;j++)
    	{
    		array[i][j]=0;
    		array3[i][j]=0;
		}
		array2[i]=0;
	}
	
	
  std::ifstream input2(argv[1]);
  
	for( std::string line; getline( input2, line ); )
	{
		line=line+"\n";
		
		for(int i=0;i<=line.size();i++)
		{
			line[i]=tolower(line[i]);
			if(line[i] == '\n')
			{
				line[i]=' ';
			}
			array2[line[i]-'\0']++;
		}
    for(int i=0;i<strlen(b);i++)
    {
    	for(int j=0;j<line.size();j++)
    	{
    		if(j>=1)
    		{
    			if(line[j-1]==b[i])
    			{
    				array[b[i]-'\0'][line[j]-'\0']++;
    				
				}
			}
		}
	}

  
    
  
  
  
}

  
  
   vocab_node *head;
    vocab_node *root;
    root= new vocab_node;
    root->next=NULL;
    head=root;
    int i=0;
    while(head->next==NULL && b[i] != '\0')
    {
    	head->character=b[i];
    	head->next=new vocab_node;
    	head=head->next;
    	head->next=NULL;
		
		i++;
    	
    
	}
    
	
	occur_node *head2;
	head=root;
	int j=0;
	i=0;
	while(head != NULL)
	{
		head->list=new occur_node;
		head2=head->list;
		head2->next=NULL;
	j=0;
	if(b[i] != '\0')
	{
	
	while(head2->next ==  NULL && j<123)
	{
		
		if(array[b[i]-'\0'][j] != 0 )
			{
				head2->next=new occur_node;
		        head2=head2->next;
				if(j!= 32)
				{
				
			char o=j;
			head2->character=o;
			head2->occurence=array[b[i]-'\0'][j];
	}
	        else
	        {
	        	head2->occurence=array[b[i]-'\0'][j];
			}
		}
		
		
		
		head2->next =  NULL;
		
		
    j++;		
	}
}
	i++;
	head=head->next;
}
	if(argv[2] == NULL)
	{
	
	head=root;
	while(head != NULL)
	{
		
		std::cout<<head->character<<":\n";
		
		head2=head->list;
		head2=head2->next;
		while(head2 != NULL)
		{
		   
        
         std::cout<<"\t<"<<head2->character<<","<<head2->occurence<<">\n";
        head2=head2->next;
	

}
		head=head->next;
		
		
	}
	
}
  
  else
  {
  	  cout<<(float)array[argv[2][0]-'\0'][argv[3][0]-'\0']/(float)array2[argv[2][0]-'\0'];
  }
  
  
  
  
  
  
  
  
  
  
  
  
	
	
	return 0;
}
