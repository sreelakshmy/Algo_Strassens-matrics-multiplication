#include <iostream>
#include <ctime>
#include<cstdlib>
using namespace std ;
void strassen ( int ** a, int **b, int **c, int size );
void naive ( int ** a, int **b, int**c, int size );
void sum (int ** a, int ** b, int **result, int size) ;
void sub( int ** a, int **b, int **result, int size) ;
int ** matrix_allocation ( int size ) ;
void matrix_deallocation( int ** matrix, int size );
int main ()
{
		
	int m=0;
        cout<<"Enter the size of the matrix:(m):";
        cin>>m;     
		  time_t start1 = time(0);
		  clock_t start =clock() ;
                  int ** A = new int*[m ] ;
   		  int ** B = new int*[m ] ;
		  int ** product = new int* [m ] ;
		  A = matrix_allocation(m ) ;
		  B = matrix_allocation(m ) ;
		  product =matrix_allocation (m ) ;
		  for (int i = 0 ;i < m ; i++ ) {
			for( int j = 0; j < m ; j++ ){
				A[i ][ j ] =rand()%1000+1 ;
			}
	  	  }
		  for (int i = 0 ;i < m ; i++ ) {
			for( int j = 0; j < m ; j++ ){
				B[i ][ j ] =rand()%1000+1;
			}
		  }
		  strassen(A,B,product,m ) ;
                  cout<<"\n\n Final matrix is :"<<endl;
		  for(int i=0;i<m;i++)
        	  {
         		for(int j=0;j<m;j++)
                	{
	        	cout<<product[i][j]<<" ";
	        	}
        		cout<<"\n";
		  }
		  matrix_deallocation( A, m) ;
		  matrix_deallocation( B, m) ;
		  matrix_deallocation( product,m) ;
                  time_t end1 = time(0);
                  double time = difftime(end1, start1) * 1000.0;
                  cout<<"\nReal time is:"<<time;
		  clock_t end = clock() ;
		  double cpu_time =(double) ( end - start )/CLOCKS_PER_SEC ;
		  cout <<"\nProcessing time is(sec) :"<< cpu_time <<endl ;
	return 0 ;
}
void strassen ( int ** a, int **b, int**c, int size )
{
					// when the size is up to 50 use naive algorithm
	if ( size<=50 )
        {  
         naive(a,b,c,size);
	 return;
        }
					// When size is larger than 50 use strassens
	int newSize = size/ 2 ;
	int **a11, ** a12, **a21,**a22 ;
	int **b11, ** b12, **b21,**b22 ;
	int **c11, ** c12, **c21,**c22 ;
	int **p1, **p2, ** p3, ** p4,**p5, ** p6, **p7 ;

					// memory allocation:

	a11 = matrix_allocation(newSize ) ;
	a12 = matrix_allocation(newSize ) ;
	a21 = matrix_allocation(newSize ) ;
	a22 = matrix_allocation(newSize ) ;
	b11 = matrix_allocation(newSize ) ;
	b12 = matrix_allocation(newSize ) ;
	b21 = matrix_allocation(newSize ) ;
	b22 = matrix_allocation(newSize ) ;
	c11 = matrix_allocation(newSize ) ;
	c12 = matrix_allocation(newSize ) ;
	c21 = matrix_allocation(newSize ) ;
	c22 = matrix_allocation(newSize ) ;
	p1 = matrix_allocation(newSize ) ;
	p2 = matrix_allocation(newSize ) ;
	p3 = matrix_allocation(newSize ) ;
	p4 = matrix_allocation(newSize ) ;
	p5 = matrix_allocation(newSize ) ;
	p6 = matrix_allocation(newSize ) ;
	p7 = matrix_allocation(newSize ) ;
	int **anew =matrix_allocation (newSize ) ;
	int **bnew =matrix_allocation(newSize ) ;
	int i, j ;

					//submatrices:

	for ( i = 0 ; i < newSize; i++) {
		for ( j = 0 ; j <newSize; j++ ) {
			a11 [ i ][ j ]= a [ i ][ j ] ;
			a12 [ i ][ j ]= a [ i ][ j + newSize ] ;
			a21 [ i ][ j ]= a [ i + newSize][ j ] ;
			a22 [ i ][ j ]= a [ i + newSize][ j + newSize ];
			b11 [ i ][ j ]= b [ i ][ j ] ;
			b12 [ i ][ j ]= b [ i ][ j + newSize ] ;
			b21 [ i ][ j ]= b [ i + newSize][ j ] ;
			b22 [ i ][ j ]= b [ i + newSize][ j + newSize ];
		}
	}
					// Calculating p1 to p7:

	sum( a11, a22, anew,newSize) ;					 // a11 + a22
	sum( b11, b22, bnew,newSize) ; 					 // b11 + b22
	strassen ( anew, bnew,p1, newSize) ;				 // p1 = (a11+a22) *(b11+b22)
	sum( a21, a22, anew,newSize) ;					 // a21 + a22
	strassen ( anew, b11, p2,newSize) ;				 // p2 = (a21+a22) * (b11)
	sub( b12, b22, bnew,newSize) ;					 // b12 - b22
	strassen ( a11, bnew, p3,newSize) ; 				 // p3 = (a11) * (b12 -b22)
	sub ( b21, b11, bnew,newSize) ;					 // b21 - b11
	strassen ( a22, bnew, p4,newSize) ;				 // p4 = (a22) * (b21 -b11)
	sum( a11, a12, anew,newSize) ;					 // a11 + a12
	strassen ( anew, b22, p5,newSize) ; 				 // p5 = (a11+a12) * (b22)
	sub ( a21, a11, anew,newSize) ;					 // a21 - a11
	sum( b11, b12, bnew,newSize) ; 					 // b11 + b12
	strassen ( anew, bnew,p6, newSize) ; 				 // p6 = (a21-a11) *(b11+b12)
	sub ( a12, a22, anew,newSize) ; 			         // a12 - a22
	sum( b21, b22, bnew,newSize) ; 					 // b21 + b22
	strassen ( anew, bnew,p7, newSize) ;                             // p7 = (a12-a22) *(b21+b22)
					
					// calculating c21, c21,c11 e c22:

	sum( p3, p5, c12,newSize) ; 					 // c12 = p3 + p5
	sum( p2, p4, c21,newSize) ;					 // c21 = p2 + p4
	sum( p1, p4, anew,newSize) ;					 // p1 + p4
	sum( anew, p7, bnew,newSize) ;					 // p1 + p4 + p7
	sub ( bnew, p5, c11,newSize) ;				         // c11 = p1 + p4 - p5 + p7
	sum( p1, p3, anew,newSize) ;					 // p1 + p3
	sum( anew, p6, bnew,newSize) ;					 // p1 + p3 + p6
	sub ( bnew, p2, c22,newSize) ;				 	 // c22 = p1 + p3 - p2 + p6

				// Grouping the results obtained in a single matrix:

	for ( i = 0 ; i <newSize ; i ++) {
		for ( j = 0 ; j <newSize ; j ++ ) {
			c [i ][ j ] =c11 [ i][ j ] ;
			c [i ][ j +newSize] = c12 [ i ][ j] ;
			c [i +newSize][ j] = c21 [ i][ j ] ;
			c [i +newSize][ j + newSize] = c22 [i ][ j ];
		}
	}

  				// deallocating memory

	matrix_deallocation( a11, newSize) ;
	matrix_deallocation( a12, newSize) ;
	matrix_deallocation( a21, newSize) ;
	matrix_deallocation( a22, newSize) ;
	matrix_deallocation( b11, newSize) ;
	matrix_deallocation( b12, newSize) ;
	matrix_deallocation( b21, newSize) ;
	matrix_deallocation( b22, newSize) ;
	matrix_deallocation( c11, newSize) ;
	matrix_deallocation( c12, newSize) ;
	matrix_deallocation( c21, newSize) ;
	matrix_deallocation( c22, newSize) ;
	matrix_deallocation( p1, newSize) ;
	matrix_deallocation( p2, newSize) ;
	matrix_deallocation( p3, newSize) ;
	matrix_deallocation( p4, newSize) ;
	matrix_deallocation( p5, newSize) ;
	matrix_deallocation( p6, newSize) ;
	matrix_deallocation( p7, newSize) ;
	matrix_deallocation( anew, newSize) ;
	matrix_deallocation( bnew, newSize) ;
} 
void naive ( int ** a, int **b, int**c, int size )
{
	for(int i=0;i<size;i++)
	{
	  for(int j=0;j<size;j++)
	  {
                c[i][j]=0;
		for(int k=0;k<size;k++)
                {
		  c[i][j]=c[i][j]+(a[i][k] * b[k][j]);
		}
	  }
	}
    //    for(int i=0;i<size;i++)
    //    {
    //      for(int j=0;j<size;j++)
    //      {
    //         cout<<c[i][j]<<"\t";
    //	  }
   //       cout<<"\n";
   //     }
     
}
void sum (int ** a, int ** b, int**rnew, int size)
{
	int i, j ;
	for ( i = 0 ; i < size; i ++ ) {
		for ( j = 0 ; j <size; j ++ ) {
			rnew[ i ][j ] = a [ i ][ j ] + b [ i ][ j ] ;
		}
	}
}

void sub ( int ** a, int **b, int**rnew, int size)
{
	int i, j ;
	for ( i = 0 ; i < size; i ++ ) {
		for ( j = 0 ; j <size; j ++ ) {
			rnew[ i ][j ] = a [ i ][ j ] - b [ i ][ j ] ;
		}
	}
}

					//matrix allocation 
int **matrix_allocation ( int size ) 
{
	int **temp = new int*[size ] ;
	for ( int i = 0 ; i < size; i ++ )
	{
		temp [ i ] = new int[size ] ;
	}
	return ( temp ) ;
}

					//matrix deallocation
void matrix_deallocation ( int ** matrix, int size )
{
	if ( matrix == NULL ) {
		return ;
	}
	for ( int i = 0 ; i < size; i ++ )
	{
		delete [] matrix [i ] ;
	}
	delete[] matrix;
}
