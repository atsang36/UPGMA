#include "dynmatrix.h"
#include <iostream>

using namespace std;


void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name)
// adds a cluster (at the tail) and the corresponding row and column to data structure
// distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode
{    if (head == NULL) {                                //if no nodes present make one
    ClusterNode *newClustNode = new ClusterNode();
    newClustNode->name = name;
    newClustNode->prev = tail;
    newClustNode->next = NULL;
    newClustNode->row = NULL;
    newClustNode->column = NULL;
    head = newClustNode;
    tail = newClustNode;
    head->next = NULL;
    head->row = new DistanceNode();
    head->row->distance = 0.0;
    head->row->nextInColumn = NULL;
    head->row->nextInRow = NULL;
    head->column = head->row;
} else {

    ClusterNode *newClustNode = new ClusterNode();
    newClustNode->name = name;
    newClustNode->prev = tail;
    newClustNode->next = NULL;
    newClustNode->row = NULL;
    newClustNode->column = NULL;
    tail->next = newClustNode;
    newClustNode->prev = tail;
    newClustNode->next = NULL;
    

    DistanceNode *newDistNode1 = new DistanceNode();
    newDistNode1->distance = 0;
    newDistNode1->nextInRow = NULL;
    newDistNode1->nextInColumn = NULL;
    tail->column->nextInRow = newDistNode1;
    newClustNode->column = newDistNode1;
    DistanceNode *t1 = tail->column;
    DistanceNode *t2 = newDistNode1;
    

    while (t1->nextInColumn) {

        t2->nextInColumn = new DistanceNode();
        t2->nextInColumn->distance = 0;
        t2->nextInColumn->nextInRow = NULL;
        t2->nextInColumn->nextInColumn = NULL;
        t1->nextInColumn->nextInRow = t2->nextInColumn;
        t1 = t1->nextInColumn;
        t2 = t2->nextInColumn;

    }
    

    DistanceNode *newDistNode2 = new DistanceNode();
    newDistNode2->distance = 0;
    newDistNode2->nextInRow = NULL;
    newDistNode2->nextInColumn = NULL;
    newClustNode->row = newDistNode2;
    tail->row->nextInColumn = newDistNode2;
    DistanceNode *t3 = tail->row;
    DistanceNode *t4 = newDistNode2;
 
    while (t3->nextInRow) {

        t4->nextInRow = new DistanceNode();
        t4->nextInRow->distance = 0;
        t4->nextInRow->nextInRow = NULL;
        t4->nextInRow->nextInColumn = NULL;
        t3->nextInRow->nextInColumn = t4->nextInRow;
        t3 = t3->nextInRow;
        t4 = t4->nextInRow;
    }
    

    tail = tail->next;                     //updates tail
}
}


