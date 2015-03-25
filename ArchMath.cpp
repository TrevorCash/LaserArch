/*
 * ArchMath.cpp
 *
 * Created: 3/25/2015 12:53:53 PM
 *  Author: 7002815
 */ 

#include "ArchMath.h"

//quick sort from http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
void quick_sort_int(int *a, int n) {
	int i, j, p, t;
	if (n < 2)
	return;
	p = a[n / 2];
	for (i = 0, j = n - 1;; i++, j--) {
		while (a[i] < p)
		i++;
		while (p < a[j])
		j--;
		if (i >= j)
		break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	quick_sort_int(a, i);
	quick_sort_int(a + i, n - i);
}



void quick_sort_fingerCon(ArchFingerBlobConnection *a, int n)
{
	int i, j, p;
	ArchFingerBlobConnection t;
	if (n < 2)
	return;
	p = a[n / 2].distance;
	for (i = 0, j = n - 1;; i++, j--) {
		while (a[i].distance < p)
		i++;
		while (p < a[j].distance)
		j--;
		if (i >= j)
		break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	quick_sort_fingerCon(a, i);
	quick_sort_fingerCon(a + i, n - i);	
}

