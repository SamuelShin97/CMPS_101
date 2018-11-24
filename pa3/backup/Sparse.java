/*Sparse.java
 * Sparse acts like the client for the Matrix ADT. 
 * It takes in an input file and outputs an output file
 * doing performing operations on the two matrices given
 * in the input file.
 * Samuel Shin, sayshin@ucsc.edu, pa3.
 */
import java.util.*;
import java.io.*;

class Sparse
{
	public static void main (String[] args) throws IOException
        {
                Scanner in = null;
                PrintWriter out = null;
                String line = null;
		int matrixSize = 0;
		Matrix A = null;
		Matrix B = null;
		boolean firstPass = true;
		boolean skipA = false;
                if (args.length < 2)
                {
                        System.err.println("Usage: FileIO infile outfile");
                        System.exit(1);
                }

                in = new Scanner(new File(args[0]));
                out = new PrintWriter(new FileWriter(args[1]));

		while (in.hasNextLine())
		{
			line = in.nextLine().trim();
			String[] token = line.split("\\s+");
			
			if (firstPass == true)
			{
				matrixSize = Integer.parseInt(token[0]); //this is just used to get the size of A and B
				A = new Matrix(matrixSize);
				B = new Matrix(matrixSize);
				firstPass = false; //set flag to never enter this if statement again
				line = in.nextLine(); //skips the first empty line
			}
			else
			{
				if (skipA == false) //still in matrix A
				{
					if (token.length < 3) //if the empty line
					{
						skipA = true;
						continue;
					}
					int row = Integer.parseInt(token[0]);
					int col = Integer.parseInt(token[1]);
					double val = Double.parseDouble(token[2]);

					A.changeEntry(row, col, val);
				}
				else //you are now putting stuff into matrix B
				{
					int row = Integer.parseInt(token[0]);
					int col = Integer.parseInt(token[1]);
					double val = Double.parseDouble(token[2]);

					B.changeEntry(row, col, val);
				}
			}
		}

		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A);

		out.println("B has " + B.getNNZ() + " non-zero entries:");
                out.println(B);	

                out.println("(1.5)*A = ");
                out.println(A.scalarMult(1.5));

		out.println("A+B = ");
		out.println(A.add(B));

		out.println("A+A = ");
		out.println(A.add(A));

		out.println("B-A = ");
		out.println(B.sub(A));
			
		out.println("A-A = ");
		out.println(A.sub(A));

		out.println("Transpose(A) = ");
		out.println(A.transpose());
	
		out.println("A*B = ");
		out.println(A.mult(B));
		
		out.println("B*B = ");
		out.println(B.mult(B));

		out.flush();
		in.close();
		out.close();
	}	
}
