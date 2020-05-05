//code creator sinni jain 201751048
#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>



#define file_name 100


//...........................................................................................................................

//global declaration
FILE* file;

int line_number=1;

int unrechable_line[10000]={0};

//...........................................................................................................................


//defined functions
char ignore_spaces(char b);
char ignore_NextLine(char a);
char ignore_spaces_enter(char a);
char* sub_string(char *str,int start,int end);
double eval(char *expr, int exprLen);
bool compare(float var1 , char *op , float var2);
int totel_line();
char expreesion_pass(char a,int brac);
char if_action_pass(char a,int type,int brace);
char while_action_pass(char a,int type,int brace);
int type_casting(char a , int brac);
void print_unrechable_line(int start_line,int end_line);
void print_whole_unrechable_line(int tline);



//..........................................................................................................................
char ignore_spaces(char b)
{
    while(b==' ')
    {
        b=fgetc(file);
    }
    
    return b;
}

//............................................................................................................................

char ignore_NextLine(char a)
{
    while(a=='\n')
    {
        line_number++;
        a=fgetc(file);
    }

    return a;
}

//............................................................................................................................


char ignore_spaces_enter(char a)
{

    while(a==' ' || a=='\t' || a=='\n')
    {

        if(a=='\n')
        {
            line_number++;
        }

        a=fgetc(file);
    }

    return a;
}


//............................................................................................................................

char* sub_string(char *str,int start,int end)
{
    int len=end-start;
    char *z=(char*)malloc(sizeof(char)*len+1);

    for(int i=start ; i < end ; i++)
    {
        z[i-start]=str[i];
    }
    z[len] = '\0';

    return (char*) z;

}


//...........................................................................................................................


int totel_line()
{
    char a=fgetc(file);

    int lines=0;

    while(a!=EOF)
    {

        if(a=='\n')
        {
            lines++;
        }

        a=fgetc(file);
    }

    fseek(file, 0, SEEK_SET);
    
    return lines+1;

}

//..............................................................................................................................


double eval(char *expr, int exprLen)
{
    char xxx[100]={0}; // Get Rid of Spaces
    int xxxCount=0;
    for (int i = 0; i < exprLen ; i++)
    {
        if (expr[i] != ' ')
        {
            xxx[xxxCount]= expr[i];
            xxxCount++;
        }
    }

    //printf("xxx==%s",xxx);

    char tok[100] = {0}; // Do parantheses first
    int tokCount=0;
    for (int i = 0; i < xxxCount ; i++)
    {
        if (xxx[i] == '(')
        {
            int iter = 1;
            char token[100]={0};
            int tokenCount=0;
            i++;
            while (true)
            {
                if (xxx[i] == '(')
                {
                    iter++;
                } 

                else if (xxx[i] == ')')
                {
                    iter--;
                    if (iter == 0)
                    {
                        i++;
                        break;
                    }
                }
                token[tokenCount]= xxx[i];
                tokenCount++;
                i++;
            }

            //printf("token==%s",token);

            char z[100]={0};
            //to_string in c (store float format value to Z string here)
            sprintf( z , "%.2f", eval(token,tokenCount));
            //cout << "(" << token << ")" << " == " << to_string(eval(token)) <<  endl;

            strcat(tok, z);
            //printf("final string = %s",tok);
            tokCount = strlen(tok);
            //printf("tokCount = %d",tokCount);
            
            
        }

        if(xxx[i]!='\0')
        {
            tok[tokCount]= xxx[i];
            tokCount++;
        }
        
    }

    for (int i = 0; i < tokCount ; i++)
    {
        if (tok[i] == '+')
        {
            //printf("\nsubstring==%s+%s\n",sub_string(tok,0,i),sub_string(tok , i+1 , tokCount));
            return eval(sub_string(tok,0,i),i) + eval(sub_string(tok , i+1 , tokCount),tokCount-i-1);
        } 

        else if (tok[i] == '-')
        {
            //printf("\nsubstring==%s-%s\n",sub_string(tok,0,i),sub_string(tok , i+1 , tokCount-i-1));
            return eval(sub_string(tok,0,i),i) - eval(sub_string(tok , i+1 , tokCount),tokCount-i-1);
        }
    }

    for (int i = 0; i < tokCount; i++)
    {
        if (tok[i] == '*')
        {
            //printf("\nsubstring==%s*%s\n",sub_string(tok,0,i),sub_string(tok , i+1 , tokCount));
            return eval(sub_string(tok,0,i),i) * eval(sub_string(tok , i+1 , tokCount),tokCount-i-1);
        } 

        else if (tok[i] == '/')
        {
            //printf("\nsubstring==%s/%s\n",sub_string(tok,0,i),sub_string(tok , i+1 , tokCount));
            return eval(sub_string(tok,0,i),i) / eval(sub_string(tok , i+1 , tokCount),tokCount-i-1);
        }
    }

    //cout << stod(tok.c_str()) << endl;
    float x; 
    //printf("\ntok===%s ,, %d\n",tok,tokCount);

    //string to digit X
    sscanf(tok, "%f", &x);
    //printf("%f\n",x);
    return x; // Return the value...
}





