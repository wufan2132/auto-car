#include "planning/replay.h"


replay::replay(string path,string io){
     if(io=="read"){
        mode =1;
        save_path = path;
        if(DEBUG){
            string str = "auto-car/ros/";
            int index = save_path.find(str);
            save_path = save_path.substr(index+str.size());
        }
        inFile.open(save_path.c_str(), ios::in); // 打开模式可省略
        char cwd[50];
        getcwd(cwd,sizeof(cwd));
        cout<<"inFile open:"<<cwd<<endl;
    }else if(io=="write"){
        mode = 2;
        save_path = path;
        if(DEBUG){
            string str = "auto-car/ros/";
            int index = save_path.find(str);
            save_path = save_path.substr(index+str.size());
        }
        outFile.open(save_path.c_str(), ios::out); // 打开模式可省略
        char cwd[50];
        getcwd(cwd,sizeof(cwd));
        cout<<"outFile open:"<<cwd<<endl;
    }else
        mode=0;
};

replay::~replay(){
    if(mode==1)
        inFile.close();
    else if(mode==2)
        outFile.close();
}

void replay::readinit(string path){
        if(mode==0){
            mode =1;
            save_path = path;
            inFile.open(save_path.c_str(), ios::in); // 打开模式可省略
            char cwd[50];
            getcwd(cwd,sizeof(cwd));
            cout<<"inFile open:"<<cwd<<endl;
        }
}
void replay::writeinit(string path){
        if(mode==0){
            mode = 2;
            save_path = path;
            outFile.open(save_path.c_str(), ios::out); // 打开模式可省略
            char cwd[50];
            getcwd(cwd,sizeof(cwd));
            cout<<"outFile open:"<<cwd<<endl;

        }
}

void replay::reset(){
    if(mode==1){
        inFile.clear();
        inFile.seekg(0,ios::beg);
    }
    else if(mode==2){
        outFile.seekp(0,ios::beg);
    }
}

void replay::close(){
    if(mode==1)
        inFile.close();
    else if(mode==2)
        outFile.close();
    mode = 0;
}



bool replay::readOnce(car_msgs::trajectory_point &point){
    static int count = 0;
    if(mode!=1) 
    {
        cout<<"mode err!";
        return 0;
    }
    string lineStr;
    getline(inFile, lineStr);
    if(lineStr.size()<10)
    {
        count = 0;
        return 0;
    }
        
    stringstream ss(lineStr);
	string str;
    point.header.seq = count;

    getline(ss, str, ',');
    point.x=atof(str.c_str());
    getline(ss, str, ',');
    point.y=atof(str.c_str());
    getline(ss, str, ',');
    point.z=atof(str.c_str());
    getline(ss, str, ',');
    point.theta=atof(str.c_str());
    getline(ss, str, ',');
    point.kappa=atof(str.c_str());
    getline(ss, str, ',');
    point.s=atof(str.c_str());
    getline(ss, str, ',');
    point.speed=atof(str.c_str());
    getline(ss, str, ',');
    point.accel=atof(str.c_str());
    getline(ss, str, ',');
    point.relative_time=atof(str.c_str());
    count++;
    return 1;
}

bool replay::saveOnce(car_msgs::trajectory_point point, int period){
    if(mode!=2){
        cout<<"mode err!";
        return 0;
    }
    static int count=0;
    count++;
    if(count>=period){
        count=0;
        cout<<"x:"<<point.x<<"  y:"<<point.y<<endl;
        outFile<<point.x<<",";
        outFile<<point.y<<",";
        outFile<<point.z<<",";
        outFile<<point.theta<<",";
        outFile<<point.kappa<<",";
        outFile<<point.s<<",";
        outFile<<point.speed<<",";
        outFile<<point.accel<<",";
        outFile<<point.relative_time<<",";
        outFile<<std::endl;
    }
    
    return 1;
}