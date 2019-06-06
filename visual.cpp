#include <stdlib.h>
#include <iostream>
#include <sys/ioctl.h>
#include <cmath>
#include <sys/ioctl.h>
#include <stdio.h>



using namespace std;

void center_text(string s){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    for (int i =0; i<floor(w.ws_col/2)-floor(s.size()/2);i++){
        cout<<"I";
    }
    cout<<"\e[2K";
    cout<<s<<'\n';

}
void line_break(){
       struct winsize w;
       ioctl(0, TIOCGWINSZ, &w);
    for (int i =0; i<w.ws_col;i++){
        cout<<"-";
    }
}
void margin_text(int n, string s){
    for (int i =0;i<n;i++){
        cout<<"I";
    }
      cout<<"\e[2K";
      cout<<s<<'\n';

}
int main(){
     
     int scene = 0;
     while (scene ==0){       
     printf("\033c");
     
     string s ="C++ neural network demo";
     
     cout<<"\e[1m";
     center_text(s);
     
     line_break();
     cout<<"\e[0m";
     cout<<"\n\n\n";
     cout<<"\e[1;4m";
     center_text("Select mode:");
     cout<<"\e[0m";
     center_text("1. testing");
     center_text("2. traning");
     char c;
     cin>>c;
    if( c=='1'){
        scene =1;
    }
     }
    while(scene==1){
        printf("\033c");
        cout<<"\e[1m";
        string s ="C++ neural network demo";
        
        center_text(s);
        line_break();
        cout<<"\n\n\n";
        cout<<"\e[1;4m";
        center_text("Input path to mnist file:");
        cout<<"\e[0m";
        string s2;
        cin>>s2;
        cout<<s;
        char c;
        cin>>c;
    }

}
