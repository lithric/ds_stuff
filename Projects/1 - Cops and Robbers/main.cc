#include <iostream>
#include <fstream>
#include "fraction.h"
#include "point.h"

using namespace std;

void sortPointsByXCoordinate(Point[]);
bool turnsLeft(Point,Point,Point);
bool turnsRight(Point,Point,Point);
bool isInsideHull(Point,Point[],int);
Point* findHull(Point[],int,int&);

const unsigned int MAX_POINTS = 100;
const bool DEBUG_LOG_ENABLED = false;
const bool VERBOSE_OUTPUT_ENABLED = true;
const bool VERBOSE_INPUT_ENABLED = true;

int main() {
    int sizeCops,sizeRobbers,sizePeople;
    Point cops[MAX_POINTS],robbers[MAX_POINTS],people[MAX_POINTS];
    int safePeople = 0, robbedPeople = 0, vulnerablePeople = 0;
    bool inputNotValid = true;
    bool firstRun = true;
    while (inputNotValid) {
        if (firstRun&&VERBOSE_INPUT_ENABLED) {cout << "Enter number of cops (3-100): ";}
        cin >> sizeCops;
        if (!(sizeCops>=3&&sizeCops<=100)) {
            if (VERBOSE_INPUT_ENABLED) {
                cout << "Input number of cops is invalid, try again: ";
            }
            firstRun = false;
            continue;
        }
        inputNotValid = false;
    }
    inputNotValid = true;
    firstRun = true;
    while (inputNotValid) {
        if (firstRun&&VERBOSE_INPUT_ENABLED) {cout << "Enter number of robbers (3-100): ";}
        cin >> sizeRobbers;
        if (!(sizeRobbers>=3&&sizeRobbers<=100)) {
            if (VERBOSE_INPUT_ENABLED) {
                cout << "Input number of robbers is invalid, try again: ";
            }
            firstRun = false;
            continue;
        }
        inputNotValid = false;
    }
    inputNotValid = true;
    firstRun = true;
    while (inputNotValid) {
        if (firstRun&&VERBOSE_INPUT_ENABLED) {cout << "Enter number of people (>=1): ";}
        cin >> sizePeople;
        if (!(sizePeople>=1)) {
            if (VERBOSE_INPUT_ENABLED) {
                cout << "Input number of people is invalid, try again: ";
            }
            firstRun = false;
            continue;
        }
        inputNotValid = false;
    }
    if (VERBOSE_INPUT_ENABLED) {
        cout << "Now Entering: Points for cops" << endl;
    }
    for (int i=0;i<sizeCops;i++) {
        if (VERBOSE_INPUT_ENABLED) {
            cout << "Point for cop " << i+1 << ": ";
        }
        cin >> cops[i];
    }
    if (VERBOSE_OUTPUT_ENABLED) {
        cout << endl;
        cout << "Now Displaying: Points for cops" << endl;
        for (int i=0;i<sizeCops;i++) {
            cout << "Point for cop " << i+1 << ": " << cops[i] << endl;
        }
        cout << endl;
    }
    if (VERBOSE_INPUT_ENABLED) {
        cout << endl;
        cout << "Now Entering: Points for robbers" << endl;
    }
    for (int i=0;i<sizeRobbers;i++) {
        if (VERBOSE_INPUT_ENABLED) {
            cout << "Point for robber " << i+1 << ": ";
        }
        cin >> robbers[i];
    }
    if (VERBOSE_OUTPUT_ENABLED) {
        cout << endl;
        cout << "Now Displaying: Points for robbers" << endl;
        for (int i=0;i<sizeRobbers;i++) {
            cout << "Point for robber " << i+1 << ": " << robbers[i] << endl;
        }
        cout << endl;
    }
    
    if (VERBOSE_INPUT_ENABLED) {
        cout << endl;
        cout << "Now Entering: Points for people" << endl;
    }
    for (int i=0;i<sizePeople;i++) {
        if (VERBOSE_INPUT_ENABLED) {
            cout << "Point for person " << i+1 << ": ";
        }
        cin >> people[i];
    }
    if (VERBOSE_OUTPUT_ENABLED) {
        cout << endl;
        cout << "Now Displaying: Points for people" << endl;
        for (int i=0;i<sizePeople;i++) {
            cout << "Point for person " << i+1 << ": " << people[i] << endl;
        }
        cout << endl;
    }
    if (VERBOSE_INPUT_ENABLED||VERBOSE_OUTPUT_ENABLED) {
        cout << endl;
    }

    int copsHullSize,robbersHullSize;
    if (DEBUG_LOG_ENABLED) {
        cout << "Finding Hull For Cops & Robbers..." << endl;
        cout << "Finding Hull For Cops..." << endl;
    }
    Point* copsHull = findHull(cops,sizeCops,copsHullSize);
    if (DEBUG_LOG_ENABLED) {
        cout << "Finding Hull For Cops Done!" << endl;
        cout << "Cops Hull Size: " << copsHullSize << endl;
        cout << "Now Displaying: Cops Hull" << endl;
        for (int i=0;i<copsHullSize;i++) {
            cout << copsHull[i] << endl;
        }
        cout << endl;
    }
    
    if (DEBUG_LOG_ENABLED) {
        cout << "Finding Hull For Robbers..." << endl;
    }
    Point* robbersHull = findHull(robbers,sizeRobbers,robbersHullSize);
    if (DEBUG_LOG_ENABLED) {
        cout << "Finding Hull For Robbers Done!" << endl;
        cout << "Robbers Hull Size: " << robbersHullSize << endl;
        cout << "Now Displaying: Robbers Hull" << endl;
        for (int i=0;i<robbersHullSize;i++) {
            cout << robbersHull[i] << endl;
        }
        cout << endl;
    }
    
    if (DEBUG_LOG_ENABLED) {
        cout << "Determining Safety of People...";
    }
    for (int i=0;i<sizePeople;i++) {
        if (isInsideHull(people[i],copsHull,copsHullSize)) {
            safePeople++;
        }
        else if (isInsideHull(people[i],robbersHull,robbersHullSize)) {
            robbedPeople++;
        }
        else {
            vulnerablePeople++;
        }
    }
    if (DEBUG_LOG_ENABLED) {
        cout << " Done!" << endl;
    }
    
    if (VERBOSE_OUTPUT_ENABLED) {
        cout << "Now Displaying: Safety of people" << endl;
    }
    cout << "Safe: " << safePeople << endl;
    cout << "Robbed: " << robbedPeople << endl;
    cout << "In Danger: " << vulnerablePeople << endl;
    if (VERBOSE_OUTPUT_ENABLED) {
        cout << endl;
    }

    if (DEBUG_LOG_ENABLED) {
        cout << "Cleaning Up Memory..." << endl;

        cout << "Deleting Hulls From Memory..." << endl;
        cout << "Deleting Cops Hull...";
    }
    delete[] copsHull;
    if (DEBUG_LOG_ENABLED) {
        cout << " Done!" << endl;
        cout << "Deleting Robbers Hull...";
    }
    delete[] robbersHull;
    if (DEBUG_LOG_ENABLED) {
        cout << " Done!" << endl;
        
        cout << "Cleaning Up Memory Done!" << endl;
        cout << endl;
        
        cout << "Ending Program..." << endl;
    }

    return 0;
}

