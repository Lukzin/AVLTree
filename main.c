#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode* AVLTree
struct AVLNode
{
    ElementType Data;
    struct AVLNode* Left;
    struct AVLNode* Right;
    int Height;
};
typedef AVLTree Position;

int main()
{
    printf("Hello world!\n");
    return 0;
}

int Max(int a, int b)
{
    return a>b ? a:b;
}

int GetHeight(AVLTree A)
{
    if(!A) return 0;
    return A->Height;
}

int GetBalance(AVLTree A)
{
    return(GetHeight(A->Left) - GetHeight(A->Right));
}

AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(A->Height, GetHeight(B->Right)) + 1;
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
    A->Left = SingleRightRotation(A->Left);
    return(SingleLeftRotation(A));
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->Right = SingleLeftRotation(A->Right);
    return(SingleRightRotation(A));
}

AVLTree Insert(AVLTree T, ElementType X)
{
    if(!T)
    {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    }
    else if(X < T->Data)
    {
        T->Left = Insert(T->Left, X);
        if(GetBalance(T) > 1)
        {
            if(GetBalance(T->Left) >= 0)
                T = SingleLeftRotation(T);
            else
                T = DoubleLeftRightRotation(T);
        }
    }
    else if(X > T->Data)
    {
        T->Right = Insert(T->Right, X);
        if(GetBalance(T) < -1)
        {
            if(GetBalance(T->Right) <= 0)
                T = SingleRightRotation(T);
            else
                T = SingleRightLeftRotation(T);
        }
    }

    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;

    return T;
}

AVLTree Delete(AVLTree T, ElementType X)
{
    AVLTree tmp;
    if(!T) return NULL;
    if(X < T->Data)
    {
        T->Left = Delete(T->Left, X);
        if(GetBalance(T) < -1)
        {
            if(GetBalance(T->Right) <= 0)
                T = SingleRightRotation(T);
            else
                T = DoubleRightLeftRotation(T);
        }
    }
    else if(X > T->Data)
    {
        T->Right = Delete(T->Right, X);
        if(GetBalance(T) > 1)
        {
            if(GetBalance(T->Left) >= 0)
                T = SingleLeftRotation(T);
            else
                T = SingleLeftRightRotation(T);
        }
    }
    else
    {
        if(!T->Left && !T->Right) /* T is a leaf node */
        {
            tmp = T;
            T = NULL;
            free(tmp);
        }
        if(T->Left) /* T has only one left child */
        {
            tmp = T->Left;
            *T = *tmp;
            free(tmp);
        }
        else(T->Right) /* T has only one right child */
        {
            tmp = T->Right;
            *T = *tmp;
            free(tmp);
        }
        else /* T has both left and right children */
        {
            tmp = FindMin(T->Right);
            T->Data = tmp->Data;
            T->Right = Delete(T->Right, tmp->Data);
        }
    }

    if(!T) return NULL;
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
    Return T;
}
