#include <iostream>
#include <fstream>
#include <algorithm>
#include "dynmatrix.h"

using namespace std;

// construct a string representation

void usage() {
    cerr << "Usage: upgma species.txt" << endl;
}


void printRowByRow(ClusterNode *head) {
    while (head) {
        cout <<head->name<<":\t";
        DistanceNode *curD = head->row;
        while (curD) {
            cout <<curD->distance<<"\t";
            curD = curD->nextInRow;
        }
        cout <<endl;
        head = head->next;
    }
}

void printColumnByColumn(ClusterNode *head) {
    while (head) {
        cout <<head->name<<":\t";
        DistanceNode *curD = head->column;
        while (curD) {
            cout <<curD->distance<<"\t";
            curD = curD->nextInColumn;
        }
        cout <<endl;
        head = head->next;
    }
}



int main( int argc, char *argv[] ) {
    if( argc != 2 ) {
        usage();
        return 0;
    }
    
    // let's start with empty DynMatrix:
    ClusterNode* head = NULL;
    ClusterNode* tail = NULL;
    
    int n = 0; // number of species
    ifstream fin( argv[1] );
    if( fin.is_open() ) {
        // read species:
        string species;
        while ((fin.peek() != '\n') && (fin >> species)) {
            n++;
            // YOUR CODE HERE: replace print statemnt by a code that insert a new species into DynMatrix
            addCluster(head, tail, species);
        }
        // read distances:
        DistanceNode *column = head->column;
        DistanceNode *row = head->row;
        for (int i=0; i < n && fin; i++) {
            for (int j = 0; j < n && fin; j++) {
                double d;
                fin >> d;
                column->distance = d;
                column = column->nextInRow;
            }
            row = row->nextInColumn;
            column = row;
        }
        fin.close();
    }
    
//    printRowByRow(head);
//    printColumnByColumn(head);

    
    while(head != tail){
        ClusterNode *C;
        ClusterNode *D;
        findMinimum(head, C, D);
        
        string name1 = C->name;
        int speciesCount1 = count(name1.begin(),name1.end(),',') + 1;
        string name2 = D->name;
        int speciesCount2 = count(name2.begin(),name2.end(),',') + 1;
        
        DistanceNode* t1 = C->row;
        DistanceNode* t2 = D->row;
        DistanceNode* t3 = D->column;
        
        D->name = "(" + name2 + "," + name1 + ")";
        
        while (t2){
            if ((t2-> nextInRow == t3)|| (t2 == head-> row)){
                t2 -> distance = 0;
            } else {
                (t2 -> distance) = ((speciesCount1 * (t1 -> distance) + speciesCount2 * (t2 -> distance))/(speciesCount1 + speciesCount2));
                t3->distance = t2 -> distance;
            }
            t2 = t2 -> nextInRow;
            t1 = t1 -> nextInRow;
            t3 = t3 -> nextInColumn;
        }
        
        removeCluster(head, tail, C);
        if ((head -> next) == tail) {
            head -> row -> distance = 0;
            tail -> row -> nextInRow -> distance = 0;
        }

       // string name = "(" + C->name + "," + D->name + ")";
//        
//        addCluster(*&head, *&tail, name);
//        
//        removeCluster(*&head, *&tail, *&C);
//        removeCluster(*&head, *&tail, *&D);
    }
    
    // print the name of the last remaining cluster
    if (head)                                    
        cout << head->name << endl;

    
    // BONUS (optional): print the tree in a nice way
    
    return 0;
}
