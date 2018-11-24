/*MatrixTest.java
 *This file is used for testing the Matrix ADT and checking that all of its public functions work the way they should
 *Samuel Shin, sayshin@ucsc.edu, pa3
 */

class MatrixTest
{
	public static void main (String[] args)
	{
		Matrix A = new Matrix(3);
		Matrix B= new Matrix(3);

		
		List list1 = new List();
		List list2 = new List();
		List list3 = new List();
		List list1b = new List();
		List list2b = new List();
		List list3b = new List();

		A.insertEntry(list1, 1, 1.0);
		A.insertEntry(list1, 3, 3.0);
		A.insertEntry(list1, 2, 2.0);
		A.insertEntry(list2, 2, 2.0);
		A.insertEntry(list2, 3, 3.0);
		A.insertEntry(list3, 3, 3.0);
		A.insertEntry(list3, 1, 1.0);

		B.insertEntry(list1b, 1, 1.0);
		B.insertEntry(list1b, 3, 3.0);
		B.insertEntry(list1b, 2, 2.0);
                B.insertEntry(list2b, 2, 2.0);
                B.insertEntry(list2b, 3, 3.0);
                B.insertEntry(list3b, 3, 3.0);
                B.insertEntry(list3b, 1, 1.0);
		
		System.out.println(list1);
		System.out.println(list2);
		System.out.println(list3);//checks if values load in col order into lists
	
		System.out.println();
		System.out.println(A.getSize());//makes sure getSize works
		
		System.out.println();
		A.insertRow(list1);
		A.insertRow(list2);
		A.insertRow(list3);
		B.insertRow(list1b);
		B.insertRow(list2b);
		B.insertRow(list3b);
		System.out.println(A.getNNZ());	//checks if getNNZ works

		System.out.println();
		System.out.println(A.equals(B)); //checks if equals method work
		B.changeEntry(1, 1, 5.0);
		System.out.println(A.equals(B));

		A.changeEntry(1, 1, 5.0); //checks for overwriting existing value to a new one
		A.changeEntry(2, 2, 0.0); //checks for setting an existing value to 0
		A.changeEntry(3, 2, 2.0); //checks for setting a value that is zero in the matrix to a nnz value
		
		System.out.println();
		System.out.println(list1);
		System.out.println(list2);
		System.out.println(list3);

		System.out.println();
		System.out.println("Matrix A:" + System.lineSeparator() + A); //checks if toString works properly

		System.out.println();
		B = A.copy();
		System.out.println("Matrix B:" + System.lineSeparator() + B); //checks if copy works properly
			
		System.out.println();		
		System.out.println("Transpose of A: " + System.lineSeparator()+ A.transpose()); //checks for the transpose of A

		System.out.println();
		System.out.println("Scalar Mult of Matrix A: " + System.lineSeparator() + A.scalarMult(2.0)); //checks for scalar mult of A
		
		System.out.println();
		B.changeEntry(1, 1, 0);
		B.changeEntry(2, 1, 1);
		B.changeEntry(3, 3, 0);
		System.out.println("Matrix A: " + System.lineSeparator() + A);
		System.out.println("Matrix B: " + System.lineSeparator() + B);
		Matrix C = A.add(B);
		System.out.println("Sum of Matrices A and B " + System.lineSeparator() + C); //checks add method

		System.out.println();
		System.out.println("Sub of Matrices A and B " + System.lineSeparator() + A.sub(B));

		System.out.println();
		System.out.println("Product of Matrices A and B: " + System.lineSeparator() + A.mult(B)); //checks mult method

		A.makeZero();
		String str = "makeZero worked";
		System.out.println(A + str); //checks and sees if makeZero works properly
	}
}
