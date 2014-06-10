#include <stdio.h>

/* qusort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
  int i, last;
  void swap(int v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than 2 elements */
  swap(v, left, (left + right)/2); /*  move partition elem */
  last = left;                     /* to v[0] */
  for (i = left + 1; i <= right; i++) /* partition */
    if (v[i] < v[left])
      swap(v, ++last, i);
  swap(v, left, last);      /* restore partition elem */
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/*  swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int main() 
{
  int i;
  int array[20];

  for (i = 0; i < 20; i++)
  {
    if (i != 0)
      array[i] = (i * 6) % 5;
    else
      array[i] = 0;
  }

  for (i = 0; i < 20; i++)
    printf("%d, ", array[i]);
  printf("\n");
  
  qsort(array, 0, 19);

  for (i = 0; i < 20; i++)
    printf("%d, ", array[i]);
  printf("\n");
}
