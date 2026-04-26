for(i=0;i<n;i++)
{
        int i =,len
        char temp[MAX];
        for(i=0;i<n;i++){
                len=prod[i]-3;
                if(len<=top+1){
                    strcpy(temp,stack+top-len+1,len);
                    temp[len]='\0';
                }
                if(strcmp(temp,prod[i])==0){
                    top-=len
                    stack[++top]=prod[i];
                    stack[top+1]='\0'
                }
                printf("STACK %-15S INPUT %-15S ACTION")
                STACK,INPUT+IP,PROD[I]
        }
}
while(1){
if(input[ip]!='\0'){
    symbol=input[ip++];
    stack[++top]=symbol;
    stack[top+1]='\0';
    check_reduce();
}
else{
        check_reduce();
        if(top==0 && stack[top]==prod[i][0])
        {
            printf("ACCEPT");
        }
        else{
            printf("Error");
        }
    }
}