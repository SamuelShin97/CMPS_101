/*Matrix.java
 *This is where the Matrix ADT is to be implemented
 *Samuel Shin, sayshin@ucsc.edu, pa3
*/
import java.util.*;
class Matrix
{
	private static class Entry
	{
		int col;
		double value;
		
		Entry(int col, double value)
		{
			this.col = col;
			this.value = value;
		}
		
		public String toString()
		{
			String str = "";
			str = "(" + col + ", " + value + ")";
			return str;
		}	

		public boolean equals(Object object)
		{
			if (object instanceof Entry)
			{
				Object o = object;
				Entry e = (Entry) o;
				if (this.col == e.col && this.value == e.value)
				{
					return true;
				}
				else 
					return false;
			}
			else return false;
		}
	}
	//fields for Matrix
	int size;
	List[] arr;

	Matrix (int n) // Makes a new nxn Matrix. pre: n >= 1;
	{
		if (n >= 1)
		{
			size = n;
			arr = new List[size + 1];
			for (int i = 1; i <= size; i++)
			{
				List L = new List();
				arr[i] = L;
			}
		}
	}	

	static void insertEntry(List L, int c, double val) //inserts an entry in a list(row) in col order
	{
		Entry e = new Entry(c, val);
		Entry listObj = null;
		if(L.length() == 0)
		{
			L.append(e);
		}
		else
		{
			
			L.moveFront();
			while (L.index() != -1)
			{
				Object o = L.get();
				if (o instanceof Entry)
				{
					listObj = (Entry) o;
				}
				else 
					break;
				if (c >= listObj.col)
				{
					L.moveNext();
					if (L.index() == -1)
					{
						L.append(e);
						break;
					}
				}
				else 
				{
					L.insertBefore(e);
					break;
				}
			}
		}
	}
	
	void insertRow(List L) //inserts a row(list) into the array of lists or the matrix
	{
		for (int i = 1; i <= size; i++)
		{
			if (arr[i].length() == 0)
			{	
				arr[i] = L;
				break;		
			}
		}
	}

	int getSize() // returns n, the number of rows and columns of this matrix
	{
		return size;
	}
	
	int getNNZ() // Returns the number of non-zero entries in this Matrix
	{
		int nnzEntries = 0;
		for (int i = 1; i <= size; i++)
		{
			nnzEntries += arr[i].length();
		}
		return nnzEntries;
	}

	public boolean equals(Object x) //overrides Object's equals() method
	{
		if (x instanceof Matrix)
		{
			Object o = x;
			Matrix m = (Matrix) o;
			if (size != m.getSize())
			{
				return false;
			}
			else 
			{
				for (int i = 1; i <= size; i++)
				{
					if (!(arr[i].equals(m.arr[i])))
					{
						return false;
					}
				}	
				return true;
			}
		}
		else return false;
	}

	void changeEntry(int i, int j, double x) //changes ith row, jth col of this Matrix to x, pre: 1<=i<=getSize(), 1<=j<=getSize()
	{
		if (i >= 1 && i <= getSize() && j >= 1 && j <= getSize())
		{
			if (arr[i].length() > 0)
			{
				arr[i].moveFront();
				while (arr[i].index() != -1)
				{
					Object o = arr[i].get();
					Entry e = (Entry) o;
					if (e.col == j && e.value != 0)
					{
						if (x == 0)
						{
							arr[i].delete();
							break;
						}
						else 
						{
							e.value = x;
							break;
						}
					}
					else if (j < e.col || arr[i].index() == arr[i].length() - 1)
					{
						if (x == 0)
						{break;}
						else 
						{
							insertEntry(arr[i], j, x);
							break;
						}
					}
					arr[i].moveNext(); 
				}
			}
			else 
			{
				if (x == 0)
				{}
				else 
				{
					Entry firstObj = new Entry(j, x);
					arr[i].append(firstObj);
				}
			}
		}
	}
	
	
	void makeZero() //sets this Matrix to the zero state
	{
		for (int i = 1; i <= size; i++)
		{
			arr[i].clear();
		}
	}
	
	Matrix copy() //returns a new Matrix having the same entries as this Matrix
	{
		Matrix clone = new Matrix(size);
	
		for (int i = 1; i <= size; i++)
		{
			arr[i].moveFront();
			while (arr[i].index() != -1)
			{
				Object o = arr[i].get();
				Entry e = (Entry) o;
				clone.changeEntry(i, e.col, e.value);
				arr[i].moveNext();
			}
		}	
		
		return clone;
	}

	Matrix transpose() //returns a new Matrix that is the transpose of this Matrix
	{
		Matrix transpose = new Matrix(size);

		for (int i = 1; i <= size; i++)
		{
			arr[i].moveFront();
			while (arr[i].index() != -1)
			{
				Object o = arr[i].get();
				Entry e = (Entry) o;
				transpose.changeEntry(e.col, i, e.value);
				arr[i].moveNext();
			}
		}
		return transpose;
	}

