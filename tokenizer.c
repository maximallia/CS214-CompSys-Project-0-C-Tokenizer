#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* temp;
//int isComment = 0;//breaks runner when this ==1

int checkOp(char s);//check when str stop containing op
void printOperator(char* s);//iterates through op string and ids the operators

int printHex(char* s, int currentIdx);//identifies Hex and prints it, returns stridx
int printOct(char* s, int currentIdx);//identifies Oct and prints it, returns stridx
int printDecimal(char* s, int currentIdx);//identifies dec, flt, fltpt and prints, returns stridx
int printWord(char* s, int currentIdx);//identifies word ops and normal words, returns stridx
int runOp(char*s, int currentIdx); //forms a short op str and runs printOperator inside, returns stridx

void finalRunner(char* s);//compiles and runs all function


//Extra credit 2
//int runComment(char* s, int currentIdx, int stopper);
/*Unfortunately, our comment code only works 80% of the time. There was one combination at cause the entire code to break.
"/ *". if there is no "* /" to complete the / ** / comment then the entire code would enter a runon. I had tried to fix it,
but considering comments were only extra credit, I commented out all the code portion for comments. Because even if I do fix it, I am unsure
if I had covered all possible bugs. If there was even one bug, it could break the code, and cause us to lose points for the assignment.
While "//" works just fine...*/

int checkOp(char s)
{//if return 0, that means char of string is one operator or part of an operator
    int status = 1; //0=T, 1=F

    //listed below are chars of operators
    if ( (s == '(')
    || (s==')')
    || (s=='[')
    || (s==']')
    || (s=='.')
    || (s== '-') // ->
    || (s== ',')
    || (s== '!')
    ||(s == '~')
    || (s== '>') //>=,>>,>>=
    || (s== '<') //<=,<<,<<=
    || (s== '^')
    || (s== '|') // ||
    || (s == '+') //++, +=
    || (s == '/') // //, /=
    || (s == '&') // &&, &=
    || (s== '?')
    || (s == ':')
    || (s== '=')
    || (s== '*') // *=
    || (s == '%') // %=
    )
    {
        status = 0; 
    }

    return status;
}



