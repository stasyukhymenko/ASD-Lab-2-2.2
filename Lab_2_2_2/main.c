#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int list;
    struct Node* next;
} Node;

void insertNode(Node** root, int list) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->list = list;
    newNode->next = NULL;

    if (*root == NULL) {
        *root = newNode;
    }
    else {
        Node* current = *root;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(Node* root) {
    Node* current = root;
    while (current != NULL) {
        printf("%d ", current->list);
        current = current->next;
    }
    printf("\n");
}

void reorderList(Node** root) {
    Node* current = *root;
    Node* prev = NULL;

    while (current != NULL) {
        int i = 0;
        Node* negativeFirst = NULL;
        Node* negativeLast = NULL;
        Node* positiveFirst = NULL;
        Node* positiveLast = NULL;

        while (current != NULL && i < 10) {
            Node* nextNode = current->next;

            if (current->list < 0) {
                if (negativeFirst == NULL) {
                    negativeFirst = current;
                    negativeLast = current;
                }
                else {
                    negativeLast->next = current;
                    negativeLast = current;
                }
            }
            else {
                if (positiveFirst == NULL) {
                    positiveFirst = current;
                    positiveLast = current;
                }
                else {
                    positiveLast->next = current;
                    positiveLast = current;
                }
            }

            current->next = NULL;
            current = nextNode;
            i++;
        }

        if (negativeFirst != NULL) {
            if (prev != NULL) {
                prev->next = negativeFirst;
            }
            else {
                *root = negativeFirst;
            }
            if (positiveFirst != NULL) {
                negativeLast->next = positiveFirst;
                prev = positiveLast;
            }
            else {
                prev = negativeLast;
            }
        }
        else {
            if (prev != NULL) {
                prev->next = positiveFirst;
            }
            else {
                *root = positiveFirst;
            }
            prev = positiveLast;
        }
    }
}

void deallocateList(Node** root) {
    Node* current = *root;
    while (current != NULL) {
        Node* nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *root = NULL;
}

int main() {

    srand(time(NULL));

    int n;
    printf("Enter n (n must be a multiple of 10): ");
    scanf_s("%d", &n);

    if (n % 10 != 0) {
        printf("Error: n must be a multiple of 10.\n");
        return 1;
    }

    Node* root = NULL;
    
    printf("Random list: \t");
    for (int i = 0; i < n; i++) {
        int sign = (i % 2 == 0) ? 1 : -1;
        int list = ((rand() % 100) + 1) * sign;
        insertNode(&root, list);
    }

    printList(root);

    reorderList(&root);

    printf("Reordered list: ");
    printList(root);

    deallocateList(&root);

    _CrtDumpMemoryLeaks(); // for debugging memory leak (from #define _CRTDBG_MAP_ALLOC and crtdbg.h)

    return 0;
}
