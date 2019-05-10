#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#define size 10000000 //size of the array to store elements.

int insertion_sort(int array[], int low, int high)
{
  int t,d; 
  for (int c = 1 + low; c <= high; c++) 
  {
    d = c;
    while ( d > low && array[d-1] > array[d]) {
      t = array[d];
      array[d]   = array[d-1];
      array[d-1] = t;
      d--;
    }
 }
 // printf(" \n Sorted list in ascending order:\n");
 
 // for (int c = 0; c <= high - 1; c++) {
 //   printf("%d \t", array[c]);
 // } 
  printf("\n"); 
  return 0;
}

int partition(int ary[], int low, int high)
{
  int left, right, temp, pivot, flag;
  left = low;
  pivot = right = high; 
  flag = 0;
  while(flag != 1)
  {
  	while((ary[pivot] >= ary[left]) && (pivot != left))
  	{
  		left++;
  	}
  	if(pivot == left)
  	{
  		flag = 1;
  	}
  	else if(ary[pivot] <= ary[left])
  	{
  		temp = ary[pivot];
  		ary[pivot] =  ary[left];
  		ary[left] = temp;
  		pivot = left;
  	}

  	if(flag!=1)
  	{
  	while((ary[pivot] <= ary[right]) && (pivot != right))
  	{
  		right--;
  	}
  	if(pivot == right)
  	{
  		flag = 1;
  	}
  	else if(ary[pivot] > ary[right])
  	{
  		temp = ary[pivot];
  		ary[pivot] =  ary[right];
  		ary[right] = temp;
  		pivot = right;
  	}
    }
  }
  return pivot;
}

void quick_sort(int arry[], int low, int high)
{
	int pivot;
	if(low < high)
	{
		pivot = partition(arry, low, high);
		quick_sort(arry, low, pivot - 1);
		quick_sort(arry, pivot + 1, high);
	}
}

void phybrid_sort(int myarr[], int low, int high, int cutoff)
{
	int pivot;
	if(low < high)
	{
		if(high - low > cutoff){
		pivot = partition(myarr, low, high);
		#pragma omp task
		{
			phybrid_sort(myarr, low, pivot - 1, cutoff);
		}
		#pragma omp task
		{
			phybrid_sort(myarr, pivot + 1, high, cutoff);
		}
	}
	}
}

void hybrid_sort(int myarr[], int low, int high, int cutoff)
{
	int pivot;
	if(low < high)
	{
		if(high - low > cutoff){
		pivot = partition(myarr, low, high);
		hybrid_sort(myarr, low, pivot - 1, cutoff);
		hybrid_sort(myarr, pivot + 1, high, cutoff);
	}
	}
}

void pruntime(int cutoff, double time)
{
	FILE *fptr;
	fptr = fopen("Parallel_time.txt","a");
	if(fptr == NULL) {
		printf(" couldn't write to the file\n");
	}
	fprintf(fptr, "%d,%f\n",cutoff, time);
	fclose(fptr);
}

void sruntime(int cutoff, double time)
{
	FILE *fptr;
	fptr = fopen("Serial_time.txt","a");
	if(fptr == NULL) {
		printf(" couldn't write to the file\n");
	}
	fprintf(fptr, "%d,%f\n",cutoff, time);
	fclose(fptr);
}