void printOperator(char* s){
    char* temp2 = s;

    int strIdx2 = 0;

    //sizeof is placed in word loop
    while(strIdx2 < strlen(temp2) )
    {
        if ( temp2[strIdx2] == '(')
        {
             printf("left parenthesis: \"(\"");
             strIdx2++;
        }
        else if (temp2[strIdx2] ==')')
        {
            printf("right parenthesis: \")\"");
            strIdx2++;
        }
        else if (temp2[strIdx2]=='[')
        {
            printf("left bracket: \"[\"");
            strIdx2++;
        }
        else if (temp2[strIdx2]==']')
        {
            printf("right bracket: \"]\"");
            strIdx2++;
        }
        else if (temp2[strIdx2]=='.')
        {
            printf( "structure member: \".\"");
            strIdx2++;
        }
        else if (temp2[strIdx2]== '-')
        {
            if(temp2[strIdx2+1]== '>')
            {
                printf( "structure point: \"->\"");
                strIdx2+=2;
            }
            else if(temp2[strIdx2+1]== '-')
            {
                printf( "decrement: \"--\"");
                strIdx2+=2;
            }
            else if(temp2[strIdx2+1]== '=')
            {
                printf( "minus equals: \"-=\"");
                strIdx2+=2;
            }
            else
            {
                printf( "minus/subtract operator: \"-\"");
                strIdx2++;
            }
        } // -> -- -=
        else if (temp2[strIdx2]== ',')
        {
            printf( "comma: \",\"");
            strIdx2++;
        }
        else if (temp2[strIdx2]== '!')
        {
            if(temp2[strIdx2+1] == '=')
            {
                printf( "inequality test: \"!=\"");
                strIdx2+=2;
            }
            else
            {
            printf( "negate: \"!\"");
            strIdx2++;
            }
        }// != !
        else if (temp2[strIdx2]== '~')
        {
            printf( "ls complement: \"~\"");
            strIdx2++;
        }
        else if (temp2[strIdx2]== '>')
        {
            if((temp2[strIdx2+1]== '>') && (temp2[strIdx2+2]== '=') )
            {
                printf( "shift right equals: \">>=\"");
                strIdx2+=3;
            }
            else if(temp2[strIdx2+1]== '>')
            {
                printf( "shift right: \">>\"");
                strIdx2+=2;
            }
            else if(temp2[strIdx2+1]== '=')
            {
                printf( "greater than or equal test: \">=\"");
                strIdx2+=2;
            }
            else
            {
                printf( "greater than test: \">\"");
                strIdx2++;
            }
        } //>=,>>,>>=, >
        else if (temp2[strIdx2]== '<')
        {
	  if((temp2[strIdx2+1]== '<') && (temp2[strIdx2+2]== '='))
            {
	      printf( "shift left equals: \"<<=\"");
	      strIdx2+=3;
            }
	  else if(temp2[strIdx2+1]== '=')
            {
	      printf( "less than or equal test: \"<=\"");
	      strIdx2+=2;
            }
	  else if(temp2[strIdx2+1]== '<')
            {
	      printf( "shift left: \"<<\"");
	      strIdx2+=2;
            }
	  else
            {
	      printf( "less than test: \"<\"");
	      strIdx2++;
            }
        } //<=,<<,<<=, <
        else if (temp2[strIdx2]== '^')
        {
            if(temp2[strIdx2+1]== '=')
            {
                printf( "bitwise XOR equals: \"^=\"");
                strIdx2+=2;
            }
            else
            {
                printf( "bitwise XOR: \"^\"");
                strIdx2++;
            }
        }// ^ ^=
        else if (temp2[strIdx2]== '|')
        {
            if(temp2[strIdx2+1]== '|')
            {
                printf( "logical OR: \"||\"");
                strIdx2+=2;
            }
            else if(temp2[strIdx2+1]== '=')
            {
                printf( "bitwise OR equals: \"|=\"");
                strIdx2+=2;
            }
            else
            {
                printf( "bitwise OR: \"|\"");
                strIdx2++;
            }
        } // || |=
        else if (temp2[strIdx2] == '+')
        {
            if(temp2[strIdx2+1] == '+')
            {
                printf( "increment: \"++\"");
                strIdx2+=2;
            }
            else if(temp2[strIdx2+1] == '=')
            {
                printf( "plus equals: \"+=\"");
                strIdx2+=2;
            }
            else
            {
                printf( "addition: \"+\"");
                strIdx2++;
            }
        }//++, +=
        else if (temp2[strIdx2] == '/')
        {
            if(temp2[strIdx2+1] == '=')
            {
                printf( "divide equals: \"/=\"");
                strIdx2+=2;
            }

            // if(temp2[strIdx2+1] == '/')
            // {
            //     break;
            // }
            else
            {
                printf( "division: \"/\"");
                strIdx2++;
            }
        } // /= /
        else if(temp2[strIdx2] == '&')
        {
            if(temp2[strIdx2+1] == '=')
            {
                printf( "bitwise AND equals: \"&=\"");
                strIdx2+=2;
            }
            else if(temp2[strIdx2+1] == '&')
            {
                printf( "logical AND: \"&&\"");
                strIdx2+=2;
            }
            else
            {
                printf( "AND/address operator: \"&\"");
                strIdx2++;
            }
        } // &&, &=, &
        else if(temp2[strIdx2] == '?')
        {
            printf("conditional true: \"?\"");
            strIdx2++;
        }//?
        else if(temp2[strIdx2] == ':')
        {
            printf("contional false: \":\"");
	    strIdx2++;
        }// :
        else if(temp2[strIdx2] == '=')
        {
            if(temp2[strIdx2+1] == '=')
            {
                printf( "equality test: \"==\"");
                strIdx2+=2;
            }
            else
            {
                printf( "assignment: \"=\"");
                strIdx2++;
            }
        } // = ==
        else if(temp2[strIdx2]== '*')
        {
            if(temp2[strIdx2+1]== '=')
            {
                printf( "times equals: \"*=\"");
                strIdx2+=2;
            }
            else
            {
                printf("multiply/dereference operator: \"*\"");
                strIdx2++;
            }
        } // *= *
        else if(temp2[strIdx2] == '%')
        {
            if(temp2[strIdx2+1] == '='){
                printf("mod equals: \"%%=\"");
            }
            else
            {
                printf("mod operator: \"%%\"");
                strIdx2++;
            }
        }// %=
        if(temp2[strIdx2]!='\0')
        {
            printf("\n");
        }
    }
    //free(temp2);
    
}

