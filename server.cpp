#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>  // memset için
#include <unistd.h>  // close için
#include <iostream>
#include <vector> // vector için
#include <math.h>  // floor için
#include <string>
#include <sstream>
#define BOYUT 1024
#define PORT 5000
#define SERVER_ADDRESS "IP"
#define CM 0.0264583333;
using namespace std;
data datas;
vector<string> vec;
 void parcala(char* alinan_veri){
    string s = alinan_veri;
    
    string  T;  
     
    stringstream X(s); 
    
    while (getline(X, T, ';')) {  
    
    if(T=="#ERR" || T=="")
        {
          cout<<"NULL DEĞER VAR yada hatalı veri"<<T<<endl;
          
          return;
        }
        else
        {
         
        ::vec.push_back(T);
        cout<<"parçalanan veriler :"<<vec.back()<<endl;
        }
    }  
    ToCantimeter(vec.at(4));
}
  void socket(){
    char veri[1024];
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_server<0){
		printf("socket oluşturulamadı\n");
		//return 1;
	}
    
    struct sockaddr_in sunucu_bilgileri;
    
    memset(&sunucu_bilgileri, 0, sizeof(sunucu_bilgileri));  // Veri yapısını sıfırlama
    
    sunucu_bilgileri.sin_family = AF_INET;
    sunucu_bilgileri.sin_addr.s_addr=INADDR_ANY;// veya  htonl(INADDR_ANY);inet_addr(SERVER_ADDRESS)
    sunucu_bilgileri.sin_port = htons(PORT);
    
  
	printf("socket başlıyor.....\n ---------------------- \n");
    // Adres bağlama
    if( bind(socket_server, (struct sockaddr*)&sunucu_bilgileri, sizeof(sunucu_bilgileri)) <0 ){
        fprintf(stderr, "Bağlama sırasında hata oluştu.");
        //return 1;
    }
 
    // Dinleme
    if( listen(socket_server, 1) < 0 ){
        fprintf(stderr, "Dinleme sırasında hata oluştu.");
        //return 1;
    }

    // istekler kabul ediliyor.
    struct sockaddr_in istemci_bilgileri;
    socklen_t boyut = sizeof(istemci_bilgileri);
    int istemci_yol = accept(socket_server, (struct sockaddr*)&istemci_bilgileri, &boyut);
    if(istemci_yol < 0){
        fprintf(stderr, "İsteklerin kabulü sırasında hata oluştu.");
        //return 1;
    }
   
    recv(istemci_yol, veri, 1024, 0);
    cout << "İstemciden gelen veri: " << veri << endl;
    
   
     parcala(veri);

    /const char mesaj = "Merhaba ben Alihan";
    if( send(istemci_yol, mesaj, strlen(mesaj), 0) < 0 ){
        fprintf(stderr, "Mesaj gönderimi sırasında hata oluştu.");
        //return 1;
    }*/
    
    close(istemci_yol);
    close(socket_server);
    
}


int main(){
    
    while (true)
    {
        socket();
        
        usleep(10000000); // 1 saniye gecikme
        
        printf("Replay ..... ---------------------- \n");
    }

    return 0;
}