//.............................................................................................................................


bool compare(float var1 , char *op , float var2)
{
    //printf("--%f %s %f--\n",var1,op,var2);
    if(op[0]=='\0')
    {
        if(var1==0)
        {
            return false;
        }

        else
        {
            return true;
        }
    }

    else if(op[0]=='>')
    {
        if(var1>var2)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    else if(op[0]=='<')
    {
        if(var1<var2)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    else if(op[0]=='>' && op[1]=='=')
    {
        if(var1>=var2)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    else if(op[0]=='<' && op[1]=='=')
    {
        if(var1<=var2)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    else if(op[0]=='=' && op[1]=='=')
    {
        if(var1==var2)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    else if(op[0]=='!' && op[1]=='=')
    {
        if(var1!=var2)
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    return false;
}


//............................................................................................................................


char expreesion_pass(char a,int brac)
{
    
    if(a=='(')
    {
        brac++;
    }

    if(a=='\n')
    {
        line_number++;
    }

    a=fgetc(file);

    while(brac!=0)
    {
        if(a=='(')
            brac++;
        
        else if(a==')')
            brac--;

        a=fgetc(file);
    }


    return a;
}


//............................................................................................................................



char if_action_pass(char a,int type,int brace)
{

    int start_line;
    int end_line;



    if(a=='{')
    {
        brace++;
        a=fgetc(file);
    }

    if(a=='}')
    {
        brace--;
        a=fgetc(file);
    }


    if(type==-1)
    {
        start_line=line_number+1;
        unrechable_line[start_line]=+1;
    }
   

    while(brace!=0)
    {

        //line count
        if(a=='\n')
        {
            line_number++;
        }


        //nesting of loops
        if(a=='i')
        {
            a=fgetc(file);
            if(a=='f')
            {
                a=fgetc(file);
                int new_type=type_casting(a,0);
                //cout << new_type << endl;
                a=fgetc(file);
                a=ignore_spaces_enter(a);
                line_number++;
                a=if_action_pass(a,new_type,0);
                a=ignore_spaces_enter(a);
            }
        }

        else
        {
            if(a=='{')
            {   
                brace++;
            }
            
            else if(a=='}')
            {    
                brace--;
            }

            a=fgetc(file);
        }

        
        //it will return char which is after "}".....keep in mind 
    }

    if(brace==0)
    {
        
        if(type==-1)
        {
            end_line=line_number-1;
            //print_unrechable_line(start_line,end_line);
            unrechable_line[end_line+1] += -1;

            return a;
        }




        else if(type==0)
        {
            return a;
        }



        else if(type==1)
        {
            
            a=ignore_spaces_enter(a);
            int flag=0;

            while(flag==0)
            {

                //..........................action due to type=1
                if(a=='e')
                {
                    a=fgetc(file);
                    if(a=='l')
                    {
                        a=fgetc(file);
                        if(a=='s')
                        {
                            a=fgetc(file);
                            if(a=='e')
                            {
                                a=fgetc(file);
                                a=ignore_spaces(a);

                                start_line=line_number+1;
                                unrechable_line[start_line]+=1;

                                if(a=='i')
                                {
                                    a=fgetc(file);
                                    if(a=='f')
                                    {

                                        a=fgetc(file);
                                        //else if part
                                        a=ignore_spaces(a);
                                        a=expreesion_pass(a,0);
                                    }
                                }

                                
                                a=ignore_spaces_enter(a);
                                
                                a=if_action_pass(a,0,0);
                                //*****point where if(true)...ke bad all else if which are unrechable
                                end_line=line_number;
                                unrechable_line[end_line+1]+=-1;
                                
                                a=ignore_spaces_enter(a);

                            }

                            else 
                            {
                                flag=1;
                            }


                        }

                        else
                        {
                           flag=1;
                        }

                    }

                    else
                    {
                        flag=1;
                    }
                }

                else
                {
                    flag=1;
                }

                //.............................................

            }

            if(flag==1)
            {
                //print_unrechable_line(start_line,end_line);
                return a;
            }


        }

        return a;
        
        
    }

    return a;

    
    
}


//...............................................................................................................................

char while_action_pass(char a,int type,int brace)
{

    int start_line;
    int end_line;



    if(a=='{')
    {
        brace++;
        a=fgetc(file);
    }

    if(a=='}')
    {
        brace--;
        a=fgetc(file);
    }


    if(type==-1)
    {
        start_line=line_number+1;
        unrechable_line[start_line]=+1;
    }
   

    while(brace!=0)
    {

        //line count
        if(a=='\n')
        {
            line_number++;
        }


        //nesting
        if(a=='w')
        {
            a=fgetc(file);
            if(a=='h')
            {
                a=fgetc(file);
                if(a=='i')
                {
                    a=fgetc(file);
                    if(a=='l')
                    {
                        a=fgetc(file);
                        if(a=='e')
                        {
                            // cout << line_number;
                            a=fgetc(file);
                            type=type_casting(a,0);
                            //cout << type << endl;
                            a=fgetc(file);
                            a=ignore_spaces_enter(a);
                            line_number++;
                            a=while_action_pass(a,type,0);
                            a=ignore_spaces_enter(a);
                        }
                    }
                }
            }
        }


        else
        {
            if(a=='{')
            {   
                brace++;
            }
            
            else if(a=='}')
            {    
                brace--;
            }

            a=fgetc(file);
        }

        
        //it will return char which is after "}".....keep in mind 
    }

    if(brace==0)
    {
        
        if(type==-1)
        {
            end_line=line_number-1;
            //print_unrechable_line(start_line,end_line);
            unrechable_line[end_line+1] += -1;

            return a;
        }




        else if(type==0)
        {
            return a;
        }



        else if(type==1)
        {

            start_line=line_number+1;
            unrechable_line[start_line]+=1;

            while(a!=EOF)
            {
                if(a=='\n')
                {
                    line_number++;
                }
                a=fgetc(file);
            }

            end_line=line_number;
            unrechable_line[end_line+1]+=-1;

            //print_unrechable_line(start_line,end_line);
            return a;


        }

        return a;
        
        
    }

    return a;

    
    
}


//...............................................................................................................................


int type_casting(char a , int brac)
{
    

    //....................
    int brac1=brac;
    a=ignore_spaces(a);

    char expr[100]={0};
    char op[2]={0};

    float var1;
    float var2;

    //....................

    
    if(a=='(')
    {
        brac1++;
    }

    
    a=fgetc(file);

    int exprCount=0;
    int opFlag=0;
    
    while(brac1!=0)
    {
        

        if(a=='(')
        {
            brac1++;
        }

        if(a==')')
        {
            brac1--;
        }


        //if variable
        if( (a>=65 && a<=95) || (a>=97 && a<122) )
        {
            //may be
            a=expreesion_pass(a,brac1);
            return 0;
        }


        //only one varibale no comparing operator
        if(brac1==0)
        {
            var1=eval(expr,exprCount);
            a=fgetc(file);
            //cuz currently pointer on ')'

            if(var1==0)
                return -1; 

            else
                return 1;  
        }



        if(a=='<' || a=='>' || a=='=' || a=='!')
        {

            // cout << expr << endl;

            var1=eval(expr,exprCount);
            //printf("\n\nall get clEar = %f\n\n",var1);




            op[0]=a;

            if(a=='=')
            {
                a=fgetc(file);
                if(a!='=')
                {
                    printf("wrong compare operator\n");

                    a=expreesion_pass(a,brac1);
                    return 0;
                
                }

                else if(a=='=')
                {
                    op[1]=a;
                    a=fgetc(file);
                }

            }

            else
            {
                a=fgetc(file);

                if(a=='=')
                {
                    op[1]=a;
                    a=fgetc(file);
                }
            }

            memset(expr, 0, sizeof expr);
            exprCount=0;

            while(brac1!=0)
            {
                if(a=='(')
                {
                    brac1++;
                }

                if(a==')')
                {
                    brac1--;
                }

                if(brac1!=0)
                {
                    expr[exprCount]=a;
                    exprCount++;
                }

                a=fgetc(file);
            }

                    

            // cout << op << endl;
            // cout << expr << endl;
            var2=eval(expr,exprCount);

            //printf("\n\nall get clEar = %f\n\n",var2);
            memset(expr, 0, sizeof expr);
            // cout << var2 << endl;
            // cout << "final destination 2" << endl;  

        }
        

        expr[exprCount]=a;  
        exprCount++;

        a=fgetc(file);

    }

    if(compare(var1,op,var2)==true)
    {
        return 1;
    }

    else if(compare(var1,op,var2)==false)
    {
        return -1;
    }




    return 0;
}



//............................................................................................................................

void print_unrechable_line(int start_line,int end_line)
{
    printf("unrechable line of code : %d to %d\n",start_line,end_line);
}

//.................................................................................................................................


void print_whole_unrechable_line(int tline)
{
    for(int t=1;t<=tline+1;t++)
    {
        //cout << t << "==" << unrechable_line[t] << endl;
        unrechable_line[t]=unrechable_line[t]+unrechable_line[t-1];
    }

    int flag=0;
    int start_line,end_line;

    for(int t=1;t<=tline+1;t++)
    {
        if(unrechable_line[t]>0 && flag==0)
        {
            flag=1;
            start_line=t;
        }

        else if(unrechable_line[t]<=0 && flag==1)
        {
            flag=0;
            end_line=t-1;
            print_unrechable_line(start_line,end_line);
        }
    }

}

//.................................................................................................................................



int main ()
{
    
  
    file = fopen ("test_case6.c", "r");

    int tline=totel_line();

    //.....................................................

    char a;

    int type;

    int start_line;

    int end_line;

    //.....................................................

    a=fgetc(file);

    while(a!=EOF)
    {

        if(a=='\n')
        {
            line_number++;
        }



        int brace=0;
        //case 1
        //spotted a return 
        if(a=='r')
        {
            a=fgetc(file);
            if(a=='e')
            {
                a=fgetc(file);
                if(a=='t')
                {
                    a=fgetc(file);
                    if(a=='u')
                    {
                        a=fgetc(file);
                        if(a=='r')
                        {
                            a=fgetc(file);
                            if(a=='n')
                            {
                                //from after next line of return the unrechable line of code started....untill it's unrechable ,the current function ends;
                                start_line=line_number+1;

                                a=fgetc(file);


                                while(a!=EOF && brace!=-1)
                                {
                                    a=fgetc(file);

                                    if(a=='\n')
                                    {
                                        line_number++;
                                    }

                                    if(a=='{')
                                    {
                                        brace++;
                                    }

                                    else if(a=='}')
                                    {
                                        brace--;
                                    }

                                }

                                // from any point inside body of function
                                //count('}')  = -1  means current fuction have ended here
                                //now code will start execute from next line

                                end_line=line_number-1;

                                if(end_line>=start_line)
                                {
                                    unrechable_line[start_line]+=1;
                                    unrechable_line[end_line+1]+=-1;
                                    //print_unrechable_line(start_line,end_line);
                                }



                            }
                        }

                    }
                }

            }
        }







        brace=0;
        //case 2
        //spotted a break 
        if(a=='b')
        {
            a=fgetc(file);
            if(a=='r')
            {
                a=fgetc(file);
                if(a=='e')
                {
                    a=fgetc(file);
                    if(a=='a')
                    {
                        a=fgetc(file);
                        if(a=='k')
                        {
                            a=fgetc(file);
                            
                            //from after next line of break the unrechable line of code started....untill it's unrechable ,the current function ends;
                            start_line=line_number+1;

                            while(a!=EOF && brace!=-1)
                            {
                                a=fgetc(file);

                                if(a=='\n')
                                {
                                    line_number++;
                                }

                                if(a=='{')
                                {
                                    brace++;
                                }

                                else if(a=='}')
                                {
                                    brace--;
                                }

                            }

                            //finded "}" means current fuction have ended here
                            //now code will start execute from next line

                            end_line=line_number-1;

                            if(end_line>=start_line)
                            {
                                unrechable_line[start_line]+=1;
                                unrechable_line[end_line+1]+=-1;
                                //print_unrechable_line(start_line,end_line);
                            }
                        }
                    }
                }
            }
        }


        else
        {
            a=fgetc(file);
        }




    }


    //.....................................................



    //seek pointer to star
    //start file again and start checking
    fseek(file,0,SEEK_SET);

    line_number=1;




    a=fgetc(file);

    //case 3 to check if-else unrechability
    while(a!=EOF)
    {

        if(a=='\n')
        {
            line_number++;
        }


        if(a=='i')
        {
            a=fgetc(file);
            if(a=='f')
            {
                // cout << line_number;
                a=fgetc(file);
                type=type_casting(a,0);
                //cout << type << endl;
                a=fgetc(file);
                a=ignore_spaces_enter(a);
                line_number++;
                a=if_action_pass(a,type,0);
                a=ignore_spaces_enter(a);

            }
        }

        else
        {
            a=fgetc(file);
        }

    }

    //seek pointer to star
    //start file again and start checking
    fseek(file,0,SEEK_SET);

    line_number=1;




    a=fgetc(file);

    //case 4 to check while loop unrechability

    while(a!=EOF)
    {

        if(a=='\n')
        {
            line_number++;
        }


        if(a=='w')
        {
            a=fgetc(file);
            if(a=='h')
            {
                a=fgetc(file);
                if(a=='i')
                {
                    a=fgetc(file);
                    if(a=='l')
                    {
                        a=fgetc(file);
                        if(a=='e')
                        {
                            // cout << line_number;
                            a=fgetc(file);
                            type=type_casting(a,0);
                            //cout << type << endl;
                            a=fgetc(file);
                            a=ignore_spaces_enter(a);
                            line_number++;
                            a=while_action_pass(a,type,0);
                            a=ignore_spaces_enter(a);
                        }
                    }
                }
            }
        }

        else
        {
            a=fgetc(file);
        }

    }


    print_whole_unrechable_line(tline);

    

}