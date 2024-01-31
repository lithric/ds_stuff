#include "project1.h"

void sortPointsByXCoordinate(Point[]);
bool turnsLeft(Point,Point,Point);
bool turnsRight(Point,Point,Point);
Point* findHull(Point[],int);

const unsigned int MAX_POINTS = 100;

int main() {
    return 0;
}



void sortPointsByXCoordinate(Point p[],int size) {
    bool finished = false;
    bool noChanges = true;

    while (!finished) {
        noChanges = true;
        for (int i=0; i<size-1; i++) {
            if (p[i].x > p[i+1].x) {
                (p[i],p[i+1])=(p[i+1],p[i]);
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

Point* findHull(Point p[],int k) {
    Point lower[MAX_POINTS];
    Point upper[MAX_POINTS];
    Point hull[MAX_POINTS*2];
    int t;
    int u;

    sortPointsByXCoordinate(p,k);

    lower[0] = p[0];
    t = 0;
    for (int i=1;i<k-1;i++) {
        while (t>0 && !turnsLeft(lower[t-1],lower[t],p[i])) {
            t--;
        }
        t++;
        lower[t] = p[i];
    }

    upper[0] = p[k-1];
    u = 0;
    for (int i=k-2;i>0;i--) {
        while (u>0 && !turnsLeft(upper[u-1],upper[u],p[i])) {
            u--;
        }
        u++;
        upper[u] = p[i];
    }

    for (int i=0;i<t-1;i++) {
        hull[i] = lower[i];
    }
    for (int i=0;i<u-1;i++) {
        hull[t-1+i] = upper[i];
    }

    return hull;
}