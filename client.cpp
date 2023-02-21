#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>  // memset için
#include <unistd.h>  // close için
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <math.h> 
#define BOYUT 1024
#define PORT 8080
#define SERVER_ADDRESS "IP"
#define pixels_per_inch 96.0
#define CM 0.0264583333;

using namespace std;

void ToCantimeter(string num){
    
    cout<<"kullanılan veri :"<<num<<endl;
    double Tocm = stod(num);
   
    cout<<"değiştirelen veri :"<<Tocm<<endl;
    Tocm= Tocm * CM ;
    Tocm= floor(Tocm);
    
    cout<<"CM :"<<Tocm<<endl;
    //double deneme=stod(alinan_veri);
    //cout<<"Pixel to CM "<<( deneme / pixels_per_inch)*2.54<<endl;
   // cout<<"bu veri string "<<s<<endl;
}
 void parcala(char* alinan_veri){
    string s = alinan_veri;
    vector<string> vec;
    string  T;  
    // use getline() function to read a line of string and store into S variable.  
    stringstream X(s); // X is an object of stringstream that references the S string  
    // use while loop to check the getline() function condition  
    while (getline(X, T, ';')) {  
    /* X represents to read the string from stringstream.
    *  T use for store the token string and. 
    ' ' whitespace represents to split the string where whitespace is found. */
    vec.push_back(T);  
    cout<<"parçalanan veriler :"<<vec.back()<<endl;
    }  
    ToCantimeter(vec.at(1));
    ToCantimeter(vec.at(2));
    ToCantimeter(vec.at(3));
}
    

int main(){



    // Bağlanılacak sunucu ayarları
    struct sockaddr_in sunucu_bilgileri;
    
    memset(&sunucu_bilgileri, 0, sizeof(sunucu_bilgileri));
    
    sunucu_bilgileri.sin_family = AF_INET;
    sunucu_bilgileri.sin_port = htons(PORT);
    
    if(inet_pton(AF_INET, SERVER_ADDRESS, &sunucu_bilgileri.sin_addr)<0){
        fprintf(stderr, "IP/PORT HATALI!!! \n");
        return 1;
        }
    printf("Sunucu Kontrol Ediliyor....\n");
    

    int socket_client = socket(AF_INET, SOCK_STREAM, 0);

    // Sunucuya bağlanma
    if( connect(socket_client, (struct sockaddr*)&sunucu_bilgileri, sizeof(sunucu_bilgileri)) < 0 ){
        fprintf(stderr, "Sunucu bağlantısı sırasında hata oluştu.\n");
        return 1;
    }
    printf("Sunucuya Bağlandın....\n");
    
    const char* message = "t";
    if (write(socket_client, message, strlen(message)) < 0) {
        printf ("mesaj gönderilemedi hata!!!!! \n");
        return -1;
    }
    char alinan_veri[1024];
    int veri_boyutu = recv(socket_client, alinan_veri, BOYUT, 0);

    if(veri_boyutu < 0){
        fprintf(stderr, "Veri alımı sırasında hata oluştu.\n");
        return 1;
    }
    parcala(alinan_veri);

        
        //fprintf(stdout, "Alınan veri: %s\n", alinan_veri);
        
        
        
        
     
        
    close(socket_client);
    return 0;
}

