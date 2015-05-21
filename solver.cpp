// Back Tracking Algorithm

/*
	Author: Kunaal Jain
	Email: kunaalus@gmail.com
*/

#include<bits/stdc++.h>
using namespace std;

// Global Variables
int row[10][10],col[10][10],box[10][10],counter=0;
int arr[9][9];

//Our main solver function
int solver(int r, int c)
{
	//How many times the function is called (Performance)
	counter++;
	//If the square is blank
	if(arr[r][c]==0)
	{
		int flag = 0, i = 1;
		// Try digits from 1 to 9 or till flag is not equal to 0
		while(i<10&&flag==0)
		{
			// If the digit is valid in the square
			if(row[r][i]==0&&col[c][i]==0&&box[((int)r/3)*3 + ((int)c/3)][i]==0)
			{
				arr[r][c]=i;
				row[r][i]=1;
				col[c][i]=1;
				box[((int)r/3)*3+ (int)c/3][i]=1;
				// Fill this digit and continue
				flag = solver(r,c);
				// Wrong digit, Backtrack
				if(flag == 0)
				{
					arr[r][c]=0;
					row[r][i]=0;
					col[c][i]=0;
					box[((int)r/3)*3 + ((int)c/3)][i]=0;
					i++;
				}
			}
			else i++;
		}
		// All good, we have solved the puzzle
		if(r==8&&c==8) return 1;
		return flag;
	}
	else
	{
		// Driver in case square is not empty
		if(r==8&&c==8) return 1;
		if(r<8&&c==8) return solver(r+1,0);
		if(r<=8&&c<8) return solver(r,c+1);
	}
}

// Function to verify the sudoku array
int verify()
{
	int r[10][10]={0}, c[10][10]={0}, sq[10][10]={0};
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(r[i][arr[i][j]]==1) return 0;
			else r[i][arr[i][j]]=1;
			if(c[j][arr[i][j]]==1) return 0;
			else c[j][arr[i][j]]=1;
			if(sq[((int)i/3)*3 + ((int)j/3)][arr[i][j]]==1) return 0;
			else sq[((int)i/3)*3 + ((int)j/3)][arr[i][j]]==1;
		}
	}
	return 1;
}

int main(int argc, char const *argv[])
{
	// Input file
	freopen("sudoku.txt","r",stdin);
	int i,j;

	// Read from file
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			char x;
			cin>>x;
			if(x=='.') arr[i][j]=0;
			else if(x<'0'||x>'9') j--;
			else arr[i][j]=x-'0';
		}
	}

	// Output the inital puzzle
	for(i=0;i<9;i++)
	{
		if(i%3==0) cout<<"------------"<<endl;
		for(j=0;j<9;j++)
		{
			if(j%3==0) cout<<'|';
			cout<<arr[i][j];
		}
		cout<<endl;
	}

	// Initalize the global values
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(arr[i][j]!=0)
			{
				row[i][arr[i][j]]=1;
				col[j][arr[i][j]]=1;
				box[((int)i/3)*3 + ((int)j/3)][arr[i][j]]=1;
			}

	// Clock for performace
	int start_s=clock();
	
	// Call the solver function
	int res=solver(0,0);
	
	int stop_s=clock();


	if(res==1) cout<<"SUCCESS"<<endl;
	else cout<<"FAIL"<<endl;
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	
	// Output the solved puzzle
	for(i=0;i<9;i++)
	{
		if(i%3==0) cout<<"------------"<<endl;
		for(j=0;j<9;j++)
		{
			if(j%3==0) cout<<'|';
			cout<<arr[i][j];
		}
		cout<<endl;
	}

	// Verify
	res=verify();
	if(res==1) cout<<"CORRECT"<<endl;
	else cout<<"ERROR! WRONG"<<endl;

	return 0;
}