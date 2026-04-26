void postfix(){
    int i,j=0;
    char c;
    for(i=0;infix[i]!='\0';i++){
        if (isalnum(infix[i]){
            postfix[j++]=infix[i];
        else if(infix[i]=='('){
            push(infix[i])
        
        }
        else if(infix[i]==')'){
            while((c=pop())!='('){
            postfix[j++]=c
            }
        }
        else{
            if(top!=-1 && precedence(infix[i])<=precedence(stack[top]))
        }

        }
    }
}
