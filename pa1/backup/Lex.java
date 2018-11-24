//Lex.java
//This program reads in an input file and produces and output file 
//that sorts the input file in alphabetical order by line by using 
//the List ADT that is defined in List.java
//Samuel Shin, sayshin@ucsc.edu, PA1
import java.io.*;
import java.util.*;

class Lex
{
	public static void main (String[] args) throws IOException
	{
		Scanner in = null;
		PrintWriter out = null;
		String line = null;
		int linenum = 0;		
		int i = 0;

		if (args.length < 2)
		{
			System.err.println("Usage: FileIO infile outfile");
			System.exit(1);
		}

		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		while (in.hasNextLine())
		{
			linenum++;
			in.nextLine();
		}
		
		String[] arr = new String[linenum];
		in = new Scanner(new File(args[0])); //reset the scanner to look at top of file again
		
		while (in.hasNextLine())
		{
			line = in.nextLine();
			arr[i] = line;
			i++;				
		}
		
		List list = new List();

		sort(arr, list);
		int a = 0;
                list.moveFront();
                while (list.index() >= 0)
                {
                        a = list.get();
                        out.println(arr[a]);
			out.flush();
                        list.moveNext();
                }
		
		in.close();
		out.close();
		
	}	

	static void sort (String[] A, List L)
	{
		int temp = 0;
		int j = 0;
		int temp2 = 0;
		boolean pass;
		for (int i = 1; i < A.length; i++)
		{
			temp = i;
			j = i -1;
			L.moveBack();
			pass = false;
			if (L.length() == 0)
                        {
                                if (A[j].compareTo(A[temp]) < 0)
                                {
                                        L.prepend(j);
                                        L.append(temp);
					continue;
                                }
                                else
                                {
                                        L.prepend(temp);
                                        L.append(j);
					continue;
                                }
                        }
			while (j >= 0)
			{
				if (A[temp].compareTo(A[j]) < 0)
				{
					L.movePrev();
				}
				if (L.index() == -1)
				{
					L.prepend(temp);
					pass = true;
				}
				j--;	
			}
			if (pass == false)
			{
				L.insertAfter(temp);
			}
		}
	}

}