int main()
{
	int *arr, n, choice;
	int a;
	arr = malloc(sizeof(int) * size);
	clock_t clk;
	int cutoff = 100;
	double avt;
	char alph;
	srand(time(0));
	printf("1.Test Cutoff for Hybrid_sort  2. Quick Sort 3. Normal HS 4. Parallel Hybrid Sort");
	scanf("%d", &choice);
	switch(choice)
	{
	case 1: printf("Generating array with random elements\n");
			for(a=0; a< 10; a++)
			{
			for(int k=0; k< size; k++)
			{
			arr[k] = rand() % 10000;
			}
		/*	printf("do you wanna see the unsorted array that has been generated Y or N ? \n");
			scanf("%s", &alph);
			if (alph == 'y')
			{
				for(int l=0; l< size; l++)
				{
					printf("%d \t", arr[l]);
				}
			} */
			printf("%d run of Phybrid_sort \n", a+1);
			double clkst = omp_get_wtime();
			#pragma omp parallel num_threads(4)
				{
					#pragma omp single nowait
					{
					//	clk = clock();
        				phybrid_sort(arr, 0, size-1, cutoff);	// Created Thread 1
   						insertion_sort(arr, 0, size-1);
   				//	clk = clock() - clk;
   					}	
   				} 
   			double clke = omp_get_wtime();
   			double tot_time = clke - clkst; //this one if for a single run
   			avt = avt + (clke - clkst); // this is used to find the average time for all the cases
   			pruntime(cutoff, tot_time); // for plotting graph
   			cutoff += 10; 
   			}
		//	 for(int q=0; q<size ; q++)
		//	{
		//		printf("%d \t", arr[q]);
		//	} 
		//	double clocks = ((double)clk) / CLOCKS_PER_SEC;
			printf("\n \n Average run time for Parallel Hybrid_sort %f \n", avt/10);
			break;

	case 2: printf("Generating array with random elements\n");
			for(int k=0; k< size; k++)
			{
			arr[k] = rand() % 1000;
			}
			printf("do you wanna see the unsorted array that has been generated Y or N ? \n");
			scanf("%s", &alph);
			if (alph == 'y')
			{
				for(int l=0; l< size; l++)
				{
					printf("%d \t", arr[l]);
				}
			} 
			clk = clock();
			//int pivots = partition(arr, 0, size-1);
		//	#pragma omp parallel sections
		//	{
		//		#pragma omp section
		//		{
        			quick_sort(arr, 0, size - 1); // Created Thread 1
    	//		}
			//	#pragma omp section
			//	{
        	//		quick_sort(arr, pivots + 1, size-1);//Created Thread 2
   			//	}
		//	}
			clk = clock() - clk; 
			// for(int q=0; q<size ; q++)
		//	{
		//		printf("%d \t", arr[q]);
		//	} 
			double tikstoks = ((double)clk) / CLOCKS_PER_SEC;
			sruntime(size, tikstoks);
			printf("\n \n quick_sort took %f time \n", tikstoks);
			break;

	case 3: printf("Generating array with random elements\n");
			for(int k=0; k< size; k++)
			{
			arr[k] = rand() % 1000;
			}
			printf("do you wanna see the unsorted array that has been generated Y or N ? \n");
			scanf("%s", &alph);
			if (alph == 'y')
			{
				for(int l=0; l< size; l++)
				{
					printf("%d \t", arr[l]);
				}
			} 
			clk = clock();
        			hybrid_sort(arr, 0, size-1, cutoff);	// Created Thread 1
   					insertion_sort(arr, 0, size-1);
			clk = clock() - clk; 
		//	 for(int q=0; q<size ; q++)
	//		{
	//			printf("%d \t", arr[q]);
	//		} 
			double clockss = ((double)clk) / CLOCKS_PER_SEC;
			sruntime(size, clockss);
			printf("\n \n Run time for Hybrid_sort = %f \n", clockss);
			break;		

	case 4: printf("Generating array with random elements\n");
			for(int k=0; k< size; k++)
			{
			arr[k] = rand() % 1000;
			}
			printf("do you wanna see the unsorted array that has been generated Y or N ? \n");
			scanf("%s", &alph);
			if (alph == 'y')
			{
				for(int l=0; l< size; l++)
				{
					printf("%d \t", arr[l]);
				}
			} 
			int fcutoff = 150;
			double clkst = omp_get_wtime();
			#pragma omp parallel num_threads(4)
				{
					#pragma omp single nowait
					{
					//	clk = clock();
        				phybrid_sort(arr, 0, size-1, fcutoff);	// Created Thread 1
   						insertion_sort(arr, 0, size-1);
   				//	clk = clock() - clk;
   					}	
   				} 
   			double clke = omp_get_wtime();
   			double tot_time = clke - clkst; //this one if for a single run
		//	 for(int q=0; q<size ; q++)
		//	{
		//		printf("%d \t", arr[q]);
		//	} 
		//	double clocks = ((double)clk) / CLOCKS_PER_SEC;
   			pruntime(size, tot_time);
			printf("\n \n Run time for Parallel Hybrid_sort %f \n", tot_time);
			break;

	default : printf("Invalid choice, choose 1, 2, 3 or 4\n");
	}
	//printf("Now testing the efficiency \n");
	return 0;
}

