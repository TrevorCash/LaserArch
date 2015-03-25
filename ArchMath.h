/*
 * ArchMath.h
 *
 * Created: 2/17/2015 10:17:41 AM
 *  Author: 7002815
 */ 

//CONTAINS convienience math for the laser arch.


#ifndef ARCHMATH_H_
#define ARCHMATH_H_

#define ARCH_PIT_TICK_HERTZ 5000000//5 Megahertz from k20 data sheet
#define ARCH_PIT_TICK_PERIOD_NS 200//200 nano seconds = 1/(5megahertz)

#define ARCH_PIT_TIMER_FROM_NANOSEC(NSEC) (NSEC/ARCH_PIT_TICK_PERIOD_NS)
#define ARCH_PIT_TIMER_FROM_USEC(USEC) (USEC/(ARCH_PIT_TICK_PERIOD_NS/(1000.0)))
#define ARCH_PIT_TIMER_FROM_MSEC(MSEC) (MSEC/(ARCH_PIT_TICK_PERIOD_NS/(1000000.0)))


//quick sort from http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
void quick_sort (int *a, int n) {
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
	quick_sort(a, i);
	quick_sort(a + i, n - i);
}




#endif /* ARCHMATH_H_ */