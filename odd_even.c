#include <stdio.h>
int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
//for even no.
    if(num % 2 == 0)
        printf("%d is even.", num);
    //for odd no.
    else
        printf("%d is odd.", num);
    
    return 0;
}
