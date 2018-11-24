//List.java
//This file is where the List ADT resides in for pa3.
//Samuel Shin, sayshin@ucsc.edu, pa3
class List
{
	private class Node
        {
		//fields
		Object data;
		Node next;
		Node previous;
		
		//constructor
		Node (Object data)
		{
			this.data = data;
			next = null;
			previous = null;
		}	
		
		//toString(): overrides Object's toString() method
		public String toString()
		{
			return String.valueOf(data);
		}

		public boolean equals (Object x)
		{
			if (x instanceof Node)
			{
				Object o = x;
				Node n = (Node) o;
				if (this == n)
				{
					return true;
				}
				else return false;	
			}
			else return false;
		}
	}
	
	//fields for List
	private Node front;
	private Node back;
	private Node cursor;
	private int length;
	private int index;

	List()//constructor for the List adt
	{
		front = null;
		back = null;
		cursor = null;
		length = 0;
		index = -1;
	}	
	
	int length() //returns the number of elements in the list
	{
		return length;	
	}	

	int index()
	{
		if (cursor != null) //if cursor is defined, returns the index of the cursor element,
				    //otherwise returns -1.
		{	
			return index;
		}
		else 
		{
			return -1;
		}
	}

	Object front() //returns front element. Pre: length() > 0
	{
		if (length() > 0)
		{
			return front.data;
		}
		else return -1;	
	}

	Object back() //returns back element. Pre: length() > 0
	{
		if (length() > 0)
		{
			return back.data;
		}
		else return -1;
	}

	Object get() //returns cursor element. Pre: length() > 0, index >= 0
	{
		if (length() > 0 && index >= 0)
		{
			return cursor.data;
		}
		else return -1;
	}

	public boolean equals (Object x) //returns true if and only if this List and L are the same
				//integer sequence. The states of the cursors in the two lists
				//are not used in determining equality.
	{
		if (x instanceof List)
		{
			Object o = x;
			List L = (List) o;	
			moveFront();
			L.moveFront();
			if (length != L.length)
			{
				return false;
			}
			else 
			{
				while (cursor != null)
				{
					if (!(cursor.data.equals(L.cursor.data)))
					{
						return false;		
					}
					moveNext();
					L.moveNext();
				}
			}
			return true;
		}
		else return false;
		
	}

	void clear() //resets this list to its original empty state
	{
		length = 0;
		index = 0;
		front = null;
		back = null;
		cursor = null;
	}	

	void moveFront() //if list is non-empty, places the cursor under the front element
			 //otherwise does nothing
	{
		if (length() > 0)
		{
			cursor = front;
			index = 0;
		}
	}

	void moveBack() //if list is non-empty, places the cursor under the back element
			//otherwise does nothing
	{
		if (length() > 0)
		{
			cursor = back;
			index = length - 1;
		}
	}

	void movePrev() //if cursor is defined and not at front, moves cursor one step toward
			//front of this list, if cursor is defined and at front, cursor becomes
			//undefined, if cursor is undefined does nothing
	{
		if (cursor != null && cursor != front) 
		{
			cursor = cursor.previous;
			index--;
		}
		else if (cursor != null && cursor == front)
		{
			cursor = null;
			index = -1;
		}
		else if (cursor == null)
		{}
	}

	void moveNext() //if cursor is defined and not at back, moves cursor one step toward
			//back of this list, if cursor is defined and at back, cursor becomes
			//undefined, if cursor is undefiend does nothing
	{
		if (cursor != null && cursor != back)
		{
			cursor = cursor.next;
			index++;
		}
		else if (cursor != null && cursor == back)
		{
			cursor = null;
			index = -1;
		}
		else if (cursor == null)
		{}
	}

	void prepend (Object data) //insert new element into this List. if List is non-empty,
				//insertion takes place before front element.
	{
		if (length() > 0)
		{
			Node n = new Node(data);
			front.previous = n;
			n.next = front;
			front = n;
			length++;
		}
		else //if list is empty new element is the first element in list
		{
			Node n = new Node(data);
			front = n;
			back = n;
			length++;	
		}
		
		if (cursor != null)
		{
			index++;
		}
	}
	
	void append (Object data) //insert new element into this List. if List is non-empty,
			       //insertion takes place after back element
	{
		if (length() > 0)
		{
			Node n = new Node(data);
			back.next = n;
			n.previous = back;
			back = n;
			length++;
		}
		else //if list is empty new element is the first element in list
		{
			Node n = new Node(data);
			front = n;
			back = n;
			length++;
		}

		if (cursor == back)
		{
			index++;
		}
	}

	void insertBefore (Object data) //insert new element before cursor
				     //pre: length() > 0, index >= 0
	{
		if (length() > 0 && index >= 0)
		{
			if (cursor == front) //if the cursor is defined as front
			{
				prepend(data);
				
			}
			else //if cursor is somewhere between front(exclusive) and back(inclusive) of list add it in before cursor
			{
				Node n = new Node(data);
				cursor.previous.next = n;
				n.previous = cursor.previous;
				n.next = cursor;
				cursor.previous = n;
				index++;
				length++;
			}
		}
	}

	void insertAfter (Object data) //insert new element after cursor
				    //pre: length() > 0, index >= 0
	{
		if (length() > 0 && index >= 0)
		{
			if (cursor == back)
			{
				append(data);
			}
			else //if cursor is somewhere between front(inclusive) and back (exclusive) of list add it in after cursor
			{
				Node n = new Node(data);
				cursor.next.previous = n;
				n.next = cursor.next;
				n.previous = cursor;
				cursor.next = n;
				length++;
			}
		}
	}

	void deleteFront() //deletes the front element. Pre: length() > 0
	{
		if (length() > 0)
		{
			if (length() == 1)
			{
				clear();
			}
			else
			{
				front = front.next;
				front.previous = front.previous.previous;	
				length--;
			}
		}
		if (index > 0)//if the index isn't at the front
		{
			index--;
		}
		else if (index == 0)
		{
			cursor = null;
			index = -1;
		}
	}
	
	void deleteBack() //deletes the back element. Pre: length() > 0
	{
		if (length() > 0)
		{
			if (length() == 1)
			{
				clear();
			}
			else 
			{
				back = back.previous;
				back.next = back.next.next;
				length--;
			}
		}
		if (index == length())
		{
			cursor = null;
			index = -1;
		}
		
	}

	void delete() //deletes cursor element, making cursor undefined.
		      //Pre: length() > 0, index >= 0
	{
		if (length() == 1 && index >= 0)
		{
			clear();
		}
		else if (length() > 0 && index >= 0)
		{
			if (cursor == front)
			{
				deleteFront();
			}
			else if (cursor == back)
			{
				deleteBack();
			}
			else 
			{
				cursor.previous.next = cursor.next;
				cursor.next.previous = cursor.previous;
				cursor = null;
				index = -1;
				length--;
			}
		}
	}
	
	public String toString() //overrides object's toString method. Returns a string
				 //representation of this List consisting of a space
				 //separated sequence of integers, with front on left.
	{
		String str = "";
		moveFront();
		while (cursor != null)
		{
			if (cursor == back)
			{
				str += cursor.data + "";
				moveNext();
			}
			else 
			{
				str += cursor.data + " ";
				moveNext();
			}
		}
		return str;
	}

	/*List copy() //returns a new List representing the same integer sequence as this
		    //List. The cursor in the new list is undefined, regardless of the 
		    //state of the cursor in this List. This List is unchanged
	{
		List clone = new List();
		moveFront();
		while (cursor != null)
		{
			clone.append(cursor.data);
			moveNext();
		}
		moveFront();
		return clone;
	}*/	
}