int printHex(char* s, int currentIdx)
{
    int strIdx = currentIdx;
    int wordIdx = 0;
    int i = 0;

    char* temp = s;

    if(temp[strIdx] == '0')
    {
        if(temp[strIdx+1]== 'x' || temp[strIdx+1]=='X')
        {
            wordIdx = strIdx+2;

            while((temp[wordIdx]>='a' && temp[wordIdx]<='f')
            ||(temp[wordIdx]>='A' && temp[wordIdx]<='F')
            ||(temp[wordIdx]>='0' && temp[wordIdx]<='9'))
            {
                //printf("%c", test[wordIdx]);
                wordIdx++;
                
            }
            
            printf("hexadecimal interger: \"");
            for( i = strIdx; i < wordIdx; i++)
            {
                printf("%c", temp[i]);
            }
            printf("\"\n");
            strIdx = wordIdx;
        } // end of Hex
    }
    //free(temp);
    return strIdx;
}

int printOct(char* s, int currentIdx)
{
    int strIdx = currentIdx;
    int wordIdx = 0;
    int skip, i;

    char* temp  =  s;

    if(temp[strIdx] == '0')
    {
        if((temp[strIdx+1]>='0' && temp[strIdx+1]<='7'))
        { // this is octal
            wordIdx = strIdx+1;
            //printf("%c   ", temp[wordIdx]);
            while((temp[wordIdx]>='0' && temp[wordIdx]<='7'))
            {
                if(temp[wordIdx+1] == '.')
                {//this is a floating point not oct
                    //printf("%c     ", temp[wordIdx+1]);
                    skip = 1;
                    break;
                }
                else{
                    wordIdx++;
                }
            }

            //printf("%d  ", skip);
            if(skip != 1)
            {
                printf("octal integer: \"");
                for( i = strIdx; i<wordIdx; i++)
                {
                    printf("%c", temp[i]);
                }
                printf("\"\n");
                //printf("%c\n", temp[wordIdx] );
                strIdx = wordIdx;
            }
            //we add the length of the word onto our strIdx
            //to move on to next word
            else
            {//means skip is 1, decimal found in 'oct,' should be fltpt
                skip = 0;
                //make skip = 0, for next word is not oct
            }
        }
    }
    //free(temp);
    return strIdx;
}

int printDecimal(char* s, int currentIdx)
{
    int strIdx = currentIdx;
    int wordIdx = 0;
    int i;
    int isfloat = 0; //0=decimal,1=floatingpoint,2=float

    char* temp = s;

    if((temp[strIdx]>='0' && temp[strIdx]<='9'))
    {
        //printf("In for loops.");
        wordIdx=strIdx;
        int decimalpt = 0;//if decimal pt is stop, then already appeared once, not wordIdx+=2
        while((temp[wordIdx]>='0' && temp[wordIdx]<='9')&& (decimalpt<=1))
        {
            //printf("%c\n", temp[wordIdx+1]);
            if((temp[wordIdx+1] == '.') && (temp[wordIdx]>='0' && temp[wordIdx]<='9' )
            )
            {
                //printf(".\n");
                decimalpt++;
                if (decimalpt <= 1)
                {
                    wordIdx +=2;
                    isfloat = 2;
                }
                
            }
            //I added three conditions for e, e-int e+int and eint.
            //These represent the three possible e's that might appear in the float
            if(temp[wordIdx+1] == 'e'
	    &&   decimalpt > 0
            && temp[wordIdx+2] == '-'
	      && (temp[wordIdx+3]>='0' && temp[wordIdx+3]<='9' ))
	      {
                wordIdx += 3;
                isfloat = 2;
            }
            if(temp[wordIdx+1] == 'e'
	    &&   decimalpt > 0
            && temp[wordIdx+2] == '+'
	       && (temp[wordIdx+3]>='0' && temp[wordIdx+3]<='9' ))
            {
                wordIdx += 3;
                isfloat = 2;
            }
            if (temp[wordIdx+1] == 'e'
	    &&   decimalpt > 0
            && (temp[wordIdx+2]>='0' && temp[wordIdx+2]<='9' ))
            {
                wordIdx += 2;
                isfloat = 2;
            }

            wordIdx++;
            
        }
        // printf("%d   ", isfloat);

        if(isfloat == 2)
        {
            printf("floating point: \"");
            isfloat=0;
        }

        else if(isfloat == 0)
        {
            printf("decimal integer: \"");
        }

        for( i = strIdx; i<wordIdx; i++)
        {
            printf("%c", temp[i]);
        }
        printf("\"\n");

        strIdx = wordIdx;
        
    }//decimal, flt, fltpot numbers complete
    //free(temp);
    return strIdx;

}