	Matrix scalarMult(double x) //returns a new Matrix that is the scalar product of this Matrix and x
	{
		Matrix scalar = new Matrix(size);
		//scalar = copy();
		for (int i = 1; i <= size; i++)
		{
			arr[i].moveFront();
			while (arr[i].index() != -1)
			{
				
				Object o = arr[i].get();
				if (o instanceof Entry)
				{
					Entry e = (Entry) o;
					scalar.changeEntry(i, e.col, e.value * x);
					arr[i].moveNext();
				}
				else 
					break;
			}
		}
		return scalar;
	}
	private void helperAdd (int row, List P, List Q)
	{
		Entry ep = null;
		Entry eq = null;
		Object listp = null;
		Object listq = null;
		P.moveFront();
		Q.moveFront();
	
		while (P.index() != -1 || Q.index() != -1)
		{
			if (P.index() != -1)
			{
				listp = P.get();
			}
			if (Q.index() != -1)
			{
				listq = Q.get();
			}
			
			if (listp instanceof Entry)
			{
				ep = (Entry) listp;
			}
			else 
			{
			}
			if (listq instanceof Entry)
			{
				eq = (Entry) listq;
			}
			else
			{
			}

			if (Q.index() == -1)
			{
				changeEntry(row, ep.col, ep.value);
				P.moveNext();
				continue;
			}
	
			if (P.index() == -1)
			{
				changeEntry(row, eq.col, eq.value);
				Q.moveNext();
				continue;
			}

			if (ep.col == eq.col)
			{
				changeEntry(row, ep.col, ep.value + eq.value);
				P.moveNext();
				Q.moveNext();
			}
			else if (ep.col < eq.col) 
			{
				changeEntry(row, ep.col, ep.value);
				P.moveNext();
			}
			else if (ep.col > eq.col)
			{
				changeEntry(row, eq.col, eq.value);
				Q.moveNext();
			}
		} 
		//return newRow;
	}

	Matrix add (Matrix M) //returns a new Matrix that is the sum of this Matrix and with M, pre: getSize() == M.getSize()
	{
		Matrix sum = new Matrix(size);
		List L = new List();
		
		if (this.equals(M))
		{
			sum = this.scalarMult(2.0);
			return sum;
		}		

		else if (getSize() == M.getSize())
		{
			for (int i = 1; i <= size; i++)
			{
				sum.helperAdd(i, arr[i], M.arr[i]);
				//sum.arr[i] = L;
			}
			return sum;
		}	

		else 	
			return null;		
	}

	Matrix sub (Matrix M)
	{
		Matrix subtraction = new Matrix(size);
		subtraction = M.scalarMult(-1);
		return this.add(subtraction);
	}
	
	private static double dot (List P, List Q)
	{
		double dotProduct = 0.0;
		
		P.moveFront();
		Q.moveFront();
		Entry ep = null;
		Entry eq = null;
		while (P.index() != -1 || Q.index() != - 1)
		{
			if (P.index() == -1)
			{
				break;
			}
			if (Q.index() == -1)
			{
				break;
			}
			Object listp = P.get();
			Object listq = Q.get();
			
			if (listp instanceof Entry)
			{
				ep = (Entry) listp;
			}
			if (listq instanceof Entry)
			{
				eq = (Entry) listq;
			}

			if (ep.col == eq.col)
			{
				dotProduct += ep.value * eq.value;
				P.moveNext();
				Q.moveNext();
			}
			else if (ep.col < eq.col)
			{
				P.moveNext();
			}
			else if (ep.col > eq.col)
			{
				Q.moveNext();
			}
		}
		return dotProduct;
	}	

	Matrix mult (Matrix M)
	{
		Matrix product = new Matrix(size);
		Matrix T = M.transpose();
		
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
			{
				product.changeEntry(i, j, dot(arr[i], T.arr[j]));
			}
		}
		return product;
	}

	public String toString() //overrides object's tostring
	{
		String str = "";
		String str2 = "";
		
		for (int i = 1; i <= size; i++)
		{
			if (arr[i].length() > 0)
			{
				str = i + ": ";
			
				arr[i].moveFront();
				while (arr[i].index() != -1)
				{
					Object o = arr[i].get();
					Entry e = (Entry) o;
					if (arr[i].index() == arr[i].length() - 1)
					{
						str += e;
					}
					else
					{
						str += e + " ";
					}

					arr[i].moveNext();
				}
				str2 += str + System.lineSeparator();
			}
			else 
			{
				str2 += "";
			}
		
		}	
		return str2;
	}
}