void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved)
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated
{
    
    if (head == toBeRemoved){
        
        ClusterNode* temp = head;
        ClusterNode* tempNext = temp->next;   //tempNext is the  clusternode to the right of head and row/column in front of the rows/columns to be deleted
        
        DistanceNode* tempRow = temp->row;
        DistanceNode* tempCol = temp->column;
        
        
        while (tempRow != NULL && tempCol != NULL && tempNext != NULL){   //delete and move on from the node on the top left corner
            if (tempRow == tempCol){
                DistanceNode* tempSame = tempRow;
                tempRow = tempSame->nextInRow;
                tempCol = tempSame->nextInColumn;
                delete tempSame;
            }
            
            DistanceNode* tempR = tempRow;                //these pointers are used for deletion
            DistanceNode* tempC = tempCol;
            
            tempNext->row = tempCol->nextInRow;
            tempNext->column  = tempRow->nextInColumn;          //assigning new rows and columns for each clusternode besides the head
            
            tempRow = tempRow->nextInRow;
            tempCol = tempCol->nextInColumn;
            
            
            tempNext = tempNext->next;
            
            if (tempNext != NULL) {
                delete tempR;
                delete tempC;
            }
            
        }
        
        temp->row = NULL;
        temp->column = NULL;
        
        if (head->next == NULL && head->prev == NULL){
            delete temp;
            head = NULL;
            tail = NULL;
            return;
        }
        else{
        head = head->next;              //set the respective areas
        delete temp;
        head->prev = NULL;
        }
        
    }
    
    else if (tail == toBeRemoved){
        ClusterNode* temp = tail;
        ClusterNode* tempPrev = temp->prev;             // the cluster node before the one to be removed
        
        DistanceNode* prevRow = tempPrev->row;
        DistanceNode* prevCol = tempPrev->column;
        
        DistanceNode* tempRow = temp->row;
        DistanceNode* tempCol = temp->column;
        
        while(tempRow != NULL && tempCol != NULL){       //at the last node where column and row are the same
            if (tempRow == tempCol){
                DistanceNode* tempSame = tempRow;
                tempCol = NULL;
                tempRow = NULL;
                delete tempSame;
                break;
                
            }
            
            DistanceNode* tempR = tempRow;
            DistanceNode* tempC = tempCol;
            
            
            prevRow->nextInColumn = NULL;               //make the next rows and colmuns of the previous node null
            prevCol->nextInRow = NULL;
            
            tempRow = tempRow->nextInRow;
            tempCol = tempCol->nextInColumn;
            prevRow = prevRow->nextInRow;
            prevCol = prevCol->nextInColumn;
            
            delete tempR;
            delete tempC;
            
        }
        
        
        temp->row = NULL;
        temp->column = NULL;
        
        tail = tail->prev;
        delete temp;
        tail->next = NULL;
    }
    
    else{
        ClusterNode* temp = head;
        while(temp->next != NULL){
            if (temp == toBeRemoved){
                
                ClusterNode* tempPrev = temp->prev;            // the cluster node before the one to be removed
                
                DistanceNode* prevRow = tempPrev->row;
                DistanceNode* prevCol = tempPrev->column;
                
                DistanceNode* tempRow = temp->row;
                DistanceNode* tempCol = temp->column;
                
                while (tempRow != NULL && tempCol != NULL){    //when the node for column and row are the same
                    if (tempRow == tempCol){
                        DistanceNode* tempSame = tempRow;
                        tempRow = tempSame->nextInRow;
                        tempCol = tempSame->nextInColumn;
                        delete tempSame;
                    }
                    
                    DistanceNode* tempR = tempRow;
                    DistanceNode* tempC = tempCol;
                    
                    prevRow->nextInColumn = tempRow->nextInColumn;       //connect the colmuns and rows of the previous node with the next one
                    prevCol->nextInRow = tempCol->nextInRow;
                    
                    tempRow = tempRow->nextInRow;
                    tempCol = tempCol->nextInColumn;
                    prevRow = prevRow->nextInRow;
                    prevCol = prevCol->nextInColumn;
                    
                    delete tempR;
                    delete tempC;
                    
                    
                }
                temp->prev->next = temp->next;     
                temp->next->prev = temp->prev;
                delete temp;
            }
            temp = temp->next;
        }
    }
}




void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D)
// finds the minimum distance (between two different clusters) in the data structure
// and returns the two clusters via C and D
{   ClusterNode* tail = head;
    
    while (tail->next != NULL){
        tail = tail->next;
        //determine the tail
    }
    
    C = head;
    D = tail;

    ClusterNode* bestC = C;
    ClusterNode* bestD = D;
    double lowestC = 9999.99;
    double lowestD = 9999.99;

    while(C != NULL){
        DistanceNode* currentCol = C->column;
        while(currentCol != NULL){
            double valueC = currentCol->distance;
                                                         //compare every distance value in C and save the lowest distance and the node containing it
            if(valueC < lowestC && valueC != 0){
                lowestC = valueC;
                bestC = C;
            }
            currentCol = currentCol->nextInColumn;
        }
        C = C->next;
        
    }

    
    while(D != NULL){
        DistanceNode* currentColD = D->column;
        while(currentColD != NULL){
            double valueD = currentColD->distance;
            if(valueD < lowestD && valueD != 0 && D != bestC){
                lowestD = valueD;
                                                             //compare every distance value in C and save the lowest distance and the node containing it
                bestD = D;
            }
            currentColD = currentColD->nextInColumn;
        }
        D = D->prev;
        
    }

    //make C and D into the nodes with the lowest distance
    C = bestC;
    D = bestD;

    
    
}



