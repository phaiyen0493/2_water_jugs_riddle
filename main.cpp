/*Name: Yen Pham
Class: CSCE2100
Instructor: ABM Rezbaul Islam
Description: The purpose of this program is to decide for the user 
how to obtain an ammount given 2 jugs
*/

#include <iostream>
using namespace std;

class Jug
{
	private:
	int capacity; //water capacity of a jug
	int value; //actual water amount in a jug
	
	public:
	Jug (int water_amount)
	{
		capacity = water_amount; //set jug's capacity 
		value = 0; // both jug is empty in the beginning
	}

	void Fill() // fill water until full
	{
		value = capacity;
	}

	void Empty()// empty the jug
	{
		value = 0;
	}

	bool isFull() // check if the jug is full
	{
		if (value < capacity) //return false if the jug is not full
		{
			return false;
		}
		else
		{
			return true;
		}
	}		
	
	bool isEmpty() // check if the jug is empty
	{
		if (value == 0) // return true if the water ammount is 0
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int getValue()
	{
		return value;
	}

	int getCapacity()
	{
		return capacity;
	}

	void pour(Jug &Random)
	{
		int old_value = value;

		value = value + Random.value; //get new water amount after being poured

		if (value > capacity)
		{
			value = capacity;// we just pour water until the jug is full
		}

		Random.value = Random.value - (value - old_value);// water ammount remaining
	}
};

int gcd (int a, int b) // find greatest common divisor
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return gcd(b, a % b);
	}  
}

bool check (int a, int b, int g) // check if the water amount g request can be done with 2 given jugs capacity a and b
{
	if (g % gcd(a,b) == 0) 
	{
		return true; 
	}

	else
	{
		return false;
	}
}

void solve(Jug A, Jug B, int result)
{
	while(A.getValue() + B.getValue() != result) //continue with the loop until the water goal is reached
	{
		//Solve simpliest cases
		if (A.getCapacity() == result || B.getCapacity() == result || A.getCapacity() + B.getCapacity() == result)
		{
			if (A.getCapacity() == result) //fill Jug A if the water goal equals to Jug A's capacity
			{
				cout<<"Fill A" << endl;
				A.Fill();
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B
			}
			
			if (B.getCapacity() == result) //fill Jug B if the water goal equals to Jug B's capacity

			{
				cout<<"Fill B" << endl; 
				B.Fill();
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl;//display water value in jug A and B
			}

			if (A.getCapacity() + B.getCapacity() == result) //fill both jug A and jug B if the water goal equals to Jug A + Jug B's capacity

			{
				cout<<"Fill A" << endl;
				A.Fill();
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B

				cout<<"Fill B" << endl;
				B.Fill();
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B			
			}
		}

		//Solve other cases
		else
		{
			if(A.isEmpty()) // fill jug A if jug A is empty
			{
				cout<<"Fill A" << endl;
				A.Fill();
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B
			}

			if(B.isFull() && !A.isEmpty() && !A.isFull()) // empty jug B if jug B is full but water goal has not been reached
			{
				cout<<"Empty B" << endl;
				B.Empty();
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B
			}

			if (!B.isFull() && A.getValue() + B.getValue() != result) // pour jug A into jug B if A is not full and water goal has not been reached
			{
				cout<<"Pour A into B" << endl;
				B.pour(A);
				cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B
			}
		}
	}
}

int main()
{
// Display name, EUID, e-mail address, the department name, and course number
	cout << "\n\t+----------------------------------------------+" << endl;
	cout << "\t|       Computer Science and Engineering       |" << endl;
	cout << "\t|      CSCE 2100 - Computing Foundation I      |" << endl;
	cout << "\t|   Yen Pham    yhp0005    yenpham@my.unt.edu  |" << endl;
	cout << "\t+----------------------------------------------+" << endl;

// Start program
	int jugA, jugB, goal;

	do // continue the loops until jug A's capacity is a positive integer
	{
		cout << "Enter capacity of Jug A: "; //prompt user to enter capacity of A
		cin >> jugA;

		// display error if capacity of A is less than or equal to 0
		if (jugA <= 0)
		{
			cout << "Capacity of Jug A has to be a positive integer" << endl;
		}
	} while (jugA <= 0);
	
	do // continue the loops until jug B's capacity is a positive integer
	{
		cout << "Enter capacity of Jug B: "; //prompt user to enter capacity of B
		cin >> jugB;

		// display error is capacity of B is less than or equal to 0
		if (jugB <= 0)
		{
			cout << "Capacity of Jug B has to be a positive integer" << endl;
		}

	} while (jugB <= 0);

	do // continue the loops until the water goal's requirement is reached
	{
		cout << "Enter water target: "; //prompt user to enter water goal
		cin >> goal;

		// display error if water goal exceeds the sum of two jugs' capacity
		if (goal > jugA + jugB)
		{
			cout << "Required water amount has to be less than or equal to the sum of Jug A and Jug B" << endl;
		}
	} while (goal > jugA + jugB);

	if (check (jugA, jugB, goal)) // check if water goal can be obtained using 2 given capacities
	{
		Jug A(jugA); // create object jug A and set the capacity
		Jug B(jugB); // create object jug B and set the capacity
		cout << "Beginning" << endl;
		cout << "(A, B) = (" << A.getValue() << ", " << B.getValue() << ")" << endl; //display water value in jug A and B
		solve(A, B, goal); // call the function to display steps to reach the water goal
		cout<< "Done!" << endl; // sucessfully obtain water goal
	}
	else // execute if water goal cannot be obtained  
	{
		cout << "Can't reach this stage with the given jugs" << endl;
	}

	return 0;
}