void sortPointsByXCoordinate(Point p[],int size) {
    bool finished = false;
    bool noChanges = true;
    Point tempPoint;

    while (!finished) {
        noChanges = true;
        for (int i=0; i<size-1; i++) {
            if (p[i].x > p[i+1].x) {
                tempPoint = p[i];
                p[i] = p[i+1];
                p[i+1] = tempPoint;
                noChanges = false;
            }
        }
        if (noChanges) {
            finished = true;
        }
    }
}

bool turnsLeft(Point a,Point b,Point c) {
    Fraction d;

    d = (b-a)*(c-a);
    return d>0;
}

bool turnsRight(Point a,Point b,Point c) {
    Fraction d;

    d = (b-a)*(c-a);
    return d<0;
}

Point* findHull(Point p[],int k,int& hullSize) {
    Point lower[k];
    Point upper[k];
    int t;
    int u;

    if (DEBUG_LOG_ENABLED) {
        cout << "Executing: Find Hull" << endl;
        cout << "Now Displaying: Received Points" << endl;
        for (int i=0;i<k;i++) {
            cout << p[i] << endl;
        }
        cout << endl;
    }
    
    if (DEBUG_LOG_ENABLED) {
        cout << "Sorting Points...";
    }
    sortPointsByXCoordinate(p,k); // Sort P by x-coordinate
    if (DEBUG_LOG_ENABLED) {
        cout << " Done!" << endl;
    }

    if (DEBUG_LOG_ENABLED) {
        cout << "Now Displaying: Sorted Points" << endl;
        for (int i=0;i<k;i++) {
            cout << p[i] << endl;
        }
        cout << endl;
    }

    lower[0] = p[0]; // lower[0] <- p_0
    t = 0; // t <- 0
    if (DEBUG_LOG_ENABLED) {
        cout << "Assigning Lower Points...";
    }
    for (int i=1;i<=k-1;i++) { // for i <- 1 to k-1 do
        while (t>0 && !turnsLeft(lower[t-1],lower[t],p[i])) {
            t--; // t <- t-1
        }
        t++; // t <- t+1
        lower[t] = p[i]; // lower[t]<-p_i
    }
    if (DEBUG_LOG_ENABLED) {
        cout << " Done!" << endl;
    }

    upper[0] = p[k-1]; // upper[0] <- p_(k-1)
    u = 0; // u <- 0
    if (DEBUG_LOG_ENABLED) {
        cout << "Assigning Upper Points...";
    }
    for (int i=k-2;i>=0;i--) { // for i <- k-2 downto 0 do
        while (u>0 && !turnsLeft(upper[u-1],upper[u],p[i])) {
            u--;
        }
        u++; // u <- u+1
        upper[u] = p[i]; // upper[u]<-p_i
    }
    if (DEBUG_LOG_ENABLED) {
        cout << " Done!" << endl;
    }

    hullSize = t+u;
    if (DEBUG_LOG_ENABLED) {
        cout << "Hull Size: " << hullSize << endl;
    }
    
    Point* hull;
    hull = new Point[hullSize]; // memory optimization

    for (int i=0;i<=t-1;i++) {
        hull[i] = lower[i];
    }
    for (int i=0;i<=u-1;i++) {
        hull[t+i] = upper[i];
    }

    if (DEBUG_LOG_ENABLED) {
        cout << "Now Displaying: Current Hull" << endl;
        for (int i=0;i<hullSize;i++) {
            cout << hull[i] << endl;
        }
        cout << endl;
        cout << "Returning Hull" << endl;
    }

    return hull; // return lower[0],lower[1],...,lower[t-1],upper[0],upper[1],...,upper[u-1]
}

bool isInsideHull(Point P,Point H[],int k) {
    int j;
    for (int i=0;i<=k-1;i++) { // for i <- 0 to k-1 do
        j = (i + 1) % k; // j <- (i+1) mod k
        if (turnsRight(P,H[i],H[j])) { // if P->h_i->h_j turns right then
            return false;
        }
    }
    return true;
}