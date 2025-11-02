#include <stdio.h>
#include <string.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);

int main() {
    int choice;
    char message[256];

    do {
        printf("========  TCS SECURE MESSAGE SYSTEM  ======\n");
        printf("===========================================\n");
        printf("1) ENCODE MESSAGE\n");
        printf("2) DECODE MESSAGE\n");
        printf("3) EXIT\n");
        printf("-------------------------------------------\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("\nENTER MESSAGE TO ENCODE: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                encodeMessage(message);
                printf("\nENCODED MESSAGE: %s\n", message);
                printf("-------------------------------------------\n");
                break;

            case 2:
                printf("\nENTER MESSAGE TO DECODE: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';
                decodeMessage(message);
                printf("\nDECODED MESSAGE: %s\n", message);
                printf("-------------------------------------------\n");
                break;

            case 3:
                printf("\nEXITING SYSTEM... GOODBYE.\n");
                printf("===========================================\n");
                break;

            default:
                printf("\nINVALID CHOICE! TRY AGAIN.\n");
                printf("-------------------------------------------\n");
        }
    } while (choice != 3);

    return 0;
}

void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void encodeMessage(char message[]) {
    reverseString(message);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = message[i] ^ (1 << 1);
        message[i] = message[i] ^ (1 << 4);
    }
}

void decodeMessage(char message[]) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = message[i] ^ (1 << 1);
        message[i] = message[i] ^ (1 << 4);
    }
    reverseString(message);
}

