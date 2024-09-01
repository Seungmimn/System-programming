#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

//int main(int argc, char **argv)
int main(int argc, char * argv[])
{
	int n, in, out;
	char buf[1024];

	if ( argc < 3){
//		write(1 , "Usage : copy file1 file2\n", 30);
//		printf("Usage : copy file1 file2\n");
		fputs("Usage : copy file1 file2\n", stderr);
		return 1;
	}

	if ((in = open(argv[1], O_RDONLY)) < 0){
		perror(argv[1]);
		return 2;
	}

	if ((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0){
		perror(argv[2]);
		return 3;
	}

	while(1)
	{
		n = read(in, buf, sizeof(buf));
		if(n > 0)
			write(out, buf, n);
		else if(n == 0)
			break;
		else
			perror("open");
	}
/*
    do
	{
		 n = read(in, buf, sizeof(buf));
         printf("n : %d\n", n);
		 if(n > 0)
		 	write(out, buf, n);
         else if(n == 0)
             break;
         else
             perror("open");
    }while
*/
	close(out);
	close(in);

	return 0;
}
