#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <ext/stdio_filebuf.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class myistream: public istream
{
    typedef __gnu_cxx::stdio_filebuf<char> filebuf_t;
    filebuf_t *filebuf;
public:
    myistream(int fd)
        :istream(filebuf = new filebuf_t(fd, std::ios::in))
    {
    }
    ~myistream()
    {
        delete filebuf;
    }
};

class myostream: public ostream
{
    typedef __gnu_cxx::stdio_filebuf<char> filebuf_t;
    filebuf_t *filebuf;
public:
    myostream(int fd)
        :ostream(filebuf = new filebuf_t(fd, std::ios::out))
    {
    }
    ~myostream()
    {
        delete filebuf;
    }
};

int fib(int n){
	int pid, pid2;
	if ( n > 10 ) return -1;
	if ( n <= 1 ) return 0;
	if ( n < 3 ) return 1;

	int pipe1[2], pipe2[2];
	pipe (pipe1);
	pipe (pipe2);
	int temp1,temp2,a;

	myistream myin1(pipe1[0]);
  myistream myin2(pipe2[0]);

	myostream myout1(pipe1[1]);
  myostream myout2(pipe2[1]);

	if (pid = fork())	{
		if (pid2 = fork()) {
      //parent
			myin1 >> temp1;
			myin2 >> temp2;
			return temp1+temp2;
		}
		else {
			myout1 << fib(n-1) << endl;
      exit(1);
    }
  }
	else {
		myout2 << fib(n-2) << endl;
    exit(1);
  }

}

int main(){
	int n;
  while(cin >> n){
	cout << "fib (" << n << ") = " << fib(n) << endl;
  }
	return 0;
}