int printWord(char* s, int currentIdx)
{
    int strIdx = currentIdx;
    int wordIdx = 0;

    int i;

    int flag = 0;//operator located in word thats not specialsign

    char* temp = s;

    if( (temp[strIdx]>='a' && temp[strIdx]<='z')
    || (temp[strIdx]>='A' && temp[strIdx]<='Z'))
    {
        flag = 0;
        wordIdx = strIdx;
        //if the word is sizeof
        if((temp[wordIdx] == 's') && (temp[wordIdx+1] == 'i') && (temp[wordIdx+2] == 'z')
        && (temp[wordIdx+3] == 'e') &&(temp[wordIdx+4] == 'o') && (temp[wordIdx+5] == 'f'))
        {//move forward with wordIdx+n to check if sizeof op exists
            flag = 1;

            printf("sizeof: \"sizeof\"\n");
            wordIdx+=5;
            strIdx = wordIdx;
        }      

        else{
            while((temp[wordIdx]>='a' && temp[wordIdx]<='z')
            || (temp[wordIdx]>='A' && temp[wordIdx]<='Z')
            || (temp[wordIdx]>='0' && temp[wordIdx]<='9'))
            {  
                if((temp[wordIdx+1] == 's') && (temp[wordIdx+2] == 'i') && (temp[wordIdx+3] == 'z')
                && (temp[wordIdx+4] == 'e') &&(temp[wordIdx+5] == 'o') && (temp[wordIdx+6] == 'f'))
                {//move forward with wordIdx+n to check if sizeof op exists within word
                    flag= 1;
                    //isWordOp = 0;
                    printf("word: \"");
                    for( i = strIdx; i<=wordIdx; i++)
                    {//its <= because we predict sizeof comes after the char in temp[wordIdx]
                        printf("%c", temp[i]);
                    }//prints out word string before sizeof
                    printf("\"\n");

                    strIdx = wordIdx;
                    break;
                    //break, we will start another printWord function if next char is word
                }

                else
                {
                    wordIdx++;
                }
            }
        }
        // printf("%c\n", temp[strIdx]);
        if(flag == 0)
        {
            printf("word: \"");
            for( i = strIdx; i<wordIdx; i++)
            {
                printf("%c", temp[i]);
            }
            printf("\"\n");
            strIdx = wordIdx;
        }
        else
        {//
            flag = 0;
        }
    } //end of words

    return strIdx;
} 

int runOp(char* s, int currentIdx)
{
    int strIdx = currentIdx;
    int wordIdx = 0;
    int i,j;
    int opLength = 0;
    char c;

    int commentFound = 0;

    char* temp = s;
    char* strOp;

    if(checkOp(temp[strIdx]) == 0)
    {
        wordIdx = strIdx;
        c = temp[wordIdx];

        while(checkOp(c) == 0)
        {
            //this part if for extra credit comments
	  /*if( temp[wordIdx] == '/' && temp[wordIdx+1]=='/')
            {                
                break;
            }

            if(temp[wordIdx]=='/' && temp[wordIdx+1]=='*')
            {
                //printf("/ * found\n");
                break;
            }
            
            else
            {*/
                wordIdx++;
                c = temp[wordIdx];
		// }
        }

        i = strIdx;
        j = 0;
        opLength = wordIdx - strIdx;

        strOp = malloc(sizeof(char) * opLength + 1);
        //malloc was used, forming new operator string from string
        //then throw the operator string into our printOperator

        
        while((i< wordIdx) && (checkOp(temp[i])==0) )
        {
            strOp[j] = temp[i];
            i++;
            j++;
        }

        printOperator(strOp);
        
        printf("\n");
        //free(result);
        strIdx = wordIdx-1;
    }  
    // }
    //free(strOp); this actually messed up the index, fixed after removed
    return strIdx;
}

// int runComment(char* s, int currentIdx, int stopper)
// {
//     //printf("%c\n", c);
//     char* temp = s;

//     int strIdx = currentIdx;
//     int wordIdx = 0;

//     int i,j;

//     int isComment = 0;

//     while(strIdx<strlen(temp))
//     {
//         if((temp[strIdx] == '/') && (temp[strIdx+1] =='/') )
//         {
//             isComment = 1;

//             printf("comment: \"//\"\n");

//             break;
//         }

