/* #include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main()
{
    int fd;

    fd = open("deneme.txt", O_WRONLY | O_CREAT  | O_RDONLY, 0644);
    if (fd == -1)
    {
        printf("Error\n");
        return (1);
    }

    char   test[120];
    
    //dup2(fd, 1);
    //write(1, "onder abi\n", 10);
    dup2(fd, 0);
    read(0, test, 100);
    write(1, test, 100);
}

 */


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main()
{
    int fd;

    fd = open("deneme.txt", O_RDONLY, 0644);
    if (fd == -1)
    {
        printf("Error\n");
        return (1);
    }

    char test[100]; // 100 baytlık bir diziyi okuyacağız, bu nedenle boyutunu 100 olarak belirleyin
    
    // Dosyayı sıfırdan okumak istediğimiz için input yönlendirme işlemini doğru şekilde yapmalıyız
    dup2(fd, 0);
    
    int bytes_read = read(0, test, 100); // Okunan bayt sayısını kontrol etmek için dönüş değerini kullanın
    if (bytes_read == -1)
    {
        printf("Error reading from file\n");
        return (1);
    }

    // Okunan bayt sayısı kadar yazma işlemi gerçekleştirin
    write(1, test, bytes_read);

    return 0;
}
