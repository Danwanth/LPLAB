#include <stdio.h>

void    main() {
     //Declare two numbers
    int a,b;
    printf("Enter two numbers: \n"); //test
    //Reading from user
    scanf("%d %d", &a, &b);
    
    /* Here we calculate
    and print the sum 
    in one line */
    printf("The sum is %d\n", a+b);
}