//         if((temp[strIdx] == '/') && (temp[strIdx+1] =='*') )
//         {
//             wordIdx = strIdx+2; //chars after /*
//             while(temp[wordIdx])
//             {
//                 if( (temp[wordIdx]=='*') && (temp[wordIdx+1]=='/'))
//                 {
//                     isComment=2;
//                     wordIdx+=2;
//                     //strIdx = tempIdx+2;//rest of string after '*/'
//                     break;
//                 }
//                 else
//                 {
//                     wordIdx++;
//                 }
//             }
//             if(isComment==2)
//             {//if false that means /* == /,* and not /**/
//             //strIdx = tempIdx+2;//rest of string after */

//                 printf("comment: \"");

//                 for( i = strIdx; i<wordIdx; i++)
//                 {
//                     printf("%c", temp[i]);
//                 }

//                 printf("\"\n");
//                 strIdx = wordIdx;
//                 break;
               
//             }
//         }
//         if(isComment == 1 || isComment == 2)
//         {
//             break;
//         }
//         strIdx++;
        
//     }
//     //strIdx = wordIdx;
//     //printf("isComment: %d\n", isComment);

//     if(isComment == 0 || isComment == 1)
//     {//no comment or '//'
//         return isComment;
//     }

//     return strIdx;
//     // '/**/' appeared, need strIdx to continue
    
// }

void finalRunner(char* s)
{
  int strIdx = 0; //point index for our temp string
  int wordIdx = 0; //pointer index for our word

  int isComment=0; //1=comment found,skip entire line, 2=skip to a specific idx

  char c; //for comparing if char is operator with checkOp


  char* temp= s;

  int stopper = strlen(temp);
  //printf("%d\n", stopper);
  //while( temp[strIdx] != '\0')

  while((strIdx <= stopper))
    {
      //for delim
      if(isspace(temp[strIdx]) )
        {//if is ' ' or any backslash, omit it by strIdx++
        
	  strIdx++;
        }

      //for hexadecimal and octal
      //used int skip
      if(temp[strIdx] == '0')
        {
	  if(temp[strIdx+1]== 'x' || temp[strIdx+1]=='X')
            {
	      wordIdx = printHex(temp, strIdx);
	      strIdx = wordIdx;
            } // end of Hex

	  else if((temp[strIdx+1]>='0' && temp[strIdx+1]<='7'))
            { // this is octal
	      wordIdx = printOct(temp, strIdx);
	      strIdx = wordIdx;
            } // end of octal
            
        } // hex and oct complete

      //now for decimal numbers && float && fltpoint
      //used int: isfloat
      if((temp[strIdx]>='0' && temp[strIdx]<='9'))
        {
	  wordIdx = printDecimal(temp, strIdx);
	  strIdx = wordIdx;
        }//decimal, flt, fltpot numbers complete
      
      //now for words
      if( (temp[strIdx]>='a' && temp[strIdx]<='z')
	  || (temp[strIdx]>='A' && temp[strIdx]<='Z'))
        {
	  wordIdx= printWord(temp, strIdx);
	  strIdx = wordIdx;
        } //end of words

      //this section is for extra credit comments: // and /**/
      //explanation in the beginning of why it was commented out 
      /*if((temp[strIdx]=='/' && temp[strIdx+1]=='/')
    || (temp[strIdx]=='/' && temp[strIdx+1]=='*'))
	{
	  isComment = runComment(temp, strIdx, stopper);
	    //strIdx = wordIdx;

	    if(isComment == 1)
        {
	        break;
        }

	    if(isComment != 0 && isComment != 1)
	    {// is not 0 and 1 then it is
	      //isComment would be returning wordIdx
	        wordIdx= isComment;
	        if(checkOp(temp[wordIdx]==0))
		    {   
		      strIdx = wordIdx;
		    }
		else
		  {
		    strIdx = wordIdx-1;
		  }

		
		//printf("strIdx: %d", strIdx);
			
	    
	    }
	    }*/
      //printf("isComment: %d\n", isComment);

      //now it is operator
      //function used: checkOp
    if(checkOp(temp[strIdx]) == 0)
      {
	wordIdx = runOp(temp, strIdx);
	strIdx = wordIdx;
      }
    strIdx++;
    }
}


int main(int argc, char** argv)
{

    if(argv[1] == NULL)
    {
        printf("ERROR, setup failed.\n");
        return 0;
    }//if no inputs

    if(argv[2] != NULL)
    {
        printf("ERROR, excess inputs.\n");
        return 0;
    }//there should only be one input string

    int count = 1;

    while(argv[count])
    {
        char* temp = malloc(sizeof(char)*strlen(argv[count])+1);
        temp = argv[count];
        finalRunner(temp);
        count++;

        //free(temp);
    }
    free(temp);
    return 0;
}
    
 

